// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_SPATIAL_SEARCHING_NN_SEARCH_H
#define SWIG_CGAL_SPATIAL_SEARCHING_NN_SEARCH_H

#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Common/Iterator.h>
#include <boost/shared_ptr.hpp>

template <class Cpp_base,class Query,class Tree>
class NN_search_wrapper
{
  //use a shared_ptr on the tree to avoid languages with garbage collector to
  //collect the tree while used by this class  
  boost::shared_ptr<typename Tree::cpp_base> tree_ptr;
  Cpp_base data;
  typedef NN_search_wrapper<Cpp_base,Query,Tree> Self;
  NN_search_wrapper(const Self&); //prevent copies
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  #endif

  typedef typename Tree::Point_d Point_d;
  typedef std::pair<Point_d,double>  Point_with_transformed_distance;
  typedef SWIG_CGAL_Iterator<typename Cpp_base::iterator,Point_with_transformed_distance> Iterator;
//Creation
  NN_search_wrapper(Tree& tree,const Query& query):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data()){}
  NN_search_wrapper(Tree& tree,const Query& query,int k):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data(),k){}
  NN_search_wrapper(Tree& tree,const Query& query,int k,double eps):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data(),k,eps){}
  NN_search_wrapper(Tree& tree,const Query& query,int k,double eps,bool search_nearest):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data(),k,eps,search_nearest){}
//Operations
  Iterator iterator() {
    return Iterator(data.begin(),data.end());
  }
};

template <class Cpp_base,class Query,class Tree>
class NN_search_wrapper_incremental
{
  //use a shared_ptr on the tree to avoid languages with garbage collector to
  //collect the tree while used by this class
  boost::shared_ptr<typename Tree::cpp_base> tree_ptr;  
  Cpp_base data;
  typedef NN_search_wrapper_incremental<Cpp_base,Query,Tree> Self;
  NN_search_wrapper_incremental(const Self&); //prevent copies
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
public:
  #ifndef SWIG
  typedef Cpp_base cpp_base;
  #endif
  typedef typename Tree::Point_d Point_d;
  typedef std::pair<Point_d,double>  Point_with_transformed_distance;
  typedef SWIG_CGAL_Iterator<typename Cpp_base::iterator,Point_with_transformed_distance> Iterator;
//Creation
  NN_search_wrapper_incremental(Tree& tree,const Query& query):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data()){}
  NN_search_wrapper_incremental(Tree& tree,const Query& query,double eps):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data(),eps){}
  NN_search_wrapper_incremental(Tree& tree,const Query& query,double eps,bool search_nearest):tree_ptr(tree.shared_ptr()),data(*tree_ptr,query.get_data(),eps,search_nearest){}
//Operations
  Iterator iterator() {
    return Iterator(data.begin(),data.end());
  }
  
  Point_d value(){
    typename Cpp_base::iterator it=data.begin();
    Point_d ret (( it )->first);
    ++it;
    return ret;
    
  }
};


#endif //SWIG_CGAL_SPATIAL_SEARCHING_NN_SEARCH_H

//Operations
// std::ostream&  s.statistics ( std::ostream& s)  Inserts statistics of the search process into the output stream s. 