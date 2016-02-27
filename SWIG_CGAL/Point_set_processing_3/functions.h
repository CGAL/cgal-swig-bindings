// ------------------------------------------------------------------------------
// Copyright (c) 2013 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------

#ifndef SWIG_CGAL_POINT_SET_PROCESSING_3_H
#define SWIG_CGAL_POINT_SET_PROCESSING_3_H

#include <SWIG_CGAL/Common/Wrapper_iterator_helper.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>

#include <CGAL/compute_average_spacing.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/jet_smooth_point_set.h>
#include <CGAL/jet_estimate_normals.h>
#include <CGAL/remove_outliers.h>
#include <CGAL/pca_estimate_normals.h>
#include <CGAL/random_simplify_point_set.h>
#include <CGAL/mst_orient_normals.h>
#include <CGAL/IO/read_xyz_points.h>
#include <CGAL/IO/read_off_points.h>
#include <CGAL/IO/write_xyz_points.h>
#include <CGAL/IO/write_off_points.h>


#if CGAL_VERSION_NR >= 1040800000
#define DFT <CGAL::Sequential_tag>
#else
#define DFT
#endif

double compute_average_spacing(Wrapper_iterator_helper<Point_3>::input point_range, int k)
{
  return CGAL::compute_average_spacing DFT (point_range.first, point_range.second, k);
}

/// Simplification functions
int grid_simplify_point_set ( Wrapper_iterator_helper<Point_3>::input point_range, double epsilon )
{
  typedef Wrapper_iterator_helper<Point_3>::input::first_type Iterator;
  std::vector<Point_3::cpp_base*> points_ptr;
//save the pointer to the original points
  for (Iterator it=point_range.first; it!=point_range.second; ++it)
    points_ptr.push_back( &(*it) );
//make a copy of the points to apply the algorithm on
  std::size_t nb_pts=points_ptr.size();
  std::vector<Point_3::cpp_base> points;
  points.reserve(nb_pts);
  for (std::size_t i=0; i<nb_pts; ++i) points.push_back( *points_ptr[i] );
//CGAL function call
  std::vector<Point_3::cpp_base>::iterator result =
    CGAL::grid_simplify_point_set(points.begin(), points.end(), epsilon);
//copy the points back into the original points
  for (std::size_t i=0; i<nb_pts; ++i) *points_ptr[i] = points[i];

  return (int) std::distance(points.begin(), result);
}

int random_simplify_point_set ( Wrapper_iterator_helper<Point_3>::input point_range, double removed_percentage )
{
  typedef Wrapper_iterator_helper<Point_3>::input::first_type Iterator;
  std::vector<Point_3::cpp_base*> points_ptr;
//save the pointer to the original points
  for (Iterator it=point_range.first; it!=point_range.second; ++it)
    points_ptr.push_back( &(*it) );
//make a copy of the points to apply the algorithm on
  std::size_t nb_pts=points_ptr.size();
  std::vector<Point_3::cpp_base> points;
  points.reserve(nb_pts);
  for (std::size_t i=0; i<nb_pts; ++i) points.push_back( *points_ptr[i] );
//CGAL function call
  std::vector<Point_3::cpp_base>::iterator result =
    CGAL::random_simplify_point_set(points.begin(), points.end(), removed_percentage);
//copy the points back into the original points
  for (std::size_t i=0; i<nb_pts; ++i) *points_ptr[i] = points[i];

  return (int) std::distance(points.begin(), result);
}


int remove_outliers (Wrapper_iterator_helper<Point_3>::input point_range, int k, double threshold_percent)
{
  typedef Wrapper_iterator_helper<Point_3>::input::first_type Iterator;
  std::vector<Point_3::cpp_base*> points_ptr;
//save the pointer to the original points
  for (Iterator it=point_range.first; it!=point_range.second; ++it)
    points_ptr.push_back( &(*it) );
//make a copy of the points to apply the algorithm on
  std::size_t nb_pts=points_ptr.size();
  std::vector<Point_3::cpp_base> points;
  points.reserve(nb_pts);
  for (std::size_t i=0; i<nb_pts; ++i) points.push_back( *points_ptr[i] );
//CGAL function call
  std::vector<Point_3::cpp_base>::iterator result =
    CGAL::remove_outliers(points.begin(), points.end(), k, threshold_percent);
//copy the points back into the original points
  for (std::size_t i=0; i<nb_pts; ++i) *points_ptr[i] = points[i];

  return (int) std::distance(points.begin(), result);
}

