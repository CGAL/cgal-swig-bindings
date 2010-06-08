#ifndef SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H
#define SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H

template<class T1,class T2>
struct Iterator_helper<std::pair<T1,T2> >{
  template <class T>
  static std::pair<T1,T2> convert(const T& i){
    return std::pair<T1,T2>(T1(i->first.first),T2(i->first.second));
  }
  
  static std::pair<T1,T2>
  default_value(){return std::pair<T1,T2>(T1(NULL),T2(NULL));}
};

template < class Base_triangulation_wrapper, class Vertex_handle >
class Constrained_triangulation_plus_2_wrapper: public Base_triangulation_wrapper
{
  typedef Base_triangulation_wrapper Base;
public:
  typedef typename Base_triangulation_wrapper::cpp_base                 cpp_base;
  typedef std::pair<Vertex_handle,Vertex_handle>                        Constraint_handle;
  typedef CGAL_Constraint_iterator<cpp_base,Constraint_handle>          Constraint_iterator;
  typedef CGAL_Subconstraint_iterator<cpp_base,Constraint_handle>       Subconstraint_iterator;
  typedef CGAL_Vertices_in_constraint_iterator<cpp_base,Vertex_handle>  Vertices_in_constraint_iterator;


  Constrained_triangulation_plus_2_wrapper():Base(){}
  
// Queries
  FORWARD_CALL_2(int,number_of_enclosing_constraints,Vertex_handle,Vertex_handle)
  Constraint_iterator constraints(){return Constraint_iterator( this->data.constraints_begin(),this->data.constraints_end() );}
  Subconstraint_iterator subconstraints(){return Subconstraint_iterator( this->data.subconstraints_begin(),this->data.subconstraints_end() );}
  Vertices_in_constraint_iterator vertices_in_constraint(const Vertex_handle& va,const Vertex_handle& vb){ return Vertices_in_constraint_iterator(this->data.vertices_in_constraint_begin(va.get_data(),vb.get_data()),this->data.vertices_in_constraint_end(va.get_data(),vb.get_data()));}
  
};

#endif //SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H


// Creation
//   Constrained_triangulation_plus_2<Tr> ctp ( Geom_traits gt=Geom_traits());
//   Constrained_triangulation_plus_2<Tr> ctp ( Constrained_triangulation_plus_2 ct);
//   template<class InputIterator>
//   Constrained_triangulation_plus_2<Tr> ctp ( InputIterator first, InputIterator last, Geom_traits gt= Geom_traits());
// Assignment
//   void   ctp.swap ( Constrained_triangulation_plus_2 tr)
// Queries
//   Context   ctp.context ( Vertex_handle va, Vertex_handle vb)
//   Context_iterator   ctp.contexts_begin ( Vertex_handle va, Vertex_handle vb)
//   Context_iterator   ctp.contexts_end ( Vertex_handle va, Vertex_handle vb)
//   Vertices_in_constraint_iterator   ctp.vertices_in_constraint_begin ( Vertex_handle va, Vertex_handle vb)
//   Vertices_in_constraint_iterator   ctp.vertices_in_constraint_end ( Vertex_handle va, Vertex_handle vb)
