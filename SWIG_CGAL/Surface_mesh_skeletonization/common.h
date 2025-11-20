#ifndef COMMON_H
#define COMMON_H

#include <CGAL/boost/graph/split_graph_into_polylines.h>
#include "structs.h"

// All functions here are template to allow in the future additional skeleton & mesh types (see examples in CGAL cpp files)

////////////////////////////////////////////
// Advanced algorithm running
////////////////////////////////////////////

template <typename TSkeletonizaion>
void set_params(TSkeletonizaion& mcs,  const local_remeshing_parameters& params1) {
  if (mcs.max_triangle_angle() != params1.max_triangle_angle) {
      mcs.set_max_triangle_angle(params1.max_triangle_angle);
  }
  if (mcs.min_edge_length() != params1.min_edge_length) {
      mcs.set_min_edge_length(params1.min_edge_length);
  }
}

template <typename TSkeletonizaion>
void set_params(TSkeletonizaion& mcs,  const algorithm_termination_parameters& params2) {
  if (mcs.max_iterations() != params2.max_iterations) {
      mcs.set_max_iterations(params2.max_iterations);
  }
  if (mcs.area_variation_factor() != params2.area_variation_factor) {
      mcs.set_area_variation_factor(params2.area_variation_factor);
  }
}

template <typename TSkeletonizaion>
void set_params(TSkeletonizaion& mcs,  const vertex_motion_parameters& params3) {
  if (mcs.quality_speed_tradeoff() != params3.quality_speed_tradeoff) {
      mcs.set_quality_speed_tradeoff(params3.quality_speed_tradeoff);
  }
  if (mcs.medially_centered_speed_tradeoff() != params3.medially_centered_speed_tradeoff) {
      mcs.set_medially_centered_speed_tradeoff(params3.medially_centered_speed_tradeoff);
  }
  if (mcs.is_medially_centered() != params3.is_medially_centered) {
      mcs.set_is_medially_centered(params3.is_medially_centered);
  }
}

template <typename TSkeleton, typename TMesh> 
void run(const TMesh& tmesh, TSkeleton& skeleton, const local_remeshing_parameters& params1,
         const algorithm_termination_parameters& params2, const vertex_motion_parameters& params3, bool debug = false) {
  CGAL::Mean_curvature_flow_skeletonization<TMesh> mcs(tmesh);

  set_params(mcs, params1);
  set_params(mcs, params2);
  set_params(mcs, params3);

  /*// 1. Contract the mesh by mean curvature flow.
  mcs.contract_geometry();

  // 2. Collapse short edges and split bad triangles.
  mcs.collapse_edges();
  mcs.split_faces();

  // 3. Fix degenerate vertices.
  mcs.detect_degeneracies();

  // Perform the above three steps in one iteration.
  mcs.contract();
  */
  // Iteratively apply step 1 to 3 until convergence.
  mcs.contract_until_convergence();

  // Convert the contracted mesh into a curve skeleton and
  // get the correspondent surface points
  mcs.convert_to_skeleton(skeleton);
}


////////////////////////////////////////////
// Output writing
////////////////////////////////////////////

template <typename TSkeleton, typename Tvertex_descriptor, typename Tout>
struct Display_polylines{ 
  const TSkeleton& skeleton;
  std::vector<Tout>& out;

  Display_polylines(const TSkeleton& skeleton, std::vector<Tout>& out)
    : skeleton(skeleton), out(out)
  {}

  void start_new_polyline(){
      out.push_back(Tout());
  }
  void add_node(const Tvertex_descriptor& v){
    out.back().push_back(skeleton[v].point);
  }
  void end_polyline() {
  }
};

template <typename TSkeleton, typename TMesh, typename Tout> 
void write_results(const TSkeleton& skeleton, const TMesh& tmesh, std::vector<Tout>& output, std::vector<Tout>& output_correspondence, bool debug) {

  if (debug) {
    std::cout << "Number of vertices of the skeleton: " << boost::num_vertices(skeleton) << "\n";
    std::cout << "Number of edges of the skeleton: " << boost::num_edges(skeleton) << "\n";
  }

  Display_polylines<TSkeleton, typename TSkeleton::vertex_descriptor, Tout> display(skeleton,output);
  CGAL::split_graph_into_polylines(skeleton, display);

  // Output skeleton points and the corresponding surface points
  for (const auto & v : CGAL::make_range(vertices(skeleton)))
    for (const auto & vd : skeleton[v].vertices)
    {
      output_correspondence.push_back(Tout());
      output_correspondence.back().push_back(skeleton[v].point);
      output_correspondence.back().push_back(get(CGAL::vertex_point, tmesh, vd));
    }
}

////////////////////////////////////////////
// Get algorithm parameters (allow setting them)
////////////////////////////////////////////

template <typename TMesh> 
local_remeshing_parameters get_local_remeshing_parameters(const TMesh& tmesh) {
    CGAL::Mean_curvature_flow_skeletonization<TMesh> mcs(tmesh);
    return local_remeshing_parameters{mcs.max_triangle_angle(), mcs.min_edge_length()};
}

template <typename TMesh> 
algorithm_termination_parameters get_algorithm_termination_parameters(const TMesh& tmesh) {
    CGAL::Mean_curvature_flow_skeletonization<TMesh> mcs(tmesh);
    return algorithm_termination_parameters{mcs.max_iterations(), mcs.area_variation_factor()};
}

template <typename TMesh> 
vertex_motion_parameters get_vertex_motion_parameters(const TMesh& tmesh) {
    CGAL::Mean_curvature_flow_skeletonization<TMesh> mcs(tmesh);
    return vertex_motion_parameters{mcs.quality_speed_tradeoff(), mcs.is_medially_centered(), mcs.medially_centered_speed_tradeoff()};
}

#endif
