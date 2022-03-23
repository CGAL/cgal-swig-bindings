// ------------------------------------------------------------------------------
// Copyright (c) 2020 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_POINT_SET_3_POINT_SET_3_H
#define SWIG_CGAL_POINT_SET_3_POINT_SET_3_H

#include <boost/static_assert.hpp>

#include <SWIG_CGAL/Common/Reference_wrapper.h>
#include <SWIG_CGAL/Common/Macros.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Vector_3.h>
#include <SWIG_CGAL/Common/Iterator.h>

#include <SWIG_CGAL/Point_set_3/typedefs.h>
#include <SWIG_CGAL/Point_set_3/Point_set_3_Property_map.h>

#include <sstream>
#include <fstream>

template <typename Point_set_base, typename T>
struct Nested_iterator_helper
{
  typedef typename Point_set_base::template Property_range<T>::const_iterator type;
};

template <typename Point_set_base>
class Point_set_3_wrapper
{
protected:
  std::shared_ptr<Point_set_base> data_sptr;

public:

#ifndef SWIG
  typedef Point_set_base cpp_base;
  const cpp_base& get_data() const { return *data_sptr; }
        cpp_base& get_data()       { return *data_sptr; }
  std::shared_ptr<cpp_base> shared_ptr() { return data_sptr; }
#endif

  typedef Point_set_3_wrapper<Point_set_base> Self;
  typedef SWIG_CGAL_Iterator<typename Point_set_base::const_iterator, int> iterator;
  typedef SWIG_CGAL_Iterator<typename Point_set_base::Point_range::const_iterator, Point_3> Point_iterator;
  typedef SWIG_CGAL_Iterator<typename Point_set_base::Vector_range::const_iterator, Vector_3> Vector_iterator;

  typedef SWIG_CGAL_Iterator<typename Nested_iterator_helper<Point_set_base, int>::type, int> Int_iterator;
  typedef SWIG_CGAL_Iterator<typename Nested_iterator_helper<Point_set_base, double>::type, double> Float_iterator;

  typedef SWIG_Point_set_3::CGAL_Property_map<Point_set_base, Point_3> Point_map;
  typedef SWIG_Point_set_3::CGAL_Property_map<Point_set_base, Vector_3> Vector_map;
  typedef SWIG_Point_set_3::CGAL_Property_map<Point_set_base, int> Int_map;
  typedef SWIG_Point_set_3::CGAL_Property_map<Point_set_base, double> Float_map;

  Point_set_3_wrapper(bool with_normal_map = false) : data_sptr (new cpp_base(with_normal_map)) { }

  Point_set_3_wrapper(const std::string& file) : data_sptr (new cpp_base()) { read(file); }

  SWIG_CGAL_FORWARD_CALL_0(bool, is_empty)
  SWIG_CGAL_FORWARD_CALL_0(bool, empty)

  SWIG_CGAL_FORWARD_CALL_0(int, number_of_points)
  SWIG_CGAL_FORWARD_CALL_0(int, size)

  bool join (Self other)
  {
    return data_sptr->join (other.get_data());
  }
  
  SWIG_CGAL_FORWARD_CALL_0(void, clear)
  SWIG_CGAL_FORWARD_CALL_0(void, clear_properties)
  
  SWIG_CGAL_FORWARD_CALL_1(void, reserve, int)
  SWIG_CGAL_FORWARD_CALL_1(void, resize, int)
  
  int insert ()
  {
    return (int)(*(data_sptr->insert()));
  }
  
  int insert (const Point_3& point)
  {
    return (int)(*(data_sptr->insert(point.get_data())));
  }

  int insert (const Point_3& point, const Vector_3& normal)
  {
    return (int)(*(data_sptr->insert(point.get_data(), normal.get_data())));
  }

  int insert (const Self& other, int idx)
  {
    return (int)(*(data_sptr->insert(other.get_data(), idx)));
  }

  void insert_range (boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > range)
  {
    data_sptr->reserve (range->size());
    for (const auto& p : *range)
      data_sptr->insert(p);
  }

