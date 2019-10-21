
import sys
sys.path.append('/usr/lib/python3.7')

import CGAL
from CGAL import CGAL_Shape_detection_3

s = CGAL_Shape_detection_3.Shape_detection_3()

p1 = s.Point_3(0, 0, 0)
v1 = s.Vector_3(-1, -1, -1)
pwn1 = s.Point_with_normal(p1, v1)

p2 = s.Point_3(1, 0, 0)
v2 = s.Vector_3(1, -1, -1)
pwn2 = s.Point_with_normal(p2, v2)

p3 = s.Point_3(1, 1, 0)
v3 = s.Vector_3(1, 1, -1)
pwn3 = s.Point_with_normal(p3, v3)

p4 = s.Point_3(0, 1, 0)
v4 = s.Vector_3(-1, 1, -1)
pwn4 = s.Point_with_normal(p4, v4)

p5 = s.Point_3(0, 0, 1)
v5 = s.Vector_3(-1, -1, 1)
pwn5 = s.Point_with_normal(p5, v5)

p6 = s.Point_3(1, 0, 1)
v6 = s.Vector_3(1, -1, 1)
pwn6 = s.Point_with_normal(p6, v6)

p7 = s.Point_3(1, 1, 1)
v7 = s.Vector_3(1, 1, 1)
pwn7 = s.Point_with_normal(p7, v7)

p8 = s.Point_3(0, 1, 1)
v8 = s.Vector_3(-1, 1, 1)
pwn8 = s.Point_with_normal(p8, v8)


s.addPointWithNormal(pwn1)
s.addPointWithNormal(pwn2)
s.addPointWithNormal(pwn3)
s.addPointWithNormal(pwn4)
s.addPointWithNormal(pwn5)
s.addPointWithNormal(pwn6)
s.addPointWithNormal(pwn7)
s.addPointWithNormal(pwn8)


s.detect()

print "Check:\n"

#print s.countShapes()
