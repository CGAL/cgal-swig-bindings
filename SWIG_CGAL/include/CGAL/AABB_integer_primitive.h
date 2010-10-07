// Copyright (c) 2010 GeometryFactory (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
//
// Author(s)     : Sebastien Loriot
//
//******************************************************************************
// File Description :
//
//******************************************************************************

#ifndef CGAL_AABB_INTEGER_PRIMITIVE_H
#define CGAL_AABB_INTEGER_PRIMITIVE_H

namespace CGAL {
    //the integer can be used if using several AABB_tree, the static counter of primitive_id 
    //is different for different value of k.
    template <class Primitive,int k=0>
    class AABB_integer_primitive
    {
    public:
        // types
        typedef int Id; // Id type
        typedef typename Kernel_traits<Primitive>::Kernel::Point_3  Point; // point type
        typedef Primitive                                           Datum; // datum type

    private:
        // member data
        Id index;
        Datum m_datum;

        // constructor
    public:
        static int& current_id(){
          static int current_id = -1;
          return current_id;
        }
    
        static void reset_id(){
          current_id()=-1;
        }
        
        
        AABB_integer_primitive() {}
        template <class Iterator>
        AABB_integer_primitive(Iterator it)
            : index( ++current_id() )
        {
            m_datum = *it; // copy primitive
        }
        AABB_integer_primitive(const AABB_integer_primitive& primitive)
        {
            m_datum = primitive.datum();
            index = primitive.id();
        }
    public:
        Id& id() { return index; }
        const Id& id() const { return index; }
        Datum& datum() { return m_datum; }
        const Datum& datum() const { return m_datum; }

        /// Returns a point on the primitive
        Point reference_point() const { return m_datum.vertex(0); }
    };

}  // end namespace CGAL


#endif // CGAL_AABB_INTEGER_PRIMITIVE_H

