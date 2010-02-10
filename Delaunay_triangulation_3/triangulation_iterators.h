#ifndef CGAL_SWIG_TRIANGULATION_ITERATORS_H
#define CGAL_SWIG_TRIANGULATION_ITERATORS_H

#include "triangulation_handles.h"
#include "triple.h"

template <class T>
struct Iterator_helper{
  template <class Ti>
  static T convert(const Ti& i){
    return T(i);
  }
  
  static T
  default_value(){return T(NULL);}
};

template<class T1>
struct Iterator_helper<std::pair<T1,int> >{
  template <class T>
  static std::pair<T1,int> convert(const T& i){
    return std::pair<T1,int>(T1(i->first),i->second);
  }
  
  static std::pair<T1,int>
  default_value(){return std::pair<T1,int>(T1(NULL),-1);}
};

template<class T1>
struct Iterator_helper<CGAL_SWIG::Triple<T1,int,int> >{
  template <class T>
  static CGAL_SWIG::Triple<T1,int,int> convert(const T& i){
    return CGAL_SWIG::Triple<T1,int,int>(T1(i->first),i->second,i->third);
  }
  
  static CGAL_SWIG::Triple<T1,int,int>
  default_value(){return CGAL_SWIG::Triple<T1,int,int>(T1(NULL),-1,-1);}
};

template <>
struct Iterator_helper<EPIC_Point_3>{
  template <class Ti>
  static EPIC_Point_3 convert(const Ti& i){
    return EPIC_Point_3(*i);
  }
  
  static EPIC_Point_3
  default_value(){return EPIC_Point_3();}
};


#ifdef SWIGPYTHON
#define DECLARE_TRIANGULATION_ITERATOR(NAME,RETURN)            \
template<class Triangulation>                                  \
class CGAL_##NAME{                                             \
  typename Triangulation::NAME cur;                            \
  typename Triangulation::NAME end;                            \
public:                                                        \
                                                               \
  CGAL_##NAME(                                                 \
    typename Triangulation::NAME cur_,                         \
    typename Triangulation::NAME end_                          \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  CGAL_##NAME<Triangulation> __iter__(){return *this;}         \
  RETURN next()                                                \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<RETURN>::convert ( (cur++) );     \
    throw 1;                                                   \
    return Iterator_helper<RETURN>::default_value();           \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};       
#else
#define DECLARE_TRIANGULATION_ITERATOR(NAME,RETURN)            \
template<class Triangulation>                                  \
class CGAL_##NAME{                                             \
  typename Triangulation::NAME cur;                            \
  typename Triangulation::NAME end;                            \
public:                                                        \
                                                               \
  CGAL_##NAME(                                                 \
    typename Triangulation::NAME cur_,                         \
    typename Triangulation::NAME end_                          \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  RETURN next()                                                \
  {                                                            \
    if (cur!=end)                                              \
      return Iterator_helper<RETURN>::convert ( (cur++) );     \
    return Iterator_helper<RETURN>::default_value();           \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};
#endif

#define PAIR_CHI std::pair<CGAL_Cell_handle<Triangulation>,int>
#define TRIPLE_CHII CGAL_SWIG::Triple<CGAL_Cell_handle<Triangulation>,int,int>

DECLARE_TRIANGULATION_ITERATOR(All_vertices_iterator,CGAL_Vertex_handle<Triangulation>)
DECLARE_TRIANGULATION_ITERATOR(Finite_vertices_iterator,CGAL_Vertex_handle<Triangulation>)

DECLARE_TRIANGULATION_ITERATOR(All_cells_iterator,CGAL_Cell_handle<Triangulation>)
DECLARE_TRIANGULATION_ITERATOR(Finite_cells_iterator,CGAL_Cell_handle<Triangulation>)

DECLARE_TRIANGULATION_ITERATOR(All_facets_iterator,PAIR_CHI)
DECLARE_TRIANGULATION_ITERATOR(Finite_facets_iterator,PAIR_CHI)

DECLARE_TRIANGULATION_ITERATOR(All_edges_iterator,TRIPLE_CHII)
DECLARE_TRIANGULATION_ITERATOR(Finite_edges_iterator,TRIPLE_CHII)

DECLARE_TRIANGULATION_ITERATOR(Point_iterator,EPIC_Point_3)

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

#endif //CGAL_SWIG_TRIANGULATION_ITERATORS_H