  iterator indices() { return iterator (get_data().begin(), get_data().end()); }
  SWIG_CGAL_FORWARD_CALL_1(Point_3, point, int)
  SWIG_CGAL_FORWARD_CALL_1(Vector_3, normal, int)

  SWIG_CGAL_FORWARD_CALL_1(void, remove, int)
  // void remove(iterator, iterator)
  SWIG_CGAL_FORWARD_CALL_1(bool, is_removed, int)
  iterator garbage() { return iterator (get_data().garbage_begin(), get_data().garbage_end()); }
  SWIG_CGAL_FORWARD_CALL_0(int, number_of_removed_points)
  SWIG_CGAL_FORWARD_CALL_0(int, garbage_size)
  SWIG_CGAL_FORWARD_CALL_0(bool, has_garbage)
  SWIG_CGAL_FORWARD_CALL_0(void, collect_garbage)
  SWIG_CGAL_FORWARD_CALL_0(void, cancel_removals)

  bool has_int_map (const std::string& name)
  {
    return data_sptr->template has_property_map<int>(name);
  }
  Int_map add_int_map (const std::string& name, int default_value = 0)
  {
    return Int_map(data_sptr->template add_property_map<int>(name, default_value));
  }
  Int_map int_map (const std::string& name)
  {
    return Int_map(data_sptr->template property_map<int>(name));
  }
  bool remove_int_map (Int_map map)
  {
    return data_sptr->remove_property_map (map.get_data());
  }

  bool has_float_map (const std::string& name)
  {
    return data_sptr->template has_property_map<double>(name);
  }
  Float_map add_float_map (const std::string& name, double default_value = 0.0)
  {
    return Float_map(data_sptr->template add_property_map<double>(name, default_value));
  }
  Float_map float_map (const std::string& name)
  {
    return Float_map(data_sptr->template property_map<double>(name));
  }
  bool remove_float_map (Float_map map)
  {
    return data_sptr->remove_property_map (map.get_data());
  }

  SWIG_CGAL_FORWARD_CALL_0(bool, has_normal_map)
  Vector_map add_normal_map() { return Vector_map (data_sptr->add_normal_map()); }
  Vector_map normal_map() { return Vector_map(data_sptr->normal_map(), data_sptr->has_normal_map()); }
  SWIG_CGAL_FORWARD_CALL_0(bool, remove_normal_map)
  Point_map point_map() { return Point_map(data_sptr->point_map(), true); }
  
  void copy_properties (const Self& other)
  {
    data_sptr->copy_properties (other.get_data());
  }

  boost::shared_ptr<std::vector<std::string> > properties() const
  {
    return boost::shared_ptr<std::vector<std::string> >
      (new std::vector<std::string>(data_sptr->properties()));
  }
  
  SWIG_CGAL_FORWARD_CALL_0(std::string, info)

  Int_iterator range (Int_map map)
  {
    return Int_iterator (get_data().range(map.get_data()).begin(),
                         get_data().range(map.get_data()).end());
  }

  Float_iterator range (Float_map map)
  {
    return Float_iterator (get_data().range(map.get_data()).begin(),
                           get_data().range(map.get_data()).end());
  }
  
  Point_iterator points() const { return Point_iterator (get_data().points().begin(), get_data().points().end()); }
  Vector_iterator normals() const { return Vector_iterator (get_data().normals().begin(), get_data().normals().end()); }

  void read (const std::string& file)
  {
    std::ifstream ifile (file, std::ios_base::binary);
    ifile >> *data_sptr;
    convert_input_properties();
  }

