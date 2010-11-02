#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBORS_3_H
#define SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBORS_3_H

//typedefs
%define Point_3_output_iterator boost::function_output_iterator< Container_writer<Point_3,Point_3::cpp_base > >  %enddef
%define DT3_wrapper Delaunay_triangulation_3_wrapper<CGAL_DT3,SWIG_Triangulation_3::CGAL_Vertex_handle<CGAL_DT3,Point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3> > %enddef
%define Point_range_3 std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > %enddef

%{
typedef boost::function_output_iterator< Container_writer<Point_3,Point_3::cpp_base > > Point_3_output_iterator;
typedef Delaunay_triangulation_3_wrapper<CGAL_DT3,SWIG_Triangulation_3::CGAL_Vertex_handle<CGAL_DT3,Point_3>,SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3> > DT3_wrapper;
typedef std::pair<Input_iterator_wrapper<Point_3,Point_3::cpp_base>,Input_iterator_wrapper<Point_3,Point_3::cpp_base> > Point_range_3;
%}

Typemap_for_Input_iterator(Point_range_3,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",surface_neighbors_3)
#ifdef SWIGPYTHON
Typemap_for_Input_iterator_additional_function(surface_neighbors_certified_3)
#endif

Typemap_for_Output_iterator(Point_3_output_iterator,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"LCGAL/Kernel/Point_3;")

void surface_neighbors_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out);
bool surface_neighbors_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out);
bool surface_neighbors_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,double max_distance,Point_3_output_iterator out);
void surface_neighbors_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out,const SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3>& start);
void surface_neighbors_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out);
%{
  void surface_neighbors_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out){
    CGAL::surface_neighbors_3(range.first,range.second,p.get_data(),normal.get_data(),out,EPIC_Kernel());
  }
  
  bool surface_neighbors_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out){
    return CGAL::surface_neighbors_certified_3(range.first,range.second,p.get_data(),normal.get_data(),out,EPIC_Kernel()).second;
  }

  bool surface_neighbors_certified_3(Point_range_3 range,const Point_3& p,const Vector_3& normal,double max_distance,Point_3_output_iterator out){
    return CGAL::surface_neighbors_certified_3(range.first,range.second,p.get_data(),normal.get_data(),max_distance,out,EPIC_Kernel()).second;
  }
  
  void surface_neighbors_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out,const SWIG_Triangulation_3::CGAL_Cell_handle<CGAL_DT3,Point_3>& start){
    CGAL::surface_neighbors_3(dt.get_data(),p.get_data(),normal.get_data(),out,start.get_data());
  }
  
  void surface_neighbors_3(const DT3_wrapper& dt,const Point_3& p,const Vector_3& normal,Point_3_output_iterator out){
    CGAL::surface_neighbors_3(dt.get_data(),p.get_data(),normal.get_data(),out);
  }
  
%}

#endif //SWIG_CGAL_INTERPOLATION_DECLARE_SURFACE_NEIGHBORS_3_H
