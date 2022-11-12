//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2020, Profoundic Technologies, Inc.
// All rights reserved.
//============================================================================

#include "vbuf_expr.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// add_vbuf_expression_ops
//============================================================================
namespace
{
  typedef vbuf_expression_parser_t::var_t var_t;
  typedef vbuf_expression_parser_t::var_stack_t var_stack_t;
  //--------------------------------------------------------------------------

  //==========================================================================
  // get_vstack_args
  //==========================================================================
  bool get_vstack_args(int num_args_, unsigned num_expected_args_, var_stack_t &vstack_, var_t *args_, unsigned *arg_types_)
  {
    if(num_args_==int(num_expected_args_))
    {
      // check if any of the args is invalid
      usize_t sarg_idx=vstack_.size()-num_expected_args_;
      const var_t *svs=vstack_.data()+sarg_idx;
      for(unsigned i=0; i<num_expected_args_; ++i)
        if(!svs[i].num_data_elems)
          goto invalid_arg;

      // get requested number of arguments
      vstack_.get(sarg_idx, args_, num_expected_args_);
      vstack_.remove_back(num_args_);
      for(unsigned i=0; i<num_expected_args_; ++i)
        arg_types_[i]=args_[i].value.type_index();
      return true;
    }

    // replace args with invalid arg
    invalid_arg:
    vstack_.remove_back(num_args_);
    vstack_.push_back();
    return false;
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // eval_1arg_expr
  //==========================================================================
  template<typename TR, typename T, typename Expr>
  void eval_1arg_expr_impl(var_t &res_, const var_t &sv_, const Expr &expr_)
  {
    // access data and setup result type 
    T *v=type_ref<T*>(sv_.value)+sv_.data_offset;
    TR *res=(TR*)res_.data.data, *res_end=res+res_.num_vals*res_.num_data_elems;
    res_.value=res;

    // execute expression for the data array
    while(res<res_end)
    {
      for(uint8_t ei=0; ei<res_.num_data_elems; ++ei)
        *res++=expr_(v[sv_.data_stride?ei:0]);
      v+=sv_.data_stride;
    }
  }
  //----

  template<typename Expr>
  void eval_1arg_expr(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top value from the variable stack
    var_t sv;
    unsigned sv_tidx;
    if(!get_vstack_args(num_args_, 1, vstack_, &sv, &sv_tidx))
      return;

    // prepare the result
    var_t &res=vstack_.push_back();
    res.data=PFC_MEM_ALLOC(sv.num_vals*sv.num_data_elems*sizeof(float32_t));
    res.init(sv.num_data_elems, sv.num_vals);

    // evaluate the expression
    switch(sv_tidx)
    {
      case vbuf_expression_value::value_t::find_type<float32_t*>::res:
        eval_1arg_expr_impl<float32_t, float32_t>(res, sv, expr_); break;
      case vbuf_expression_value::value_t::find_type<int32_t*>::res:
        eval_1arg_expr_impl<int32_t, int32_t>(res, sv, expr_); break;
    }
  }
  //----

  template<typename T, typename Expr>
  void eval_1arg_expr_fixed(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top value from the variable stack
    var_t sv;
    unsigned sv_tidx;
    if(!get_vstack_args(num_args_, 1, vstack_, &sv, &sv_tidx))
      return;

    // check for proper argument
    var_t &res=vstack_.push_back();
    if(sv_tidx!=vbuf_expression_value::value_t::find_type<T*>::res)
      return;

    // prepare the result and evaluate the expression
    res.data=PFC_MEM_ALLOC(sv.num_vals*sv.num_data_elems*sizeof(T));
    res.init(sv.num_data_elems, sv.num_vals);
    eval_1arg_expr_impl<T, T>(res, sv, expr_);
  }
  //----

  template<typename Expr>
  void eval_1arg_cmp_expr(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top value from the variable stack
    var_t sv;
    unsigned sv_tidx;
    if(!get_vstack_args(num_args_, 1, vstack_, &sv, &sv_tidx))
      return;

    // prepare the result
    var_t &res=vstack_.push_back();
    res.data=PFC_MEM_ALLOC(sv.num_vals*sv.num_data_elems*sizeof(float32_t));
    res.init(sv.num_data_elems, sv.num_vals);

    // evaluate the expression
    switch(sv_tidx)
    {
      case vbuf_expression_value::value_t::find_type<float32_t*>::res:
        eval_1arg_expr_impl<int32_t, float32_t>(res, sv, expr_); break;
      case vbuf_expression_value::value_t::find_type<int32_t*>::res:
        eval_1arg_expr_impl<int32_t, int32_t>(res, sv, expr_); break;
    }
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // eval_2arg_expr
  //==========================================================================
  template<typename TR, typename TP, typename T0, typename T1, typename Expr>
  void eval_2arg_expr_impl(var_t &res_, const var_t &v0_, const var_t &v1_, const Expr &expr_)
  {
    // access data and setup result type 
    T0 *v0=type_ref<T0*>(v0_.value)+v0_.data_offset;
    T1 *v1=type_ref<T1*>(v1_.value)+v1_.data_offset;
    TR *res=(TR*)res_.data.data, *res_end=res+res_.num_vals*res_.num_data_elems;
    res_.value=res;

    // execute expression for the data array
    while(res<res_end)
    {
      for(uint8_t ei=0; ei<res_.num_data_elems; ++ei)
        *res++=expr_((TP)v0[v0_.data_stride?ei:0], (TP)(v1[v1_.data_stride?ei:0]));
      v0+=v0_.data_stride;
      v1+=v1_.data_stride;
    }
  }
  //----

  template<typename Expr>
  void eval_2arg_expr(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top two values from the variable stack
    var_t sv[2];
    unsigned sv_tidx[2];
    if(!get_vstack_args(num_args_, 2, vstack_, sv, sv_tidx))
      return;

    // check for proper arguments
    var_t &res=vstack_.push_back();
    if(sv[0].num_data_elems!=1 && sv[1].num_data_elems!=1 && sv[0].num_data_elems!=sv[1].num_data_elems)
      return;

    // prepare the result
    uint32_t num_vals=max(sv[0].num_vals, sv[1].num_vals);
    uint8_t num_data_elems=max(sv[0].num_data_elems, sv[1].num_data_elems);
    res.data=PFC_MEM_ALLOC(num_vals*num_data_elems*sizeof(float32_t));
    res.init(num_data_elems, num_vals);

    // evaluate the expression for proper type combination
    typedef void(*expr_func_t)(var_t&, const var_t&, const var_t&, const Expr&);
    static const expr_func_t s_expr_funcs[]=
    {
      &eval_2arg_expr_impl<float32_t, float32_t, float32_t, float32_t, Expr>,
      &eval_2arg_expr_impl<float32_t, float32_t,   int32_t, float32_t, Expr>,
      &eval_2arg_expr_impl<float32_t, float32_t, float32_t,   int32_t, Expr>,
      &eval_2arg_expr_impl<  int32_t,   int32_t,   int32_t,   int32_t, Expr>,
    };
    unsigned sv0_offs=sv_tidx[0]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:1;
    unsigned sv1_offs=sv_tidx[1]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:2;
    expr_func_t efunc=s_expr_funcs[sv0_offs|sv1_offs];
    efunc(res, sv[0], sv[1], expr_);
  }
  //----

  template<typename T, typename Expr>
  void eval_2arg_expr_fixed(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top two values from the variable stack
    var_t sv[2];
    unsigned sv_tidx[2];
    if(!get_vstack_args(num_args_, 2, vstack_, sv, sv_tidx))
      return;

    // check for proper arguments
    var_t &res=vstack_.push_back();
    if(   (sv[0].num_data_elems!=1 && sv[1].num_data_elems!=1 && sv[0].num_data_elems!=sv[1].num_data_elems)
       || sv_tidx[0]!=vbuf_expression_value::value_t::find_type<T*>::res
       || sv_tidx[1]!=vbuf_expression_value::value_t::find_type<T*>::res)
      return;

    // prepare the result and evaluate the expression
    uint32_t num_vals=max(sv[0].num_vals, sv[1].num_vals);
    uint8_t num_data_elems=max(sv[0].num_data_elems, sv[1].num_data_elems);
    res.data=PFC_MEM_ALLOC(num_vals*num_data_elems*sizeof(T));
    res.init(num_data_elems, num_vals);
    eval_2arg_expr_impl<T, T, T, T>(res, sv[0], sv[1], expr_); 
  }
  //----

  template<typename Expr>
  void eval_2arg_cmp_expr(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top two values from the variable stack
    var_t sv[2];
    unsigned sv_tidx[2];
    if(!get_vstack_args(num_args_, 2, vstack_, sv, sv_tidx))
      return;

    // check for proper arguments
    var_t &res=vstack_.push_back();
    if(sv[0].num_data_elems!=1 && sv[1].num_data_elems!=1 && sv[0].num_data_elems!=sv[1].num_data_elems)
      return;

    // prepare the result
    uint32_t num_vals=max(sv[0].num_vals, sv[1].num_vals);
    uint8_t num_data_elems=max(sv[0].num_data_elems, sv[1].num_data_elems);
    res.data=PFC_MEM_ALLOC(num_vals*num_data_elems*sizeof(int32_t));
    res.init(num_data_elems, num_vals);

    // evaluate the expression for proper type combination
    typedef void(*expr_func_t)(var_t&, const var_t&, const var_t&, const Expr&);
    static const expr_func_t s_expr_funcs[]=
    {
      &eval_2arg_expr_impl<int32_t, float32_t, float32_t, float32_t, Expr>,
      &eval_2arg_expr_impl<int32_t, float32_t,   int32_t, float32_t, Expr>,
      &eval_2arg_expr_impl<int32_t, float32_t, float32_t,   int32_t, Expr>,
      &eval_2arg_expr_impl<int32_t,   int32_t,   int32_t,   int32_t, Expr>,
    };
    unsigned sv0_offs=sv_tidx[0]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:1;
    unsigned sv1_offs=sv_tidx[1]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:2;
    expr_func_t efunc=s_expr_funcs[sv0_offs|sv1_offs];
    efunc(res, sv[0], sv[1], expr_);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // eval_3arg_expr
  //==========================================================================
  template<typename TR, typename T0, typename T1, typename T2, typename Expr>
  void eval_3arg_expr_impl(var_t &res_, const var_t &v0_, const var_t &v1_, const var_t &v2_, const Expr &expr_)
  {
    // access data and setup result type
    T0 *v0=type_ref<T0*>(v0_.value)+v0_.data_offset;
    T1 *v1=type_ref<T1*>(v1_.value)+v1_.data_offset;
    T2 *v2=type_ref<T2*>(v2_.value)+v2_.data_offset;
    TR *res=(TR*)res_.data.data, *res_end=res+res_.num_vals*res_.num_data_elems;
    res_.value=res;

    // execute expression for the data array
    while(res<res_end)
    {
      for(uint8_t ei=0; ei<res_.num_data_elems; ++ei)
        *res++=expr_((TR)v0[v0_.data_stride?ei:0], (TR)v1[v1_.data_stride?ei:0], (TR)v2[v2_.data_stride?ei:0]);
      v0+=v0_.data_stride;
      v1+=v1_.data_stride;
      v2+=v2_.data_stride;
    }
  }
  //----

  template<typename Expr>
  void eval_3arg_expr(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top three values from the variable stack
    var_t sv[3];
    unsigned sv_tidx[3];
    if(!get_vstack_args(num_args_, 3, vstack_, sv, sv_tidx))
      return;

    // check for proper arguments
    var_t &res=vstack_.push_back();
    if(   (sv[0].num_data_elems!=1 && sv[1].num_data_elems!=1 && sv[0].num_data_elems!=sv[1].num_data_elems)
       || (sv[0].num_data_elems!=1 && sv[2].num_data_elems!=1 && sv[0].num_data_elems!=sv[2].num_data_elems)
       || (sv[1].num_data_elems!=1 && sv[2].num_data_elems!=1 && sv[1].num_data_elems!=sv[2].num_data_elems))
      return;

    // prepare the result
    uint32_t num_vals=max(sv[0].num_vals, sv[1].num_vals, sv[2].num_vals);
    uint8_t num_data_elems=max(sv[0].num_data_elems, sv[1].num_data_elems, sv[2].num_data_elems);
    res.data=PFC_MEM_ALLOC(num_vals*num_data_elems*sizeof(float32_t));
    res.init(num_data_elems, num_vals);

    // evaluate the expression for proper type combination
    typedef void(*expr_func_t)(var_t&, const var_t&, const var_t&, const var_t&, const Expr&);
    static const expr_func_t s_expr_funcs[]=
    {
      &eval_3arg_expr_impl<float32_t, float32_t, float32_t, float32_t, Expr>,
      &eval_3arg_expr_impl<float32_t,   int32_t, float32_t, float32_t, Expr>,
      &eval_3arg_expr_impl<float32_t, float32_t,   int32_t, float32_t, Expr>,
      &eval_3arg_expr_impl<float32_t,   int32_t,   int32_t, float32_t, Expr>,
      &eval_3arg_expr_impl<float32_t, float32_t, float32_t,   int32_t, Expr>,
      &eval_3arg_expr_impl<float32_t,   int32_t, float32_t,   int32_t, Expr>,
      &eval_3arg_expr_impl<float32_t, float32_t,   int32_t,   int32_t, Expr>,
      &eval_3arg_expr_impl<  int32_t,   int32_t,   int32_t,   int32_t, Expr>,
    };
    unsigned sv0_offs=sv_tidx[0]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:1;
    unsigned sv1_offs=sv_tidx[1]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:2;
    unsigned sv2_offs=sv_tidx[2]==vbuf_expression_value::value_t::find_type<float32_t*>::res?0:4;
    expr_func_t efunc=s_expr_funcs[sv0_offs|sv1_offs|sv2_offs];
    efunc(res, sv[0], sv[1], sv[2], expr_);
  }
  //----

  template<typename T, typename Expr>
  void eval_3arg_expr_fixed(int num_args_, var_stack_t &vstack_, const Expr &expr_)
  {
    // get the top three values from the variable stack
    var_t sv[3];
    unsigned sv_tidx[3];
    if(!get_vstack_args(num_args_, 3, vstack_, sv, sv_tidx))
      return;

    // check for proper arguments
    var_t &res=vstack_.push_back();
    if(   (sv[0].num_data_elems!=1 && sv[1].num_data_elems!=1 && sv[0].num_data_elems!=sv[1].num_data_elems)
       || (sv[0].num_data_elems!=1 && sv[2].num_data_elems!=1 && sv[0].num_data_elems!=sv[2].num_data_elems)
       || (sv[1].num_data_elems!=1 && sv[2].num_data_elems!=1 && sv[1].num_data_elems!=sv[2].num_data_elems)
       || sv_tidx[0]!=vbuf_expression_value::value_t::find_type<T*>::res
       || sv_tidx[1]!=vbuf_expression_value::value_t::find_type<T*>::res
       || sv_tidx[2]!=vbuf_expression_value::value_t::find_type<T*>::res)
      return;

    // prepare the result and evaluate the expression
    uint32_t num_vals=max(sv[0].num_vals, sv[1].num_vals, sv[2].num_vals);
    uint8_t num_data_elems=max(sv[0].num_data_elems, sv[1].num_data_elems, sv[2].num_data_elems);
    res.data=PFC_MEM_ALLOC(num_vals*num_data_elems*sizeof(T));
    res.init(num_data_elems,  num_vals);
    eval_3arg_expr_impl<T, T, T, T>(res, sv[0], sv[1], sv[2], expr_); 
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // eval_conv_expr
  //==========================================================================
  template<typename T>
  void eval_conv_expr(int num_args_, var_stack_t &vstack_, bool is_vec_)
  {
    // get vector size
    uint32_t num_data_elems=0, num_vals=0;
    const var_t *svs=vstack_.data()+vstack_.size()-num_args_;
    for(int ai=0; ai<num_args_; ++ai)
    {
      num_data_elems+=svs[ai].num_data_elems;
      num_vals=max(num_vals, svs[ai].num_vals);
    }
    if(!is_vec_)
      num_data_elems=1;
    if(!num_data_elems || num_data_elems>4)
    {
      vstack_.remove_back(num_args_);
      vstack_.push_back();
      return;
    }

    // prepare the result
    var_t res;
    T *res_data=(T*)PFC_MEM_ALLOC(num_vals*num_data_elems*sizeof(T)), *res_data_end=res_data+num_vals*num_data_elems;
    res.data=res_data;
    res.init(res_data, (uint8_t)num_data_elems,  num_vals);

    // vectorize all arguments
    for(int ai=0; ai<(is_vec_?num_args_:1); ++ai)
    {
      const var_t &sv=svs[ai];
      unsigned num_arg_elems=is_vec_?sv.num_data_elems:1;
      for(uint8_t ei=0; ei<num_arg_elems; ++ei)
      {
        // switch to float32_t/int32_t component copy
        T *rdata=res_data;
        switch(sv.value.type_index())
        {
          case vbuf_expression_value::value_t::find_type<float32_t*>::res:
          {
            // copy float32 component to the result component
            float32_t *sdata=type_ref<float32_t*>(sv.value)+sv.data_offset+ei;
            while(rdata<res_data_end)
            {
              *rdata=(T)*sdata;
              rdata+=num_data_elems;
              sdata+=sv.data_stride;
            }
          } break;

          case vbuf_expression_value::value_t::find_type<int32_t*>::res:
          {
            // copy int32_t component to the result component
            int32_t *sdata=type_ref<int32_t*>(sv.value)+sv.data_offset+ei;
            while(rdata<res_data_end)
            {
              *rdata=(T)*sdata;
              rdata+=num_data_elems;
              sdata+=sv.data_stride;
            }
          } break;
        }

        // proceed to the next component
        ++res_data;
      }
    }

    // remove old values and add the result to the stack
    vstack_.remove_back(num_args_);
    vstack_.push_back(res);
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // operators
  //==========================================================================
  void op_dot(int num_args_, var_stack_t &vstack_)
  {
    // get the top two values from the variable stack
    var_t sv1=vstack_.back();
    vstack_.pop_back();
    var_t &sv0=vstack_.back();
    const char *mvar=type_ref<const char*>(sv1.value);

    // check for single component accessor
    if(sv0.num_data_elems && sv1.num_vals==1)
      switch(*mvar)
      {
        // x/r component
        case 'x':
        case 'r':
        {
          sv0.num_data_elems=1;
          return;
        } break;

        // y/g component
        case 'y':
        case 'g':
        {
          if(sv0.data_offset+1<sv0.num_data_elems)
          {
            sv0.data_offset+=1;
            sv0.num_data_elems=1;
            return;
          }
        } break;

        // z/b component
        case 'b':
        case 'z':
        {
          if(sv0.data_offset+2<sv0.num_data_elems)
          {
            sv0.data_offset+=2;
            sv0.num_data_elems=1;
            return;
          }
        } break;

        // w/a component
        case 'a':
        case 'w':
        {
          if(sv0.data_offset+3<sv0.num_data_elems)
          {
            sv0.data_offset+=3;
            sv0.num_data_elems=1;
            return;
          }
        } break;
      }

    // reset the value to 0
    sv0=vbuf_expression_value();
  }
  //----

  void op_ternary(int num_args_, var_stack_t &vstack_)
  {
    // get the top three values from the variable stack
    var_t sv[3];
    unsigned sv_tidx[3];
    if(!get_vstack_args(num_args_, 3, vstack_, sv, sv_tidx))
      return;

    // check for proper variables
    var_t &res=vstack_.push_back();
    if(   sv_tidx[0]!=vbuf_expression_value::value_t::find_type<float32_t*>::res
       && sv_tidx[0]!=vbuf_expression_value::value_t::find_type<int32_t*>::res)
      return;

    // apply ternary operator
    uint32_t v=*(uint32_t*)sv[0].value.data();
    res=v?sv[1]:sv[2];
  }
  //--------------------------------------------------------------------------

  //==========================================================================
  // basic low-level operators
  //==========================================================================
  void op_add(int num_args_, var_stack_t &vstack_) {eval_2arg_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_+v1_;});}
  void op_sub(int num_args_, var_stack_t &vstack_) {eval_2arg_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_-v1_;});}
  void op_mul(int num_args_, var_stack_t &vstack_) {eval_2arg_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_*v1_;});}
  void op_div(int num_args_, var_stack_t &vstack_) {eval_2arg_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v1_?v0_/v1_:0;});}
  void op_mod(int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v0_, int32_t v1_) {return v1_?v0_%v1_:0;});}
  void op_bw_not(int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v_) {return ~v_;});}
  void op_bw_and(int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v0_, int32_t v1_) {return v0_&v1_;});}
  void op_bw_or (int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v0_, int32_t v1_) {return v0_|v1_;});}
  void op_bw_xor(int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v0_, int32_t v1_) {return v0_^v1_;});}
  void op_bw_shl(int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v0_, int32_t v1_) {return v0_<<v1_;});}
  void op_bw_shr(int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<int32_t>(num_args_, vstack_, [](int32_t v0_, int32_t v1_) {return v0_>>v1_;});}
  //--------------------------------------------------------------------------

  //==========================================================================
  // logical and comparison operators
  //==========================================================================
  void op_and(int num_args_, var_stack_t &vstack_) {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_&&v1_?1:0;});}
  void op_or(int num_args_, var_stack_t &vstack_)  {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_||v1_?1:0;});}
  void op_not(int num_args_, var_stack_t &vstack_) {eval_1arg_cmp_expr(num_args_, vstack_, [](auto v_) {return !v_?1:0;});}
  void op_eq(int num_args_, var_stack_t &vstack_)  {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_==v1_?1:0;});}
  void op_neq(int num_args_, var_stack_t &vstack_) {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_!=v1_?1:0;});}
  void op_lt(int num_args_, var_stack_t &vstack_)  {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_<v1_?1:0;});}
  void op_gt(int num_args_, var_stack_t &vstack_)  {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_>v1_?1:0;});}
  void op_lte(int num_args_, var_stack_t &vstack_) {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_<=v1_?1:0;});}
  void op_gte(int num_args_, var_stack_t &vstack_) {eval_2arg_cmp_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return v0_>=v1_?1:0;});}
  //--------------------------------------------------------------------------

  //==========================================================================
  // data conversion functions
  //==========================================================================
  void func_int  (int num_args_, var_stack_t &vstack_) {eval_conv_expr<int32_t>(num_args_, vstack_, false);}
  void func_float(int num_args_, var_stack_t &vstack_) {eval_conv_expr<float32_t>(num_args_, vstack_, false);}
  void func_veci (int num_args_, var_stack_t &vstack_) {eval_conv_expr<int32_t>(num_args_, vstack_, true);}
  void func_vecf (int num_args_, var_stack_t &vstack_) {eval_conv_expr<float32_t>(num_args_, vstack_, true);}
  //--------------------------------------------------------------------------

  //==========================================================================
  // basic component-wise functions
  //==========================================================================
  void func_min    (int num_args_, var_stack_t &vstack_) {eval_2arg_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return min(v0_, v1_);});}
  void func_max    (int num_args_, var_stack_t &vstack_) {eval_2arg_expr(num_args_, vstack_, [](auto v0_, auto v1_) {return max(v0_, v1_);});}
  void func_sat    (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return sat(v_);});}
  void func_ssat   (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return ssat(v_);});}
  void func_abs    (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return abs(v_);});}
  void func_clamp  (int num_args_, var_stack_t &vstack_) {eval_3arg_expr(num_args_, vstack_, [](auto v_, auto min_, auto max_) {return clamp(v_, min_, max_);});}
  void func_floor  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return floor(v_);});}
  void func_ceil   (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return ceil(v_);});}
  void func_trunc  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return trunc(v_);});}
  void func_round  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return round(v_);});}
  void func_frc    (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return frc(v_);});}
  void func_mod    (int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_, float32_t div_) {return mod(v_, div_);});}
  void func_sgn    (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return sgn(v_);});}
  void func_sgn_zp (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return sgn_zp(v_);});}
  void func_sqr    (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return sqr(v_);});}
  void func_cubic  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr(num_args_, vstack_, [](auto v_) {return cubic(v_);});}
  void func_sqrt   (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return pfc::sqrt(v_);});}
  void func_sqrt_z (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return sqrt_z(v_);});}
  void func_cbrt   (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return cbrt(v_);});}
  void func_rsqrt  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return rsqrt(v_);});}
  void func_rsqrt_z(int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return rsqrt_z(v_);});}
  void func_rcbrt  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return rcbrt(v_);});}
  void func_rcbrt_z(int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return rcbrt_z(v_);});}
  void func_exp    (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return exp(v_);});}
  void func_exp2   (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return exp2(v_);});}
  void func_ln     (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return ln(v_);});}
  void func_log2   (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return log2(v_);});}
  void func_log10  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return log10(v_);});}
  void func_pow    (int num_args_, var_stack_t &vstack_) {eval_2arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t b_, float32_t e_) {return pow(b_, e_);});}
  //--------------------------------------------------------------------------

  //==========================================================================
  // higher level functions
  //==========================================================================
  void func_lerp        (int num_args_, var_stack_t &vstack_) {eval_3arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v0_, float32_t v1_, float32_t t_) {return lerp(v0_, v1_, t_);});}
  void func_smoothstep  (int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return smoothstep(v_);});}
  void func_smootherstep(int num_args_, var_stack_t &vstack_) {eval_1arg_expr_fixed<float32_t>(num_args_, vstack_, [](float32_t v_) {return smootherstep(v_);});}
} // namespace <anonymous>
//----------------------------------------------------------------------------

