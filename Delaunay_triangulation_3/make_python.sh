swig -python -c++ DT3.i
g++ -fPIC -frounding-math  -c  EPIC_Kernel.cpp DT3_wrap.cxx  -I/usr/include/python2.5 -I${CGAL_DIR}/../../../include -I${CGAL_DIR}/include
g++ -shared DT3_wrap.o EPIC_Kernel.o -o _DT3.so -lCGAL -lm -L${CGAL_DIR}/lib

#python main.py
