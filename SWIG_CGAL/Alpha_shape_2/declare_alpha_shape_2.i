#ifndef SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I
#define SWIG_CGAL_ALPHA_SHAPE_2_DECLARE_ALPHA_SHAPE_2_I

%include "SWIG_CGAL/Triangulation_2/declare_Delaunay_triangulation_2.i"
%include "SWIG_CGAL/Triangulation_2/declare_regular_triangulation_2.i"

//Expose a alpha_shape_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the alpha_shape_2
// --POINT_TYPE the name of the class wrapping Point or Weighted_point type
// --WTAG is CGAL::Tag_false if the cpp triangulation is not weighted and CGAL::Tag_true otherwise
// --REG_OR_DEL is either regular in the weighted case and Delaunay otherwise
// --BASE_WRAPPER is the triangulation base wrapper class
%define Declare_alpha_shape_2_internal(CLASSNAME,CPPTYPE,POINT_TYPE,WTAG,REG_OR_DEL,BASE_WRAPPER)
  //extending handle classes
  %extend SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE> {
    std::pair<double,double> get_range() const {return $self->get_data()->get_range();}
    void set_range(std::pair<double,double> range) {$self->get_data_ref()->set_range(range);}
  }

  %extend SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,POINT_TYPE> {
    double get_alpha() const {return $self->get_data()->get_alpha();}
    SWIG_CGAL::Triple<double,double,double> get_ranges(int i) const { return $self->get_data()->get_ranges(i); }
    void set_ranges(int i,SWIG_CGAL::Triple<double,double,double> r){$self->get_data_ref()->set_ranges(i,internal::make_conversion(r));}
    void set_alpha (double d) {$self->get_data_ref()->set_alpha(d);}
  }


  Declare_##REG_OR_DEL##_triangulation_2_internal(Internal_##REG_OR_DEL##_##CLASSNAME,CLASSNAME,CPPTYPE)

  //Alpha shape
  %typemap(javaimports)          Alpha_shape_2_wrapper%{import CGAL.Kernel.POINT_TYPE; import java.util.Iterator; import java.util.Collection;%}
  %template(CLASSNAME)           Alpha_shape_2_wrapper<CPPTYPE,POINT_TYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,POINT_TYPE>,WTAG,BASE_WRAPPER <CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE>,SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,POINT_TYPE> > >;  
  
  //typemaps for iterators
  SWIG_CGAL_set_as_java_iterator(CGAL_Alpha_shape_vertices_iterator,CLASSNAME##_Vertex_handle,import CGAL.Kernel.POINT_TYPE;)
  %template(CLASSNAME##_Alpha_shape_vertices_iterator) CGAL_Alpha_shape_vertices_iterator<CPPTYPE,SWIG_Triangulation_2::CGAL_Vertex_handle<CPPTYPE,POINT_TYPE> >;
  SWIG_CGAL_set_as_java_iterator(CGAL_Alpha_shape_edges_iterator,CLASSNAME##_Edge,)
  %template(CLASSNAME##_Alpha_shape_edges_iterator) CGAL_Alpha_shape_edges_iterator<CPPTYPE,std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CPPTYPE,POINT_TYPE>,int> >;  
  %typemap(jstype) double "Double"  //next() return type must be Double
  SWIG_CGAL_set_as_java_iterator(CGAL_Alpha_iterator,Double,)
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
