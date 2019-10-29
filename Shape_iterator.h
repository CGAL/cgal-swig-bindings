/*
  Shape_iterator.h
  Teton Simulation
  Authored on   October 28, 2019
  Last modified October 28, 2019
*/

#ifndef SWIG_CGAL_SHAPE_ITERATOR_H
#define SWIG_CGAL_SHAPE_ITERATOR_H

#include <CGAL/Shape_detection_3.h>
#include <CGAL/Iterator_range.h>
#include <SWIG_CGAL/Common/Macros.h>


template <class Shape_detection>
class Shape_iterator_wrapper
{
  //  TYPE DEFINITIONS
public:
  typedef Shape_iterator_wrapper<Shape_detection> Self;
  typedef typename Shape_detection::Shape Shape;

protected:
  typename Shape_detection::Shape_range data;


public: 
  #ifndef SWIG
    typedef typename Shape_detection::Shape_range cpp_base;
    Shape_iterator_wrapper(cpp_base h):data(h){}
    const cpp_base& get_data() const {return data;}
          cpp_base& get_data()       {return data;}
  #endif

  Shape_iterator_wrapper(Shape_detection* data_ptr):data(data_ptr->shapes()){}

//  Accessors

  SWIG_CGAL_FORWARD_CALL_0(int,count)
  //SWIG_CGAL_FORWARD_CALL_AND_REF_0(Shape_iterator_wrapper, shapes)


//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};


#endif
