// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------


#ifndef SWIG_CGAL_JAVA_TYPEMAPS_I
#define SWIG_CGAL_JAVA_TYPEMAPS_I

//IN typemap for reading points from an array of double
%define SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in_advanced(KERNEL)
%typemap(jni) boost::shared_ptr<std::vector<KERNEL::Point_3> > "jdoubleArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<KERNEL::Point_3> > "double[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<KERNEL::Point_3> > "double[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<KERNEL::Point_3> > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<KERNEL::Point_3> > {
  boost::shared_ptr<std::vector<KERNEL::Point_3> > res(new std::vector<KERNEL::Point_3>());
  const jsize size = jenv->GetArrayLength($input) / 3;
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jdouble* points = jenv->GetDoubleArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back(KERNEL::Point_3(points[i*3],points[i*3+1],points[i*3+2]));
  }
  jenv->ReleaseDoubleArrayElements($input, points, JNI_ABORT);
  $1=res;
}
%enddef
%define SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in
SWIG_CGAL_array_of_double_to_vector_of_point_3_typemap_in_advanced(EPIC_Kernel)
%enddef

//IN typemap for reading vector of points from an array of array of double
%define SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_point_3_typemap_in_advanced(KERNEL)
%typemap(jni) boost::shared_ptr<std::vector< std::vector<KERNEL::Point_3> > > "jobjectArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector< std::vector<KERNEL::Point_3> > > "double[][]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector< std::vector<KERNEL::Point_3> > > "double[][]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector< std::vector<KERNEL::Point_3> > > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector< std::vector<KERNEL::Point_3> > > {
  boost::shared_ptr<std::vector< std::vector<KERNEL::Point_3> > > res(new std::vector< std::vector<KERNEL::Point_3> >());

  const jsize size_of_lines = jenv->GetArrayLength($input);
  res->resize(size_of_lines);

  jboolean is_copy;

  for (jsize l=0;l<size_of_lines;++l){
    jdoubleArray line = (jdoubleArray) jenv->GetObjectArrayElement($input,l);

    const jsize size = jenv->GetArrayLength(line) / 3;
    (*res)[l].reserve((const std::size_t) size);
    jdouble* points = jenv->GetDoubleArrayElements(line, &is_copy);
    for (int i = 0 ; i < size ; i++){
      (*res)[l].push_back(KERNEL::Point_3(points[i*3],points[i*3+1],points[i*3+2]));
    }
    jenv->ReleaseDoubleArrayElements(line, points, JNI_ABORT);
  }
  $1=res;
}
%enddef
%define SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_point_3_typemap_in
SWIG_CGAL_array_of_array_of_double_to_vector_of_vector_of_point_3_typemap_in_advanced(EPIC_Kernel)
%enddef

//IN typemap for reading a vector of triple of int from an array of int
%define SWIG_CGAL_array_of_int_to_vector_of_triple_of_int_typemap_in
%typemap(jni) boost::shared_ptr<std::vector<boost::tuple<int,int,int> > > "jintArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<boost::tuple<int,int,int> > > "int[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<boost::tuple<int,int,int> > > "int[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<boost::tuple<int,int,int> > > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<boost::tuple<int,int,int> > > {
  boost::shared_ptr<std::vector<boost::tuple<int,int,int> > > res(new std::vector<boost::tuple<int,int,int> >());
  const jsize size = jenv->GetArrayLength($input) / 3;
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jint* indices = jenv->GetIntArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back(boost::tuple<int,int,int>(indices[i*3],indices[i*3+1],indices[i*3+2]));
  }
  jenv->ReleaseIntArrayElements($input, indices, JNI_ABORT);
  $1=res;
}
%enddef

//IN typemap for reading a vector of triple of int put into a vector of int from an array of int
%define SWIG_CGAL_array_of_int_to_vector_of_vector_of_int_typemap_in
%typemap(jni) boost::shared_ptr<std::vector<std::vector<int> > > "jintArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<std::vector<int> > > "int[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<std::vector<int> > > "int[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<std::vector<int> > > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<std::vector<int> > > {
  boost::shared_ptr<std::vector<std::vector<int> > > res(new std::vector<std::vector<int> >());
  const jsize size = jenv->GetArrayLength($input) / 3;
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jint* indices = jenv->GetIntArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back( std::vector<int>(3) );
    res->back()[i*3]=indices[i*3];
    res->back()[i*3+1]=indices[i*3+1];
    res->back()[i*3+2]=indices[i*3+2];
  }
  jenv->ReleaseIntArrayElements($input, indices, JNI_ABORT);
  $1=res;
}
%enddef

