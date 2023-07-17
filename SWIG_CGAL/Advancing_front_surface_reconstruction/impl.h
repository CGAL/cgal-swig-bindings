// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_ADVANCING_FRONT_SURFACE_RECONSTRUCTION_IMPL_H
#define SWIG_CGAL_ADVANCING_FRONT_SURFACE_RECONSTRUCTION_IMPL_H

#include <CGAL/Advancing_front_surface_reconstruction.h>
#include <CGAL/boost/graph/Euler_operations.h>
#include <boost/iterator/transform_iterator.hpp>
#include <CGAL/property_map.h>

#include <utility>

template <class Kernel>
struct Auto_count
{
  mutable int i = 0;

  std::pair<typename Kernel::Point_3,int>
  operator()(const typename Kernel::Point_3& p) const {
    return { p, i++ };
  }
};


template <class OutputIterator, class Surface_reconstruction>
OutputIterator
afsr_write_indices(OutputIterator out, const Surface_reconstruction& sr)
{ 
  typedef typename Surface_reconstruction::Triangulation_3 Triangulation_3;
  typedef typename Surface_reconstruction::Finite_facets_iterator Finite_facets_iterator;
  typedef typename Surface_reconstruction::Cell_handle Cell_handle;
  Triangulation_3& T = sr.triangulation_3();

 
  for(Finite_facets_iterator f_it = T.finite_facets_begin(); 
      f_it != T.finite_facets_end(); 
      f_it++)
  {
    Cell_handle n, c = (*f_it).first;
    int ni, ci = (*f_it).second;
    n = c->neighbor(ci);
    ni = n->index(c);
    int i1, i2 ,i3;

    if (c->is_selected_facet(ci))
    {
      i1 = (ci+1) & 3;
      i2 = (ci+2) & 3;
      i3 = (ci+3) & 3;
      *out++ = c->vertex(i1)->id();
      *out++ = c->vertex(i2)->id();
      *out++ = c->vertex(i3)->id();
    }

     if (n->is_selected_facet(ni))
    {
      i1 = (ni+1) & 3;
      i2 = (ni+2) & 3;
      i3 = (ni+3) & 3;

      *out++ = n->vertex(i1)->id();
      *out++ = n->vertex(i2)->id();
      *out++ = n->vertex(i3)->id();
    }
  }
  return out;
}

template <class TriangleMesh,
          class VertexPointMap =  typename boost::property_map< TriangleMesh, CGAL::vertex_point_t>::type >
struct Construct_face_graph
{
  typedef boost::graph_traits<TriangleMesh> GT;
  typedef typename GT::vertex_descriptor vertex_descriptor;
  typedef typename GT::vertex_iterator vertex_iterator;
  typedef CGAL::Property_map_to_unary_function<VertexPointMap> Unary_function;
  typedef boost::transform_iterator< Unary_function,
                                     vertex_iterator > Point_iterator;
  
  TriangleMesh& tm;
  VertexPointMap vpm;
  std::vector<vertex_descriptor> tm_vertices;

  template < typename PointIterator>
  void init(PointIterator b,
            PointIterator e)

  {
    for(; b!=e; ++b)
    {
      tm_vertices.push_back( add_vertex(tm) );
      put(vpm, tm_vertices.back(), *b);
    }
  }

  template < typename PointIterator>
  Construct_face_graph( TriangleMesh& tm,
                        PointIterator b,
                        PointIterator e,
                        VertexPointMap vpm)
    : tm(tm)
    , vpm(vpm)
  {
    init(b,e);
  }

  template < typename PointIterator>
  Construct_face_graph( TriangleMesh& tm_,
                        PointIterator b,
                        PointIterator e)
    : tm(tm_)
    , vpm(get(CGAL::vertex_point, tm_))
  {
    init(b,e);
  }

  Construct_face_graph& operator=(const CGAL::cpp11::array<std::size_t,3>& f)
  {
    CGAL::Euler::add_face(
      CGAL::make_array(tm_vertices[f[0]], tm_vertices[f[1]], tm_vertices[f[2]]),
      tm
    );
    return *this;
  }

  Construct_face_graph&
  operator*() { return *this; }
  Construct_face_graph&
  operator++(int) { return *this; }
  
  Point_iterator points_begin()
  {
    return boost::make_transform_iterator(vertices(tm).first, Unary_function(vpm));
  }

  Point_iterator points_end()
  {
    return boost::make_transform_iterator(vertices(tm).second, Unary_function(vpm));
  }  
};

template <class Kernel, class PointIterator, class IntOutputIterator>
void afsr_reconstruction(PointIterator point_begin, PointIterator point_end,
                         IntOutputIterator out,
                         double radius_ratio_bound, double beta)
{
  typedef CGAL::Advancing_front_surface_reconstruction<> Surface_reconstruction;
  typedef typename Surface_reconstruction::Triangulation_3 Triangulation_3;

  #ifdef AFSR_VERBOSE
  std::cerr << "Compute Delaunay Tetrahedrization " << std::endl;
  CGAL::Timer t1;
  t1.start();
  #endif

  Triangulation_3 dt( boost::make_transform_iterator(point_begin, Auto_count<Kernel>()),
                      boost::make_transform_iterator(point_end, Auto_count<Kernel>() )  );

  #ifdef AFSR_VERBOSE
  t1.stop();
  std::cerr << "   Inserted " << dt.number_of_vertices() << " points, "
            <<  dt.number_of_cells() << " cells computed in "
            << t1.time() << " sec." << std::endl;

  t1.reset();
  t1.start();
  #endif

  Surface_reconstruction sr(dt);
  sr.run(radius_ratio_bound, beta);

  #ifdef AFSR_VERBOSE
  t1.stop();
  std::cerr << "Reconstruction takes " << t1.time() << " sec.\n";
  std::cerr << "   "  << sr.number_of_outliers() << " outliers.\n";
  std::cerr << "   Reconstructed surface: " << sr.number_of_facets() <<
    " facets, " << sr.number_of_vertices() << " vertices.\n";
  std::cerr << "   "  << sr.number_of_border_edges() <<
    " border edges.\n";
  std::cerr << "   number of connected components <= "
            << (std::max)(1, sr.number_of_connected_components()-1)
            << std::endl;
  #endif

  afsr_write_indices(out, sr);
}

template <class Kernel, class PointIterator, class Polyhedron>
void afsr_reconstruction_poly(PointIterator point_begin, PointIterator point_end, 
                              Polyhedron& out,
                              double radius_ratio_bound, double beta)
{
  Construct_face_graph<Polyhedron> cfg(out, point_begin, point_end);
  CGAL::advancing_front_surface_reconstruction(cfg.points_begin(), cfg.points_end(), cfg, radius_ratio_bound, beta);
}


#endif //SWIG_CGAL_ADVANCING_FRONT_SURFACE_RECONSTRUCTION_IMPL_H
