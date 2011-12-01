// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_GENERIC_ITERATOR_H
#define SWIG_CGAL_GENERIC_ITERATOR_H

//This file contains general classes that can be used when nothing in
//done for a specific target languages to handle input and output iterators.

#include <SWIG_CGAL/Common/Iterator.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <iterator>


#ifndef SWIG
namespace internal{
  template <class Object>
  struct Container_writer_base{
    boost::shared_ptr< std::vector<Object> > data_sptr;
    Container_writer_base(): data_sptr(new std::vector<Object>() ){}
    std::vector<Object>& data() {return *data_sptr;}
  };
}
#endif


template <class Object>
class Generic_output_iterator
#ifndef SWIG
:public internal::Container_writer_base<typename internal::Converter<Object>::result_type>, 
 public std::back_insert_iterator<std::vector<typename internal::Converter<Object>::result_type> >
#endif
{
public:
  typedef typename internal::Converter<Object>::result_type Cpp_object;
  typedef SWIG_CGAL_Iterator<typename std::vector<Cpp_object>::iterator,Object > Iterator;

  #ifndef SWIG
  typedef internal::Container_writer_base<Cpp_object> Base1;
  typedef std::back_insert_iterator<std::vector<Cpp_object> > Base2;
  #endif

  Generic_output_iterator()
  #ifndef SWIG
  :Base1(), Base2(this->data())
  #endif
  {}

  Iterator iterator(){
    return Iterator(this->data().begin(),this->data().end());
  }
};

#endif //SWIG_CGAL_GENERIC_ITERATOR_H
