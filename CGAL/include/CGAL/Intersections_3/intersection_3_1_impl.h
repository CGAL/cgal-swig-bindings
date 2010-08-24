// Copyright (c) 1997-2004  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/trunk/Intersections_3/include/CGAL/Intersections_3/intersection_3_1_impl.h $
// $Id: intersection_3_1_impl.h 58250 2010-08-24 08:28:00Z sloriot $
// 
//
// Author(s)     : Geert-Jan Giezeman <geert@cs.uu.nl>


#include <CGAL/wmult.h>

namespace CGAL {

namespace internal {

template <class K>
Object
intersection(const typename K::Plane_3  &plane, 
	     const typename K::Line_3 &line, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Direction_3 Direction_3;
    typedef typename K::RT RT;

    const Point_3 &line_pt = line.point();
    const Direction_3 &line_dir = line.direction();

    RT num = plane.a()*line_pt.hx() + plane.b()*line_pt.hy()
           + plane.c()*line_pt.hz() + wmult_hw((K*)0, plane.d(), line_pt);
    RT den = plane.a()*line_dir.dx() + plane.b()*line_dir.dy()
           + plane.c()*line_dir.dz();
    if (den == 0) {
        if (num == 0) {
            // all line
            return make_object(line);
        } else {
            // no intersection
            return Object();
        }
    }
    return make_object(Point_3(
        den*line_pt.hx()-num*line_dir.dx(),
        den*line_pt.hy()-num*line_dir.dy(),
        den*line_pt.hz()-num*line_dir.dz(),
        wmult_hw((K*)0, den, line_pt)));
}

template <class K>
inline
Object
intersection(const typename K::Line_3 &line, 
	     const typename K::Plane_3  &plane, 
	     const K& k)
{
  return intersection(plane, line, k);
}

template <class K>
Object
intersection(const typename K::Plane_3 &plane1, 
	     const typename K::Plane_3 &plane2, 
	     const K&)
{
  typedef typename K::Point_3 Point_3;
  typedef typename K::Direction_3 Direction_3;
  typedef typename K::Line_3 Line_3;

    typedef typename K::RT RT;
    const RT &a = plane1.a();
    const RT &b = plane1.b();
    const RT &c = plane1.c();
    const RT &d = plane1.d();
    const RT &p = plane2.a();
    const RT &q = plane2.b();
    const RT &r = plane2.c();
    const RT &s = plane2.d();

    RT det = a*q-p*b;
    if (det != 0) {
        Point_3 is_pt = Point_3(b*s-d*q, p*d-a*s, 0, det);
        Direction_3 is_dir = Direction_3(b*r-c*q, p*c-a*r, det);
        return make_object(Line_3(is_pt, is_dir));
    }
    det = a*r-p*c;
    if (det != 0) {
        Point_3 is_pt = Point_3(c*s-d*r, 0, p*d-a*s, det);
        Direction_3 is_dir = Direction_3(c*q-b*r, det, p*b-a*q);
        return make_object(Line_3(is_pt, is_dir));
    }
    det = b*r-c*q;
    if (det != 0) {
        Point_3 is_pt = Point_3(0, c*s-d*r, d*q-b*s, det);
        Direction_3 is_dir = Direction_3(det, c*p-a*r, a*q-b*p);
        return make_object(Line_3(is_pt, is_dir));
    }
// degenerate case
    if (a!=0 || p!=0) {
        if (a*s == p*d)
            return make_object(plane1);
        else
            return Object();
    }
    if (b!=0 || q!=0) {
        if (b*s == q*d)
            return make_object(plane1);
        else
            return Object();
    }
    if (c!=0 || r!=0) {
        if (c*s == r*d)
            return make_object(plane1);
        else
            return Object();
    }
    return make_object(plane1);
}

template <class K>
Object
intersection(const typename K::Plane_3 &plane1,
	     const typename K::Plane_3 &plane2,
	     const typename K::Plane_3 &plane3,
	     const K& k)
{
    typedef typename K::Line_3       Line_3;
    typedef typename K::Plane_3      Plane_3;

    // Intersection between plane1 and plane2 can either be
    // a line, a plane, or empty.
    Object o12 = internal::intersection(plane1, plane2, k);

    if (const Line_3 *l = object_cast<Line_3>(&o12))
        return internal::intersection(plane3, *l, k);

    if (const Plane_3 *pl = object_cast<Plane_3>(&o12))
        return internal::intersection(plane3, *pl, k);

    return Object();
}


template <class K>
bool
do_intersect(const typename K::Plane_3 &plane, 
	     const typename K::Line_3 &line,
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Direction_3 Direction_3;
    typedef typename K::RT RT;
    const Point_3 &line_pt = line.point();
    const Direction_3 &line_dir = line.direction();

    RT den = plane.a()*line_dir.dx() + plane.b()*line_dir.dy()
           + plane.c()*line_dir.dz();
    if (den != 0)
        return true;
    RT num = plane.a()*line_pt.hx() + plane.b()*line_pt.hy()
           + plane.c()*line_pt.hz() + wmult_hw((K*)0, plane.d(), line_pt);
    if (num == 0) {
        // all line
        return true;
    } else {
        // no intersection
        return false;
    }
}

template <class K>
inline
bool
do_intersect(const typename K::Line_3 &line, 
	     const typename K::Plane_3 &plane, 
	     const K& k)
{
  return do_intersect(plane, line, k);
}

template <class K>
Object
intersection(const typename K::Line_3 &l1,
	     const typename K::Line_3 &l2,
	     const K&)
{
  typedef typename K::FT           FT;
  typedef typename K::Line_3       Line_3;
  typedef typename K::Point_3      Point_3;
  typedef typename K::Vector_3     Vector_3;

  if(K().has_on_3_object()(l1, l2.point())) {
    const Vector_3& v1 = l1.to_vector();
    const Vector_3& v2 = l2.to_vector();
    if((v1.x() * v2.y() == v1.y() * v2.x()) &&
       (v1.x() * v2.z() == v1.z() * v2.x()) &&
       (v1.y() * v2.z() == v1.z() * v2.y()))
      return make_object(l1);
  }
  
  if(K().are_parallel_3_object()(l1,l2)) return Object();
  const Point_3 &p1 = l1.point();
  const Point_3 &p3 = l2.point();
  const Vector_3 &v1 = l1.to_vector();
  const Vector_3 &v2 = l2.to_vector();
  const Point_3 p2 = p1 + v1;
  const Point_3 p4 = p2 + v2;
  if(!K().coplanar_3_object()(p1,p2,p3,p4)) return Object();
  const Vector_3 v3 = p3 - p1;
 const Vector_3 v3v2 = cross_product(v3,v2);
  const Vector_3 v1v2 = cross_product(v1,v2);
  const FT t = ((v3v2.x()*v1v2.x()) + (v3v2.y()*v1v2.y()) + (v3v2.z()*v1v2.z())) /
               (v1v2.squared_length());
  return make_object(p1 + (v1 * t));
}

template <class K>
bool
do_intersect(const typename K::Line_3 &l1,
	     const typename K::Line_3 &l2,
	     const K&)
{
  typedef typename K::FT           FT;
  typedef typename K::Line_3       Line_3;
  typedef typename K::Point_3      Point_3;
  typedef typename K::Vector_3     Vector_3;

  if(K().has_on_3_object()(l1, l2.point())) return true;
  if(K().are_parallel_3_object()(l1,l2)) return false;
  const Point_3 &p1 = l1.point();
  const Point_3 &p3 = l2.point();
  const Vector_3 &v1 = l1.to_vector();
  const Vector_3 &v2 = l2.to_vector();
  const Point_3 p2 = p1 + v1;
  const Point_3 p4 = p2 + v2;
  return K().coplanar_3_object()(p1,p2,p3,p4);
}

template <class K>
Object
intersection(const typename K::Segment_3 &s1,
	     const typename K::Segment_3 &s2,
	     const K& k)
{
  CGAL_precondition(! s1.is_degenerate () && ! s2.is_degenerate () );
  Object res = intersection(s1.supporting_line(),s2.supporting_line());
  const typename K::Point_3* p=object_cast<typename K::Point_3> (&res);
  if (p!=NULL){
    typename K::Collinear_are_ordered_along_line_3 cln_order=k.collinear_are_ordered_along_line_3_object();
    if ( cln_order(s1[0],*p,s1[1]) && cln_order(s2[0],*p,s2[1]) )
      return res;
  }
  else{
    const typename K::Line_3* l=object_cast<typename K::Line_3> (&res);
    if (l!=NULL){
      const typename K::Point_3& p=s1[0],q=s1[1],r=s2[0],s=s2[1];
      typename K::Collinear_are_ordered_along_line_3 cln_order=k.collinear_are_ordered_along_line_3_object();
      
      if ( cln_order(p,r,q) ){
        if ( cln_order(p,s,q) )
          return make_object(s2);
        if ( cln_order(r,p,s) )
          return r!=p ? make_object( typename K::Segment_3(r,p) ) : make_object(p);
        else
          return r!=q ? make_object( typename K::Segment_3(r,q) ) : make_object(q);
      }

      if ( cln_order(p,s,q) ){
        if ( cln_order(r,p,s) )
          return s!=p ? make_object( typename K::Segment_3(s,p) ) : make_object(p);
        else
          return s!=q ? make_object( typename K::Segment_3(s,q) ) : make_object(q);
      }
      
      if ( cln_order(r,p,s) )
        return make_object(s1);
    }
  }
  return Object();
}

template <class K>
inline
bool
do_intersect(const typename K::Segment_3  &s1,
             const typename K::Segment_3  &s2,
             const K & k)
{
  CGAL_precondition(! s1.is_degenerate () && ! s2.is_degenerate () );
  bool b=do_intersect(s1.supporting_line(),s2.supporting_line(),k);
  if (b)
  {
    //supporting_line intersects: points are coplanar
    typename K::Coplanar_orientation_3 cpl_orient=k.coplanar_orientation_3_object();
    ::CGAL::Orientation or1 =  cpl_orient(s1[0],s1[1],s2[0]);
    ::CGAL::Orientation or2 =  cpl_orient(s1[0],s1[1],s2[1]);
    
    if ( or1 == COLLINEAR && or2 ==COLLINEAR )
    {
      //segments are collinear
      typename K::Collinear_are_ordered_along_line_3 cln_order=k.collinear_are_ordered_along_line_3_object();
      return cln_order(s1[0],s2[0],s1[1]) || 
             cln_order(s1[0],s2[1],s1[1]) ||
             cln_order(s2[0],s1[0],s2[1]) ;
    }
    
    if ( or1 != or2 ){
      or1=cpl_orient(s2[0],s2[1],s1[0]);
      return (or1 == COLLINEAR || or1 != cpl_orient(s2[0],s2[1],s1[1]));
    }
  }
  return false;
}

template <class K>
Object
intersection(const typename K::Plane_3 &p,
             const typename K::Sphere_3 &s,
             const K&)
{
  typedef typename K::Sphere_3 Sphere_3;
  typedef typename K::Circle_3 Circle_3;
  typedef typename K::Plane_3 Plane_3;
  typedef typename K::Point_3 Point_3;
  typedef typename K::FT FT;
  const FT d2 = CGAL::square(p.a()*s.center().x() + 
                             p.b()*s.center().y() + 
                             p.c()*s.center().z() + p.d()) /
      (square(p.a()) + square(p.b()) + square(p.c()));
  const FT cmp = d2 - s.squared_radius();
  if(CGAL_NTS is_zero(cmp)) { // tangent
    return make_object(p.projection(s.center()));
  } else if(CGAL_NTS is_negative(cmp)) { // intersect
    Point_3 center = p.projection(s.center());
    return make_object(Circle_3(center,s.squared_radius() - d2,p));
  } // do not intersect
  return Object();
}

template <class K>
inline
bool
do_intersect(const typename K::Plane_3 &p,
             const typename K::Sphere_3 &s,
             const K&)
{
  typedef typename K::Sphere_3 Sphere_3;
  typedef typename K::Circle_3 Circle_3;
  typedef typename K::Plane_3 Plane_3;
  typedef typename K::Point_3 Point_3;
  typedef typename K::FT FT;
  const FT d2 = CGAL::square(p.a()*s.center().x() + 
                             p.b()*s.center().y() + 
                             p.c()*s.center().z() + p.d()) /
      (square(p.a()) + square(p.b()) + square(p.c()));
  return d2 <= s.squared_radius();
}

template <class K>
inline
bool
do_intersect(const typename K::Sphere_3 &s,
             const typename K::Plane_3 &p,
             const K& k)
{
  return do_intersect(p,s);
}


template <class K>
inline
Object
intersection(const typename K::Sphere_3 &s,
             const typename K::Plane_3 &p,
             const K& k)
{
  return intersection(p, s, k);
}

template <class K>
inline
Object
intersection(const typename K::Sphere_3 &s1,
             const typename K::Sphere_3 &s2,
             const K& k)
{
  typedef typename K::Plane_3 Plane_3;
  typedef typename K::Sphere_3 Sphere_3;
  if(s1.center() == s2.center()) {
    if(s1.squared_radius() == s2.squared_radius()) {
      if(is_zero(s1.squared_radius())) return make_object(s1.center());
      else return make_object(s1);
    } else return Object();  // cocentrics
  }
  Plane_3 p = K().construct_radical_plane_3_object()(s1,s2);
  return intersection(p, s1, k);
}

template <class K>
inline
bool
do_intersect(const typename K::Sphere_3 &s1,
             const typename K::Sphere_3 &s2,
             const K& k)
{
  typedef typename K::Plane_3 Plane_3;
  typedef typename K::Sphere_3 Sphere_3;
  if(s1.center() == s2.center()) {
    return s1.squared_radius() == s2.squared_radius();
  }
  Plane_3 p = K().construct_radical_plane_3_object()(s1,s2);
  return do_intersect(p, s1, k);
}

template <class K>
Object
intersection(const typename K::Plane_3 &plane, 
	     const typename K::Ray_3 &ray, 
	     const K& k)
{
    typedef typename K::Point_3 Point_3;
    const Object line_intersection =
            intersection(plane, ray.supporting_line(), k);
    if (const Point_3 *isp = object_cast<Point_3>(&line_intersection)) {
        if (ray.collinear_has_on(*isp))
            return line_intersection;
        else
            return Object();
    }
    if (line_intersection.is_empty())
        return line_intersection;
    return make_object(ray);
}


template <class K>
inline
Object
intersection(const typename K::Ray_3 &ray, 
	     const typename K::Plane_3 &plane, 
	     const K& k)
{
  return intersection(plane, ray, k);
}



template <class K>
bool
do_intersect(const typename K::Plane_3 &plane, 
	     const typename K::Ray_3 &ray, 
	     const K& k)
{
    typedef typename K::Point_3 Point_3;
    const Object line_intersection =
            intersection(plane, ray.supporting_line(), k);
    if (line_intersection.is_empty())
        return false;
    if (const Point_3 *isp = object_cast<Point_3>(&line_intersection))
        return ray.collinear_has_on(*isp);
    return true;
}


template <class K>
inline
bool
do_intersect(const typename K::Ray_3 &ray, 
	     const typename K::Plane_3 &plane, 
	     const K& k)
{
  return do_intersect(plane, ray, k);
}


template <class K>
Object
intersection(const typename K::Plane_3 &plane, 
	     const typename K::Segment_3 &seg, 
	     const K& k)
{
    typedef typename K::Point_3 Point_3;
    const Point_3 &source = seg.source();
    const Point_3 &target = seg.target();

    Oriented_side source_side = plane.oriented_side(source);
    Oriented_side target_side = plane.oriented_side(target);

    switch (source_side) {
    case ON_ORIENTED_BOUNDARY:
        if (target_side == ON_ORIENTED_BOUNDARY)
            return make_object(seg);
        else
            return make_object(source);
    case ON_POSITIVE_SIDE:
        switch (target_side) {
        case ON_ORIENTED_BOUNDARY:
            return make_object(target);
        case ON_POSITIVE_SIDE:
            return Object();
        case ON_NEGATIVE_SIDE:
          { 
            // intersection object should be a point, but rounding errors 
            // could lead to a line. In such case, return seg.
            Object obj = intersection(plane, seg.supporting_line(), k);
            if ( NULL == object_cast<typename K::Line_3>(&obj) )
              return obj;
            else
              return make_object(seg);
          }
        }
    case ON_NEGATIVE_SIDE:
        switch (target_side) {
        case ON_ORIENTED_BOUNDARY:
            return make_object(target);
        case ON_POSITIVE_SIDE:
          { 
            // intersection object should be a point, but rounding errors 
            // could lead to a line. In such case, return seg.
            Object obj = intersection(plane, seg.supporting_line(), k);
            if ( NULL == object_cast<typename K::Line_3>(&obj) )
              return obj;
            else 
              return make_object(seg);
          }
        case ON_NEGATIVE_SIDE:
            return Object();
        }
    }
    CGAL_kernel_assertion_msg(false, "Supposedly unreachable code.");
    return Object();
}


template <class K>
inline
Object
intersection(const typename K::Segment_3 &seg, 
	     const typename K::Plane_3 &plane, 
	     const K& k)
{
  return intersection(plane, seg, k);
}


template <class K>
bool
do_intersect(const typename K::Plane_3  &plane, 
	     const typename K::Segment_3 &seg, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    const Point_3 &source = seg.source();
    const Point_3 &target = seg.target();

    Oriented_side source_side = plane.oriented_side(source);
    Oriented_side target_side = plane.oriented_side(target);

    if ( source_side == target_side
       && target_side != ON_ORIENTED_BOUNDARY) {
        return false;
    }
    return true;
}


template <class K>
inline
bool
do_intersect(const typename K::Segment_3 &seg, 
	     const typename K::Plane_3  &plane, 
	     const K& k)
{
  return do_intersect(plane, seg, k);
}


template <class K>
Object
intersection(const typename K::Line_3 &line,
	     const Bbox_3 &box, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Direction_3 Direction_3;
    const Point_3 &linepoint = line.point();
    const Direction_3 &linedir = line.direction();
    return intersection_bl<K>(box,
        CGAL::to_double(linepoint.x()),
        CGAL::to_double(linepoint.y()),
        CGAL::to_double(linepoint.z()),
        CGAL::to_double(linedir.dx()),
        CGAL::to_double(linedir.dy()),
        CGAL::to_double(linedir.dz()),
        true, true
        );
}


template <class K>
inline
Object
intersection(const Bbox_3 &box, 
	     const typename K::Line_3 &line, 
	     const K& k)
{
  return intersection(line, box, k);
}


template <class K>
Object
intersection(const typename K::Ray_3 &ray,
	     const Bbox_3 &box, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Direction_3 Direction_3;
    const Point_3 &linepoint = ray.source();
    const Direction_3 &linedir = ray.direction();
    return intersection_bl<K>(box,
        CGAL::to_double(linepoint.x()),
        CGAL::to_double(linepoint.y()),
        CGAL::to_double(linepoint.z()),
        CGAL::to_double(linedir.dx()),
        CGAL::to_double(linedir.dy()),
        CGAL::to_double(linedir.dz()),
        false, true
        );
}


template <class K>
inline
Object
intersection(const Bbox_3 &box, 
	     const typename K::Ray_3 &ray, 
	     const K& k)
{
  return intersection(ray, box, k);
}



template <class K>
Object
intersection(const typename K::Segment_3 &seg, 
	     const Bbox_3 &box, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Vector_3 Vector_3;
    const Point_3 &linepoint = seg.source();
    const Vector_3 &diffvec = seg.target()-linepoint;
    return intersection_bl<K>(box,
        CGAL::to_double(linepoint.x()),
        CGAL::to_double(linepoint.y()),
        CGAL::to_double(linepoint.z()),
        CGAL::to_double(diffvec.x()),
        CGAL::to_double(diffvec.y()),
        CGAL::to_double(diffvec.z()),
        false, false
        );
}


template <class K>
inline
Object
intersection(const Bbox_3 &box, 
	     const typename K::Segment_3 &seg, 
	     const K& k)
{
  return intersection(seg, box, k);
}


template <class K>
Object
intersection(const typename K::Line_3 &line,
	     const typename K::Iso_cuboid_3 &box, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Vector_3 Vector_3;
    typedef typename K::Segment_3 Segment_3;
    typedef typename K::RT RT;
    typedef typename K::FT FT;
    bool all_values = true;
    FT _min = 0, _max = 0; // initialization to stop compiler warning
    Point_3 const & _ref_point=line.point();
    Vector_3 const & _dir=line.direction().vector();
    Point_3 const & _iso_min=(box.min)();
    Point_3 const & _iso_max=(box.max)();
    for (int i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == 0) {
            if (_ref_point.cartesian(i) < _iso_min.cartesian(i)) {
                return Object();
            }
            if (_ref_point.cartesian(i) > _iso_max.cartesian(i)) {
                return Object();
            }
        } else {
            FT newmin, newmax;
            if (_dir.homogeneous(i) > 0) {
                newmin = (_iso_min.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_iso_max.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            } else {
                newmin = (_iso_max.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_iso_min.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            }
            if (all_values) {
                _min = newmin;
                _max = newmax;
            } else {
                if (newmin > _min)
                    _min = newmin;
                if (newmax < _max)
                    _max = newmax;
                if (_max < _min) {
                    return Object();
                }
            }
            all_values = false;
        }
    }
    CGAL_kernel_assertion(!all_values);
    if (_max == _min) {
        return make_object(Point_3(_ref_point + _dir * _min ));
    }
    return make_object(
        Segment_3(_ref_point + _dir*_min, _ref_point + _dir*_max));
}


template <class K>
inline
Object
intersection(const typename K::Iso_cuboid_3 &box, 
	     const typename K::Line_3 &line, 
	     const K& k)
{
  return intersection(line, box, k);
}



template <class K>
Object
intersection(const typename K::Ray_3 &ray,
	     const typename K::Iso_cuboid_3 &box, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Vector_3 Vector_3;
    typedef typename K::Segment_3 Segment_3;
    typedef typename K::RT RT;
    typedef typename K::FT FT;
    bool all_values = true;
    FT _min = 0, _max = 0; // initialization to prevent compiler warning
    Point_3 const & _ref_point=ray.source();
    Vector_3 const & _dir=ray.direction().vector();
    Point_3 const & _iso_min=(box.min)();
    Point_3 const & _iso_max=(box.max)();

    for (int i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == 0) {
            if (_ref_point.cartesian(i) < _iso_min.cartesian(i)) {
                return Object();
            }
            if (_ref_point.cartesian(i) > _iso_max.cartesian(i)) {
                return Object();
            }
        } else {
            FT newmin, newmax;
            if (_dir.homogeneous(i) > 0) {
                newmin = (_iso_min.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_iso_max.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            } else {
                newmin = (_iso_max.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_iso_min.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            }
            if (all_values) {
                _max = newmax;
            } else {
                if (newmax < _max)
                    _max = newmax;
            }
            if (newmin > _min)
                 _min = newmin;
            if (_max < _min)
                return Object();
            all_values = false;
        }
    }
    CGAL_kernel_assertion(!all_values);
    if (_max == _min) {
        return make_object(Point_3(_ref_point + _dir * _min ));
    }
    return make_object(
        Segment_3(_ref_point + _dir*_min, _ref_point + _dir*_max));
}


template <class K>
inline
Object
intersection(const typename K::Iso_cuboid_3 &box, 
	     const typename K::Ray_3 &ray,
	     const K& k)
{
  return intersection(ray, box, k);
}


template <class K>
Object
intersection(const typename K::Segment_3 &seg,
	     const typename K::Iso_cuboid_3 &box, 
	     const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Vector_3 Vector_3;
    typedef typename K::Segment_3 Segment_3;
    typedef typename K::RT RT;
    typedef typename K::FT FT;
    FT _min = 0, _max;

    Point_3 const & _ref_point=seg.source();
    Vector_3 const & _dir=seg.direction().vector();
    Point_3 const & _iso_min=(box.min)();
    Point_3 const & _iso_max=(box.max)();
    int main_dir =
        (CGAL_NTS abs(_dir.x()) > CGAL_NTS abs(_dir.y()) )
            ? (CGAL_NTS abs(_dir.x()) > CGAL_NTS abs(_dir.z()) ? 0 : 2)
            : (CGAL_NTS abs(_dir.y()) > CGAL_NTS abs(_dir.z()) ? 1 : 2);
    _max = (seg.target().cartesian(main_dir)-_ref_point.cartesian(main_dir)) /
            _dir.cartesian(main_dir);

    for (int i=0; i< _ref_point.dimension(); i++) {
        if (_dir.homogeneous(i) == 0) {
            if (_ref_point.cartesian(i) < _iso_min.cartesian(i)) {
                return Object();
            }
            if (_ref_point.cartesian(i) > _iso_max.cartesian(i)) {
                return Object();
            }
        } else {
            FT newmin, newmax;
            if (_dir.homogeneous(i) > 0) {
                newmin = (_iso_min.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_iso_max.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            } else {
                newmin = (_iso_max.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
                newmax = (_iso_min.cartesian(i) - _ref_point.cartesian(i)) /
                    _dir.cartesian(i);
            }
            if (newmax < _max)
                _max = newmax;
            if (newmin > _min)
                 _min = newmin;
            if (_max < _min)
                return Object();
        }
    }
    if (_max == _min) {
        return make_object(Point_3(_ref_point + _dir * _min ));
    }
    return make_object(
        Segment_3(_ref_point + _dir*_min, _ref_point + _dir*_max));
}


template <class K>
inline
Object
intersection(const typename K::Iso_cuboid_3 &box, 
	     const typename K::Segment_3 &seg,
	     const K& k)
{
  return intersection(seg, box, k);
}


template <class K>
Object
intersection(
    const typename K::Iso_cuboid_3 &icub1,
    const typename K::Iso_cuboid_3 &icub2, 
    const K&)
{
    typedef typename K::Point_3 Point_3;
    typedef typename K::Iso_cuboid_3 Iso_cuboid_3;

    Point_3 min_points[2];
    Point_3 max_points[2];
    min_points[0] = (icub1.min)();
    min_points[1] = (icub2.min)();
    max_points[0] = (icub1.max)();
    max_points[1] = (icub2.max)();
    typedef typename K::FT FT;
    const int DIM = 3;
    int min_idx[DIM];
    int max_idx[DIM];
    Point_3 newmin;
    Point_3 newmax;
    for (int dim = 0; dim < DIM; ++dim) {
        min_idx[dim] =
          min_points[0].cartesian(dim) >= min_points[1].cartesian(dim) ? 0 : 1;
        max_idx[dim] =
          max_points[0].cartesian(dim) <= max_points[1].cartesian(dim) ? 0 : 1;
        if (min_idx[dim] != max_idx[dim]
                && max_points[max_idx[dim]].cartesian(dim)
                   < min_points[min_idx[dim]].cartesian(dim))
            return Object();
    }
    if (min_idx[0] == min_idx[1] && min_idx[0] == min_idx[2]) {
        newmin = min_points[min_idx[0]];
    } else {
        newmin = Point_3(
            min_idx[0] == 0
                ? wmult_hw((K*)0, min_points[0].hx(), min_points[1])
                : wmult_hw((K*)0, min_points[1].hx(), min_points[0])
            ,
            min_idx[1] == 0
                ? wmult_hw((K*)0, min_points[0].hy(), min_points[1])
                : wmult_hw((K*)0, min_points[1].hy(), min_points[0])
            ,
            min_idx[2] == 0
                ? wmult_hw((K*)0, min_points[0].hz(), min_points[1])
                : wmult_hw((K*)0, min_points[1].hz(), min_points[0])
            ,
            wmult_hw((K*)0, min_points[0].hw(), min_points[1]) );
    }
    if (max_idx[0] == max_idx[1] && max_idx[0] == max_idx[2]) {
        newmax = max_points[max_idx[0]];
    } else {
        newmax = Point_3(
            max_idx[0] == 0
                ? wmult_hw((K*)0, max_points[0].hx(), max_points[1])
                : wmult_hw((K*)0, max_points[1].hx(), max_points[0])
            ,
            max_idx[1] == 0
                ? wmult_hw((K*)0, max_points[0].hy(), max_points[1])
                : wmult_hw((K*)0, max_points[1].hy(), max_points[0])
            ,
            max_idx[2] == 0
                ? wmult_hw((K*)0, max_points[0].hz(), max_points[1])
                : wmult_hw((K*)0, max_points[1].hz(), max_points[0])
            ,
            wmult_hw((K*)0, max_points[0].hw(), max_points[1]) );
    }
    Object result = make_object(Iso_cuboid_3(newmin, newmax));
    return result;
}


} // namespace internal






template <class K>
inline
Object 
intersection(const Plane_3<K> &plane1, const Plane_3<K> &plane2)
{
  return typename K::Intersect_3()(plane1, plane2);
}

template <class K>
inline
Object 
intersection(const Plane_3<K> &plane1, const Plane_3<K> &plane2,
             const Plane_3<K> &plane3)
{
  return typename K::Intersect_3()(plane1, plane2, plane3);
}


template <class K>
inline
Object
intersection(const Plane_3<K>  &plane, const Line_3<K> &line)
{
  return typename K::Intersect_3()(plane, line);
}

template <class K>
inline
bool
do_intersect(const Plane_3<K> &plane, const Line_3<K> &line)
{
  return typename K::Do_intersect_3()(plane, line);
}

template <class K>
inline
Object
intersection(const Plane_3<K> &plane, const Ray_3<K> &ray)
{
  return typename K::Intersect_3()(plane, ray);
}

template <class K>
inline
bool
do_intersect(const Plane_3<K> &plane, const Ray_3<K> &ray)
{
  return typename K::Do_intersect_3()(plane, ray);
}

template <class K>
inline
Object
intersection(const Plane_3<K> &plane, const Segment_3<K> &seg)
{
  return typename K::Intersect_3()(plane, seg);
}


template <class K>
inline
bool
do_intersect(const Plane_3<K>  &plane, const Segment_3<K> &seg)
{
  return typename K::Do_intersect_3()(plane, seg);
}

template <class K>
inline
Object
intersection(const Line_3<K> &line,
	     const Bbox_3 &box)
{
  return typename K::Intersect_3()(line, box);
}

template <class K>
inline
Object
intersection(const Ray_3<K> &ray,
	     const Bbox_3 &box)
{
  return typename K::Intersect_3()(ray, box);
}

template <class K>
inline
Object
intersection(const Segment_3<K> &seg,
	     const Bbox_3 &box)
{
  return typename K::Intersect_3()(seg, box);
}

template <class K>
inline
Object
intersection(const Line_3<K> &line,
	     const Iso_cuboid_3<K> &box)
{
  return typename K::Intersect_3()(line, box);
}

template <class K>
inline
Object
intersection(const Ray_3<K> &ray,
	     const Iso_cuboid_3<K> &box)
{
  return typename K::Intersect_3()(ray, box);
}

template <class K>
inline
Object
intersection(const Segment_3<K> &seg,
	     const Iso_cuboid_3<K> &box)
{
  return typename K::Intersect_3()(seg, box);
}


template <class K>
inline
Object
intersection(const Iso_cuboid_3<K> &icub1,
	     const Iso_cuboid_3<K> &icub2)
{
  return typename K::Intersect_3()(icub1, icub2);
}

template <class K>
inline
Object
intersection(const Line_3<K> &l1,
             const Line_3<K> &l2) {
  return typename K::Intersect_3()(l1, l2);
}

template <class K>
inline
bool
do_intersect(const Line_3<K> &l1,
             const Line_3<K> &l2)
{
  return typename K::Do_intersect_3()(l1, l2);
}

template <class K>
inline
Object
intersection(const Segment_3<K> &s1,
             const Segment_3<K> &s2) {
  return typename K::Intersect_3()(s1, s2);
}

template <class K>
inline
bool
do_intersect(const Segment_3<K> &s1, const Segment_3<K> &s2)
{
  return typename K::Do_intersect_3()(s1, s2);
}

template <class K>
inline
Object
intersection(const Sphere_3<K> &s1,
             const Sphere_3<K> &s2) {
  return typename K::Intersect_3()(s1, s2);
}

template <class K>
inline
bool
do_intersect(const Sphere_3<K> &s1,
             const Sphere_3<K> &s2)
{
  return typename K::Do_intersect_3()(s1, s2);
}

template <class K>
inline
Object
intersection(const Plane_3<K> &p,
             const Sphere_3<K> &s) {
  return typename K::Intersect_3()(p, s);
}

template <class K>
inline
bool
do_intersect(const Plane_3<K> &p,
             const Sphere_3<K> &s)
{
  return typename K::Do_intersect_3()(p, s);
}

} //namespace CGAL
