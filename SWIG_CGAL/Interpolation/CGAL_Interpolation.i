%module CGAL_Interpolation

%include "SWIG_CGAL/common.i"
%import  "SWIG_CGAL/Common/Macros.h"

//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Triangulation_2/Delaunay_triangulation_2.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_iterators.h>  
  #include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
  #include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
  #include <CGAL/natural_neighbor_coordinates_2.h>
%}


%include "SWIG_CGAL/Triangulation_2/config.i"
%import  "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"
%import "SWIG_CGAL/Kernel/Point_2.h"

%pragma(java) jniclassimports  =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Kernel.Point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle;%}
%pragma(java) moduleimports    =%{import CGAL.Triangulation_2.Delaunay_triangulation_2; import CGAL.Kernel.Point_2; import java.util.Collection; import CGAL.Triangulation_2.Delaunay_triangulation_2_Face_handle; import CGAL.Triangulation_2.Delaunay_triangulation_2_Vertex_handle;%}

%include "std_pair.i"
%template(Double_and_bool) std::pair<double,bool>;
%typemap(javaimports)  std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
%template(Point_2_and_double) std::pair<Point_2,double>;

//typedefs
%define Point_2_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > >  %enddef
%define DT2_wrapper Delaunay_triangulation_2_wrapper<CGAL_DT2,CGAL_Vertex_handle<CGAL_DT2,Point_2>,CGAL_Face_handle<CGAL_DT2,Point_2> > %enddef
%define Point_2_and_double_wrapper std::pair<Point_2,double> %enddef
%define Point_2_and_double_base std::pair<Point_2::cpp_base,double> %enddef
%define DT2_Edge_wrapper std::pair<CGAL_Face_handle<CGAL_DT2,Point_2>,int>%enddef
%define DT2_Edge_iterator std::pair<Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge>,Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge> > %enddef

%{
  typedef boost::function_output_iterator< Container_writer<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > > Point_2_and_double_output_iterator;
  typedef Delaunay_triangulation_2_wrapper<CGAL_DT2,CGAL_Vertex_handle<CGAL_DT2,Point_2>,CGAL_Face_handle<CGAL_DT2,Point_2> > DT2_wrapper;
  typedef std::pair<Point_2,double> Point_2_and_double_wrapper;
  typedef std::pair<Point_2::cpp_base,double> Point_2_and_double_base;
  typedef std::pair<CGAL_Face_handle<CGAL_DT2,Point_2>,int> DT2_Edge_wrapper;
  typedef std::pair<Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge>,Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge> > DT2_Edge_iterator;
%}


Typemap_for_Output_iterator(Point_2_and_double_output_iterator,Point_2_and_double_wrapper,Point_2_and_double,Point_2_and_double_base,SWIGTYPE_p_std__pairT_Point_2_double_t,"LCGAL/Interpolation/Point_2_and_double;")
Typemap_for_Input_iterator(DT2_Edge_iterator,DT2_Edge_wrapper,Delaunay_triangulation_2_Edge,CGAL_DT2::Edge,SWIGTYPE_p_Point_3,"(LCGAL/Triangulation_2/Delaunay_triangulation_2_Edge;)J",insert_range)

std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,const CGAL_Face_handle<CGAL_DT2,Point_2>& start);
std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out);
//std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,DT2_Edge_iterator its);
std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const CGAL_Vertex_handle<CGAL_DT2,Point_2>& vh,Point_2_and_double_output_iterator out);

%{
  #ifndef SWIG
  namespace internal{
    template <class T1,class T2,class T3>
    std::pair<T2,T3> extract_pair(const CGAL::Triple<T1,T2,T3>& triple){return std::make_pair(triple.second,triple.third);}
  }
  #endif
  
  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,const CGAL_Face_handle<CGAL_DT2,Point_2>& start)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,start.get_data()) );
  }

  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out) );
  }

//  std::pair<double,bool>
//  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,DT2_Edge_iterator its)
//  {
//    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,its.first,its.second) );
//  }
  
  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const CGAL_Vertex_handle<CGAL_DT2,Point_2>& vh,Point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),vh.get_data(),out) );
  }
%}


//=============



