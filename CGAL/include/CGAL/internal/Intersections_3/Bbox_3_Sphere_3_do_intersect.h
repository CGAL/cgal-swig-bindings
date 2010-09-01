// Copyright (c) 2008  INRIA Sophia-Antipolis (France), ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://sloriot@scm.gforge.inria.fr/svn/cgal/trunk/Intersections_3/include/CGAL/internal/Intersections_3/Bbox_3_Sphere_3_do_intersect.h $
// $Id: Bbox_3_Sphere_3_do_intersect.h 58408 2010-09-01 08:49:24Z sloriot $
//
//
// Author(s)     : Camille Wormser, Jane Tournois, Pierre Alliez


#ifndef CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_SPHERE_3_DO_INTERSECT_H
#define CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_SPHERE_3_DO_INTERSECT_H

#include <CGAL/Sphere_3.h>
#include <CGAL/Bbox_3.h>

#include <CGAL/number_utils.h>


namespace CGAL {

namespace internal {

    template <class K>
    bool do_intersect(const typename K::Sphere_3& sphere,
        const CGAL::Bbox_3& bbox,
        const K&)
    {
        typedef typename K::FT FT;
        typedef typename K::Point_3 Point;
        FT d = FT(0);
        FT distance = FT(0);
		Point center = sphere.center();

		if(center.x() < (FT)bbox.xmin())
		{
			d = (FT)bbox.xmin() - center.x();
			distance += d * d;
		}
		else if(center.x() > (FT)bbox.xmax())
		{
			d = center.x() - (FT)bbox.xmax();
			distance += d * d;
		}

		if(center.y() < (FT)bbox.ymin())
		{
			d = (FT)bbox.ymin() - center.y();
			distance += d * d;
		}
		else if(center.y() > (FT)bbox.ymax())
		{
			d = center.y() - (FT)bbox.ymax();
			distance += d * d;
		}

		if(center.z() < (FT)bbox.zmin())
		{
			d = (FT)bbox.zmin() - center.z();
			distance += d * d;
		}
		else if(center.z() > (FT)bbox.zmax())
		{
			d = center.z() - (FT)bbox.zmax();
			distance += d * d;
		}

		// For unknown reason this causes a syntax error on VC2005
		// but compiles fine on Linux and MAC
		//int i;
		//for(i = 0; i < 3; ++i)
		//{
		//	if(center[i] < (FT)bbox.min(i))
		//	{
		//		d = (FT)bbox.min(i) - center[i];
		//		distance += d * d;
		//	}
		//	else if(center[i] > (FT)bbox.max(i))
		//	{
		//		d = center[i] - (FT)bbox.max(i);
		//		distance += d * d;
		//	}
		//}

		return distance <= sphere.squared_radius();
    }

} // namespace internal

template <class K>
bool do_intersect(const CGAL::Sphere_3<K>& sphere,
                  const CGAL::Bbox_3& bbox)
{
    return typename K::Do_intersect_3()(sphere, bbox);
}

template <class K>
bool do_intersect(const CGAL::Bbox_3& bbox,
                  const CGAL::Sphere_3<K>& sphere)
{
    return typename K::Do_intersect_3()(sphere, bbox);
}

} //namespace CGAL

#endif  // CGAL_INTERNAL_INTERSECTIONS_3_BBOX_3_SPHERE_3_DO_INTERSECT_H
