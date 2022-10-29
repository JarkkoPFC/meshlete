//============================================================================
// Meshlete - Meshlet-based 3D object converter
//
// Copyright (c) 2022, Jarkko Lempiainen
// All rights reserved.
//============================================================================

#include "export.h"
#include "mlet_gen.h"
#include "core/math/tform3.h"
#include "core/streams.h"
using namespace pfc;
//----------------------------------------------------------------------------


//============================================================================
// export_p3g
//============================================================================
bool pfc::export_p3g(bin_output_stream_base &fout_, const export_cfg_p3g &cfg_, const mesh_geometry &mgeo_, const p3g_mesh_geometry &p3g_geo_)
{
  // access export geometry
  const array<p3g_meshlet> &mlets=p3g_geo_.mlets;
  const array<uint32_t> &mlet_vidx=p3g_geo_.mlet_vidx;
  const array<uint8_t> &mlet_tidx=p3g_geo_.mlet_tidx;

  // calculate offsets and total size
  const usize_t num_vtx=mgeo_.num_vertices;
  const usize_t num_segs=mgeo_.num_segs;
  const usize_t num_mlets=mlets.size();
  const usize_t num_mlet_vidx=mlet_vidx.size();
  const usize_t num_mlet_tidx=mlet_tidx.size();
  const usize_t vbuf_size=mgeo_.vbuf_size;
  const bool use_32bit_vtx_ibuf=num_vtx>=65536;
  const uint32_t vidx_size=use_32bit_vtx_ibuf?4:2;
  static const uint32_t s_header_size=40;
  static const uint32_t s_segment_size=16;
  static const uint32_t s_meshlet_size=8+(cfg_.export_meshlet_bvols?4:0)+(cfg_.export_meshlet_vcones?4:0);
  const uint32_t offs_segs=s_header_size;
  const usize_t offs_mlets=offs_segs+s_segment_size*num_segs;
  const usize_t offs_vibuf=offs_mlets+s_meshlet_size*num_mlets;
  const usize_t offs_tibuf=offs_vibuf+(use_32bit_vtx_ibuf?num_mlet_vidx*4:((num_mlet_vidx+1)&-2)*2);
  usize_t offs_vbuf=offs_tibuf+((num_mlet_tidx+3)&-4);
  const uint32_t vbuf_align_dwords=cfg_.vbuf_align>4?(cfg_.vbuf_align-(offs_vbuf%cfg_.vbuf_align))/4:0;
  offs_vbuf+=vbuf_align_dwords*4;
  const usize_t total_fsize=offs_vbuf+vbuf_size;

  // log size stats
  {
    // log index data size
    float idx_data_size=float(offs_vbuf-offs_vibuf);
    float vidx_data_size=float(offs_tibuf-offs_vibuf);
    float tidx_data_size=float(offs_vbuf-offs_tibuf);
    stack_str8 idx_unit=" bytes", vidx_unit=" bytes", tidx_unit=" bytes";
    bool idx_unit_frc=false, vidx_unit_frc=false, tidx_unit_frc=false;
    if(idx_data_size>=1024.0f) {idx_data_size/=1024.0f; idx_unit="KB"; idx_unit_frc=true;}
    if(idx_data_size>=1024.0f) {idx_data_size/=1024.0f; idx_unit="MB"; idx_unit_frc=true;}
    if(vidx_data_size>=1024.0f) {vidx_data_size/=1024.0f; vidx_unit="KB"; vidx_unit_frc=true;}
    if(vidx_data_size>=1024.0f) {vidx_data_size/=1024.0f; vidx_unit="MB"; vidx_unit_frc=true;}
    if(tidx_data_size>=1024.0f) {tidx_data_size/=1024.0f; tidx_unit="KB"; tidx_unit_frc=true;}
    if(tidx_data_size>=1024.0f) {tidx_data_size/=1024.0f; tidx_unit="MB"; tidx_unit_frc=true;}
    logf(idx_unit_frc?">   Index data: %.1f%s":">   Index data: %.0f%s", idx_data_size, idx_unit.c_str());
    logf(vidx_unit_frc?" (vtx: %.1f%s":" (vtx: %.0f%s", vidx_data_size, vidx_unit.c_str());
    logf(tidx_unit_frc?", tri: %.1f%s)\r\n":", tri: %.0f%s)\r\n", tidx_data_size, tidx_unit.c_str());

    // log vertex data size
    float vbuf_data_size=float(vbuf_size);
    stack_str8 vbuf_unit=" bytes";
    bool vbuf_unit_frc=false;
    if(vbuf_data_size>=1024.0f) {vbuf_data_size/=1024.0f; vbuf_unit="KB"; vbuf_unit_frc=true;}
    if(vbuf_data_size>=1024.0f) {vbuf_data_size/=1024.0f; vbuf_unit="MB"; vbuf_unit_frc=true;}
    logf(vbuf_unit_frc?">   Vertex data: %.1f%s\r\n":">   Vertex data: %.0f%s\r\n", vbuf_data_size, vbuf_unit.c_str());

    // total size
    float total_file_size=float(total_fsize);
    stack_str8 total_unit=" bytes";
    bool total_unit_frc=false;
    if(total_file_size>=1024.0f) {total_file_size/=1024.0f; total_unit="KB"; total_unit_frc=true;}
    if(total_file_size>=1024.0f) {total_file_size/=1024.0f; total_unit="MB"; total_unit_frc=true;}
    logf(total_unit_frc?">   File size: %.1f%s\r\n":">   File size: %.0f%s\r\n", total_file_size, total_unit.c_str());
  }

  // output file header
  fout_.write_bytes("p3dg", 4); /*todo; support big-endian?*/
  fout_<<uint16_t(p3g_file_version);
  uint16_t flags= (use_32bit_vtx_ibuf?p3gflag_32bit_index:0)
                 |(p3g_geo_.is_stripified?p3gflag_tristrips:0)
                 |(cfg_.export_meshlet_bvols?p3gflag_bvols:0)
                 |(cfg_.export_meshlet_vcones?p3gflag_vcones:0);
  fout_<<uint16_t(flags);
  fout_<<uint32_t(total_fsize);
  fout_<<uint16_t(num_mlets);
  fout_<<uint8_t(num_segs);
  fout_<<uint8_t(mgeo_.vfmt_id);
  fout_<<uint32_t(offs_vbuf);
  fout_<<uint32_t(vbuf_size);
  fout_<<mgeo_.bvol.pos<<mgeo_.bvol.rad;
  PFC_ASSERT(fout_.pos()==s_header_size);

  // write mesh segments
  for(usize_t seg_idx=0; seg_idx<num_segs; ++seg_idx)
  {
    usize_t start_pos=fout_.pos();
    const p3g_mesh_segment &p3g_seg=p3g_geo_.segs[seg_idx];
    fout_<<uint32_t(p3g_seg.material_id);
    fout_<<uint16_t(p3g_seg.start_mlet);
    fout_<<uint16_t(p3g_seg.num_mlets);
    fout_<<p3g_seg.qbvol_pos[0]<<p3g_seg.qbvol_pos[1]<<p3g_seg.qbvol_pos[2]<<p3g_seg.qbvol_rad;
    PFC_ASSERT(fout_.pos()-start_pos==s_segment_size);
  }

  // write meshlets
  usize_t offs_mlet_vibuf=offs_vibuf;
  usize_t offs_mlet_tibuf=offs_tibuf;
  for(usize_t mseg_idx=0; mseg_idx<num_segs; ++mseg_idx)
  {
    const p3g_mesh_segment &p3g_seg=p3g_geo_.segs[mseg_idx];
    for(uint32_t mlet_idx=0; mlet_idx<p3g_seg.num_mlets; ++mlet_idx)
    {
      usize_t start_pos=fout_.pos();
      const p3g_meshlet &mlet=mlets[p3g_seg.start_mlet+mlet_idx];
      fout_<<uint32_t((offs_mlet_vibuf&0x00ffffff)|(mlet.num_vtx<<24));
      fout_<<uint32_t((offs_mlet_tibuf&0x00ffffff)|(mlet.num_tris<<24));
      if(cfg_.export_meshlet_bvols)
        fout_<<mlet.qbvol_pos[0]<<mlet.qbvol_pos[1]<<mlet.qbvol_pos[2]<<mlet.qbvol_rad;
      if(cfg_.export_meshlet_vcones)
        fout_<<mlet.qvcone_dir[0]<<mlet.qvcone_dir[1]<<mlet.qvcone_dir[2]<<mlet.qvcone_dot;
      PFC_ASSERT(fout_.pos()-start_pos==s_meshlet_size);
      offs_mlet_vibuf+=mlet.num_vtx*vidx_size;
      offs_mlet_tibuf+=mlet.num_idx;
    }
  }
  PFC_ASSERT(((offs_mlet_tibuf+3)&-4)==offs_vbuf);
  PFC_ASSERT(((offs_mlet_vibuf+3)&-4)==offs_tibuf);

  // write vertex index buffer
  PFC_ASSERT(fout_.pos()==offs_vibuf);
  if(use_32bit_vtx_ibuf)
    fout_.write_bytes(mlet_vidx.data(), mlet_vidx.size()*4);
  else
  {
    // write 16-bit vertex index buffer (align to 32-bit boundary)
    for(uint32_t vidx: mlet_vidx)
      fout_<<uint16_t(vidx);
    if(mlet_vidx.size()&1)
      fout_<<uint16_t(0);
  }
  PFC_ASSERT((fout_.pos()&3)==0);

  // write triangle index buffer (align to 32-bit boundary)
  PFC_ASSERT(fout_.pos()==offs_tibuf);
  fout_.write_bytes(mlet_tidx.data(), num_mlet_tidx);
  for(usize_t i=num_mlet_tidx; (i&3)!=0; ++i)
    fout_<<uint8_t(0);
  PFC_ASSERT((fout_.pos()&3)==0);

  // align and write vertex buffer
  for(usize_t i=0; i<vbuf_align_dwords; ++i)
    fout_<<uint32_t(0);
  PFC_ASSERT(!cfg_.vbuf_align || (fout_.pos()%cfg_.vbuf_align)==0);
  PFC_ASSERT(fout_.pos()==offs_vbuf);
  fout_.write_bytes(mgeo_.vbuf, vbuf_size);
  return true;
}
//----------------------------------------------------------------------------


