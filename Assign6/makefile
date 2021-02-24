# PROGRAM:    Assignment 6
# PROGRAMMER: alexander kashyap
# LOGON ID:   z1926618
# DATE DUE:   feb 12 2021
    
# Compiler variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror
        
# Rule to link object code files to create executable file
assign6: pipes.o
	$(CXX) $(CXXFLAGS) -o assign6 $^

# Rules to compile source code file to object code
main.o: pipes.cpp
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f assign6 *.o