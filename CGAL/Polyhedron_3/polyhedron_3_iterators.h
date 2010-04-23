#ifndef CGAL_SWIG_POLYHEDRON_3_ITERATORS
#define CGAL_SWIG_POLYHEDRON_3_ITERATORS

#include "../Common/Input_iterator.h"
#include "../Kernel/Point_3.h"
#include "../Kernel/Plane_3.h"

DECLARE_ITERATOR_CLASS(Halfedge_iterator)
DECLARE_ITERATOR_CLASS(Edge_iterator)
DECLARE_ITERATOR_CLASS(Vertex_iterator)
DECLARE_ITERATOR_CLASS(Facet_iterator)
DECLARE_ITERATOR_CLASS(Point_iterator)
DECLARE_ITERATOR_CLASS(Plane_iterator)


DECLARE_CIRCULATOR_CLASS(Halfedge_around_vertex_circulator)
DECLARE_CIRCULATOR_CLASS(Halfedge_around_facet_circulator)

#endif// CGAL_SWIG_POLYHEDRON_3_ITERATORS
