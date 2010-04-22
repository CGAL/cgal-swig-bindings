#ifndef CGAL_SWIG_POLYHEDRON_3_ITERATORS
#define CGAL_SWIG_POLYHEDRON_3_ITERATORS

#include "../Common/Input_iterator.h"
#include "polyhedron_3_handles.h"
#include "../Kernel/Point_3.h"
#include "../Kernel/Plane_3.h"

DECLARE_ITERATOR_CLASS(Halfedge_iterator,CGAL_Halfedge_handle<T>)
DECLARE_ITERATOR_CLASS(Edge_iterator,CGAL_Halfedge_handle<T>)
DECLARE_ITERATOR_CLASS(Vertex_iterator,CGAL_Vertex_handle<T>)
DECLARE_ITERATOR_CLASS(Facet_iterator,CGAL_Facet_handle<T>)
DECLARE_ITERATOR_CLASS(Point_iterator,Point_3)
DECLARE_ITERATOR_CLASS(Plane_iterator,Plane_3)


DECLARE_CIRCULATOR_CLASS(Halfedge_around_vertex_circulator,CGAL_Halfedge_handle<T>)
DECLARE_CIRCULATOR_CLASS(Halfedge_around_facet_circulator,CGAL_Halfedge_handle<T>)

#endif// CGAL_SWIG_POLYHEDRON_3_ITERATORS
