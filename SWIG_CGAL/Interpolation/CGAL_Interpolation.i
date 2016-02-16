// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


%module (package="CGAL") CGAL_Interpolation

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Interpolation)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"

//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
//needed for triangulation_2 import
  #include <SWIG_CGAL/Triangulation_2/Object.h>
  #include <SWIG_CGAL/Triangulation_2/all_includes.h>
//needed for triangulation_3 import
  #include <SWIG_CGAL/Triangulation_3/all_includes.h>
//include of the package
  #include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
  #include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
  #include <SWIG_CGAL/Common/triple.h>
  #include <SWIG_CGAL/Interpolation/Data_access.h>
  #include <SWIG_CGAL/Interpolation/typedefs.h>
%}


%include "SWIG_CGAL/Common/Input_iterator_wrapper.h"
%import  "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"
%import  "SWIG_CGAL/Triangulation_3/CGAL_Triangulation_3.i"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"

%pragma(java) jniclassimports  =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_3.Delaunay_triangulation_3; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; import CGAL.Kernel.Vector_2; import CGAL.Kernel.Weighted_point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle; import java.util.Iterator; import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge; import CGAL.Triangulation_2.Regular_triangulation_2_Edge; import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;%}
%pragma(java) moduleimports    =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_3.Delaunay_triangulation_3; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; import CGAL.Kernel.Vector_2; import CGAL.Kernel.Weighted_point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle; import java.util.Iterator; import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge; import CGAL.Triangulation_2.Regular_triangulation_2_Edge; import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;%}

%include "std_pair.i"
SWIG_CGAL_declare_identifier_of_template_class(Double_and_bool,std::pair<double,bool>)
%include "SWIG_CGAL/Common/triple.h"
SWIG_CGAL_declare_identifier_of_template_class(Double_bool_bool,SWIG_CGAL::Triple<double,bool,bool>)
%typemap(javaimports)  std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(Point_2_and_double,std::pair<Point_2,double>)
%typemap(javaimports)  std::pair<Weighted_point_2,double> %{import CGAL.Kernel.Weighted_point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(Weighted_point_2_and_double,std::pair<Weighted_point_2,double>)
%typemap(javaimports)  std::pair<Point_3,double> %{import CGAL.Kernel.Point_3;%}
SWIG_CGAL_declare_identifier_of_template_class(Point_3_and_double,std::pair<Point_3,double>)
%include "SWIG_CGAL/Interpolation/Data_access.h"
%typemap(javaimports)  Data_access_wrapper<I_DA_PD,Point_2,double>  %{import CGAL.Kernel.Point_2;%}
SWIG_CGAL_declare_identifier_of_template_class(Data_access_double_2,Data_access_wrapper<I_DA_PD,Point_2,double>)
%typemap(javaimports)  Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>  %{import CGAL.Kernel.Point_2; import CGAL.Kernel.Vector_2;%}
SWIG_CGAL_declare_identifier_of_template_class(Data_access_vector_2,Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>)

%include "SWIG_CGAL/Interpolation/declare_natural_neighbor_coordinates_2.i"
%include "SWIG_CGAL/Interpolation/declare_regular_neighbor_coordinates_2.i"
%include "SWIG_CGAL/Interpolation/declare_surface_neighbors_3.i"
%include "SWIG_CGAL/Interpolation/declare_surface_neighbor_coordinates_3.i"
%include "SWIG_CGAL/Interpolation/declare_interpolation_functions.i"


#ifdef SWIG_CGAL_HAS_Interpolation_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Interpolation/extensions.i"
#endif

