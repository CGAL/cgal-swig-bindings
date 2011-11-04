#ifndef SWIG_CGAL_SURFACE_MESHER_C2T3_H
#define SWIG_CGAL_SURFACE_MESHER_C2T3_H

#include <SWIG_CGAL/Common/Input_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
#include <SWIG_CGAL/Common/Input_iterator.h>

namespace C2T3_internal{

template <class Triangulation>
struct Iterator_helper
{
  typedef boost::function_output_iterator< Container_writer<typename Triangulation::Facet,typename Triangulation::cpp_base::Facet > >     output;
};

} //namespace internal

enum Face_status { NOT_IN_COMPLEX, BOUNDARY, REGULAR, SINGULAR};

template <class C2T3,class Triangulation>
class C2T3_wrapper
{
  C2T3 data;
public:
  #ifndef SWIG
  typedef C2T3 cpp_base;
  const cpp_base& get_data() const {return data;}
  cpp_base& get_data_ref() {return data;}    
  #endif
  typedef typename Triangulation::Edge Edge;
  typedef typename Triangulation::Facet Facet;
  typedef typename Triangulation::Vertex_handle Vertex_handle;
  typedef typename Triangulation::Cell_handle Cell_handle;

  typedef CGAL_Vertex_iterator<C2T3,Vertex_handle>               Vertex_iterator;
  typedef CGAL_Edge_iterator<C2T3,Edge>                          Edge_iterator;
  typedef CGAL_Facet_iterator<C2T3,Facet>                        Facet_iterator;
  typedef CGAL_Boundary_edges_iterator<C2T3,Edge>                Boundary_edges_iterator;

  typedef typename C2T3_internal::Iterator_helper<Triangulation>::output Output_iterator;

//Creation
  C2T3_wrapper(Triangulation& t3):data(t3.get_data_ref()){}
//Member access
  SWIG_CGAL_FORWARD_CALL_AND_REF_0(Triangulation,triangulation)
//Modifications
  SWIG_CGAL_FORWARD_CALL_1(void,add_to_complex,Facet)
  SWIG_CGAL_FORWARD_CALL_2(void ,add_to_complex,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(void ,remove_from_complex,Facet)
  SWIG_CGAL_FORWARD_CALL_2(void ,remove_from_complex,Cell_handle,int)
//Queries
  SWIG_CGAL_FORWARD_CALL_0(int,number_of_facets)
  SWIG_CGAL_FORWARD_CALL_1(Face_status,face_status,Facet)
  SWIG_CGAL_FORWARD_CALL_2(Face_status,face_status,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(Face_status,face_status,Edge)
  SWIG_CGAL_FORWARD_CALL_3(Face_status,face_status,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_1(Face_status,face_status,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_in_complex,Facet)
  SWIG_CGAL_FORWARD_CALL_2(bool,is_in_complex,Cell_handle,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_in_complex,Edge)
  SWIG_CGAL_FORWARD_CALL_3(bool,is_in_complex,Cell_handle,int,int)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_in_complex,Vertex_handle)
  SWIG_CGAL_FORWARD_CALL_1(bool,is_regular_or_boundary_for_vertices,Vertex_handle)
//Traversal of the complex
  Facet_iterator  facets() {return Facet_iterator(data.facets_begin(),data.facets_end());}
  Edge_iterator   edges() {return Edge_iterator(data.edges_begin(),data.edges_end());}
  Boundary_edges_iterator  boundary_edges() {return Boundary_edges_iterator(data.boundary_edges_begin(),data.boundary_edges_end());}
  Vertex_iterator  vertices() {return Vertex_iterator(data.vertices_begin(),data.vertices_end());}
  //
  void incident_facets ( Vertex_handle v, Output_iterator out){data.incident_facets(v.get_data(),out);}
  SWIG_CGAL_FORWARD_CALL_AND_REF_2(Facet,neighbor,Facet,int)
  SWIG_CGAL_FORWARD_CALL_AND_REF_3(Facet,neighbor,Cell_handle,int,int)  
};


//Creation
//Traversal of the complex
//  template < class FacetSelector> SurfaceMeshComplex_2InTriangulation_3 c2t3 ( Triangulation& t3, FacetSelector select);



#endif //SWIG_CGAL_SURFACE_MESHER_C2T3_H
