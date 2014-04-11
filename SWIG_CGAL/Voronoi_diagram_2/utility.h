// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H

#include <CGAL/Polygon_2.h>
#include <CGAL/Lazy_exact_nt.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Cartesian_converter.h>
#include <boost/optional.hpp>

namespace internal{

// raw version
//template <class Primitive, class Kernel, class Output_iterator>
//bool
//cast_into_segment(const Primitive& p, const typename CGAL::Iso_rectangle_2<Kernel>& bbox, Output_iterator out)
//{
//  typename Kernel::Segment_2 s;
//  CGAL::Object object = CGAL::intersection(p,bbox);
//  if ( CGAL::assign(s, object) )
//  {
//    *out++=s;
//    return true;
//  }
//  return false;
//}

//using interval arithmetic to snap points onto bbox
template <class Primitive, class Kernel, class Output_iterator>
bool
cast_into_segment(const Primitive& p, const typename CGAL::Iso_rectangle_2<Kernel>& bbox, Output_iterator out)
{
  if ( p.is_degenerate() ) return false;

  typedef CGAL::Simple_cartesian< CGAL::Lazy_exact_nt<CGAL::Gmpq> > Exact_kernel;
  CGAL::Cartesian_converter<Kernel,Exact_kernel> to_exact;
  
  typename Exact_kernel::Segment_2 s;
  CGAL::Object object = CGAL::intersection( to_exact(p), to_exact(bbox) );
  if ( CGAL::assign(s, object) )
  {
    typename Kernel::Point_2 src(
      approx( s.source().x() ).do_overlap( bbox.xmax() )? bbox.xmax() :
     (approx( s.source().x() ).do_overlap( bbox.xmin() )? bbox.xmin() : to_double(s.source().x()) ),
      approx( s.source().y() ).do_overlap( bbox.ymax() )? bbox.ymax() :
     (approx( s.source().y() ).do_overlap( bbox.ymin() )? bbox.ymin() : to_double(s.source().y()) )
    );

    typename Kernel::Point_2 tgt(
      approx( s.target().x() ).do_overlap( bbox.xmax() )? bbox.xmax() :
     (approx( s.target().x() ).do_overlap( bbox.xmin() )? bbox.xmin() : to_double(s.target().x()) ),
      approx( s.target().y() ).do_overlap( bbox.ymax() )? bbox.ymax() :
     (approx( s.target().y() ).do_overlap( bbox.ymin() )? bbox.ymin() : to_double(s.target().y()) )
    );
    
    *out++=typename Kernel::Segment_2(src,tgt);
    return true;
  }
  return false;
}

/*! crop voronoi bissectors to a given bbox as a set of segments*/
template <class Voronoi_diagram, class Kernel, class Segment_output_iterator>
Segment_output_iterator
crop_face_boundary(const Voronoi_diagram& vd,
                   const CGAL::Iso_rectangle_2<Kernel>& bbox,
                   typename Voronoi_diagram::Face_handle face,
                   Segment_output_iterator output)
{
  typename Voronoi_diagram::Ccb_halfedge_circulator start=face->outer_ccb();
  typename Voronoi_diagram::Ccb_halfedge_circulator current=start;
  do{
    CGAL::Object dual = vd.dual().dual(current->dual() );

    const typename Kernel::Segment_2* segment_ptr;
    const typename Kernel::Line_2* line_ptr;
    const typename Kernel::Ray_2* ray_ptr;

    if ( ( segment_ptr=CGAL::object_cast<typename Kernel::Segment_2>(&dual) ) ) cast_into_segment(*segment_ptr, bbox, output);
    else{
      if ( ( line_ptr=CGAL::object_cast<typename Kernel::Line_2>(&dual) ) ) cast_into_segment(*line_ptr, bbox, output);
      else
      {
        if ( ( ray_ptr=CGAL::object_cast<typename Kernel::Ray_2>(&dual) ) ) cast_into_segment(*ray_ptr, bbox, output);
      }
    }
  }
  while(++current!=start);
  return output;
}

/*! returns k if `pt=bbox[k]` or `(k + k+1)/2` if `pt` lies inbetween bbox[k] and bbox[k+1] */
template <class Point_2, class Iso_rectangle_2>
double index_on_bbox(const Point_2& pt, const Iso_rectangle_2& bbox)
{
  CGAL_precondition( bbox[0].x()==bbox.xmin() && bbox[0].y()==bbox.ymin() );

  if ( pt.y() == bbox.ymin() ){
    if ( pt.x() == bbox.xmin() ) return 0;
    if ( pt.x() == bbox.xmax() ) return 1;
    return 0.5;
  }

  if ( pt.y() == bbox.ymax() ){
    if ( pt.x() == bbox.xmin() ) return 3;
    if ( pt.x() == bbox.xmax() ) return 2;
    return 2.5;
  }

  if ( pt.x() == bbox.xmin() ) return 3.5;
  CGAL_assertion ( pt.x() == bbox.xmax() );
  return 1.5;
}

template <class Kernel, class Iso_rectangle_2, class Polygon_2>
void
add_next_points_on_rectangle(
  const typename Kernel::Point_2& bissector_target,
  const typename Kernel::Point_2& next_point,
  const Iso_rectangle_2& bbox,
  Polygon_2& polygon  )
{
  //ensure bissector_target is on the bbox boundary
  CGAL_assertion(
    bbox.xmin()==bissector_target.x() ||  bbox.xmax()==bissector_target.x() ||
    bbox.ymin()==bissector_target.y() ||  bbox.ymax()==bissector_target.y()
  );
  //ensure next_point is on the bbox boundary
  CGAL_assertion(
    bbox.xmin()==next_point.x() ||  bbox.xmax()==next_point.x() ||
    bbox.ymin()==next_point.y() ||  bbox.ymax()==next_point.y()
  );
  //ensure the points are different
  CGAL_assertion( next_point!=bissector_target );

  //bbox[0], bbox[1], bbox[2], bbox[3] are counterclockwise oriented
  double index_target=index_on_bbox(bissector_target,bbox);
  double index_next=index_on_bbox(next_point,bbox);

  if (index_next == index_target) return;

  if (index_next < index_target) index_next+=4;
  int k = std::floor( index_target);

  while (++k <= index_next) polygon.push_back( bbox[k] );
}

template <class Iterator,class T>
Iterator next_in_a_loop(Iterator curr,std::vector<T>& vector)
{
  if (++curr==vector.end()) return vector.begin();
  return curr;
}

/*! crop voronoi bissectors to a given bbox as a closed polygon, including bbox boundary */
template <class Voronoi_diagram, class Kernel>
void
crop_voronoi_facet_polygon(const Voronoi_diagram& vd,
                           const CGAL::Iso_rectangle_2<Kernel>& bbox,
                           typename Voronoi_diagram::Face_handle face,
                           CGAL::Polygon_2<Kernel>& polygon)
{
  typename Voronoi_diagram::Ccb_halfedge_circulator start=face->outer_ccb();
  typename Voronoi_diagram::Ccb_halfedge_circulator current=start;

  std::vector< std::pair<typename Kernel::Point_2,bool> > points;
  static const bool ORIGINAL = true;

  do{
    CGAL::Object dual = vd.dual().dual(current->dual() );

    const typename Kernel::Segment_2* segment_ptr;
    const typename Kernel::Line_2* line_ptr;
    const typename Kernel::Ray_2* ray_ptr;

    typename Kernel::Segment_2 cr_seg;
    typename Kernel::Vector_2 direction;

    if ( ( segment_ptr=CGAL::object_cast<typename Kernel::Segment_2>(&dual) ) )
    {
      if ( !cast_into_segment(*segment_ptr, bbox, &cr_seg) ) continue;
      typename Kernel::Vector_2 direction = current->target()->point() - current->source()->point();

      if ( cr_seg.to_vector() * direction < 0 ) cr_seg=cr_seg.opposite();
      typename Kernel::Segment_2 original = ( segment_ptr->to_vector() * direction < 0 ) ? segment_ptr->opposite():*segment_ptr;
      points.push_back( std::make_pair( cr_seg.source(), original.source()==cr_seg.source() ) );
      points.push_back( std::make_pair( cr_seg.target(), original.target()==cr_seg.target() ) );


    }
    else{
      if ( ( line_ptr=CGAL::object_cast<typename Kernel::Line_2>(&dual) ) )
      {
        if ( !cast_into_segment(*line_ptr, bbox, &cr_seg) ) continue;
        typename Kernel::Point_2 dual_pt=face->dual()->point();
        typename Kernel::Point_2 p1=line_ptr->point(0);
        typename Kernel::Point_2 p2=line_ptr->point(1);
        typename Kernel::Vector_2 direction = CGAL::orientation(p1,p2,dual_pt) == CGAL::LEFT_TURN ?
                                              (p2-p1):(p1-p2);
        if ( cr_seg.to_vector() * direction < 0 ) cr_seg=cr_seg.opposite();
        points.push_back( std::make_pair( cr_seg.source(), !ORIGINAL ) );
        points.push_back( std::make_pair( cr_seg.target(), !ORIGINAL ) );
      }
      else
      {
        if ( ( ray_ptr=CGAL::object_cast<typename Kernel::Ray_2>(&dual) ) )
        {
          if ( !cast_into_segment(*ray_ptr, bbox, &cr_seg) ) continue;
          typename Kernel::Vector_2 direction = current->has_source() ?
                                                (ray_ptr->point(1) - ray_ptr->source()) :
                                                (ray_ptr->source() - ray_ptr->point(1)) ;
          if ( cr_seg.to_vector() * direction < 0 ) cr_seg=cr_seg.opposite();
          if (current->has_source())
          {
            points.push_back( std::make_pair( cr_seg.source(), ray_ptr->source()==cr_seg.source() ) );
            points.push_back( std::make_pair( cr_seg.target(), !ORIGINAL ) );
          }
          else
          {
            points.push_back( std::make_pair( cr_seg.source(), !ORIGINAL ) );
            points.push_back( std::make_pair( cr_seg.target(), ray_ptr->source()==cr_seg.target() ) );
          }
        }
      }
    }
  }
  while(++current!=start);

  if ( points.empty() )
  {
    polygon.push_back( bbox[0] );
    polygon.push_back( bbox[1] );
    polygon.push_back( bbox[2] );
    polygon.push_back( bbox[3] );
    return;
  }

  for (typename std::vector< std::pair<typename Kernel::Point_2,bool> >::iterator
        itpt=points.begin(), itpt_end=points.end(); itpt!=itpt_end; ++itpt)
  {
    polygon.push_back(itpt->first);
    ++itpt;
    if ( itpt->second != ORIGINAL )
    {
      polygon.push_back(itpt->first);
      add_next_points_on_rectangle<Kernel>(
        itpt->first,
        next_in_a_loop(itpt,points)->first,
        bbox,
        polygon
      );
    }
  }
}

/*! crop a voronoi bissector to a given bbox as a segment */
template <class Voronoi_diagram, class Kernel>
boost::optional< typename Kernel::Segment_2 >
crop_bissector( const Voronoi_diagram& vd,
                typename Voronoi_diagram::Halfedge_handle hedge,
                const CGAL::Iso_rectangle_2<Kernel>& bbox )
{
  typedef CGAL::Simple_cartesian< CGAL::Lazy_exact_nt<CGAL::Gmpq> > Exact_kernel;
  typedef typename Exact_kernel::Point_2 EPoint_2;
  typedef typename Exact_kernel::Segment_2 ESegment_2;

  typedef typename Kernel::Ray_2 Ray_2;
  typedef typename Kernel::Line_2 Line_2;
  typedef typename Kernel::Segment_2 Segment_2;

  CGAL::Cartesian_converter<Kernel,Exact_kernel> to_exact;
  CGAL::Cartesian_converter<Exact_kernel,Kernel> to_output;

  CGAL::Object dual_obj = vd.dual().dual( hedge->dual() );
  CGAL::Object crop_obj;

  if (const Segment_2 * segment_ptr = CGAL::object_cast<Segment_2>(&dual_obj)) {
    if ( segment_ptr->is_degenerate() )
      crop_obj = intersection( to_exact(segment_ptr->source()), to_exact(bbox) );
    else
      crop_obj = intersection( to_exact(*segment_ptr), to_exact(bbox) );
  } else {
    if (const Ray_2 * ray_ptr = CGAL::object_cast<Ray_2>(&dual_obj)) {
      crop_obj = intersection( to_exact(*ray_ptr), to_exact(bbox) );
    }
    else
    {
      const Line_2 * line_ptr = CGAL::object_cast<Line_2>(&dual_obj);
      CGAL_assertion(  line_ptr );
      crop_obj = intersection( to_exact(*line_ptr), to_exact(bbox) );
    }
  }

  if ( crop_obj.empty() ) return boost::optional<typename Kernel::Segment_2>();

  if (const EPoint_2 * point = CGAL::object_cast<EPoint_2>(&crop_obj))
      return Segment_2(to_output(*point), to_output(*point));

  const ESegment_2 * segment = CGAL::object_cast<ESegment_2>(&crop_obj);
  CGAL_assertion(segment);
  return to_output(*segment);
}

} //namespace internal


#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H
