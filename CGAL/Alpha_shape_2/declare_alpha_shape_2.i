#ifndef SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I
#define SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I

%include "../Triangulation_2/declare_Delaunay_triangulation_2.i"
%include "../Triangulation_2/declare_regular_triangulation_2.i"

//Expose a alpha_shape_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the alpha_shape_2
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
// --WTAG is CGAL::Tag_false if the cpp triangulation is not weighted and CGAL::Tag_true otherwise
// --REG_OR_DEL is either regular in the weighted case and Delaunay otherwise
// --BASE_WRAPPER is the triangulation base wrapper class
%define Declare_alpha_shape_2_internal(CLASSNAME,CPPTYPE,POINT_TYPE,WTAG,REG_OR_DEL,BASE_WRAPPER)
  Declare_##REG_OR_DEL##_triangulation_2_internal(Internal_##REG_OR_DEL##_##CLASSNAME,CLASSNAME,CPPTYPE)

  //Alpha shape
  %typemap(javaimports)          Alpha_shape_2_wrapper%{import CGAL.Kernel.POINT_TYPE; import java.util.Iterator; import java.util.Collection;%}
  %template(CLASSNAME)           Alpha_shape_2_wrapper<CPPTYPE,POINT_TYPE,CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,CGAL_Face_handle<CPPTYPE,POINT_TYPE>,WTAG,BASE_WRAPPER <CPPTYPE,CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,CGAL_Face_handle<CPPTYPE,POINT_TYPE> > >;  
  
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
  
//Expose a alpha_shape_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the alpha shape
%define Declare_alpha_shape_2(CLASSNAME,CPPTYPE)
  Declare_alpha_shape_2_internal(CLASSNAME,CPPTYPE,Point_2,CGAL::Tag_false,Delaunay,Delaunay_triangulation_2_wrapper)
%enddef

//Expose a weighted alpha_shape_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the weighted alpha shape 
%define Declare_weighted_alpha_shape_2(CLASSNAME,CPPTYPE)
  Declare_alpha_shape_2_internal(CLASSNAME,CPPTYPE,Weighted_point_2,CGAL::Tag_true,regular,Regular_triangulation_2_wrapper)
%enddef  
  
#endif //SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I
