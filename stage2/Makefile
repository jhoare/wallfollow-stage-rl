CXX=g++
CFLAGS=-I.. `pkg-config playerc++ --cflags` -Wall -Werror -g
LIBS=`pkg-config playerc++ --libs`
EXE=testStateSpace testActionSet testMatrix testLoadMatrix hoare-Project3

all: $(EXE)

.cpp.o:
	$(CXX) $(CFLAGS) $< -c

testStateSpace: testStateSpace.o ../StateSpace.cpp RobotCenterPlayer.o
	$(CXX) $(CFLAGS) testStateSpace.o ../StateSpace.cpp RobotCenterPlayer.o $(LIBS) -o $@

testActionSet: testActionSet.o ../ActionSet.cpp ../StateSpace.cpp testStateSpace.o RobotCenterPlayer.o
	$(CXX) $(CFLAGS) testActionSet.o ../ActionSet.cpp ../StateSpace.cpp RobotCenterPlayer.o $(LIBS) -o $@

hoare-Project3: hoare-Project3.o ../ActionSet.cpp ../StateSpace.cpp RobotCenterPlayer.o
	$(CXX) $(CFLAGS) hoare-Project3.o ../ActionSet.cpp ../StateSpace.cpp RobotCenterPlayer.o $(LIBS) -o $@

testMatrix: testMatrix.o 
	$(CXX) $(CFLAGS) testMatrix.o -o $@ 

testLoadMatrix: testLoadMatrix.o 
	$(CXX) $(CFLAGS) $< -o $@ 

clean: 
	rm -f *.o $(EXE) core
