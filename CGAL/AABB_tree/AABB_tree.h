#ifndef SWIG_CGAL_AABB_TREE_AABB_TREE_H
#define SWIG_CGAL_AABB_TREE_AABB_TREE_H

#include "../Common/Macros.h"
#include "../Common/Input_iterator.h"
#include "../Common/Optional.h"
#include "../Kernel/Point_3.h"
#include "../Kernel/Plane_3.h"
#include "../Kernel/CGAL_Object.h"
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
  typedef std::pair<Input_iterator_wrapper<Primitive_object,typename Primitive_object::cpp_base>,
                    Input_iterator_wrapper<Primitive_object,typename Primitive_object::cpp_base> >                      input;
  typedef boost::function_output_iterator< Container_writer<Primitive_object,typename Primitive_object::cpp_base> >     output;
  typedef boost::function_output_iterator< Container_writer<std::pair<CGAL_Object,Primitive_object>,std::pair<CGAL::Object,typename Primitive_object::cpp_base> > >     output2;
};

typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range;

template <class Tree,class Primitive_object,class Primitive_id>
class AABB_tree_wrapper
{
  Tree data;
public:
  typedef Tree cpp_base;
  typedef typename Primitive_iterator_helper<Primitive_object>::input Primitive_range;
  typedef std::pair<Point_3,Primitive_id> Point_and_primitive_id;
  typedef std::pair<CGAL_Object,Primitive_id>  Object_and_primitive_id;
  typedef Optional<Primitive_id> Optional_primitive_id;
  typedef Optional<Object_and_primitive_id> Optional_object_and_primitive_id;
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
//Intersection Tests
  //do_intersect  
  FORWARD_CALL_1(bool,do_intersect,Segment_3)
  FORWARD_CALL_1(bool,do_intersect,Triangle_3)
  FORWARD_CALL_1(bool,do_intersect,Plane_3)
  //number_of_intersected_primitives
  FORWARD_CALL_1(int,number_of_intersected_primitives,Segment_3)
  FORWARD_CALL_1(int,number_of_intersected_primitives,Triangle_3)
  FORWARD_CALL_1(int,number_of_intersected_primitives,Plane_3)
  //all_intersected_primitives
  void all_intersected_primitives (const Segment_3 & query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Triangle_3& query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  void all_intersected_primitives (const Plane_3   & query, typename Primitive_iterator_helper<Primitive_id>::output out) {data.all_intersected_primitives(query.get_data(),out);}
  //any_intersected_primitive
  Optional_primitive_id any_intersected_primitive(const Segment_3 & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }
  Optional_primitive_id any_intersected_primitive(const Triangle_3 & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }
  Optional_primitive_id any_intersected_primitive(const Plane_3 & query) {
    boost::optional<typename Tree::Primitive::Id> res=data.any_intersected_primitive(query.get_data());
    if (res)
      return Optional_primitive_id(Primitive_id(*res));
    return Optional_primitive_id();
  }
//Intersections
  //any_intersection
  Optional_object_and_primitive_id any_intersection(const Segment_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  Optional_object_and_primitive_id any_intersection(const Plane_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  Optional_object_and_primitive_id any_intersection(const Triangle_3& query)
  {
    boost::optional<std::pair<CGAL::Object,typename Tree::Primitive::Id> > res=data.any_intersection(query.get_data());
    if (res)
      return Optional_object_and_primitive_id(Object_and_primitive_id(*res));
    return Optional_object_and_primitive_id();
  }
  //all_intersections
  void all_intersections (const Segment_3 & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Plane_3 & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  void all_intersections (const Triangle_3 & query, typename Primitive_iterator_helper<Primitive_id>::output2 out) {data.all_intersections(query.get_data(),out);}
  
//Distance Queries
  FORWARD_CALL_1(double,squared_distance,Point_3)
  FORWARD_CALL_1(Point_3,closest_point,Point_3)
  FORWARD_CALL_1(Point_and_primitive_id,closest_point_and_primitive,Point_3)
//Accelerating the Distance Queries
  FORWARD_CALL_0(bool,accelerate_distance_queries)
  FORWARD_CALL_2(double,squared_distance,Point_3,Point_3)
  FORWARD_CALL_2(Point_3,closest_point,Point_3,Point_3)
  FORWARD_CALL_2(Point_and_primitive_id,closest_point_and_primitive,Point_3,Point_and_primitive_id)  
  void accelerate_distance_queries (Point_range range) {data.accelerate_distance_queries(range.first,range.second);}  
};


#endif //SWIG_CGAL_AABB_TREE_AABB_TREE_H




