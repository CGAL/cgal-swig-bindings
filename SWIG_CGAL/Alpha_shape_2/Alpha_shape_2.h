// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_2_H
#define SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_2_H

#include <SWIG_CGAL/Triangulation_2/Delaunay_triangulation_2.h>
#include <SWIG_CGAL/Triangulation_2/Regular_triangulation_2.h>

enum Classification_type { EXTERIOR, SINGULAR, REGULAR, INTERIOR};
enum Mode { GENERAL, REGULARIZED};

namespace internal{
  template <>
  struct Converter<Classification_type>{
    typedef int result_type;
    static const bool is_reference=false;
    static result_type  convert(Classification_type t){return t;}
  };

  template <>
  struct Converter<Mode>{
    typedef int result_type;
    static const bool is_reference=false;
    static result_type  convert(Mode t){return t;}
  };
  
} //namespace internal

#include <SWIG_CGAL/Common/Iterator.h>

template <class Alpha_shape,class Point, class Vertex_handle, class Face_handle,class Weighted_tag,class Base_wrapper>
class Alpha_shape_2_wrapper : public Base_wrapper
{
  typedef Alpha_shape_2_wrapper<Alpha_shape,Point, Vertex_handle, Face_handle,Weighted_tag,Base_wrapper> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);  
public:
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Weighting_helper<Weighted_tag>::Point_range Point_range;
  #else
  typedef Generic_input_iterator<Point> Point_range;
  #endif

  typedef std::pair<Face_handle,int> Edge;
  typedef SWIG_CGAL_Iterator<typename Alpha_shape::Alpha_iterator,double>                              Alpha_iterator;
  typedef SWIG_CGAL_Iterator<typename Alpha_shape::Alpha_shape_vertices_iterator,Vertex_handle>        Alpha_shape_vertices_iterator;
  typedef SWIG_CGAL_Iterator<typename Alpha_shape::Alpha_shape_edges_iterator,Edge>                    Alpha_shape_edges_iterator;
//Creation
  Alpha_shape_2_wrapper(){}
  Alpha_shape_2_wrapper(double alpha){this->get_data().set_alpha(alpha);}
  Alpha_shape_2_wrapper(Point_range range,double alpha){this->get_data().set_alpha(alpha); this->get_data().make_alpha_shape(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));}
  Alpha_shape_2_wrapper(double alpha,Mode m){this->get_data().set_alpha(alpha);this->get_data().set_mode( CGAL::enum_cast<typename Alpha_shape::Mode>(m) );}    
  Alpha_shape_2_wrapper(Point_range range,double alpha,Mode m){
    this->get_data().set_alpha(alpha);
    this->get_data().set_mode( CGAL::enum_cast<typename Alpha_shape::Mode>(m) );
    this->get_data().make_alpha_shape(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));  
  }
//Operations
  SWIG_CGAL_FORWARD_CALL_0(Mode,set_mode)
  Mode set_mode(Mode m){return CGAL::enum_cast<Mode>( this->get_data().set_mode( CGAL::enum_cast<typename Alpha_shape::Mode>(m) ) );}
  SWIG_CGAL_FORWARD_CALL_0(Mode,get_mode)
  SWIG_CGAL_FORWARD_CALL_0(void,clear)
  SWIG_CGAL_FORWARD_CALL_1(double,set_alpha,double)
  SWIG_CGAL_FORWARD_CALL_0(double,get_alpha)
  SWIG_CGAL_FORWARD_CALL_1(double,get_nth_alpha,int)
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_alphas)
  int make_alpha_shape(Point_range range){
    return this->get_data().make_alpha_shape(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));
  }  
//Traversal of the alpha-Values
  Alpha_iterator  alpha(){return Alpha_iterator(this->get_data().alpha_begin(),this->get_data().alpha_end());}
  Alpha_iterator  alpha_find(double a){return Alpha_iterator(this->get_data().alpha_find(a),this->get_data().alpha_end());}
  Alpha_iterator  alpha_lower_bound(double a){return Alpha_iterator(this->get_data().alpha_lower_bound(a),this->get_data().alpha_end());}
  Alpha_iterator  alpha_upper_bound(double a){return Alpha_iterator(this->get_data().alpha_upper_bound(a),this->get_data().alpha_end());}
//Operations
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_solid_components) 
  SWIG_CGAL_FORWARD_CALL_1(int,number_of_solid_components,double) 
  Alpha_iterator  find_optimal_alpha(int i){return Alpha_iterator(this->get_data().find_optimal_alpha(i),this->get_data().alpha_end());}  
  Alpha_shape_vertices_iterator  alpha_shape_vertices(){return Alpha_shape_vertices_iterator(this->get_data().alpha_shape_vertices_begin(),this->get_data().alpha_shape_vertices_end());}
  Alpha_shape_edges_iterator     alpha_shape_edges(){return Alpha_shape_edges_iterator(this->get_data().alpha_shape_edges_begin(),this->get_data().alpha_shape_edges_end());}
//Predicates
  SWIG_CGAL_FORWARD_CALL_1(Classification_type,classify,Point)
  SWIG_CGAL_FORWARD_CALL_1(Classification_type,classify,Face_handle)
  SWIG_CGAL_FORWARD_CALL_1(Classification_type,classify,Edge )
  SWIG_CGAL_FORWARD_CALL_2(Classification_type,classify,Face_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(Classification_type,classify,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_2(Classification_type,classify,Point,double)
  SWIG_CGAL_FORWARD_CALL_2(Classification_type,classify,Face_handle,double)
  SWIG_CGAL_FORWARD_CALL_2(Classification_type,classify,Edge,double)
  SWIG_CGAL_FORWARD_CALL_3(Classification_type,classify,Face_handle,int,double)
  SWIG_CGAL_FORWARD_CALL_2(Classification_type,classify,Vertex_handle,double)  
};


#endif //SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_2_H

//I/O
//  ostream&  ostream& os << A  Inserts the alpha shape A for the current ?-value into the stream os.
