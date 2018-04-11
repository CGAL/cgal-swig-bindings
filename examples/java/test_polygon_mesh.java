import CGAL.Polygon_mesh.Polygon_mesh_processing;
import CGAL.Polygon_mesh.Helper;
import CGAL.Polygon_mesh.PolygonMeshBase;
import CGAL.Polygon_mesh.PointSetBase;
import CGAL.Polygon_mesh.PolygonMeshBase.PropertyElementType;
import CGAL.Polygon_mesh.PolygonMeshBase.PropertyValueType;
import CGAL.Polygon_mesh.PolygonMeshPolyline;
import CGAL.Polygon_mesh.PolygonMeshRange.FaceDescriptorSubRange;
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorSubRange;
import CGAL.Polygon_mesh.PolygonMeshRange.FaceDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshRange.VertexDescriptorOutputRange;
import CGAL.Polygon_mesh.PolygonMeshIntProperty;
import CGAL.Polygon_mesh.PolygonMeshDoubleProperty;
import CGAL.Polygon_mesh.PolygonMeshUtils;
import CGAL.Polygon_mesh.PolygonMeshMultiPolyline;
import CGAL.Polygon_mesh.PolygonMeshSkeleton;
import CGAL.Polygon_mesh.PolygonMeshRidges;
import CGAL.Polygon_mesh.PolygonMeshUmbilics;
import CGAL.Polygon_mesh.Advancing_front_surface_reconstruction;
import CGAL.Polygon_mesh.Triangulated_surface_mesh_simplification;
import CGAL.Polygon_mesh.Triangulated_surface_mesh_segmentation;
import CGAL.Polygon_mesh.Jet_fitting_3;
import CGAL.Polygon_mesh.Surface_mesh_deformation;
import CGAL.Polygon_mesh.Surface_mesh_shortest_path;
import CGAL.Polygon_mesh.Surface_mesh_skeletonization;
import CGAL.Polygon_mesh.Ridges_3;
import CGAL.Polygon_mesh.Convex_hull_3;
import CGAL.Polygon_mesh.Point_set_processing_3;
import CGAL.Polygon_mesh.Surface_reconstruction_3;
import CGAL.Polygon_mesh.Subdivision_method_3;

import java.util.Vector;
import java.nio.IntBuffer;
import java.nio.DoubleBuffer;
import java.util.PrimitiveIterator;
import java.io.Writer;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.FileOutputStream;
import java.io.IOException;

public class test_polygon_mesh{

  public static void test_coref()
  {
    System.out.println("=== Test corefinement ===");
    // test corefine
    PolygonMeshBase pm1 = new PolygonMeshBase(10);
    PolygonMeshBase pm2 = new PolygonMeshBase(10);
    Helper.read_off(pm1,"../data/elephant.off");
    Helper.read_off(pm2,"../data/sphere.off");
    System.out.println("  #Vertices before corefine: "+pm1.numberOfVertices() + " - "+pm2.numberOfVertices());
    Polygon_mesh_processing.corefine(pm1, pm2);
    System.out.println("  #Vertices after corefine: "+pm1.numberOfVertices() + " - "+pm2.numberOfVertices());

    //test corefine_and_compute_union_inplace
    pm1 = new PolygonMeshBase(10);
    pm2 = new PolygonMeshBase(10);
    Helper.read_off(pm1,"../data/elephant.off");
    Helper.read_off(pm2,"../data/sphere.off");
    System.out.println("  #Vertices before corefine_and_compute_union (inplace): "+pm1.numberOfVertices() + " - "+pm2.numberOfVertices());
    Polygon_mesh_processing.corefine_and_compute_union(pm1, pm2, pm1);
    System.out.println("  #Vertices after corefine_and_compute_union (inplace): "+pm1.numberOfVertices() + " - "+pm2.numberOfVertices());
    Helper.write_off(pm1,"union_inplace.off");

    //test corefine_and_compute_union
    pm1 = new PolygonMeshBase(10);
    pm2 = new PolygonMeshBase(10);
    Helper.read_off(pm1,"../data/elephant.off");
    Helper.read_off(pm2,"../data/sphere.off");
    System.out.println("  #Vertices before corefine_and_compute_union: "+pm1.numberOfVertices() + " - "+pm2.numberOfVertices());
    PolygonMeshBase pm_out = new PolygonMeshBase(3000);
    Polygon_mesh_processing.corefine_and_compute_union(pm1, pm2, pm_out);
    System.out.println("  #Vertices after corefine_and_compute_union: "+pm1.numberOfVertices() + " - "+pm2.numberOfVertices());
    Helper.write_off(pm_out,"union.off");
  }

