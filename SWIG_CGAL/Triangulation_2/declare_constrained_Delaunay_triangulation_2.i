#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_constrained_triangulation_2.i"


//Expose a constrained Delaunay triangulation 2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_Delaunay_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_constrained_triangulation_2_internal(Internal_Contrained_triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)

  %typemap(javaimports)          Constrained_Delaunay_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;  import CGAL.Triangulation_2.Constraint;%}
  %template(EXPOSEDNAME)         Constrained_Delaunay_triangulation_2_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2>,CGAL_Face_handle<CPPTYPE,Point_2> >;  
%enddef


//Expose a constrained Delaunay triangulation 2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_Delaunay_triangulation_2(CLASSNAME,CPPTYPE)
  Declare_constrained_Delaunay_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_I
