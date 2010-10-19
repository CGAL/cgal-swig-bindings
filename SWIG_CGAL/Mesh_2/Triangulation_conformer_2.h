#ifndef SWIG_CGAL_MESH_2_TRIANGULATION_CONFORMER_2_H
#define SWIG_CGAL_MESH_2_TRIANGULATION_CONFORMER_2_H


template <class CDT_cpp,class CDT_wrapper>
class Triangulation_conformer_2_wrapper
{
  CGAL::Triangulation_conformer_2<CDT_cpp> data;
public:
  #ifndef SWIG
  typedef CGAL::Triangulation_conformer_2<CDT_cpp> cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Triangulation_conformer_2_wrapper(const cpp_base& base):data(base){}
  #endif

//Creation
  Triangulation_conformer_2_wrapper( CDT_wrapper& cdt):data(cdt.get_data_ref()){}
//Conforming methods
  FORWARD_CALL_0(void,make_conforming_Delaunay)
  FORWARD_CALL_0(void,make_conforming_Gabriel)
//Checking
  FORWARD_CALL_0(bool,is_conforming_Delaunay)
  FORWARD_CALL_0(bool,is_conforming_Gabriel)
//Step by step operations
  FORWARD_CALL_0(void,init_Delaunay)
  FORWARD_CALL_0(bool,step_by_step_conforming_Delaunay)
  FORWARD_CALL_0(void,init_Gabriel)
  FORWARD_CALL_0(bool,step_by_step_conforming_Gabriel)
  FORWARD_CALL_0(bool,is_conforming_done)
};

#endif //SWIG_CGAL_MESH_2_TRIANGULATION_CONFORMER_2_H
