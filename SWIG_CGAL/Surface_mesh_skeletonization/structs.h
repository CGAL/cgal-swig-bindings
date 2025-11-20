#ifndef STRUCTS_H
#define STRUCTS_H

#include <sstream>
struct local_remeshing_parameters
{
  double max_triangle_angle;
  double min_edge_length;

  std::string __str__() const { // match the python __str__ saved word
    std::ostringstream oss(std::ostringstream::out);
    oss << "{'max_triangle_angle':" << (*this).max_triangle_angle << ", 'min_edge_length':" <<  (*this).min_edge_length << "}";
    return oss.str();
  }
};

struct algorithm_termination_parameters
{
  std::size_t max_iterations;
  double area_variation_factor;
  std::string __str__() const { // match the python __str__ saved word
    std::ostringstream oss(std::ostringstream::out);
    oss << "{'max_iterations':" << (*this).max_iterations << ", 'area_variation_factor':" <<  (*this).area_variation_factor << "}";
    return oss.str();
  }
};

struct vertex_motion_parameters
{
  double quality_speed_tradeoff;
  bool is_medially_centered;
  double medially_centered_speed_tradeoff;
  std::string __str__() const { // match the python __str__ saved word
    std::ostringstream oss(std::ostringstream::out);
    oss << "{'quality_speed_tradeoff':" << (*this).quality_speed_tradeoff << ", 'is_medially_centered':" <<  (*this).is_medially_centered 
        << ", 'medially_centered_speed_tradeoff':" <<  (*this).medially_centered_speed_tradeoff  << "}";
    return oss.str();
  }
};

#endif
