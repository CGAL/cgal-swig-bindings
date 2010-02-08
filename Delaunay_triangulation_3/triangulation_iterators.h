#ifndef CGAL_SWIG_TRIANGULATION_ITERATORS_H
#define CGAL_SWIG_TRIANGULATION_ITERATORS_H

#include "triangulation_handles.h"
#include "triple.h"

#ifdef SWIGPYTHON
#define DECLARE_TRIANGULATION_ITERATOR(NAME,RETURN)            \
template<class Triangulation>                                  \
class NAME{                                                    \
  typename Triangulation::NAME cur;                            \
  typename Triangulation::NAME end;                            \
public:                                                        \
                                                               \
  NAME(                                    \
    typename Triangulation::NAME cur_,                         \
    typename Triangulation::NAME end_                          \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  NAME<Triangulation> __iter__(){return *this;}                \
  RETURN next()                          \
  {                                                            \
    if (cur!=end)                                              \
      return RETURN ( (cur++) );         \
    throw 1;                                                   \
    return RETURN(NULL);                 \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};       

#define DECLARE_TRIANGULATION_ITERATOR_PAIR(NAME,FIRST,SECOND) \
template<class Triangulation>                                  \
class NAME{                                                    \
  typename Triangulation::NAME cur;                            \
  typename Triangulation::NAME end;                            \
public:                                                        \
                                                               \
  NAME(                                                        \
    typename Triangulation::NAME cur_,                         \
    typename Triangulation::NAME end_                          \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  NAME __iter__(){return *this;}                               \
  std::pair<FIRST,SECOND> next()                               \
  {                                                            \
    if (cur!=end){                                             \
      typename Triangulation::NAME res=cur++;                  \
      return                                                   \
      std::pair<FIRST,SECOND> (FIRST(res->first),res->second); \
    }                                                          \
    throw 1;                                                   \
    return std::pair<FIRST,SECOND> (FIRST(),0);                \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};                                                             

#define DECLARE_TRIANGULATION_ITERATOR_TRIPLE(NAME,FIRST,SECOND,THIRD) \
template<class Triangulation>                                          \
class NAME{                                                            \
  typename Triangulation::NAME cur;                                    \
  typename Triangulation::NAME end;                                    \
public:                                                                \
                                                                       \
  NAME(                                                                \
    typename Triangulation::NAME cur_,                                 \
    typename Triangulation::NAME end_                                  \
  ):cur(cur_),end(end_){}                                              \
                                                                       \
  NAME __iter__(){return *this;}                                       \
  CGAL_SWIG::Triple<FIRST,SECOND,THIRD> next()                         \
  {                                                                    \
    if (cur!=end){                                                     \
      typename Triangulation::NAME res=cur++;                          \
      return                                                           \
      CGAL_SWIG::Triple<FIRST,SECOND,THIRD> (FIRST(res->first),        \
                                             res->second,              \
                                             res->third);              \
    }                                                                  \
    throw 1;                                                           \
    return CGAL_SWIG::Triple<FIRST,SECOND,THIRD>(FIRST(),-1,-1);       \
  }                                                                    \
                                                                       \
  bool hasNext(){                                                      \
    return cur!=end;                                                   \
  }                                                                    \
};

#else


#define DECLARE_TRIANGULATION_ITERATOR(NAME,RETURN)            \
template<class Triangulation>                                  \
class NAME{                                                    \
  typename Triangulation::NAME cur;                            \
  typename Triangulation::NAME end;                            \
public:                                                        \
                                                               \
  NAME(                                                        \
    typename Triangulation::NAME cur_,                         \
    typename Triangulation::NAME end_                          \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  RETURN next()                          \
  {                                                            \
    if (cur!=end)                                              \
      return RETURN ( (cur++) );         \
    return RETURN(NULL);                 \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};             

#define DECLARE_TRIANGULATION_ITERATOR_PAIR(NAME,FIRST,SECOND) \
template<class Triangulation>                                  \
class NAME{                                                    \
  typename Triangulation::NAME cur;                            \
  typename Triangulation::NAME end;                            \
public:                                                        \
                                                               \
  NAME(                                                        \
    typename Triangulation::NAME cur_,                         \
    typename Triangulation::NAME end_                          \
  ):cur(cur_),end(end_){}                                      \
                                                               \
  std::pair<FIRST,SECOND> next()                               \
  {                                                            \
    if (cur!=end){                                             \
      typename Triangulation::NAME res=cur++;                  \
      return                                                   \
      std::pair<FIRST,SECOND> (FIRST(res->first),res->second); \
    }                                                          \
    return std::pair<FIRST,SECOND> (FIRST(),0);                \
  }                                                            \
                                                               \
  bool hasNext(){                                              \
    return cur!=end;                                           \
  }                                                            \
};                                                             

#define DECLARE_TRIANGULATION_ITERATOR_TRIPLE(NAME,FIRST,SECOND,THIRD) \
template<class Triangulation>                                          \
class NAME{                                                            \
  typename Triangulation::NAME cur;                                    \
  typename Triangulation::NAME end;                                    \
public:                                                                \
                                                                       \
  NAME(                                                                \
    typename Triangulation::NAME cur_,                                 \
    typename Triangulation::NAME end_                                  \
  ):cur(cur_),end(end_){}                                              \
                                                                       \
  CGAL_SWIG::Triple<FIRST,SECOND,THIRD> next()                         \
  {                                                                    \
    if (cur!=end){                                                     \
      typename Triangulation::NAME res=cur++;                          \
      return                                                           \
      CGAL_SWIG::Triple<FIRST,SECOND,THIRD> (FIRST(res->first),        \
                                             res->second,              \
                                             res->third);              \
    }                                                                  \
    return CGAL_SWIG::Triple<FIRST,SECOND,THIRD>(FIRST(),-1,-1);       \
  }                                                                    \
                                                                       \
  bool hasNext(){                                                      \
    return cur!=end;                                                   \
  }                                                                    \
};

#endif


DECLARE_TRIANGULATION_ITERATOR(All_vertices_iterator,CGAL_Vertex_handle<Triangulation>)
DECLARE_TRIANGULATION_ITERATOR(Finite_vertices_iterator,CGAL_Vertex_handle<Triangulation>)

DECLARE_TRIANGULATION_ITERATOR(All_cells_iterator,CGAL_Cell_handle<Triangulation>)
DECLARE_TRIANGULATION_ITERATOR(Finite_cells_iterator,CGAL_Cell_handle<Triangulation>)

DECLARE_TRIANGULATION_ITERATOR_PAIR(All_facets_iterator,CGAL_Cell_handle<Triangulation> , int)
DECLARE_TRIANGULATION_ITERATOR_PAIR(Finite_facets_iterator,CGAL_Cell_handle<Triangulation> , int)

DECLARE_TRIANGULATION_ITERATOR_TRIPLE(All_edges_iterator,CGAL_Cell_handle<Triangulation> , int, int)
DECLARE_TRIANGULATION_ITERATOR_TRIPLE(Finite_edges_iterator,CGAL_Cell_handle<Triangulation> , int, int)

template<class Triangulation>
class Point_iterator{
  typename Triangulation::Point_iterator cur;
  typename Triangulation::Point_iterator end;
public:

  Point_iterator(
    typename Triangulation::Point_iterator cur_,
    typename Triangulation::Point_iterator end_
  ):cur(cur_),end(end_){}
  #ifdef SWIGPYTHON
  Point_iterator<Triangulation> __iter__(){return *this;}
  #endif
  EPIC_Point_3 next()
  {
    if (cur!=end)
      return EPIC_Point_3 ( *(cur++) );
    #ifdef SWIGPYTHON
    throw 1;
    #endif
    return EPIC_Point_3();
  }

  bool hasNext(){
    return cur!=end;
  }
};

template<class Triangulation>
class Cell_circulator{
  typename Triangulation::Cell_circulator cur;
public:
  Cell_circulator( typename Triangulation::Cell_circulator cur_):cur(cur_){}
  #ifdef SWIGPYTHON
  Cell_circulator<Triangulation> __iter__(){return *this;}
  #endif
  CGAL_Cell_handle<Triangulation> next() { return CGAL_Cell_handle<Triangulation> ( (cur++) ); }

  bool hasNext(){return true; }
};

template<class Triangulation>
class Facet_circulator{
  typename Triangulation::Facet_circulator cur;
public:
  Facet_circulator( typename Triangulation::Facet_circulator cur_):cur(cur_){}
  #ifdef SWIGPYTHON
  Facet_circulator<Triangulation> __iter__(){return *this;}
  #endif
  std::pair<CGAL_Cell_handle<Triangulation>,int> next(){
    typename Triangulation::Facet_circulator res=cur++;
    return std::make_pair(CGAL_Cell_handle<Triangulation>(res->first),res->second); 
  }

  bool hasNext(){return true; }
};

#endif //CGAL_SWIG_TRIANGULATION_ITERATORS_H
