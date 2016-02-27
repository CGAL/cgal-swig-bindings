// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_JAVA_EXCEPTION_H
#define SWIG_CGAL_JAVA_EXCEPTION_H

#ifndef SWIG 
#include <SWIG_CGAL/Java/global_functions.h>
#include <iostream>
#include <stdexcept>
 
bool throwJavaException(const char* msg)
{
  jclass exception = JNU_GetEnv()->FindClass("CGAL/Java/SWIGCGALException");
  if(!exception) {
    std::cerr << "Cannot find class \"CGAL.Java.SWIGCGALException\","
              << " and cannot throw java exception!\n";
  }
  else if(JNU_GetEnv()->ThrowNew(exception, msg) != 0)
  {
    std::cerr << 
      "Call to JNU_GetEnv()->ThrowNew(JNU_GetEnv()->FindClass(\"CGAL.Java.SWIGCGALException\"), msg)"
      " failed\n";
  }
  else {
    return true;
  }
  std::cerr << "msg is:\n" << msg << "\n";
  return false;
}
#endif // SWIG


#define JNI_THROW_ON_ERROR(JOBJECT,METHOD,WITH) \
  if (JOBJECT==NULL) throw std::runtime_error(std::string("Error in " #METHOD " -- ")+WITH);

#endif //SWIG_CGAL_JAVA_EXCEPTION_H
