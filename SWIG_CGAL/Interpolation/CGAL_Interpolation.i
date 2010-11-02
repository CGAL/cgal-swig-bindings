%module CGAL_Interpolation

%include "SWIG_CGAL/common.i"
%import  "SWIG_CGAL/Common/Macros.h"

//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
//needed for triangulation_2 import
  #include <SWIG_CGAL/Triangulation_2/Delaunay_triangulation_2.h>
  #include <SWIG_CGAL/Triangulation_2/Regular_triangulation_2.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_iterators.h>  
//needed for triangulation_3 import
  #include <SWIG_CGAL/Triangulation_3/Delaunay_triangulation_3.h>
  #include <SWIG_CGAL/Triangulation_3/Regular_triangulation_3.h>
  #include <SWIG_CGAL/Triangulation_3/triangulation_handles.h>
  #include <SWIG_CGAL/Common/triple.h>
  #include <SWIG_CGAL/Triangulation_3/triangulation_iterators.h>
//include of the package
  #include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
  #include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
  #include <SWIG_CGAL/Common/triple.h>
  #include <CGAL/natural_neighbor_coordinates_2.h>
  #include <CGAL/regular_neighbor_coordinates_2.h>
  #include <CGAL/surface_neighbors_3.h>
  #include <CGAL/surface_neighbor_coordinates_3.h>
%}


%include "SWIG_CGAL/Triangulation_2/config.i"
%include "SWIG_CGAL/Triangulation_3/config.i"
%import  "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"
%import  "SWIG_CGAL/Triangulation_3/CGAL_Triangulation_3.i"
%import "SWIG_CGAL/Kernel/Point_2.h"
%import "SWIG_CGAL/Kernel/Point_3.h"
%import "SWIG_CGAL/Kernel/Vector_3.h"
%import "SWIG_CGAL/Kernel/Weighted_point_3.h"

%pragma(java) jniclassimports  =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_3.Delaunay_triangulation_3; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; import CGAL.Kernel.Weighted_point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle; import java.util.Iterator; import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge; import CGAL.Triangulation_2.Regular_triangulation_2_Edge; import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;%}
%pragma(java) moduleimports    =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_3.Delaunay_triangulation_3; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; import CGAL.Kernel.Weighted_point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle; import java.util.Iterator; import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge; import CGAL.Triangulation_2.Regular_triangulation_2_Edge; import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;%}

%include "std_pair.i"
%template(Double_and_bool) std::pair<double,bool>;
%include "SWIG_CGAL/Common/triple.h"
%template(Double_bool_bool) CGAL_SWIG::Triple<double,bool,bool>;
%typemap(javaimports)  std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
%template(Point_2_and_double) std::pair<Point_2,double>;
%typemap(javaimports)  std::pair<Weighted_point_2,double> %{import CGAL.Kernel.Weighted_point_2;%}
%template(Weighted_point_2_and_double) std::pair<Weighted_point_2,double>;
%typemap(javaimports)  std::pair<Point_3,double> %{import CGAL.Kernel.Point_3;%}
%template(Point_3_and_double) std::pair<Point_3,double>;

%{
  #ifndef SWIG
  namespace internal{
    template <class T1,class T2,class T3>
    std::pair<T2,T3> extract_pair(const CGAL::Triple<T1,T2,T3>& triple){return std::make_pair(triple.second,triple.third);}
    
    template <class T1,class T2,class T3,class T4>
    CGAL_SWIG::Triple<T2,T3,T4> extract_triple(const CGAL::Quadruple<T1,T2,T3,T4>& quad){return CGAL_SWIG::Triple<T2,T3,T4>(quad.second,quad.third,quad.fourth);}
  }
  #endif
%}

%include "SWIG_CGAL/Interpolation/declare_natural_neighbor_coordinates_2.i"
%include "SWIG_CGAL/Interpolation/declare_regular_neighbor_coordinates_2.i"
%include "SWIG_CGAL/Interpolation/declare_surface_neighbors_3.i"
%include "SWIG_CGAL/Interpolation/declare_surface_neighbor_coordinates_3.i"


//=============



