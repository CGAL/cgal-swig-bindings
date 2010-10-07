
//assign JavaData to a class using info() method
//  CNAME is the class to which we add info() method
//  EXTRA  are additional javaimports that should be declared
%define add_JavaData_info_to_class(CNAME,EXTRA)
%extend CNAME {
  JavaData& info(){
    return $self->get_data_ref()->info();
  }
}
%typemap(javaimports)                               CNAME %{import CGAL.Java.JavaData; EXTRA%}
%enddef

