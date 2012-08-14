// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_SPATIAL_SEARCHING_KD_TREE_H
#define SWIG_CGAL_SPATIAL_SEARCHING_KD_TREE_H


#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
#include <boost/shared_ptr.hpp>

#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
template <class Query>
struct Query_iterator_helper{
  typedef typename internal::Converter<Query>::result_type Base;
  typedef std::pair<Input_iterator_wrapper<Query,Base>,Input_iterator_wrapper<Query,Base> > input;
  typedef boost::function_output_iterator< Container_writer<Query,Base> >                                       output;
};
#endif

template<class Cpp_base, class Query, class Fuzzy_sphere, class Fuzzy_iso_box>
class Kd_tree_wrapper{
  boost::shared_ptr<Cpp_base> data_sptr;
  typedef Kd_tree_wrapper<Cpp_base,Query,Fuzzy_sphere,Fuzzy_iso_box>  Self;
  Kd_tree_wrapper(const Self&); //right now CGAL's KDtree does not have a copy constructor.
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  const cpp_base& get_data() const {return *data_sptr;}
        cpp_base& get_data()       {return *data_sptr;}
  boost::shared_ptr<cpp_base> shared_ptr() {return data_sptr;}
  #endif
  typedef SWIG_CGAL_Iterator<typename Cpp_base::iterator,Query> Iterator;
  typedef Query Point_d;
//Input iterator
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef typename Query_iterator_helper<Query>::input       Point_range; 
  #else
  typedef Generic_input_iterator<Query> Point_range;
  #endif

//Creation
  Kd_tree_wrapper():data_sptr(new cpp_base()){}
  Kd_tree_wrapper(Point_range range):data_sptr(new cpp_base(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range))){}
  
//Operations
  SWIG_CGAL_FORWARD_CALL_1(void,insert,Point_d)
  void insert(Point_range range){ get_data().insert(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range));}
  Iterator iterator(){return Iterator(get_data().begin(),get_data().end());}
  SWIG_CGAL_FORWARD_CALL_0(void,clear)
  SWIG_CGAL_FORWARD_CALL_0(int,size)
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  void search(typename Query_iterator_helper<Query>::output out, const Fuzzy_sphere& fsphere) { get_data().search(out,fsphere.get_data());}
  void search(typename Query_iterator_helper<Query>::output out, const Fuzzy_iso_box& fbox)   { get_data().search(out,fbox.get_data());}
  #else
  void search(Generic_output_iterator<Query> out, const Fuzzy_sphere& fsphere) { get_data().search(out,fsphere.get_data());}
  void search(Generic_output_iterator<Query> out, const Fuzzy_iso_box& fbox)   { get_data().search(out,fbox.get_data());}
  #endif
  
  SWIG_CGAL_FORWARD_CALL_0(void,build)
//Special for SWIG
  bool same_internal_object(const Kd_tree_wrapper<Cpp_base,Query,Fuzzy_sphere,Fuzzy_iso_box>& other) {return other.data_sptr.get()==data_sptr.get();}
};


#endif //SWIG_CGAL_SPATIAL_SEARCHING_KD_TREE_H

//Operations
//  SWIG_CGAL_FORWARD_CALL_0(Node_handle,root)
// Kd_tree_rectangle<Traits>  tree.bounding_box ()  
// std::ostream&  tree.statistics ( std::ostream& s)