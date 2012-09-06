%define declare_voronoi_diagram_2(WRAPPER_PREFIX,CPP_BASE,SITE_WRAPPER,TRIANGULATION_WRAPPER)
  //Voronoi handles
  %typemap(javaimports)  Voronoi_vertex_wrapper_2 %{ import CGAL.Kernel.Point_2; import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Face_handle; import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Vertex_handle; %}
  %typemap(javaimports)  Voronoi_halfedge_wrapper_2 %{ import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Edge; import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Vertex_handle; %}
  %typemap(javaimports)  Voronoi_face_wrapper_2 %{ import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Vertex_handle; %}

  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Vertex_handle,   Voronoi_vertex_wrapper_2   <CPP_BASE, TRIANGULATION_WRAPPER##_Vertex_handle_SWIG_wrapper, TRIANGULATION_WRAPPER##_Face_handle_SWIG_wrapper>)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Face_handle,     Voronoi_face_wrapper_2     <CPP_BASE, TRIANGULATION_WRAPPER##_Vertex_handle_SWIG_wrapper, TRIANGULATION_WRAPPER##_Face_handle_SWIG_wrapper>)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Halfedge_handle, Voronoi_halfedge_wrapper_2 <CPP_BASE, TRIANGULATION_WRAPPER##_Vertex_handle_SWIG_wrapper, TRIANGULATION_WRAPPER##_Face_handle_SWIG_wrapper>)

  //Iterators and circulators
  SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,WRAPPER_PREFIX##_Face_handle,)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Face_iterator,SWIG_CGAL_Iterator<CPP_BASE::Face_iterator,WRAPPER_PREFIX##_Face_handle_SWIG_wrapper >)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Bounded_faces_iterator,SWIG_CGAL_Iterator<CPP_BASE::Bounded_faces_iterator,WRAPPER_PREFIX##_Face_handle_SWIG_wrapper >)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Unbounded_faces_iterator,SWIG_CGAL_Iterator<CPP_BASE::Unbounded_faces_iterator,WRAPPER_PREFIX##_Face_handle_SWIG_wrapper >)

  SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,WRAPPER_PREFIX##_Halfedge_handle,)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Edge_iterator,SWIG_CGAL_Iterator<CPP_BASE::Edge_iterator,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper >)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Halfedge_iterator,SWIG_CGAL_Iterator<CPP_BASE::Halfedge_iterator,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper >)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Unbounded_halfedges_iterator,SWIG_CGAL_Iterator<CPP_BASE::Unbounded_halfedges_iterator,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper >)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Bounded_halfedges_iterator,SWIG_CGAL_Iterator<CPP_BASE::Bounded_halfedges_iterator,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper >)

  SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Circulator, WRAPPER_PREFIX##_Halfedge_handle,)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Ccb_halfedge_circulator,SWIG_CGAL_Circulator<CPP_BASE::Ccb_halfedge_circulator,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper >)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Halfedge_around_vertex_circulator,SWIG_CGAL_Circulator<CPP_BASE::Halfedge_around_vertex_circulator,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper >)

  SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,WRAPPER_PREFIX##_Vertex_handle,)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Vertex_iterator,SWIG_CGAL_Iterator<CPP_BASE::Vertex_iterator,WRAPPER_PREFIX##_Vertex_handle_SWIG_wrapper >)

  SWIG_CGAL_set_as_java_iterator(SWIG_CGAL_Iterator,SITE_WRAPPER,import CGAL.Kernel.SITE_WRAPPER;)
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Site_iterator,SWIG_CGAL_Iterator<CPP_BASE::Site_iterator,SITE_WRAPPER >)

  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX##_Locate_result, Locate_result_wrapper<WRAPPER_PREFIX##_Vertex_handle_SWIG_wrapper,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper,WRAPPER_PREFIX##_Face_handle_SWIG_wrapper>)

  %typemap(javaimports)  Voronoi_diagram_2_wrapper %{ import CGAL.Triangulation_2.TRIANGULATION_WRAPPER; import CGAL.Kernel.Point_2; import CGAL.Kernel.Weighted_point_2; import java.util.Iterator; import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Face_handle; import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Edge; import CGAL.Triangulation_2.TRIANGULATION_WRAPPER##_Vertex_handle; %}
  SWIG_CGAL_declare_identifier_of_template_class(WRAPPER_PREFIX,Voronoi_diagram_2_wrapper<CPP_BASE,SITE_WRAPPER,TRIANGULATION_WRAPPER##_SWIG_wrapper,TRIANGULATION_WRAPPER##_Vertex_handle_SWIG_wrapper, TRIANGULATION_WRAPPER##_Face_handle_SWIG_wrapper, WRAPPER_PREFIX##_Vertex_handle_SWIG_wrapper,WRAPPER_PREFIX##_Halfedge_handle_SWIG_wrapper,WRAPPER_PREFIX##_Face_handle_SWIG_wrapper>)
%enddef