  public static void main(String arg[]){

    PolygonMeshBase pm = new PolygonMeshBase(10);

    Helper.read_off(pm,"../data/elephant.off");

    //testing helper functions
    if (Helper.is_closed(pm))
      System.out.println("The input is closed");
    if (Helper.is_triangle_mesh(pm))
      System.out.println("The input is a triangle mesh");

    int nb_border_hedges = 0;
    PrimitiveIterator.OfInt halfedges = pm.halfedges();
    while(halfedges.hasNext())
      if(Helper.is_border(halfedges.nextInt(),pm))
        ++nb_border_hedges;
    System.out.println("nb_border_hedges="+nb_border_hedges);

    System.out.println("=== Testing connected_components ===");
    PolygonMeshIntProperty ifp = (PolygonMeshIntProperty) pm.createFaceConnectedComponentProperty();
    System.out.println("  nb cc = "+Polygon_mesh_processing.connected_components(pm, ifp));

    System.out.println("=== Testing normal computations ===");
    PolygonMeshDoubleProperty nfp = (PolygonMeshDoubleProperty) pm.createFaceNormalProperty();
    Polygon_mesh_processing.compute_face_normals(pm, nfp);

    PolygonMeshDoubleProperty nvp = (PolygonMeshDoubleProperty) pm.createVertexNormalProperty();
    Polygon_mesh_processing.compute_vertex_normals(pm, nvp);

    Polygon_mesh_processing.compute_normals(pm, nvp, nfp);

    System.out.println("  #v "+pm.numberOfVertices()+" #f "+pm.numberOfFaces());
    FaceDescriptorOutputRange face_output=new FaceDescriptorOutputRange();
    VertexDescriptorOutputRange vertex_output=new VertexDescriptorOutputRange();
    long tb = System.currentTimeMillis();
    Polygon_mesh_processing.refine(pm,pm.faces(),face_output,vertex_output,2);
    System.out.println("  #v "+pm.numberOfVertices()+" #f "+pm.numberOfFaces());
    System.out.println("  face_output.getSize() "+face_output.getSize()+
                       " vertex_output.getSize() "+vertex_output.getSize());

    FaceDescriptorSubRange face_range = new FaceDescriptorSubRange();
    for (int i=0; i<2000; ++i)
      face_range.add(i);
    face_output=new FaceDescriptorOutputRange();
    vertex_output=new VertexDescriptorOutputRange();
    Polygon_mesh_processing.refine(pm,face_range,face_output,vertex_output,2);
    System.out.println("  #v "+pm.numberOfVertices()+" #f "+pm.numberOfFaces());
    System.out.println("  face_output.getSize() "+face_output.getSize()+
                       " vertex_output.getSize() "+vertex_output.getSize());
    System.out.println("  Time " + (System.currentTimeMillis()-tb));

    System.out.println("=== Testing slicer ===");
    PolygonMeshMultiPolyline polylines = new PolygonMeshMultiPolyline();
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    double[] planes = new double[]{1,0,0,0,0,1,0,0,0,0,1,0};
    Polygon_mesh_processing.polygon_mesh_slicer(pm, planes, polylines);
    System.out.println("  Nb of polylines " + polylines.getNumberOfPolylines());

    // Advancing front surface reconstruction
    System.out.println("=== Test call to Advancing front reconstruction ===");
    PolygonMeshBase P = new PolygonMeshBase(10);
    double[] pts = new double[]{0, 0, 0, 0, 1 , 0, 1 , 0, 0};
    Advancing_front_surface_reconstruction.
      advancing_front_surface_reconstruction(pts, P);
    System.out.println("  nb faces in the reconstruction " + P.numberOfFaces());

    // Testing corefinement
    test_coref();

    // Testing edge_collapse
    System.out.println("=== Test call to edge_collapse ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    Triangulated_surface_mesh_simplification.edge_collapse(pm,Triangulated_surface_mesh_simplification.Stop.COUNT_STOP, 1000);
    System.out.println("  nb edges after simplification " + pm.numberOfEdges());
    Helper.write_off(pm,"simplified.off");

    //Testing side_of_triangle_mesh
    System.out.println("=== Test call to side_of_triangle_mesh ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/sphere.off");
    DoubleBuffer points = CGAL.Polygon_mesh.PolygonMeshUtils.allocateNewDoubleBuffer(6);
    points.put(new double[] {0,0,0,1,1,1}, 0, 6);
    IntBuffer out = CGAL.Polygon_mesh.PolygonMeshUtils.allocateNewIntBuffer(2);
    Polygon_mesh_processing.side_of_triangle_mesh(pm, points, out);
    System.out.println("  Sides "+out.get(0)+ " " + out.get(1));
    PointSetBase ps_st = new PointSetBase();
    ps_st.addPoint(0,0,0);
    ps_st.addPoint(1,1,1);
    PolygonMeshIntProperty side_of = (PolygonMeshIntProperty) ps_st.createProperty(PointSetBase.PropertyValueType.INT, 1);
    Polygon_mesh_processing.side_of_triangle_mesh(pm, ps_st, side_of);
    assert ps_st.getNumberOfPoints() == 2;
    assert side_of.get( ps_st.getIndex(0) ) == 1;
    assert side_of.get( ps_st.getIndex(1) ) == -1;

    //Testing segmentation
    System.out.println("=== Test segmentation ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    PolygonMeshDoubleProperty sdf_values = (PolygonMeshDoubleProperty) pm.createProperty(PropertyElementType.FACE, PropertyValueType.DOUBLE, 1);
    double[] range = Triangulated_surface_mesh_segmentation.sdf_values(pm, sdf_values);
    System.out.println("  sdf range "+range[0]+ " " + range[1]);
    PolygonMeshIntProperty segment_ids = (PolygonMeshIntProperty) pm.createProperty(PropertyElementType.FACE, PropertyValueType.INT, 1);
    int nb_segmens = Triangulated_surface_mesh_segmentation.segmentation_from_sdf_values(pm, sdf_values, segment_ids);
    System.out.println("  nb segments  " + nb_segmens);

    //Testing Jet_fitting_3
    System.out.println("=== Test Jet_fitting_3 ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    PolygonMeshDoubleProperty min_curv_directions = (PolygonMeshDoubleProperty) pm.createProperty(PropertyElementType.VERTEX, PropertyValueType.DOUBLE, 3);
    PolygonMeshDoubleProperty max_curv_directions = (PolygonMeshDoubleProperty) pm.createProperty(PropertyElementType.VERTEX, PropertyValueType.DOUBLE, 3);
    Jet_fitting_3.estimate_curvature_directions(pm, min_curv_directions, max_curv_directions);

    // Testing Triangulated Surface Mesh Deformation
    System.out.println("=== Test deformation ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");

    VertexDescriptorSubRange ctl_vertex_range = new VertexDescriptorSubRange();
    ctl_vertex_range.add(302);
    ctl_vertex_range.add(2173);
    double[] ctl_new_positions = new double[]{-0.3, -0.29, -0.25, 0.5, -0.4 , -0.25};

    Surface_mesh_deformation.deform(pm, pm.vertices(), ctl_vertex_range, ctl_new_positions);

    Helper.write_off(pm,"elephant_deformed.off");

    // Testing Triangulated Surface Mesh Shortest Path
    System.out.println("=== Test shortest paths ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    double[] sources = new double[]{0.2046704152, 0.4799502874, 0.1067118924, 0.1224919338, -0.4543273997, -0.07089286468};
    double[] targets = new double[]{-0.1011125557, -0.2432933115, 0.194370818, 0.0144555091, 0.05315424589, -0.1119029306};
    PolygonMeshMultiPolyline shortest_paths = new PolygonMeshMultiPolyline();
    Surface_mesh_shortest_path.shortest_paths(pm, sources, targets, shortest_paths);

    // Testing Triangulated Surface Mesh Skeletonization
    System.out.println("=== Test skeletonization ===");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    PolygonMeshIntProperty vertex_to_skeleton_vertex = (PolygonMeshIntProperty) pm.createProperty(PropertyElementType.VERTEX, PropertyValueType.INT, 1);
    PolygonMeshSkeleton skeleton = new PolygonMeshSkeleton();
    Surface_mesh_skeletonization.extract_mean_curvature_flow_skeleton(pm, skeleton, vertex_to_skeleton_vertex);
    System.out.println("Skeleton has "+skeleton.getNumberOfPoints()+" vertices");
    System.out.println("Skeleton has "+skeleton.getNumberOfEdges()+" edges");
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    PolygonMeshIntProperty vertex_to_skeleton_vertex2 = (PolygonMeshIntProperty) pm.createProperty(PropertyElementType.VERTEX, PropertyValueType.INT, 1);
    Surface_mesh_skeletonization.Mean_curvature_flow_skeletonization skeletonization =
      new Surface_mesh_skeletonization.Mean_curvature_flow_skeletonization(pm, vertex_to_skeleton_vertex2);
    skeleton = new PolygonMeshSkeleton();
    skeletonization.run(skeleton);
    System.out.println("Skeleton has "+skeleton.getNumberOfPoints()+" vertices");
    System.out.println("Skeleton has "+skeleton.getNumberOfEdges()+" edges");
    PolygonMeshBase meso_pm = new PolygonMeshBase(10);
    skeletonization.meso_skeleton(meso_pm);
    Helper.write_off(meso_pm,"last_meso_skeleton.off");

    // Testing Ridges_3
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    PolygonMeshRidges ridges = new PolygonMeshRidges();
    Ridges_3.compute_crest_ridges(pm, ridges);
    System.out.println("Number of ridges extracted: "+ridges.getNumberOfRidges());
    Writer writer = null;
    try {
      writer = new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream("ridges.polylines.cgal"), "utf-8"));
      for(int rId=0; rId<ridges.getNumberOfRidges(); ++rId)
      {
        writer.write(""+ridges.getNumberOfPoints(rId));
        for( int ptId=0; ptId<ridges.getNumberOfPoints(rId); ++ptId)
        {
          writer.write(" "+ridges.getRidgePointX(rId,ptId,pm)+
                       " "+ridges.getRidgePointY(rId,ptId,pm)+
                       " "+ridges.getRidgePointZ(rId,ptId,pm));
        }
        writer.write("\n");
      }
    } catch (IOException ex) {
      // report
    } finally {
       try {writer.close();} catch (Exception ex) {/*ignore*/}
    }
    PolygonMeshUmbilics umbilics = new PolygonMeshUmbilics();
    Ridges_3.compute_umbilics(pm, umbilics);
    System.out.println("Number of umbilics extracted: "+umbilics.getNumberOfUmbilics());
    Writer writer2 = null;
    try {
      writer = new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream("umbilics.xyz"), "utf-8"));
      writer2 = new BufferedWriter(new OutputStreamWriter(
            new FileOutputStream("umbilic_contours.polylines.cgal"), "utf-8"));
      writer.write(umbilics.getNumberOfUmbilics()+"\n");
      for(int uId=0; uId<umbilics.getNumberOfUmbilics(); ++uId)
      {
        writer.write(pm.vertexX(umbilics.getUmbilic(uId))+" "+
                     pm.vertexY(umbilics.getUmbilic(uId))+" "+
                     pm.vertexZ(umbilics.getUmbilic(uId))+"\n");
        int nbContourHedges = umbilics.getNumberOfCoutourHalfedges(uId);
        for (int j=0; j<nbContourHedges; ++j)
        {
          int h = umbilics.getHalfedgeContour(uId, j);
          writer2.write("2 "+
             pm.vertexX(pm.source(h))+" "+pm.vertexY(pm.source(h))+" "+pm.vertexZ(pm.source(h))+" "+
             pm.vertexX(pm.target(h))+" "+pm.vertexY(pm.target(h))+" "+pm.vertexZ(pm.target(h))+"\n");
        }
      }
    } catch (IOException ex) {
      // report
    } finally {
       try {writer.close(); writer2.close();} catch (Exception ex) {/*ignore*/}
    }

    //Testing Convex_hull_3
    double[] cube_pts = new double[]{0, 0, 0, 0, 1 , 0, 1, 1, 0, 1, 0, 0,
                                     0, 0, 1, 0, 1 , 1, 1, 1, 1, 1, 0, 1};
    PolygonMeshBase pm_ch = new PolygonMeshBase(10);
    Convex_hull_3.convex_hull_3(cube_pts, pm_ch);
    System.out.println("convex hull has " + pm_ch.numberOfVertices() + " vertices");
    System.out.println("is pm_ch strongly convex: "+Convex_hull_3.is_strongly_convex_3(pm_ch));
    double[] cube_planes = new double[]{-1, 0, 0, 0, 1, 0, 0, -1,
                                        0, -1, 0, 0, 0, 1, 0, -1,
                                        0, 0, -1, 0, 0, 0, 1, -1};
    pm_ch = new PolygonMeshBase(10);
    Convex_hull_3.halfspace_intersection_3(cube_planes, pm_ch);
    System.out.println("convex hull has " + pm_ch.numberOfVertices() + " vertices");

    // Testing PolygonMesh/PointSet
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    PointSetBase ps = new PointSetBase();

    Polygon_mesh_processing.sample_triangle_mesh(pm, ps);
    System.out.println("sampling pm with " + ps.getNumberOfPoints() + " points.");
    Helper.write_xyz(ps, "samples.xyz");

    PolygonMeshBase pm_ch_smpl = new PolygonMeshBase(10);
    Convex_hull_3.convex_hull_3(ps, pm_ch_smpl);
    Helper.write_off(pm_ch_smpl,"samples_ch.off");

    //Testing Point Set Processing
    PointSetBase ps_psp = new PointSetBase(10);
    Helper.read_xyz(ps_psp, "../data/kitten.xyz");
    System.out.println("Read a file of " + ps_psp.getNumberOfPoints() + " points.");
    PolygonMeshDoubleProperty normal_map = (PolygonMeshDoubleProperty) ps_psp.createNormalProperty();
    Point_set_processing_3.jet_estimate_normals(ps_psp, normal_map, 6);
    Point_set_processing_3.jet_smooth_point_set(ps_psp, 10);
    Helper.write_xyz(ps_psp, "kitten_smoothed.xyz");
    Point_set_processing_3.random_simplify_point_set(ps_psp, 20);
    System.out.println("Nb pts kept: " + ps_psp.getNumberOfPoints());
    Helper.write_xyz(ps_psp, "kitten_simplified.xyz");
    PointSetBase ps_psp2 = new PointSetBase(10);
    Point_set_processing_3.wlop_simplify_and_regularize_point_set(ps_psp, ps_psp2);
    System.out.println("Nb pts after wlop: " + ps_psp2.getNumberOfPoints());
    Helper.write_xyz(ps_psp2, "kitten_wlop.xyz");
    PolygonMeshIntProperty knn_scale = (PolygonMeshIntProperty) ps_psp2.createProperty(PointSetBase.PropertyValueType.INT, 1);
    Point_set_processing_3.estimate_local_k_neighbor_scales(ps_psp, ps_psp2, knn_scale);
    //commented as too slow
    //Point_set_processing_3.edge_aware_upsample_point_set(ps_psp, normal_map, 30, 1 , 6, 4200);
    //System.out.println("Nb pts after upsample " + ps_psp.getNumberOfPoints());

    //Testing reconstruction
    Helper.read_xyz(ps_psp, "../data/kitten.xyz");
    System.out.println("Read a file of " + ps_psp.getNumberOfPoints() + " points.");
    Point_set_processing_3.jet_estimate_normals(ps_psp, normal_map, 6);
    Point_set_processing_3.mst_orient_normals(ps_psp, normal_map, 6);

    double average_spacing = Point_set_processing_3.compute_average_spacing(ps_psp, 6);
    pm = new PolygonMeshBase(10);
    Surface_reconstruction_3.poisson_surface_reconstruction_delaunay(ps_psp, normal_map, pm, average_spacing);
    Helper.write_off(pm, "poisson_kitten.off");

    pm = new PolygonMeshBase(10);
    Surface_reconstruction_3.advancing_front_surface_reconstruction(ps_psp, pm);
    Helper.write_off(pm, "afsr_kitten.off");

    //Testing Surface Subdivision method
    pm = new PolygonMeshBase(10);
    Helper.read_off(pm,"../data/elephant.off");
    Subdivision_method_3.Loop_subdivision(pm, 2);
    Helper.write_off(pm, "elephant_loop2.off");
  }
}
