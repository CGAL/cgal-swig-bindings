#ifndef CGAL_SWIG_PYTHON_INPUT_ITERATOR_WRAPPER_H
#define CGAL_SWIG_PYTHON_INPUT_ITERATOR_WRAPPER_H

#include <boost/iterator/iterator_facade.hpp>
#include <stdexcept>

#ifdef SWIG
%include exception.i
#endif

template <class Cpp_wrapper,class Cpp_base>
class Input_iterator_wrapper:
public boost::iterator_facade<
    Input_iterator_wrapper<Cpp_wrapper,Cpp_base>,
    const Cpp_base,
    boost::forward_traversal_tag>
{
  friend class boost::iterator_core_access;

  void update_with_next_point(){
    if (current!=size){
      PyObject *item = PyList_GetItem(list, current);
      void* ret=0;
      int res = SWIG_ConvertPtr(item, &ret, type,  0  | 0);
      if (!SWIG_IsOK(res)) {// object in list is not of correct type
        PyErr_SetString(PyExc_TypeError, "List contains a least one object with incorrect type.");
        throw 1;
        current_ptr=NULL;
        return;
      }
      current_ptr=(Cpp_wrapper*) ret;
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
    if (!PyList_Check(list)) { //not a list
      current_ptr=NULL;
      PyErr_SetString(PyExc_TypeError, "Not a list.");
      throw 1;
      return;
    }
    size=PyList_Size(list);
    update_with_next_point();
    current=0;
  }

  
  void increment(){update_with_next_point();}
  bool equal(const Input_iterator_wrapper & other) const{ return current_ptr==other.current_ptr; }
  const Cpp_base& dereference() const { current_ptr->get_data_ref(); }
};




#endif //CGAL_SWIG_PYTHON_INPUT_ITERATOR_WRAPPER_H

