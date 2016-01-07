// ------------------------------------------------------------------------------
// Copyright (c) 2015 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_PMP_UTILS_H
#define SWIG_CGAL_PMP_UTILS_H

#include <CGAL/property_map.h>

template <class Handle, class X>
struct X_from_id_pmap{
  std::vector<X>& props;
  typedef boost::read_write_property_map_tag category;
  typedef Handle key_type;
  typedef const X& reference;
  typedef X value_type;

  X_from_id_pmap(std::vector<X>& v) : props(v) {}

  friend const X& get(X_from_id_pmap<Handle,X> map, Handle h){
     return map.props[h->id()];
  }
  friend void put(X_from_id_pmap<Handle,X> map, Handle h, const X& v){
     map.props[h->id()]=v;
  }
};

template <class Handle>
struct Int_from_id_pmap{
  std::vector<int>& ids;
  typedef boost::read_write_property_map_tag category;
  typedef Handle key_type;
  typedef int reference;
  typedef int value_type;

  Int_from_id_pmap(std::vector<int>& v) : ids(v) {}

  friend int get(Int_from_id_pmap<Handle> map, Handle h){
    CGAL_assertion(h->id()<map.ids.size());
    return map.ids[h->id()];
  }
  friend void put(Int_from_id_pmap<Handle> map, Handle h, int v){
    CGAL_assertion(h->id()<map.ids.size());
    map.ids[h->id()]=v;
  }
};

#endif // SWIG_CGAL_PMP_UTILS_H
