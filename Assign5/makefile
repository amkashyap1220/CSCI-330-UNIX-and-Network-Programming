#
# PROGRAM:    Assignment 5
# PROGRAMMER: alexander kashyap
# LOGON ID:   z1926618
# DATE DUE:   feb 12 2021
#
    
# Compiler variables
CXX = g++
CXXFLAGS = -std=c++11 # -Wall -Werror
        
# Rule to link object code files to create executable file
dog: main.o dataprocess.o
	$(CXX) $(CXXFLAGS) -o dog $^

# Rules to compile source code file to object code
main.o: main.cc dataprocess.h
dataprocess.o: dataprocess.cc dataprocess.h
   
# Pseudo-target to remove object code and executable files
clean:
	rm -f dog *.o