/// Smoothing functions
void jet_smooth_point_set (Wrapper_iterator_helper<Point_3>::input point_range,unsigned int nb_neighbors, unsigned int degree_fitting=2, unsigned int degree_monge=2)
{
  typedef Wrapper_iterator_helper<Point_3>::input::first_type Iterator;
  std::vector<Point_3::cpp_base*> points_ptr;
//save the pointer to the original points
  for (Iterator it=point_range.first; it!=point_range.second; ++it)
    points_ptr.push_back( &(*it) );
//make a copy of the points to apply the algorithm on
  std::size_t nb_pts=points_ptr.size();
  std::vector<Point_3::cpp_base> points;
  points.reserve(nb_pts);
  for (std::size_t i=0; i<nb_pts; ++i) points.push_back( *points_ptr[i] );
//CGAL function call
  CGAL::jet_smooth_point_set DFT (points.begin(), points.end(), nb_neighbors, degree_fitting, degree_monge);
//copy the points back into the original points
  for (std::size_t i=0; i<nb_pts; ++i) *points_ptr[i] = points[i];
}

/// Normal estimation functions
void jet_estimate_normals (Wrapper_iterator_helper<Point_3>::input point_range, Wrapper_iterator_helper<Vector_3>::output normal_writer, unsigned int k, unsigned int degree_fitting=2)
{
  std::vector< std::pair<Point_3::cpp_base, Vector_3::cpp_base> > input;
  typedef Wrapper_iterator_helper<Point_3>::input::first_type Iterator;
  Vector_3::cpp_base normal = Vector_3::cpp_base();
  for (Iterator it=point_range.first; it!=point_range.second; ++it)
    input.push_back( std::make_pair(*it, normal) );

  CGAL::First_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Second_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;
  CGAL::jet_estimate_normals DFT (input.begin(), input.end(), point_pmap, normal_pmap, k, degree_fitting );

  //copy the normal inside the output iterator
  std::size_t nb_pts=input.size();
  for(std::size_t i=0; i<nb_pts; ++i) *normal_writer++=input[i].second;
}

int mst_orient_normals (Wrapper_iterator_helper<Point_3>::input point_range, Wrapper_iterator_helper<Vector_3>::input normal_range, unsigned int k)
{
  std::vector< std::pair<Point_3::cpp_base, Vector_3::cpp_base> > input;
  std::vector< std::pair<Point_3::cpp_base*, Vector_3::cpp_base*> > ptrs;

  typedef Wrapper_iterator_helper<Point_3>::input::first_type PointIterator;
  typedef Wrapper_iterator_helper<Vector_3>::input::first_type VectorIterator;

  VectorIterator nit=normal_range.first;
  for (PointIterator pit=point_range.first; pit!=point_range.second; ++pit, ++nit)
  {
    input.push_back( std::make_pair(*pit, *nit) );
    ptrs.push_back( std::make_pair(&(*pit), &(*nit)) );
  }

  CGAL::First_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Second_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;

  std::vector< std::pair<Point_3::cpp_base, Vector_3::cpp_base> >::iterator result =
    CGAL::mst_orient_normals(input.begin(), input.end(), point_pmap, normal_pmap, k);

  //copy the normal inside the output iterator
  std::size_t nb_pts=input.size();
  for(std::size_t i=0; i<nb_pts; ++i)
  {
    *ptrs[i].first=input[i].first;
    *ptrs[i].second=input[i].second;
  }

  return (int) std::distance(input.begin(), result);
}

void pca_estimate_normals (Wrapper_iterator_helper<Point_3>::input point_range, Wrapper_iterator_helper<Vector_3>::output normal_writer, unsigned int k)
{
  std::vector< std::pair<Point_3::cpp_base, Vector_3::cpp_base> > input;
  typedef Wrapper_iterator_helper<Point_3>::input::first_type Iterator;
  Vector_3::cpp_base normal = Vector_3::cpp_base();
  for (Iterator it=point_range.first; it!=point_range.second; ++it)
    input.push_back( std::make_pair(*it, normal) );

  CGAL::First_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Second_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;
  CGAL::pca_estimate_normals DFT (input.begin(), input.end(), point_pmap, normal_pmap, k);

  //copy the normal inside the output iterator
  std::size_t nb_pts=input.size();
  for(std::size_t i=0; i<nb_pts; ++i) *normal_writer++=input[i].second;
}


/// I/O functions on points
#include <fstream>

#ifndef SWIG
namespace CGAL{

template <>
struct value_type_traits< Wrapper_iterator_helper< ::Point_3 >::output >
{
  typedef ::Point_3::cpp_base type;
};

}
#endif //SWIG


bool read_off_points(const char* fname, Wrapper_iterator_helper<Point_3>::output output)
{
  std::ifstream input(fname);
  return CGAL::read_off_points(input, output);
}

bool read_xyz_points (const char* fname, Wrapper_iterator_helper<Point_3>::output output)
{
  std::ifstream input(fname);
  return CGAL::read_xyz_points(input, output);
}

