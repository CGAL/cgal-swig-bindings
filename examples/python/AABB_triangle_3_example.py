from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Triangle_3
from CGAL.CGAL_Kernel import Ray_3
from CGAL.CGAL_AABB_tree import AABB_tree_Triangle_3_soup

a = Point_3(1.0, 0.0, 0.0)
b = Point_3(0.0, 1.0, 0.0)
c = Point_3(0.0, 0.0, 1.0)
d = Point_3(0.0, 0.0, 0.0)

triangles = []
triangles.append(Triangle_3(a,b,c))
triangles.append(Triangle_3(a,b,d))
triangles.append(Triangle_3(a,d,c))

# constructs AABB tree
tree = AABB_tree_Triangle_3_soup(triangles)

# counts #intersections
ray_query =  Ray_3(a,b)
print(tree.number_of_intersected_primitives(ray_query), " intersections(s) with ray query")

# compute closest point and squared distance
point_query = Point_3(2.0, 2.0, 2.0)
closest_point = tree.closest_point(point_query)
sqd = tree.squared_distance(point_query)
print("squared distance: ", sqd)
