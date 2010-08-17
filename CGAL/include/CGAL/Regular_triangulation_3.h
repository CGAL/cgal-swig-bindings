// Copyright (c) 1999-2004  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/trunk/Triangulation_3/include/CGAL/Regular_triangulation_3.h $
// $Id: Regular_triangulation_3.h 57364 2010-07-07 11:26:48Z stayeb $
//
//
// Author(s)     : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//                 Sylvain Pion
//                 Christophe Delage <Christophe.Delage@sophia.inria.fr>

#ifndef CGAL_REGULAR_TRIANGULATION_3_H
#define CGAL_REGULAR_TRIANGULATION_3_H

#include <CGAL/basic.h>

#include <set>

#include <CGAL/Triangulation_3.h>
#include <CGAL/Regular_triangulation_cell_base_3.h>

#include <boost/bind.hpp>

#if defined(BOOST_MSVC)
#  pragma warning(push)
#  pragma warning(disable:4355) // complaint about using 'this' to
#endif                          // initialize a member

namespace CGAL {

template < class Gt, class Tds_ = Default >
class Regular_triangulation_3
  : public Triangulation_3<Gt,
              typename Default::Get<Tds_, Triangulation_data_structure_3 <
                                             Triangulation_vertex_base_3<Gt>,
                                             Regular_triangulation_cell_base_3<Gt> > >::type>
{
  typedef Regular_triangulation_3<Gt, Tds_>      Self;

  typedef typename Default::Get<Tds_, Triangulation_data_structure_3 <
                                           Triangulation_vertex_base_3<Gt>,
                                           Regular_triangulation_cell_base_3<Gt> > >::type Tds;

  typedef Triangulation_3<Gt,Tds>               Tr_Base;

public:

  typedef Tds                                   Triangulation_data_structure;
  typedef Gt                                    Geom_traits;

  typedef typename Tr_Base::Vertex_handle       Vertex_handle;
  typedef typename Tr_Base::Cell_handle         Cell_handle;
  typedef typename Tr_Base::Vertex              Vertex;
  typedef typename Tr_Base::Cell                Cell;
  typedef typename Tr_Base::Facet               Facet;
  typedef typename Tr_Base::Edge                Edge;

  typedef typename Tr_Base::size_type           size_type;
  typedef typename Tr_Base::Locate_type         Locate_type;
  typedef typename Tr_Base::Cell_iterator       Cell_iterator;
  typedef typename Tr_Base::Facet_iterator      Facet_iterator;
  typedef typename Tr_Base::Edge_iterator       Edge_iterator;
  typedef typename Tr_Base::Facet_circulator    Facet_circulator;

  typedef typename Tr_Base::Finite_vertices_iterator Finite_vertices_iterator;
  typedef typename Tr_Base::Finite_cells_iterator    Finite_cells_iterator;
  typedef typename Tr_Base::Finite_facets_iterator   Finite_facets_iterator;
  typedef typename Tr_Base::Finite_edges_iterator    Finite_edges_iterator;
  typedef typename Tr_Base::All_cells_iterator       All_cells_iterator;

  typedef typename Gt::Weighted_point_3            Weighted_point;
  typedef typename Gt::Bare_point                  Bare_point;
  typedef typename Gt::Segment_3                   Segment;
  typedef typename Gt::Triangle_3                  Triangle;
  typedef typename Gt::Tetrahedron_3               Tetrahedron;

  // types for dual:
  typedef typename Gt::Line_3        Line;
  typedef typename Gt::Ray_3         Ray;
  typedef typename Gt::Plane_3       Plane;
  typedef typename Gt::Object_3      Object;

  //Tag to distinguish Delaunay from Regular triangulations
  typedef Tag_true   Weighted_tag;

  using Tr_Base::cw;
  using Tr_Base::ccw;
#ifndef CGAL_CFG_USING_BASE_MEMBER_BUG_2
  using Tr_Base::geom_traits;
#endif
  using Tr_Base::number_of_vertices;
  using Tr_Base::dimension;
  using Tr_Base::finite_facets_begin;
  using Tr_Base::finite_facets_end;
  using Tr_Base::finite_vertices_begin;
  using Tr_Base::finite_vertices_end;
  using Tr_Base::finite_cells_begin;
  using Tr_Base::finite_cells_end;
  using Tr_Base::finite_edges_begin;
  using Tr_Base::finite_edges_end;
  using Tr_Base::tds;
  using Tr_Base::infinite_vertex;
  using Tr_Base::next_around_edge;
  using Tr_Base::vertex_triple_index;
  using Tr_Base::mirror_vertex;
  using Tr_Base::mirror_index;
  using Tr_Base::orientation;
  using Tr_Base::coplanar_orientation;
  using Tr_Base::adjacent_vertices;
  using Tr_Base::construct_segment;
  using Tr_Base::incident_facets;
  using Tr_Base::insert_in_conflict;
  using Tr_Base::is_infinite;
  using Tr_Base::is_valid_finite;
  using Tr_Base::locate;
  using Tr_Base::side_of_segment;
  using Tr_Base::side_of_edge;
  using Tr_Base::find_conflicts;
  using Tr_Base::is_valid;

  Regular_triangulation_3(const Gt & gt = Gt())
    : Tr_Base(gt), hidden_point_visitor(this)
  {}

  Regular_triangulation_3(const Regular_triangulation_3 & rt)
    : Tr_Base(rt), hidden_point_visitor(this)
  {
      CGAL_triangulation_postcondition( is_valid() );
  }

  //insertion
  template < typename InputIterator >
  Regular_triangulation_3(InputIterator first, InputIterator last,
                          const Gt & gt = Gt())
      : Tr_Base(gt), hidden_point_visitor(this)
  {
      insert(first, last);
  }

  template < class InputIterator >
  std::ptrdiff_t
  insert(InputIterator first, InputIterator last)
  {
    size_type n = number_of_vertices();

    std::vector<Weighted_point> points(first, last);
    spatial_sort (points.begin(), points.end(), geom_traits());

    Cell_handle hint;
    for (typename std::vector<Weighted_point>::const_iterator p = points.begin(),
		    end = points.end(); p != end; ++p)
    {
        Locate_type lt;
        Cell_handle c;
        int li, lj;
        c = locate (*p, lt, li, lj, hint);

        Vertex_handle v = insert (*p, lt, c, li, lj);

        hint = v == Vertex_handle() ? c : v->cell();
    }
    return number_of_vertices() - n;
  }

  Vertex_handle insert(const Weighted_point & p, Vertex_handle hint)
  {
    return insert(p, hint == Vertex_handle() ? this->infinite_cell() : hint->cell());
  }

  Vertex_handle insert(const Weighted_point & p,
	               Cell_handle start = Cell_handle());

  Vertex_handle insert(const Weighted_point & p, Locate_type lt,
	               Cell_handle c, int li, int);

  template <class OutputIteratorBoundaryFacets,
            class OutputIteratorCells,
            class OutputIteratorInternalFacets>
  Triple<OutputIteratorBoundaryFacets,
         OutputIteratorCells,
         OutputIteratorInternalFacets>
  find_conflicts(const Weighted_point &p, Cell_handle c,
	         OutputIteratorBoundaryFacets bfit,
                 OutputIteratorCells cit,
		 OutputIteratorInternalFacets ifit) const
  {
      CGAL_triangulation_precondition(dimension() >= 2);

      std::vector<Cell_handle> cells;
      cells.reserve(32);
      std::vector<Facet> facets;
      facets.reserve(64);

      if (dimension() == 2) {
          Conflict_tester_2 tester(p, this);
          if (! tester (c)) return make_triple (bfit, cit, ifit);
	  ifit = Tr_Base::find_conflicts
	    (c, tester,
	     make_triple(std::back_inserter(facets),
			 std::back_inserter(cells),
			 ifit)).third;
      }
      else {
          Conflict_tester_3 tester(p, this);
          if (! tester (c)) return make_triple (bfit, cit, ifit);
	  ifit = Tr_Base::find_conflicts
	    (c, tester,
	     make_triple(std::back_inserter(facets),
			 std::back_inserter(cells),
			 ifit)).third;
      }

      // Reset the conflict flag on the boundary.
      for(typename std::vector<Facet>::iterator fit=facets.begin();
          fit != facets.end(); ++fit) {
        fit->first->neighbor(fit->second)->tds_data().clear();
	*bfit++ = *fit;
      }

      // Reset the conflict flag in the conflict cells.
      for(typename std::vector<Cell_handle>::iterator ccit=cells.begin();
        ccit != cells.end(); ++ccit) {
        (*ccit)->tds_data().clear();
	*cit++ = *ccit;
      }
      return make_triple(bfit, cit, ifit);
  }

  template <class OutputIteratorBoundaryFacets, class OutputIteratorCells>
  std::pair<OutputIteratorBoundaryFacets, OutputIteratorCells>
  find_conflicts(const Weighted_point &p, Cell_handle c,
	         OutputIteratorBoundaryFacets bfit,
                 OutputIteratorCells cit) const
  {
      Triple<OutputIteratorBoundaryFacets,
             OutputIteratorCells,
	     Emptyset_iterator> t = find_conflicts(p, c, bfit, cit,
		                                   Emptyset_iterator());
      return std::make_pair(t.first, t.second);
  }

  // Returns the vertices on the boundary of the conflict hole.
  template <class OutputIterator>
  OutputIterator
  vertices_in_conflict(const Weighted_point&p, Cell_handle c,
		       OutputIterator res) const
  {
      CGAL_triangulation_precondition(dimension() >= 2);

      // Get the facets on the boundary of the hole.
      std::vector<Facet> facets;
      find_conflicts(p, c, std::back_inserter(facets),
	             Emptyset_iterator(), Emptyset_iterator());

      // Then extract uniquely the vertices.
      std::set<Vertex_handle> vertices;
      if (dimension() == 3) {
          for (typename std::vector<Facet>::const_iterator i = facets.begin();
	       i != facets.end(); ++i) {
	      vertices.insert(i->first->vertex((i->second+1)&3));
	      vertices.insert(i->first->vertex((i->second+2)&3));
	      vertices.insert(i->first->vertex((i->second+3)&3));
          }
      } else {
          for (typename std::vector<Facet>::const_iterator i = facets.begin();
	       i != facets.end(); ++i) {
	      vertices.insert(i->first->vertex(cw(i->second)));
	      vertices.insert(i->first->vertex(ccw(i->second)));
          }
      }

      return std::copy(vertices.begin(), vertices.end(), res);
  }

  void remove (Vertex_handle v);

  template < typename InputIterator >
  size_type remove(InputIterator first, InputIterator beyond)
  {
    size_type n = number_of_vertices();
    while (first != beyond) {
      remove (*first);
      ++first;
    }
    return n - number_of_vertices();
  }

  // DISPLACEMENT
  Vertex_handle move_point(Vertex_handle v, const Weighted_point & p);

  // Displacement works only for Regular triangulation
  // without hidden points at any time
  Vertex_handle move_if_no_collision(Vertex_handle v, const Weighted_point & p);
  Vertex_handle move(Vertex_handle v, const Weighted_point & p);

protected:

  Oriented_side
  side_of_oriented_power_sphere(const Weighted_point &p0,
                                const Weighted_point &p1,
                                const Weighted_point &p2,
                                const Weighted_point &p3,
                                const Weighted_point &p,
                                bool perturb = false) const;

  Oriented_side
  side_of_oriented_power_circle(const Weighted_point &p0,
                                const Weighted_point &p1,
                                const Weighted_point &p2,
                                const Weighted_point &p,
                                bool perturb = false) const;

  Bounded_side
  side_of_bounded_power_circle(const Weighted_point &p0,
                               const Weighted_point &p1,
                               const Weighted_point &p2,
                               const Weighted_point &p,
                               bool perturb = false) const;

  Bounded_side
  side_of_bounded_power_segment(const Weighted_point &p0,
                                const Weighted_point &p1,
                                const Weighted_point &p,
                                bool perturb = false) const;


public:

  // Queries
  Bounded_side
  side_of_power_sphere(Cell_handle c, const Weighted_point &p,
                       bool perturb = false) const;

  Bounded_side
  side_of_power_circle(const Facet & f, const Weighted_point & p,
                       bool /* perturb */ = false) const
  {
      return side_of_power_circle(f.first, f.second, p);
  }

  Bounded_side
  side_of_power_circle(Cell_handle c, int i, const Weighted_point &p,
                       bool perturb = false) const;

  Bounded_side
  side_of_power_segment(Cell_handle c, const Weighted_point &p,
                        bool perturb = false) const;

  Vertex_handle
  nearest_power_vertex_in_cell(const Bare_point& p,
			       Cell_handle c)  const;

  Vertex_handle
  nearest_power_vertex(const Bare_point& p, Cell_handle c =
		       Cell_handle()) const;

  bool is_Gabriel(Cell_handle c, int i) const;
  bool is_Gabriel(Cell_handle c, int i, int j) const;
  bool is_Gabriel(const Facet& f)const ;
  bool is_Gabriel(const Edge& e) const;
  bool is_Gabriel(Vertex_handle v) const;


  // Dual functions
  Bare_point dual(Cell_handle c) const;

  Object dual(const Facet & f) const
    { return dual( f.first, f.second ); }

  Object dual(Cell_handle c, int i) const;

  template < class Stream> 		
  Stream& draw_dual(Stream & os)
    {
      for (Finite_facets_iterator fit = finite_facets_begin(),
                                  end = finite_facets_end();
           fit != end; ++fit) {
	Object o = dual(*fit);
	if      (const Segment    *s = object_cast<Segment>(&o))    os << *s;
	else if (const Ray        *r = object_cast<Ray>(&o))        os << *r;
	else if (const Bare_point *p = object_cast<Bare_point>(&o)) os << *p;
      }
      return os;
    }

  bool is_valid(bool verbose = false, int level = 0) const;

protected:
  bool
  less_power_distance(const Bare_point &p,
		      const Weighted_point &q,
		      const Weighted_point &r)  const
  {
    return
      geom_traits().compare_power_distance_3_object()(p, q, r) == SMALLER;
  }

  Bare_point
  construct_weighted_circumcenter(const Weighted_point &p,
				  const Weighted_point &q,
				  const Weighted_point &r,
				  const Weighted_point &s) const
  {
     return geom_traits().construct_weighted_circumcenter_3_object()(p,q,r,s);
  }

  Bare_point
  construct_weighted_circumcenter(const Weighted_point &p,
				  const Weighted_point &q,
				  const Weighted_point &r) const
  {
     return geom_traits().construct_weighted_circumcenter_3_object()(p,q,r);
  }

  Line
  construct_perpendicular_line(const Plane &pl, const Bare_point &p) const
  {
      return geom_traits().construct_perpendicular_line_3_object()(pl, p);
  }

  Plane
  construct_plane(const Bare_point &p, const Bare_point &q, const Bare_point &r) const
  {
      return geom_traits().construct_plane_3_object()(p, q, r);
  }

  Ray
  construct_ray(const Bare_point &p, const Line &l) const
  {
      return geom_traits().construct_ray_3_object()(p, l);
  }

  Object
  construct_object(const Bare_point &p) const
  {
      return geom_traits().construct_object_3_object()(p);
  }

  Object
  construct_object(const Segment &s) const
  {
      return geom_traits().construct_object_3_object()(s);
  }

  Object
  construct_object(const Ray &r) const
  {
      return geom_traits().construct_object_3_object()(r);
  }

  Vertex_handle
  nearest_power_vertex(const Bare_point &p,
		       Vertex_handle v,
		       Vertex_handle w) const
  {
      // In case of equality, v is returned.
      CGAL_triangulation_precondition(v != w);
      if (is_infinite(v))	  return w;
      if (is_infinite(w))	  return v;
      return less_power_distance(p, w->point(), v->point()) ? w : v;
  }

  Oriented_side
  power_test(const Weighted_point &p, const Weighted_point &q) const
  {
      CGAL_triangulation_precondition(this->equal(p, q));
      return geom_traits().power_test_3_object()(p, q);
  }

  Oriented_side
  power_test(const Weighted_point &p, const Weighted_point &q,
	     const Weighted_point &r) const
  {
      CGAL_triangulation_precondition(this->collinear(p, q, r));
      return geom_traits().power_test_3_object()(p, q, r);
  }

  Oriented_side
  power_test(const Weighted_point &p, const Weighted_point &q,
	     const Weighted_point &r, const Weighted_point &s) const
  {
      CGAL_triangulation_precondition(this->coplanar(p, q, r, s));
      return geom_traits().power_test_3_object()(p, q, r, s);
  }

  Oriented_side
  power_test(const Weighted_point &p, const Weighted_point &q,
	     const Weighted_point &r, const Weighted_point &s,
	     const Weighted_point &t) const
  {
      return geom_traits().power_test_3_object()(p, q, r, s, t);
  }

  bool in_conflict_3(const Weighted_point &p, const Cell_handle c) const
  {
      return side_of_power_sphere(c, p, true) == ON_BOUNDED_SIDE;
  }

  bool in_conflict_2(const Weighted_point &p, const Cell_handle c, int i) const
  {
      return side_of_power_circle(c, i, p, true) == ON_BOUNDED_SIDE;
  }

  bool in_conflict_1(const Weighted_point &p, const Cell_handle c) const
  {
      return side_of_power_segment(c, p, true) == ON_BOUNDED_SIDE;
  }

  bool in_conflict_0(const Weighted_point &p, const Cell_handle c) const
  {
      return power_test(c->vertex(0)->point(), p) == ON_POSITIVE_SIDE;
  }

  bool in_conflict(const Weighted_point &p, const Cell_handle c) const
  {
      switch (dimension()) {
          case 0: return in_conflict_0(p, c);
          case 1: return in_conflict_1(p, c);
          case 2: return in_conflict_2(p, c, 3);
          case 3: return in_conflict_3(p, c);
      }
      return true;
  }

  class Conflict_tester_3
  {
    const Weighted_point &p;
    const Self *t;

  public:

    Conflict_tester_3(const Weighted_point &pt, const Self *tr)
      : p(pt), t(tr) {}

    bool operator()(const Cell_handle c) const {
      return t->in_conflict_3(p, c);
    }

    bool test_initial_cell(const Cell_handle c) const {
      return operator()(c);
    }
    Oriented_side compare_weight(const Weighted_point &wp1,
				 const Weighted_point &wp2) const
    {
      return t->power_test (wp1, wp2);
    }
  };

  class Conflict_tester_2
  {
      const Weighted_point &p;
      const Self *t;
  public:

    Conflict_tester_2(const Weighted_point &pt, const Self *tr)
      : p(pt), t(tr) {}

    bool operator()(const Cell_handle c) const
    {
      return t->in_conflict_2(p, c, 3);
    }
    bool test_initial_cell(const Cell_handle c) const {
      return operator()(c);
    }
    Oriented_side compare_weight(const Weighted_point &wp1,
				 const Weighted_point &wp2) const
    {
      return t->power_test (wp1, wp2);
    }
  };

  class Conflict_tester_1
  {
      const Weighted_point &p;
      const Self *t;

  public:

    Conflict_tester_1(const Weighted_point &pt, const Self *tr)
      : p(pt), t(tr) {}

    bool operator()(const Cell_handle c) const
    {
      return t->in_conflict_1(p, c);
    }
    bool test_initial_cell(const Cell_handle c) const {
      return operator()(c);
    }
    Oriented_side compare_weight(const Weighted_point &wp1,
				 const Weighted_point &wp2) const
    {
      return t->power_test (wp1, wp2);
    }
  };

  class Conflict_tester_0
  {
      const Weighted_point &p;
      const Self *t;

  public:

    Conflict_tester_0(const Weighted_point &pt, const Self *tr)
      : p(pt), t(tr) {}

    bool operator()(const Cell_handle c) const
    {
      return t->in_conflict_0(p, c);
    }
    bool test_initial_cell(const Cell_handle c) const {
      return operator()(c);
    }
    int compare_weight(const Weighted_point &wp1,
		       const Weighted_point &wp2) const
    {
      return t->power_test (wp1, wp2);
    }
  };

  class Hidden_point_visitor
  {
    Self *t;
    mutable std::vector<Vertex_handle> vertices;
    mutable std::vector<Weighted_point> hidden_points;

  public:

    Hidden_point_visitor(Self *tr) : t(tr) {}

    template <class InputIterator>
    void process_cells_in_conflict(InputIterator start, InputIterator end) const
    {
      int dim = t->dimension();
      while (start != end) {
	std::copy((*start)->hidden_points_begin(),
		  (*start)->hidden_points_end(),
		  std::back_inserter(hidden_points));
	
	for (int i=0; i<=dim; i++) {
	  Vertex_handle v = (*start)->vertex(i);
	  if (v->cell() != Cell_handle()) {
	    vertices.push_back(v);
	    v->set_cell(Cell_handle());
	  }
	}
	start ++;
      }
    }
    void reinsert_vertices(Vertex_handle v) {
      Cell_handle hc = v->cell();
	for (typename std::vector<Vertex_handle>::iterator
	     vi = vertices.begin(); vi != vertices.end(); ++vi) {
	if ((*vi)->cell() != Cell_handle()) continue;
	hc = t->locate ((*vi)->point(), hc);
	hide_point(hc, (*vi)->point());
	t->tds().delete_vertex(*vi);
      }
      vertices.clear();
      for (typename std::vector<Weighted_point>::iterator
	     hp = hidden_points.begin(); hp != hidden_points.end(); ++hp) {
	hc = t->locate (*hp, hc);
	hide_point (hc, *hp);
      }
      hidden_points.clear();
    }
    Vertex_handle replace_vertex(Cell_handle c, int index,
				 const Weighted_point &p) {
      Vertex_handle v = c->vertex(index);
      hide_point(c, v->point());
      v->set_point(p);
      return v;
    }
    void hide_point(Cell_handle c, const Weighted_point &p) {
      c->hide_point(p);
    }
  };

  template < class RegularTriangulation_3 >
  class Vertex_remover;

  template < class RegularTriangulation_3 >
  class Vertex_inserter;

  Hidden_point_visitor hidden_point_visitor;
};


template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
nearest_power_vertex_in_cell(const Bare_point& p,
			     Cell_handle c) const
// Returns the finite vertex of the cell c with smaller
// power distance  to p.
{
    CGAL_triangulation_precondition(dimension() >= 1);
    Vertex_handle nearest = nearest_power_vertex(p,
						 c->vertex(0),
						 c->vertex(1));
    if (dimension() >= 2) {
	nearest = nearest_power_vertex(p, nearest, c->vertex(2));
        if (dimension() == 3)
	    nearest = nearest_power_vertex(p, nearest, c->vertex(3));
    }
    return nearest;
}


template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
nearest_power_vertex(const Bare_point& p, Cell_handle start) const
{
    if (number_of_vertices() == 0)
      return Vertex_handle();

    // Use a brute-force algorithm if dimension < 3.
    if (dimension() < 3) {
	Finite_vertices_iterator vit = finite_vertices_begin();
	Vertex_handle res = vit;
	++vit;
	for (Finite_vertices_iterator end = finite_vertices_end(); vit != end; ++vit)
	    res = nearest_power_vertex(p, res, vit);
	return res;
    }

    Locate_type lt;
    int li, lj;
    // I put the cast here temporarily
    // until we solve the traits class pb of regular triangulation
    Cell_handle c = locate(static_cast<Weighted_point>(p), lt, li, lj, start);

    // - start with the closest vertex from the located cell.
    // - repeatedly take the nearest of its incident vertices if any
    // - if not, we're done.
    Vertex_handle nearest = nearest_power_vertex_in_cell(p, c);
    std::vector<Vertex_handle> vs;
    vs.reserve(32);
    while (true) {
	Vertex_handle tmp = nearest;
        adjacent_vertices(nearest, std::back_inserter(vs));
        for (typename std::vector<Vertex_handle>::const_iterator
		vsit = vs.begin(); vsit != vs.end(); ++vsit)
	    tmp = nearest_power_vertex(p, tmp, *vsit);
	if (tmp == nearest)
	    break;
	vs.clear();
	nearest = tmp;
    }
    return nearest;
}

template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Bare_point
Regular_triangulation_3<Gt,Tds>::
dual(Cell_handle c) const
{
  CGAL_triangulation_precondition(dimension()==3);
  CGAL_triangulation_precondition( ! is_infinite(c) );
  return construct_weighted_circumcenter( c->vertex(0)->point(),
					  c->vertex(1)->point(),
					  c->vertex(2)->point(),
					  c->vertex(3)->point() );
}

template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Object
Regular_triangulation_3<Gt,Tds>::
dual(Cell_handle c, int i) const
{
  CGAL_triangulation_precondition(dimension()>=2);
  CGAL_triangulation_precondition( ! is_infinite(c,i) );

  if ( dimension() == 2 ) {
    CGAL_triangulation_precondition( i == 3 );
    return construct_object(
       construct_weighted_circumcenter(c->vertex(0)->point(),
				       c->vertex(1)->point(),
				       c->vertex(2)->point()) );
  }

  // dimension() == 3
  Cell_handle n = c->neighbor(i);
  if ( ! is_infinite(c) && ! is_infinite(n) )
    return construct_object(construct_segment( dual(c), dual(n) ));

  // either n or c is infinite
  int in;
  if ( is_infinite(c) )
    in = n->index(c);
  else {
    n = c;
    in = i;
  }
  // n now denotes a finite cell, either c or c->neighbor(i)
  int ind[3] = {(in+1)&3,(in+2)&3,(in+3)&3};
  if ( (in&1) == 1 )
      std::swap(ind[0], ind[1]);
  const Weighted_point& p = n->vertex(ind[0])->point();
  const Weighted_point& q = n->vertex(ind[1])->point();
  const Weighted_point& r = n->vertex(ind[2])->point();

  Line l =
    construct_perpendicular_line( construct_plane(p,q,r),
				  construct_weighted_circumcenter(p,q,r) );
  return construct_object(construct_ray( dual(n), l));
}


template < class Gt, class Tds >
Oriented_side
Regular_triangulation_3<Gt,Tds>::
side_of_oriented_power_sphere(const Weighted_point &p0,
                              const Weighted_point &p1,
                              const Weighted_point &p2,
                              const Weighted_point &p3,
                              const Weighted_point &p, bool perturb) const
{
    CGAL_triangulation_precondition( orientation(p0, p1, p2, p3) == POSITIVE );

    using namespace boost;

    Oriented_side os = power_test(p0, p1, p2, p3, p);

    if (os != ON_ORIENTED_BOUNDARY || !perturb)
        return os;

    // We are now in a degenerate case => we do a symbolic perturbation.

    // We sort the points lexicographically.
    const Weighted_point * points[5] = {&p0, &p1, &p2, &p3, &p};
    std::sort(points, points + 5,
              boost::bind(geom_traits().compare_xyz_3_object(),
                          boost::bind(Dereference<Weighted_point>(), _1),
                          boost::bind(Dereference<Weighted_point>(), _2)) == SMALLER);

    // We successively look whether the leading monomial, then 2nd monomial
    // of the determinant has non null coefficient.
    for (int i=4; i>1; --i) {
        if (points[i] == &p)
            return ON_NEGATIVE_SIDE; // since p0 p1 p2 p3 are non coplanar
                                     // and positively oriented
	Orientation o;
        if (points[i] == &p3 && (o = orientation(p0,p1,p2,p)) != COPLANAR )
            return o;
        if (points[i] == &p2 && (o = orientation(p0,p1,p,p3)) != COPLANAR )
            return o;
        if (points[i] == &p1 && (o = orientation(p0,p,p2,p3)) != COPLANAR )
            return o;
        if (points[i] == &p0 && (o = orientation(p,p1,p2,p3)) != COPLANAR )
            return o;
    }

    CGAL_triangulation_assertion(false);
    return ON_NEGATIVE_SIDE;
}


template < class Gt, class Tds >
Bounded_side
Regular_triangulation_3<Gt,Tds>::
side_of_power_sphere(Cell_handle c, const Weighted_point &p,
                     bool perturb) const
{
  CGAL_triangulation_precondition( dimension() == 3 );
  int i3;
  if ( ! c->has_vertex( infinite_vertex(), i3 ) ) {
    return Bounded_side( side_of_oriented_power_sphere(c->vertex(0)->point(),
                                                       c->vertex(1)->point(),
                                                       c->vertex(2)->point(),
                                                       c->vertex(3)->point(),
                                                       p, perturb) );
  }
  // else infinite cell :
  int i0,i1,i2;
  if ( (i3%2) == 1 ) {
    i0 = (i3+1)&3;
    i1 = (i3+2)&3;
    i2 = (i3+3)&3;
  }
  else {
    i0 = (i3+2)&3;
    i1 = (i3+1)&3;
    i2 = (i3+3)&3;
  }

  // general case
  Orientation o = orientation(c->vertex(i0)->point(),
		              c->vertex(i1)->point(),
		              c->vertex(i2)->point(), p);
  if (o != ZERO)
    return Bounded_side(o);

  // else p coplanar with i0,i1,i2
  return side_of_bounded_power_circle(c->vertex(i0)->point(),
                                      c->vertex(i1)->point(),
                                      c->vertex(i2)->point(),
                                      p, perturb);
}


template < class Gt, class Tds >
Bounded_side
Regular_triangulation_3<Gt,Tds>::
side_of_bounded_power_circle(const Weighted_point &p0,
                             const Weighted_point &p1,
                             const Weighted_point &p2,
                             const Weighted_point &p, bool perturb) const
{
    CGAL_triangulation_precondition(coplanar_orientation(p0, p1, p2) != 0);
    if (coplanar_orientation(p0, p1, p2) == POSITIVE)
        return Bounded_side (side_of_oriented_power_circle(p0, p1, p2, p, perturb));
    // Wrong because the low level power test already does a coplanar orientation
    // test.
    // return Bounded_side (- side_of_oriented_power_circle (p0, p2, p1, p,
    // perturb));
    return Bounded_side (side_of_oriented_power_circle(p0, p2, p1, p, perturb));
}


template < class Gt, class Tds >
Oriented_side
Regular_triangulation_3<Gt,Tds>::
side_of_oriented_power_circle(const Weighted_point &p0,
                              const Weighted_point &p1,
                              const Weighted_point &p2,
                              const Weighted_point &p, bool perturb) const
{
    CGAL_triangulation_precondition( coplanar_orientation(p0, p1, p2) == POSITIVE );

    using namespace boost;

    Oriented_side os = power_test(p0, p1, p2, p);

    if (os != ON_ORIENTED_BOUNDARY || !perturb)
        return os;

    // We are now in a degenerate case => we do a symbolic perturbation.

    // We sort the points lexicographically.
    const Weighted_point * points[4] = {&p0, &p1, &p2, &p};
    std::sort(points, points + 4,
              boost::bind(geom_traits().compare_xyz_3_object(),
                          boost::bind(Dereference<Weighted_point>(), _1),
                          boost::bind(Dereference<Weighted_point>(), _2)) == SMALLER);

    // We successively look whether the leading monomial, then 2nd monomial
    // of the determinant has non null coefficient.
    // 2 iterations are enough (cf paper)
    for (int i=3; i>1; --i) {
        if (points[i] == &p)
            return ON_NEGATIVE_SIDE; // since p0 p1 p2 are non collinear
                                     // and positively oriented
	Orientation o;
        if (points[i] == &p2 && (o = coplanar_orientation(p0,p1,p)) != COPLANAR )
            return o;
        if (points[i] == &p1 && (o = coplanar_orientation(p0,p,p2)) != COPLANAR )
            return o;
        if (points[i] == &p0 && (o = coplanar_orientation(p,p1,p2)) != COPLANAR )
            return o;
    }

    CGAL_triangulation_assertion(false);
    return ON_NEGATIVE_SIDE;
}


template < class Gt, class Tds >
Bounded_side
Regular_triangulation_3<Gt,Tds>::
side_of_power_circle(Cell_handle c, int i, const Weighted_point &p,
		     bool perturb) const
{
  CGAL_triangulation_precondition( dimension() >= 2 );
  int i3 = 5;
  if ( dimension() == 2 ) {
    CGAL_triangulation_precondition( i == 3 );
    // the triangulation is supposed to be valid, ie the facet
    // with vertices 0 1 2 in this order is positively oriented
    if ( ! c->has_vertex( infinite_vertex(), i3 ) )
      return Bounded_side( side_of_oriented_power_circle(c->vertex(0)->point(),
                                                         c->vertex(1)->point(),
                                                         c->vertex(2)->point(),
                                                         p, perturb) );
    // else infinite facet
    // v1, v2 finite vertices of the facet such that v1,v2,infinite
    // is positively oriented
    Vertex_handle v1 = c->vertex( ccw(i3) ),
                  v2 = c->vertex( cw(i3) );
    CGAL_triangulation_assertion(coplanar_orientation(v1->point(), v2->point(),
                                 mirror_vertex(c, i3)->point()) == NEGATIVE);
    Orientation o = coplanar_orientation(v1->point(), v2->point(), p);
    if ( o != ZERO )
	return Bounded_side( o );
    // case when p collinear with v1v2
    return side_of_bounded_power_segment(v1->point(),
                                         v2->point(),
                                         p, perturb);
  }// dim 2

  // else dimension == 3
  CGAL_triangulation_precondition( (i >= 0) && (i < 4) );
  if ( ( ! c->has_vertex(infinite_vertex(),i3) ) || ( i3 != i ) ) {
    // finite facet
    // initialization of i0 i1 i2, vertices of the facet positively
    // oriented (if the triangulation is valid)
    int i0 = (i>0) ? 0 : 1;
    int i1 = (i>1) ? 1 : 2;
    int i2 = (i>2) ? 2 : 3;
    CGAL_triangulation_precondition(this->coplanar(c->vertex(i0)->point(),
						   c->vertex(i1)->point(),
						   c->vertex(i2)->point(), p));
    return side_of_bounded_power_circle(c->vertex(i0)->point(),
                                        c->vertex(i1)->point(),
                                        c->vertex(i2)->point(),
                                        p, perturb);
  }
  //else infinite facet
  // v1, v2 finite vertices of the facet such that v1,v2,infinite
  // is positively oriented
  Vertex_handle v1 = c->vertex( next_around_edge(i3,i) ),
                v2 = c->vertex( next_around_edge(i,i3) );
  Orientation o = (Orientation)
                  (coplanar_orientation( v1->point(), v2->point(),
					c->vertex(i)->point()) *
                  coplanar_orientation( v1->point(), v2->point(), p));
  // then the code is duplicated from 2d case
  if ( o != ZERO )
      return Bounded_side( -o );
  // because p is in f iff
  // it is not on the same side of v1v2 as c->vertex(i)
  // case when p collinear with v1v2 :
  return side_of_bounded_power_segment(v1->point(),
                                       v2->point(),
                                       p, perturb);
}

template < class Gt, class Tds >
Bounded_side
Regular_triangulation_3<Gt,Tds>::
side_of_bounded_power_segment(const Weighted_point &p0,
                              const Weighted_point &p1,
                              const Weighted_point &p, bool perturb) const
{
    Oriented_side os = power_test(p0, p1, p);

    if (os != ON_ORIENTED_BOUNDARY || !perturb)
        return Bounded_side(os);

    // We are now in a degenerate case => we do a symbolic perturbation.

    switch (this->collinear_position(p0, p, p1)) {
        case Tr_Base::BEFORE: case Tr_Base::AFTER:
            return ON_UNBOUNDED_SIDE;
        case Tr_Base::MIDDLE:
            return ON_BOUNDED_SIDE;
        default:
            ;
    }

    CGAL_triangulation_assertion(false);
    return ON_UNBOUNDED_SIDE;
}

template < class Gt, class Tds >
Bounded_side
Regular_triangulation_3<Gt,Tds>::
side_of_power_segment(Cell_handle c, const Weighted_point &p,
                      bool perturb) const
{
  CGAL_triangulation_precondition( dimension() == 1 );
  if ( ! is_infinite(c,0,1) )
    return side_of_bounded_power_segment(c->vertex(0)->point(),
                                         c->vertex(1)->point(),
                                         p, perturb);
  Locate_type lt; int i;
  Bounded_side soe = side_of_edge( p, c, lt, i );
  if (soe != ON_BOUNDARY)
    return soe;
  // Either we compare weights, or we use the finite neighboring edge
  Cell_handle finite_neighbor = c->neighbor(c->index(infinite_vertex()));
  CGAL_triangulation_assertion(!is_infinite(finite_neighbor,0,1));
  return side_of_bounded_power_segment(finite_neighbor->vertex(0)->point(),
                                       finite_neighbor->vertex(1)->point(),
                                       p, perturb);
}

template < class Gt, class Tds >
bool
Regular_triangulation_3<Gt,Tds>::
is_Gabriel(const Facet& f) const
{
  return is_Gabriel(f.first, f.second);
}

template < class Gt, class Tds >
bool
Regular_triangulation_3<Gt,Tds>::
is_Gabriel(Cell_handle c, int i) const
{
  CGAL_triangulation_precondition(dimension() == 3 && !is_infinite(c,i));
  typename Geom_traits::Side_of_bounded_orthogonal_sphere_3
    side_of_bounded_orthogonal_sphere =
    geom_traits().side_of_bounded_orthogonal_sphere_3_object();

  if ((!is_infinite(c->vertex(i))) &&
      side_of_bounded_orthogonal_sphere(
	 c->vertex(vertex_triple_index(i,0))->point(),
	 c->vertex(vertex_triple_index(i,1))->point(),
	 c->vertex(vertex_triple_index(i,2))->point(),
	 c->vertex(i)->point()) == ON_BOUNDED_SIDE ) return false;

  Cell_handle neighbor = c->neighbor(i);
  int in = neighbor->index(c);

  if ((!is_infinite(neighbor->vertex(in))) &&
      side_of_bounded_orthogonal_sphere(
	 c->vertex(vertex_triple_index(i,0))->point(),
	 c->vertex(vertex_triple_index(i,1))->point(),
	 c->vertex(vertex_triple_index(i,2))->point(),	
	 neighbor->vertex(in)->point()) == ON_BOUNDED_SIDE ) return false;

  return true;
}


template < class Gt, class Tds >
bool
Regular_triangulation_3<Gt,Tds>::
is_Gabriel(const Edge& e) const
{
  return is_Gabriel(e.first, e.second, e.third);
}

template < class Gt, class Tds >
bool
Regular_triangulation_3<Gt,Tds>::
is_Gabriel(Cell_handle c, int i, int j) const
{
  CGAL_triangulation_precondition(dimension() == 3 && !is_infinite(c,i,j));
  typename Geom_traits::Side_of_bounded_orthogonal_sphere_3
    side_of_bounded_orthogonal_sphere =
    geom_traits().side_of_bounded_orthogonal_sphere_3_object();

  Facet_circulator fcirc = incident_facets(c,i,j),
                   fdone(fcirc);
  Vertex_handle v1 = c->vertex(i);
  Vertex_handle v2 = c->vertex(j);
  do {
      // test whether the vertex of cc opposite to *fcirc
      // is inside the sphere defined by the edge e = (s, i,j)
      Cell_handle cc = (*fcirc).first;
      int ii = (*fcirc).second;
      if (!is_infinite(cc->vertex(ii)) &&
	  side_of_bounded_orthogonal_sphere( v1->point(),
					 v2->point(),
					 cc->vertex(ii)->point())
	  == ON_BOUNDED_SIDE ) return false;
  } while(++fcirc != fdone);
  return true;
}

template < class Gt, class Tds >
bool
Regular_triangulation_3<Gt,Tds>::
is_Gabriel(Vertex_handle v) const
{
  return nearest_power_vertex( v->point().point(), v->cell()) == v;
}

template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
insert(const Weighted_point & p, Cell_handle start)
{
    Locate_type lt;
    int li, lj;
    Cell_handle c = locate(p, lt, li, lj, start);
    return insert(p, lt, c, li, lj);
}

template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
insert(const Weighted_point & p, Locate_type lt, Cell_handle c, int li, int lj)
{
  switch (dimension()) {
  case 3:
    {
      Conflict_tester_3 tester (p, this);
      return insert_in_conflict(p, lt,c,li,lj, tester, hidden_point_visitor);
    }
  case 2:
    {
      Conflict_tester_2 tester (p, this);
      return insert_in_conflict(p, lt,c,li,lj, tester, hidden_point_visitor);
    }
  case 1:
    {
      Conflict_tester_1 tester (p, this);
      return insert_in_conflict(p, lt,c,li,lj, tester, hidden_point_visitor);
    }
  }

  Conflict_tester_0 tester (p, this);
  return insert_in_conflict(p, lt,c,li,lj, tester, hidden_point_visitor);
}

template <class Gt, class Tds >
template <class RegularTriangulation_3>
class Regular_triangulation_3<Gt, Tds>::Vertex_remover {
  typedef RegularTriangulation_3 Regular;
  typedef typename Gt::Point_3 Point;
public:
  typedef typename std::vector<Point>::iterator
      Hidden_points_iterator;

