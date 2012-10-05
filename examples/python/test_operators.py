from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Kernel import Vector_2


def assertion(b,k):
    assert(b)
    print "Test ",k," OK"
  
def test_2d():
  print "2D Tests"

  p1 = Point_2(0,0)
  p2 = Point_2(1,2)
  v1 = Vector_2(1,1)
  v2 = Vector_2(1,2)

  #operations on points
  assertion( p1+v2 == p2, 1)
  assertion( p1-v2 < p2, 2)
  assertion( p2-p1 == v2, 3)
  assertion( p2 > p1, 4)
  assertion( p2>=p2, 5)
  assertion( p2<=p2, 6)
  assertion( p2 != p1, 7)
  
  #operations on vector
  assertion( v1+v2 == Vector_2(2,3),8 )
  assertion( v1-v2 == Vector_2(0,-1),9 )
  assertion( v2*v1 == 3,10 )
  assertion( v2*2 == Vector_2(2,4),11 )
  assertion( 2*v2 == Vector_2(2,4),"11 bis" )
  assertion( v1/2 == Vector_2(0.5,0.5),12 )
  assertion( -v2 ==  Vector_2(-1,-2) ,13 )
  assertion( v2 !=  v1 ,14 )


def test_3d():
  print "3D Tests"

  p1 = Point_3(0,0,0)
  p2 = Point_3(1,2,0)
  v1 = Vector_3(1,1,0)
  v2 = Vector_3(1,2,0)

  #operations on points
  assertion( p1+v2 ==  p2 , 1)
  assertion( p1-v2 < p2, 2)
  assertion( p2-p1 == v2, 3)
  assertion( p2 > p1, 4)
  assertion( p2>=p2, 5)
  assertion( p2<=p2, 6)
  assertion( p2 != p1, 7)
  
  #operations on vector
  assertion( v1+v2 == Vector_3(2,3,0),8 )
  assertion( v1-v2 == Vector_3(0,-1,0),9 )
  assertion( v2*v1 == 3,10 )
  assertion( v2*2 == Vector_3(2,4,0),11 )
  assertion( 2*v2 == Vector_3(2,4,0),"11 bis" )
  assertion( v1/2 == Vector_3(0.5,0.5,0),12 )
  assertion( -v2 ==  Vector_3(-1,-2,0) ,13 )    
  assertion( v2 !=  v1 ,14 )
  
test_2d()
test_3d()
