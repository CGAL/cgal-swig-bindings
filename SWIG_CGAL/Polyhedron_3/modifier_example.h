#ifndef CGAL_SWIG_POLYHEDRON_3_EXAMPLE_MODIFIER_H
#define CGAL_SWIG_POLYHEDRON_3_EXAMPLE_MODIFIER_H

#include <CGAL/config.h>
#include <CGAL/Modifier_base.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <SWIG_CGAL/Kernel/Point_3.h>

template <class HDS>
class Build_triangle : public CGAL::Modifier_base<HDS>{
public:
    Build_triangle() {}
    void operator()( HDS& hds) {
        // Postcondition: `hds' is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
        B.begin_surface( 3, 1, 6);
        typedef typename HDS::Vertex   Vertex;
        typedef typename Vertex::Point Point;
        B.add_vertex( Point( 0, 0, 0));
        B.add_vertex( Point( 1, 0, 0));
        B.add_vertex( Point( 0, 1, 0));
        B.begin_facet();
        B.add_vertex_to_facet( 0);
        B.add_vertex_to_facet( 1);
        B.add_vertex_to_facet( 2);
        B.end_facet();
        B.end_surface();
    }
};

template <class HDS>
class Build_square : public CGAL::Modifier_base<HDS>{
public:
    Build_square() {}
    void operator()( HDS& hds) {
        // Postcondition: `hds' is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
        B.begin_surface( 3, 1, 6);
        typedef typename HDS::Vertex   Vertex;
        typedef typename Vertex::Point Point;
        B.add_vertex( Point( 0, 0, 0));
        B.add_vertex( Point( 1, 0, 0));
        B.add_vertex( Point( 0, 1, 0));
        B.add_vertex( Point( 0, 0, 1));
        B.begin_facet();
        B.add_vertex_to_facet( 0);
        B.add_vertex_to_facet( 1);
        B.add_vertex_to_facet( 2);
        B.add_vertex_to_facet( 3);
        B.end_facet();
        B.end_surface();
    }
};

#include <SWIG_CGAL/Common/Macros.h>
#ifdef SWIGPYTHON
#include <SWIG_CGAL/Python/Input_iterator_wrapper.h>
#endif
#ifdef SWIGJAVA
#include <SWIG_CGAL/Java/Input_iterator_wrapper.h>
#endif

#include <SWIG_CGAL/Common/triple.h>

typedef CGAL_SWIG::Triple<int,int,int> Integer_triple;
typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range;
typedef std::pair<Input_iterator_wrapper<Integer_triple,Integer_triple>,Input_iterator_wrapper<Integer_triple,Integer_triple> > Triple_integer_range;

template <class HDS>
class Build_triangular_facets_from_point_range : public CGAL::Modifier_base<HDS>{
  typedef std::list<Point_3::cpp_base> Point_container;
  typedef std::list<Integer_triple> Triple_container;
  Point_container points;
  Triple_container triples;
  
public:
    Build_triangular_facets_from_point_range(){}
    
    std::back_insert_iterator< Point_container >   point_writer() {return std::back_inserter(points);}
    std::back_insert_iterator< Triple_container >  integer_triple_writer() {return std::back_inserter(triples);}
      
      
    void operator()(HDS& hds) {
        // Postcondition: `hds' is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
      
        B.begin_surface(points.size(),triples.size());
        typedef typename HDS::Vertex   Vertex;
        typedef typename Vertex::Point Point;
        for (Point_container::const_iterator it=points.begin();it!=points.end();++it)
          B.add_vertex(*it);
        
        for (Triple_container::const_iterator it=triples.begin();it!=triples.end();++it)
        {
          B.begin_facet();
          B.add_vertex_to_facet(it->first);
          B.add_vertex_to_facet(it->second);
          B.add_vertex_to_facet(it->third);
          B.end_facet();
        }
        
        B.end_surface();
    }
};

#endif //CGAL_SWIG_POLYHEDRON_3_EXAMPLE_MODIFIER_H
