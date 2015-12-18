// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_OUTPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_COMMON_OUTPUT_ITERATOR_WRAPPER_H

#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/Output_iterator_wrapper.h>
#endif
#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/Output_iterator_wrapper.h>
#endif

#if SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
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
#else
#include <CGAL/value_type_traits.h>

namespace CGAL{
template <class Cpp_wrapper, class Cpp_base>
struct value_type_traits<
  boost::function_output_iterator< Container_writer<Cpp_wrapper, Cpp_base> >
>
{
  typedef Cpp_base type;
};
} //end of namespace CGAL
#endif

#endif //SWIG_CGAL_COMMON_OUTPUT_ITERATOR_WRAPPER_H
