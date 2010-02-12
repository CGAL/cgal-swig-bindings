%module DT3

//macro function to define proper java iterators
#ifdef SWIGJAVA
%define Iterator_for_java(Iterator_type,Object_type)
  %typemap(javaimports) Iterator_type
  %{
  import java.lang.Iterable;
  import java.lang.UnsupportedOperationException;
  import java.util.Iterator;
  %}
  
  %typemap(javainterfaces) Iterator_type %{  Iterable<Object_type>, Iterator<Object_type> %}

  %typemap(javacode) Iterator_type
  %{
    public void remove() {
      throw new UnsupportedOperationException();
    }
    
    public Iterator<Object_type> iterator() {
      return this;
    }  
  %}
%enddef

%define Add_info(Class_name,Info_type)
  %typemap(javacode) Class_name
  %{
    public void setInfo(Info_type i) {
      setInfo_i( (Object) i);
    }
    
    public Info_type getInfo(){
      return (Info_type) getInfo_i();
    }
  %}
%enddef

#else
%define Iterator_for_java(Iterator_type,Object_type)
%enddef
#endif

//exception for iterators (for next fonctions)
#ifdef SWIGPYTHON
%include exception.i
%exception next
{
  try{
    $action
    }
    catch(int){//TODO: throw a specify exception
      SWIG_SetErrorObj(PyExc_StopIteration, SWIG_Py_Void());
      SWIG_fail;
    }
}
#endif

//Special treatment for enum in java
#ifdef SWIGJAVA
%include "enums.swg"
%javaconst(1);
#endif

#ifdef SWIGJAVA
%rename(set_equal) operator=;
#endif

//include files
%{
  #include "EPIC_Kernel.h"
  #ifdef SWIGJAVA
  #include "JavaData.h"
  #endif
  #include "Delaunay_triangulation_3.h"
  #include "triangulation_handles.h"
  #include "triple.h"
  #include "triangulation_iterators.h"
%}


//definitions
%include "EPIC_Kernel.h"
#ifdef SWIGJAVA
%include "JavaData.h"
#endif
%include "Delaunay_triangulation_3.h"
%include "triangulation_handles.h"
%include "triple.h"
%include "triangulation_iterators.h"

//Handles
%template(DT3_Cell_handle)        CGAL_Cell_handle<EPIC_DT3>;
%template(DT3_Vertex_handle)      CGAL_Vertex_handle<EPIC_DT3>;

%include "std_pair.i"
%template(DT3_Facet) std::pair<CGAL_Cell_handle<EPIC_DT3>,int>;
%template(DT3_Edge)  CGAL_SWIG::Triple<CGAL_Cell_handle<EPIC_DT3>,int,int>;

//Triangulation
%template(DT3_T)                  Delaunay_triangulation_3<EPIC_DT3,CGAL_Vertex_handle<EPIC_DT3>,CGAL_Cell_handle<EPIC_DT3> >;

//Iterators
Iterator_for_java(CGAL_All_vertices_iterator,DT3_Vertex_handle)
%template(DT3_All_vertices_iterator) CGAL_All_vertices_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_vertices_iterator,DT3_Vertex_handle)
%template(DT3_Finite_vertices_iterator) CGAL_Finite_vertices_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_All_cells_iterator,DT3_Cell_handle)
%template(DT3_All_cells_iterator) CGAL_All_cells_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_cells_iterator,DT3_Cell_handle)
%template(DT3_Finite_cells_iterator) CGAL_Finite_cells_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_All_facets_iterator,DT3_Facet)
%template(DT3_All_facets_iterator) CGAL_All_facets_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_facets_iterator,DT3_Facet)
%template(DT3_Finite_facets_iterator) CGAL_Finite_facets_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_All_edges_iterator,DT3_Edge)
%template(DT3_All_edges_iterator) CGAL_All_edges_iterator<EPIC_DT3>;
Iterator_for_java(CGAL_Finite_edges_iterator,DT3_Edge)
%template(DT3_Finite_edges_iterator) CGAL_Finite_edges_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_Point_iterator,EPIC_Point_3)
%template(DT3_Point_iterator) CGAL_Point_iterator<EPIC_DT3>;

Iterator_for_java(CGAL_Cell_circulator,DT3_Cell_handle)
%template(DT3_Cell_circulator) CGAL_Cell_circulator<EPIC_DT3>;

Iterator_for_java(CGAL_Facet_circulator,DT3_Facet)
%template(DT3_Facet_circulator) CGAL_Facet_circulator<EPIC_DT3>;