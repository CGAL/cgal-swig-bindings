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

#include "PolygonMeshJNILink.h"
#include <stdexcept>
#include <cassert>

JavaVM* & get_cached_jvm(){
  static JavaVM* cached_jvm = NULL;
  return cached_jvm;
}

JNIEnv * JNU_GetEnv() {
  JNIEnv *env;
  jint rc = get_cached_jvm()->GetEnv((void **)&env, JNI_VERSION_1_2);
  assert(get_cached_jvm()!=NULL);
  if (rc == JNI_EDETACHED)
    throw std::runtime_error("current thread not attached");
  if (rc == JNI_EVERSION)
    throw std::runtime_error("jni version not supported");
  return env;
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void * ) {
  get_cached_jvm() = jvm;
  polygonMeshJNILink = PolygonMeshJNILink(JNU_GetEnv());
  return JNI_VERSION_1_2;
}

PolygonMeshJNILink::PolygonMeshJNILink(){}

PolygonMeshJNILink::PolygonMeshJNILink(JNIEnv *jni){
      // retrieve Java class for data access
      jclass cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshBase");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshBase");
      // elementSize
      getElementSizeMID = jni->GetMethodID(cls, "getElementSize","()Ljava/nio/IntBuffer;");
      if(!getElementSizeMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getElementSize()");
      // elementCapacity
      getElementCapacityMID = jni->GetMethodID(cls, "getElementCapacity","()Ljava/nio/IntBuffer;");
      if(!getElementCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getElementCapacity()");
      // firstFreeElement
      getFirstFreeElementMID = jni->GetMethodID(cls, "getFirstFreeElement","()Ljava/nio/IntBuffer;");
      if(!getFirstFreeElementMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getFirstFreeElement()");
      // removedElement
      getRemovedElementMID = jni->GetMethodID(cls, "getRemovedElement","()Ljava/nio/IntBuffer;");
      if(!getRemovedElementMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getRemovedElement()");
      // reserve
      reserveMID = jni->GetMethodID(cls, "reserve","(III)V");
      if(!reserveMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.reserve()");
      // nextHE
      getNextHEMID = jni->GetMethodID(cls, "getNextHEArray","()Ljava/nio/IntBuffer;");
      if(!getNextHEMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getNextHEArray()");
      // prevHE
      getPrevHEMID = jni->GetMethodID(cls, "getPrevHEArray","()Ljava/nio/IntBuffer;");
      if(!getPrevHEMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getPrevHEArray()");
      // heVertex
      getHEVertexMID = jni->GetMethodID(cls, "getHEVertexArray","()Ljava/nio/IntBuffer;");
      if(!getHEVertexMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getHEVertexArray()");
      // heFace
      getHEFaceMID = jni->GetMethodID(cls, "getHEFaceArray","()Ljava/nio/IntBuffer;");
      if(!getHEFaceMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getHEFaceArray()");
      // vertexHE
      getVertexHEMID = jni->GetMethodID(cls, "getVertexHEArray","()Ljava/nio/IntBuffer;");
      if(!getVertexHEMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getVertexHEArray()");
      // faceHE
      getFaceHEMID = jni->GetMethodID(cls, "getFaceHEArray","()Ljava/nio/IntBuffer;");
      if(!getFaceHEMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getFaceHEArray()");
      // vertexX
      getVertexXMID = jni->GetMethodID(cls, "getVertexXArray","()Ljava/nio/DoubleBuffer;");
      if(!getVertexXMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getVertexXArray()");
      // vertexY
      getVertexYMID = jni->GetMethodID(cls, "getVertexYArray","()Ljava/nio/DoubleBuffer;");
      if(!getVertexYMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getVertexYArray()");
      // vertexZ
      getVertexZMID = jni->GetMethodID(cls, "getVertexZArray","()Ljava/nio/DoubleBuffer;");
      if(!getVertexZMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.getVertexZArray()");
      // retrieve methods for memory allocation
      incVCapacityMID = jni->GetMethodID(cls, "increaseVertexCapacity","()V");
      if(!incVCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.increaseVertexCapacity()");
      incECapacityMID = jni->GetMethodID(cls, "increaseEdgeCapacity","()V");
      if(!incECapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.increaseEdgeCapacity()");
      incFCapacityMID = jni->GetMethodID(cls, "increaseFaceCapacity","()V");
      if(!incFCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshBase.increaseFaceCapacity()");

      // pointers to methods used for indexing
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshAccess");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshAccess");
      getVertexIndexArrayMID = jni->GetMethodID(cls, "getVertexIndexArray","()Ljava/nio/IntBuffer;");
      if(!getVertexIndexArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshAccess.getVertexIndexArray()");
      getEdgeIndexArrayMID = jni->GetMethodID(cls, "getEdgeIndexArray","()Ljava/nio/IntBuffer;");
      if(!getEdgeIndexArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshAccess.getEdgeIndexArray()");
      getFaceIndexArrayMID = jni->GetMethodID(cls, "getFaceIndexArray","()Ljava/nio/IntBuffer;");
      if(!getFaceIndexArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshAccess.getFaceIndexArray()");

      // retrieve Java class for data access
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshRange$DescriptorRange");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshRange.DescriptorRange");
      // pointers to methods used by RangeIndexJNI
      getRangeIndexTypeMID = jni->GetMethodID(cls, "getType","()I");
      if(!getRangeIndexTypeMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRange.DescriptorRange.getType()");

      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshRange$SubRange");
      getSubRangeSizeAndCapacityMID = jni->GetMethodID(cls, "getSizeAndCapacity","()Ljava/nio/IntBuffer;");
      if(!getSubRangeSizeAndCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRange.SubRange.getSize()");
      getSubRangeArrayMID = jni->GetMethodID(cls, "getArray","()Ljava/nio/IntBuffer;");
      if(!getSubRangeArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRange.SubRange.getArray()");
      incSubRangeCapacityMID = jni->GetMethodID(cls, "increaseCapacity","()Ljava/nio/IntBuffer;");
      if(!incSubRangeCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRange.SubRange.increaseCapacity()");

      // retrieve methods to access property buffers
      cls = jni->FindClass("CGAL/Polygon_mesh/IPolygonMeshIntProperty");
      getIntPropertyValuesArrayMID = jni->GetMethodID(cls, "getIntBuffer", "()Ljava/nio/IntBuffer;");
      if(!getIntPropertyValuesArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.IPolygonMeshIntProperty.getIntBuffer()");

      cls = jni->FindClass("CGAL/Polygon_mesh/IPolygonMeshDoubleProperty");
      getDoublePropertyValuesArrayMID = jni->GetMethodID(cls, "getDoubleBuffer", "()Ljava/nio/DoubleBuffer;");
      if(!getDoublePropertyValuesArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.IPolygonMeshDoubleProperty.getDoubleBuffer()");

      cls = jni->FindClass("CGAL/Polygon_mesh/IPolygonMeshByteProperty");
      getBoolPropertyValuesArrayMID = jni->GetMethodID(cls, "getByteBuffer", "()Ljava/nio/ByteBuffer;");
      if(!getBoolPropertyValuesArrayMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.IPolygonMeshByteProperty.getByteBuffer()");

      // retrieve methods to access polylines
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshPolyline");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshPolyline");
      getPolylineBufferMID = jni->GetMethodID(cls, "getArray", "()Ljava/nio/DoubleBuffer;");
      if(!getPolylineBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshPolyline.getArray()");
      getPolylineSizeAndCapacityMID = jni->GetMethodID(cls, "getSizeAndCapacity", "()Ljava/nio/IntBuffer;");
      if(!getPolylineSizeAndCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshPolyline.getSizeAndCapacity()");
      incPolylineCapacityMID = jni->GetMethodID(cls, "increaseCapacity", "()Ljava/nio/DoubleBuffer;");
      if(!incPolylineCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshPolyline.increaseCapacity()");

      // retrieve methods to access multi polylines
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshMultiPolyline");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshMultiPolyline");
      getMPVertexBufferMID = jni->GetMethodID(cls, "getVertexArray", "()Ljava/nio/DoubleBuffer;");
      if(!getMPVertexBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshMultiPolyline.getVertexArray()");
      getMPEndpointsBufferMID = jni->GetMethodID(cls, "getPolylineArray", "()Ljava/nio/IntBuffer;");
      if(!getMPEndpointsBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshMultiPolyline.getPolylineArray()");
      getMPSizesAndCapacityMID = jni->GetMethodID(cls, "getSizesAndCapacities", "()Ljava/nio/IntBuffer;");
      if(!getMPSizesAndCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshMultiPolyline.getSizesAndCapacity()");
      incMPVertexCapacityMID = jni->GetMethodID(cls, "increaseVertexCapacity", "()Ljava/nio/DoubleBuffer;");
      if(!incPolylineCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshMultiPolyline.increaseVertexCapacity()");
      incMPPolylineCapacityMID = jni->GetMethodID(cls, "increasePolylineCapacity", "()Ljava/nio/IntBuffer;");
      if(!incMPPolylineCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshMultiPolyline.increasePolylineCapacity()");

      // retrieve methods to access skeleton
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshSkeleton");
      getSKCoordsBufferMID = jni->GetMethodID(cls, "getCoordsArray", "()Ljava/nio/DoubleBuffer;");
      if(!getSKCoordsBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshSkeleton.getCoordsArray()");
      getSKEdgesBufferMID = jni->GetMethodID(cls, "getEdgesArray", "()Ljava/nio/IntBuffer;");
      if(!getSKEdgesBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshSkeleton.getEdgesArray()");
      getSKsizesAndCapacitiesMID = jni->GetMethodID(cls, "getsizesAndCapacities", "()Ljava/nio/IntBuffer;");
      if(!getSKsizesAndCapacitiesMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshSkeleton.getsizesAndCapacities()");
      setSKCoordsCapacityMID = jni->GetMethodID(cls, "setCoordsCapacity", "(I)Ljava/nio/DoubleBuffer;");
      if(!setSKCoordsCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshSkeleton.setCoordsCapacity()");
      setSKEdgesCapacityMID = jni->GetMethodID(cls, "setEdgesCapacity", "(I)Ljava/nio/IntBuffer;");
      if(!setSKEdgesCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshSkeleton.setEdgesCapacity()");

      // retrieve methods to access ridges
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshRidges");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshRidges");
      getRStrengthBufferMID = jni->GetMethodID(cls, "getStrengthsArray", "()Ljava/nio/DoubleBuffer;");
      if(!getRStrengthBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.getStrengthsArray()");
      getRSharpnessBufferMID = jni->GetMethodID(cls, "getSharpnessArray", "()Ljava/nio/DoubleBuffer;");
      if(!getRSharpnessBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.getSharpnessArray()");
      getRBCBufferMID = jni->GetMethodID(cls, "getBarycentricCoordinateArray", "()Ljava/nio/DoubleBuffer;");
      if(!getRBCBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.getBarycentricCoordinateArray()");
      getRTypeBufferMID = jni->GetMethodID(cls, "getTypesArray", "()Ljava/nio/IntBuffer;");
      if(!getRTypeBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.getTypesArray()");
      getRNbRangeBufferMID = jni->GetMethodID(cls, "getnbRidgesAndRangeArray", "()Ljava/nio/IntBuffer;");
      if(!getRNbRangeBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.getnbRidgesAndRangeArray()");
      getRHalfedgeBufferMID = jni->GetMethodID(cls, "getHalfedgeArray", "()Ljava/nio/IntBuffer;");
      if(!getRHalfedgeBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.getHalfedgeArray()");
      ridgeReserveMID = jni->GetMethodID(cls, "reserve","(II)V");
      if(!ridgeReserveMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshRidges.reserve()");

      // retrieve methods to access umbilics
      cls = jni->FindClass("CGAL/Polygon_mesh/PolygonMeshUmbilics");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PolygonMeshUmbilics");
      getUTypeBufferMID = jni->GetMethodID(cls, "getTypesArray", "()Ljava/nio/IntBuffer;");
      if(!getUTypeBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshUmbilics.getTypesArray()");
      getUmbilicBufferMID = jni->GetMethodID(cls, "getUmbilicArray", "()Ljava/nio/IntBuffer;");
      if(!getUmbilicBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshUmbilics.getUmbilicArray()");
      umbilicsReserveMID = jni->GetMethodID(cls, "reserve","(II)V");
      if(!umbilicsReserveMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshUmbilics.reserve()");
      getUNbRangeBufferMID = jni->GetMethodID(cls, "getNbUmbilicsAndRangeArray", "()Ljava/nio/IntBuffer;");
      if(!getUNbRangeBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshUmbilics.getNbUmbilicsAndRangeArray()");
      getUCHalfedgeBufferMID = jni->GetMethodID(cls, "getContourHalfedgeArray", "()Ljava/nio/IntBuffer;");
      if(!getUCHalfedgeBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PolygonMeshUmbilics.getContourHalfedgeArray()");

      // retrieve methods to access PointSet
      cls = jni->FindClass("CGAL/Polygon_mesh/PointSetBase");
      if(!cls) throw std::runtime_error("could not find class CGAL.Polygon_mesh.PointSetBase");
      getPSSizeAndCapacityBufferMID = jni->GetMethodID(cls, "getSizeAndCapacity", "()Ljava/nio/IntBuffer;");
      if(!getPSSizeAndCapacityBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PointSetBase.getSizeAndCapacity()");
      getPSPointIndexBufferMID = jni->GetMethodID(cls, "getPointIndex", "()Ljava/nio/IntBuffer;");
      if(!getPSPointIndexBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PointSetBase.getPointIndex()");
      getPSPointXBufferMID = jni->GetMethodID(cls, "getPointXArray", "()Ljava/nio/DoubleBuffer;");
      if(!getPSPointXBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PointSetBase.getPointXArray()");
      getPSPointYBufferMID = jni->GetMethodID(cls, "getPointYArray", "()Ljava/nio/DoubleBuffer;");
      if(!getPSPointYBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PointSetBase.getPointYArray()");
      getPSPointZBufferMID = jni->GetMethodID(cls, "getPointZArray", "()Ljava/nio/DoubleBuffer;");
      if(!getPSPointZBufferMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PointSetBase.getPointZArray()");
      increasePSCapacityMID =  jni->GetMethodID(cls, "increaseCapacity","(I)V");
      if(!increasePSCapacityMID) throw std::runtime_error("could not find method CGAL.Polygon_mesh.PointSetBase.increaseCapacity()");

}

void PolygonMeshJNI::retrieveVertexArrays(){
   vertexHE = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getVertexHEMID));
   vX = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getVertexXMID));
   vY = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getVertexYMID));
   vZ = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getVertexZMID));
   vIndex = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getVertexIndexArrayMID));
}

void PolygonMeshJNI::retrieveEdgeArrays(){
   nextHE = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getNextHEMID));
   prevHE = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPrevHEMID));
   heVertex = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getHEVertexMID));
   heFace = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getHEFaceMID));
   eIndex = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getEdgeIndexArrayMID));
}

void PolygonMeshJNI::retrieveFaceArrays(){
   faceHE = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getFaceHEMID));
   fIndex = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getFaceIndexArrayMID));
}


void PolygonMeshJNI::increaseVertexCapacity(){
   jni->CallObjectMethod(self, polygonMeshJNILink.incVCapacityMID);
   retrieveVertexArrays();
   // update vertex property arrays
   for (std::vector<PolygonMeshPropertyJNI*>::iterator it = vertexProperties.begin(); it != vertexProperties.end(); ++it) {
     (*it)->retrieveArray();
   }
}

void PolygonMeshJNI::increaseEdgeCapacity(){
   jni->CallObjectMethod(self, polygonMeshJNILink.incECapacityMID);
   retrieveEdgeArrays();
   // update edge property arrays
   for (std::vector<PolygonMeshPropertyJNI*>::iterator it = edgeProperties.begin(); it != edgeProperties.end(); ++it) {
     (*it)->retrieveArray();
   }
   // update halfedge property arrays
   for (std::vector<PolygonMeshPropertyJNI*>::iterator it = halfedgeProperties.begin(); it != halfedgeProperties.end(); ++it) {
     (*it)->retrieveArray();
   }
}

void PolygonMeshJNI::increaseFaceCapacity(){
   jni->CallObjectMethod(self, polygonMeshJNILink.incFCapacityMID);
   retrieveFaceArrays();
   // update face property arrays
   for (std::vector<PolygonMeshPropertyJNI*>::iterator it = faceProperties.begin(); it != faceProperties.end(); ++it) {
     (*it)->retrieveArray();
   }
}


PolygonMeshJNI::PolygonMeshJNI(JNIEnv *env, jobject obj) : jni(env), self(obj) {

    // elementSize
    elementSize = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getElementSizeMID));
    // elementCapacity
    elementCapacity = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getElementCapacityMID));
    // firstFreeElement
    firstFreeElement = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getFirstFreeElementMID));
    // removedElement
    removedElement = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRemovedElementMID));
    // retrieve arrays
    retrieveVertexArrays();
    retrieveEdgeArrays();
    retrieveFaceArrays();
 }

void PolygonMeshJNI::registerVertexProperty(PolygonMeshPropertyJNI* prop) {
   vertexProperties.push_back(prop);
}

void PolygonMeshJNI::registerEdgeProperty(PolygonMeshPropertyJNI* prop) {
   edgeProperties.push_back(prop);
}

void PolygonMeshJNI::registerHalfedgeProperty(PolygonMeshPropertyJNI* prop) {
   halfedgeProperties.push_back(prop);
}

void PolygonMeshJNI::registerFaceProperty(PolygonMeshPropertyJNI* prop) {
   faceProperties.push_back(prop);
}

void PolygonMeshJNI::reserve(int nv, int ne, int nf) {
  jni->CallObjectMethod(self, polygonMeshJNILink.reserveMID,nv, ne, nf);
  retrieveVertexArrays();
  retrieveEdgeArrays();
  retrieveFaceArrays();
}

void RangeIndexJNI::fill()
{
  int type = jni->CallIntMethod(self, polygonMeshJNILink.getRangeIndexTypeMID);
  if (type == 0 )
  {
    indices=NULL;
    size=0;
  }
  else{
    indices = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSubRangeArrayMID));
    size = ((int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSubRangeSizeAndCapacityMID)))[0];
  }
}

void WritableRangeIndexJNI::fill()
{
  indices = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSubRangeArrayMID));
  size_and_capacity = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSubRangeSizeAndCapacityMID));
}

void WritableRangeIndexJNI::push_back(int i)
{
  if (size_and_capacity[0]==size_and_capacity[1])
    indices = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.incSubRangeCapacityMID));
  indices[size_and_capacity[0]]=i;
  ++size_and_capacity[0];
}

void PolygonMeshBoolPropertyJNI::retrieveArray() {
    values = (unsigned char*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getBoolPropertyValuesArrayMID));
}

void PolygonMeshIntPropertyJNI::retrieveArray() {
    values = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getIntPropertyValuesArrayMID));
}

void PolygonMeshDoublePropertyJNI::retrieveArray() {
    values = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getDoublePropertyValuesArrayMID));
}

PolygonMeshPolylineJNI::PolygonMeshPolylineJNI(JNIEnv* env, jobject obj) : jni(env), self(obj) {
    sizeAndCapacity =(int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPolylineSizeAndCapacityMID));
    coords =(double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPolylineBufferMID));
}

PolygonMeshSkeletonJNI::PolygonMeshSkeletonJNI(JNIEnv* env, jobject obj) : jni(env), self(obj) {
    sizesAndCapacities = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSKsizesAndCapacitiesMID));
    coords = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSKCoordsBufferMID));
    edges = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSKEdgesBufferMID));
}

