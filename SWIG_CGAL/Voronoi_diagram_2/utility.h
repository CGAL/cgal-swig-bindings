// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H
#define SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H


namespace internal{

template <class Primitive, class Kernel, class Output_iterator>
Output_iterator
cast_into_segment(const Primitive& p, const typename CGAL::Iso_rectangle_2<Kernel>& bbox, Output_iterator out)      
{
  typename Kernel::Segment_2 s;
  CGAL::Object object = CGAL::intersection(p,bbox);
  if ( CGAL::assign(s, object) ) *out++=s;
  return out;
}

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

}

#endif //SWIG_CGAL_VORONOI_DIAGRAM_2_UTILITY_H