void init_vbuf_expression_parser_funcs(vbuf_expression_parser_t &parser_)
{
  // add basic low-level operators
  parser_.set_op(exprop_dot, &op_dot);
  parser_.set_op(exprop_ternary, &op_ternary);
  parser_.set_op(exprop_add, &op_add);
  parser_.set_op(exprop_sub, &op_sub);
  parser_.set_op(exprop_mul, &op_mul);
  parser_.set_op(exprop_div, &op_div);
  parser_.set_op(exprop_mod, &op_mod);
  parser_.set_op(exprop_bw_not, &op_bw_not);
  parser_.set_op(exprop_bw_and, &op_bw_and);
  parser_.set_op(exprop_bw_or,  &op_bw_or);
  parser_.set_op(exprop_bw_xor, &op_bw_xor);
  parser_.set_op(exprop_bw_shl, &op_bw_shl);
  parser_.set_op(exprop_bw_shr, &op_bw_shr);

  // add logical and comparison operators
  parser_.set_op(exprop_and, &op_and);
  parser_.set_op(exprop_or,  &op_or);
  parser_.set_op(exprop_not, &op_not);
  parser_.set_op(exprop_eq,  &op_eq);
  parser_.set_op(exprop_neq, &op_neq);
  parser_.set_op(exprop_lt,  &op_lt);
  parser_.set_op(exprop_gt,  &op_gt);
  parser_.set_op(exprop_lte, &op_lte);
  parser_.set_op(exprop_gte, &op_gte);

  // add data conversion functions
  parser_.set_func("int",   &func_int);
  parser_.set_func("float", &func_float);
  parser_.set_func("veci",  &func_veci);
  parser_.set_func("vecf",  &func_vecf);

  // add basic component-wise functions
  parser_.set_func("min",     &func_min);
  parser_.set_func("max",     &func_max);
  parser_.set_func("sat",     &func_sat);
  parser_.set_func("ssat",    &func_ssat);
  parser_.set_func("abs",     &func_abs);
  parser_.set_func("clamp",   &func_clamp);
  parser_.set_func("floor",   &func_floor);
  parser_.set_func("ceil",    &func_ceil);
  parser_.set_func("trunc",   &func_trunc);
  parser_.set_func("round",   &func_round);
  parser_.set_func("frc",     &func_frc);
  parser_.set_func("mod",     &func_mod);
  parser_.set_func("sgn",     &func_sgn);
  parser_.set_func("sgn_zp",  &func_sgn_zp);
  parser_.set_func("sqr",     &func_sqr);
  parser_.set_func("cubic",   &func_cubic);
  parser_.set_func("sqrt",    &func_sqrt);
  parser_.set_func("sqrt_z",  &func_sqrt_z);
  parser_.set_func("cbrt",    &func_cbrt);
  parser_.set_func("rsqrt",   &func_rsqrt);
  parser_.set_func("rsqrt_z", &func_rsqrt_z);
  parser_.set_func("rcbrt",   &func_rcbrt);
  parser_.set_func("rcbrt_z", &func_rcbrt_z);
  parser_.set_func("exp",     &func_exp);
  parser_.set_func("exp2",    &func_exp2);
  parser_.set_func("ln",      &func_ln);
  parser_.set_func("log2",    &func_log2);
  parser_.set_func("log10",   &func_log10);
  parser_.set_func("pow",     &func_pow);

  // add higher level composite functions
  parser_.set_func("lerp", &func_lerp);
  parser_.set_func("smoothstep", &func_smoothstep);
  parser_.set_func("smootherstep", &func_smootherstep);
}
//----------------------------------------------------------------------------


