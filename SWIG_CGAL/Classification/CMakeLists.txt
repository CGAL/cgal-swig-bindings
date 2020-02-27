SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

find_package(Eigen3 3.1.0)

find_package( Boost OPTIONAL_COMPONENTS serialization iostreams )
if( WIN32 )
# to avoid a warning with old cmake 
  set(_Boost_BZIP2_HEADERS             "boost/iostreams/filter/bzip2.hpp")
  set(_Boost_ZLIB_HEADERS              "boost/iostreams/filter/zlib.hpp")
  find_package( Boost OPTIONAL_COMPONENTS bzip2 zlib)
else()
  find_package(ZLIB QUIET)
endif()


if (EIGEN3_FOUND AND Boost_SERIALIZATION_FOUND AND Boost_IOSTREAMS_FOUND)
  include( ${EIGEN3_USE_FILE} )

  if(TARGET Boost::serialization AND TARGET Boost::iostreams)
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH} Boost::serialization Boost::iostreams)
  else()
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH}
      ${Boost_SERIALIZATION_LIBRARY}
      ${Boost_IOSTREAMS_LIBRARY})
  endif()

  if (TBB_FOUND)
    set(LIBSTOLINKWITH ${LIBSTOLINKWITH} TBB::tbb TBB::tbbmalloc Threads::Threads)
  endif()
  
  # Modules
  ADD_SWIG_CGAL_JAVA_MODULE   ( Classification ${LIBSTOLINKWITH} )
  ADD_SWIG_CGAL_PYTHON_MODULE ( Classification ${LIBSTOLINKWITH} "-keyword" )
  ADD_SWIG_CGAL_RUBY_MODULE   ( Classification ${LIBSTOLINKWITH} )

else()
  if (NOT EIGEN3_FOUND)
    message(STATUS "NOTICE: Classification bindings requires Eigen version 3.1 or greater, and will not be compiled.")
  endif()
  if (NOT Boost_SERIALIZATION_FOUND)
    message(STATUS "NOTICE: Classification bindings requires Boost Serialization, and will not be compiled.")
  endif()
  if (NOT Boost_IOSTREAMS_FOUND)
    message(STATUS "NOTICE: Classification bindings requires Boost IO Streams, and will not be compiled.")
  endif()
endif()