void PolygonMeshPolylineJNI::retrieveArray() {
    coords =(double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPolylineBufferMID));
}

void PolygonMeshSkeletonJNI::retrieveArrays() {
    coords =(double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSKCoordsBufferMID));
    edges =(int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getSKEdgesBufferMID));
}

void PolygonMeshPolylineJNI::increaseCapacity() {
   jni->CallObjectMethod(self, polygonMeshJNILink.incPolylineCapacityMID);
   retrieveArray();
}

void PolygonMeshPolylineJNI::push_back(double x, double y, double z) {
    int size = sizeAndCapacity[0];
    int capacity = sizeAndCapacity[1];
    if (size >= capacity) {
        increaseCapacity();
    }
    coords[3 * size] = x;
    coords[3 * size + 1] = y;
    coords[3 * size + 2] = z;
    size++;
    sizeAndCapacity[0] = size;
}

PolygonMeshMultiPolylineJNI::PolygonMeshMultiPolylineJNI(JNIEnv* env, jobject obj) : jni(env), self(obj) {
    sizesAndCapacities = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getMPSizesAndCapacityMID));
    coords = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getMPVertexBufferMID));
    polylineEndpoints = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getMPEndpointsBufferMID));
}

void PolygonMeshMultiPolylineJNI::retrieveVertexArray() {
    coords = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getMPVertexBufferMID));
}

