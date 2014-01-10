# Change these
cxxtestpath = ../cxxtest/
testcode    = example_test.h

testcode.cpp: $(testcode)
	python $(cxxtestpath)cxxtestgen.py --error-printer -o testcode.cpp $(testcode)

runtest0%: testcode.cpp
	g++ -I $(cxxtestpath) -o runtest0$* testcode.cpp Matrix0$*.o

runmatrix: testcode.cpp
	g++ -stdlib=libc++ -std=c++0x -I $(cxxtestpath) -o runtest testcode.cpp ../../cprog13-vector/Matrix.cpp

clean:
	touch runtest01 testcode.cpp
	rm runtest0* testcode.cpp
	rm runtest testcode.cpp

