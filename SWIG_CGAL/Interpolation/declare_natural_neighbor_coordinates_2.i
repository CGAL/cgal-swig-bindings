#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_NATURAL_NEIGHBOR_COORDINATES_2_I
#define SWIG_CGAL_INTERPOLATION_DECLARE_NATURAL_NEIGHBOR_COORDINATES_2_I

//typedefs
%define Point_2_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > >  %enddef
%define DT2_wrapper Delaunay_triangulation_2_wrapper<CGAL_DT2,SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2> > %enddef
%define DT2_Edge_wrapper std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>%enddef
%define DT2_Edge_iterator std::pair<Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge>,Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge> > %enddef

%{
  typedef boost::function_output_iterator< Container_writer<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > > Point_2_and_double_output_iterator;
  typedef Delaunay_triangulation_2_wrapper<CGAL_DT2,SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2> > DT2_wrapper;
  typedef std::pair<Point_2,double> Point_2_and_double_wrapper;
  typedef std::pair<Point_2::cpp_base,double> Point_2_and_double_base;
  typedef std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int> DT2_Edge_wrapper;
  typedef std::pair<Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge>,Input_iterator_wrapper<DT2_Edge_wrapper,CGAL_DT2::Edge> > DT2_Edge_iterator;
%}


Typemap_for_Output_iterator(Point_2_and_double_output_iterator,Point_2_and_double_wrapper,Point_2_and_double,Point_2_and_double_base,SWIGTYPE_p_std__pairT_Point_2_double_t,"LCGAL/Interpolation/Point_2_and_double;")
Typemap_for_Input_iterator(DT2_Edge_iterator,DT2_Edge_wrapper,Delaunay_triangulation_2_Edge,CGAL_DT2::Edge,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_DT2_Point_2_t_int_t,"(LCGAL/Triangulation_2/Delaunay_triangulation_2_Edge;)J",natural_neighbor_coordinates_2)

std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,const SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>& start);
std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out);
std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>& vh,Point_2_and_double_output_iterator out);
std::pair<double,bool> natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,DT2_Edge_iterator its);
#ifdef SWIGPYTHON
//to have the type SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_DT2_Point_2_t_int_t defined
%types(std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>*, std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>);
%template() std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>,int>;
#endif
%{
  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,const SWIG_Triangulation_2::CGAL_Face_handle<CGAL_DT2,Point_2>& start)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,start.get_data()) );
  }

  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out) );
  }

  std::pair<double,bool>
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const Point_2& p,Point_2_and_double_output_iterator out,DT2_Edge_iterator its)
  {
    //we need to make a copy as the algorithm uses operator-- on the iterator, which is not defined in our case.
    std::list<CGAL_DT2::Edge> edges;
    std::copy(its.first,its.second,std::back_inserter(edges));
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,edges.begin(),edges.end()) );
  }
  
  std::pair<double,bool> 
  natural_neighbor_coordinates_2(const DT2_wrapper& dt,const SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_DT2,Point_2>& vh,Point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::natural_neighbor_coordinates_2(dt.get_data(),vh.get_data(),out) );
  }
%}

#endif // SWIG_CGAL_INTERPOLATION_DECLARE_NATURAL_NEIGHBOR_COORDINATES_2_I
