SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

find_package(Eigen3 3.1.0)

find_package( Boost OPTIONAL_COMPONENTS serialization iostreams )

if(Boost_SERIALIZATION_FOUND AND Boost_IOSTREAMS_FOUND)
  if(TARGET Boost::serialization AND TARGET Boost::iostreams)
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH} Boost::serialization Boost::iostreams)
  else()
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH}
      ${Boost_SERIALIZATION_LIBRARY}
      ${Boost_IOSTREAMS_LIBRARY})
  endif()
  add_definitions(-DCGAL_LINKED_WITH_BOOST_SERIALIZATION -DCGAL_LINKED_WITH_BOOST_IOSTREAMS)
else()
  if (NOT Boost_SERIALIZATION_FOUND)
    message(STATUS "NOTICE: Classification IO functions require Boost Serialization, and will not be compiled.")
  endif()
  if (NOT Boost_IOSTREAMS_FOUND)
    message(STATUS "NOTICE: Classification IO functions require Boost IO Streams, and will not be compiled.")
  endif()
endif()

if (EIGEN3_FOUND )
  include(CGAL_Eigen3_support)
  set(LIBSTOLINKWITH ${LIBSTOLINKWITH} CGAL::Eigen3_support)
  if (TBB_FOUND)
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
  endif()
  # Modules
  ADD_SWIG_CGAL_JAVA_MODULE   ( Classification ${LIBSTOLINKWITH} )
  ADD_SWIG_CGAL_PYTHON_MODULE ( Classification ${LIBSTOLINKWITH} "-keyword" )
  ADD_SWIG_CGAL_RUBY_MODULE   ( Classification ${LIBSTOLINKWITH} )
else()
    message(STATUS "NOTICE: Classification bindings requires Eigen version 3.1 or greater, and will not be compiled.")
endif()