  Vertex_remover(Regular &tmp_) : tmp(tmp_) {}

  Regular &tmp;

  void add_hidden_points(Cell_handle ch) {
    std::copy (ch->hidden_points_begin(), ch->hidden_points_end(),
                std::back_inserter(hidden));
  }

  Hidden_points_iterator hidden_points_begin() {
    return hidden.begin();
  }
  Hidden_points_iterator hidden_points_end() {
    return hidden.end();
  }

  Bounded_side side_of_bounded_circle(const Point &p, const Point &q,
    const Point &r, const Point &s, bool perturb = false) const {
    return tmp.side_of_bounded_power_circle(p,q,r,s,perturb);
  }

private:
  // The removal of v may un-hide some points,
  // Space functions output them.
  std::vector<Point> hidden;
};

// The displacement method works only
// on regular triangulation without hidden points at any time
// the vertex inserter is used only
// for the purpose of displacements
template <class Gt, class Tds >
template <class RegularTriangulation_3>
class Regular_triangulation_3<Gt, Tds>::Vertex_inserter {
  typedef RegularTriangulation_3 Regular;
public:
  typedef Nullptr_t Hidden_points_iterator;

  Vertex_inserter(Regular &tmp_) : tmp(tmp_) {}

  Regular &tmp;

  void add_hidden_points(Cell_handle) {}
  Hidden_points_iterator hidden_points_begin() { return NULL; }
  Hidden_points_iterator hidden_points_end() { return NULL; }

