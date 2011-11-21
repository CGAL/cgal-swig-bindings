
//assign JavaData to a class using info() method
//  CNAME is the class to which we add info() method
//  EXTRA  are additional javaimports that should be declared
%define SWIG_CGAL_add_JavaData_info_to_class(CNAME,EXTRA)
%extend CNAME {
  JavaData& info(){
    return $self->get_data()->info();
  }
  void get_info(JavaData& jd){
    jd=$self->get_data()->info();
  }
  void set_info(const JavaData& jd){
    $self->get_data()->info()=jd;
  }
}
%typemap(javaimports)                               CNAME %{import CGAL.Java.JavaData; EXTRA%}
%enddef

