from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Weighted_point_2
from CGAL.CGAL_Alpha_shape_2 import Alpha_shape_2
from CGAL.CGAL_Alpha_shape_2 import Weighted_alpha_shape_2
from CGAL.CGAL_Alpha_shape_2 import Weighted_alpha_shape_2_Face_handle
from CGAL.CGAL_Alpha_shape_2 import GENERAL, EXTERIOR, SINGULAR, REGULAR, INTERIOR
from CGAL.CGAL_Alpha_shape_2 import Alpha_shape_2_Vertex_handle
from CGAL.CGAL_Alpha_shape_2 import Alpha_shape_2_Face_handle
from CGAL.CGAL_Alpha_shape_2 import Face_Interval_3


lst = []
lst.append( Point_2(0,0) )
lst.append( Point_2(0,4) )
lst.append( Point_2(44,0) )
lst.append( Point_2(44,5) )
lst.append( Point_2(444,51) )
lst.append( Point_2(14,1) )

t = Alpha_shape_2(lst,0,GENERAL)
t2 = Alpha_shape_2(lst,0)
t.clear()
t.make_alpha_shape(lst)


for d in t.alpha():
    print(d)


for v in t.finite_vertices():
    type = t.classify(v)
    print(v.get_range()[0])

    if type == INTERIOR:
        print("INTERIOR")
    elif type == SINGULAR:
        print("SINGULAR")
    elif type == REGULAR:
        print("REGULAR")
    elif type == EXTERIOR:
        print("EXTERIOR")


for f in t.finite_faces():
    i=f.get_ranges(0)
    print(i.first)
    print(i.second)
    print(i.third)


was = Weighted_alpha_shape_2()
lst_wp = []
lst_wp.append( Weighted_point_2( Point_2(0,0) ,1 ) )
lst_wp.append( Weighted_point_2( Point_2(0,4) ,1 ) )
lst_wp.append( Weighted_point_2( Point_2(44,0) ,1 ) )
lst_wp.append( Weighted_point_2( Point_2(44,5) ,1 ) )
lst_wp.append( Weighted_point_2( Point_2(444,51) ,1 ) )
lst_wp.append( Weighted_point_2( Point_2(14,1) ,1 ) )

was.make_alpha_shape(lst_wp)
