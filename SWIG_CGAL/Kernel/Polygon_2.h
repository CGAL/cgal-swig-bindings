// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_POLYGON_2_H
#define SWIG_CGAL_KERNEL_POLYGON_2_H

#include <sstream>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Segment_2.h>
#include <SWIG_CGAL/Kernel/Bbox_2.h>
#include <SWIG_CGAL/Kernel/enum.h>
  
#include <CGAL/Polygon_2.h>
#include <boost/next_prior.hpp>

class SWIG_CGAL_KERNEL_DECL Polygon_2{
  CGAL::Polygon_2<EPIC_Kernel,std::vector<EPIC_Kernel::Point_2> > data;
public:
  #ifndef SWIG
  typedef CGAL::Polygon_2<EPIC_Kernel,std::vector<EPIC_Kernel::Point_2> > cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Polygon_2(const cpp_base& base):data(base){}
  #endif

//Creation
  Polygon_2():data(){}
//Modifiers
  void set( int pos, Point_2 x){data.set(boost::next(data.vertices_begin(),pos),x.get_data());}
  int insert( int i, Point_2 q){return std::distance(data.vertices_begin(),data.insert(boost::next(data.vertices_begin(),i),q.get_data()));}
  SWIG_CGAL_FORWARD_CALL_1(void,push_back,Point_2)
  SWIG_CGAL_FORWARD_CALL_0(void,clear)
  SWIG_CGAL_FORWARD_CALL_0(void,reverse_orientation)
  void erase ( int i) {data.erase(boost::next(data.vertices_begin(),i));}
  void erase (int i, int j){data.erase(boost::next(data.vertices_begin(),i),boost::next(data.vertices_begin(),j));}  
//Predicates
  SWIG_CGAL_FORWARD_CALL_0(bool,is_simple)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_convex)
  SWIG_CGAL_FORWARD_CALL_0(Orientation,orientation)
  SWIG_CGAL_FORWARD_CALL_1(Oriented_side,oriented_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(Bounded_side,bounded_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_0(double,area)
  int left_vertex ()  {return std::distance(data.vertices_begin(),data.left_vertex());}
  int right_vertex()  {return std::distance(data.vertices_begin(),data.right_vertex());}
  int top_vertex()    {return std::distance(data.vertices_begin(),data.top_vertex());}
  int bottom_vertex() {return std::distance(data.vertices_begin(),data.bottom_vertex());}
  SWIG_CGAL_FORWARD_CALL_0(bool,is_counterclockwise_oriented)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_clockwise_oriented)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_collinear_oriented)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_positive_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_negative_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_boundary,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_bounded_side,Point_2)
  SWIG_CGAL_FORWARD_CALL_1(bool,has_on_unbounded_side,Point_2)
//Random access methods
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,vertex,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Segment_2,edge,int)
//Miscellaneous
  SWIG_CGAL_FORWARD_CALL_0(int,size)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_empty)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Bbox_2,bbox)
//Operators
  DEFINE_EQUALITY_OPERATORS(Polygon_2)
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Polygon_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};
#endif //SWIG_CGAL_KERNEL_POLYGON_2_H

//  Polygon_2<Traits,Container> transform ( Transformation t, Polygon_2<Traits,Container> p)
