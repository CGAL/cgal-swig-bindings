// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_2_QUALITY_H
#define SWIG_CGAL_MESH_2_QUALITY_H

template <class Criteria>
class Quality_pair_wrapper{
  typename Criteria::Quality data;
  typedef Quality_pair_wrapper<Criteria>  Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef typename Criteria::Quality cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
        
  Quality_pair_wrapper(const cpp_base& base):data(base){}
  #endif
  Quality_pair_wrapper():data(){}
  Quality_pair_wrapper(double first,double second):data(first,second){}
  double getFirst() const {return data.first;}
  double getSecond() const {return data.second;}
  void setFirst(double d) {data.first=d;}
  void setSecond(double d) {data.second=d;}
};

#endif // SWIG_CGAL_MESH_2_QUALITY_H
