// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_CLASSIFICATION_POINT_SET_FEATURE_GENERATOR_H
#define SWIG_CGAL_CLASSIFICATION_POINT_SET_FEATURE_GENERATOR_H

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>

#include <SWIG_CGAL/Point_set_3/Point_set_3.h>

template <typename Neighborhood_base>
class Point_set_neighbor_query_wrapper
{
public:
  typedef typename Neighborhood_base::K_neighbor_query K_neighbor_query;
  typedef typename Neighborhood_base::Sphere_neighbor_query Sphere_neighbor_query;

protected:

  std::shared_ptr<K_neighbor_query> k_base;
  std::shared_ptr<Sphere_neighbor_query> sphere_base;
  bool use_sphere_;

public:

#ifndef SWIG
  const K_neighbor_query& k_neighbor_query() const { return *k_base; }
        K_neighbor_query& k_neighbor_query()       { return *k_base; }
  const Sphere_neighbor_query& sphere_neighbor_query() const { return *sphere_base; }
        Sphere_neighbor_query& sphere_neighbor_query()       { return *sphere_base; }
  bool use_sphere() const { return use_sphere_; }

  Point_set_neighbor_query_wrapper (const K_neighbor_query& query)
    : k_base (new K_neighbor_query (query)), use_sphere_ (false) { }
  Point_set_neighbor_query_wrapper (const Sphere_neighbor_query& query)
    : sphere_base (new Sphere_neighbor_query (query)), use_sphere_ (true) { }
#endif

  Point_set_neighbor_query_wrapper() { }
};

template <typename Neighborhood_base>
class Point_set_neighborhood_wrapper
{
protected:
  const Neighborhood_base* data_ptr;

public:

#ifndef SWIG
  typedef Neighborhood_base cpp_base;
  const cpp_base& get_data() const { return *data_ptr; }
        cpp_base& get_data()       { return *data_ptr; }
  const cpp_base* ptr() { return data_ptr; }
#endif

  Point_set_neighborhood_wrapper (const Neighborhood_base& base)
    : data_ptr (&base) { }
  

  Point_set_neighbor_query_wrapper<Neighborhood_base> k_neighbor_query (int k)
  {
    return Point_set_neighbor_query_wrapper<Neighborhood_base> (data_ptr->k_neighbor_query(k));
  }

  Point_set_neighbor_query_wrapper<Neighborhood_base> sphere_neighbor_query (double radius)
  {
    return Point_set_neighbor_query_wrapper<Neighborhood_base> (data_ptr->sphere_neighbor_query(radius));
  }
};

template <typename Generator_base, typename Feature_set, typename Neighborhood>
class Point_set_feature_generator_wrapper
{
  SWIG_CGAL_INIT_WRAPPER_CLASS (Generator_base, data_sptr);

#ifndef SWIG
  class Color_map
  {
    typename Point_set_3_wrapper<CGAL_PS3>::Int_map r, g, b;

  public:

    typedef typename CGAL_PS3::Index key_type;
    typedef CGAL::Color value_type;
    typedef CGAL::Color reference;
    typedef boost::readable_property_map_tag category;

    Color_map() { }
    
    Color_map (typename Point_set_3_wrapper<CGAL_PS3>::Int_map r,
               typename Point_set_3_wrapper<CGAL_PS3>::Int_map g,
               typename Point_set_3_wrapper<CGAL_PS3>::Int_map b)
      : r(r), g(g), b(b) { }

    friend reference get (const Color_map& map, const key_type& idx)
    {
      return CGAL::Color ((unsigned char)(get(map.r.get_data(), idx)),
                          (unsigned char)(get(map.g.get_data(), idx)),
                          (unsigned char)(get(map.b.get_data(), idx)));
    }
  };
#endif

  Color_map color_map;

public:

  Point_set_feature_generator_wrapper (Point_set_3_wrapper<CGAL_PS3> point_set,
                                       int nb_scales, double voxel_size = -1.)
    : data_sptr (new Generator_base (point_set.get_data(),
                                     point_set.get_data().point_map(),
                                     nb_scales, voxel_size))
  { }


  void generate_point_based_features (Feature_set features)
  {
    data_sptr->generate_point_based_features (features.get_data());
  }

  void generate_normal_based_features (Feature_set features,
                                       typename Point_set_3_wrapper<CGAL_PS3>::Vector_map normal_map)
  {
    data_sptr->generate_normal_based_features (features.get_data(), normal_map.get_data());
  }

  void generate_color_based_features (Feature_set features,
                                      typename Point_set_3_wrapper<CGAL_PS3>::Int_map red_map,
                                      typename Point_set_3_wrapper<CGAL_PS3>::Int_map green_map,
                                      typename Point_set_3_wrapper<CGAL_PS3>::Int_map blue_map)
  {
    color_map = Color_map (red_map, green_map, blue_map);
    data_sptr->generate_color_based_features (features.get_data(), color_map);
  }

  void generate_echo_based_features (Feature_set features,
                                     typename Point_set_3_wrapper<CGAL_PS3>::Int_map echo_map)
  {
    data_sptr->generate_echo_based_features (features.get_data(), echo_map.get_data());
  }

  Neighborhood neighborhood (int scale = 0)
  {
    return Neighborhood (data_sptr->neighborhood(scale));
  }
  
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_scales)

  SWIG_CGAL_FORWARD_CALL_1(double, grid_resolution, int)
  SWIG_CGAL_FORWARD_CALL_1(double, radius_neighbors, int)
  SWIG_CGAL_FORWARD_CALL_1(double, radius_dtm, int)


};

#endif // SWIG_CGAL_CLASSIFICATION_POINT_SET_FEATURE_GENERATOR_H
