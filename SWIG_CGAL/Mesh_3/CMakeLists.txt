# cpp common library
ADD_SWIG_CGAL_LIBRARY ( CGAL_Mesh_3_cpp Object.cpp CGAL_Kernel_cpp )

# Modules
ADD_SWIG_CGAL_JAVA_MODULE   ( Mesh_3 CGAL_Mesh_3_cpp CGAL_Kernel_cpp )
ADD_SWIG_CGAL_PYTHON_MODULE ( Mesh_3 CGAL_Mesh_3_cpp CGAL_Kernel_cpp )
ADD_SWIG_CGAL_RUBY_MODULE   ( Mesh_3 CGAL_Mesh_3_cpp CGAL_Kernel_cpp )
