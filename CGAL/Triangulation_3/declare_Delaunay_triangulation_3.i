#ifndef SWIG_CGAL_TRIANGULATION_3_DECLARE_DELAUNAY_TRIANGULATION_3_I
#define SWIG_CGAL_TRIANGULATION_3_DECLARE_DELAUNAY_TRIANGULATION_3_I

%import "declare_triangulation_3.i"


//Expose a Delaunay triangulation_3
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_Delaunay_triangulation_3_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_triangulation_3_internal(Internal_Triangulation_3_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_3,CGAL::Tag_false)
  
  %typemap(javaimports)          Delaunay_triangulation_3_wrapper%{import CGAL.Kernel.Point_3; import CGAL.Kernel.Bounded_side; import java.util.Iterator; import java.util.Collection;%}  
  %template(EXPOSEDNAME)         Delaunay_triangulation_3_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_3>,CGAL_Cell_handle<CPPTYPE,Point_3> >;  
%enddef


//Expose a Delaunay_triangulation_3
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_Delaunay_triangulation_3(CLASSNAME,CPPTYPE)
  Declare_Delaunay_triangulation_3_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_3_DECLARE_DELAUNAY_TRIANGULATION_3_I
