SRC = ./SRC
INC = ./Include
LIB = ./LIB

TARGET = QEngine.exe

OBJS =  $(SRC)/complex.o \
		$(SRC)/matrices.o \
		$(SRC)/bit.o \
		$(SRC)/register.o \
		$(SRC)/operation.o \
		$(SRC)/circuit.o \
		$(SRC)/interface.o \
		$(SRC)/main.o

CXX = g++

#Compiler flags
DBFLAGS = -O3
WFLAGS = -Wall -std=c++17 -g

#Include & local libs flags
IFLAGS = -I${INC}
LFLAGS = -lstdc++ -fopenmp

#Compiling flags
CXXFLAGS = ${DBFLAGS} ${WFLAGS} ${IFLAGS} ${LFLAGS}
#LDFLAGS = 

all: $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)

.SUFFIXES: .o .c .cpp .cxx .cc
.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) $<
.c.o:
	$(CXX) -c $(CXXFLAGS) $<
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJS)