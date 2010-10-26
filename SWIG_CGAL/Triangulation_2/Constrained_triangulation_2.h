#ifndef SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_2_H
#define SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_2_H

#include <SWIG_CGAL/Triangulation_2/Triangulation_2.h>

#include <boost/function_output_iterator.hpp>
#include <SWIG_CGAL/Common/Output_iterator_wrapper.h>
#include <CGAL/Constrained_triangulation_2.h>

typedef std::pair<Point_2,Point_2>                                          Constraint;
typedef Input_iterator_wrapper<Constraint,std::pair<Point_2::cpp_base,Point_2::cpp_base> > Input_constraint_iterator;
typedef std::pair<Input_constraint_iterator,Input_constraint_iterator > Constraint_range;

template <class Triangulation,class Vertex_handle, class Face_handle>
class Constrained_triangulation_2_wrapper: public Triangulation_2_wrapper<Triangulation,Point_2,Vertex_handle,Face_handle,CGAL::Tag_false>
{
  typedef Triangulation_2_wrapper<Triangulation,Point_2,Vertex_handle,Face_handle,CGAL::Tag_false>    Base;
public:
  typedef typename Base::Edge                                                 Edge;
  #ifndef SWIG
  typedef Triangulation cpp_base;
  #endif

// Creation  
  Constrained_triangulation_2_wrapper():Base(){}
  Constrained_triangulation_2_wrapper(Constraint_range range):Base(){
    for (Input_constraint_iterator it=range.first;it!=range.second;++it)
      this->data.push_back(*it);
  }        
// Queries
  FORWARD_CALL_1(bool,is_constrained,Edge)
  FORWARD_CALL_1(bool,are_there_incident_constraints,Vertex_handle)
  FORWARD_CALL_1(void,push_back,Constraint)

  typedef boost::function_output_iterator< Container_writer<Edge,typename Triangulation::Edge> > Edge_output_iterator;
  void incident_constraints (const Vertex_handle& v, Edge_output_iterator edge_output_iterator){
    this->data.incident_constraints(v.get_data(),edge_output_iterator);
  }      
// Insertion and removal
  FORWARD_CALL_2(void,insert_constraint,Point_2,Point_2)    
  FORWARD_CALL_2(void,insert_constraint,Vertex_handle,Vertex_handle)
  FORWARD_CALL_1(void,remove,Vertex_handle)
  FORWARD_CALL_1(void,remove_incident_constraints,Vertex_handle)
  FORWARD_CALL_2(void,remove_constrained_edge,Face_handle, int)
  
  void insert_constraint_range(Constraint_range range){
    for (Input_constraint_iterator it=range.first;it!=range.second;++it)
      this->data.push_back(*it);
  }
};

#endif //SWIG_CGAL_TRIANGULATION_2_CONSTRAINED_TRIANGULATION_2_H

// Creation
//   Constrained_triangulation_2<Traits,Tds,Itag> ct ( Constrained_triangulation_2 ct1);
//   template<class InputIterator>
//   Constrained_triangulation_2<Traits,Tds,Itag> ct ( InputIterator first, InputIterator last, Traits t=Traits());
// I/O
//   ostream &   ostream& os << Constrained_triangulation_2<Traits,Tds> Ct

