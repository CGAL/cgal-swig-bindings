#ifndef SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I
#define SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I

%include "../Triangulation_2/declare_Delaunay_triangulation_2.i"

//Expose a alpha_shape
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
// --WTAG is CGAL::Tag_false if the cpp triangulation is not weighted and CGAL::Tag_true otherwise
%define Declare_alpha_shape_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,POINT_TYPE,WTAG)
  //Base triangulation
  Declare_Delaunay_triangulation_2_internal(Internal_Delaunay_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)

  //Triangulations
  %typemap(javaimports)          Alpha_shape_2_wrapper%{import CGAL.Kernel.POINT_TYPE; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Alpha_shape_2_wrapper<CPPTYPE,POINT_TYPE,CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,CGAL_Face_handle<CPPTYPE,POINT_TYPE>,WTAG>;

  //Iterators and circulators
%enddef

//Expose a alpha_shape_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
// --WTAG is CGAL::Tag_false if the cpp triangulation is not weighted and CGAL::Tag_true otherwise
%define Declare_alpha_shape_2(CLASSNAME,CPPTYPE,POINT_TYPE,WTAG)
  Declare_alpha_shape_2_internal(CLASSNAME,CLASSNAME,CPPTYPE,POINT_TYPE,WTAG)
  //typemaps for iterators
  Iterator_for_java(CGAL_Alpha_shape_vertices_iterator,CLASSNAME##_Vertex_handle,import CGAL.Kernel.POINT_TYPE;)
  %template(CLASSNAME##_Alpha_shape_vertices_iterator) CGAL_Alpha_shape_vertices_iterator<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,POINT_TYPE> >;
  Iterator_for_java(CGAL_Alpha_shape_edges_iterator,CLASSNAME##_Edge,)
  %template(CLASSNAME##_Alpha_shape_edges_iterator) CGAL_Alpha_shape_edges_iterator<CPPTYPE,std::pair<CGAL_Face_handle<CPPTYPE,POINT_TYPE>,int> >;  
  %typemap(jstype) double "Double"  //next() return type must be Double
  Iterator_for_java(CGAL_Alpha_iterator,Double,)
  %template(CLASSNAME##_Alpha_iterator) CGAL_Alpha_iterator<CPPTYPE,double>;
  %typemap(jstype) double "double"  //restore to default
%enddef

#endif //SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I
