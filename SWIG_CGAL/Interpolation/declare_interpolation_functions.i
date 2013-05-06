// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_INTERPOLATION_DECLARE_INTERPOLATION_FUNCTIONS_H
#define SWIG_CGAL_INTERPOLATION_DECLARE_INTERPOLATION_FUNCTIONS_H


//typedefs
#if !SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Point_2_and_double_range std::pair<Input_iterator_wrapper<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> >,Input_iterator_wrapper<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > > %enddef
%define Point_2_and_double_wrapper std::pair<Point_2,double> %enddef
%define Point_2_and_double_base std::pair<Point_2::cpp_base,double> %enddef

%{
typedef std::pair<Input_iterator_wrapper<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> >,Input_iterator_wrapper<std::pair<Point_2,double>,std::pair<Point_2::cpp_base,double> > > Point_2_and_double_range;
typedef std::pair<Point_2,double> Point_2_and_double_wrapper;
typedef std::pair<Point_2::cpp_base,double> Point_2_and_double_base;
%}

SWIG_CGAL_input_iterator_typemap_in(Point_2_and_double_range,Point_2_and_double_wrapper,Point_2_and_double,Point_2_and_double_base,SWIGTYPE_p_std__pairT_Point_2_double_t,"(LCGAL/Interpolation/Point_2_and_double;)J",linear_interpolation)
#ifdef SWIGPYTHON
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(quadratic_interpolation)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(sibson_c1_interpolation)
SWIG_CGAL_input_iterator_typemap_in_python_extra_function(sibson_c1_interpolation_square)
#endif
#else //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE
%define Point_2_and_double_range Generic_input_iterator< std::pair<Point_2,double> > %enddef
%{ typedef Generic_input_iterator< std::pair<Point_2,double> > Point_2_and_double_range; %}
%template(Point_2_and_double_input_iterator) Generic_input_iterator< std::pair<Point_2,double> >;
#endif //!SWIG_CGAL_NON_SUPPORTED_TARGET_LANGUAGE


%inline %{
  double linear_interpolation(Point_2_and_double_range range,double norm,const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values){
    return CGAL::linear_interpolation(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),norm,function_values.get_data());
  }
  
  std::pair<double,bool> quadratic_interpolation(Point_2_and_double_range range,double norm,const Point_2& p,const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values,const Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>& gradients){
    return CGAL::quadratic_interpolation(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),norm,p.get_data(),function_values.get_data(),gradients.get_data(),CGAL::Interpolation_traits_2<EPIC_Kernel>());
  }
  
  std::pair<double,bool> sibson_c1_interpolation(Point_2_and_double_range range,double norm,const Point_2& p,const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values,const Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>& gradients){
    return CGAL::sibson_c1_interpolation(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),norm,p.get_data(),function_values.get_data(),gradients.get_data(),CGAL::Interpolation_traits_2<EPIC_Kernel>());
  }

  std::pair<double,bool> sibson_c1_interpolation_square(Point_2_and_double_range range,double norm,const Point_2& p,const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values,const Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>& gradients){
    return CGAL::sibson_c1_interpolation_square(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),norm,p.get_data(),function_values.get_data(),gradients.get_data(),CGAL::Interpolation_traits_2<EPIC_Kernel>());
  }

  std::pair<double,bool> farin_c1_interpolation(Point_2_and_double_range range,double norm,const Point_2& p,const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values,const Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>& gradients){
    std::vector<std::pair<Point_2::cpp_base,double> > data;
    std::copy(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),std::back_inserter(data));
    return CGAL::farin_c1_interpolation(data.begin(),data.end(),norm,p.get_data(),function_values.get_data(),gradients.get_data(),CGAL::Interpolation_traits_2<EPIC_Kernel>());
  }

  Vector_2 sibson_gradient_fitting(Point_2_and_double_range range,double norm,const Point_2& p,const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values){
    return Vector_2( CGAL::sibson_gradient_fitting(SWIG_CGAL::get_begin(range),SWIG_CGAL::get_end(range),norm,p.get_data(),function_values.get_data(),CGAL::Interpolation_gradient_fitting_traits_2<EPIC_Kernel>()) );
  }

  void sibson_gradient_fitting_nn_2(const Delaunay_triangulation_2_SWIG_wrapper& dt, Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>& gradients, const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values){
    CGAL::sibson_gradient_fitting_nn_2(dt.get_data(),std::inserter(gradients.get_map(),gradients.get_map().begin()),function_values.get_data(),CGAL::Interpolation_gradient_fitting_traits_2<EPIC_Kernel>());
  }
  
  void sibson_gradient_fitting_rn_2(const Regular_triangulation_2_SWIG_wrapper& rt, Data_access_wrapper<I_DA_PV2,Point_2,Vector_2>& gradients, const Data_access_wrapper<I_DA_PD,Point_2,double>& function_values){
    CGAL::sibson_gradient_fitting_rn_2(rt.get_data(),std::inserter(gradients.get_map(),gradients.get_map().begin()),function_values.get_data(),CGAL::Interpolation_gradient_fitting_traits_2<EPIC_Kernel>());
  }
%}

#endif //SWIG_CGAL_INTERPOLATION_DECLARE_INTERPOLATION_FUNCTIONS_H
