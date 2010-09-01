//macros defining the underlying types used
%{
#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/Complex_2_in_triangulation_3.h>
  
typedef CGAL::Surface_mesh_default_triangulation_3 C2T3_DT;
typedef CGAL::Complex_2_in_triangulation_3<C2T3_DT> C2T3;

%}
