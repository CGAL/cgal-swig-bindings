from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3_with_info
from CGAL.CGAL_Kernel import Point_3

T = Delaunay_triangulation_3_with_info()
T.insert(Point_3(0, 0, 0))
T.insert(Point_3(1, 0, 0))
T.insert(Point_3(0, 1, 0))
T.insert(Point_3(0, 0, 1))
T.insert(Point_3(2, 2, 2))
T.insert(Point_3(-1, 0, 1))

print(f"Number of vertices: {T.number_of_vertices()}")
assert T.number_of_vertices() == 6
print("Test passed!")
