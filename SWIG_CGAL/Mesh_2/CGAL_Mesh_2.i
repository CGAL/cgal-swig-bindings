// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


%module (package="CGAL") CGAL_Mesh_2

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Mesh_2)
SWIG_CGAL_package_common()

%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"

//include files
%{
  #include  <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Triangulation_2/Object.h>
  #include <SWIG_CGAL/Triangulation_2/all_includes.h>
  #include <SWIG_CGAL/Common/Iterator.h>
  #include <SWIG_CGAL/Mesh_2/all_includes.h>
%}

%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Mesh_2/Delaunay_mesher_2.h"
%include "SWIG_CGAL/Mesh_2/Criteria.h"
%include "SWIG_CGAL/Mesh_2/Triangulation_conformer_2.h"
%import  "SWIG_CGAL/Triangulation_2/CGAL_Triangulation_2.i"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Ref_int; import CGAL.Triangulation_2.Ref_Locate_type_2; import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2; import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2; import CGAL.Kernel.Point_2; import CGAL.Kernel.Segment_2;  import CGAL.Kernel.Triangle_2; import java.util.Iterator; import CGAL.Triangulation_2.Constraint; import java.util.Collection;%}
%pragma(java) moduleimports  =%{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2; import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2; import java.util.Iterator;import CGAL.Kernel.Point_2;%}


//Extending the face type
//  Constrained triangulation for Mesh_2
%extend SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT,Point_2> {
  bool is_in_domain(){
    return $self->get_data()->is_in_domain();
  }

  void set_in_domain(bool b){
    $self->get_data()->set_in_domain(b);
  }
}
//  Constrained triangulation plus for Mesh_2
%extend SWIG_Triangulation_2::CGAL_Face_handle<M2_CDT_plus,Point_2> {
  bool is_in_domain(){
    return $self->get_data()->is_in_domain();
  }

  void set_in_domain(bool b){
    $self->get_data()->set_in_domain(b);
  }
}

// CDT classes for conforming and refinement
SWIG_CGAL_import_Constrained_Delaunay_triangulation_2_SWIG_wrapper
SWIG_CGAL_import_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper
SWIG_CGAL_declare_constrained_Delaunay_triangulation_2(Mesh_2_Constrained_Delaunay_triangulation_2,M2_CDT, Mesh_2)
SWIG_CGAL_declare_constrained_Delaunay_triangulation_plus_2(Mesh_2_Constrained_Delaunay_triangulation_plus_2,M2_CDT_plus, Mesh_2)

//typemap for the Delaunay mes
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
#define  P2_RANGE std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> >
SWIG_CGAL_input_iterator_typemap_in(P2_RANGE,Point_2,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",set_seeds)
//typemap for facet input range
#define M2_CDT_FH SWIG_Triangulation_2::CGAL_Face_handle<Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper::cpp_base,Point_2>
#define M2_CDT_plus_FH SWIG_Triangulation_2::CGAL_Face_handle<Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper::cpp_base,Point_2>
SWIG_CGAL_input_iterator_typemap_in(DM2_Input_iterator_helper<Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper_for_typemap>::range,M2_CDT_FH,Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle,M2_CDT_FH ::cpp_base,SWIGTYPE_p_SWIG_Triangulation_2__CGAL_Face_handleT_M2_CDT_Point_2_t,"(LCGAL/Mesh_2/Mesh_2_Constrained_Delaunay_triangulation_2_Face_handle;)J",set_bad_faces)
SWIG_CGAL_input_iterator_typemap_in(DM2_Input_iterator_helper<Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper_for_typemap>::range,M2_CDT_plus_FH,Mesh_2_Constrained_Delaunay_triangulation_plus_2_Face_handle,M2_CDT_plus_FH ::cpp_base,SWIGTYPE_p_SWIG_Triangulation_2__CGAL_Face_handleT_M2_CDT_plus_Point_2_t,"(LCGAL/Mesh_2/Mesh_2_Constrained_Delaunay_triangulation_plus_2_Face_handle;)J",set_bad_faces)
#else //SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
SWIG_CGAL_declare_identifier_of_template_class(Mesh_2_CDT_Face_handle_input_iterator,Generic_input_iterator<SWIG_Triangulation_2::CGAL_Face_handle<Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper::cpp_base,Point_2> >)
SWIG_CGAL_declare_identifier_of_template_class(Mesh_2_CDT_plus_Face_handle_input_iterator,Generic_input_iterator<SWIG_Triangulation_2::CGAL_Face_handle<Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper::cpp_base,Point_2> >)
#endif//SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE


//Conformer class for CDT_2
%typemap(javaimports)                       Triangulation_conformer_2_wrapper %{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;%}
SWIG_CGAL_declare_identifier_of_template_class(Constrained_Delaunay_triangulation_conformer_2,Triangulation_conformer_2_wrapper<CGAL_CDT2,Constrained_Delaunay_triangulation_2_SWIG_wrapper>)
//Confromer class CDT_2_plus
%typemap(javaimports)                       Triangulation_conformer_2_wrapper %{import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_plus_2;%}
SWIG_CGAL_declare_identifier_of_template_class(Constrained_Delaunay_triangulation_plus_conformer_2,Triangulation_conformer_2_wrapper<CGAL_CDTplus2,Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper>)

//  Delaunay mesher classes for M2_CDT //
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_2,import CGAL.Kernel.Point_2;)
SWIG_CGAL_declare_identifier_of_template_class(Delaunay_mesher_2_Seeds_const_iterator,SWIG_CGAL_Iterator<DM2_M::Seeds_const_iterator,Point_2>)

