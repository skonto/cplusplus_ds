CC=g++
INCLUDES=../include
INC=-I $(INCLUDES)
CPPFLAGS=-Wall -O3 -std=c++11 
DEP_FILE=.depend
SRC=$(wildcard *.cpp)
OBJS=$(SRC:.cpp=.out)

all :   $(DEP_FILE) exec run_tests clean

run_tests: $(OBJS)
		$(patsubst %,./%;,$^)		

exec :  $(OBJS)
	
%.out: %.cpp
		@$(CC) $(CPPFLAGS) -I$(INCLUDES) $< -o $@ -L../src -lds
		
	
$(DEP_FILE):
	    @$(CC) $(CPPFLAGS) -M -I$(INCLUDES) $(SRC) >> $(DEP_FILE)
	
ifeq ($(findstring $(MAKECMDGOALS), all,  $(DEP_FILE)), )
include $(DEP_FILE)	
endif
	
.PHONY : all clean


clean:
		rm -r  *.out .depend
		
