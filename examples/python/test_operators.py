from __future__ import print_function
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Kernel import Vector_2
from CGAL.CGAL_Kernel import ORIGIN
from CGAL.CGAL_Kernel import NULL_VECTOR


def assertion(b,k):
    assert(b)
    print("Test ",k," OK")

def test_2d():
  print("2D Tests")

  p1 = Point_2(0,0)
  p2 = Point_2(1,2)
  v1 = Vector_2(1,1)
  v2 = Vector_2(1,2)

  #operations on points
  assertion( p1+v2 == p2, 1)
  assertion( p1-v2 < p2, 2)
  assertion( p2-p1 == v2, 3)
  assertion( p2 - ORIGIN == v2, 3.1);
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

  #operations on ORIGIN/NULL_VECTOR
  assertion( ORIGIN - p2 == -v2, 14 )
  assertion( ORIGIN + v2 ==  p2, 15 )
  assertion( p1 == ORIGIN, 15.1);
  assertion( p1 - p1 == NULL_VECTOR, 15.2);
  
  #test inplace operations
  pt_tmp=p1.deepcopy();
  pt_tmp+=v2;
  assertion( pt_tmp == p2 , 16)
  
  vect_tmp=Vector_2( 2,3)
  vect_tmp-=v1;
  assertion( vect_tmp == v2, 17)

def test_3d():
  print("3D Tests")

  p1 = Point_3(0,0,0)
  p2 = Point_3(1,2,0)
  v1 = Vector_3(1,1,0)
  v2 = Vector_3(1,2,0)

  #operations on points
  assertion( p1+v2 ==  p2 , 1)
  assertion( p1-v2 < p2, 2)
  assertion( p2-p1 == v2, 3)
  assertion( p2 - ORIGIN == v2, 3.1);
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

  #operations on ORIGIN/NULL_VECTOR
  assertion( ORIGIN - p2 == -v2, 14 )
  assertion( ORIGIN + v2 ==  p2, 15 )
  assertion( p1 == ORIGIN, 15.1);
  assertion( p1 - p1 == NULL_VECTOR, 15.2);

  #test inplace operations
  pt_tmp=p1.deepcopy();
  pt_tmp+=v2;
  assertion( pt_tmp == p2 , 16)
  
  vect_tmp=Vector_3( 2,3,0)
  vect_tmp-=v1;
  assertion( vect_tmp == v2, 17)
  
test_2d()
test_3d()