void PolygonMeshMultiPolylineJNI::retrievePolylineArray() {
    polylineEndpoints = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getMPEndpointsBufferMID));
}

void PolygonMeshMultiPolylineJNI::increaseVertexCapacity() {
   jni->CallObjectMethod(self, polygonMeshJNILink.incMPVertexCapacityMID);
   retrieveVertexArray();
}

void PolygonMeshMultiPolylineJNI::increasePolylineCapacity() {
   jni->CallObjectMethod(self, polygonMeshJNILink.incMPPolylineCapacityMID);
   retrievePolylineArray();
}

void PolygonMeshMultiPolylineJNI::push_back(double x, double y, double z) {
   int size = sizesAndCapacities[0];
   int capacity = sizesAndCapacities[2];
   if (size >= capacity) {
     increaseVertexCapacity();
   }
   coords[3 * size] = x;
   coords[3 * size + 1] = y;
   coords[3 * size + 2] = z;
   size++;
   sizesAndCapacities[0] = size;
}
void PolygonMeshMultiPolylineJNI::beginPolyline() {
   int size = sizesAndCapacities[1];
   int nVertices = sizesAndCapacities[0];
   int capacity = sizesAndCapacities[3];
   if (size >= capacity) {
     increasePolylineCapacity();
   }
   polylineEndpoints[2 * size] = nVertices;
}

