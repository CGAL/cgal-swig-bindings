// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_COMMON_VARIANT_H
#define SWIG_CGAL_COMMON_VARIANT_H

#if CGAL_VERSION_NR >= 1060000000
#include <variant>
#else
#include <boost/variant.hpp>
#endif

template <class T1,class T2>
class Variant
{
  typedef typename internal::Converter<T1>::result_type T1_base;
  typedef typename internal::Converter<T2>::result_type T2_base;
public:
  typedef Variant<T1,T2> Self;
#ifndef SWIG
#if CGAL_VERSION_NR >= 1060000000
  typedef std::variant< T1_base,T2_base > cpp_base;
#else
  typedef boost::variant< T1_base,T2_base > cpp_base;
#endif
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Variant(const cpp_base& base):data(base){}
#endif // not SWIG

  Variant():data(){}
  Variant(const T1& t1):data(internal::Converter<T1>::convert(t1)){}
  Variant(const T2& t2):data(internal::Converter<T2>::convert(t2)){}

#if CGAL_VERSION_NR >= 1060000000
  bool is_of_first_type()  const {return std::get_if<T1_base>(&data)?true:false;}
  bool is_of_second_type() const {return std::get_if<T2_base>(&data)?true:false;}
  T1 get_first()  const {return T1(std::get<T1_base>(data));}
  T2 get_second() const {return T2(std::get<T2_base>(data));}
#else
  bool is_of_first_type()  const {return boost::get<T1_base>(&data)?true:false;}
  bool is_of_second_type() const {return boost::get<T2_base>(&data)?true:false;}
  T1 get_first()  const {return T1(boost::get<T1_base>(data));}
  T2 get_second() const {return T2(boost::get<T2_base>(data));}
#endif
//Deep copy
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
private:
  cpp_base data;
};

#endif //SWIG_CGAL_COMMON_VARIANT_H
