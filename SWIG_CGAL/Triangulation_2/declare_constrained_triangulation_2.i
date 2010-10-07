#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_triangulation_2.i"


//Expose a constrained triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_triangulation_2_internal(Internal_Triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_2,CGAL::Tag_false)

  //typemaps for Edge_output_iterator
  %define EXPOSEDNAME##_Edge_output_iterator Constrained_triangulation_2_wrapper< CPPTYPE,CGAL_Vertex_handle< CPPTYPE,Point_2 >,CGAL_Face_handle< CPPTYPE,Point_2 > >::Edge_output_iterator %enddef
  %{
  typedef std::pair<CGAL_Face_handle< CPPTYPE,Point_2 >,int> CLASSNAME_PREFIX##_Edge;
  %}
  Typemap_for_Output_iterator(EXPOSEDNAME##_Edge_output_iterator,CLASSNAME_PREFIX##_Edge,CLASSNAME_PREFIX##_Edge,CPPTYPE::Edge,SWIGTYPE_p_std__pairT_CGAL_Face_handleT_##CPPTYPE##_Point_2_t_int_t,"LCGAL/Triangulation_2/" #CLASSNAME_PREFIX "_Edge;")

  %typemap(javaimports)          Constrained_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Constrained_triangulation_2_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2>,CGAL_Face_handle<CPPTYPE,Point_2> >;  
%enddef


//Expose a constrained triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_triangulation_2(CLASSNAME,CPPTYPE)
  Declare_constrained_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_TRIANGULATION_2_I