//============================================================================
// vbuf_expression_value
//============================================================================
vbuf_expression_value::vbuf_expression_value()
{
  init(0, 0);
}
//----

vbuf_expression_value::vbuf_expression_value(const vbuf_expression_value &v_)
  :value(v_.value)
  ,data(0)
  ,num_vals(v_.num_vals)
  ,pinned_owner(0)
  ,num_data_elems(v_.num_data_elems)
  ,data_stride(v_.data_stride)
  ,data_offset(v_.data_offset)
{
  if(!v_.pinned_owner)
    data=v_.data;
}

vbuf_expression_value::vbuf_expression_value(float64_t v_)
{
  data=PFC_MEM_ALLOC(sizeof(float32_t));
  float32_t *v=(float*)data.data;
  *v=float32_t(v_);
  init(v, 1, 1);
}
//----

vbuf_expression_value::vbuf_expression_value(int64_t v_)
{
  data=PFC_MEM_ALLOC(sizeof(int32_t));
  int32_t *v=(int32_t*)data.data;
  *v=int32_t(v_);
  init(v, 1, 1);
}
//----

vbuf_expression_value::vbuf_expression_value(const char *str_, usize_t str_len_)
{
  init(str_, 0, (uint32_t)str_len_);
}
//----

vbuf_expression_value::vbuf_expression_value(const float32_t *data_, uint32_t num_vals_)
{
  init((float32_t*)data_, 1, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const vec2f *data_, uint32_t num_vals_)
{
  init((float32_t*)data_, 2, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const vec3f *data_, uint32_t num_vals_)
{
  init((float32_t*)data_, 3, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const vec4f *data_, uint32_t num_vals_)
{
  init((float32_t*)data_, 4, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const int32_t *data_, uint32_t num_vals_)
{
  init((int32_t*)data_, 1, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const vec2i *data_, uint32_t num_vals_)
{
  init((int32_t*)data_, 2, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const vec3i *data_, uint32_t num_vals_)
{
  init((int32_t*)data_, 3, num_vals_);
}
//----

vbuf_expression_value::vbuf_expression_value(const vec4i *data_, uint32_t num_vals_)
{
  init((int32_t*)data_, 4, num_vals_);
}
//----

vbuf_expression_value::~vbuf_expression_value()
{
}
//----

void vbuf_expression_value::init(uint8_t num_elems_, uint32_t num_vals_)
{
  num_vals=num_vals_;
  pinned_owner=0;
  num_data_elems=num_elems_;
  data_stride=num_vals_>1?num_elems_:0;
  data_offset=0;
}
//----------------------------------------------------------------------------
