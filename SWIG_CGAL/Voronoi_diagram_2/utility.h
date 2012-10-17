// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H

#include <CGAL/Polygon_2.h>

namespace internal{

template <class Primitive, class Kernel, class Output_iterator>
bool
cast_into_segment(const Primitive& p, const typename CGAL::Iso_rectangle_2<Kernel>& bbox, Output_iterator out)
{
  typename Kernel::Segment_2 s;
  CGAL::Object object = CGAL::intersection(p,bbox);
  if ( CGAL::assign(s, object) )
  {
    *out++=s;
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

} //namespace internal



}

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H
