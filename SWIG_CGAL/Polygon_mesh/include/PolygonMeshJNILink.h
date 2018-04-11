// Copyright (c) 2018 GeometryFactory (France).
// All rights reserved.
//
// This file if part of CGAL PolygonMesh java wrapper.
// It is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this file.  If not, see <https://www.gnu.org/licenses/>.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// $URL$
// $Id$
// SPDX-License-Identifier: AGPL-3.0+
//

#ifndef POLYGON_MESH_JNI_LINK_HEADER
#define POLYGON_MESH_JNI_LINK_HEADER
#include <jni.h>
#include <vector>
#include "PolygonMesh.h"
#include "PointSet.h"
#include "RangeIndex.h"
#include "graph_traits_PolygonMesh.h"
#include "properties_PolygonMesh.h"

class PolygonMeshPropertyJNI;

class PolygonMeshJNILink {
public:
   // pointers to methods used to retrieve the new arrays when they are created by Java
   jmethodID getNextHEMID;
   jmethodID getPrevHEMID;
   jmethodID getHEVertexMID;
   jmethodID getHEFaceMID;
   jmethodID getVertexHEMID;
   jmethodID getFaceHEMID;
   jmethodID getVertexXMID;
   jmethodID getVertexYMID;
   jmethodID getVertexZMID;

   // pointers to methods used to retrieve the small arrays (element size, capacity...)
   jmethodID getElementSizeMID;
   jmethodID getFirstFreeElementMID;
   jmethodID getElementCapacityMID;
   jmethodID getRemovedElementMID;
   jmethodID reserveMID;

   // pointers to methods used to tell Java that it needs to increase capacity
   jmethodID incVCapacityMID;
   jmethodID incECapacityMID;
   jmethodID incFCapacityMID;

    // pointers to methods used for indexing
   jmethodID getVertexIndexArrayMID;
   jmethodID getEdgeIndexArrayMID;
   jmethodID getFaceIndexArrayMID;

   // pointers to methods used by RangeIndexJNI and WritableRangeIndexJNI
   jmethodID getRangeIndexTypeMID;
   jmethodID getSubRangeSizeAndCapacityMID;
   jmethodID getSubRangeArrayMID;
   jmethodID incSubRangeCapacityMID;

   // pointers to methods used by Polygon Mesh properties
   jmethodID getDoublePropertyValuesArrayMID;
   jmethodID getIntPropertyValuesArrayMID;
   jmethodID getBoolPropertyValuesArrayMID;

   // pointers to methods used by PolygonMeshPolyline
   jmethodID getPolylineBufferMID;
   jmethodID getPolylineSizeAndCapacityMID;
   jmethodID incPolylineCapacityMID;

   // pointers to methods used by PolygonMeshMultiPolyline
   jmethodID getMPVertexBufferMID;
   jmethodID getMPEndpointsBufferMID;
   jmethodID getMPSizesAndCapacityMID;
   jmethodID incMPVertexCapacityMID;
   jmethodID incMPPolylineCapacityMID;

   // pointers to methods used by PolygonMeshSkeleton
   jmethodID getSKCoordsBufferMID;
   jmethodID getSKEdgesBufferMID;
   jmethodID setSKCoordsCapacityMID;
   jmethodID setSKEdgesCapacityMID;
   jmethodID getSKsizesAndCapacitiesMID;

   // pointers to methods used by PolygonMeshRidges
   jmethodID getRStrengthBufferMID;
   jmethodID getRSharpnessBufferMID;
   jmethodID getRBCBufferMID;
   jmethodID getRTypeBufferMID;
   jmethodID getRNbRangeBufferMID;
   jmethodID getRHalfedgeBufferMID;
   jmethodID ridgeReserveMID;

   // pointers to methods used by PolygonMeshUmbilicsJNI
   jmethodID getUTypeBufferMID;
   jmethodID getUNbRangeBufferMID;
   jmethodID getUCHalfedgeBufferMID;
   jmethodID getUmbilicBufferMID;
   jmethodID umbilicsReserveMID;

