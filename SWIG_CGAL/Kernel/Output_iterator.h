#ifndef SWIG_CGAL_KERNEL_OUTPUT_ITERATOR_H
#define SWIG_CGAL_KERNEL_OUTPUT_ITERATOR_H

#include <vector>
#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/exceptions.h>
#endif


template<class Container,class Object>
class General_iterator{
  typename Container::cpp_iterator cur;
  typename Container::cpp_iterator end;
  
public:
  typedef Object value_type;

  General_iterator(
    typename Container::cpp_iterator cur_,
    typename Container::cpp_iterator end_
  ):cur(cur_),end(end_){}
   
  General_iterator __iter__(){return *this;}
  
  value_type next()
  {
    if (cur!=end)
      return *cur++;
    #ifdef SWIGPYTHON
    throw Stop_iteration();
    #endif
    return value_type();
  }
  
  bool hasNext(){
    return cur!=end;
  }
};


template <class Object>
class Output_iterator{
  std::vector<Object> data;
  
public:
  typedef typename std::vector<Object>::iterator cpp_iterator;
  typedef General_iterator<Output_iterator<Object>,Object > iterator;


  Output_iterator(){data.push_back(Object(1,1,1));data.push_back(Object(2,2,2));data.push_back(Object(3,3,3));}

  std::vector<Object>& get_data(){return data;}
  
  iterator objects(){
    return iterator(data.begin(),data.end());
  }
  
  
};


#endif //SWIG_CGAL_KERNEL_OUTPUT_ITERATOR_H
