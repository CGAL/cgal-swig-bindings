#ifndef SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H
#define SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_PLUS_2_H


template <  class Triangulation,
            class Vertex_handle,
            class Face_handle,
            class Base_triangulation_wrapper
          >
class Constrained_triangulation_plus_2_wrapper: public Base_triangulation_wrapper
{
  typedef Base_triangulation_wrapper Base;
public:
  Constrained_triangulation_plus_2_wrapper():Base(){}
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
//   Constraint_iterator   ctp.constraints_begin ()
//   Constraint_iterator   ctp.constraints_end ()
//   Subconstraint_iterator   ctp.subconstraints_begin ()
//   Subconstraint_iterator   ctp.subconstraints_end ()
//   int   ctp.number_of_enclosing_constraints ( Vertex_handle va, Vertex_handle vb)
//   Context   ctp.context ( Vertex_handle va, Vertex_handle vb)
//   Context_iterator   ctp.contexts_begin ( Vertex_handle va, Vertex_handle vb)
//   Context_iterator   ctp.contexts_end ( Vertex_handle va, Vertex_handle vb)
//   Vertices_in_constraint_iterator   ctp.vertices_in_constraint_begin ( Vertex_handle va, Vertex_handle vb)
//   Vertices_in_constraint_iterator   ctp.vertices_in_constraint_end ( Vertex_handle va, Vertex_handle vb)
