// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_INPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_COMMON_INPUT_ITERATOR_WRAPPER_H

#include <SWIG_CGAL/Common/Macros.h>

#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/Input_iterator_wrapper.h>
#endif
#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/Input_iterator_wrapper.h>
#endif

namespace SWIG_CGAL{
  template <class T> inline T& get_begin(std::pair<T,T>& p){return p.first;}
  template <class T> inline T& get_end(std::pair<T,T>& p){return p.second;}
}


#if SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Object>
class Generic_input_iterator
{
  typedef typename internal::Converter<Object>::result_type Cpp_object;
  boost::shared_ptr< std::vector<Cpp_object> > data_sptr;
public:
  
  typedef typename std::vector<Cpp_object>::iterator Iterator;

  Generic_input_iterator():data_sptr(new std::vector<Cpp_object>()){}

  void reserve(int k){data_sptr->reserve(k);}
    
  void push_back(const Object& obj){
    data_sptr->push_back( internal::Converter<Object>::convert(obj) );
  }
  
  #ifndef SWIG
  Iterator begin(){
    return data_sptr->begin();
  }
  Iterator end(){
    return data_sptr->end();
  }
  #endif
};

namespace SWIG_CGAL{
  template <class Object> 
  inline typename Generic_input_iterator<Object>::Iterator get_begin(Generic_input_iterator<Object>& gii){return gii.begin();}
  template <class Object> 
  inline typename Generic_input_iterator<Object>::Iterator get_end  (Generic_input_iterator<Object>& gii){return gii.end();}  
}
#endif


#endif //SWIG_CGAL_COMMON_INPUT_ITERATOR_WRAPPER_H
