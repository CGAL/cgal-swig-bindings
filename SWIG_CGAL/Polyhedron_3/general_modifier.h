// ------------------------------------------------------------------------------
// Copyright (c) 2012 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POLYHEDRON_3_GENERAL_MODIFIER_H
#define SWIG_CGAL_POLYHEDRON_3_GENERAL_MODIFIER_H

#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>

//TODO: a specific Input_iterator_wrapper for int and a SWIG macro
//typedef std::pair<Input_iterator_wrapper<int,int>,Input_iterator_wrapper<int,int> > Integer_range;

enum Modifier_mode { RELATIVE_INDEXING=0, ABSOLUTE_INDEXING=1};

template <class HDS>
class General_modifier 
#ifndef SWIG
: public CGAL::Modifier_base<HDS>
#endif
{
  typedef General_modifier<HDS> Self;
  //disable deep copy
  Self deepcopy();
  void deepcopy(const Self&);
  
  typedef typename HDS::Vertex::Point Point;
  
  typedef std::vector<Point> Point_container;
  typedef std::vector< std::list<int> > Facet_container;
  
  Point_container points;
  Facet_container facets;
  int m_h;
  int m_mode;
  
public:
    General_modifier() {}
    void begin_surface(int v,int f,int h=0,Modifier_mode mode=RELATIVE_INDEXING)
    {
      points.reserve(v);
      facets.reserve(f);
      m_h=h;
      m_mode=mode;
    }
    void end_surface(){}
    void add_vertex(const Point_3& p){points.push_back(p.get_data());}
    void begin_facet(){facets.push_back(std::list<int>());}
    void end_facet(){}
    void add_vertex_to_facet(int i){facets.back().push_back(i);}
    void rollback() {points.clear(); facets.clear();}
    void clear() {points.clear(); facets.clear();}
//    void add_facet(Integer_range range){
//      facets.push_back(std::list<int>());
//      std::copy( range.first,range.second,std::back_inserter(facets.back()) );
//    }
#ifndef SWIG
    void operator()( HDS& hds) {
        // Postcondition: `hds' is a valid polyhedral surface.
        CGAL::Polyhedron_incremental_builder_3<HDS> B( hds, true);
        B.begin_surface(points.size(),facets.size(),m_h,m_mode);

        for (typename Point_container::const_iterator it=points.begin();it!=points.end();++it)
          B.add_vertex(*it);
        
        for (typename Facet_container::const_iterator it=facets.begin();it!=facets.end();++it)
          B.add_facet(it->begin(),it->end());
        B.end_surface();
    }
#endif
};

#endif //SWIG_CGAL_POLYHEDRON_3_GENERAL_MODIFIER_H

// enum { RELATIVE_INDEXING, ABSOLUTE_INDEXING}; 
