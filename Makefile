all:	qtdriver	
qtdriver:	qttest.cpp
	g++	-std=c++11	-o	qtdriver	qttest.cpp	QuadTree.cpp	Node.cpp
clean:	
	rm	qtdriver