void PolygonMeshMultiPolylineJNI::endPolyline() {
   int size = sizesAndCapacities[1];
   int nVertices = sizesAndCapacities[0];
   int capacity = sizesAndCapacities[3];
   if (size >= capacity) {
     increasePolylineCapacity();
   }
   polylineEndpoints[2 * size + 1] = nVertices;
   size++;
   sizesAndCapacities[1] = size;
}

void PolygonMeshSkeletonJNI::push_back_point(double x, double y, double z) {
    int size=sizesAndCapacities[0];
    coords[3 * size] = x;
    coords[3 * size + 1] = y;
    coords[3 * size + 2] = z;
    size++;
    sizesAndCapacities[0] = size;
}

void PolygonMeshSkeletonJNI::push_back_edge(int i, int j) {
    int size=sizesAndCapacities[1];
    edges[2 * size] = i;
    edges[2 * size + 1] = j;
    size++;
    sizesAndCapacities[1] = size;
}

void PolygonMeshSkeletonJNI::set_capacities(int nb_pts, int nb_edges)
{
  coords = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.setSKCoordsCapacityMID, nb_pts));
  edges = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.setSKEdgesCapacityMID, nb_edges));
}

PolygonMeshRidgesJNI::PolygonMeshRidgesJNI(JNIEnv* env, jobject obj)
  : jni(env), self(obj)
  , types(NULL)
  , strengths(NULL)
  , sharpnesses(NULL)
  , halfedges(NULL)
  , barycentric_coordinates(NULL)
  , nb_ridges_and_ranges(NULL)
{}

