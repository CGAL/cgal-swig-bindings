// Copyright (c) 2018 GeometryFactory (France).
// All rights reserved.
//
// This file if part of CGAL PolygonMesh java wrapper.
// It is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this file.  If not, see <https://www.gnu.org/licenses/>.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// $URL$
// $Id$
// SPDX-License-Identifier: AGPL-3.0+
//

%module CGAL_Polygon_mesh

%include "SWIG_CGAL/common.i"
SWIG_CGAL_add_java_loadLibrary(CGAL_Polygon_mesh)
%import  "SWIG_CGAL/Common/Macros.h"

%pragma(java) jniclassimports=
%{
import CGAL.Polygon_mesh.PolygonMeshBase;
import CGAL.Polygon_mesh.PolygonMeshRange.FaceDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.EdgeDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.FaceDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshRange.HalfedgeDescriptorOutputRange;
import CGAL.Polygon_mesh.IPolygonMeshProperty;
import CGAL.Polygon_mesh.IPolygonMeshMultiComponentProperty;
import CGAL.Polygon_mesh.IPolygonMeshDoubleProperty;
import CGAL.Polygon_mesh.IPolygonMeshIntProperty;
import CGAL.Polygon_mesh.IPolygonMeshByteProperty;
import CGAL.Polygon_mesh.PolygonMeshDoubleProperty;
import CGAL.Polygon_mesh.PolygonMeshIntProperty;
import CGAL.Polygon_mesh.PolygonMeshByteProperty;
import java.nio.IntBuffer;
import java.nio.DoubleBuffer;
%}

//include files
%{
  #include <fstream>

  #include "graph_traits_PolygonMesh.h"
  #include "properties_PolygonMesh.h"
  #include "PolygonMeshJNILink.h"

  #include <SWIG_CGAL/Polygon_mesh/include/PMP.h>
  #include <SWIG_CGAL/Polygon_mesh/include/PSP.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Euler.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Helper.h>
  #include <SWIG_CGAL/Polygon_mesh/include/AFSR.h>
  #include <SWIG_CGAL/Polygon_mesh/include/SMS.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Segmentation.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Jet_fitting_3.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Ridges_3.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Surface_mesh_deformation.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Surface_mesh_shortest_path.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Surface_mesh_skeletonization.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Convex_hull_3.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Surface_reconstruction_3.h>
  #include <SWIG_CGAL/Polygon_mesh/include/Subdivision_method_3.h>
%}

// typemaps for PolygonMesh
%typemap(jni) PolygonMesh& "jobject"  //replace in jni class
%typemap(jtype) PolygonMesh& "PolygonMeshBase"   //replace in java wrapping class
%typemap(jstype) PolygonMesh& "PolygonMeshBase"  //replace in java function args
%typemap(javain) PolygonMesh& "$javainput" //replace in java function call to wrapped function

%typemap(in, noblock=1) PolygonMesh& {
  PolygonMeshJNI pm_base(jenv, $input);
  $1 = static_cast<PolygonMesh*>( &pm_base );
}

%typemap(in, noblock=1) PolygonMesh& pm2{
  PolygonMeshJNI pm_base2(jenv, $input);
  $1 = static_cast<PolygonMesh*>( &pm_base2 );
}

%typemap(in, noblock=1) PolygonMesh& pm_out{
  PolygonMeshJNI pm_base_out(jenv, $input);
  $1 = static_cast<PolygonMesh*>( &pm_base_out );
}

