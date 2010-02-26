%module Triangulation_3

%include "../common.i"
%import  "../Kernel/Point_3.h"

//include files
%{
  #include "Delaunay_triangulation_3.h"
  #include "triangulation_handles.h"
  #include "triple.h"
  #include "triangulation_iterators.h"
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3;%}



//definitions
%include "Delaunay_triangulation_3.h"
%include "triangulation_handles.h"
%include "triple.h"
%include "triangulation_iterators.h"
%include "../Common/Output_iterator.h"
%include "../Common/Reference_wrapper.h"

//Handles
%template(DT3_Cell_handle)        CGAL_Cell_handle<EPIC_DT3>;
%typemap(javaimports) CGAL_Vertex_handle %{import CGAL.Kernel.Point_3;%}
%template(DT3_Vertex_handle)      CGAL_Vertex_handle<EPIC_DT3>;

%include "std_pair.i"
%template(DT3_Facet) std::pair<CGAL_Cell_handle<EPIC_DT3>,int>;
%template(DT3_Edge)  CGAL_SWIG::Triple<CGAL_Cell_handle<EPIC_DT3>,int,int>;

//Triangulation
%typemap(javaimports) Delaunay_triangulation_3%{import CGAL.Kernel.Point_3;%}
%template(DT3_T)                  Delaunay_triangulation_3<EPIC_DT3,CGAL_Vertex_handle<EPIC_DT3>,CGAL_Cell_handle<EPIC_DT3> >;


//References
%template(Ref_int) Reference_wrapper<int>;

//Iterators
Iterator_for_java(CGAL_All_vertices_iterator,DT3_Vertex_handle)
%typemap(javaimports) CGAL_All_vertices_iterator
%{
  import CGAL.Kernel.Point_3;
  //TODO: find a way to avoid copy that from Iterator_for_java
  import java.lang.Iterable;
  import java.lang.UnsupportedOperationException;
  import java.util.Iterator;  
%}
%template(DT3_All_vertices_iterator) CGAL_All_vertices_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_vertices_iterator,DT3_Vertex_handle)
%typemap(javaimports) CGAL_Finite_vertices_iterator
%{
  import CGAL.Kernel.Point_3;
  //TODO: find a way to avoid copy that from Iterator_for_java
  import java.lang.Iterable;
  import java.lang.UnsupportedOperationException;
  import java.util.Iterator;  
%}
%template(DT3_Finite_vertices_iterator) CGAL_Finite_vertices_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_All_cells_iterator,DT3_Cell_handle)
%template(DT3_All_cells_iterator) CGAL_All_cells_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_cells_iterator,DT3_Cell_handle)
%template(DT3_Finite_cells_iterator) CGAL_Finite_cells_iterator<EPIC_DT3>;
//output iterator
%template(Cell_handle_output_iterator) Output_iterator<CGAL_Cell_handle<EPIC_DT3> >;
Iterator_for_java(General_iterator,DT3_Cell_handle)
%template(Iterator_of_cell_handle) General_iterator< Output_iterator<CGAL_Cell_handle<EPIC_DT3> >,CGAL_Cell_handle<EPIC_DT3> >;

Iterator_for_java(CGAL_All_facets_iterator,DT3_Facet)
%template(DT3_All_facets_iterator) CGAL_All_facets_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_facets_iterator,DT3_Facet)
%template(DT3_Finite_facets_iterator) CGAL_Finite_facets_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_All_edges_iterator,DT3_Edge)
%template(DT3_All_edges_iterator) CGAL_All_edges_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_edges_iterator,DT3_Edge)
%template(DT3_Finite_edges_iterator) CGAL_Finite_edges_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_Point_iterator,Point_3)
%typemap(javaimports) CGAL_Point_iterator
%{
  import CGAL.Kernel.Point_3;
  //TODO: find a way to avoid copy that from Iterator_for_java
  import java.lang.Iterable;
  import java.lang.UnsupportedOperationException;
  import java.util.Iterator;  
%}
%template(DT3_Point_iterator) CGAL_Point_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_Cell_circulator,DT3_Cell_handle)
%template(DT3_Cell_circulator) CGAL_Cell_circulator<EPIC_DT3>;

Iterator_for_java(CGAL_Facet_circulator,DT3_Facet)
%template(DT3_Facet_circulator) CGAL_Facet_circulator<EPIC_DT3>;