bool write_off_points (const char* fname, Wrapper_iterator_helper<Point_3>::input input)
{
  std::ofstream output(fname);
  return CGAL::write_off_points(output, input.first, input.second);
}

bool write_xyz_points (const char* fname, Wrapper_iterator_helper<Point_3>::input input)
{
  std::ofstream output(fname);
  return CGAL::write_xyz_points(output, input.first, input.second);
}

/// I/O functions on points and normals

#ifndef SWIG

//VP stands for value_type_pair, OP for OutputIterator_pair
template <class VP, class OP>
class Pair_dispatch_output_iterator: public OP{
  typedef Pair_dispatch_output_iterator<VP,OP> Self;

public:
  typedef VP Value_type_tuple;
  typedef OP Iterator_tuple;
  typedef std::output_iterator_tag iterator_category;
  typedef Value_type_tuple         value_type; //hack to avoid the need of value_type_traits specialization
  typedef void                     difference_type;
  typedef void                     pointer;
  typedef void                     reference;


  Self& operator*(){ return *this; }
  Self& operator++(){ return *this; }
  Self& operator++(int){ return *this; }

  Pair_dispatch_output_iterator(typename OP::first_type out1, typename OP::second_type out2):OP(out1,out2){}

  //Added because required by MSVC10
  Pair_dispatch_output_iterator(const Self& other):
    Iterator_tuple(static_cast<const Iterator_tuple&>(other))
  {}

  Self& operator=(const VP& pair){
    *(this->first)++=pair.first;
    *(this->second)++=pair.second;
    return *this;
  }

  Self& operator=(const Self& s){
    static_cast< Iterator_tuple& >(*this) = static_cast< const Iterator_tuple& >(s);
    return *this;
  }
};
#endif //SWIG

#include <CGAL/iterator.h>
bool read_xyz_points_and_normals (const char* fname, Wrapper_iterator_helper<Point_3>::output point_writer, Wrapper_iterator_helper<Vector_3>::output normal_writer)
{
  typedef Pair_dispatch_output_iterator<
    std::pair< Point_3::cpp_base, Vector_3::cpp_base >,
    std::pair< Wrapper_iterator_helper<Point_3>::output, Wrapper_iterator_helper<Vector_3>::output >
  > OutputIterator;

  std::ifstream input(fname);
  CGAL::First_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Second_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;
  return CGAL::read_xyz_points_and_normals(input, OutputIterator(point_writer, normal_writer), point_pmap, normal_pmap);
}

bool read_off_points_and_normals (const char* fname, Wrapper_iterator_helper<Point_3>::output point_writer, Wrapper_iterator_helper<Vector_3>::output normal_writer)
{
  typedef Pair_dispatch_output_iterator<
    std::pair< Point_3::cpp_base, Vector_3::cpp_base >,
    std::pair< Wrapper_iterator_helper<Point_3>::output, Wrapper_iterator_helper<Vector_3>::output >
  > OutputIterator;

  std::ifstream input(fname);
  CGAL::First_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Second_of_pair_property_map< std::pair<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;
  return CGAL::read_off_points_and_normals(input, OutputIterator(point_writer, normal_writer), point_pmap, normal_pmap);
}

#include <boost/iterator/zip_iterator.hpp>
bool write_off_points_and_normals (const char* fname, Wrapper_iterator_helper<Point_3>::input points, Wrapper_iterator_helper<Vector_3>::input normals)
{
  std::ofstream output(fname);
  CGAL::Nth_of_tuple_property_map< 0, boost::tuple<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Nth_of_tuple_property_map< 1, boost::tuple<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;
  return CGAL::write_off_points_and_normals(  output,
                                              boost::make_zip_iterator(boost::make_tuple(points.first, normals.first)),
                                              boost::make_zip_iterator(boost::make_tuple(points.second, normals.second)),
                                              point_pmap, normal_pmap );
}

bool write_xyz_points_and_normals (const char* fname, Wrapper_iterator_helper<Point_3>::input points, Wrapper_iterator_helper<Vector_3>::input normals)
{
  std::ofstream output(fname);
  CGAL::Nth_of_tuple_property_map< 0, boost::tuple<Point_3::cpp_base, Vector_3::cpp_base > > point_pmap;
  CGAL::Nth_of_tuple_property_map< 1, boost::tuple<Point_3::cpp_base, Vector_3::cpp_base > > normal_pmap;
  return CGAL::write_xyz_points_and_normals(  output,
                                              boost::make_zip_iterator(boost::make_tuple(points.first, normals.first)),
                                              boost::make_zip_iterator(boost::make_tuple(points.second, normals.second)),
                                              point_pmap, normal_pmap );
}

#undef DFT

#endif //SWIG_CGAL_POINT_SET_PROCESSING_3_H