   // pointers to methods used by PointSet
   jmethodID getPSPointXBufferMID;
   jmethodID getPSPointYBufferMID;
   jmethodID getPSPointZBufferMID;
   jmethodID getPSPointIndexBufferMID;
   jmethodID getPSSizeAndCapacityBufferMID;
   jmethodID increasePSCapacityMID;

   // constructor and destructor
   PolygonMeshJNILink();
   PolygonMeshJNILink(JNIEnv*);
};


// object containing all the method IDs used to access PolygonMesh data
static PolygonMeshJNILink polygonMeshJNILink;

JavaVM* & get_cached_jvm();

JNIEnv * JNU_GetEnv();

// Class linking the C++ PolygonMesh class with the Java class
class PolygonMeshJNI : public PolygonMesh {
   // Java environment
   JNIEnv *jni;
   // pointer to the Java alter-ego of this class
   jobject self;

   // flag for indexed polygon mesh
   bool indexed;

   // lists of properties
   std::vector<PolygonMeshPropertyJNI*> vertexProperties;
   std::vector<PolygonMeshPropertyJNI*> edgeProperties;
   std::vector<PolygonMeshPropertyJNI*> faceProperties;
   std::vector<PolygonMeshPropertyJNI*> halfedgeProperties;

   void retrieveVertexArrays();

   void retrieveEdgeArrays();

   void retrieveFaceArrays();

public:
   void registerVertexProperty(PolygonMeshPropertyJNI*);

   void registerEdgeProperty(PolygonMeshPropertyJNI*);

   void registerHalfedgeProperty(PolygonMeshPropertyJNI*);

   void registerFaceProperty(PolygonMeshPropertyJNI*);

   void reserve(int nv, int ne, int nf);

   // delegated methods

protected:
   void increaseVertexCapacity();

   void increaseEdgeCapacity();

   void increaseFaceCapacity();

public:
  PolygonMeshJNI(JNIEnv*, jobject );
  bool equals(const PolygonMeshJNI& other) const
  {
    return jni->IsSameObject(self, other.self);
  }
};

// Class linking the C++ PointSet class with the Java class
class PointSetJNI : public PointSet {
   // Java environment
   JNIEnv *jni;
   // pointer to the Java alter-ego of this class
   jobject self;

  std::vector<PolygonMeshPropertyJNI*> properties;

  void ensure_capacity(int c);
  void retrieve_arrays();
  void reserve(int n)
  {
    ensure_capacity(n);
  }
public:
  PointSetJNI(JNIEnv *env, jobject obj)
    : jni(env)
    , self(obj)
  {
    retrieve_arrays();
  }
  void registerProperty(PolygonMeshPropertyJNI*);
};

class RangeIndexJNI : public Range_index {
  // Java environment
  JNIEnv *jni;
  // pointer to the Java alter-ego of this class
  jobject self;

  void fill();

public:
  RangeIndexJNI() {};
  RangeIndexJNI(JNIEnv* env, jobject obj)
    : jni(env), self(obj)
  {
    fill();
  }
};

class WritableRangeIndexJNI : public Writable_range_index {
    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;

    void fill();

  public:
    typedef int const_reference;
    typedef int value_type;

    WritableRangeIndexJNI() {};
    WritableRangeIndexJNI(JNIEnv* env, jobject obj)
      : jni(env), self(obj)
    {
      fill();
    }

    void push_back(int i);
};


class PolygonMeshPropertyJNI {

  protected:

    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;


  public:

    PolygonMeshPropertyJNI() {};

    PolygonMeshPropertyJNI(JNIEnv* env, jobject obj)
      : jni(env), self(obj){}

    virtual void retrieveArray() = 0;
};

// type-specific properties
struct PolygonMeshBoolPropertyJNI
  : public PolygonMeshPropertyJNI
{
  PolygonMeshBoolPropertyJNI(JNIEnv* env, jobject obj)
    : PolygonMeshPropertyJNI(env, obj)
  {
    retrieveArray();
  }

  unsigned char* values;
  void retrieveArray();
};

