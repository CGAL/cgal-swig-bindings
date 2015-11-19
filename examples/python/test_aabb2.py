'''
Created on Nov 18, 2015

@author: Willie Maddox

Test passing a python sequence directly to aabb trees
and print out some timing info.
Verified with with python lists, tuples, and numpy arrays.

The following results were obtained with
ubuntu 14.04 running on Intel Xeon E5-2620 cpu.
Bindings compiled with CGAL 4.6 gcc 4.8.4
nx = 1000
ny = 1000

gen_vertices_cgal      10.36432
*******************************
gen_triangle_soup      19.83478
gen_triangle_tree       0.45456
Total:                 30.65385
*******************************
gen_triangle_soup_Nx9   0.16211
gen_triangle_tree_Nx9   1.94723
Total:                  2.10945
*******************************
gen_segment_soup       31.55930
gen_segment_tree        0.63369
Total:                 42.55750
*******************************
gen_segment_soup_Nx6    0.50796
gen_segment_tree_Nx6    2.22729
Total:                  2.73538
*******************************

'''

from __future__ import print_function
import sys, time

from CGAL.CGAL_Kernel import Point_3, Segment_3, Triangle_3
from CGAL.CGAL_AABB_tree import AABB_tree_Segment_3_soup, AABB_tree_Triangle_3_soup

import numpy as np

# Helper functions
def gen_vertices(nx, ny):
    '''
    Create a Regular grid of vertices formatted as an (nx*ny,3) numpy array.
    '''
    xvals = np.linspace(-nx/2, nx/2, nx)
    yvals = np.linspace(-ny/2, ny/2, ny)
    xy = np.array([[i,j] for i in xvals for j in yvals])
    # add some purturbations to z values.
    zvals = (np.random.random((nx*ny))-0.5)*0.5
    vertices = np.vstack((xy.T,zvals)).T
    return vertices
#end
def gen_faces(nx, ny):
    '''
    Generate a list of faces from an nx by ny regular grid.
    '''
    a = np.arange(nx*ny).reshape(ny,nx)[:-1,:-1].flatten()        
    b = a + 1
    c = a + nx
    d = c + 1
    nfaces = 2*(nx-1)*(ny-1)
    faces = np.zeros((nfaces, 3)).astype(int)
    faces[::2] = np.vstack([a,c,b]).T
    faces[1::2] = np.vstack([b,c,d]).T
    assert nfaces == len(faces)
    return faces
#end
def gen_edges(faces):
    '''
    Generate the edges corresponding to the faces.
    '''
    fs = np.sort(faces, axis=1)
    F_EP = [[(f[0], f[1]), (f[0], f[2]), (f[1], f[2])] for f in fs]
    edges0 = set([E for EP in F_EP for E in EP])
    EP_F = {EP:() for EP in edges0}
    for F, EP in enumerate(F_EP):
        EP_F[EP[0]] += (F,)
        EP_F[EP[1]] += (F,)
        EP_F[EP[2]] += (F,)
    edges = np.array(list(edges0))
    return edges
#end
# Testing functions
def gen_vertices_cgal(vertices):
    t0 = time.time()
    vertices_cgal = [Point_3(x, y, z) for x, y, z in vertices]
    print('{:<21} {:>9.5f}'.format('gen_vertices_cgal', time.time()-t0))
    return vertices_cgal
#end
def gen_triangle_soup(vertices_cgal, faces):
    t0 = time.time()
    soup = [Triangle_3(vertices_cgal[f[0]], vertices_cgal[f[1]], vertices_cgal[f[2]]) for f in faces]
    print('{:<21} {:>9.5f}'.format('gen_triangle_soup', time.time()-t0))
    return soup
#end
def gen_segment_soup(vertices_cgal, edges):
    t0 = time.time()
    soup = [Segment_3(vertices_cgal[e[0]], vertices_cgal[e[1]]) for e in edges]
    print('{:<21} {:>9.5f}'.format('gen_segment_soup', time.time()-t0))
    return soup
#end
def gen_triangle_tree(soup):
    t0 = time.time()
    tree = AABB_tree_Triangle_3_soup(soup)
    print('{:<21} {:>9.5f}'.format('gen_triangle_tree', time.time()-t0))
    return tree
#end
def gen_segment_tree(soup):
    t0 = time.time()
    tree = AABB_tree_Segment_3_soup(soup)
    print('{:<21} {:>9.5f}'.format('gen_segment_tree', time.time()-t0))
    return tree
