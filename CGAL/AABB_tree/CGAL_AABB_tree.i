%module CGAL_AABB_tree

%include "../common.i"
%import  "../Common/Macros.h"
%import  "../Kernel/Point_3.h"
%import  "../Kernel/Triangle_3.h"
%import  "../Kernel/Segment_3.h"
%import  "../Kernel/CGAL_Object.h"
%import  "../Polyhedron_3/Polyhedron_3.h"
%import  "../Polyhedron_3/polyhedron_3_handles.h"
%include "../Common/Input_iterator.h"
%include "../Common/Optional.h"

//include files
%{
  #include <CGAL/AABB_tree.h>
  #include <CGAL/AABB_traits.h>
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

%pragma(java) jniclassimports=%{
  import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Plane_3; import CGAL.Kernel.Point_3; import CGAL.Kernel.CGAL_Object;
  import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle; import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle; import java.util.Iterator; import java.util.Collection;
%}

%include "std_pair.i"
//Point_and_primitive_id
%typemap(javaimports)       std::pair<Point_3,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > %{import CGAL.Kernel.Point_3; import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;%}
%template(Point_and_Polyhedron_3_Facet_handle) std::pair<Point_3,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >;
%typemap(javaimports)       std::pair<Point_3,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> > %{import CGAL.Kernel.Point_3; import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;%}
%template(Point_and_Polyhedron_3_Halfedge_handle) std::pair<Point_3,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;
%typemap(javaimports)       std::pair<Point_3,int > %{import CGAL.Kernel.Point_3;%}
%template(Point_and_Integer) std::pair<Point_3,int >;
//CGAL_Object_and_primitive_id
%typemap(javaimports)       std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > %{import CGAL.Kernel.CGAL_Object; import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;%}
%template(Object_and_Polyhedron_3_Facet_handle) std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >;
%typemap(javaimports)       std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> > %{import CGAL.Kernel.CGAL_Object; import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;%}
%template(Object_and_Polyhedron_3_Halfedge_handle) std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;
%typemap(javaimports)       std::pair<CGAL_Object,int > %{import CGAL.Kernel.CGAL_Object; import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;%}
%template(Object_and_Integer) std::pair<CGAL_Object,int >;
//Optional<primitive_id>
%typemap(javaimports)       Optional<SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> > %{import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;%}
%template (Optional_Polyhedron_3_Halfedge_handle) Optional<SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;
%typemap(javaimports)       Optional<SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > %{import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;%}
%template (Optional_Polyhedron_3_Facet_handle) Optional<SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >;
%template (Optional_Integer) Optional< int >;
//Optional<CGAL_Object_and_primitive_id>
%template (Optional_Object_and_Polyhedron_3_Halfedge_handle) Optional< std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> > >;
%template (Optional_Object_and_Polyhedron_3_Facet_handle)    Optional< std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > >;
%template (Optional_Object_and_Integer)    Optional< std::pair<CGAL_Object,int > >;


Typemap_for_Input_iterator(Primitive_iterator_helper< SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >::input,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>,Polyhedron_3_Facet_handle,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>::cpp_base,SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t,"(LCGAL/Polyhedron_3/Polyhedron_3_Facet_handle;)J",rebuild)
Typemap_for_Input_iterator(Primitive_iterator_helper< SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >::input,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,Polyhedron_3_Halfedge_handle,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>::cpp_base,SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t,"(LCGAL/Polyhedron_3/Polyhedron_3_Halfedge_handle;)J",rebuild)
Typemap_for_Input_iterator(Primitive_iterator_helper< Triangle_3 >::input,Triangle_3,Triangle_3,Triangle_3::cpp_base,SWIGTYPE_p_Triangle_3,"(LCGAL/Kernel/Triangle_3;)J",rebuild)
Typemap_for_Input_iterator(Primitive_iterator_helper< Segment_3 >::input,Segment_3,Segment_3,Segment_3::cpp_base,SWIGTYPE_p_Segment_3,"(LCGAL/Polyhedron_3/Polyhedron_3_Halfedge_handle;)J",rebuild)
#ifdef SWIGPYTHON
Typemap_for_Input_iterator_additional_function(AABB_tree_wrapper::AABB_tree_wrapper)
#endif
Typemap_for_Input_iterator(Point_range,Point_3,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",accelerate_distance_queries)

//intersected primitive output iterator
%define Polyhedron_3_Facet_output_iterator Primitive_iterator_helper<SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >::output %enddef
Typemap_for_Output_iterator(Polyhedron_3_Facet_output_iterator,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> ,Polyhedron_3_Facet_handle,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> ::cpp_base,SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t,"LCGAL/Polyhedron_3/Polyhedron_3_Facet_handle;")
%define Polyhedron_3_Halfedge_output_iterator Primitive_iterator_helper<SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >::output %enddef
Typemap_for_Output_iterator(Polyhedron_3_Halfedge_output_iterator,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,Polyhedron_3_Halfedge_handle,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>::cpp_base,SWIGTYPE_p_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t,"LCGAL/Polyhedron_3/Polyhedron_3_Halfedge_handle;")

%define Integer_output_iterator Primitive_iterator_helper< int >::output %enddef
Typemap_for_Output_iterator(Integer_output_iterator,int,Integer,int,swig_types[0],"Ljava/lang/Integer;")


//intersection output iterator
%define Polyhedron_3_Facet_output_iterator_2 Primitive_iterator_helper<SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >::output2 %enddef
%{ typedef std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> > Object_and_Polyhedron_3_Facet_handle; %}
%define Object_and_Polyhedron_3_Facet_handle_base std::pair<CGAL::Object,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>::cpp_base> %enddef
Typemap_for_Output_iterator(Polyhedron_3_Facet_output_iterator_2,Object_and_Polyhedron_3_Facet_handle,Object_and_Polyhedron_3_Facet_handle,Object_and_Polyhedron_3_Facet_handle_base,SWIGTYPE_p_std__pairT_CGAL_Object_SWIG_Polyhedron_3__CGAL_Facet_handleT_Polyhedron_3__t_t,"LCGAL/AABB_tree/Object_and_Polyhedron_3_Facet_handle;")

%define Polyhedron_3_Halfedge_output_iterator_2 Primitive_iterator_helper<SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >::output2 %enddef
%{ typedef std::pair<CGAL_Object,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> > Object_and_Polyhedron_3_Halfedge_handle; %}
%define Object_and_Polyhedron_3_Halfedge_handle_base std::pair<CGAL::Object,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>::cpp_base> %enddef
Typemap_for_Output_iterator(Polyhedron_3_Halfedge_output_iterator_2,Object_and_Polyhedron_3_Halfedge_handle,Object_and_Polyhedron_3_Halfedge_handle,Object_and_Polyhedron_3_Halfedge_handle_base,SWIGTYPE_p_std__pairT_CGAL_Object_SWIG_Polyhedron_3__CGAL_Halfedge_handleT_Polyhedron_3__t_t,"LCGAL/AABB_tree/Object_and_Polyhedron_3_Halfedge_handle;")

%define Soup_output_iterator_2 Primitive_iterator_helper< int >::output2 %enddef
%{ typedef std::pair<CGAL_Object,int > Object_and_Integer; %}
%define Object_and_Integer_base std::pair<CGAL::Object,int> %enddef
Typemap_for_Output_iterator(Soup_output_iterator_2,Object_and_Integer,Object_and_Integer,Object_and_Integer_base,SWIGTYPE_p_std__pairT_CGAL_Object_int_t,"LCGAL/AABB_tree/Object_and_Integer;")


//Declaration of the main classes
%typemap(javaimports)      AABB_tree_wrapper%{import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle; import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Plane_3; import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection;%}
%template (AABB_tree_Polyhedron_3_Facet) AABB_tree_wrapper<CGAL_PTP_Tree,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Facet_handle<Polyhedron_3_> >;
  %typemap(javaimports)      AABB_tree_wrapper%{import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle; import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Plane_3; import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection;%}
%template (AABB_tree_Polyhedron_3_Halfedge) AABB_tree_wrapper<CGAL_PSP_Tree,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_>,SWIG_Polyhedron_3::CGAL_Halfedge_handle<Polyhedron_3_> >;
%typemap(javaimports)      AABB_tree_wrapper%{import CGAL.Kernel.Triangle_3; import CGAL.Kernel.Segment_3; import CGAL.Kernel.Plane_3; import CGAL.Kernel.Point_3; import java.util.Iterator; import java.util.Collection;%}
%template (AABB_tree_Segment_3_soup) AABB_tree_wrapper<CGAL_SSP_Tree,Segment_3,int >;
%template (AABB_tree_Triangle_3_soup) AABB_tree_wrapper<CGAL_TSP_Tree,Triangle_3,int >;


