%module CGAL_Interpolation

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Interpolation");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Interpolation failed to load. \n" + e);
      throw e;
    }
  }
%}


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
  #include <SWIG_CGAL/Interpolation/Data_access.h>
  #include <CGAL/natural_neighbor_coordinates_2.h>
  #include <CGAL/regular_neighbor_coordinates_2.h>
  #include <CGAL/surface_neighbors_3.h>
  #include <CGAL/surface_neighbor_coordinates_3.h>
  #include <CGAL/interpolation_functions.h>
  #include <CGAL/Interpolation_traits_2.h>
  #include <CGAL/sibson_gradient_fitting.h>
  #include <CGAL/Interpolation_gradient_fitting_traits_2.h>
//typedefs for the package
  #include <map>
  typedef std::map<EPIC_Kernel::Point_2,double,EPIC_Kernel::Less_xy_2> I_MPD;
  typedef CGAL::Data_access<I_MPD> I_DA_PD;
  typedef std::map<EPIC_Kernel::Point_2,EPIC_Kernel::Vector_2,EPIC_Kernel::Less_xy_2> I_MPV2;
  typedef CGAL::Data_access<I_MPV2> I_DA_PV2;
%}


%include "SWIG_CGAL/Triangulation_2/config.i"
%include "SWIG_CGAL/Triangulation_3/config.i"
%import  "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"
%import  "SWIG_CGAL/Triangulation_3/CGAL_Triangulation_3.i"
%import "SWIG_CGAL/Kernel/Point_2.h"
%import "SWIG_CGAL/Kernel/Point_3.h"
%import "SWIG_CGAL/Kernel/Vector_3.h"
%import "SWIG_CGAL/Kernel/Vector_2.h"
%import "SWIG_CGAL/Kernel/Weighted_point_3.h"



%pragma(java) jniclassimports  =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_3.Delaunay_triangulation_3; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; import CGAL.Kernel.Vector_2; import CGAL.Kernel.Weighted_point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle; import java.util.Iterator; import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge; import CGAL.Triangulation_2.Regular_triangulation_2_Edge; import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;%}
%pragma(java) moduleimports    =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Triangulation_3.Delaunay_triangulation_3; import CGAL.Triangulation_2.Regular_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3; import CGAL.Kernel.Vector_3; import CGAL.Kernel.Vector_2; import CGAL.Kernel.Weighted_point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Face_handle; import CGAL.Triangulation_2.Regular_triangulation_2_Vertex_handle; import java.util.Iterator; import CGAL.Triangulation_2.Delaunay_triangulation_2_Edge; import CGAL.Triangulation_2.Regular_triangulation_2_Edge; import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;%}

%include "std_pair.i"
%template(Double_and_bool) std::pair<double,bool>;
%include "SWIG_CGAL/Common/triple.h"
%template(Double_bool_bool) SWIG_CGAL::Triple<double,bool,bool>;
%typemap(javaimports)  std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
%template(Point_2_and_double) std::pair<Point_2,double>;
%typemap(javaimports)  std::pair<Weighted_point_2,double> %{import CGAL.Kernel.Weighted_point_2;%}
%template(Weighted_point_2_and_double) std::pair<Weighted_point_2,double>;
%typemap(javaimports)  std::pair<Point_3,double> %{import CGAL.Kernel.Point_3;%}
%template(Point_3_and_double) std::pair<Point_3,double>;
%include "SWIG_CGAL/Interpolation/Data_access.h"
%typemap(javaimports)  Data_access_wrapper<I_DA_PD,Point_2,double>  %{import CGAL.Kernel.Point_2;%}
%template(Data_access_double_2) Data_access_wrapper<I_DA_PD,Point_2,double>;
%typemap(javaimports)  Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>  %{import CGAL.Kernel.Point_2; import CGAL.Kernel.Vector_2;%}
%template(Data_access_vector_2) Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>;

%{
  #ifndef SWIG
  namespace internal{
    template <class T1,class T2,class T3>
    std::pair<T2,T3> extract_pair(const CGAL::Triple<T1,T2,T3>& triple){return std::make_pair(triple.second,triple.third);}
    
    template <class T1,class T2,class T3,class T4>
    SWIG_CGAL::Triple<T2,T3,T4> extract_triple(const CGAL::Quadruple<T1,T2,T3,T4>& quad){return SWIG_CGAL::Triple<T2,T3,T4>(quad.second,quad.third,quad.fourth);}
  }
  #endif
%}

%include "SWIG_CGAL/Interpolation/declare_natural_neighbor_coordinates_2.i"
%include "SWIG_CGAL/Interpolation/declare_regular_neighbor_coordinates_2.i"
%include "SWIG_CGAL/Interpolation/declare_surface_neighbors_3.i"
%include "SWIG_CGAL/Interpolation/declare_surface_neighbor_coordinates_3.i"
%include "SWIG_CGAL/Interpolation/declare_interpolation_functions.i"


//=============



