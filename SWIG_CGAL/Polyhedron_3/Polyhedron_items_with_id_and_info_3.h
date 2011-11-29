// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POLYHEDRON_3_POLYHEDRON_ITEMS_WITH_ID_AND_INFO_3_H
#define SWIG_CGAL_POLYHEDRON_3_POLYHEDRON_ITEMS_WITH_ID_AND_INFO_3_H


#include <CGAL/HalfedgeDS_vertex_base.h>
#include <CGAL/HalfedgeDS_halfedge_base.h>
#include <CGAL/HalfedgeDS_face_base.h>

namespace CGAL{

template < class Refs, class P, class ID, class Info>
class HalfedgeDS_vertex_max_base_with_id_and_info : public HalfedgeDS_vertex_base< Refs, Tag_true, P>
{
public:
    typedef HalfedgeDS_vertex_base< Refs, Tag_true, P> Base ;
    typedef ID size_type ;
    typedef P Point ;
private:
    size_type mID ;
    Info info_;
public:
    HalfedgeDS_vertex_max_base_with_id_and_info() : mID ( size_type(-1) )  {}
    HalfedgeDS_vertex_max_base_with_id_and_info( Point const& p) : Base(p), mID ( size_type(-1) ) {}
    HalfedgeDS_vertex_max_base_with_id_and_info( Point const& p, size_type i ) : Base(p), mID(i) {}
    size_type&       id()       { return mID; }
    size_type const& id() const { return mID; }
    Info& info(){return info_;}
};


template < class Refs, class ID, class Info>
class HalfedgeDS_halfedge_max_base_with_id_and_info : public HalfedgeDS_halfedge_base< Refs, Tag_true, Tag_true, Tag_true >
{
public:
    typedef HalfedgeDS_halfedge_base< Refs, Tag_true, Tag_true, Tag_true> Base ;
    typedef typename Base::Base_base Base_base ;
    typedef ID size_type ;
private:
    size_type mID ;
    Info info_;
public:
    HalfedgeDS_halfedge_max_base_with_id_and_info( size_type i = size_type(-1) ) : mID(i) {}
    size_type&       id()       { return mID; }
    size_type const& id() const { return mID; }
    Info& info(){return info_;}
};

template < class Refs, class Pln, class ID, class Info>
class HalfedgeDS_face_max_base_with_id_and_info : public HalfedgeDS_face_base< Refs, Tag_true, Pln>
{
public:
    typedef HalfedgeDS_face_base< Refs, Tag_true, Pln> Base ;
    typedef ID size_type ;
private:
    size_type mID ;
    Info info_;
public:
    HalfedgeDS_face_max_base_with_id_and_info() : mID ( size_type(-1) ) {}
    HalfedgeDS_face_max_base_with_id_and_info( Pln const& p) : Base(p), mID ( size_type(-1) ) {}
    HalfedgeDS_face_max_base_with_id_and_info( Pln const& p, size_type i ) : Base(p), mID (i) {}
    size_type&       id()       { return mID; }
    size_type const& id() const { return mID; }
    Info& info(){return info_;}
};


template <class Info>
class Polyhedron_items_with_id_and_info_3 {
public:
    template < class Refs, class Traits>
    struct Vertex_wrapper {
        typedef typename Traits::Point_3 Point;
        typedef HalfedgeDS_vertex_max_base_with_id_and_info< Refs, Point, std::size_t,Info> Vertex;
    };
    template < class Refs, class Traits>
    struct Halfedge_wrapper {
        typedef HalfedgeDS_halfedge_max_base_with_id_and_info<Refs, std::size_t,Info> Halfedge;
    };
    template < class Refs, class Traits>
    struct Face_wrapper {
        typedef HalfedgeDS_face_max_base_with_id_and_info< Refs, Tag_false, std::size_t,Info>  Face;
    };
};


}//namespace CGAL

#endif //SWIG_CGAL_POLYHEDRON_3_POLYHEDRON_ITEMS_WITH_ID_AND_INFO_3_H

