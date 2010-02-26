#ifndef SWIG_CGAL_COMMON_OUTPUT_ITERATOR_H
#define SWIG_CGAL_COMMON_OUTPUT_ITERATOR_H

#include <vector>


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
    throw 1;
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


  std::vector<Object>& get_data(){return data;}
  
  iterator objects(){
    return iterator(data.begin(),data.end());
  }
  
  
};


#endif //SWIG_CGAL_COMMON_OUTPUT_ITERATOR_H
