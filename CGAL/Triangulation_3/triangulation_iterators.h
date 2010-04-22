#ifndef SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_ITERATORS_H
#define SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_ITERATORS_H

#include "triangulation_handles.h"
#include "../Common/Input_iterator.h"

#define PAIR_CHI std::pair<CGAL_Cell_handle<T>,int>
#define TRIPLE_CHII CGAL_SWIG::Triple<CGAL_Cell_handle<T>,int,int>

DECLARE_ITERATOR_CLASS(All_vertices_iterator,CGAL_Vertex_handle<T>)
DECLARE_ITERATOR_CLASS(Finite_vertices_iterator,CGAL_Vertex_handle<T>)

DECLARE_ITERATOR_CLASS(All_cells_iterator,CGAL_Cell_handle<T>)
DECLARE_ITERATOR_CLASS(Finite_cells_iterator,CGAL_Cell_handle<T>)

DECLARE_ITERATOR_CLASS(All_facets_iterator,PAIR_CHI)
DECLARE_ITERATOR_CLASS(Finite_facets_iterator,PAIR_CHI)

DECLARE_ITERATOR_CLASS(All_edges_iterator,TRIPLE_CHII)
DECLARE_ITERATOR_CLASS(Finite_edges_iterator,TRIPLE_CHII)

DECLARE_ITERATOR_CLASS(Point_iterator,Point_3)

template<class Triangulation>
class CGAL_Cell_circulator{
  typename Triangulation::Cell_circulator cur;
public:
  CGAL_Cell_circulator( typename Triangulation::Cell_circulator cur_):cur(cur_){}
  #ifdef SWIGPYTHON
  CGAL_Cell_circulator<Triangulation> __iter__(){return *this;}
  #endif
  CGAL_Cell_handle<Triangulation> next() { return CGAL_Cell_handle<Triangulation> ( (cur++) ); }

  bool hasNext(){return true; }
};

template<class Triangulation>
class CGAL_Facet_circulator{
  typename Triangulation::Facet_circulator cur;
public:
  CGAL_Facet_circulator( typename Triangulation::Facet_circulator cur_):cur(cur_){}
  #ifdef SWIGPYTHON
  CGAL_Facet_circulator<Triangulation> __iter__(){return *this;}
  #endif
  std::pair<CGAL_Cell_handle<Triangulation>,int> next(){
    typename Triangulation::Facet_circulator res=cur++;
    return std::make_pair(CGAL_Cell_handle<Triangulation>(res->first),res->second); 
  }

  bool hasNext(){return true; }
};

#endif //SWIG_CGAL_TRIANGULATION_3_TRIANGULATION_ITERATORS_H