  bool write (const std::string& file)
  {
    std::string extension (file.begin() + file.size() - 3, file.end());
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    std::ofstream ofile (file, std::ios_base::binary);
    
    if (extension == "xyz")
    {
      ofile.precision(18);
      return CGAL::write_xyz_point_set (ofile, *data_sptr);
    }
    if (extension == "off")
    {
      ofile.precision(18);
      return CGAL::write_off_point_set (ofile, *data_sptr);
    }
    if (extension == "ply")
    {
      convert_ply_output_properties();
      CGAL::set_binary_mode(ofile);
      bool out = CGAL::write_ply_point_set (ofile, *data_sptr);
      convert_input_properties();
      return out;
    }
#ifdef CGAL_LINKED_WITH_LASLIB
    if (extension == "las")
    {
      convert_las_output_properties();
      bool out = CGAL::write_las_point_set (ofile, *data_sptr);
      convert_input_properties();
      return out;
    }
    std::cerr << "Error: unknown extension " << extension << ", possible values are xyz, off, ply or las" << std::endl;
#else
    std::cerr << "Error: unknown extension " << extension << ", possible values are xyz, off or ply" << std::endl;
#endif
      
    return false;
  }

private:

  void convert_input_properties()
  {
    std::vector<std::string> properties = data_sptr->properties();
    for (const std::string& p : properties)
    {
      if (convert_map<char, int>(p))
        continue;
      if (convert_map<signed char, int>(p))
        continue;
      if (convert_map<unsigned char, int>(p))
        continue;
      if (convert_map<short, int>(p))
        continue;
      if (convert_map<unsigned short, int>(p))
        continue;
      if (convert_map<unsigned int, int>(p))
        continue;
      if (convert_map<float, double>(p))
        continue;
    }
  }

  void convert_ply_output_properties()
  {
    std::vector<std::string> properties = data_sptr->properties();
    for (const std::string& p : properties)
      if (p == "R" || p == "r" || p == "red" ||
          p == "G" || p == "g" || p == "green" ||
          p == "B" || p == "b" || p == "blue" ||
          p == "A" || p == "a" || p == "alpha")
        convert_map<int, unsigned char>(p);
  }

  void convert_las_output_properties()
  {
    std::vector<std::string> properties = data_sptr->properties();
    for (const std::string& p : properties)
    {
      if (p == "intensity")
        convert_map<int, unsigned short>(p);
      else if (p == "return_number")
        convert_map<int, unsigned char>(p);
      else if (p == "number_of_returns")
        convert_map<int, unsigned char>(p);
      else if (p == "scan_direction_flag")
        convert_map<int, unsigned char>(p);
      else if (p == "edge_of_flight_line")
        convert_map<int, unsigned char>(p);
      else if (p == "classification")
        convert_map<int, unsigned char>(p);
      else if (p == "synthetic_flag")
        convert_map<int, unsigned char>(p);
      else if (p == "keypoint_flag")
        convert_map<int, unsigned char>(p);
      else if (p == "withheld_flag")
        convert_map<int, unsigned char>(p);
      else if (p == "scan_angle")
        convert_map<double, float>(p);
      else if (p == "user_data")
        convert_map<int, unsigned char>(p);
      else if (p == "point_source_ID")
        convert_map<int, unsigned short>(p);
      else if (p == "deleted_flag")
        convert_map<int, unsigned int>(p);
      else if (p == "R")
        convert_map<int, unsigned short>(p);
      else if (p == "G")
        convert_map<int, unsigned short>(p);
      else if (p == "B")
        convert_map<int, unsigned short>(p);
      else if (p == "I")
        convert_map<int, unsigned short>(p);
    }
  }

  template <typename Input, typename Output>
  bool convert_map (const std::string& name)
  {
    typename Point_set_base::template Property_map<Input> imap;
    bool okay;
    std::tie (imap, okay) = data_sptr->template property_map<Input>(name);
    if (!okay)
      return false;

    typename Point_set_base::template Property_map<Output> omap;
    std::tie (omap, okay) = data_sptr->template add_property_map<Output>(name);
    if (!okay)
      return false;
    
    for (typename Point_set_base::Index idx : *data_sptr)
      omap[idx] = static_cast<Output>(imap[idx]);
    data_sptr->remove_property_map(imap);
    return true;
  }

};

namespace CGAL { namespace Point_set_processing_3 {

template <typename T> class GetFt;

template <typename Point_set_base>
class GetFt<Point_set_3_wrapper<Point_set_base> >
{
public:
  typedef double type;
};
} }

#endif // SWIG_CGAL_POINT_SET_3_POINT_SET_3_H