void PolygonMeshRidgesJNI::retrieveArrays()
{
  types = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRTypeBufferMID));
  strengths = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRStrengthBufferMID));
  sharpnesses = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRSharpnessBufferMID));
  halfedges = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRHalfedgeBufferMID));
  barycentric_coordinates = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRBCBufferMID));
  nb_ridges_and_ranges = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getRNbRangeBufferMID));
}

void PolygonMeshRidgesJNI::reserve(int nb_ridges, int total_nb_points)
{
  jni->CallObjectMethod(self, polygonMeshJNILink.ridgeReserveMID,nb_ridges, total_nb_points);
  retrieveArrays();
}

PolygonMeshUmbilicsJNI::PolygonMeshUmbilicsJNI(JNIEnv* env, jobject obj)
  : jni(env), self(obj)
  , types(NULL)
  , umbilics(NULL)
  , contour_halfedges(NULL)
  , nb_umbilics_and_ranges(NULL)
{}

void PolygonMeshUmbilicsJNI::retrieveArrays()
{
  types = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getUTypeBufferMID));
  umbilics = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getUmbilicBufferMID));
  contour_halfedges = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getUCHalfedgeBufferMID));
  nb_umbilics_and_ranges = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getUNbRangeBufferMID));
}

void PolygonMeshUmbilicsJNI::reserve(int nb_umbilics, int total_nb_contour_halfedges)
{
  jni->CallObjectMethod(self, polygonMeshJNILink.umbilicsReserveMID,nb_umbilics, total_nb_contour_halfedges);
  retrieveArrays();
}

void PointSetJNI::retrieve_arrays()
{
  point_x = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPSPointXBufferMID));
  point_y = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPSPointYBufferMID));
  point_z = (double*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPSPointZBufferMID));
  point_index = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPSPointIndexBufferMID));
  size_and_capacity = (int*)jni->GetDirectBufferAddress(jni->CallObjectMethod(self, polygonMeshJNILink.getPSSizeAndCapacityBufferMID));
}

void PointSetJNI::ensure_capacity(int c)
{
  jni->CallObjectMethod(self, polygonMeshJNILink.increasePSCapacityMID,c);
  // update vertex property arrays
  for (std::vector<PolygonMeshPropertyJNI*>::iterator it = properties.begin(); it != properties.end(); ++it)
    (*it)->retrieveArray();
  retrieve_arrays();
}

void PointSetJNI::registerProperty(PolygonMeshPropertyJNI* prop)
{
  properties.push_back(prop);
}