struct PolygonMeshIntPropertyJNI
  : public PolygonMeshPropertyJNI
{
  PolygonMeshIntPropertyJNI(JNIEnv* env, jobject obj)
    : PolygonMeshPropertyJNI(env, obj)
  {
    retrieveArray();
  }

  int* values;
  void retrieveArray();
};

struct PolygonMeshDoublePropertyJNI
  : public PolygonMeshPropertyJNI
{
  PolygonMeshDoublePropertyJNI(JNIEnv* env, jobject obj)
    : PolygonMeshPropertyJNI(env, obj)
  {
    retrieveArray();
  }

  double* values;
  void retrieveArray();
};

class PolygonMeshPolylineJNI {

    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;

    // array containing coordinates
    double *coords;

    // array containing size and capacity
    int *sizeAndCapacity;

    void retrieveArray();

    void increaseCapacity();


  public:

    PolygonMeshPolylineJNI() {};

    PolygonMeshPolylineJNI(JNIEnv* env, jobject obj);

    void push_back(double x, double y, double z);

};

class PolygonMeshSkeletonJNI{

    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;

    // array containing coordinates
    double *coords;

    // array containing edges
    int *edges;

    // array containing sizes and capacities
    int* sizesAndCapacities;

    // array containing size and capacity
    void retrieveArrays();

  public:

    PolygonMeshSkeletonJNI() {};

    PolygonMeshSkeletonJNI(JNIEnv* env, jobject obj);

    void set_capacities(int nb_pts, int nb_edges);
    void push_back_point(double x, double y, double z);
    void push_back_edge(int i, int j);

};

class PolygonMeshMultiPolylineJNI {

    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;

    // array containing vertex coordinates
    double *coords;

    // array containing polyline endpoints
    int *polylineEndpoints;

    // array containing sizes and capacity
    int *sizesAndCapacities;

    void retrieveVertexArray();

    void retrievePolylineArray();

    void increaseVertexCapacity();

    void increasePolylineCapacity();


  public:

    PolygonMeshMultiPolylineJNI() {}

    PolygonMeshMultiPolylineJNI(JNIEnv* env, jobject obj);

    void push_back(double x, double y, double z);

    void beginPolyline();

    void endPolyline();

  #ifndef SWIG
    template <class Point_3>
    void convert_to_CGAL(std::vector< std::vector<Point_3> >& polylines)
    {
      int nb_polylines = sizesAndCapacities[1];
      polylines.resize( nb_polylines );
      for (int i=0; i<nb_polylines; ++i)
      {
        int begin = polylineEndpoints[2*i];
        int end = polylineEndpoints[2*i+1];
        polylines[i].reserve(end-begin);
        for(; begin!=end; ++begin)
          polylines[i].push_back(Point_3(coords[3*begin],
                                         coords[3*begin+1],
                                         coords[3*begin+2]));
      }
    }
  #endif

};

struct PolygonMeshRidgesJNI {

    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;

    // array containing sizes and capacity
    int *types;
    double *strengths;
    double *sharpnesses;
    int *halfedges;
    double *barycentric_coordinates;
    int *nb_ridges_and_ranges;

    void retrieveArrays();

  public:

    PolygonMeshRidgesJNI() {}

    PolygonMeshRidgesJNI(JNIEnv* env, jobject obj);

    void reserve(int nb_ridges, int total_nb_points);
};

struct PolygonMeshUmbilicsJNI{

    // Java environment
    JNIEnv *jni;

    // pointer to the Java alter-ego of this class
    jobject self;

    // array containing sizes and capacity
    int *types;
    int *umbilics;
    int *contour_halfedges;
    int *nb_umbilics_and_ranges;

    void retrieveArrays();

  public:

    PolygonMeshUmbilicsJNI() {}

    PolygonMeshUmbilicsJNI(JNIEnv* env, jobject obj);

    void reserve(int nb_umbilics , int total_nb_contour_halfedges);
};

#endif //POLYGON_MESH_JNI_LINK_HEADER