SWIG_CGAL_declare_identifier_of_template_class(Delaunay_mesh_size_criteria_2,Criteria_wrapper<DM2_C>)
%typemap(javaimports)  Delaunay_mesher_2_wrapper %{import CGAL.Kernel.Point_2; import java.util.Iterator; import CGAL.Triangulation_2.Constraint;%}
SWIG_CGAL_declare_identifier_of_template_class(Default_Delaunay_mesher_2,Delaunay_mesher_2_wrapper<DM2_M,Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper,Criteria_wrapper<DM2_C> >)

SWIG_CGAL_declare_identifier_of_template_class(Mesh_2_Constrained_Delaunay_triangulation_conformer_2,Triangulation_conformer_2_wrapper<M2_CDT,Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper >)
/////////////////////////////////////////

//  Delaunay mesher classes for M2_CDT_plus //
SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,Point_2,import CGAL.Kernel.Point_2;)
SWIG_CGAL_declare_identifier_of_template_class(Delaunay_mesher_plus_2_Seeds_const_iterator,SWIG_CGAL_Iterator<DM2_M_plus::Seeds_const_iterator,Point_2>)

SWIG_CGAL_declare_identifier_of_template_class(Delaunay_mesh_plus_size_criteria_2,Criteria_wrapper<DM2_C_plus>)
%typemap(javaimports)  Delaunay_mesher_2_wrapper %{import CGAL.Kernel.Point_2; import java.util.Iterator; import CGAL.Triangulation_2.Constraint;%}
SWIG_CGAL_declare_identifier_of_template_class(Default_Delaunay_mesher_plus_2,Delaunay_mesher_2_wrapper<DM2_M_plus,Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper,Criteria_wrapper<DM2_C_plus> >)

SWIG_CGAL_declare_identifier_of_template_class(Mesh_2_Constrained_Delaunay_triangulation_conformer_plus_2,Triangulation_conformer_2_wrapper<M2_CDT_plus,Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper >)
//////////////////////////////////////////////

//global functions
%include "SWIG_CGAL/Mesh_2/mesh_2_macros.i"
declare_conforming_global_functions(Constrained_Delaunay_triangulation_2_SWIG_wrapper)
declare_conforming_global_functions(Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper)
declare_conforming_global_functions(Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper)
declare_conforming_global_functions(Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper)
declare_refine_global_functions(Mesh_2_Constrained_Delaunay_triangulation_2_SWIG_wrapper, Criteria_wrapper<DM2_C>)
declare_refine_global_functions(Mesh_2_Constrained_Delaunay_triangulation_plus_2_SWIG_wrapper, Criteria_wrapper<DM2_C_plus>)

#ifdef SWIGJAVA
%include "SWIG_CGAL/Mesh_2/java_extensions.i"
#endif

#ifdef SWIG_CGAL_HAS_Mesh_2_USER_PACKAGE
%include "SWIG_CGAL/User_packages/Mesh_2/extensions.i"
#endif
