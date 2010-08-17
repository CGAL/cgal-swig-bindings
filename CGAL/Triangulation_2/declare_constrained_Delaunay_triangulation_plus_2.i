#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_PLUS_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_PLUS_I

%import "declare_constrained_Delaunay_triangulation_2.i"


//Expose a constrained Delaunay triangulation plus 2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_Delaunay_triangulation_plus_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_constrained_Delaunay_triangulation_2_internal(Internal_Constrained_Delaunay_triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)

  //types
  %include "std_pair.i"
  %template(CLASSNAME_PREFIX##_Constraint) std::pair<CGAL_Vertex_handle <CPPTYPE,Point_2>,CGAL_Vertex_handle<CPPTYPE,Point_2> >;

  //Iterators
  Iterator_for_java(CGAL_Constraint_iterator,CLASSNAME_PREFIX##_Constraint,)
  %template(CLASSNAME_PREFIX##_Constraint_iterator) CGAL_Constraint_iterator<CPPTYPE,std::pair<CGAL_Vertex_handle <CPPTYPE,Point_2>,CGAL_Vertex_handle<CPPTYPE,Point_2> > >;

  Iterator_for_java(CGAL_Subconstraint_iterator,CLASSNAME_PREFIX##_Constraint,)
  %template(CLASSNAME_PREFIX##_Subconstraint_iterator) CGAL_Subconstraint_iterator<CPPTYPE,std::pair<CGAL_Vertex_handle <CPPTYPE,Point_2>,CGAL_Vertex_handle<CPPTYPE,Point_2> > >;

  Iterator_for_java(CGAL_Vertices_in_constraint_iterator,CLASSNAME_PREFIX##_Vertex_handle,import CGAL.Kernel.Point_2;)
  %template(CLASSNAME_PREFIX##_Vertices_in_constraint_iterator) CGAL_Vertices_in_constraint_iterator<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2> >;

  Iterator_for_java(CGAL_Context_iterator,CLASSNAME_PREFIX##_Context,)
  %template(CLASSNAME_PREFIX##_Context_iterator) CGAL_Context_iterator<CPPTYPE,CDTP_context<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2> > >;

  //Triangulation
  %typemap(javaimports)          Constrained_triangulation_plus_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Constrained_triangulation_plus_2_wrapper< Constrained_Delaunay_triangulation_2_wrapper< CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2>,CGAL_Face_handle<CPPTYPE,Point_2> >,CGAL_Vertex_handle<CPPTYPE,Point_2> >;
  %template (CLASSNAME_PREFIX##_Context) CDTP_context<CPPTYPE, CGAL_Vertex_handle<CPPTYPE,Point_2> >;
  
%enddef


//Expose a constrained Delaunay triangulation plus 2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_Delaunay_triangulation_plus_2(CLASSNAME,CPPTYPE)
  Declare_constrained_Delaunay_triangulation_plus_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_PLUS_I
