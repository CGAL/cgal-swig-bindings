// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_TRIANGULATION_2_DELAUNAY_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_DELAUNAY_TRIANGULATION_2_H

#include <SWIG_CGAL/Triangulation_2/Triangulation_2.h>
#include <SWIG_CGAL/Kernel/Iso_rectangle_2.h>

#include <CGAL/Delaunay_triangulation_2.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>


#ifndef SWIG
#if CGAL_VERSION_NR >= 1060000000
#include <variant>
namespace Dt2_internal {
  template <typename Type, class... Args>
  static auto get_if(std::variant<Args...>* variant) {
    return std::get_if<Type>(variant);
  }
}
#else // CGAL < 6.0
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
namespace Dt2_internal {
  template <typename Type, class... Args>
  static auto get_if(boost::variant<Args...>* variant) {
    return boost::get<Type>(variant);
  }
}
#endif // CGAL < 6.0
#endif // not SWIG

template <class Triangulation,class Vertex_handle, class Face_handle>
class Delaunay_triangulation_2_wrapper: public Triangulation_2_wrapper<Triangulation,Point_2,Vertex_handle,Face_handle,CGAL::Tag_false>
{
  typedef Triangulation_2_wrapper<Triangulation,Point_2,Vertex_handle,Face_handle,CGAL::Tag_false> Base;
public:
  #if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
  typedef boost::function_output_iterator< Container_writer<std::pair<Face_handle,int>,std::pair<typename Triangulation::Face_handle,int> > >     Edge_output_iterator;
  typedef boost::function_output_iterator< Container_writer<Face_handle,typename Triangulation::Face_handle > >                                   Face_output_iterator;
  #else
  typedef Generic_output_iterator< std::pair<Face_handle,int> >       Edge_output_iterator;
  typedef Generic_output_iterator< Face_handle >                      Face_output_iterator;
  #endif

  typedef std::pair<Face_handle,int> Edge;
  #ifndef SWIG
  typedef Triangulation cpp_base;
  Delaunay_triangulation_2_wrapper(const cpp_base& base) : Base(base) {}
  #endif
  Delaunay_triangulation_2_wrapper() : Base() {}
//Displacement
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,move_if_no_collision,Vertex_handle,Point_2)
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,move,Vertex_handle,Point_2)
//Queries
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Vertex_handle,nearest_vertex,Point_2,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Vertex_handle,nearest_vertex,Point_2)
  void get_conflicts_and_boundary(const Point_2& p,Face_output_iterator fout,Edge_output_iterator eout,const Face_handle& start) const
  {
    this->get_data().get_conflicts_and_boundary(p.get_data(),fout,eout,start.get_data());
  }
  void get_conflicts(const Point_2& p,Face_output_iterator fout,const Face_handle& start) const
  {
    this->get_data().get_conflicts(p.get_data(),fout,start.get_data());
  }

  void get_boundary_of_conflicts(const Point_2& p, Edge_output_iterator out, Face_handle start) const
  {
    this->get_data().get_boundary_of_conflicts(p.get_data(),out,start.get_data());
  }

  // Voronoi diagram
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Point_2,dual,Face_handle)
  SWIG_CGAL_FORWARD_CALL_AND_REF_1(Object,dual,Edge)
  Segment_2 dual(const Edge& e, const Iso_rectangle_2& ir)
  {
    CGAL::Object d = this->get_data().dual(std::make_pair(e.first.get_data(), e.second));

    if (const EPIC_Kernel::Segment_2* ss = CGAL::object_cast<EPIC_Kernel::Segment_2>(&d))
    {
      auto res = CGAL::intersection(*ss,ir.get_data());
      if (!res) return EPIC_Kernel::Segment_2(EPIC_Kernel::Point_2(0,0), EPIC_Kernel::Point_2(0,0));
      if (const EPIC_Kernel::Segment_2* s = Dt2_internal::get_if<EPIC_Kernel::Segment_2>(&(*res)))
        return *s;
    }
    if (const EPIC_Kernel::Line_2* l = CGAL::object_cast<EPIC_Kernel::Line_2>(&d))
    {
      auto res = CGAL::intersection(*l,ir.get_data());
      if (!res) return EPIC_Kernel::Segment_2(EPIC_Kernel::Point_2(0,0), EPIC_Kernel::Point_2(0,0));
      if (const EPIC_Kernel::Segment_2* s = Dt2_internal::get_if<EPIC_Kernel::Segment_2>(&(*res)))
        return *s;
    }
    const EPIC_Kernel::Ray_2* r = CGAL::object_cast<EPIC_Kernel::Ray_2>(&d);
    CGAL_assertion(r);
    auto res = CGAL::intersection(*r,ir.get_data());
    if (res)
      if (const EPIC_Kernel::Segment_2* s = Dt2_internal::get_if<EPIC_Kernel::Segment_2>(&(*res)))
        return *s;
    return EPIC_Kernel::Segment_2(EPIC_Kernel::Point_2(0,0), EPIC_Kernel::Point_2(0,0));
  }

//Deep copy
  #ifndef CGAL_DO_NOT_DEFINE_FOR_ALPHA_SHAPE_2
  typedef Delaunay_triangulation_2_wrapper<Triangulation,Vertex_handle,Face_handle> Self;
  Self deepcopy() const {return Self(this->get_data());}
  #endif
};

#endif //SWIG_CGAL_TRIANGULATION_2_DELAUNAY_TRIANGULATION_2_H

// Voronoi diagram
//   Object   dt.dual ( Edge_circulator ec)
//   Object   dt.dual ( Edge_iterator ei)
//   template < class Stream>
//   Stream&   dt.draw_dual ( Stream & ps)
