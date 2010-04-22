#ifndef CGAL_SWIG_POLYHEDRON_3_ITERATORS
#define CGAL_SWIG_POLYHEDRON_3_ITERATORS

#include "../Common/Input_iterator.h"
#include "polyhedron_3_handles.h"

DECLARE_ITERATOR_CLASS(Halfedge_iterator,CGAL_Halfedge_handle<T>)
DECLARE_ITERATOR_CLASS(Edge_iterator,CGAL_Halfedge_handle<T>)
DECLARE_ITERATOR_CLASS(Vertex_iterator,CGAL_Vertex_handle<T>)
DECLARE_ITERATOR_CLASS(Facet_iterator,CGAL_Facet_handle<T>)
DECLARE_ITERATOR_CLASS(Point_iterator,Point_3)

#endif// CGAL_SWIG_POLYHEDRON_3_ITERATORS