//============================================================================
// export_dae - Collada (dae) file export
//============================================================================
bool pfc::export_dae(bin_output_stream_base &fout_, const export_cfg_dae &cfg_, const mesh_geometry &mgeo_, const p3g_mesh_geometry &p3g_geo_)
{
  // setup output streams and access export geometry
  text_output_stream tout(fout_);
//  const mesh_vertex_buffer &vbuf=egeo_.vbuf;
  const array<p3g_mesh_segment> &segs=p3g_geo_.segs;
  const array<p3g_meshlet> &mlets=p3g_geo_.mlets;
  const array<uint32_t> &mlet_vidx=p3g_geo_.mlet_vidx;
  const array<uint8_t> &mlet_tidx=p3g_geo_.mlet_tidx;

  // export Collada header
  fout_<<
  R"(<?xml version="1.0" encoding="utf-8"?>)""\r\n"
  R"(<COLLADA xmlns="http://www.collada.org/2005/11/COLLADASchema" version="1.4.1" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">)""\r\n"
  R"(  <asset>)""\r\n"
  R"(    <unit name="meter" meter="1"/>)""\r\n"
  R"(    <up_axis>Z_UP</up_axis>)""\r\n"
  R"(  </asset>)""\r\n"
  R"(  <library_images/>)""\r\n"
  R"(  <library_geometries>)""\r\n";

  // export mesh geometry (vertex positions, meshlet colors and triangles)
  fout_<<
  R"(    <geometry id="Mesh_001-mesh" name="Mesh.001">)""\r\n"
  R"(      <mesh>)""\r\n"
  R"(        <source id="Mesh_001-mesh-positions">)""\r\n"
  R"(          <float_array id="Mesh_001-mesh-positions-array" count=")";
  const vec3f *vtx_pos=mgeo_.vertices;
  uint32_t num_vtx=(uint32_t)mgeo_.num_vertices;
  tout<<num_vtx*3<<"\">";
  for(usize_t i=0; i<num_vtx; ++i)
    tout<<vtx_pos[i].x<<' '<<vtx_pos[i].y<<' '<<vtx_pos[i].z<<' ';
  fout_<<
  R"(</float_array>)""\r\n"
  R"(          <technique_common>)""\r\n"
  R"(            <accessor source="#Mesh_001-mesh-positions-array" count=")";
  tout<<num_vtx;
  fout_<<
  R"(" stride="3">)""\r\n"
  R"(              <param name="X" type="float"/><param name="Y" type="float"/><param name="Z" type="float"/>)""\r\n"
  R"(            </accessor>)""\r\n"
  R"(          </technique_common>)""\r\n"
  R"(        </source>)""\r\n"
  R"(        <source id="Mesh_001-mesh-colors-Col" name="Col">)""\r\n"
  R"(          <float_array id="Mesh_001-mesh-colors-Col-array" count=")";
  uint32_t num_mlets=(uint32_t)mlets.size();
  tout<<num_mlets*4<<"\">";
  rng_simple rng(12345);
  for(usize_t i=0; i<mlets.size(); ++i)
  {
    float r=rng.rand_ureal1();
    float g=rng.rand_ureal1();
    float b=rng.rand_ureal1();
    float s=1.0f/(r+g+b);
    tout<<r*s<<' '<<g*s<<' '<<b*s<<" 1 ";
  }
  fout_<<
  R"(</float_array>)""\r\n"
  R"(          <technique_common>)""\r\n"
  R"(            <accessor source="#Mesh_001-mesh-colors-Col-array" count=")";
  tout<<mlets.size();
  fout_<<
  R"(" stride="4">)""\r\n"
  R"(              <param name="R" type="float"/><param name="G" type="float"/><param name="B" type="float"/><param name="A" type="float"/>)""\r\n"
  R"(            </accessor>)""\r\n"
  R"(          </technique_common>)""\r\n"
  R"(        </source>)""\r\n"
  R"(        <vertices id="Mesh_001-mesh-vertices">)""\r\n"
  R"(          <input semantic="POSITION" source="#Mesh_001-mesh-positions"/>)""\r\n"
  R"(        </vertices>)""\r\n"
  R"(        <triangles count=")";
  tout<<p3g_geo_.num_tris;
  fout_<<
  R"(">)""\r\n"
  R"(          <input semantic="VERTEX" source="#Mesh_001-mesh-vertices" offset="0"/>)""\r\n"
  R"(          <input semantic="COLOR" source="#Mesh_001-mesh-colors-Col" offset="1" set="0"/>)""\r\n"
  R"(          <p>)";

  uint32_t num_total_mlets=0;
  for(usize_t seg_idx=0; seg_idx<segs.size(); ++seg_idx)
  {
    const p3g_mesh_segment &seg=segs[seg_idx];
    uint32_t mlet_start_vidx=seg.start_vidx;
    uint32_t mlet_start_tidx=seg.start_tidx;
    for(usize_t mlet_idx=0; mlet_idx<seg.num_mlets; ++mlet_idx)
    {
      const p3g_meshlet &mlet=mlets[seg.start_mlet+mlet_idx];
      const uint8_t *tidx=mlet_tidx.data()+mlet_start_tidx, *tidx_end=tidx+mlet.num_idx;
      if(p3g_geo_.is_stripified)
      {
        tidx_end-=2;
        uint8_t parity=0;
        while(tidx<tidx_end)
        {
          if(!p3g_meshlet_tristrip_restart || tidx[2]!=p3g_meshlet_tristrip_restart)
          {
            if(tidx[0]!=tidx[1] && tidx[0]!=tidx[2] && tidx[1]!=tidx[2])
            {
              uint8_t tidx0=parity?tidx[0]:tidx[1], tidx1=parity?tidx[1]:tidx[0], tidx2=tidx[2];
              tout<<mlet_vidx[mlet_start_vidx+tidx0]<<' '<<num_total_mlets<<' ';
              tout<<mlet_vidx[mlet_start_vidx+tidx1]<<' '<<num_total_mlets<<' ';
              tout<<mlet_vidx[mlet_start_vidx+tidx2]<<' '<<num_total_mlets<<' ';
            }
            ++tidx;
            parity^=1;
          }
          else
          {
            parity=0;
            tidx+=3;
          }
        }
      }
      else
        while(tidx<tidx_end)
          tout<<mlet_vidx[mlet_start_vidx+*tidx++]<<' '<<num_total_mlets<<' ';
      mlet_start_vidx+=mlet.num_vtx;
      mlet_start_tidx+=mlet.num_idx;
      ++num_total_mlets;
    }
  }
  fout_<<
  R"(</p>)""\r\n"
  R"(        </triangles>)""\r\n"
  R"(      </mesh>)""\r\n"
  R"(    </geometry>)""\r\n";

  // export meshlet bounding sphere mesh geometry
  if(cfg_.export_meshlet_bvols)
    fout_<<
    R"(    <geometry id="Sphere-mesh" name="Sphere">)""\r\n"
    R"(      <mesh>)""\r\n"
    R"(        <source id="Sphere-mesh-positions">)""\r\n"
    R"(          <float_array id="Sphere-mesh-positions-array" count="342">0 0.7071068 0.7071068 0 0.9238795 0.3826834 0 0.9238795 -0.3826835 0 0.3826835 -0.9238795 0.1464465 0.3535534 0.9238795 0.270598 0.6532815 0.7071068 0.3535534 0.8535534 0.3826834 0.3826834 0.9238795 0 0.3535534 0.8535534 -0.3826835 0.270598 0.6532815 -0.7071068 0.1464465 0.3535534 -0.9238795 0.2705979 0.2705981 0.9238795 0.4999999 0.5 0.7071068 0.6532814 0.6532815 0.3826834 0.7071067 0.7071068 0 0.6532814 0.6532815 -0.3826835 0.4999999 0.5 -0.7071068 0.270598 0.2705981 -0.9238795 0.3535532 0.1464467 0.9238795 0.6532813 0.2705981 0.7071068 0.8535532 0.3535534 0.3826834 0.9238794 0.3826834 0 0.8535532 0.3535534 -0.3826835 0.6532813 0.2705981 -0.7071068 0.3535533 0.1464466 -0.9238795 0.3826833 1.30703e-7 0.9238795 0.7071065 0 0.7071068 0.9238793 0 0.3826834 0.9999998 0 0 0.9238793 0 -0.3826835 0.7071065 0 -0.7071068 0.3826833 0 -0.9238795 0.3535532 -0.1464464 0.9238795 0.6532812 -0.2705979 0.7071068 0.8535531 -0.3535533 0.3826834 0.9238792 -0.3826833 0 0.8535531 -0.3535533 -0.3826835 0.6532812 -0.2705979 -0.7071068 0.3535532 -0.1464465 -0.9238795 0.2705979 -0.2705978 0.9238795 0.4999997 -0.4999998 0.7071068 0.6532812 -0.6532813 0.3826834 0.7071064 -0.7071066 0 0.6532812 -0.6532813 -0.3826835 0.4999997 -0.4999998 -0.7071068 0.2705978 -0.2705979 -0.9238795 0.1464465 -0.3535531 0.9238795 0.2705977 -0.6532812 0.7071068 0.3535531 -0.8535531 0.3826834 0.382683 -0.9238792 0 0.3535531 -0.8535531 -0.3826835 0.2705977 -0.6532812 -0.7071068 0.1464464 -0.3535531 -0.9238795 0 -0.3826831 0.9238795 -2.664e-7 -0.7071064 0.7071068 -2.96202e-7 -0.9238792 0.3826834 -3.26005e-7 -0.9999995 0 -2.96202e-7 -0.9238792 -0.3826835 -2.664e-7 -0.7071064 -0.7071068 -1.62092e-7 -0.3826831 -0.9238795 -0.1464466 -0.3535531 0.9238795 -0.2705982 -0.653281 0.7071068 -0.3535536 -0.8535529 0.3826834 -0.3826836 -0.923879 0 -0.3535536 -0.8535529 -0.3826835 -0.2705982 -0.653281 -0.7071068 -0.1464467 -0.353553 -0.9238795 -0.270598 -0.2705977 0.9238795 -0.5 -0.4999994 0.7071068 -0.6532815 -0.6532809 0.3826834 -0.7071068 -0.7071061 0 -0.6532815 -0.6532809 -0.3826835 -0.5 -0.4999994 -0.7071068 -0.2705981 -0.2705976 -0.9238795 -0.3535532 -0.1464463 0.9238795 -0.6532813 -0.2705975 0.7071068 -0.8535532 -0.3535528 0.3826834 -0.9238794 -0.3826828 0 -0.8535532 -0.3535528 -0.3826835 -0.6532813 -0.2705975 -0.7071068 -0.3535533 -0.1464462 -0.9238795 -0.3826832 2.49912e-7 0.9238795 -0.7071065 4.88331e-7 0.7071068 -0.9238792 5.18133e-7 0.3826834 -0.9999997 6.0754e-7 0 -0.9238792 5.18133e-7 -0.3826835 -0.7071065 4.88331e-7 -0.7071068 -0.3826832 3.39319e-7 -0.9238795 -0.3535532 0.1464468 0.9238795 -0.653281 0.2705984 0.7071068 -0.8535529 0.3535538 0.3826834 -0.923879 0.3826839 0 -0.8535529 0.3535538 -0.3826835 -0.653281 0.2705984 -0.7071068 -0.3535531 0.1464468 -0.9238795 -0.2705978 0.2705981 0.9238795 -0.4999995 0.5000001 0.7071068 -0.6532809 0.6532817 0.3826834 -0.7071061 0.707107 0 -0.6532809 0.6532817 -0.3826835 -0.4999995 0.5000001 -0.7071068 -0.2705978 0.2705982 -0.9238795 -0.1464464 0.3535534 0.9238795 -0.2705975 0.6532814 0.7071068 -0.3535528 0.8535533 0.3826834 -0.3826827 0.9238795 0 -0.3535528 0.8535533 -0.3826835 -0.2705975 0.6532814 -0.7071068 -0.1464463 0.3535534 -0.9238795 0 0 1 0 0.3826833 0.9238795 6.57472e-7 0.9999997 0 4.33955e-7 0.7071065 -0.7071068 0 1.50996e-7 -1</float_array>)""\r\n"
    R"(          <technique_common>)""\r\n"
    R"(            <accessor source="#Sphere-mesh-positions-array" count="114" stride="3">)""\r\n"
    R"(              <param name="X" type="float"/><param name="Y" type="float"/><param name="Z" type="float"/>)""\r\n"
    R"(            </accessor>)""\r\n"
    R"(          </technique_common>)""\r\n"
    R"(        </source>)""\r\n"
    R"(        <vertices id="Sphere-mesh-vertices">)""\r\n"
    R"(          <input semantic="POSITION" source="#Sphere-mesh-positions"/>)""\r\n"
    R"(        </vertices>)""\r\n"
    R"(        <triangles count="224">)""\r\n"
    R"(          <input semantic="VERTEX" source="#Sphere-mesh-vertices" offset="0"/>)""\r\n"
    R"(          <p>0 6 1 110 109 4 113 3 10 112 8 9 111 6 7 110 5 0 112 10 3 111 8 2 8 16 9 6 14 7 4 12 5 10 16 17 7 15 8 5 13 6 4 109 11 113 10 17 17 23 24 14 22 15 12 20 13 11 109 18 113 17 24 15 23 16 13 21 14 11 19 12 22 28 29 20 26 27 18 109 25 113 24 31 22 30 23 20 28 21 18 26 19 24 30 31 113 31 38 29 37 30 27 35 28 25 33 26 31 37 38 29 35 36 26 34 27 25 109 32 34 42 35 33 39 40 38 44 45 35 43 36 33 41 34 32 109 39 113 38 45 36 44 37 44 52 45 42 50 43 40 48 41 39 109 46 113 45 52 44 50 51 41 49 42 40 46 47 47 55 48 46 109 53 113 52 59 51 57 58 48 56 49 47 53 54 51 59 52 49 57 50 113 59 66 58 64 65 55 63 56 54 60 61 58 66 59 56 64 57 54 62 55 53 109 60 61 67 68 66 72 73 64 70 71 61 69 62 60 109 67 113 66 73 65 71 72 62 70 63 72 80 73 70 78 71 68 76 69 67 109 74 113 73 80 72 78 79 70 76 77 68 74 75 74 109 81 113 80 87 79 85 86 77 83 84 75 81 82 79 87 80 77 85 78 75 83 76 86 92 93 84 90 91 82 88 89 87 93 94 84 92 85 82 90 83 81 109 88 113 87 94 94 100 101 91 99 92 89 97 90 88 109 95 113 94 101 93 99 100 91 97 98 89 95 96 98 106 99 96 104 97 95 109 102 113 101 108 100 106 107 98 104 105 96 102 103 101 107 108 113 108 3 107 2 112 105 1 111 103 110 0 107 3 108 105 2 106 104 0 1 102 109 110 0 5 6 112 2 8 111 1 6 110 4 5 112 9 10 111 7 8 8 15 16 6 13 14 4 11 12 10 9 16 7 14 15 5 12 13 17 16 23 14 21 22 12 19 20 15 22 23 13 20 21 11 18 19 22 21 28 20 19 26 22 29 30 20 27 28 18 25 26 24 23 30 29 36 37 27 34 35 25 32 33 31 30 37 29 28 35 26 33 34 34 41 42 33 32 39 38 37 44 35 42 43 33 40 41 36 43 44 44 51 52 42 49 50 40 47 48 44 43 50 41 48 49 40 39 46 47 54 55 51 50 57 48 55 56 47 46 53 51 58 59 49 56 57 58 57 64 55 62 63 54 53 60 58 65 66 56 63 64 54 61 62 61 60 67 66 65 72 64 63 70 61 68 69 65 64 71 62 69 70 72 79 80 70 77 78 68 75 76 72 71 78 70 69 76 68 67 74 79 78 85 77 76 83 75 74 81 79 86 87 77 84 85 75 82 83 86 85 92 84 83 90 82 81 88 87 86 93 84 91 92 82 89 90 94 93 100 91 98 99 89 96 97 93 92 99 91 90 97 89 88 95 98 105 106 96 103 104 100 99 106 98 97 104 96 95 102 101 100 107 107 106 2 105 104 1 103 102 110 107 112 3 105 111 2 104 103 0</p>)""\r\n"
    R"(        </triangles>)""\r\n"
    R"(      </mesh>)""\r\n"
    R"(    </geometry>)""\r\n";

  // export visibility cone mesh geometry
  if(cfg_.export_meshlet_vcones)
  {
    // green cone geometry
    fout_<<
    R"(    <geometry id="GreenCone-mesh" name="GreenCone">)""\r\n"
    R"(      <mesh>)""\r\n"
    R"(        <source id="GreenCone-mesh-positions">)""\r\n"
    R"(          <float_array id="GreenCone-mesh-positions-array" count="99">0 -0.9999994 1 0.1950903 -0.9807847 1 0.3826835 -0.9238789 1 0.5555703 -0.831469 1 0.7071068 -0.7071062 1 0.8314697 -0.5555696 1 0.9238795 -0.3826829 1 0.9807853 -0.1950898 1 1 4.74551e-7 1 0.9807853 0.1950907 1 0.9238796 0.3826838 1 0.8314697 0.5555708 1 0.7071068 0.7071074 1 0.5555702 0.8314703 1 0.3826833 0.9238802 1 0.1950901 0.9807859 1 -3.25841e-7 1 1 -0.1950907 0.9807858 1 -0.3826839 0.9238799 1 -0.5555707 0.8314699 1 -0.7071073 0.707107 1 -0.83147 0.5555703 1 -0.9238799 0.3826832 1 0 6.37471e-7 0 -0.9807854 0.19509 1 -1 -4.15551e-7 1 -0.9807851 -0.1950908 1 -0.9238791 -0.3826839 1 -0.8314689 -0.5555707 1 -0.7071059 -0.7071071 1 -0.5555691 -0.8314698 1 -0.3826821 -0.9238795 1 -0.1950888 -0.980785 1</float_array>)""\r\n"
    R"(          <technique_common>)""\r\n"
    R"(            <accessor source="#GreenCone-mesh-positions-array" count="33" stride="3">)""\r\n"
    R"(              <param name="X" type="float"/><param name="Y" type="float"/><param name="Z" type="float"/>)""\r\n"
    R"(            </accessor>)""\r\n"
    R"(          </technique_common>)""\r\n"
    R"(        </source>)""\r\n"
    R"(        <source id="GreenCone-mesh-colors-Col" name="GreenCol">)""\r\n"
    R"(          <float_array id="GreenCone-mesh-colors-GreenCol-array" count="4">0 1 0 1</float_array>)""\r\n"
    R"(          <technique_common>)""\r\n"
    R"(            <accessor source="#GreenCone-mesh-colors-Col-array" count="1" stride="4">)""\r\n"
    R"(              <param name="R" type="float"/><param name="G" type="float"/><param name="B" type="float"/><param name="A" type="float"/>)""\r\n"
    R"(            </accessor>)""\r\n"
    R"(          </technique_common>)""\r\n"
    R"(        </source>)""\r\n"
    R"(        <vertices id="GreenCone-mesh-vertices">)""\r\n"
    R"(          <input semantic="POSITION" source="#GreenCone-mesh-positions"/>)""\r\n"
    R"(        </vertices>)""\r\n"
    R"(        <triangles count="62">)""\r\n"
    R"(          <input semantic="VERTEX" source="#GreenCone-mesh-vertices" offset="0"/>)""\r\n"
    R"(          <input semantic="COLOR" source="#GreenCone-mesh-colors-Col" offset="1" set="0"/>)""\r\n"
    R"(          <p>0 0 23 0 1 0 1 0 23 0 2 0 2 0 23 0 3 0 3 0 23 0 4 0 4 0 23 0 5 0 5 0 23 0 6 0 6 0 23 0 7 0 7 0 23 0 8 0 8 0 23 0 9 0 9 0 23 0 10 0 10 0 23 0 11 0 11 0 23 0 12 0 12 0 23 0 13 0 13 0 23 0 14 0 14 0 23 0 15 0 15 0 23 0 16 0 16 0 23 0 17 0 17 0 23 0 18 0 18 0 23 0 19 0 19 0 23 0 20 0 20 0 23 0 21 0 21 0 23 0 22 0 22 0 23 0 24 0 24 0 23 0 25 0 25 0 23 0 26 0 26 0 23 0 27 0 27 0 23 0 28 0 28 0 23 0 29 0 29 0 23 0 30 0 30 0 23 0 31 0 31 0 23 0 32 0 32 0 23 0 0 0 7 0 15 0 24 0 32 0 0 0 1 0 1 0 2 0 3 0 3 0 4 0 7 0 4 0 5 0 7 0 5 0 6 0 7 0 7 0 8 0 9 0 9 0 10 0 7 0 10 0 11 0 7 0 11 0 12 0 15 0 12 0 13 0 15 0 13 0 14 0 15 0 15 0 16 0 17 0 17 0 18 0 19 0 19 0 20 0 21 0 21 0 22 0 24 0 24 0 25 0 26 0 26 0 27 0 28 0 28 0 29 0 32 0 29 0 30 0 32 0 30 0 31 0 32 0 32 0 1 0 3 0 15 0 17 0 24 0 17 0 19 0 24 0 19 0 21 0 24 0 24 0 26 0 32 0 26 0 28 0 32 0 32 0 3 0 7 0 7 0 11 0 15 0 32 0 7 0 24 0</p>)""\r\n"
    R"(        </triangles>)""\r\n"
    R"(      </mesh>)""\r\n"
    R"(    </geometry>)""\r\n";

    // red cone geometry
    fout_<<
    R"(    <geometry id="RedCone-mesh" name="RedCone">)""\r\n"
    R"(      <mesh>)""\r\n"
    R"(        <source id="RedCone-mesh-positions">)""\r\n"
    R"(          <float_array id="RedCone-mesh-positions-array" count="99">0 -0.9999994 1 0.1950903 -0.9807847 1 0.3826835 -0.9238789 1 0.5555703 -0.831469 1 0.7071068 -0.7071062 1 0.8314697 -0.5555696 1 0.9238795 -0.3826829 1 0.9807853 -0.1950898 1 1 4.74551e-7 1 0.9807853 0.1950907 1 0.9238796 0.3826838 1 0.8314697 0.5555708 1 0.7071068 0.7071074 1 0.5555702 0.8314703 1 0.3826833 0.9238802 1 0.1950901 0.9807859 1 -3.25841e-7 1 1 -0.1950907 0.9807858 1 -0.3826839 0.9238799 1 -0.5555707 0.8314699 1 -0.7071073 0.707107 1 -0.83147 0.5555703 1 -0.9238799 0.3826832 1 0 6.37471e-7 0 -0.9807854 0.19509 1 -1 -4.15551e-7 1 -0.9807851 -0.1950908 1 -0.9238791 -0.3826839 1 -0.8314689 -0.5555707 1 -0.7071059 -0.7071071 1 -0.5555691 -0.8314698 1 -0.3826821 -0.9238795 1 -0.1950888 -0.980785 1</float_array>)""\r\n"
    R"(          <technique_common>)""\r\n"
    R"(            <accessor source="#RedCone-mesh-positions-array" count="33" stride="3">)""\r\n"
    R"(              <param name="X" type="float"/><param name="Y" type="float"/><param name="Z" type="float"/>)""\r\n"
    R"(            </accessor>)""\r\n"
    R"(          </technique_common>)""\r\n"
    R"(        </source>)""\r\n"
    R"(        <source id="RedCone-mesh-colors-Col" name="RedCol">)""\r\n"
    R"(          <float_array id="RedCone-mesh-colors-RedCol-array" count="4">1 0 0 1</float_array>)""\r\n"
    R"(          <technique_common>)""\r\n"
    R"(            <accessor source="#RedCone-mesh-colors-Col-array" count="1" stride="4">)""\r\n"
    R"(              <param name="R" type="float"/><param name="G" type="float"/><param name="B" type="float"/><param name="A" type="float"/>)""\r\n"
    R"(            </accessor>)""\r\n"
    R"(          </technique_common>)""\r\n"
    R"(        </source>)""\r\n"
    R"(        <vertices id="RedCone-mesh-vertices">)""\r\n"
    R"(          <input semantic="POSITION" source="#RedCone-mesh-positions"/>)""\r\n"
    R"(        </vertices>)""\r\n"
    R"(        <triangles count="62">)""\r\n"
    R"(          <input semantic="VERTEX" source="#RedCone-mesh-vertices" offset="0"/>)""\r\n"
    R"(          <input semantic="COLOR" source="#RedCone-mesh-colors-Col" offset="1" set="0"/>)""\r\n"
    R"(          <p>0 0 23 0 1 0 1 0 23 0 2 0 2 0 23 0 3 0 3 0 23 0 4 0 4 0 23 0 5 0 5 0 23 0 6 0 6 0 23 0 7 0 7 0 23 0 8 0 8 0 23 0 9 0 9 0 23 0 10 0 10 0 23 0 11 0 11 0 23 0 12 0 12 0 23 0 13 0 13 0 23 0 14 0 14 0 23 0 15 0 15 0 23 0 16 0 16 0 23 0 17 0 17 0 23 0 18 0 18 0 23 0 19 0 19 0 23 0 20 0 20 0 23 0 21 0 21 0 23 0 22 0 22 0 23 0 24 0 24 0 23 0 25 0 25 0 23 0 26 0 26 0 23 0 27 0 27 0 23 0 28 0 28 0 23 0 29 0 29 0 23 0 30 0 30 0 23 0 31 0 31 0 23 0 32 0 32 0 23 0 0 0 7 0 15 0 24 0 32 0 0 0 1 0 1 0 2 0 3 0 3 0 4 0 7 0 4 0 5 0 7 0 5 0 6 0 7 0 7 0 8 0 9 0 9 0 10 0 7 0 10 0 11 0 7 0 11 0 12 0 15 0 12 0 13 0 15 0 13 0 14 0 15 0 15 0 16 0 17 0 17 0 18 0 19 0 19 0 20 0 21 0 21 0 22 0 24 0 24 0 25 0 26 0 26 0 27 0 28 0 28 0 29 0 32 0 29 0 30 0 32 0 30 0 31 0 32 0 32 0 1 0 3 0 15 0 17 0 24 0 17 0 19 0 24 0 19 0 21 0 24 0 24 0 26 0 32 0 26 0 28 0 32 0 32 0 3 0 7 0 7 0 11 0 15 0 32 0 7 0 24 0</p>)""\r\n"
    R"(        </triangles>)""\r\n"
    R"(      </mesh>)""\r\n"
    R"(    </geometry>)""\r\n";
  }

  // end geometry definition
  fout_<<
  R"(  </library_geometries>)""\r\n";

  // export mesh instance
  fout_<<
  R"(  <library_visual_scenes>)""\r\n"
  R"(    <visual_scene id="Scene" name="Scene">)""\r\n"
  R"(      <node id="Mesh" name="Mesh" type="NODE">)""\r\n"
  R"(        <matrix sid="transform">1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1</matrix>)""\r\n"
  R"(        <instance_geometry url="#Mesh_001-mesh" name="Mesh"/>)""\r\n"
  R"(      </node>)""\r\n";

  // export meshlet bounding sphere and visibility cone instances
  if(cfg_.export_meshlet_bvols || cfg_.export_meshlet_vcones)
  {
    usize_t num_segs=segs.size();
    usize_t num_total_mlets=0;
    for(usize_t seg_idx=0; seg_idx<num_segs; ++seg_idx)
    {
      const p3g_mesh_segment &seg=segs[seg_idx];
      sphere3f seg_bvol=dequantize_segment_bvol(seg.qbvol_pos, seg.qbvol_rad, mgeo_.bvol);
      usize_t num_mlets=seg.num_mlets;
      for(usize_t mlet_idx=0; mlet_idx<num_mlets; ++mlet_idx)
      {
        const p3g_meshlet &mlet=mlets[seg.start_mlet+mlet_idx];
        const sphere3f bvol=dequantize_meshlet_bvol(mlet.qbvol_pos, mlet.qbvol_rad, seg_bvol);
        if(cfg_.export_meshlet_bvols)
        {
          mat44f o2w(bvol.rad,     0.0f,     0.0f, bvol.pos.x,
                        0.0f,  bvol.rad,     0.0f, bvol.pos.y,
                        0.0f,      0.0f, bvol.rad, bvol.pos.z,
                        0.0f,      0.0f,     0.0f,       1.0f);
          stack_str16 mesh_name;
          mesh_name.format("Sphere-%i", num_total_mlets);
          fout_<<R"(      <node id=")"<<mesh_name.c_str()<<R"(" name=")"<<mesh_name.c_str()<<R"(" type="NODE"><matrix sid="transform">)";
          for(unsigned m=0; m<4; ++m)
            for(unsigned n=0; n<4; ++n)
              tout<<o2w[m][n]<<' ';
          fout_<<R"(</matrix><instance_geometry url="#Sphere-mesh" name=")"<<mesh_name.c_str()<<R"("/></node>)"<<"\r\n";
        }
        if(cfg_.export_meshlet_vcones)
        {
          // setup cone transform
          if(mlet.qvcone_dot!=-127)
          {
            vec3f vcone_dir;
            float vcone_dot;
            dequantize_meshlet_vcone(vcone_dir, vcone_dot, mlet.qvcone_dir, mlet.qvcone_dot);
            bool positive_space=vcone_dot>=0.0f;
            vcone_dot=abs(vcone_dot);
            float cone_angle=acos(vcone_dot);
            float xyscale=1.0f, zscale=1.0f;
            if(cone_angle<mathf::pi*0.25f)
              xyscale=tan(cone_angle);
            else
              zscale=cot(cone_angle);
            float scale=0.5f;
            tform3f o2w=tform3f(xyscale*bvol.rad*scale, xyscale*bvol.rad*scale, zscale*bvol.rad*scale)*zrot_u(positive_space?vcone_dir:-vcone_dir);
            o2w.set_translation(bvol.pos+max(zscale, 0.25f)*bvol.rad*vcone_dir);

            stack_str16 mesh_name;
            mesh_name.format("Cone-%i", num_total_mlets);
            fout_<<R"(      <node id=")"<<mesh_name.c_str()<<R"(" name=")"<<mesh_name.c_str()<<R"(" type="NODE"><matrix sid="transform">)";
            mat44f mo2w=o2w.matrix44();
            transpose(mo2w);
            for(unsigned m=0; m<4; ++m)
              for(unsigned n=0; n<4; ++n)
                tout<<mo2w[m][n]<<' ';
            if(positive_space)
              fout_<<R"(</matrix><instance_geometry url="#GreenCone-mesh" name=")"<<mesh_name.c_str()<<R"("/></node>)"<<"\r\n";
            else
              fout_<<R"(</matrix><instance_geometry url="#RedCone-mesh" name=")"<<mesh_name.c_str()<<R"("/></node>)"<<"\r\n";
          }
        }
        ++num_total_mlets;
      }
    }
  }

  // export Collada footer
  fout_<<
  R"(    </visual_scene>)""\r\n"
  R"(  </library_visual_scenes>)""\r\n"
  R"(  <scene>)""\r\n"
  R"(    <instance_visual_scene url="#Scene"/>)""\r\n"
  R"(  </scene>)""\r\n"
  R"(</COLLADA>)""\r\n";
  return true;
}
//----------------------------------------------------------------------------
