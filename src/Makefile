CC = g++ -fopenmp -DMINGW
#CC = g++ -mno-cygwin -DMINGW
CFLAG = -c -O3 -I$(PF_FILES)/include 
CCFLAG = -o laplace2d_fem -L$(PF_FILES)/lib/linux_64 -lplatform -lm
OBJECT=Vector3d.o Vector2d.o \
	Timer.o gourmain.o cmdlineopts.o \
	bicgstab.o \
	Mesh2d.o  Element2d.o ShapeFunc2d.o Integral2d.o \
	LaplaceFEM2d.o Laplace2dFEMSimulator.o laplace2d_fem_driver.o

all :$(OBJECT)
	$(CC) $(OBJECT) $(CCFLAG)

Vector3d.o : coord/Vector3d.cpp coord/Vector3d.h
	$(CC) coord/Vector3d.cpp $(CFLAG)

Vector2d.o : coord/Vector2d.cpp coord/Vector2d.h
	$(CC) coord/Vector2d.cpp $(CFLAG)

Timer.o : utility/Timer.cpp utility/Timer.h
	$(CC) utility/Timer.cpp $(CFLAG)

gourmain.o : udf/gourmain.cpp udf/gourmain.h
	$(CC) udf/gourmain.cpp $(CFLAG)

cmdlineopts.o : udf/cmdlineopts.cpp udf/cmdlineopts.h
	$(CC) udf/cmdlineopts.cpp $(CFLAG)

bicgstab.o : bicgstab/bicgstab.cpp bicgstab/bicgstab.h
	$(CC) bicgstab/bicgstab.cpp $(CFLAG)

Mesh2d.o : mesh/Mesh2d.cpp mesh/Mesh2d.h
	$(CC) mesh/Mesh2d.cpp $(CFLAG)

Element2d.o : mesh/Element2d.cpp mesh/Element2d.h
	$(CC) mesh/Element2d.cpp $(CFLAG)

ShapeFunc2d.o : mesh/ShapeFunc2d.cpp mesh/ShapeFunc2d.h
	$(CC) mesh/ShapeFunc2d.cpp $(CFLAG)

Integral2d.o : integral/Integral2d.cpp integral/Integral2d.h
	$(CC) integral/Integral2d.cpp $(CFLAG)

LaplaceFEM2d.o : LaplaceFEM2d.cpp LaplaceFEM2d.h
	$(CC) LaplaceFEM2d.cpp $(CFLAG)

Laplace2dFEMSimulator.o : Laplace2dFEMSimulator.cpp Laplace2dFEMSimulator.h
	$(CC) Laplace2dFEMSimulator.cpp $(CFLAG)

laplace2d_fem_driver.o : laplace2d_fem_driver.cpp
	$(CC) laplace2d_fem_driver.cpp $(CFLAG)

clean : 
	rm -f *.o laplace2d_fem

install :
	strip laplace2d_fem
	cp laplace2d_fem ../bin
