#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_PLUS_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_PLUS_I

%import "declare_constrained_Delaunay_triangulation_2.i"


//Expose a Constrained_triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_Delaunay_triangulation_plus_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_constrained_Delaunay_triangulation_2_internal(Internal_Constrained_Delaunay_triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)

  %typemap(javaimports)          Constrained_triangulation_plus_2_wrapper%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Segment_2; import CGAL.Kernel.Triangle_2; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Constrained_triangulation_plus_2_wrapper< Constrained_Delaunay_triangulation_2_wrapper< CPPTYPE,CGAL_Vertex_handle<CPPTYPE>,CGAL_Face_handle<CPPTYPE> > >;
%enddef


//Expose a Constrained_triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_constrained_Delaunay_triangulation_plus_2(CLASSNAME,CPPTYPE)
  Declare_constrained_Delaunay_triangulation_plus_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_CONSTRAINED_DELAUNAY_TRIANGULATION_2_PLUS_I
