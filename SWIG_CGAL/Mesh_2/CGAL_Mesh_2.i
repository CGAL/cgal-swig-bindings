%module CGAL_Mesh_2


%include "SWIG_CGAL/common.i"
%import  "SWIG_CGAL/Common/Macros.h"

//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Triangulation_2/Constrained_Delaunay_triangulation_2.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_iterators.h>  
%}

%include "SWIG_CGAL/Triangulation_2/config.i"
%import "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"

%pragma(java) jniclassimports=%{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;%}
%pragma(java) moduleimports  =%{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;%}


%include "SWIG_CGAL/Mesh_2/config.i"

//Constrained triangulation for Mesh_2
%extend CGAL_Face_handle<M2_CDT,Point_2> {
  bool is_in_domain(){
    return $self->get_data()->is_in_domain();
  }
  
  void set_in_domain(bool b){
    $self->get_data_ref()->set_in_domain(b);
  }
}
Declare_constrained_Delaunay_triangulation_2(Mesh_2_Constrained_Delaunay_triangulation_2,M2_CDT)

//global functions
%{
       #include <CGAL/Triangulation_conformer_2.h>
%}
%define T2_CDT_wrapper Constrained_Delaunay_triangulation_2_wrapper<CGAL_CDT2,CGAL_Vertex_handle<CGAL_CDT2,Point_2>,CGAL_Face_handle<CGAL_CDT2,Point_2> > %enddef
%{
  typedef Constrained_Delaunay_triangulation_2_wrapper<CGAL_CDT2,CGAL_Vertex_handle<CGAL_CDT2,Point_2>,CGAL_Face_handle<CGAL_CDT2,Point_2> > T2_CDT_wrapper;
%}
void make_conforming_Delaunay_2(T2_CDT_wrapper& cdt);
void make_conforming_Gabriel_2(T2_CDT_wrapper& cdt);

%{
  void make_conforming_Delaunay_2(T2_CDT_wrapper& cdt)
  {
    CGAL::make_conforming_Delaunay_2(cdt.get_data_ref());
  }
  void make_conforming_Gabriel_2(T2_CDT_wrapper& cdt){
    CGAL::make_conforming_Gabriel_2(cdt.get_data_ref());
  }
%}