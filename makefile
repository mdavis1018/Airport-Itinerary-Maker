CXX = g++
CXXFLAGS = -Wall -g
IODIR = ../../proj3_IO/

proj3: Route.o Airport.o Navigator.o proj3.cpp 
	$(CXX) $(CXXFLAGS) Route.o Airport.o Navigator.o proj3.cpp -o proj3

Navigator.o: Airport.o Route.o Navigator.h Navigator.cpp
	$(CXX) $(CXXFLAGS) -c Navigator.cpp

Route.o: Airport.o Route.h Route.cpp
	$(CXX) $(CXXFLAGS) -c Route.cpp

Airport.o: Airport.h Airport.cpp
	$(CXX) $(CXXFLAGS) -c Airport.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3 proj3_data.txt

run1:
	./proj3 proj3_data.txt

val1:
	valgrind ./proj3 proj3_data.txt

submit:
	cp Airport.h Airport.cpp Route.h Route.cpp Navigator.h Navigator.cpp proj3.cpp ~/cs202proj/proj3

##########Grading Commands############

##Used to do regular tests
grading:
	valgrind ./proj3 $(IODIR)proj3_grading.txt

##Used if the student forgot the header files
copy_headers:
	cp $(IODIR)Airport.h $(IODIR)Route.h $(IODIR)Navigator.h .

##Used to copy the test file into the current directory
copy_test:
	cp $(IODIR)proj3_grading.txt .