//IN typemap for reading a vector of pair of int from an array of int
%define SWIG_CGAL_array_of_int_to_vector_of_pair_of_int_typemap_in
%typemap(jni) boost::shared_ptr<std::vector< std::pair<int,int> > > "jintArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector< std::pair<int,int> > > "int[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector< std::pair<int,int> > > "int[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector< std::pair<int,int> > > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector< std::pair<int,int> > > {
  boost::shared_ptr<std::vector< std::pair<int,int> > > res(new std::vector< std::pair<int,int> >());
  const jsize size = jenv->GetArrayLength($input) / 2;
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jint* indices = jenv->GetIntArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back( std::pair<int,int>(indices[i*2],indices[i*2+1]));
  }
  jenv->ReleaseIntArrayElements($input, indices, JNI_ABORT);
  $1=res;
}
%enddef

//IN typemap for a vector of int from an array of int
%define SWIG_CGAL_array_of_int_to_vector_of_int_typemap_in
%typemap(jni) boost::shared_ptr<std::vector<int> > "jintArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<int> > "int[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<int> > "int[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<int> > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<int> > {
  boost::shared_ptr<std::vector<int> > res(new std::vector<int>());
  const jsize size = jenv->GetArrayLength($input);
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jint* indices = jenv->GetIntArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back(indices[i]);
  }
  jenv->ReleaseIntArrayElements($input, indices, JNI_ABORT);
  $1=res;
}
%enddef

//IN typemap for a vector of float from an array of double
%define SWIG_CGAL_array_of_float_to_vector_of_float_typemap_in
%typemap(jni) boost::shared_ptr<std::vector<float> > "jfloatArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<float> > "float[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<float> > "float[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<float> > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<float> > {
  boost::shared_ptr<std::vector<float> > res(new std::vector<float>());
  const jsize size = jenv->GetArrayLength($input);
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jfloat* indices = jenv->GetFloatArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back(indices[i]);
  }
  jenv->ReleaseFloatArrayElements($input, indices, JNI_ABORT);
  $1=res;
}
%enddef

//IN typemap for a vector of double from an array of double
%define SWIG_CGAL_array_of_double_to_vector_of_double_typemap_in
%typemap(jni) boost::shared_ptr<std::vector<double> > "jdoubleArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<double> > "double[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<double> > "double[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<double> > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<double> > {
  boost::shared_ptr<std::vector<double> > res(new std::vector<double>());
  const jsize size = jenv->GetArrayLength($input);
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jdouble* indices = jenv->GetDoubleArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back(indices[i]);
  }
  jenv->ReleaseDoubleArrayElements($input, indices, JNI_ABORT);
  $1=res;
}
%enddef

// IN typemap from an array of 9-uple of double to vector of triangles
%define SWIG_CGAL_array_of_array9_of_double_to_vector_of_triangle_3_typemap_in
%typemap(jni) boost::shared_ptr< std::vector<Triangle_3::cpp_base>  > "jobjectArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr< std::vector<Triangle_3::cpp_base>  > "double[][]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr< std::vector<Triangle_3::cpp_base>  > "double[][]"  //replace in java function args
%typemap(javain) boost::shared_ptr< std::vector<Triangle_3::cpp_base>  > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr< std::vector<Triangle_3::cpp_base>  > {
  boost::shared_ptr< std::vector<Triangle_3::cpp_base> > res(new std::vector<Triangle_3::cpp_base>());

  const jsize nb_arrays = jenv->GetArrayLength($input);
  res->resize(nb_arrays);

  jboolean is_copy;

  for (jsize l=0;l<nb_arrays;++l){
    jdoubleArray line = (jdoubleArray) jenv->GetObjectArrayElement($input,l);
    if (jenv->GetArrayLength(line)!=9){
      throw std::runtime_error("Arrays must be of size 9");
    }
    jdouble* points = jenv->GetDoubleArrayElements(line, &is_copy);
    EPIC_Kernel::Point_3 p1(points[0],points[1],points[2]);
    EPIC_Kernel::Point_3 p2(points[3],points[4],points[5]);
    EPIC_Kernel::Point_3 p3(points[6],points[7],points[8]);

    (*res)[l]=Triangle_3::cpp_base(p1,p2,p3);
    jenv->ReleaseDoubleArrayElements(line, points, JNI_ABORT);
  }
  $1=res;
}
%enddef

