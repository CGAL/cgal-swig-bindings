/*
  Shape_iterator.h
  Teton Simulation
  Authored on   October 24, 2019
  Last Modified October 24, 2019
*/

#ifndef CGAL_SWIG_SHAPE_ITERATOR_H
#define CGAL_SWIG_SHAPE_ITERATOR_H


template <class Shape_detection, class Shape_range>
class Shape_iterator_wrapper
{
protected:
  Shape_detection* data_ptr;
  boost::shared_ptr<Shape_range> shapes;

public: 
  #ifndef SWIG
    typedef Shape_detection cpp_base;
    const cpp_base& get_data() const {return *data_ptr;}
    const cpp_base& get_data()       {return *data_ptr;}
    Shape_iterator_wrapper(const cpp_base& base):data_ptr(new cpp_base(base)) {}
  #endif

//  Constructors
  Shape_iterator_wrapper(Shape_detection* ptr)
  {
    data_ptr = ptr;
    *shapes = ptr->shapes();
  }

  int count() { return shapes->end() - shapes->begin(); }
  

};


#endif
