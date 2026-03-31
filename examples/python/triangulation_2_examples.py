from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Triangulation_2 import Delaunay_triangulation_2
from CGAL.CGAL_Triangulation_2 import Constrained_Delaunay_triangulation_2
from CGAL.CGAL_Triangulation_2 import Constraint
from CGAL.CGAL_Triangulation_2 import Ref_Locate_type_2
from CGAL.CGAL_Triangulation_2 import VERTEX, EDGE, FACE, OUTSIDE_CONVEX_HULL, OUTSIDE_AFFINE_HULL
from CGAL.CGAL_Kernel import Ref_int
import os

# --- Delaunay_triangulation_2 ---
print("Delaunay_triangulation_2")
dt = Delaunay_triangulation_2()

# Insertion
v1 = dt.insert(Point_2(0, 0))
v2 = dt.insert(Point_2(1, 0))
v3 = dt.insert(Point_2(0, 1))
v4 = dt.insert(Point_2(0.5, 0.5))

assert dt.number_of_vertices() == 4
assert dt.is_valid()

# Locate
lt = Ref_Locate_type_2()
ri = Ref_int()
query = Point_2(0.2, 0.25)
face = dt.locate(query, lt, ri)
assert not dt.is_infinite(face)
assert lt.object() == FACE
assert dt.is_valid()

# Test nearest_vertex
nv = dt.nearest_vertex(Point_2(0.1, 0.1))
assert nv == v1

# Removal
dt.remove(v4)
assert dt.number_of_vertices() == 3
assert dt.is_valid()

# Traversal
print("Finite vertices:")
for v in dt.finite_vertices():
    print(v.point())

# Range insertion
lst = []
lst.append(Point_2(10, 10))
lst.append(Point_2(11, 10))
lst.append(Point_2(10, 11))
dt.insert(lst)
assert dt.number_of_vertices() == 6
assert dt.is_valid()
print("Nb vertices after range insertion:", dt.number_of_vertices())


# --- Constrained_Delaunay_triangulation_2 ---
print("Constrained_Delaunay_triangulation_2")
cdt = Constrained_Delaunay_triangulation_2()

# Insert constraints
constraints = []
constraints.append(Constraint(Point_2(0, 0), Point_2(1, 0)))
constraints.append(Constraint(Point_2(1, 0), Point_2(1, 1)))
constraints.append(Constraint(Point_2(1, 1), Point_2(0, 1)))
constraints.append(Constraint(Point_2(0, 1), Point_2(0, 0)))

cdt.insert_constraint_range(constraints)
assert cdt.is_valid()
assert cdt.number_of_vertices() == 4

# Check constrained edges
count = 0
for e in cdt.finite_edges():
    if cdt.is_constrained(e):
        count += 1
assert count == 4
print("Nb constrained edges:", count)

# Vertex insertion
vh1 = cdt.insert(Point_2(0.5, 0.5))
assert cdt.number_of_vertices() == 5
assert cdt.is_valid()

# Incident vertices
print("Incident vertices of (0.5, 0.5):")
circ = cdt.incident_vertices(vh1)
if circ.hasNext():
    first = circ.next()
    v = first
    while True:
        if not cdt.is_infinite(v):
            print(v.point())
        v = circ.next()
        if v == first:
            break

# File I/O
print("File I/O")
filename = "triangulation_output.tri"
dt.write_to_file(filename)
dt2 = Delaunay_triangulation_2()
dt2.read_from_file(filename)
assert dt2.is_valid()
assert dt2.number_of_vertices() == dt.number_of_vertices()
if os.path.exists(filename):
    os.remove(filename)
print("File I/O OK")

print("All triangulation tests passed!")
