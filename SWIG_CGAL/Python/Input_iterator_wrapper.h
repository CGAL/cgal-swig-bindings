// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_PYTHON_INPUT_ITERATOR_WRAPPER_H
#define SWIG_CGAL_PYTHON_INPUT_ITERATOR_WRAPPER_H

#include <boost/iterator/iterator_facade.hpp>
#include <stdexcept>

#include <SWIG_CGAL/Python/exceptions.h>

#ifdef SWIG
%include exception.i
#endif

template <class Cpp_wrapper,class Cpp_base>
class Input_iterator_wrapper:
public boost::iterator_facade<
    Input_iterator_wrapper<Cpp_wrapper,Cpp_base>,
    Cpp_base,
    boost::forward_traversal_tag,
    typename boost::mpl::if_<
          boost::mpl::bool_<internal::Converter<Cpp_wrapper>::is_reference>, 
          const Cpp_base&, Cpp_base
        >::type //this allows to use a reference for dereference when possible
    >
{
  friend class boost::iterator_core_access;

  void update_with_next_point(){
    if (current!=size){
      PyObject *item = PyList_GetItem(list, current);
      void* ret=0;
      int res = SWIG_ConvertPtr(item, &ret, type,  0  | 0);
      if (!SWIG_IsOK(res)) {// object in list is not of correct type
        SWIG_SetErrorMsg(PyExc_TypeError, "List contains at least one object with incorrect type.");
        throw Bad_list_element();
        current_ptr=NULL;
        return;
      }
      current_ptr=reinterpret_cast<Cpp_wrapper*> (ret); 
      ++current;
    }
    else
      current_ptr=NULL;
  }
  
  PyObject* list;
  unsigned size;
  unsigned current;
  Cpp_wrapper* current_ptr;
  swig_type_info* type;
  
public:
  

  Input_iterator_wrapper():current_ptr(NULL){}
  Input_iterator_wrapper(PyObject * list_,swig_type_info* tinfo):list(list_),type(tinfo)
  {
    
    // CGAL_precondition(PyList_Check(list)); //properly handle by a typecheck in SWIG macro
    //only for function with overload !!!
    if (!PyList_Check(list)){
      SWIG_SetErrorMsg(PyExc_TypeError, "Not a List.");
      throw Not_a_list();
    }
    size=PyList_Size(list);
    current=0;
    update_with_next_point();
  }

  
  void increment(){update_with_next_point();}
  bool equal(const Input_iterator_wrapper & other) const{ return current_ptr==other.current_ptr; }

  typename boost::mpl::if_<
        boost::mpl::bool_<internal::Converter<Cpp_wrapper>::is_reference>, 
        const Cpp_base&, Cpp_base
      >::type
    dereference() const { return internal::Converter<Cpp_wrapper>::convert(*current_ptr); }
};




#endif //SWIG_CGAL_PYTHON_INPUT_ITERATOR_WRAPPER_H

