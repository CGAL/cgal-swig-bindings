#ifndef SWIG_CGAL_COMMON_OPTIONAL_H
#define SWIG_CGAL_COMMON_OPTIONAL_H

#include <boost/optional.hpp>

template <class T>
class Optional
{
  boost::optional<T> data;
  bool empty_;
public:
  #ifndef SWIG
  typedef boost::optional<T> cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}
  Optional(const cpp_base& base):data(base){}
  #endif

  Optional():data(){}
  Optional(const T& t):data(t){}
  
  bool empty() const {return data?false:true;}
  const T& value() const {return *data;}  
};

#endif //SWIG_CGAL_COMMON_OPTIONAL_H
