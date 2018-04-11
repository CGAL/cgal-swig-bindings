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

package CGAL.Polygon_mesh;

import java.nio.ByteBuffer;

/**
 * Interface representing a {@link IPolygonMeshMultiComponentProperty} holding byte values
 */
public interface IPolygonMeshByteProperty extends IPolygonMeshMultiComponentProperty {

  /**
   * Returns the default value used to initialize newly allocated values
   */
  byte initializationValue();

  /**
   * Returns the underlying buffer 
   */
  ByteBuffer getByteBuffer();
  
  /**
   * Returns the value corresponding to the given element. If the property is multi-component, the first component will be returned.<br>
   * <b>WARNING</b>: remember to check if the element is valid by calling isValidVertex/Edge/Face/Halfedge on the corresponding mesh.
   */
  byte get(int e);
  
  /**
   * Sets the value corresponding to the given element. If the property is multi-component, the first component will be set.<br>
   * <b>WARNING</b>: remember to check if the element is valid by calling isValidVertex/Edge/Face/Halfedge on the corresponding mesh.
   */
  void set(int e, byte v);

  /**
   * Returns the value corresponding to the given component of the property on the given element.<br>
   * <b>WARNING</b>: remember to check if the element is valid by calling isValidVertex/Edge/Face/Halfedge on the corresponding mesh.
   */
  byte get(int e, int component);
  
  /**
   * Sets the value corresponding to the given component of the property on the given element.<br>
   * <b>WARNING</b>: remember to check if the element is valid by calling isValidVertex/Edge/Face/Halfedge on the corresponding mesh.
   */
  void set(int e, int component, byte v);


}
