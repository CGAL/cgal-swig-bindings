/*
  Shape_iterator.h
  Teton Simulation
  Authored on   October 24, 2019
  Last Modified October 24, 2019
*/

#ifndef CGAL_SWIG_SHAPE_ITERATOR_H
#define CGAL_SWIG_SHAPE_ITERATOR_H

#include <CGAL/Shape_detection_3.h>
#include <SWIG_CGAL/Common/Macros.h>

template <class Shape_detection>
class Shape_iterator_wrapper
{
protected:
  boost::shared_ptr<Shape_detection> data;

public: 
  #ifndef SWIG
  typedef boost::shared_ptr<Shape_detection> cpp_base;
  Shape_iterator_wrapper(cpp_base h):data(h){}
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  #endif
  typedef Shape_iterator_wrapper<Shape_detection> Self;

  //Shape_iterator_wrapper(boost::shared_ptr<Shape_detection> ptr) {data = ptr;}
  
  Shape_iterator_wrapper():data(NULL){}
  
//Operations
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Shape_iterator_wrapper, shapes)

  //int count(){ return data->shapes().end() - data->shapes().begin(); }

};


#endif
