
#  Shape_detection_3

**Version: 0.0.2**

C++ to Python bindings for CGAL's Shape_detection_3 library.


**Table of Contents**
*  [Prerequisites](#prerequisites)
*  [Installation](#installation)
*  [Usage](#usage)
    *  [Constructors](#constructors)
    *  [Accessors](#accessors)
    *  [Mutators](#mutators)

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

**NOTE:**  Shape_detection_3 is templated, and requires CGAL type `Shape_type` as parameter.

#### Constructors
*  `Shape_detection_3()`    --  Creates an uninitialized shape detection object
*  `Shape_detection_3(p)`   --  Creates a shape detection object using `p` as set of points


####  Accessors
*  `s.getShapes()`   --  Returns iterator detected shapes in `s`


####  Mutators
*  `s.clear()`    --  Clears current selection of points
*  `s.setPoints(p)`    --  Sets current selection of points to `p`
*  `s.detect()`   --  Detects shapes within shape detection object (`s`)


