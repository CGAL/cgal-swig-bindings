#ifndef SWIG_CGAL_COMMON_DECL_H
#define SWIG_CGAL_COMMON_DECL_H
#  if defined(_WIN32) || defined(__CYGWIN__)
#    define SWIG_CGAL_DLL_IMPORT __declspec(dllimport)
#    define SWIG_CGAL_DLL_EXPORT __declspec(dllexport)
#    define SWIG_CGAL_DLL_LOCAL
#  else
    #if __GNUC__ >= 4
      #define SWIG_CGAL_DLL_IMPORT __attribute__ ((visibility ("default")))
      #define SWIG_CGAL_DLL_EXPORT __attribute__ ((visibility ("default")))
      #define SWIG_CGAL_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
    #else
      #define SWIG_CGAL_DLL_IMPORT
      #define SWIG_CGAL_DLL_EXPORT
      #define SWIG_CGAL_DLL_LOCAL
    #endif
#endif
#endif // SWIG_CGAL_COMMON_DECL_H
