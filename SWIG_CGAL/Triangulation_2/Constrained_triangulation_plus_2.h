// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H
#define SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H

#include <SWIG_CGAL/Triangulation_2/Constrained_triangulation_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>  
#include <CGAL/version.h>

#ifndef SWIG
#include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>
template <class Triangulation,class Point>
struct Iterator_helper<std::pair<SWIG_Triangulation_2::CGAL_Vertex_handle<Triangulation,Point>,SWIG_Triangulation_2::CGAL_Vertex_handle<Triangulation,Point> > >{
  typedef SWIG_Triangulation_2::CGAL_Vertex_handle<Triangulation,Point> Vertex_handle;

  template <class T1, class T2>
  static std::pair<Vertex_handle,Vertex_handle> convert(const std::pair<T1,T2>& i){
    return std::pair<Vertex_handle,Vertex_handle>(Vertex_handle(i.first.first),Vertex_handle(i.first.second));
  }

  #if CGAL_VERSION_NR >= 1040600000
  static std::pair<Vertex_handle,Vertex_handle> convert(const typename Triangulation::Constraint_id& i){
    return std::pair<Vertex_handle,Vertex_handle>(Vertex_handle(i.second->front().vertex()),
                                                  Vertex_handle(i.second->back().vertex()));
  }
  #endif

  template <class Iterator>
  static std::pair<Vertex_handle,Vertex_handle> convert(Iterator it){
    return convert(*it);
  }

  static std::pair<Vertex_handle,Vertex_handle>
  default_value(){return std::pair<Vertex_handle,Vertex_handle>(Vertex_handle(NULL),Vertex_handle(NULL));}
};
#endif

template <class CDT_plus_2, class Vertex_handle>
class CDTP_context{
  typename CDT_plus_2::Context data;
  typedef CDTP_context<CDT_plus_2,Vertex_handle> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);  
public:
  #ifndef SWIG
  typedef typename CDT_plus_2::Context cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  CDTP_context(const cpp_base& p):data(p){}
  #endif
  typedef SWIG_CGAL_Iterator<typename CDT_plus_2::Vertices_in_constraint_iterator,Vertex_handle>  Vertices_in_constraint_iterator;    
  CDTP_context(){}
  Vertices_in_constraint_iterator vertices() {return Vertices_in_constraint_iterator(data.vertices_begin(),data.vertices_end());}
  Vertices_in_constraint_iterator current() {return Vertices_in_constraint_iterator(data.current(),data.vertices_end());}
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_vertices)
};

template < class Cpp_base,class Base_triangulation_wrapper, class Vertex_handle >
class Constrained_triangulation_plus_2_wrapper: public Base_triangulation_wrapper
{
  typedef Base_triangulation_wrapper Base;
public:
  #ifndef SWIG  
  typedef typename Base_triangulation_wrapper::cpp_base                 cpp_base;
  #endif
  typedef std::pair<Vertex_handle,Vertex_handle>                        Constraint_handle;
  typedef CDTP_context<Cpp_base,Vertex_handle>                          Context;

  typedef SWIG_CGAL_Iterator<typename Cpp_base::Constraint_iterator,Constraint_handle>          Constraint_iterator;
  typedef SWIG_CGAL_Iterator<typename Cpp_base::Subconstraint_iterator,Constraint_handle>       Subconstraint_iterator;
  typedef SWIG_CGAL_Iterator<typename Cpp_base::Vertices_in_constraint_iterator,Vertex_handle>  Vertices_in_constraint_iterator;
  typedef SWIG_CGAL_Iterator<typename Cpp_base::Context_iterator,Context>                       Context_iterator;

  Constrained_triangulation_plus_2_wrapper():Base(){}
  Constrained_triangulation_plus_2_wrapper(Constraint_range range):Base(){
    for (Input_constraint_iterator it=SWIG_CGAL::get_begin(range);it!=SWIG_CGAL::get_end(range);++it)
      this->get_data().push_back(*it);
  }
  #ifndef SWIG
  Constrained_triangulation_plus_2_wrapper(const cpp_base& cbase):Base(cbase){}
  #endif
  SWIG_CGAL_FORWARD_CALL_2(void,remove_constraint,Vertex_handle,Vertex_handle)
// Queries
  SWIG_CGAL_FORWARD_CALL_2(int,number_of_enclosing_constraints,Vertex_handle,Vertex_handle)
  Constraint_iterator constraints(){return Constraint_iterator( this->get_data().constraints_begin(),this->get_data().constraints_end() );}
  Subconstraint_iterator subconstraints(){return Subconstraint_iterator( this->get_data().subconstraints_begin(),this->get_data().subconstraints_end() );}
  Vertices_in_constraint_iterator vertices_in_constraint(const Vertex_handle& va,const Vertex_handle& vb){ return Vertices_in_constraint_iterator(this->get_data().vertices_in_constraint_begin(va.get_data(),vb.get_data()),this->get_data().vertices_in_constraint_end(va.get_data(),vb.get_data()));}
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Context,context,Vertex_handle,Vertex_handle)
  Context_iterator contexts(const Vertex_handle& va,Vertex_handle& vb) {return Context_iterator(this->get_data().contexts_begin(va.get_data(),vb.get_data()),this->get_data().contexts_end(va.get_data(),vb.get_data()));}
//Deep copy
  typedef Constrained_triangulation_plus_2_wrapper<Cpp_base,Base_triangulation_wrapper,Vertex_handle> Self;
  Self deepcopy() const {return Self(this->get_data());}
};

#endif //SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H


// Creation
//   Constrained_triangulation_plus_2<Tr> ctp ( Geom_traits gt=Geom_traits());
//   Constrained_triangulation_plus_2<Tr> ctp ( Constrained_triangulation_plus_2 ct);
// Assignment
//   void   ctp.swap ( Constrained_triangulation_plus_2 tr)

