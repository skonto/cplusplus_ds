CC=g++
INCLUDES=../include
INC=-I $(INCLUDES)
CPPFLAGS=-Wall -O3 -std=c++11 
DEP_FILE=.depend
SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)

all :  $(DEP_FILE) LIB clean_objects
	

LIB :  $(OBJS)
		ar rcs libds.a $^ 
	
%.o: %.cpp
		@$(CC) $(CPPFLAGS) $(INC) -c $< -o $@
			
$(DEP_FILE):
	    	@$(CC) -M -I$(INCLUDES) $(SRC) >> $(DEP_FILE)
	
ifeq ($(findstring $(MAKECMDGOALS), all, LIB), )
include $(DEP_FILE)	
endif
	
.PHONY : all clean clean_objects
clean_objects:
		rm -r *.o .depend


clean:
		rm -r *.a
		
