from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Point_set_3 import Point_set_3

import os

datadir = os.environ.get('DATADIR', '../data')
datafile = datadir + '/oni.xyz'

points = Point_set_3()

# Insertions
idx = points.insert()
print("Point", idx, "inserted =", points.point(idx))
idx = points.insert(Point_3(0, 1, 2))
print("Point", idx, "inserted =", points.point(idx))
points.insert_range([2., 4., 5., 2, 3, 4])

# Iterate and display points
print("Point set:")
for p in points.points():
    print(" *", p)

# With normal
points.add_normal_map()
idx = points.insert(Point_3(6, 7, 8), Vector_3(1, 1, 1))
print("Point", idx, "inserted = (", points.point(idx), "), (",
      points.normal(idx), ")")

# Access/modification through normal map
normal_map = points.normal_map()
if normal_map.is_valid():
    print("Normal 3 =", normal_map.get(3))
    normal_map.set(2, Vector_3(1, 2, 3))
    print("Normal 2 =", normal_map.get(2))

# Iterate and display normals
print("Normal set:")
for n in points.normals():
    print(" *", n)

# Removal
print("Removing point at index 2...")
points.remove(2)
print("Point set has", points.size(), "point(s) and", points.garbage_size(),
      "garbage point(s)")

# Iterate and display points+normals through indices
print("Point set:")
for idx in points.indices():
    print(" (", idx, ") Point = (", points.point(idx), "), Normal = (",
          points.normal(idx), ")")

# Removing points only puts them in garbage, we can display it too
print("Garbage:")
for idx in points.garbage():
    print(" (", idx, ") Point = (", points.point(idx), "), Normal = (",
          points.normal(idx), ")")

# Collect the garbage and remove them for good if we don't need them anymore
print("Collecting garbage...")
points.collect_garbage()
print("Point set has", points.size(), "point(s) and", points.garbage_size(),
      "garbage point(s)")

# Dynamic property addition
print("Adding intensity map...")
intensity = points.add_float_map("intensity")
if intensity.is_valid():

    # Display properties
    print("Point set has the following properties:", points.properties())

    print("Setting intensity(1)=1.25 and intensity(8)=0.5")
    intensity.set(1, 1.25)
    intensity.set(3, 0.5)

    # Displaying intensity through indices
    for idx in points.indices():
        print(" * Intensity(", idx, ") =", intensity.get(idx))

    # Displaying intensity as a range
    print("Intensity range:")
    for i in points.range(intensity):
        print(" *", i)

    # Removing the map
    points.remove_float_map(intensity)

# Reading a file
print("Clearing and reading", datafile)
points.clear()
points.read(datafile)
print(datafile, "has", points.size(), "point(s) and", points.garbage_size(),
      "garbage point(s)")
print(datafile, "has the following properties:", (points.properties()))

# Writing the point set to different formats
print("Writing output to xyz...")
if not points.write("test.xyz"):
    print("Cannot write test.xyz")  # this sould NOT be displayed
print("Writing output to off...")
if not points.write("test.off"):
    print("Cannot write test.off")  # this sould NOT be displayed
print("Writing output to ply...")
if not points.write("test.ply"):
    print("Cannot write test.ply")  # this sould NOT be displayed
print("Trying to write output to doc...")
if not points.write("test.doc"):
    print("Cannot write test.doc")  # this should be displayed
