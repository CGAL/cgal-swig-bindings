#include <CGAL/Polyhedron_3.h>
#include <CGAL/extract_mean_curvature_flow_skeleton.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <fstream>
#include <vector>

#include "structs.h"
#include "common.h"

// output types
typedef Point_3 Point_3_wrapper;
typedef std::vector<Point_3_wrapper> Polyline_wrapper;

// input types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel, CGAL::Polyhedron_items_with_id_3> Polyhedron;

// algorithm types
typedef CGAL::Mean_curvature_flow_skeletonization<Polyhedron> Skeletonization;
typedef Skeletonization::Skeleton                             Skeleton;

// define a double-precision representation of seconds
using fsecs = std::chrono::duration<double, std::chrono::seconds::period>;

int skeletonization(const Polyhedron & tmesh, std::vector<Polyline_wrapper> & output_skeleton, 
                    std::vector<Polyline_wrapper> & output_correspondence, bool debug = false)
{
  if (!CGAL::is_triangle_mesh(tmesh))
  {
    std::cout << "Input geometry is not triangulated." << std::endl;
    return EXIT_FAILURE;
  }

  auto begin = std::chrono::steady_clock::now();
  
  Skeleton skeleton;
  CGAL::extract_mean_curvature_flow_skeleton(tmesh, skeleton);

  auto end = std::chrono::steady_clock::now();

  write_results(skeleton, tmesh, output_skeleton, output_correspondence, debug=debug);
  
  if (debug) {
    std::cout << "Skeletonization took: " << std::chrono::duration_cast<fsecs>(end - begin).count() << " seconds" << std::endl;
  }

  return EXIT_SUCCESS;
}

int skeletonization_advanced(const Polyhedron & tmesh, std::vector<Polyline_wrapper> & output_skeleton, 
                             std::vector<Polyline_wrapper> & output_correspondence, const local_remeshing_parameters& params1, 
			     const algorithm_termination_parameters& params2, const vertex_motion_parameters& params3, bool debug = false)
{
  if (!CGAL::is_triangle_mesh(tmesh))
  {
    std::cout << "Input geometry is not triangulated." << std::endl;
    return EXIT_FAILURE;
  }

  if (debug) {
    std::cout << "Parameters: " << params1.__str__() << params2.__str__() << params3.__str__() << std::endl;
  }

  auto begin = std::chrono::steady_clock::now();

  Skeleton skeleton;
  run(tmesh, skeleton, params1, params2, params3, debug);

  auto end = std::chrono::steady_clock::now();

  write_results(skeleton, tmesh, output_skeleton, output_correspondence, debug);
  
  if (debug) {
    std::cout << "Skeletonization took: " << std::chrono::duration_cast<fsecs>(end - begin).count() << " seconds" << std::endl;
  }

  return EXIT_SUCCESS;
}

