// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_VARIANT_H
#define SWIG_CGAL_COMMON_VARIANT_H

#include <boost/variant.hpp>

template <class T1,class T2>
class Variant
{
  typedef typename internal::Converter<T1>::result_type T1_base;
  typedef typename internal::Converter<T2>::result_type T2_base;
public:
  typedef Variant<T1,T2> Self;
#ifndef SWIG
  typedef boost::variant< T1_base,T2_base > cpp_base;
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
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
private:
  cpp_base data;  
};

#endif //SWIG_CGAL_COMMON_VARIANT_H
