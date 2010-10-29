#ifndef SWIG_CGAL_TRIANGULATION_3_DECLARE_REGULAR_TRIANGULATION_3_I
#define SWIG_CGAL_TRIANGULATION_3_DECLARE_REGULAR_TRIANGULATION_3_I

%import "SWIG_CGAL/Triangulation_3/declare_triangulation_3.i"


//Expose a Regular triangulation_3
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_regular_triangulation_3_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_triangulation_3_internal(Internal_Triangulation_3_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Weighted_point_3,CGAL::Tag_true)


  %typemap(javaimports)          Regular_triangulation_3_wrapper%{import CGAL.Kernel.Weighted_point_3; import CGAL.Kernel.Bounded_side; import java.util.Iterator; import java.util.Collection;%}  
  %template(EXPOSEDNAME)         Regular_triangulation_3_wrapper<CPPTYPE,SWIG_Triangulation_3::CGAL_Vertex_handle<CPPTYPE,Weighted_point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<CPPTYPE,Weighted_point_3> >;  
%enddef


//Expose a Regular_triangulation_3
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_regular_triangulation_3(CLASSNAME,CPPTYPE)
  Declare_regular_triangulation_3_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_3_DECLARE_REGULAR_TRIANGULATION_3_I
