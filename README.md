
#  Shape_detection_3

**Version: 0.0.3**

C++ to Python bindings for CGAL's Shape_detection_3 library.


**Table of Contents**
*  [Prerequisites](#prerequisites)
*  [Installation](#installation)
*  [Usage](#usage)
*  [Methods](#methods)
    *  [Constructors](#constructors)
    *  [Accessors](#accessors)
    *  [Mutators](#mutators)
    *  [Utilities](#utilities)


###  Prerequisites

**Install CGAL Libraries**
```bash
[ ]$  sudo apt-get install libcgal-dev
```

**Install SWIG**
```bash
[ ]$  sudo apt-get install swig
```

**Install SWIG-CGAL Bindings**
```bash
[ ]$  git clone https://github.com/CGAL/cgal-swig-bindings
```

###  Installation

```bash
[ ]$  mkdir cgal-swig-bindings/SWIG_CGAL/User_packages && cd cgal-swig-bindings/SWIG_CGAL/User_packages
[ ]$  echo "add_subdirectory(Shape_detection_3)" >> CMakeLists.txt
[ ]$  git clone https://github.com/CodyFagley/Shape_detection_3
[ ]$  cd ../.. 
[ ]$  cmake .
[ ]$  make
```

###  Usage

```python
from CGAL import CGAL_Shape_detection_3
s = CGAL_Shape_detection_3.Shape_detection_3()
p = s.Point_3(1, 1, 1)
v = s.Vector_3(0, 1, 0)
pwn = s.Point_with_normal(p, v)
s.addPointWithNormal(pwn)
s.detect()
```

###  Methods

#### Constructors
*  `Shape_detection_3()`    --  Creates an uninitialized shape detection object
*  `Shape_detection_3(p)`   --  Creates a shape detection object using `p` as set of points (w/ normals)


####  Accessors
*  `s.getShapes()`   --  Returns iterator detected shapes in `s`
*  `s.countShapes()` --  Returns number of detected shapes in `s`


####  Mutators
*  `s.clear()`    --  Clears current selection of points
*  `s.addPointWithNormal` --  Adds a Vertex
*  `s.setPoints(p)`    --  Sets current selection of points to `p`
*  `s.detect()`   --  Detects shapes within shape detection object (`s`)


###  Utilities
*  `s.Point_3(x, y, z)`  --  Builds recognizable 3D Point
*  `s.Vector_3`(x, y, z) --  Builds recognizable 3D Vector
*  `s.Point_with_normal(p, v)`  --  Builds recognizable Vertex from Point and Normal Vector