  Vertex_handle insert(const Weighted_point& p,
		       Locate_type lt, Cell_handle c, int li, int lj) {
    return tmp.insert(p, lt, c, li, lj);
  }

  Vertex_handle insert(const Weighted_point& p, Cell_handle c) {
    return tmp.insert(p, c);
  }

  Vertex_handle insert(const Weighted_point& p) {
    return tmp.insert(p);
  }
};

template < class Gt, class Tds >
void
Regular_triangulation_3<Gt,Tds>::
remove(Vertex_handle v)
{
    Cell_handle c;
    if (dimension() > 0)
        c = v->cell()->neighbor(v->cell()->index(v));

    Self tmp;
    Vertex_remover<Self> remover(tmp);
    Tr_Base::remove(v,remover);

    // Re-insert the points that v was hiding.
    for (typename Vertex_remover<Self>::Hidden_points_iterator
        hi = remover.hidden_points_begin();
        hi != remover.hidden_points_end(); ++hi) {
      Vertex_handle hv = insert (*hi, c);
      if (hv != Vertex_handle()) c = hv->cell();
    }
    CGAL_triangulation_expensive_postcondition (is_valid());
}

// Again, verbatim copy from Delaunay.
template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
move_point(Vertex_handle v, const Weighted_point & p)
{
    CGAL_triangulation_precondition(! is_infinite(v));
    CGAL_triangulation_expensive_precondition(is_vertex(v));

    // Dummy implementation for a start.

    // Remember an incident vertex to restart
    // the point location after the removal.
    Cell_handle c = v->cell();
    Vertex_handle old_neighbor = c->vertex(c->index(v) == 0 ? 1 : 0);
    CGAL_triangulation_assertion(old_neighbor != v);

    remove(v);

    if (dimension() <= 0)
        return insert(p);
    return insert(p, old_neighbor->cell());
}

// Displacement works only for Regular triangulation
// without hidden points at any time
template < class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
move_if_no_collision(Vertex_handle v, const Weighted_point &p)
{
  Self tmp;
  Vertex_remover<Self> remover (tmp);
  Vertex_inserter<Self> inserter (*this);
  Vertex_handle res = Tr_Base::move_if_no_collision(v,p,remover,inserter);

  CGAL_triangulation_expensive_postcondition(is_valid());	
  return res;
}

template <class Gt, class Tds >
typename Regular_triangulation_3<Gt,Tds>::Vertex_handle
Regular_triangulation_3<Gt,Tds>::
move(Vertex_handle v, const Weighted_point &p) {
  CGAL_triangulation_precondition(!is_infinite(v));
  if(v->point() == p) return v;
  Self tmp;
  Vertex_remover<Self> remover (tmp);
  Vertex_inserter<Self> inserter (*this);
  return Tr_Base::move(v,p,remover,inserter);
}

template < class Gt, class Tds >
bool
Regular_triangulation_3<Gt,Tds>::
is_valid(bool verbose, int level) const
{
  if ( ! Tr_Base::is_valid(verbose,level) ) {
    if (verbose)
	std::cerr << "invalid base triangulation" << std::endl;
    CGAL_triangulation_assertion(false);
    return false;
  }

  switch ( dimension() ) {
  case 3:
    {
      for(Finite_cells_iterator it = finite_cells_begin(), end = finite_cells_end(); it != end; ++it) {
	is_valid_finite(it, verbose, level);
	for(int i=0; i<4; i++) {
	  if ( !is_infinite
	       (it->neighbor(i)->vertex(it->neighbor(i)->index(it))) ) {
	    if ( side_of_power_sphere
		 (it,
		  it->neighbor(i)->vertex(it->neighbor(i)->index(it))->point())
		  == ON_BOUNDED_SIDE ) {
	      if (verbose)
		std::cerr << "non-empty sphere " << std::endl;
	      CGAL_triangulation_assertion(false);
	      return false;
	    }
	  }
	}
      }
      break;
    }
  case 2:
    {
      for(Finite_facets_iterator it = finite_facets_begin(), end = finite_facets_end(); it!= end; ++it) {
	is_valid_finite((*it).first, verbose, level);
	for(int i=0; i<3; i++) {
	  if( !is_infinite
	      ((*it).first->neighbor(i)->vertex( (((*it).first)->neighbor(i))
						 ->index((*it).first))) ) {
	    if ( side_of_power_circle
		 ( (*it).first, 3,
		   (*it).first->neighbor(i)->
		   vertex( (((*it).first)->neighbor(i))
			   ->index((*it).first) )->point() )
		 == ON_BOUNDED_SIDE ) {
	      if (verbose)
		std::cerr << "non-empty circle " << std::endl;
	      CGAL_triangulation_assertion(false);
	      return false;
	    }
	  }
	}
      }
      break;
    }
  case 1:
    {
      for(Finite_edges_iterator it = finite_edges_begin(), end = finite_edges_end(); it != end; ++it) {
	is_valid_finite((*it).first, verbose, level);
	for(int i=0; i<2; i++) {
	  if( !is_infinite
	      ((*it).first->neighbor(i)->vertex( (((*it).first)->neighbor(i))
						 ->index((*it).first))) ) {
	    if ( side_of_power_segment
		 ( (*it).first,
		   (*it).first->neighbor(i)->
		   vertex( (((*it).first)->neighbor(i))
			   ->index((*it).first) )->point() )
		 == ON_BOUNDED_SIDE ) {
	      if (verbose)
		std::cerr << "non-empty edge " << std::endl;
	      CGAL_triangulation_assertion(false);
	      return false;
	    }
	  }
	}
      }
      break;
    }
  }
  if (verbose)
      std::cerr << "valid Regular triangulation" << std::endl;
  return true;
}

} //namespace CGAL

#if defined(BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif // CGAL_REGULAR_TRIANGULATION_3_H
