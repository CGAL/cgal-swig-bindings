// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_POLYLINE_SIMPLIFICATION_2_H
#define SWIG_CGAL_POLYLINE_SIMPLIFICATION_2_H

// Cost functors
#include <CGAL/Polyline_simplification_2/Hybrid_squared_distance_cost.h>
#include <CGAL/Polyline_simplification_2/Scaled_squared_distance_cost.h>
#include <CGAL/Polyline_simplification_2/Squared_distance_cost.h>

template <class CDTP2_cpp>
struct Hybrid_squared_distance_cost_wrapper{
  #ifndef SWIG
  typedef typename CGAL::Polyline_simplification_2::Hybrid_squared_distance_cost<double> cpp_base;
  cpp_base data;
  cpp_base& get_data(){ return data; }
  const cpp_base& get_data() const { return data; }
  Hybrid_squared_distance_cost_wrapper(const cpp_base& base): data(base) {}
  Hybrid_squared_distance_cost_wrapper():data(0) {}
  #endif
  Hybrid_squared_distance_cost_wrapper(double ratio):data(ratio){}
};

template <class CDTP2_cpp>
struct Scaled_squared_distance_cost_wrapper{
  #ifndef SWIG
  typedef typename CGAL::Polyline_simplification_2::Scaled_squared_distance_cost cpp_base;
  cpp_base data;
  cpp_base& get_data(){ return data; }
  const cpp_base& get_data() const { return data; }
  Scaled_squared_distance_cost_wrapper(const cpp_base& base): data(base) {}
  #endif
  Scaled_squared_distance_cost_wrapper(){}
};

template <class CDTP2_cpp>
struct Squared_distance_cost_wrapper{
  #ifndef SWIG
  typedef typename CGAL::Polyline_simplification_2::Squared_distance_cost cpp_base;
  cpp_base data;
  cpp_base& get_data(){ return data; }
  const cpp_base& get_data() const { return data; }
  Squared_distance_cost_wrapper(const cpp_base& base): data(base) {}
  #endif
  Squared_distance_cost_wrapper(){}
};


#include <CGAL/Polyline_simplification_2/Stop_above_cost_threshold.h>
#include <CGAL/Polyline_simplification_2/Stop_below_count_ratio_threshold.h>
#include <CGAL/Polyline_simplification_2/Stop_below_count_threshold.h>

template <class CDTP2_cpp>
struct Stop_above_cost_threshold_wrapper{
  #ifndef SWIG
  typedef typename CGAL::Polyline_simplification_2::Stop_above_cost_threshold cpp_base;
  cpp_base data;
  cpp_base& get_data(){ return data; }
  const cpp_base& get_data() const { return data; }
  Stop_above_cost_threshold_wrapper(const cpp_base& base): data(base) {}
  Stop_above_cost_threshold_wrapper(){} // needed by SWIG
  #endif
  Stop_above_cost_threshold_wrapper(double threshold): data(threshold) {}
};

template <class CDTP2_cpp>
struct Stop_below_count_ratio_threshold_wrapper{
  #ifndef SWIG
  typedef typename CGAL::Polyline_simplification_2::Stop_below_count_ratio_threshold cpp_base;
  cpp_base data;
  cpp_base& get_data(){ return data; }
  const cpp_base& get_data() const { return data; }
  Stop_below_count_ratio_threshold_wrapper(const cpp_base& base): data(base) {}
  Stop_below_count_ratio_threshold_wrapper(){} // needed by SWIG
  #endif
  Stop_below_count_ratio_threshold_wrapper(double threshold): data(threshold) {}
};

template <class CDTP2_cpp>
struct Stop_below_count_threshold_wrapper{
  #ifndef SWIG
  typedef typename CGAL::Polyline_simplification_2::Stop_below_count_threshold cpp_base;
  cpp_base data;
  cpp_base& get_data(){ return data; }
  const cpp_base& get_data() const { return data; }
  Stop_below_count_threshold_wrapper(const cpp_base& base): data(base) {}
  Stop_below_count_threshold_wrapper(){} // needed by SWIG
  #endif
  Stop_below_count_threshold_wrapper(int threshold): data(threshold) {}
};

#endif //SWIG_CGAL_POLYLINE_SIMPLIFICATION_2_H
