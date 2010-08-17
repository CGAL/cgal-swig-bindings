#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I

%import "declare_triangulation_2.i"


//Expose a Delaunay triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_Delaunay_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_triangulation_2_internal(Internal_Triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_2,CGAL::Tag_false)

  %typemap(javaimports)          Delaunay_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Delaunay_triangulation_2_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2>,CGAL_Face_handle<CPPTYPE,Point_2> >;  
%enddef


//Expose a Delaunay_triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_Delaunay_triangulation_2(CLASSNAME,CPPTYPE)
  Declare_Delaunay_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I
