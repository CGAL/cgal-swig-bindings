from __future__ import print_function

from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Spatial_searching import Orthogonal_incremental_neighbor_search_tree_2
from CGAL.CGAL_Spatial_searching import Orthogonal_incremental_neighbor_search_2
from CGAL.CGAL_Spatial_searching import Orthogonal_incremental_neighbor_search_tree_3
from CGAL.CGAL_Spatial_searching import Orthogonal_incremental_neighbor_search_3
from CGAL.CGAL_Spatial_searching import K_neighbor_search_tree_2
from CGAL.CGAL_Spatial_searching import K_neighbor_search_2
from CGAL.CGAL_Spatial_searching import Point_with_transformed_distance_2
from CGAL.CGAL_Spatial_searching import Point_with_transformed_distance_3
from CGAL.CGAL_Spatial_searching import Fuzzy_sphere_2
from CGAL.CGAL_Spatial_searching import Fuzzy_iso_box_2

def test_2d():
  print("Test 2D")
  
  lst=[]
  lst.append( Point_2(0,0) )
  lst.append( Point_2(0,4) )
  lst.append( Point_2(44,0) )
  lst.append( Point_2(44,5) )
  lst.append( Point_2(444,51) )
  lst.append( Point_2(14,1) )
  
  tree = Orthogonal_incremental_neighbor_search_tree_2(lst)
  
  for p in tree.iterator():
    print(p)
  search = Orthogonal_incremental_neighbor_search_2(tree,Point_2(0,0))
  
  for p in search.iterator():
    print(p[0],p[1])
  
  lst_search = []
  fs = Fuzzy_sphere_2(Point_2(0,0),8)
  fb = Fuzzy_iso_box_2(Point_2(-4,-4), Point_2(4,4.1))
  tree.search(lst_search,fs)
  print(len(lst_search))
  tree.search(lst_search,fb)
  print(len(lst_search))
  
  tree2= K_neighbor_search_tree_2()
  tree2.insert(lst)
  search2 = K_neighbor_search_2(tree2, Point_2(0,0), 3)
  for p in search2.iterator():
    print(p[0],p[1])

def test_3d():
  print("Test 3D")
  lst= []
  lst.append( Point_3(0,0,1) )
  lst.append( Point_3(0,4,2) )
  lst.append( Point_3(44,0,3) )
  lst.append( Point_3(44,5,4) )
  lst.append( Point_3(444,51,5) )
  lst.append( Point_3(14,1,7) )
  
  tree= Orthogonal_incremental_neighbor_search_tree_3(lst)
  
  search = Orthogonal_incremental_neighbor_search_3(Orthogonal_incremental_neighbor_search_tree_3(lst), Point_3(0,0,0))
  
  for p in search.iterator():
    print(p[0], p[1])

test_2d()
test_3d()
