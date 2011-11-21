#ifndef SWIG_CGAL_MESH_2_DECLARE_MACROS_I
#define SWIG_CGAL_MESH_2_DECLARE_MACROS_I


%define declare_conforming_global_functions(CDTWRAPPER)
  void make_conforming_Delaunay_2(CDTWRAPPER& cdt);
  void make_conforming_Gabriel_2(CDTWRAPPER& cdt);

  %{
    void make_conforming_Delaunay_2(CDTWRAPPER& cdt)
    {
      CGAL::make_conforming_Delaunay_2(cdt.get_data());
    }
    void make_conforming_Gabriel_2(CDTWRAPPER& cdt){
      CGAL::make_conforming_Gabriel_2(cdt.get_data());
    }
  %}
%enddef

%define declare_refine_global_functions(CRITERIA)
  void refine_Delaunay_mesh_2 (M2_CDT_wrapper& t, CRITERIA criteria);
  void refine_Delaunay_mesh_2 (M2_CDT_wrapper& t,Point_range range,CRITERIA criteria,bool mark);
  void refine_Delaunay_mesh_2 (M2_CDT_wrapper& t,Point_range range,CRITERIA criteria);

  %{
    void refine_Delaunay_mesh_2 (M2_CDT_wrapper& t, CRITERIA criteria)
    {
      CGAL::refine_Delaunay_mesh_2(t.get_data(),criteria.get_data());
    }
    void refine_Delaunay_mesh_2 (M2_CDT_wrapper& t,Point_range range,CRITERIA criteria,bool mark)
    {
      CGAL::refine_Delaunay_mesh_2(t.get_data(),range.first,range.second,criteria.get_data(),mark);
    }    
    void refine_Delaunay_mesh_2 (M2_CDT_wrapper& t,Point_range range,CRITERIA criteria)
    {
      CGAL::refine_Delaunay_mesh_2(t.get_data(),range.first,range.second,criteria.get_data());
    }
  %} 
%enddef  

#endif //SWIG_CGAL_MESH_2_DECLARE_MACROS_I
