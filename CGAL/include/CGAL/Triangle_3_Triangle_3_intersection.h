#ifndef CGAL_TRIANGLE_3_TRIANGLE_3_INTERSECTION_H
#define CGAL_TRIANGLE_3_TRIANGLE_3_INTERSECTION_H

namespace CGAL {

namespace internal{

template <class Kernel>
Object
intersection_coplanar_triangles(
  const typename Kernel::Triangle_3& t1,
  const typename Kernel::Triangle_3& t2,
  const Kernel& k)
{
  typename Kernel::Has_on_3 has_on=k.has_on_3_object();
  
  return Object();
}
  
template <class Kernel>
Object
intersection(
  const typename Kernel::Triangle_3& t1,
  const typename Kernel::Triangle_3& t2,
  const Kernel& k)
{
  CGAL_precondition(!t1.is_degenerate() && !t2.is_degenerate());
  
  typename Kernel::Intersect_3 inter=k.intersect_3_object();
  CGAL::Object res=inter(t1.supporting_plane(),t2.supporting_plane());
  
  const typename Kernel::Line_3* line=CGAL::object_cast<typename Kernel::Line_3>(&res);
  
  if (line==NULL){
    const typename Kernel::Plane_3* plane=CGAL::object_cast<typename Kernel::Plane_3>(&res);
    if (plane!=NULL)
      return intersection_coplanar_triangles(t1,t2,k);
    return Object();
  }
  
  //The supporting planes of the triangles intersect along a line.
  Object inter1=inter(t1,*line);
  Object inter2=inter(t2,*line);
  
  
  const typename Kernel::Segment_3* sgt1=CGAL::object_cast<typename Kernel::Segment_3>(&inter1);
  
  if (sgt1 == NULL){
    //intersection of the line and triangle 1 is a point or is empty
    const typename Kernel::Point_3* pt1=CGAL::object_cast<typename Kernel::Point_3>(&inter1);
    if (pt1==NULL) return Object(); //the line does not intersect the triangle t1
    const typename Kernel::Segment_3* sgt2=CGAL::object_cast<typename Kernel::Segment_3>(&inter2);
    if (sgt2==NULL){
      const typename Kernel::Point_3* pt2=CGAL::object_cast<typename Kernel::Point_3>(&inter2);
      if (pt2==NULL || *pt1!=*pt2) return Object();
      return inter1;
    }
    //case point, segment
    if ( sgt2->has_on(*pt1) ) return inter1;
    return Object();
  }
  
  const typename Kernel::Segment_3* sgt2=CGAL::object_cast<typename Kernel::Segment_3>(&inter2);
  if (sgt2==NULL){
    const typename Kernel::Point_3* pt2=CGAL::object_cast<typename Kernel::Point_3>(&inter2);
    if ( pt2==NULL || !sgt1->has_on(*pt2) ) return Object();
    return inter2;
  }
  
  return intersection_collinear_segments(*sgt1,*sgt2,k);
}


}//namespace internal

template <class K>
inline
Object
intersection(const Triangle_3<K> &t1, const Triangle_3<K> &t2)
{
  return typename K::Intersect_3()(t1, t2);
}

} // namespace CGAL




#endif //CGAL_TRIANGLE_3_TRIANGLE_3_INTERSECTION_H
