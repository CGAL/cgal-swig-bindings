#ifndef SWIG_CGAL_MESH_2_CRITERIA_H
#define SWIG_CGAL_MESH_2_CRITERIA_H

template <class Cpp>
class Criteria_wrapper{
  Cpp data;
public:
  #ifndef SWIG
  typedef Cpp cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data_ref()   {return data;}
  Criteria_wrapper(const cpp_base& base):data(base){}
  #endif
  Criteria_wrapper(){}
};

#endif //SWIG_CGAL_MESH_2_CRITERIA_H
