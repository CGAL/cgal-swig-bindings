#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBOR_COORDINATES_3_H
#define SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBOR_COORDINATES_3_H

//typedefs
%define Point_3_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Point_3,double>,std::pair<Point_3::cpp_base,double> > >  %enddef
%define Point_3_and_double_base std::pair<Point_3::cpp_base,double> %enddef
%define Point_3_and_double_wrapper std::pair<Point_3,double> %enddef
%{
  typedef boost::function_output_iterator< Container_writer<std::pair<Point_3,double>,std::pair<Point_3::cpp_base,double> > >  Point_3_and_double_output_iterator;
  typedef std::pair<Point_3::cpp_base,double> Point_3_and_double_base;
  typedef std::pair<Point_3,double> Point_3_and_double_wrapper;
%}

#ifdef SWIGPYTHON
Typemap_for_Input_iterator_additional_function(surface_neighbor_coordinates_certified_3)
Typemap_for_Input_iterator_additional_function(surface_neighbor_coordinates_3)
#endif

Typemap_for_Output_iterator(Point_3_and_double_output_iterator,Point_3_and_double_wrapper,Point_3_and_double,Point_3_and_double_base,SWIGTYPE_p_std__pairT_Point_3_double_t,"LCGAL/Interpolation/Point_3_and_double;")

std::pair<double, bool > surface_neighbor_coordinates_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out);
CGAL_SWIG::Triple<double, bool, bool > surface_neighbor_coordinates_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out);
CGAL_SWIG::Triple<double, bool, bool > surface_neighbor_coordinates_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,double max_distance,Point_3_and_double_output_iterator out);
std::pair< double, bool > surface_neighbor_coordinates_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out,const SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3>& start);
std::pair< double, bool > surface_neighbor_coordinates_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out);

%{
  std::pair<double, bool > surface_neighbor_coordinates_3 (Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out){
    return internal::extract_pair(CGAL::surface_neighbor_coordinates_3(range.first,range.second,p.get_data(),normal.get_data(),out,EPIC_Kernel()));
  }

  CGAL_SWIG::Triple<double, bool, bool > surface_neighbor_coordinates_certified_3 (Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out)  {
    return internal::extract_triple(CGAL::surface_neighbor_coordinates_certified_3(range.first,range.second,p.get_data(),normal.get_data(),out,EPIC_Kernel()));
  }

  CGAL_SWIG::Triple<double, bool, bool > surface_neighbor_coordinates_certified_3 (Point_range_3 range,const Point_3& p,const Vector_3& normal,double max_distance,Point_3_and_double_output_iterator out){
    return internal::extract_triple(CGAL::surface_neighbor_coordinates_certified_3(range.first,range.second,p.get_data(),normal.get_data(),max_distance,out,EPIC_Kernel()));
  }

  std::pair< double, bool > surface_neighbor_coordinates_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out,const SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3>& start){
    return internal::extract_pair(CGAL::surface_neighbor_coordinates_3(dt.get_data(),p.get_data(),normal.get_data(),out,start.get_data()));
  }

  std::pair< double, bool > surface_neighbor_coordinates_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_and_double_output_iterator out){
    return internal::extract_pair(CGAL::surface_neighbor_coordinates_3(dt.get_data(),p.get_data(),normal.get_data(),out));
  }
%}


#endif //SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBOR_COORDINATES_3_H
