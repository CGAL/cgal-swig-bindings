#ifndef CGAL_SWIG_POLYHEDRON_3_EXAMPLE_MODIFIER_H
#define CGAL_SWIG_POLYHEDRON_3_EXAMPLE_MODIFIER_H

#include <CGAL/config.h>
#include <CGAL/Modifier_base.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

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

#endif //CGAL_SWIG_POLYHEDRON_3_EXAMPLE_MODIFIER_H