// range of PolygonMesh as input
%typemap(jni) boost::shared_ptr<std::vector<PolygonMesh*> > "jobjectArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<PolygonMesh*> > "PolygonMeshBase[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<PolygonMesh*> > "PolygonMeshBase[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<PolygonMesh*> > "$javainput" //replace in java function call to wrapped function

%typemap(in, noblock=1) boost::shared_ptr<std::vector<PolygonMesh*> > {
  $1 = boost::shared_ptr<std::vector<PolygonMesh*> >(new std::vector<PolygonMesh*>());
  std::vector<PolygonMeshJNI> pm_base_vector;
  const jsize size = jenv->GetArrayLength($input);
  pm_base_vector.reserve((const std::size_t) size);
  $1->reserve((const std::size_t) size);
  for (int i = 0 ; i < size ; ++i){
    pm_base_vector.push_back(PolygonMeshJNI(jenv, jenv->GetObjectArrayElement($input, i)));
    $1->push_back(static_cast<PolygonMesh*>( &(pm_base_vector.back()) ) );
  }
}
//


// typemaps for PointSet
%typemap(jni) PointSet& "jobject"  //replace in jni class
%typemap(jtype) PointSet& "PointSetBase"   //replace in java wrapping class
%typemap(jstype) PointSet& "PointSetBase"  //replace in java function args
%typemap(javain) PointSet& "$javainput" //replace in java function call to wrapped function

%typemap(in, noblock=1) PointSet& {
  PointSetJNI ps_base(jenv, $input);
  $1 = static_cast<PointSet*>( &ps_base );
}

%typemap(in, noblock=1) PointSet& output_ps{
  PointSetJNI output_ps_base(jenv, $input);
  $1 = static_cast<PointSet*>( &output_ps_base );
}

%typemap(in, noblock=1) PointSet& input_ps{
  PointSetJNI input_ps_base(jenv, $input);
  $1 = static_cast<PointSet*>( &input_ps_base );
}

%typemap(in, noblock=1) PointSet& ps1{
  PointSetJNI ps1_base(jenv, $input);
  $1 = static_cast<PointSet*>( &ps1_base );
}

%typemap(in, noblock=1) PointSet& ps2{
  PointSetJNI ps2_base(jenv, $input);
  $1 = static_cast<PointSet*>( &ps2_base );
}

//typemaps for all properties
%typemap(jni) PolygonMeshIntPropertyJNI& "jobject"  //replace in jni class
%typemap(jni) PolygonMeshBoolPropertyJNI& "jobject"  //replace in jni class
%typemap(jni) PolygonMeshDoublePropertyJNI& "jobject"  //replace in jni class

%typemap(javain) PolygonMeshIntPropertyJNI& "$javainput" //replace in java function call to wrapped function
%typemap(javain) PolygonMeshBoolPropertyJNI& "$javainput" //replace in java function call to wrapped function
%typemap(javain) PolygonMeshDoublePropertyJNI& "$javainput" //replace in java function call to wrapped function

%typemap(jtype) PolygonMeshIntPropertyJNI& "IPolygonMeshIntProperty"   //replace in java wrapping class
%typemap(jtype) PolygonMeshDoublePropertyJNI& "IPolygonMeshDoubleProperty"   //replace in java wrapping class
%typemap(jtype) PolygonMeshBoolPropertyJNI& "IPolygonMeshByteProperty"   //replace in java wrapping class

%typemap(jstype) PolygonMeshBoolPropertyJNI& "IPolygonMeshByteProperty"  //replace in java function args
%typemap(jstype) PolygonMeshIntPropertyJNI& "IPolygonMeshIntProperty"  //replace in java function args
%typemap(jstype) PolygonMeshDoublePropertyJNI& "IPolygonMeshDoubleProperty"  //replace in java function args

//typemaps for face properties
%typemap(in, noblock=1) PolygonMeshIntPropertyJNI& face_int_map
{
  PolygonMeshIntPropertyJNI fimap(jenv, $input);
  $1 = &fimap;
  pm_base.registerFaceProperty(&fimap);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& face_double_map
{
  PolygonMeshDoublePropertyJNI fdmap(jenv, $input);
  $1 = &fdmap;
  pm_base.registerFaceProperty(&fdmap);
}

//typemaps for edge properties
%typemap(in, noblock=1) PolygonMeshBoolPropertyJNI& edge_bool_map
{
  PolygonMeshBoolPropertyJNI ebmap(jenv, $input);
  $1 = &ebmap;
  pm_base.registerEdgeProperty(&ebmap);
}

//typemaps for vertex properties
%typemap(in, noblock=1) PolygonMeshIntPropertyJNI& vertex_int_map
{
  PolygonMeshIntPropertyJNI vimap(jenv, $input);
  $1 = &vimap;
  pm_base.registerVertexProperty(&vimap);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map
{
  PolygonMeshDoublePropertyJNI vdmap(jenv, $input);
  $1 = &vdmap;
  pm_base.registerVertexProperty(&vdmap);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map2
{
  PolygonMeshDoublePropertyJNI vdmap2(jenv, $input);
  $1 = &vdmap2;
  pm_base.registerVertexProperty(&vdmap2);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map3
{
  PolygonMeshDoublePropertyJNI vdmap3(jenv, $input);
  $1 = &vdmap3;
  pm_base.registerVertexProperty(&vdmap3);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map4
{
  PolygonMeshDoublePropertyJNI vdmap4(jenv, $input);
  $1 = &vdmap4;
  pm_base.registerVertexProperty(&vdmap4);
}%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map5
{
  PolygonMeshDoublePropertyJNI vdmap5(jenv, $input);
  $1 = &vdmap5;
  pm_base.registerVertexProperty(&vdmap5);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map6
{
  PolygonMeshDoublePropertyJNI vdmap6(jenv, $input);
  $1 = &vdmap6;
  pm_base.registerVertexProperty(&vdmap6);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map7
{
  PolygonMeshDoublePropertyJNI vdmap7(jenv, $input);
  $1 = &vdmap7;
  pm_base.registerVertexProperty(&vdmap7);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& vertex_double_map8
{
  PolygonMeshDoublePropertyJNI vdmap8(jenv, $input);
  $1 = &vdmap8;
  pm_base.registerVertexProperty(&vdmap8);
}
%typemap(in, noblock=1) PolygonMeshBoolPropertyJNI& vertex_bool_map
{
  PolygonMeshBoolPropertyJNI vbmap(jenv, $input);
  $1 = &vbmap;
  pm_base.registerVertexProperty(&vbmap);
}
//typemaps for point properties
%typemap(in, noblock=1) PolygonMeshIntPropertyJNI& point_int_map
{
  PolygonMeshIntPropertyJNI vimap(jenv, $input);
  $1 = &vimap;
  ps_base.registerProperty(&vimap);
}
%typemap(in, noblock=1) PolygonMeshDoublePropertyJNI& point_double_map
{
  PolygonMeshDoublePropertyJNI vimap(jenv, $input);
  $1 = &vimap;
  ps_base.registerProperty(&vimap);
}
%typemap(in, noblock=1) PolygonMeshBoolPropertyJNI& point_bool_map
{
  PolygonMeshBoolPropertyJNI vimap(jenv, $input);
  $1 = &vimap;
  ps_base.registerProperty(&vimap);
}


//typemaps for ranges
%typemap(jni) RangeIndexJNI "jobject"  //replace in jni class
%typemap(javain) RangeIndexJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) RangeIndexJNI face_range "FaceDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI face_range "FaceDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI vertex_range "VertexDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI vertex_range "VertexDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI roi_vertex_range "VertexDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI roi_vertex_range "VertexDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI ctl_vertex_range "VertexDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI ctl_vertex_range "VertexDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI halfedge_range "HalfedgeDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI halfedge_range "HalfedgeDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI edge_range "EdgeDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI edge_range "EdgeDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI constrained_edges "EdgeDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI constrained_edges "EdgeDescriptorRange"  //replace in java function args
%typemap(jtype) RangeIndexJNI constrained_vertices "VertexDescriptorRange"   //replace in java wrapping class
%typemap(jstype) RangeIndexJNI constrained_vertices "VertexDescriptorRange"  //replace in java function args

%typemap(jni) WritableRangeIndexJNI "jobject"  //replace in jni class
%typemap(javain) WritableRangeIndexJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) WritableRangeIndexJNI face_output "FaceDescriptorOutputRange"   //replace in java wrapping class
%typemap(jstype) WritableRangeIndexJNI face_output "FaceDescriptorOutputRange"  //replace in java function args
%typemap(jtype) WritableRangeIndexJNI vertex_output "VertexDescriptorOutputRange"   //replace in java wrapping class
%typemap(jstype) WritableRangeIndexJNI vertex_output "VertexDescriptorOutputRange"  //replace in java function args
%typemap(jtype) WritableRangeIndexJNI halfedge_output "HalfedgeDescriptorOutputRange"   //replace in java wrapping class
%typemap(jstype) WritableRangeIndexJNI halfedge_output "HalfedgeDescriptorOutputRange"  //replace in java function args

%typemap(in) RangeIndexJNI {
  $1 = RangeIndexJNI(jenv, $input);
}
%typemap(in) WritableRangeIndexJNI {
  $1 = WritableRangeIndexJNI(jenv, $input);
}

// typemaps for PolygonMeshPolylineJNI
%typemap(jni) PolygonMeshPolylineJNI "jobject"  //replace in jni class
%typemap(javain) PolygonMeshPolylineJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) PolygonMeshPolylineJNI "PolygonMeshPolyline"   //replace in java wrapping class
%typemap(jstype) PolygonMeshPolylineJNI "PolygonMeshPolyline"  //replace in java function args
%typemap(in) PolygonMeshPolylineJNI {
  $1 = PolygonMeshPolylineJNI(jenv, $input);
}

// typemaps for PolygonMeshMultiPolylineJNI
%typemap(jni) PolygonMeshMultiPolylineJNI "jobject"  //replace in jni class
%typemap(javain) PolygonMeshMultiPolylineJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) PolygonMeshMultiPolylineJNI "PolygonMeshMultiPolyline"   //replace in java wrapping class
%typemap(jstype) PolygonMeshMultiPolylineJNI "PolygonMeshMultiPolyline"  //replace in java function args
%typemap(in) PolygonMeshMultiPolylineJNI {
  $1 = PolygonMeshMultiPolylineJNI(jenv, $input);
}

// typemaps for PolygonMeshSkeletonJNI
%typemap(jni) PolygonMeshSkeletonJNI "jobject"  //replace in jni class
%typemap(javain) PolygonMeshSkeletonJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) PolygonMeshSkeletonJNI "PolygonMeshSkeleton"   //replace in java wrapping class
%typemap(jstype) PolygonMeshSkeletonJNI "PolygonMeshSkeleton"  //replace in java function args
%typemap(in) PolygonMeshSkeletonJNI {
  $1 = PolygonMeshSkeletonJNI(jenv, $input);
}

// typemaps for PolygonMeshRidgesJNI
%typemap(jni) PolygonMeshRidgesJNI "jobject"  //replace in jni class
%typemap(javain) PolygonMeshRidgesJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) PolygonMeshRidgesJNI "PolygonMeshRidges"   //replace in java wrapping class
%typemap(jstype) PolygonMeshRidgesJNI "PolygonMeshRidges"  //replace in java function args
%typemap(in) PolygonMeshRidgesJNI {
  $1 = PolygonMeshRidgesJNI(jenv, $input);
}

// typemaps for PolygonMeshUmbilicsJNI
%typemap(jni) PolygonMeshUmbilicsJNI "jobject"  //replace in jni class
%typemap(javain) PolygonMeshUmbilicsJNI "$javainput" //replace in java function call to wrapped function
%typemap(jtype) PolygonMeshUmbilicsJNI "PolygonMeshUmbilics"   //replace in java wrapping class
%typemap(jstype) PolygonMeshUmbilicsJNI "PolygonMeshUmbilics"  //replace in java function args
%typemap(in) PolygonMeshUmbilicsJNI {
  $1 = PolygonMeshUmbilicsJNI(jenv, $input);
}

%typemap(javaimports) Polygon_mesh_processing
%{
import CGAL.Polygon_mesh.PolygonMeshRange.FaceDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.EdgeDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.FaceDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshRange.HalfedgeDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshMultiPolyline;
import java.nio.IntBuffer;
import java.nio.DoubleBuffer;
%}
%typemap(javaimports) Euler
%{
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorRange;
import CGAL.Polygon_mesh.PolygonMeshRange.EdgeDescriptorRange;
%}

// == typemaps ==
%include  "SWIG_CGAL/Java/typemaps.i"
%include  "SWIG_CGAL/Kernel/typedefs.h"
SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in
SWIG_CGAL_array_of_int_to_vector_of_vector_of_int_typemap_in
SWIG_CGAL_array_of_int_to_vector_of_int_typemap_in
SWIG_CGAL_array_of_double_to_vector_of_double_typemap_in
SWIG_CGAL_vector_of_int_to_array_of_int_typemap_out
SWIG_CGAL_DirectIntBuffer_to_int_array_typemap_in
SWIG_CGAL_DirectDoubleBuffer_with_size_to_int_array_typemap_in
SWIG_CGAL_double_pair_to_array_of_double_typemap_out
SWIG_CGAL_array_of_double_to_vector_of_planes_typemap_in
// ==


%include "CGAL/version.h" // get the definition of CGAL_VERSION_NR
%include "SWIG_CGAL/Polygon_mesh/include/PMP.h"
%include "SWIG_CGAL/Polygon_mesh/include/Helper.h"
%include "SWIG_CGAL/Polygon_mesh/include/Euler.h"

// Advancing front reconstruction
%include "SWIG_CGAL/Polygon_mesh/include/AFSR.h"

// Triangulated surface mesh simplification
%include "SWIG_CGAL/Polygon_mesh/include/SMS.h"

// Triangulated surface mesh segmentation
%include "SWIG_CGAL/Polygon_mesh/include/Segmentation.h"

// Estimation of Local Differential Properties of Point-Sampled Surfaces
%include "SWIG_CGAL/Polygon_mesh/include/Jet_fitting_3.h"

// Triangulated Surface Mesh Deformation
%typemap(javaimports) Surface_mesh_deformation
%{
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorRange;
%}

%include "SWIG_CGAL/Polygon_mesh/include/Surface_mesh_deformation.h"

// Triangulated Surface Mesh Shortest Path
%include "SWIG_CGAL/Polygon_mesh/include/Surface_mesh_shortest_path.h"

// Triangulated Surface Mesh Skeletonization
%typemap(javaimports) Surface_mesh_skeletonization
%{
import CGAL.Polygon_mesh.PolygonMeshSkeleton;
%}
%include "SWIG_CGAL/Polygon_mesh/include/Surface_mesh_skeletonization.h"

// Approximation of Ridges and Umbilics on Triangulated Surface Meshes
%include  "SWIG_CGAL/Polygon_mesh/include/Ridges_3.h"

// Convex hull 3
%include  "SWIG_CGAL/Polygon_mesh/include/Convex_hull_3.h"

// Point Set Processing
%include  "SWIG_CGAL/Polygon_mesh/include/PSP.h"

// Surface reconstruction
%include  "SWIG_CGAL/Polygon_mesh/include/Surface_reconstruction_3.h"

// Surface Subdivision methods
%include  "SWIG_CGAL/Polygon_mesh/include/Subdivision_method_3.h"



