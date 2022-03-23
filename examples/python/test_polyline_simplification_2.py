from __future__ import print_function

from CGAL.CGAL_Kernel import Polygon_2
from CGAL.CGAL_Kernel import Point_2

from CGAL import CGAL_Polyline_simplification_2
from CGAL.CGAL_Polyline_simplification_2 import Stop_below_count_ratio_threshold
from CGAL.CGAL_Polyline_simplification_2 import Squared_distance_cost
from CGAL.CGAL_Polyline_simplification_2 import PS2_Constrained_Delaunay_triangulation_plus_2
from CGAL.CGAL_Polyline_simplification_2 import PS2_Constrained_Delaunay_triangulation_plus_2_Constraint_id
from CGAL.CGAL_Polyline_simplification_2 import PS2_Constrained_Delaunay_triangulation_plus_2_Vertex_handle

ptlst = []
ptlst.append(Point_2(0, 0))
ptlst.append(Point_2(0, 1))
ptlst.append(Point_2(1, 1))

# test polygon function
poly = Polygon_2(ptlst)
poly_simplified = CGAL_Polyline_simplification_2.simplify(
    poly, Squared_distance_cost(), Stop_below_count_ratio_threshold(0.5))

# test point version
outlist = []
CGAL_Polyline_simplification_2.simplify(ptlst, Squared_distance_cost(),
                                        Stop_below_count_ratio_threshold(0.5),
                                        outlist)

# test cdt version
polyline1 = []
polyline1.append(Point_2(0, 0))
polyline1.append(Point_2(0, 1))
polyline1.append(Point_2(0, 2))
polyline1.append(Point_2(0, 3))

polyline2 = []
polyline2.append(Point_2(1, 0))
polyline2.append(Point_2(1, 1))
polyline2.append(Point_2(1, 2))
polyline2.append(Point_2(1, 3))

polyline3 = []
polyline3.append(Point_2(-1, -1))
polyline3.append(Point_2(2, -1))
polyline3.append(Point_2(2, 4))
polyline3.append(Point_2(-1, 4))

cdt = PS2_Constrained_Delaunay_triangulation_plus_2()
cid1 = cdt.insert_constraint(polyline1)
cid2 = cdt.insert_constraint(polyline2)
# consider polyline3 as closed
cid3 = cdt.insert_constraint(polyline3, True)

# simplify only one polyline
CGAL_Polyline_simplification_2.simplify(
    cdt, cid1, Squared_distance_cost(),
    Stop_below_count_ratio_threshold(0.5))  # simplify only
# simplify all polylines
CGAL_Polyline_simplification_2.simplify(cdt, Squared_distance_cost(),
                                        Stop_below_count_ratio_threshold(0.5))

print("Vertices of first polyline")
for vh in cdt.vertices_in_constraint(cid1):
    print(vh.point())

print("Vertices of second polyline")
for vh in cdt.vertices_in_constraint(cid2):
    print(vh.point())

print(
    "Vertices of third polyline, note the last vertex is duplicated since it is closed"
)
for vh in cdt.vertices_in_constraint(cid3):
    print(vh.point())
