#include <SWIG_CGAL/Kernel/Polygon_2.h>

Polygon_2::Polygon_2():data(){}
//~ Polygon_2::Polygon_2(Point_range_2 range):data(range.first,range.second){}


bool Polygon_2::equals(const Polygon_2& r){return data==r.get_data();}

std::string Polygon_2::toString(){
  std::stringstream sstr;
  sstr << data;
  return sstr.str();
}

#ifdef NO_SWIG_OR_PYTHON
bool Polygon_2::__ne__(const Polygon_2& r){return data!=r.get_data();}
#endif