#end
def gen_triangle_soup_Nx9(vertices, faces):
    t0 = time.time()
    soup = vertices[faces].reshape(len(faces),9)
    print('{:<21} {:>9.5f}'.format('gen_triangle_soup_Nx9', time.time()-t0))
    return soup
#end
def gen_segment_soup_Nx6(vertices, edges):
    t0 = time.time()
    soup = vertices[edges].reshape(len(edges),6)
    print('{:<21} {:>9.5f}'.format('gen_segment_soup_Nx6', time.time()-t0))
    return soup
#end
def gen_triangle_tree_Nx9(soup):
    t0 = time.time()
    tree = AABB_tree_Triangle_3_soup()
    tree.insert_from_array(soup)
    print('{:<21} {:>9.5f}'.format('gen_triangle_tree_Nx9', time.time()-t0))
    return tree
#end
def gen_segment_tree_Nx6(soup):
    t0 = time.time()
    tree = AABB_tree_Segment_3_soup()
    tree.insert_from_array(soup)
    print('{:<21} {:>9.5f}'.format('gen_segment_tree_Nx6', time.time()-t0))
    return tree
#end

# Set sizes.
nx = 100
ny = 100
sepstring = '*'*31
# Set up some testing primitives
p1 = Point_3(-1,-1,-1)
p2 = Point_3(1,1,1)
p3 = Point_3(1,1,-1)
tri0 = Triangle_3(p1, p2, p3)
seg0 = Segment_3(p1, p2)

# Generate an initial set of points, faces, and edges.
verts = gen_vertices(nx, ny)
faces = gen_faces(nx, ny)
edges = gen_edges(faces)

nverts = len(verts)
nfaces = len(faces)
nedges = len(edges)

# Convert points to list of CGAL Point_3 objects.
t0 = time.time()
verts_cgal = gen_vertices_cgal(verts)
tverts = time.time()-t0
assert nverts == len(verts_cgal)
print(sepstring)

# test AABB triangle trees
# Generate CGAL soups on python side and pass to CGAL.
t0 = time.time()
triangle_soup = gen_triangle_soup(verts_cgal, faces)
tfaces = time.time()-t0
assert nfaces == len(triangle_soup)
t0 = time.time()
triangle_tree = gen_triangle_tree(triangle_soup)
ttree = time.time()-t0
assert nfaces == triangle_tree.size()
print('{:<21} {:>9.5f}'.format('Total:', tverts+tfaces+ttree))
print(sepstring)
tsi = []
triangle_tree.all_intersections(seg0, tsi)
tsii = [ip.second for ip in tsi]

# Pass Nx9 list directly to CGAL.
t0 = time.time()
triangle_soup_Nx9 = gen_triangle_soup_Nx9(verts, faces)
tfaces = time.time()-t0
assert nfaces == len(triangle_soup_Nx9)
t0 = time.time()
triangle_tree_Nx9 = gen_triangle_tree_Nx9(triangle_soup_Nx9)
ttree = time.time()-t0
assert nfaces == triangle_tree_Nx9.size()
print('{:<21} {:>9.5f}'.format('Total:', tfaces+ttree))
print(sepstring)
tsi9 = []
triangle_tree_Nx9.all_intersections(seg0, tsi9)
tsi9i = [ip.second for ip in tsi9]

assert tsii == tsi9i

# test AABB segment trees
# Using standard python.
t0 = time.time()
segment_soup = gen_segment_soup(verts_cgal, edges)
tedges = time.time()-t0
assert nedges == len(segment_soup)
t0 = time.time()
segment_tree = gen_segment_tree(segment_soup)
ttree = time.time()-t0
assert nedges == segment_tree.size()
print('{:<21} {:>9.5f}'.format('Total:', tverts+tedges+ttree))
print(sepstring)
sti = []
segment_tree.all_intersections(tri0, sti)
stii = [ip.second for ip in sti]

# Pass Nx6 list directly to CGAL.
t0 = time.time()
segment_soup_Nx6 = gen_segment_soup_Nx6(verts, edges)
tedges = time.time()-t0
assert nedges == len(segment_soup_Nx6)
t0 = time.time()
segment_tree_Nx6 = gen_segment_tree_Nx6(segment_soup_Nx6)
ttree = time.time()-t0
assert nedges == segment_tree_Nx6.size()
print('{:<21} {:>9.5f}'.format('Total:', tedges+ttree))
print(sepstring)
sti6 = []
segment_tree_Nx6.all_intersections(tri0, sti6)
sti6i = [ip.second for ip in sti6]

assert stii == sti6i

print('done')
