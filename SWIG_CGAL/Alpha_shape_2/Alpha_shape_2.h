#ifndef SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_2_H
#define SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_2_H

#include <CGAL/Alpha_shape_2.h>
#include <CGAL/Weighted_point.h>
#include <CGAL/Weighted_alpha_shape_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>

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

#include <SWIG_CGAL/Common/Input_iterator.h>

template <class Alpha_shape,class Point, class Vertex_handle, class Face_handle,class Weighted_tag,class Base>
class Alpha_shape_2_wrapper : public Base
{
public:
  typedef std::pair<Face_handle,int> Edge;
  typedef CGAL_Alpha_iterator<Alpha_shape,double>                              Alpha_iterator;
  typedef CGAL_Alpha_shape_vertices_iterator<Alpha_shape,Vertex_handle>        Alpha_shape_vertices_iterator;
  typedef CGAL_Alpha_shape_edges_iterator<Alpha_shape,Edge>                    Alpha_shape_edges_iterator;
//Creation
  Alpha_shape_2_wrapper(){}
  Alpha_shape_2_wrapper(double alpha){this->data.set_alpha(alpha);}
  Alpha_shape_2_wrapper(typename Weighting_helper<Weighted_tag>::Point_range range,double alpha){this->data.set_alpha(alpha); this->data.make_alpha_shape(range.first,range.second);}
  Alpha_shape_2_wrapper(double alpha,Mode m){this->data.set_alpha(alpha);this->data.set_mode( CGAL::enum_cast<typename Alpha_shape::Mode>(m) );}    
  Alpha_shape_2_wrapper(typename Weighting_helper<Weighted_tag>::Point_range range,double alpha,Mode m){
    this->data.set_alpha(alpha);
    this->data.set_mode( CGAL::enum_cast<typename Alpha_shape::Mode>(m) );
    this->data.make_alpha_shape(range.first,range.second);  
  }
//Operations
  FORWARD_CALL_0(Mode,set_mode)
  Mode set_mode(Mode m){return CGAL::enum_cast<Mode>( this->data.set_mode( CGAL::enum_cast<typename Alpha_shape::Mode>(m) ) );}
  FORWARD_CALL_0(Mode,get_mode)
  FORWARD_CALL_0(void,clear)
  FORWARD_CALL_1(double,set_alpha,double)
  FORWARD_CALL_0(double,get_alpha)
  FORWARD_CALL_1(double,get_nth_alpha,int)
  FORWARD_CALL_0(int,number_of_alphas)
  int make_alpha_shape(typename Weighting_helper<Weighted_tag>::Point_range range){
    return this->data.make_alpha_shape(range.first,range.second);
  }  
//Traversal of the alpha-Values
  Alpha_iterator  alpha(){return Alpha_iterator(this->data.alpha_begin(),this->data.alpha_end());}
  Alpha_iterator  alpha_find(double a){return Alpha_iterator(this->data.alpha_find(a),this->data.alpha_end());}
  Alpha_iterator  alpha_lower_bound(double a){return Alpha_iterator(this->data.alpha_lower_bound(a),this->data.alpha_end());}
  Alpha_iterator  alpha_upper_bound(double a){return Alpha_iterator(this->data.alpha_upper_bound(a),this->data.alpha_end());}
//Operations
  FORWARD_CALL_0(int,number_of_solid_components) 
  FORWARD_CALL_1(int,number_of_solid_components,double) 
  Alpha_iterator  find_optimal_alpha(int i){return Alpha_iterator(this->data.find_optimal_alpha(i),this->data.alpha_end());}  
  Alpha_shape_vertices_iterator  alpha_shape_vertices(){return Alpha_shape_vertices_iterator(this->data.alpha_shape_vertices_begin(),this->data.alpha_shape_vertices_end());}
  Alpha_shape_edges_iterator     alpha_shape_edges(){return Alpha_shape_edges_iterator(this->data.alpha_shape_edges_begin(),this->data.alpha_shape_edges_end());}

  
//Predicates
  FORWARD_CALL_1(Classification_type,classify,Point)
  FORWARD_CALL_1(Classification_type,classify,Face_handle)
  FORWARD_CALL_1(Classification_type,classify,Edge )
  FORWARD_CALL_2(Classification_type,classify,Face_handle,int)
  FORWARD_CALL_1(Classification_type,classify,Vertex_handle)
  FORWARD_CALL_2(Classification_type,classify,Point,double)
  FORWARD_CALL_2(Classification_type,classify,Face_handle,double)
  FORWARD_CALL_2(Classification_type,classify,Edge,double)
  FORWARD_CALL_3(Classification_type,classify,Face_handle,int,double)
  FORWARD_CALL_2(Classification_type,classify,Vertex_handle,double)  
 
};


#endif //SWIG_CGAL_ALPHA_SHAPE_2_ALPHA_SHAPE_2_H

//Creation
//  template < class InputIterator > Alpha_shape_2<Dt> A ( InputIterator first, InputIterator last, FT alpha = 0, Mode m = GENERAL);
//Operations
//  template < class InputIterator > int  A.make_alpha_shape ( InputIterator first, InputIterator last)
//I/O
//  ostream&  ostream& os << A  Inserts the alpha shape A for the current ?-value into the stream os.
