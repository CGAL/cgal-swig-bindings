%{
typedef CGAL::Triangulation_3<EPIC_Kernel>                              CGAL_T3;
typedef CGAL::Delaunay_triangulation_3<EPIC_Kernel>                     CGAL_DT3;
typedef CGAL::Regular_triangulation_euclidean_traits_3<EPIC_Kernel>     RT_traits;
typedef CGAL::Regular_triangulation_3< RT_traits >                      CGAL_RT3;
%}

//macro to decide which class to expose
#define SWIG_EXPOSE_TRIANGULATION_3
#define SWIG_EXPOSE_DELAUNAY_TRIANGULATION_3
#define SWIG_EXPOSE_REGULAR_TRIANGULATION_3
