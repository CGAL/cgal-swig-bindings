
#  Shape_detection_3

This repository contains C++ TO Python bindings for CGAL's Shape_detection_3 library.


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
[ ]$  echo "add_subdirectory(Shape_detection_3)" > CMakeLists.txt
[ ]$  cd ../.. 
[ ]$  cmake .
[ ]$  make**Mutators**
```

###  Usage

**NOTE:**  Shape_detection_3 is templated, and requires a Shape_Type on creation.

#### Constructors
*  `Shape_detection_3()`    --  Creates a shape detection object without set of points
*  `Shape_detection_3(p)`   --  Creates a shape detection object using `p` as set of points


####  Accessors
*  `s.getShapes()`   --  Returns iterator detected shapes in shape detection object (`s`)


####  Mutators
*  `s.clear()`    --  Clears current selection of points
*  `s.setPoints(p)`    --  Sets current selection of points to `p`
*  `s.detect()`   --  Detects shapes within shape detection object (`s`)


