#ifndef SWIG_CGAL_JAVA_TYPEMAPS_I
#define SWIG_CGAL_JAVA_TYPEMAPS_I

//IN typemap for reading points from an array of double
%define Typemap_in_double_Array_to_Point_3_Vector
%typemap(jni) boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > "jdoubleArray"  //replace in jni class
%typemap(jtype) boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > "double[]"   //replace in java wrapping class
%typemap(jstype) boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > "double[]"  //replace in java function args
%typemap(javain) boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > "$javainput" //replace in java function call to wrapped function

%typemap(in) boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > {
  boost::shared_ptr<std::vector<EPIC_Kernel::Point_3> > res(new std::vector<EPIC_Kernel::Point_3>());
  const jsize size = jenv->GetArrayLength($input) / 3;
  res->reserve((const std::size_t) size);
  jboolean is_copy;
  jdouble* points = jenv->GetDoubleArrayElements($input, &is_copy);
  for (int i = 0 ; i < size ; i++){
    res->push_back(EPIC_Kernel::Point_3(points[i*3],points[i*3+1],points[i*3+2]));
  }
  jenv->ReleaseDoubleArrayElements($input, points, JNI_ABORT);
  $1=res;
}
%enddef

//IN typemap for reading points from an array of double
%define Typemap_in_int_Array_to_Triple_int_Vector
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

//OUT typemap for writting segments into a java array
%define Typemap_out_Segment_3_Vector_to_double_Array
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

#endif //SWIG_CGAL_JAVA_TYPEMAPS_I
