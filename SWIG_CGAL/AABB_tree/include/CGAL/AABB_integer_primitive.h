// ------------------------------------------------------------------------------
// Copyright (c) 2010 GeometryFactory (France).
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------

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
        AABB_integer_primitive() {}
        template <class Iterator>
        AABB_integer_primitive(Iterator it)
        {
            m_datum = *it; // copy primitive
            index=-1;
        }
        AABB_integer_primitive(const Primitive& p)
        {
            m_datum = p; // copy primitive
            index=-1;
        }
    public:
        Id& id() { return index; }
        const Id& id() const { return index; }
        Datum& datum() { return m_datum; }
        const Datum& datum() const { return m_datum; }

        /// Returns a point on the primitive
        Point reference_point() const { return m_datum.vertex(0); }
    };

  template <class Primitive, int k>
  void update_primitive_id(AABB_integer_primitive<Primitive,k>& prim,int& counter)
  {
    prim.id()=++counter;
  }
}  // end namespace CGAL


#endif // CGAL_AABB_INTEGER_PRIMITIVE_H

