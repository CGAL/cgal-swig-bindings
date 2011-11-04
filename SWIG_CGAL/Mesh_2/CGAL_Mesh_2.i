%module CGAL_Mesh_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("CGAL_Mesh_2");
        System.loadLibrary("CGAL_Java");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library CGAL_Mesh_2 failed to load. \n" + e);
      throw e;
    }
  }
%}


#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/Reference_wrappers.i"

%include "SWIG_CGAL/Mesh_2/config.i"

//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Triangulation_2/Constrained_Delaunay_triangulation_2.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
  #include <SWIG_CGAL/Triangulation_2/triangulation_iterators.h>  
  #include <SWIG_CGAL/Common/Input_iterator.h>
  #include <SWIG_CGAL/Mesh_2/Delaunay_mesher_2.h>
  #include <SWIG_CGAL/Mesh_2/Criteria.h>
  #include <SWIG_CGAL/Mesh_2/Triangulation_conformer_2.h>
%}

%include "SWIG_CGAL/Common/Input_iterator.h"
%include "SWIG_CGAL/Mesh_2/Delaunay_mesher_2.h"
%include "SWIG_CGAL/Mesh_2/Criteria.h"
%include "SWIG_CGAL/Mesh_2/Triangulation_conformer_2.h"


%include "SWIG_CGAL/Triangulation_2/config.i"
%import "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Ref_int; import CGAL.Triangulation_2.Ref_Locate_type; import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Segment_2;  import CGAL.Kernel.Triangle_2; import java.util.Iterator; import CGAL.Triangulation_2.Constraint; import java.util.Collection;%}
%pragma(java) moduleimports  =%{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2; import java.util.Iterator;import CGAL.Kernel.Point_2;%}


//Constrained triangulation for Mesh_2
%extend SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2> {
  bool is_in_domain(){
    return $self->get_data()->is_in_domain();
  }
  
  void set_in_domain(bool b){
    $self->get_data_ref()->set_in_domain(b);
  }
}
Declare_constrained_Delaunay_triangulation_2(Mesh_2_Constrained_Delaunay_triangulation_2,M2_CDT)


%define T2_CDT_wrapper Constrained_Delaunay_triangulation_2_wrapper<CGAL_CDT2,SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_CDT2,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CGAL_CDT2,Point_2> > %enddef
%define M2_CDT_wrapper Constrained_Delaunay_triangulation_2_wrapper<M2_CDT,SWIG_Triangulation_2::CGAL_Vertex_handle<M2_CDT,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2> > %enddef
%{
  typedef Constrained_Delaunay_triangulation_2_wrapper<CGAL_CDT2,SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_CDT2,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CGAL_CDT2,Point_2> > T2_CDT_wrapper;
  typedef Constrained_Delaunay_triangulation_2_wrapper<M2_CDT,SWIG_Triangulation_2::CGAL_Vertex_handle<M2_CDT,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2> > M2_CDT_wrapper;
%}

//typemap for point input iterator
#define  P2_RANGE std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> > 
SWIG_CGAL_input_iterator_typemap_in(P2_RANGE,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",set_seeds)
//typemap for facet input range
#define M2_CDT_FH SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT_wrapper::cpp_base,Point_2>
SWIG_CGAL_input_iterator_typemap_in(DM2_Input_iterator_helper<M2_CDT_wrapper>::range,M2_CDT_FH,Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle,M2_CDT_FH ::cpp_base,SWIGTYPE_p_SWIG_Triangulation_2__CGAL_Face_handleT_M2_CDT_Point_2_t,"(LCGAL/Mesh_2/Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle;)J",set_bad_faces)

SWIG_CGAL_set_as_java_iterator(CGAL_Seeds_const_iterator,Point_2,import CGAL.Kernel.Point_2;)
%template(Delaunay_mesher_2_Seeds_const_iterator) CGAL_Seeds_const_iterator<DM2_M,Point_2>;



%template(Delaunay_mesh_size_criteria_2) Criteria_wrapper<DM2_C>;
%typemap(javaimports)  Delaunay_mesher_2_wrapper %{import CGAL.Kernel.Point_2; import java.util.Iterator; import CGAL.Triangulation_2.Constraint;%}
%template(Default_Delaunay_mesher_2) Delaunay_mesher_2_wrapper<DM2_M,M2_CDT_wrapper,Criteria_wrapper<DM2_C> >;


%template(Mesh_2_Constrained_Delaunay_triangulation_conformer_2) Triangulation_conformer_2_wrapper<M2_CDT,M2_CDT_wrapper>;
%typemap(javaimports)                       Triangulation_conformer_2_wrapper %{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;%}
%template(Constrained_Delaunay_triangulation_conformer_2) Triangulation_conformer_2_wrapper<CGAL_CDT2,T2_CDT_wrapper>;





//global functions
%include "SWIG_CGAL/Mesh_2/declare_macros.i"
declare_conforming_global_functions(T2_CDT_wrapper)
declare_conforming_global_functions(M2_CDT_wrapper)

declare_refine_global_functions(Criteria_wrapper<DM2_C>)

#ifdef SWIGJAVA
%{
  #include <SWIG_CGAL/Mesh_2/Quality.h>
%}
%include "SWIG_CGAL/Java/Java_caller_code.h"
%include "SWIG_CGAL/Mesh_2/Quality.h"

%template (Quality_pair) Quality_pair_wrapper<DM2_C>;
%template(Mesh_2_predicate) Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness>;
%define T_User_crit_simple Java_criteria_wrapper< Java_Is_bad_wrapper<Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness>,SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C> >,Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness> > %enddef
%{
  #include <SWIG_CGAL/Java/Java_caller_code.h>
  typedef Java_criteria_wrapper< Java_Is_bad_wrapper<Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness>,SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C> >,Java_caller_code_2<SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2>,Quality_pair_wrapper<DM2_C>,Face_badness> > T_User_crit_simple;
%}
%template (User_mesh_criteria_simple_2) T_User_crit_simple;

declare_refine_global_functions(T_User_crit_simple)
#endif

%include "SWIG_CGAL/Mesh_2/user_config.i"

