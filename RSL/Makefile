#OBJS specifies which files to compile as part of the project
OBJS = RSL.cpp RSLTest.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -std=c++14 

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = RSLTest

debug : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -DDEBUG -O -o $(OBJ_NAME).debug

dev : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -DDEBUG -DRSL_EXPERIMENTAL -O -o $(OBJ_NAME)

release : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -O2 -o $(OBJ_NAME)

#This is the target that compiles our executable
all : clean debug release

clean:
	rm -f $(OBJ_NAME) $(OBJ_NAME).debug *.log *.o *.a *.gch	