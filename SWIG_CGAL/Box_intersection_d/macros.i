// ------------------------------------------------------------------------------
// Copyright (c) 2014 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_BOX_INTERSECTION_D_MACROS_I
#define SWIG_CGAL_BOX_INTERSECTION_D_MACROS_I

%define declare_box_intersection_d_box_functions(BOX_WRAPPER, CALLBACK_WRAPPER)

%inline %{
  void box_intersection_d(  Wrapper_iterator_helper< BOX_WRAPPER >::input range1
                          , Wrapper_iterator_helper< BOX_WRAPPER >::input range2
                          , CALLBACK_WRAPPER& callback
                          , int cutoff=10
                          , Topology topology=CLOSED
                          , Setting setting=BIPARTITE
  )
  {
    std::vector<BOX_WRAPPER::cpp_base> cpp_range1(range1.first, range1.second);
    std::vector<BOX_WRAPPER::cpp_base> cpp_range2(range2.first, range2.second);
    CGAL::box_intersection_d( cpp_range1.begin(), cpp_range1.end(),
                              cpp_range2.begin(), cpp_range2.end(),
                              callback, (std::ptrdiff_t) cutoff,
                              CGAL::enum_cast< CGAL::Box_intersection_d::Topology >(topology),
                              CGAL::enum_cast< CGAL::Box_intersection_d::Setting >(setting)
    );
  }

  void box_intersection_all_pairs_d(  Wrapper_iterator_helper< BOX_WRAPPER >::input range1
                                    , Wrapper_iterator_helper< BOX_WRAPPER >::input range2
                                    , CALLBACK_WRAPPER& callback
                                    , Topology topology=CLOSED
  )
  {
    std::vector<BOX_WRAPPER::cpp_base> cpp_range1(range1.first, range1.second);
    std::vector<BOX_WRAPPER::cpp_base> cpp_range2(range2.first, range2.second);
    CGAL::box_intersection_all_pairs_d( cpp_range1.begin(), cpp_range1.end(),
                                        cpp_range2.begin(), cpp_range2.end(),
                                        callback,
                                        CGAL::enum_cast< CGAL::Box_intersection_d::Topology >(topology)
    );
  }

  void box_self_intersection_d(  Wrapper_iterator_helper< BOX_WRAPPER >::input range
                               , CALLBACK_WRAPPER& callback
                               , int cutoff=10
                               , Topology topology=CLOSED
  )
  {
    std::vector<BOX_WRAPPER::cpp_base> cpp_range(range.first, range.second);
    CGAL::box_self_intersection_d(cpp_range.begin(), cpp_range.end(),
                                  callback, (std::ptrdiff_t) cutoff,
                                  CGAL::enum_cast< CGAL::Box_intersection_d::Topology >(topology)
    );
  }

  void box_self_intersection_all_pairs_d(  Wrapper_iterator_helper< BOX_WRAPPER >::input range
                                         , CALLBACK_WRAPPER& callback
                                         , Topology topology=CLOSED
  )
  {
    std::vector<BOX_WRAPPER::cpp_base> cpp_range(range.first, range.second);
    CGAL::box_self_intersection_all_pairs_d(cpp_range.begin(), cpp_range.end(),
                                            callback,
                                            CGAL::enum_cast< CGAL::Box_intersection_d::Topology >(topology)
    );
  }
%}

%enddef

#endif //SWIG_CGAL_BOX_INTERSECTION_D_MACROS_I
