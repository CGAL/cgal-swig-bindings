%module CGAL_Triangulation_3

%include "../common.i"
%import  "../Common/Macros.h"
%import  "../Kernel/Point_3.h"
%import  "../Kernel/Weighted_point_3.h"
%import  "../Kernel/Segment_3.h"
%import  "../Kernel/Tetrahedron_3.h"
%import  "../Kernel/Triangle_3.h"
%include "../Common/Input_iterator.h"

//include files
%{
  #include "Delaunay_triangulation_3.h"
  #include "Regular_triangulation_3.h"
  #include "triangulation_handles.h"
  #include "../Common/triple.h"
  #include "triangulation_iterators.h"
%}

%pragma(java) jniclassimports=%{import CGAL.Kernel.Point_3; import CGAL.Kernel.Weighted_point_3; import java.util.Iterator; import java.util.Collection;%}


//definitions
%include "Triangulation_3.h"
%include "Delaunay_triangulation_3.h"
%include "Regular_triangulation_3.h"
%include "triangulation_handles.h"
%include "../Common/triple.h"
%include "triangulation_iterators.h"
%include "../Common/Output_iterator.h"
%include "../Common/Reference_wrapper.h"

%include "config.i"

//typemaps for Input iterator(s)
Typemap_for_Input_iterator(Weighting_helper_3<CGAL::Tag_false>::Point_range,Point_3,Point_3::cpp_base,SWIGTYPE_p_Point_3,"(LCGAL/Kernel/Point_3;)J",insert_range)
Typemap_for_Input_iterator(Weighting_helper_3<CGAL::Tag_true>::Point_range,Weighted_point_3,Weighted_point_3::cpp_base,SWIGTYPE_p_Weighted_point_3,"(LCGAL/Kernel/Weighted_point_3;)J",insert_range)

//WARNING CANNOT DECLARE MORE THAT ONE CLASS
//OTHERWISE GOT A COMPILATION ERROR. SOLVED IN SWIG 2

//#ifdef   SWIG_EXPOSE_TRIANGULATION_3
//%import "declare_triangulation_3.i"
//Declare_triangulation_3(Triangulation_3,CGAL_T3)
//#endif //SWIG_EXPOSE_TRIANGULATION_3

#ifdef   SWIG_EXPOSE_DELAUNAY_TRIANGULATION_3
%import "declare_Delaunay_triangulation_3.i"
Declare_Delaunay_triangulation_3(Delaunay_triangulation_3,CGAL_DT3)
#endif //SWIG_EXPOSE_DELAUNAY_TRIANGULATION_3

//#ifdef   SWIG_EXPOSE_REGULAR_TRIANGULATION_3
//%import "declare_regular_triangulation_3.i"
//Declare_regular_triangulation_3(Regular_triangulation_3,CGAL_RT3)
//#endif //SWIG_EXPOSE_REGULAR_TRIANGULATION_3

//References
%template(Ref_int) Reference_wrapper<int>;

