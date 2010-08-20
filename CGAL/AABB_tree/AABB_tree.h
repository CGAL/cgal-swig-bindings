#ifndef SWIG_CGAL_AABB_TREE_AABB_TREE_H
#define SWIG_CGAL_AABB_TREE_AABB_TREE_H

#include "../Common/Macros.h"
#include "../Common/Input_iterator.h"
#include "../Kernel/Plane_3.h"
#include "../Kernel/Segment_3.h"
#include "../Kernel/Triangle_3.h"

#ifdef SWIGPYTHON
#include "../Python/Input_iterator_wrapper.h"
#include "../Python/Output_iterator_wrapper.h"
#endif
#ifdef SWIGJAVA
#include "../Java/Input_iterator_wrapper.h"
#include "../Java/Output_iterator_wrapper.h"
#endif


template <class Primitive_object>
struct Primitive_iterator_helper
{
  typedef std::pair<Input_iterator_wrapper<Primitive_object,typename Primitive_object::cpp_base>,Input_iterator_wrapper<Primitive_object,typename Primitive_object::cpp_base> > input;
};

template <class Tree,class Primitive_object>
class AABB_tree_wrapper
{
  Tree data;
public:
  typedef Tree cpp_base;
  typedef typename Primitive_iterator_helper<Primitive_object>::input Primitive_range;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}

//Creation
  AABB_tree_wrapper(){}
  AABB_tree_wrapper(Primitive_range range):data(range.first,range.second){}
//Operations  
  void rebuild(Primitive_range range){ data.rebuild(range.first,range.second); }
  FORWARD_CALL_0(void,clear)
  FORWARD_CALL_0(int,size)
  FORWARD_CALL_0(bool,empty)
  
};


#endif //SWIG_CGAL_AABB_TREE_AABB_TREE_H

//Types
//  typedef std::pair<Point, Primitive::Id>  Point_and_primitive_id;
//  typedef std::pair<CGAL::Object, Primitive::Id> Object_and_primitive_id;
//Intersection Tests
//  template <class Query> bool  tree.do_intersect ( Query query)  Returns true, iff the query intersects at least one of the input primitives. Type Query must be a type for which do_intersect predicates are defined in the AT class.
//  template <class Query> size_type  tree.number_of_intersected_primitives ( Query query)
//  template <class Query, class OutputIterator> OutputIterator  tree.all_intersected_primitives ( Query query, OutputIterator out)
//  template <class Query> boost::optional<Primitive::Id>  tree.any_intersected_primitive ( Query query)
//Intersections
//  template <class Query, class OutputIterator> OutputIterator  tree.all_intersections ( Query query, OutputIterator out)
//  template <class Query> boost::optional<Object_and_primitive_id>  tree.any_intersection ( Query query)
//Distance Queries
//  FT  tree.squared_distance ( Point query)
//  Point  tree.closest_point ( Point query)
//  Point_and_primitive_id  tree.closest_point_and_primitive ( Point query)
//Accelerating the Distance Queries
//  bool  tree.accelerate_distance_queries ()
//  template <class InputIterator, class PointAndIdBuilder> bool  tree.accelerate_distance_queries (  InputIterator begin, InputIterator beyond, PointAndIdBuilder idb = PointAndIdBuilder())
//  FT  tree.squared_distance ( Point query, Point hint)
//  Point  tree.closest_point ( Point query, Point hint)
//  Point_and_primitive_id  tree.closest_point_and_primitive ( Point query, Point_and_primitive_id hint)


