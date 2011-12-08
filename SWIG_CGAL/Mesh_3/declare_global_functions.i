// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_MESH_3_DECLARE_GLOBAL_FUNCTIONS_I
#define SWIG_CGAL_MESH_3_DECLARE_GLOBAL_FUNCTIONS_I

//theses macros declare global functions
//--C3T3 the Complex_3_in_triangulation_3 type
//--DOMAIN the domain type
//--CRITERIA the criteria type
//--PARAMETERS the parameters type


//C3T3 dependant
%define declare_global_functions(C3T3)
//global functions
%inline %{
  Mesh_optimization_return_code  exude_mesh_3( C3T3& c3t3, double time_limit, double sliver_bound)
  {
    return CGAL::enum_cast< Mesh_optimization_return_code >( CGAL::exude_mesh_3(c3t3.get_data(),time_limit,sliver_bound) );
  }
%}
%enddef //end declare_global_functions


//C3T3-DOMAIN dependant
%define declare_global_functions_domain(C3T3,DOMAIN)
%inline  %{
  Mesh_optimization_return_code perturb_mesh_3 (  C3T3& c3t3,const DOMAIN& domain,double time_limit,double sliver_bound)
  {
    return CGAL::enum_cast< Mesh_optimization_return_code >( CGAL::perturb_mesh_3(c3t3.get_data(),domain.get_data(),time_limit,sliver_bound) );
  } 
    
  Mesh_optimization_return_code lloyd_optimize_mesh_3 ( C3T3& c3t3,const DOMAIN& domain,double time_limit,int max_iteration_number,double convergence,double freeze_bound)
  {
    return CGAL::enum_cast< Mesh_optimization_return_code >( CGAL::lloyd_optimize_mesh_3(c3t3.get_data(),domain.get_data(),time_limit,max_iteration_number,convergence,freeze_bound) );
  }

  Mesh_optimization_return_code odt_optimize_mesh_3 (C3T3& c3t3,const DOMAIN& domain,double time_limit,std::size_t max_iteration_number,double convergence,double freeze_bound)
  {
    return CGAL::enum_cast< Mesh_optimization_return_code >( CGAL::odt_optimize_mesh_3(c3t3.get_data(),domain.get_data(),time_limit,max_iteration_number,convergence,freeze_bound) );
  }  
%}
%enddef //end declare_global_functions_domain

//C3T3-domain-criteria dependant
%define declare_global_functions_domain_criteria(C3T3,DOMAIN,CRITERIA,PARAMETERS)
%inline %{
  C3T3 make_mesh_3(const DOMAIN& domain, const CRITERIA& criteria,const PARAMETERS& parameters)
  {
    return C3T3( CGAL::make_mesh_3<C3T3::cpp_base>( domain.get_data(),criteria.get_data(),
                                                                        parameters.get_lloyd_parameters(),
                                                                        parameters.get_odt_parameters(),
                                                                        parameters.get_perturb_parameters(),
                                                                        parameters.get_exude_parameters()
    ));
  }

  void  refine_mesh_3 ( C3T3& c3t3, const DOMAIN& domain,const CRITERIA& criteria,const PARAMETERS& parameters)
  {
    CGAL::refine_mesh_3(c3t3.get_data(),domain.get_data(),criteria.get_data(),
                        parameters.get_lloyd_parameters(),
                        parameters.get_odt_parameters(),
                        parameters.get_perturb_parameters(),
                        parameters.get_exude_parameters());
  }
%}
%enddef //end declare_global_functions_domain_criteria

#endif // SWIG_CGAL_MESH_3_DECLARE_GLOBAL_FUNCTIONS_I