// IN typemap from an array of 6-uple of double to vector of triangles
%define SWIG_CGAL_array_of_array6_of_double_to_vector_of_segment_3_typemap_in
%typemap(jni) boost::shared_ptr< std::vector<Segment_3::cpp_base> > "jobjectArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr< std::vector<Segment_3::cpp_base> > "double[][]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr< std::vector<Segment_3::cpp_base> > "double[][]"  //replace in java function args
%typemap(javain) boost::shared_ptr< std::vector<Segment_3::cpp_base> > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr< std::vector<Segment_3::cpp_base> > {
  boost::shared_ptr< std::vector<Segment_3::cpp_base> > res(new std::vector<Segment_3::cpp_base>());

  const jsize nb_arrays = jenv->GetArrayLength($input);
  res->resize(nb_arrays);

  jboolean is_copy;

  for (jsize l=0;l<nb_arrays;++l){
    jdoubleArray line = (jdoubleArray) jenv->GetObjectArrayElement($input,l);
    if (jenv->GetArrayLength(line)!=6){
      throw std::runtime_error("Arrays must be of size 6");
    }
    jdouble* points = jenv->GetDoubleArrayElements(line, &is_copy);
    EPIC_Kernel::Point_3 p1(points[0],points[1],points[2]);
    EPIC_Kernel::Point_3 p2(points[3],points[4],points[5]);

    (*res)[l]=Segment_3::cpp_base(p1,p2);
    jenv->ReleaseDoubleArrayElements(line, points, JNI_ABORT);
  }
  $1=res;
}
%enddef

//OUT typemap for vector of int into a java array
%define SWIG_CGAL_vector_of_int_to_array_of_int_typemap_out
%typemap(jni) boost::shared_ptr<std::vector<int> > "jintArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<int> > "int[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<int> > "int[]"  //replace in java function args
%typemap(javaout) boost::shared_ptr<std::vector<int> > "{return $jnicall;}" //replace in java function call to wrapped function

%typemap(out) boost::shared_ptr<std::vector<int> > {
  const jsize size = $1->size();
  jintArray jInts = jenv->NewIntArray(size);
  jenv->SetIntArrayRegion(jInts, 0, size, &((*$1)[0]));
  $result=jInts;
}
%enddef

//OUT typemap for writting segments into a java array
%define SWIG_CGAL_vector_of_segment_3_to_array_of_double_typemap_out
%typemap(jni) boost::shared_ptr<std::vector<EPIC_Kernel::Segment_3> > "jdoubleArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<EPIC_Kernel::Segment_3> > "double[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<EPIC_Kernel::Segment_3> > "double[]"  //replace in java function args
%typemap(javaout) boost::shared_ptr<std::vector<EPIC_Kernel::Segment_3> > "{return $jnicall;}" //replace in java function call to wrapped function

%typemap(out) boost::shared_ptr<std::vector<EPIC_Kernel::Segment_3> > {
  const jsize size = $1->size();

  jdoubleArray jSegments = jenv->NewDoubleArray(size*6);
  jdouble tmp_seg[6];

  for (int i = 0 ; i < size; ++i){
    const EPIC_Kernel::Segment_3& seg = (*$1)[i];
    tmp_seg[0] = seg.source().x();
    tmp_seg[1] = seg.source().y();
    tmp_seg[2] = seg.source().z();
    tmp_seg[3] = seg.target().x();
    tmp_seg[4] = seg.target().y();
    tmp_seg[5] = seg.target().z();
    jenv->SetDoubleArrayRegion(jSegments, 6*i, 6, tmp_seg);
  }

  $result=jSegments;
}
%enddef

//OUT typemap for writting points into a java array
%define SWIG_CGAL_vector_of_points_3_to_array_of_double_typemap_out_advanced(KERNEL)
%typemap(jni) boost::shared_ptr<std::vector<KERNEL::Point_3> > "jdoubleArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<KERNEL::Point_3> > "double[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<KERNEL::Point_3> > "double[]"  //replace in java function args
%typemap(javaout) boost::shared_ptr<std::vector<KERNEL::Point_3> > "{return $jnicall;}" //replace in java function call to wrapped function

%typemap(out) boost::shared_ptr<std::vector<KERNEL::Point_3> > {
  const jsize size = $1->size();

  jdoubleArray jPoints = jenv->NewDoubleArray(size*3);
  jdouble tmp_pt[3];

  for (int i = 0 ; i < size; ++i){
    const KERNEL::Point_3& pt = (*$1)[i];
    tmp_pt[0] = pt.x();
    tmp_pt[1] = pt.y();
    tmp_pt[2] = pt.z();
    jenv->SetDoubleArrayRegion(jPoints, 3*i, 3, tmp_pt);
  }

  $result=jPoints;
}
%enddef

%define SWIG_CGAL_vector_of_points_3_to_array_of_double_typemap_out
SWIG_CGAL_vector_of_points_3_to_array_of_double_typemap_out_advanced(EPIC_Kernel)
%enddef


#endif //SWIG_CGAL_JAVA_TYPEMAPS_I
