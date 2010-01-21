.PHONY     : t all clean d
all        :

CXX        = g++
CC         = $(CXX)
CPPFLAGS   = -I. -It/common $(DEF)

TODDLIB    = libtodd-algorithm.a
srcs       = $(wildcard *.cpp)
$(TODDLIB) : $(srcs:.cpp=.o) ; $(AR) $(ARFLAGS) $@ $^

t_tests    = $(basename $(wildcard t/*/*.cpp))
$(t_tests) : $(TODDLIB)

benchmark  = $(basename $(wildcard benchmark/*.cpp))
$(benchmark) : $(TODDLIB)

all        : $(TODDLIB) $(t_tests) $(benchmark)
clean      : ; $(RM) -r $(TODDLIB) $(wildcard *.o) $(t_tests) $(benchmark) *.dSYM */*.dSYM */*/*.dSYM */*.o */*/*.o

t          : all; prove t/*/*.t -rsj100
d          : *.h *.cpp t/*/*.h t/*/*.cpp benchmark/*.cpp
	g++ -MM -MG $(CPPFLAGS) $^ | \
	perl -i -lpe 's{^(\S+?).o:\s+(\S+?)\1.cpp}{$$2$$&}' > .depend
-include .depend

CXXFLAGS   = -g
