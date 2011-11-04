#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_REGULAR_NEIGHBOR_COORDINATES_2_I
#define SWIG_CGAL_INTERPOLATION_DECLARE_REGULAR_NEIGHBOR_COORDINATES_2_I

//typedefs
%define Weighted_point_2_and_double_output_iterator boost::function_output_iterator< Container_writer<std::pair<Weighted_point_2,double>,std::pair<Weighted_point_2::cpp_base,double> > >  %enddef
%define RT2_wrapper Regular_triangulation_2_wrapper<CGAL_RT2,SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2> > %enddef
%define RT2_Edge_wrapper std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>%enddef
%define RT2_Edge_iterator   std::pair<Input_iterator_wrapper<RT2_Edge_wrapper,CGAL_RT2::Edge>,Input_iterator_wrapper<RT2_Edge_wrapper,CGAL_RT2::Edge> > %enddef
%define RT2_Vertex_wrapper SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2> %enddef
%define RT2_Vertex_iterator std::pair<Input_iterator_wrapper<RT2_Vertex_wrapper,CGAL_RT2::Vertex_handle>,Input_iterator_wrapper<RT2_Vertex_wrapper,CGAL_RT2::Vertex_handle> > %enddef

%{
  typedef boost::function_output_iterator< Container_writer<std::pair<Weighted_point_2,double>,std::pair<Weighted_point_2::cpp_base,double> > > Weighted_point_2_and_double_output_iterator;
  typedef Regular_triangulation_2_wrapper<CGAL_RT2,SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2>,SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2> > RT2_wrapper;
  typedef std::pair<Weighted_point_2,double> Weighted_point_2_and_double_wrapper;
  typedef std::pair<Weighted_point_2::cpp_base,double> Weighted_point_2_and_double_base;
  typedef std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int> RT2_Edge_wrapper;
  typedef SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2>              RT2_Vertex_wrapper;
  typedef std::pair<Input_iterator_wrapper<RT2_Edge_wrapper,CGAL_RT2::Edge>,Input_iterator_wrapper<RT2_Edge_wrapper,CGAL_RT2::Edge> > RT2_Edge_iterator;
  typedef std::pair<Input_iterator_wrapper<RT2_Vertex_wrapper,CGAL_RT2::Vertex_handle>,Input_iterator_wrapper<RT2_Vertex_wrapper,CGAL_RT2::Vertex_handle> > RT2_Vertex_iterator;
%}


SWIG_CGAL_output_iterator_typemap_in(Weighted_point_2_and_double_output_iterator,Weighted_point_2_and_double_wrapper,Weighted_point_2_and_double,Weighted_point_2_and_double_base,SWIGTYPE_p_std__pairT_Weighted_point_2_double_t,"LCGAL/Interpolation/Weighted_point_2_and_double;")
SWIG_CGAL_input_iterator_typemap_in(RT2_Edge_iterator,RT2_Edge_wrapper,Regular_triangulation_2_Edge,CGAL_RT2::Edge,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_RT2_Weighted_point_2_t_int_t,"(LCGAL/Triangulation_2/Regular_triangulation_2_Edge;)J",regular_neighbor_coordinates_2)
SWIG_CGAL_input_iterator_typemap_in(RT2_Vertex_iterator,RT2_Vertex_wrapper,Regular_triangulation_2_Vertex_handle,CGAL_RT2::Vertex_handle,SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_RT2_Weighted_point_2_t_int_t,"(LCGAL/Triangulation_2/Regular_triangulation_2_Vertex_handle;)J",regular_neighbor_coordinates_2)

std::pair<double,bool> regular_neighbor_coordinates_2(const RT2_wrapper& dt,const Weighted_point_2& p,Weighted_point_2_and_double_output_iterator out,const SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>& start);
std::pair<double,bool> regular_neighbor_coordinates_2(const RT2_wrapper& dt,const Weighted_point_2& p,Weighted_point_2_and_double_output_iterator out);
std::pair<double,bool> regular_neighbor_coordinates_2(const RT2_wrapper& dt,const SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2>& vh,Weighted_point_2_and_double_output_iterator out);
std::pair<double,bool> regular_neighbor_coordinates_2(const RT2_wrapper& dt,const Weighted_point_2& p,Weighted_point_2_and_double_output_iterator out,RT2_Edge_iterator its,RT2_Vertex_iterator its_v);
#ifdef SWIGPYTHON
//to have the type SWIGTYPE_p_std__pairT_SWIG_Triangulation_2__CGAL_Face_handleT_CGAL_RT2_Weighted_point_2_t_int_t defined
%types(std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>*, std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>);
%template() std::pair<SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>,int>;
#endif

%{
  std::pair<double,bool> 
  regular_neighbor_coordinates_2(const RT2_wrapper& dt,const Weighted_point_2& p,Weighted_point_2_and_double_output_iterator out,const SWIG_Triangulation_2::CGAL_Face_handle<CGAL_RT2,Weighted_point_2>& start)
  {
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,start.get_data()) );
  }

  std::pair<double,bool> 
  regular_neighbor_coordinates_2(const RT2_wrapper& dt,const Weighted_point_2& p,Weighted_point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),p.get_data(),out) );
  }

  std::pair<double,bool>
  regular_neighbor_coordinates_2(const RT2_wrapper& dt,const Weighted_point_2& p,Weighted_point_2_and_double_output_iterator out,RT2_Edge_iterator erange,RT2_Vertex_iterator vrange)
  {
    //we need to make a copy as the algorithm uses operator-- on the iterator, which is not defined in our case.
    std::list<CGAL_RT2::Edge> edges;
    std::copy(erange.first,erange.second,std::back_inserter(edges));
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),p.get_data(),out,edges.begin(),edges.end(),vrange.first,vrange.second) );
  }
  
  std::pair<double,bool> 
  regular_neighbor_coordinates_2(const RT2_wrapper& dt,const SWIG_Triangulation_2::CGAL_Vertex_handle<CGAL_RT2,Weighted_point_2>& vh,Weighted_point_2_and_double_output_iterator out)
  {
    return internal::extract_pair( CGAL::regular_neighbor_coordinates_2(dt.get_data(),vh.get_data(),out) );
  }
%}

#endif // SWIG_CGAL_INTERPOLATION_DECLARE_REGULAR_NEIGHBOR_COORDINATES_2_I
