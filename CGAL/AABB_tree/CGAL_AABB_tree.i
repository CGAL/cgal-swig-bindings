%module AABB_tree

%include "../common.i"
%import  "../Common/Macros.h"
%import  "../Kernel/Point_3.h"
%import  "../Kernel/Triangle_3.h"
%import  "../Kernel/Segment_3.h"
%import  "../Polyhedron_3/Polyhedron_3.h"
%import  "../Polyhedron_3/polyhedron_3_handles.h"
%include "../Common/Input_iterator.h"


//include files
%{
  #include <CGAL/AABB_tree.h>
  #include  "../Kernel/typedefs.h"
  #include  "../Kernel/Point_3.h"
  #include  "../Kernel/Triangle_3.h"
  #include  "../Kernel/Segment_3.h"
  #include  "../Polyhedron_3/Polyhedron_3.h"
  #include  "../Polyhedron_3/polyhedron_3_handles.h"
  #include "AABB_tree.h"
%}


%include "config.i"

//definitions
%include "AABB_tree.h"

%pragma(java) jniclassimports=%{import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle; import java.util.Iterator;%}


Typemap_for_Input_iterator(Primitive_iterator_helper< Polyhedron_3_Facet_handle >::input,Polyhedron_3_Facet_handle,Polyhedron_3_Facet_handle::cpp_base,SWIGTYPE_p_CGAL_Facet_handleT_CGAL__Polyhedron_3T_EPIC_Kernel_CGAL__Polyhedron_items_with_id_and_info_3T_JavaData_t_t_t,"(LCGAL/Polyhedron_3/Polyhedron_3_Facet_handle;)J",insert_range)

%typemap(javaimports)      AABB_tree_wrapper%{import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle; import java.util.Iterator;%}
%template (AABB_tree_test) AABB_tree_wrapper<CGAL_PTP_Tree,Polyhedron_3_Facet_handle>;


