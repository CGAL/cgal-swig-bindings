%module CGAL_Spatial_searching

%include "../common.i"
%import  "../Common/Macros.h"
%import  "../Kernel/Point_2.h"
%import  "../Kernel/Point_3.h"
%include "../Common/Input_iterator.h"

//include files
%{
  #include "../Kernel/typedefs.h"
  #include "Kd_tree.h"
  #include "NN_search.h"
  #include "Fuzzy_objects.h"
%}

%include "config.i"

//definitions
%include "Kd_tree.h"
%include "NN_search.h"
%include "Fuzzy_objects.h"


%{
  #include "typedefs.h"
%}
%include "typedefs.h"

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Point_3;  import java.util.Iterator; import java.util.Collection;%}

//==================

//typemap for point input iterator
Typemap_for_Input_iterator(Point_range_helper<Point_2>::type,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",insert_range)
Typemap_for_Input_iterator(Point_range_helper<Point_3>::type,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",insert_range)

%typemap(javaimports)       Fuzzy_sphere_wrapper%{import CGAL.Kernel.Point_2;%}
%template(Fuzzy_sphere_2)   Fuzzy_sphere_wrapper <CGAL_FS_2,Point_2>;
%typemap(javaimports)       Fuzzy_iso_box_wrapper%{import CGAL.Kernel.Point_2;%}
%template(Fuzzy_iso_box_2)  Fuzzy_iso_box_wrapper<CGAL_FB_2,Point_2>;
//~ %typemap(javaimports)       Kd_tree_wrapper%{import CGAL.Kernel.Point_2;import java.util.Iterator; import java.util.Collection;%}
%typemap(javaimports)       Kd_tree_wrapper%{import CGAL.Kernel.Point_2;import java.util.Iterator;%}
%template(Orthogonal_incremental_neighbor_search_tree_2) Kd_tree_wrapper<CGAL_OI_T_2,Point_2,SWIG_FS_2,SWIG_FB_2>;
%typemap(javaimports)       NN_search_wrapper%{import CGAL.Kernel.Point_2;%}
%template(Orthogonal_incremental_neighbor_search_2) NN_search_wrapper<CGAL_OI_S_2,Point_2,SWIG_OI_T_2>;

%include "std_pair.i"
%typemap(javaimports)       std::pair<Point_2,double> %{import CGAL.Kernel.Point_2;%}
%template(Point_with_transformed_distance_2) std::pair<Point_2,double>;

//typemaps for iterators
Iterator_for_java(Kd_tree_iterator,Point_2,import CGAL.Kernel.Point_2;)
%template(Kd_tree_iterator_2) Kd_tree_iterator<CGAL_OI_T_2,Point_2 >;

Iterator_for_java(NN_search_iterator,Point_with_transformed_distance_2,import CGAL.Kernel.Point_2;)
%template(NN_search_iterator_2) NN_search_iterator<CGAL_OI_S_2,SWIG_PTD_2 >;



//==================

//  typedef Kd_tree_iterator<Cpp_base,Query> Iterator;
//  typedef NN_search_iterator<cpp_base,Point_with_transformed_distance> Iterator;
//  typedef std::pair<Point_d,double>  Point_with_transformed_distance;




//~ typedef CGAL::Search_traits_2<EPIC_Kernel>                        CGAL_ST_2;
//~ typedef CGAL::Fuzzy_sphere <CGAL_ST_2>                            CGAL_FS_2;
//~ typedef CGAL::Fuzzy_iso_box<CGAL_ST_2>                            CGAL_FB_2;
//~ //2D search methods
//~ typedef CGAL::Orthogonal_incremental_neighbor_search<CGAL_ST_2>   CGAL_OI_S_2;
//~ typedef CGAL::Incremental_neighbor_search<CGAL_ST_2>              CGAL_I_S_2;
//~ typedef CGAL::K_neighbor_search<CGAL_ST_2>                        CGAL_K_S_2;
//~ typedef CGAL::Orthogonal_k_neighbor_search<CGAL_ST_2>             CGAL_OK_S_2;
//~ //2D trees
//~ typedef CGAL_OI_S_2::Tree                                         CGAL_OI_T_2;
//~ typedef CGAL_I_S_2 ::Tree                                         CGAL_I_T_2;
//~ typedef CGAL_K_S_2 ::Tree                                         CGAL_K_T_2;
//~ typedef CGAL_OK_S_2::Tree                                         CGAL_OK_T_2;


//~ //vertex range
//~ %include "std_pair.i"
//~ %template(Vertex_range) std::pair<double,double>;

//~ //Face Interval_3
//~ %include "../Common/triple.h"
//~ %template(Face_Interval_3)  CGAL_SWIG::Triple<double,double,double>;

//~ %pragma(java) jniclassimports=%{import CGAL.Kernel.Point_2; import CGAL.Kernel.Weighted_point_2;  import java.util.Iterator; import java.util.Collection;%}

//~ //typemap for point input iterator
//~ Typemap_for_Input_iterator(Weighting_helper<CGAL::Tag_false>::Point_range,Point_2,Point_2::cpp_base,SWIGTYPE_p_Point_2,"(LCGAL/Kernel/Point_2;)J",make_alpha_shape)
//~ //typemap for weighted point input iterator
//~ Typemap_for_Input_iterator(Weighting_helper<CGAL::Tag_true>::Point_range,Weighted_point_2,Weighted_point_2::cpp_base,SWIGTYPE_p_Weighted_point_2,"(LCGAL/Kernel/Weighted_point_2;)J",make_alpha_shape)

//~ %import "declare_alpha_shape_2.i"

//~ #ifdef   SWIG_EXPOSE_ALPHA_SHAPE_2
//~ Declare_alpha_shape_2(Alpha_shape_2,CGAL_AS2)
//~ #endif //SWIG_EXPOSE_ALPHA_SHAPE_2
//~ #ifdef   SWIG_EXPOSE_WEIGHTED_ALPHA_SHAPE_2
//~ Declare_weighted_alpha_shape_2(Weighted_alpha_shape_2,CGAL_WAS2)
//~ #endif //SWIG_EXPOSE_WEIGHTED_ALPHA_SHAPE_2

