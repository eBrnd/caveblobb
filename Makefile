CXX := g++
CXXFLAGS := -lSDL -lSDL_ttf -lSDL_gfx -Werror -Wall -pthread $(CXXFLAGS)
BINARY := caveworm

ifneq "$(DEBUG)" ""
    CXXFLAGS += -g
else
    CXXFLAGS += -O3
endif

ifeq "$(VERBOSE)" ""
    VERBOSE := @
else
    VERBOSE := 
    FIND_VERB := -print
    RM_VERB := -v
endif

SRC := $(wildcard *.cpp)
OBJECTS := $(SRC:.cpp=.o)
MODULES := 

all: $(BINARY)

-include $(OBJECTS:.o=.dep)

$(BINARY): $(MODULES) $(OBJECTS)
	@echo "Linking main executable"
	$(VERBOSE)$(CXX) $(CXXFLAGS) -o $(BINARY) $(OBJECTS)

%.dep: %.cpp
	@echo "Analyzing dependencies of $*.cpp"
	$(VERBOSE)./depend.sh `dirname $*` $(CXXFLAGS) $*.cpp > $@

%.o: %.cpp
	@echo "Compiling $*.cpp"
	$(VERBOSE)$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o

.PHONY: clean-deps clean-objs

clean: clean-deps clean-objs

clean-deps:
	-$(VERBOSE)find . -name '*.dep' -delete $(FIND_VERB)

clean-objs:
	-$(VERBOSE)find . '(' -name '*.dep' -or -name '*.o' ')' -delete $(FIND_VERB)
	-$(VERBOSE)rm $(RM_VERB) -f $(BINARY)

%:
	@echo $* > /dev/null
