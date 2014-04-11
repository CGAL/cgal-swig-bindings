from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Mesh_3 import Mesh_3_Complex_3_in_triangulation_3
from CGAL.CGAL_Mesh_3 import Polyhedral_mesh_domain_3
from CGAL.CGAL_Mesh_3 import Mesh_3_parameters
from CGAL.CGAL_Mesh_3 import Default_mesh_criteria
from CGAL import CGAL_Mesh_3

import os
datadir = os.environ.get('DATADIR', '../data')
datafile = datadir+'/elephant.off'

#Create input polyhedron
polyhedron=Polyhedron_3(datafile)

#Create domain
domain = Polyhedral_mesh_domain_3(polyhedron)
params = Mesh_3_parameters()

#Mesh criteria (no cell_size set)
criteria = Default_mesh_criteria()
criteria.facet_angle(25).facet_size(0.15).facet_distance(0.008).cell_radius_edge_ratio(3)
#Mesh generation
c3t3=CGAL_Mesh_3.make_mesh_3(domain,criteria,params)

#Output
c3t3.output_to_medit("out_1.mesh")

#Set tetrahedron size (keep cell_radius_edge), ignore facets
new_criteria = Default_mesh_criteria()
new_criteria.cell_radius_edge_ratio(3).cell_size(0.03)

#Mesh refinement
CGAL_Mesh_3.refine_mesh_3(c3t3, domain, new_criteria,params)

#Output
c3t3.output_to_medit("out_2.mesh")
