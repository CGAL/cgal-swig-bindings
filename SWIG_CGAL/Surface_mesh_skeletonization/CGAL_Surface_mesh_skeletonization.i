// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

%define AW3_DOCSTRING
"SWIG wrapper for the CGAL 3D Surface_mesh_skeletonization provided under the GPL-3.0+ license"
%enddef
%module (package="CGAL", docstring=AW3_DOCSTRING) CGAL_Surface_mesh_skeletonization

%include "SWIG_CGAL/common.i"
Decl_void_type()

SWIG_CGAL_add_java_loadLibrary(CGAL_Surface_mesh_skeletonization)
SWIG_CGAL_package_common()

%include <std_string.i>
%include "SWIG_CGAL/Common/Iterator.h"
%include "SWIG_CGAL/Kernel/typedefs.h"
%import  "SWIG_CGAL/Common/Macros.h"
%import  "SWIG_CGAL/Kernel/CGAL_Kernel.i"
%include  "SWIG_CGAL/Common/Output_iterator_wrapper.h"
%include  "SWIG_CGAL/Surface_mesh_skeletonization/structs.h" // include so structs are recognized in python

//include files
%{
  #include <SWIG_CGAL/Kernel/typedefs.h>
  #include <SWIG_CGAL/Kernel/Point_3.h>
  #include <SWIG_CGAL/Polyhedron_3/all_includes.h>
  #include <SWIG_CGAL/Point_set_3/all_includes.h>
  #include <SWIG_CGAL/Surface_mesh_skeletonization/impl_polyhedron_3.h>
  #include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
%}

%types(Point_3*,Point_3); //needed so that the identifier SWIGTYPE_p_Point_3 is generated

%pragma(java) jniclassimports=%{
  import CGAL.Kernel.Point_3;
  import java.util.Iterator;
  import java.util.Collection;
  import CGAL.Polyhedron_3.Polyhedron_3;
%}

%pragma(java) moduleimports=%{
  import CGAL.Kernel.Point_3;
  import java.util.Iterator;
  import java.util.Collection;
  import CGAL.Polyhedron_3.Polyhedron_3;
%}

%define Integer_output_iterator boost::function_output_iterator<Container_writer<int,int> > %enddef
SWIG_CGAL_output_iterator_typemap_in(Integer_output_iterator,int,Integer,int,swig_types[0],"Ljava/lang/Integer;")

//import definitions of Polyhedron objects
%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"

//import Polyhedron_3 wrapper types
SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper

//import STL vector
%include "std_vector.i"

// output types
typedef Point_3 Point_3_wrapper;
typedef std::vector<Point_3_wrapper> Polyline_wrapper;

// main function
void surface_mesh_skeletonization(const Polyhedron_3_SWIG_wrapper &polyhedron, std::vector<Polyline_wrapper> &output_skeleton, 
                                  std::vector<Polyline_wrapper> &output_correspondence, bool debug=false);

void surface_mesh_skeletonization(const Polyhedron_3_SWIG_wrapper &polyhedron, std::vector<Polyline_wrapper> &output_skeleton, 
                                  std::vector<Polyline_wrapper> &output_correspondence, const local_remeshing_parameters& params1, 
                                  const algorithm_termination_parameters& params2, const vertex_motion_parameters& params3, bool debug=false);

// get default parameters - allow setting them later
local_remeshing_parameters get_local_remeshing_parameters(const Polyhedron_3_SWIG_wrapper &polyhedron);
algorithm_termination_parameters get_algorithm_termination_parameters(const Polyhedron_3_SWIG_wrapper &polyhedron);
vertex_motion_parameters get_vertex_motion_parameters(const Polyhedron_3_SWIG_wrapper &polyhedron);

// inline implementations - wrap get_data & call implementation from impl_polyhedron_3.h 
%{
  void surface_mesh_skeletonization(const Polyhedron_3_SWIG_wrapper &polyhedron,
    std::vector<Polyline_wrapper> &output_skeleton, std::vector<Polyline_wrapper> &output_correspondence, bool debug = false) {
    skeletonization(polyhedron.get_data(), output_skeleton, output_correspondence, debug);
  }

  void surface_mesh_skeletonization(const Polyhedron_3_SWIG_wrapper &polyhedron, std::vector<Polyline_wrapper> &output_skeleton, 
                                  std::vector<Polyline_wrapper> &output_correspondence, const local_remeshing_parameters& params1, 
                                  const algorithm_termination_parameters& params2, const vertex_motion_parameters& params3, bool debug = false){
    skeletonization_advanced(polyhedron.get_data(), output_skeleton, output_correspondence, 
                             params1, params2, params3, debug);
  }

  local_remeshing_parameters get_local_remeshing_parameters(const Polyhedron_3_SWIG_wrapper &polyhedron) {
      return get_local_remeshing_parameters(polyhedron.get_data());
  }
  algorithm_termination_parameters get_algorithm_termination_parameters(const Polyhedron_3_SWIG_wrapper &polyhedron) {
      return get_algorithm_termination_parameters(polyhedron.get_data());
  }
  vertex_motion_parameters get_vertex_motion_parameters(const Polyhedron_3_SWIG_wrapper &polyhedron) {
      return get_vertex_motion_parameters(polyhedron.get_data());
  }
   
%}

