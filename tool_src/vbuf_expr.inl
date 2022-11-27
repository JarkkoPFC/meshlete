//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================


//============================================================================
// vbuf_expression_value
//============================================================================
template<typename T>
void vbuf_expression_value::init(T *data_, uint8_t num_elems_, uint32_t num_vals_)
{
  value=data_;
  num_vals=num_vals_;
  pinned_owner=0;
  num_data_elems=num_elems_;
  data_stride=num_vals_>1?num_elems_:0;
  data_offset=0;
}
//----------------------------------------------------------------------------

template<typename T>
bool vbuf_expression_value::get(T *res_, uint32_t num_vals_, unsigned stride_) const
{
  using namespace pfc;
  if(!num_data_elems)
    return false;
  if(!stride_)
    stride_=sizeof(T);
  num_vals_=data_stride?min(num_vals_, num_vals):num_vals_;
  T *res_end=(T*)(((uint8_t*)res_)+num_vals_*stride_);
  switch(value.type_index())
  {
    case vbuf_expression_value::value_t::find_type<pfc::float32_t*>::res:
    {
      const pfc::float32_t *data=type_ref<pfc::float32_t*>(value)+data_offset;
      while(res_<res_end)
      {
        T v=T(*data);
        mem_copy(res_, &v, sizeof(T));
        (uint8_t*&)res_+=stride_;
        data+=data_stride;
      }
    } break;

    case vbuf_expression_value::value_t::find_type<int32_t*>::res:
    {
      const int32_t *data=type_ref<int32_t*>(value)+data_offset;
      while(res_<res_end)
      {
        T v=T(*data);
        mem_copy(res_, &v, sizeof(T));
        (uint8_t*&)res_+=stride_;
        data+=data_stride;
      }
    } break;
  }
  return true;
}
//----------------------------------------------------------------------------
