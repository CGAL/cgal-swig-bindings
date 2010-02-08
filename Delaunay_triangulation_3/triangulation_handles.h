#ifndef CGAL_SWIG_TRIANGULATION_HANDLES_H
#define CGAL_SWIG_TRIANGULATION_HANDLES_H

template <class Triangulation>
class CGAL_Cell_handle;

template <class Triangulation>
class CGAL_Vertex_handle{
  typename Triangulation::Vertex_handle data;
  
  public:
  CGAL_Vertex_handle():data(NULL){}
  CGAL_Vertex_handle(typename Triangulation::Vertex_handle v):data(v){}
  typename Triangulation::Vertex_handle get_data() const {return data;}
  EPIC_Point_3 point(){return EPIC_Point_3(data->point());}
  CGAL_Cell_handle<Triangulation> cell(){return CGAL_Cell_handle<Triangulation>(data->cell());}
  
  bool equals(const CGAL_Vertex_handle<Triangulation>& v){
    return data==v.get_data();
  }
  
  #ifdef SWIGPYTHON
  bool __eq__(const CGAL_Vertex_handle<Triangulation>& v){return equals(v);}
  bool __ne__(const CGAL_Vertex_handle<Triangulation>& v){return !equals(v);}
  #endif
  //void set_cell(Cell_handle c)
  //void set_point(Point p)
  //bool is_valid(bool verbose = false) 
  
};


template <class Triangulation>
class CGAL_Cell_handle{
  typename Triangulation::Cell_handle data;
  
  public:
  CGAL_Cell_handle():data(NULL){}
  CGAL_Cell_handle(typename Triangulation::Cell_handle v):data(v){}
  typename Triangulation::Cell_handle get_data() const {return data;}
  
  
  CGAL_Vertex_handle<Triangulation> vertex (int i){return CGAL_Vertex_handle<Triangulation>(data->vertex(i));}
  int index (const CGAL_Vertex_handle<Triangulation>& v){return data->index(v.get_data());}

  bool equals(const CGAL_Cell_handle<Triangulation>& c){
    return data==c.get_data();
  }  

  #ifdef SWIGPYTHON
  bool __eq__(const CGAL_Cell_handle<Triangulation>& c){return equals(c);}
  bool __ne__(const CGAL_Cell_handle<Triangulation>& c){return !equals(c);}
  #endif  
  
  //bool has_vertex ( Vertex_handle v)
  //bool has_vertex ( Vertex_handle v, int & i)
  //Cell_handle neighbor ( int i)
  //int index ( Cell_handle n)
  //bool has_neighbor ( Cell_handle n)
  //bool has_neighbor ( Cell_handle n, int & i)
  //void set_vertex ( int i, Vertex_handle v)
  //void set_vertices ( Vertex_handle v0, Vertex_handle v1, Vertex_handle v2, Vertex_handle v3)
  //void set_neighbor ( int i, Cell_handle n)
  //void set_neighbors ( Cell_handle n0, Cell_handle n1, Cell_handle n2, Cell_handle n3)
  //bool is_valid ( bool verbose = false, int level = 0)
};

#endif //CGAL_SWIG_TRIANGULATION_HANDLES_H
