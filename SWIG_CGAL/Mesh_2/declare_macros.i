#ifndef SWIG_CGAL_MESH_2_DECLARE_MACROS_I
#define SWIG_CGAL_MESH_2_DECLARE_MACROS_I


%define declare_conforming_global_functions(CDTWRAPPER)
  void make_conforming_Delaunay_2(CDTWRAPPER& cdt);
  void make_conforming_Gabriel_2(CDTWRAPPER& cdt);

  %{
    void make_conforming_Delaunay_2(CDTWRAPPER& cdt)
    {
      CGAL::make_conforming_Delaunay_2(cdt.get_data_ref());
    }
    void make_conforming_Gabriel_2(CDTWRAPPER& cdt){
      CGAL::make_conforming_Gabriel_2(cdt.get_data_ref());
    }
  %}
%enddef

#endif //SWIG_CGAL_MESH_2_DECLARE_MACROS_I
