#ifndef SWIG_CGAL_COMMON_OPTIONAL_H
#define SWIG_CGAL_COMMON_OPTIONAL_H

template <class T>
class Optional
{
  bool empty_;
  T value_;
public:
  Optional():empty_(true){}
  Optional(const T& t):empty_(false),value_(t){}
  
  bool empty() const {return empty_;}
  const T& value() const {return value_;}  
};

#endif //SWIG_CGAL_COMMON_OPTIONAL_H
