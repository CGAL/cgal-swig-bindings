SET (LIBSTOLINKWITH CGAL_Kernel_cpp)

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Polygon_mesh_processing ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_PYTHON_MODULE ( Polygon_mesh_processing ${LIBSTOLINKWITH} )
ADD_SWIG_CGAL_RUBY_MODULE   ( Polygon_mesh_processing ${LIBSTOLINKWITH} )
