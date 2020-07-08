import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_3.Point_set_3;
import CGAL.Point_set_3.Point_set_3_Int_map;
import CGAL.Classification.Label;
import CGAL.Classification.Label_set;
import CGAL.Classification.Feature_set;
import CGAL.Classification.Point_set_feature_generator;
import CGAL.Classification.ETHZ_Random_forest_classifier;
import CGAL.Classification.CGAL_Classification;
import CGAL.Classification.Evaluation;

public class Classification_example{
  public static void main(String args[]){

    String datafile = "../data/b9_training.ply";
    Point_set_3 points = new Point_set_3(datafile);

    System.out.println(points.size() + " points read");

    Label_set labels = new Label_set();
    Label ground = labels.add("ground");
    Label vegetation = labels.add("vegetation");
    Label building = labels.add("building");

    System.out.println("Computing feature...");

    Feature_set features = new Feature_set();
    Point_set_feature_generator generator = new Point_set_feature_generator(points, 5);

    features.begin_parallel_additions();
    generator.generate_point_based_features(features);
    if (points.has_normal_map())
      generator.generate_normal_based_features(features, points.normal_map());
    features.end_parallel_additions();

    System.out.println("10 first features are:");
    for (int i = 0; i < Math.min(features.size(), 10); ++ i)
      System.out.println(" Feature " + i + " : " + features.get(i).name());

    Point_set_3_Int_map classification = points.int_map("label");
    if (!classification.is_valid())
    {
      System.out.println("No ground truth found. Exiting.");
      return;
    }

    // Copy classification in training map for later evaluating
    Point_set_3_Int_map training = points.add_int_map("training");
    for (int idx : points.indices())
      training.set(idx, classification.get(idx));

    System.out.println("Training random forest classifier...");
    ETHZ_Random_forest_classifier classifier = new ETHZ_Random_forest_classifier(labels, features);
    classifier.train(points.range(training),
                     true, // reset trees
                     50, // num_trees
                     30); // max_depth

    System.out.println("Saving classifier's trained configuration...");
    classifier.save_configuration("trained_random_forest.gz");

    // classification map will be overwritten
    if (args.length > 0)
    {
      if (args[0].equals("-g") || args[0].equals("--graphcut"))
      {
        System.out.println("Classifying with graphcut...");
        CGAL_Classification.classify_with_graphcut (points, labels, classifier,
                                                    generator.neighborhood().k_neighbor_query(6),
                                                    0.5, // strength of graphcut
                                                    12, // nb subdivisions (speed up)
                                                    classification);
      }
      else if (args[0].equals("-s") || args[0].equals("--smoothing"))
      {
        System.out.println("Classifying with local smoothing...");
        CGAL_Classification.classify_with_local_smoothing (points, labels, classifier,
                                                           generator.neighborhood().k_neighbor_query(6),
                                                           classification);
      }
      else
      {
        System.out.println ("Unknown option " + args[0]);
        return;
      }
    }
    else
    {
      System.out.println("Classifying...");
      CGAL_Classification.classify (points, labels, classifier, classification);
    }

    System.out.println("Writing output...");
    points.write("classified.ply");

    System.out.println("Evaluation:");
    Evaluation evaluation = new Evaluation(labels, points.range(training), points.range(classification));

    System.out.println(" * Accuracy = " + evaluation.accuracy());
    System.out.println(" * Mean F1 score = " + evaluation.mean_f1_score());
    System.out.println(" * Mean IoU = " + evaluation.mean_intersection_over_union());

    System.out.println("Per label evaluation:");

    Label[] all_labels = {ground, vegetation, building };
    for (Label label : all_labels)
      System.out.println(" * " + label.name() + " : precision = " + evaluation.precision(label)
                         + " ; recall = " + evaluation.recall(label)
                         + " ; iou = " + evaluation.intersection_over_union(label));
  }
}
