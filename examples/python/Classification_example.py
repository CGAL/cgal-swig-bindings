from __future__ import print_function
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Point_set_3 import Point_set_3
from CGAL.CGAL_Classification import *

import sys
import os
datadir = os.environ.get('DATADIR', '../data')
datafile = datadir+'/b9_training.ply'

print("Reading input...")
points = Point_set_3(datafile)
print(points.size(), "points read")

labels = Label_set()
ground = labels.add("ground")
vegetation = labels.add("vegetation")
building = labels.add("building")

print("Computing feature...")

features = Feature_set()
generator = Point_set_feature_generator(points, 5)

features.begin_parallel_additions()
generator.generate_point_based_features(features)
if points.has_normal_map():
    generator.generate_normal_based_features(features, points.normal_map())

if points.has_int_map("red") and points.has_int_map("green") and points.has_int_map("blue"):
    generator.generate_color_based_features(features,
                                            points.int_map("red"),
                                            points.int_map("green"),
                                            points.int_map("blue"))

    
features.end_parallel_additions()

print("10 first features are:")
for idx in range(min(10,features.size())):
    print(" Feature", idx, ":", features.get(idx).name())

classification = points.int_map("label")
if not classification.is_valid():
    print("No ground truth found. Exiting.")
    exit()

# Copy classification in training map for later evaluating
training = points.add_int_map("training")
for idx in points.indices():
    training.set(idx, classification.get(idx))

print("Training random forest classifier...")
classifier = ETHZ_Random_forest_classifier(labels, features)
classifier.train(points.range(training), num_trees = 50, max_depth = 30)

print("Saving classifier's trained configuration...")
classifier.save_configuration("trained_random_forest.gz")

# classification map will be overwritten
if len(sys.argv) > 1:
    if sys.argv[1] == "-g" or sys.argv[1] == "--graphcut":
        print("Classifying with graphcut...")
        classify_with_graphcut (points, labels, classifier,
                                generator.neighborhood().k_neighbor_query(6),
                                0.5, # strength of graphcut
                                12, ## nb subdivisions (speed up)
                                classification)
    elif sys.argv[1] == "s" or sys.argv[1] == "--smoothing":
        print("Classifying with local smoothing...")
        classify_with_local_smoothing (points, labels, classifier,
                                    generator.neighborhood().k_neighbor_query(6),
                                       classification)
    else:
        print ("Unknown option", sys.argv[1])
        exit(-1)
else:
    print("Classifying...")
    classify (points, labels, classifier, classification)


print("Writing output...")
points.write("classified.ply")



print("Evaluation:")
evaluation = Evaluation(labels, points.range(training), points.range(classification))

print(" * Accuracy =", evaluation.accuracy())
print(" * Mean F1 score =", evaluation.mean_f1_score())
print(" * Mean IoU =", evaluation.mean_intersection_over_union())

print("Per label evaluation:")

for label in [ ground, vegetation, building ]:
    print(" *", label.name(), ": precision =", evaluation.precision(label),
          "; recall =", evaluation.recall(label),
          "; iou =", evaluation.intersection_over_union(label))
