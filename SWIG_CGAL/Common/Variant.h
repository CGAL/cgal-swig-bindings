#ifndef SWIG_CGAL_COMMON_VARIANT_H
#define SWIG_CGAL_COMMON_VARIANT_H

#include <boost/variant.hpp>

template <class T1,class T2>
class Variant
{
  typedef typename internal::Converter<T1>::result_type T1_base;
  typedef typename internal::Converter<T2>::result_type T2_base;
public:
#ifndef SWIG
  typedef boost::variant< T1_base,T2_base > cpp_base;
#endif
private:
  cpp_base data;
public:
#ifndef SWIG
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Variant(const cpp_base& base):data(base){}
#endif

  Variant():data(){}
  Variant(const T1& t1):data(internal::Converter<T1>::convert(t1)){}
  Variant(const T2& t2):data(internal::Converter<T2>::convert(t2)){}
  
  
  bool is_of_first_type()  const {return boost::get<T1_base>(&data)?true:false;}
  bool is_of_second_type() const {return boost::get<T2_base>(&data)?true:false;}
  T1 get_first()  const {return T1(boost::get<T1_base>(data));}
  T2 get_second() const {return T2(boost::get<T2_base>(data));}
};

#endif //SWIG_CGAL_COMMON_VARIANT_H
