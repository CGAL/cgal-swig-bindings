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
    boost::single_pass_traversal_tag,
    typename boost::mpl::if_<
          boost::mpl::bool_<internal::Converter<Cpp_wrapper>::is_reference>, 
          Cpp_base&, Cpp_base
        >::type //this allows to use a reference for dereference when possible
    >
{
  friend class boost::iterator_core_access;

  void update_with_next_point(){
    if (m_item!=NULL){ Py_DECREF(m_item); }
    m_item = PyIter_Next(m_iterator);
    if ( m_item!=NULL ){
      void* ret=0;
      int res = SWIG_ConvertPtr(m_item, &ret, m_type,  0  | 0);
      if (!SWIG_IsOK(res)) {// object is not of correct type
        SWIG_SetErrorMsg(PyExc_TypeError, "object is of incorrect type.");
        m_current_ptr=NULL;
        throw Bad_element_type();
        return;
      }
      m_current_ptr=reinterpret_cast<Cpp_wrapper*> (ret);
    }
    else
      m_current_ptr=NULL;
  }
  
  PyObject* m_iterator;
  PyObject* m_item; //m_item must stay valid so that m_current_ptr is
  Cpp_wrapper* m_current_ptr;
  swig_type_info* m_type;
  
  
public:
  Input_iterator_wrapper():m_iterator(NULL),m_item(NULL),m_current_ptr(NULL){}
  Input_iterator_wrapper(const Input_iterator_wrapper& other)
    :m_iterator(other.m_iterator),m_item(other.m_item),m_current_ptr(other.m_current_ptr),m_type(other.m_type)
  {
    if (m_iterator!=NULL){ Py_INCREF(m_iterator); }
    if (m_item!=NULL) { Py_INCREF(m_item);  }
  }
  Input_iterator_wrapper(PyObject * container,swig_type_info* tinfo)
    :m_iterator(NULL),m_item(NULL),m_type(tinfo)
  {
    m_iterator=PyObject_GetIter(container);
    
    //only for function with overload !!!
    if (!(PyIter_Check(m_iterator)) ){
      SWIG_SetErrorMsg(PyExc_TypeError, "Not an iterator.");
      if (m_iterator!=NULL) {Py_DECREF(m_iterator); m_iterator=NULL;}
      throw Not_an_iterator();
    }
    update_with_next_point();
  }
  ~Input_iterator_wrapper(){
    if (m_iterator!=NULL){ Py_DECREF(m_iterator); }
    if (m_item!=NULL) { Py_DECREF(m_item);  }
  }
  Input_iterator_wrapper&  operator=(const Input_iterator_wrapper& other){
    //cleanup
    if (m_iterator!=NULL){ Py_DECREF(m_iterator); }
    if (m_item!=NULL) { Py_DECREF(m_item);  }
    //copy
    m_iterator=other.m_iterator;
    m_item=other.m_item;
    m_current_ptr=other.m_current_ptr;
    m_type=other.m_type;
    if (m_iterator!=NULL){ Py_INCREF(m_iterator); }
    if (m_item!=NULL) { Py_INCREF(m_item);  }
    return *this;
  }
  
  void increment(){update_with_next_point();}
  bool equal(const Input_iterator_wrapper & other) const{ return m_current_ptr==other.m_current_ptr; }

  typename boost::mpl::if_<
        boost::mpl::bool_<internal::Converter<Cpp_wrapper>::is_reference>, 
        Cpp_base&, Cpp_base
      >::type
    dereference() const { 
      return internal::Converter<Cpp_wrapper>::convert(*m_current_ptr);
    }
};

//This wrapper is the former I used when input iterator could only be a list.
template <class Cpp_wrapper,class Cpp_base>
class Input_iterator_wrapper_for_lists:
public boost::iterator_facade<
    Input_iterator_wrapper_for_lists<Cpp_wrapper,Cpp_base>,
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
      PyObject *m_item = PyList_GetItem(list, current);
      void* ret=0;
      int res = SWIG_ConvertPtr(m_item, &ret, m_type,  0  | 0);
      if (!SWIG_IsOK(res)) {// object in list is not of correct type
        SWIG_SetErrorMsg(PyExc_TypeError, "List contains at least one object with incorrect type.");
        throw Bad_element_type();
        m_current_ptr=NULL;
        return;
      }
      m_current_ptr=reinterpret_cast<Cpp_wrapper*> (ret); 
      ++current;
    }
    else
      m_current_ptr=NULL;
  }
  
  PyObject* list;
  unsigned size;
  unsigned current;
  Cpp_wrapper* m_current_ptr;
  swig_type_info* m_type;
  
public:
  

  Input_iterator_wrapper_for_lists():m_current_ptr(NULL){}
  Input_iterator_wrapper_for_lists(PyObject * list_,swig_type_info* tinfo):list(list_),m_type(tinfo)
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
  bool equal(const Input_iterator_wrapper_for_lists & other) const{ return m_current_ptr==other.m_current_ptr; }

  typename boost::mpl::if_<
        boost::mpl::bool_<internal::Converter<Cpp_wrapper>::is_reference>, 
        const Cpp_base&, Cpp_base
      >::type
    dereference() const { return internal::Converter<Cpp_wrapper>::convert(*m_current_ptr); }
};




#endif //SWIG_CGAL_PYTHON_INPUT_ITERATOR_WRAPPER_H

