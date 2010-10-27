#ifndef SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I
#define SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I

%import "SWIG_CGAL/Triangulation_2/declare_triangulation_2.i"


//Expose a Delaunay triangulation_2
// --EXPOSEDNAME is the name of the class exposed by SWIG
// --CLASSNAME_PREFIX is the prefixed of the final class exposed by SWIG (different from EXPOSEDNAME if used for a base class instantiation)
// --CPPTYPE is the c++ type of the triangulation
%define Declare_Delaunay_triangulation_2_internal(EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE)
  Declare_triangulation_2_internal(Internal_Triangulation_2_##EXPOSEDNAME,CLASSNAME_PREFIX,CPPTYPE,Point_2,CGAL::Tag_false)

  %define iSWIG_##EXPOSEDNAME##_wrapper Delaunay_triangulation_2_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2>,CGAL_Face_handle<CPPTYPE,Point_2> > %enddef
  %define iSWIG_##EXPOSEDNAME##_Edge_wrapper std::pair<CGAL_Face_handle<CPPTYPE,Point_2>,int > %enddef
  %define iSWIG_##EXPOSEDNAME##_Edge_base std::pair<CPPTYPE::Face_handle,int > %enddef
  Typemap_for_Output_iterator(iSWIG_##EXPOSEDNAME##_wrapper::Edge_output_iterator,iSWIG_##EXPOSEDNAME##_Edge_wrapper,EXPOSEDNAME##_Edge,iSWIG_##EXPOSEDNAME##_Edge_base,SWIGTYPE_p_std__pairT_CGAL_Face_handleT_##CPPTYPE##_Point_2_t_int_t,"LCGAL/Triangulation_2/" #EXPOSEDNAME "_Edge;")

  %define iSWIG_##EXPOSEDNAME##_Face_wrapper CGAL_Face_handle<CPPTYPE,Point_2> %enddef
  Typemap_for_Output_iterator(iSWIG_##EXPOSEDNAME##_wrapper::Face_output_iterator,iSWIG_##EXPOSEDNAME##_Face_wrapper,EXPOSEDNAME##_Face_handle,CPPTYPE::Face_handle,SWIGTYPE_p_CGAL_Face_handleT_##CPPTYPE##_Point_2_t,"LCGAL/Triangulation_2/" #EXPOSEDNAME "_Face_handle;")
  

  %typemap(javaimports)          Delaunay_triangulation_2_wrapper%{import CGAL.Kernel.Point_2; import java.util.Iterator; import java.util.Collection;%}
  %template(EXPOSEDNAME)         Delaunay_triangulation_2_wrapper<CPPTYPE,CGAL_Vertex_handle<CPPTYPE,Point_2>,CGAL_Face_handle<CPPTYPE,Point_2> >;
%enddef


//Expose a Delaunay_triangulation_2
// --CLASSNAME  is the name of the class exposed by SWIG
// --CPPTYPE is the c++ type of the triangulation
%define Declare_Delaunay_triangulation_2(CLASSNAME,CPPTYPE)
  Declare_Delaunay_triangulation_2_internal(CLASSNAME,CLASSNAME,CPPTYPE)
%enddef

#endif //SWIG_CGAL_TRIANGULATION_2_DECLARE_DELAUNAY_TRIANGULATION_2_I
