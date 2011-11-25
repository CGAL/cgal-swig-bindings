#ifndef SWIG_CGAL_MESH_2_DELAUNAY_MESHER_2_H
#define SWIG_CGAL_MESH_2_DELAUNAY_MESHER_2_H

#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Triangulation_2/triangulation_handles.h>


SWIG_CGAL_DECLARE_ITERATOR_CLASS(Seeds_const_iterator)

typedef std::pair<Input_iterator_wrapper<Point_2,Point_2::cpp_base>,Input_iterator_wrapper<Point_2,Point_2::cpp_base> > Point_range;

template <class CDT_wrapper>
struct DM2_Input_iterator_helper
{
  typedef SWIG_Triangulation_2::CGAL_Face_handle<typename CDT_wrapper::cpp_base,Point_2> Face_handle;
  typedef std::pair<Input_iterator_wrapper<Face_handle,typename Face_handle::cpp_base>,Input_iterator_wrapper<Face_handle,typename Face_handle::cpp_base> > range;  
};

template <class Cpp,class CDT_wrapper,class Criteria_wrapper>
class Delaunay_mesher_2_wrapper
{
  Cpp data;
  typedef Delaunay_mesher_2_wrapper<Cpp,CDT_wrapper,Criteria_wrapper> Self;
  //disable deep copy (some criteria cannot be copied)
  Self deepcopy();
  void deepcopy(const Self&);    
public:
  #ifndef SWIG
  typedef Cpp cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Delaunay_mesher_2_wrapper(const cpp_base& base):data(base){}
  #endif
    
  typedef CGAL_Seeds_const_iterator<Cpp,Point_2>          Seeds_const_iterator;
  typedef typename DM2_Input_iterator_helper<CDT_wrapper>::range   Facet_range;
    
//Creation
  Delaunay_mesher_2_wrapper(CDT_wrapper& cdt):data(cdt.get_data()){}
  Delaunay_mesher_2_wrapper(CDT_wrapper& cdt,const Criteria_wrapper& criteria):data(cdt.get_data(),criteria.get_data()){}
//Seeds functions
  SWIG_CGAL_FORWARD_CALL_0(void,clear_seeds)
  void  set_seeds (Point_range range, const bool mark){data.set_seeds(range.first,range.second,mark);}
  void  set_seeds (Point_range range)                 {data.set_seeds(range.first,range.second);}
  Seeds_const_iterator seeds() const {return Seeds_const_iterator(data.seeds_begin(),data.seeds_end());}
//Meshing methods
  SWIG_CGAL_FORWARD_CALL_0(void,refine_mesh)
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Criteria_wrapper,get_criteria)
  SWIG_CGAL_FORWARD_CALL_1(void,set_criteria,Criteria_wrapper)
  SWIG_CGAL_FORWARD_CALL_2(void,set_criteria,Criteria_wrapper,bool)
  void set_bad_faces(Facet_range range){data.set_bad_faces(range.first,range.second);}
  //Step by step operations
  SWIG_CGAL_FORWARD_CALL_0(void,init)
  SWIG_CGAL_FORWARD_CALL_0(bool,is_refinement_done)
  SWIG_CGAL_FORWARD_CALL_0(bool,step_by_step_refine_mesh)
};

#endif //SWIG_CGAL_MESH_2_DELAUNAY_MESHER_2_H


