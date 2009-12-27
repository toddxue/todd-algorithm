.PHONY     : t all clean d
all        : 

CPPFLAGS   = -I. -It/common

TODDLIB    = libtodd-algorithm.a
srcs       = $(wildcard *.cpp)
$(TODDLIB) : $(srcs:.cpp=.o) ; $(AR) $(ARFLAGS) $@ $^

t_tests    = $(basename $(wildcard t/*/*.cpp))
$(t_tests) : $(TODDLIB)

all        : $(TODDLIB) $(t_tests)
clean      : ; $(RM) -r $(TODDLIB) $(wildcard *.o) $(t_tests) *.dSYM t/*/*.o t/*/*.dSYM

t          : all; prove -rsj100
d          : *.h *.cpp t/*/*.h t/*/*.cpp
	g++ -MM -MG $(CPPFLAGS) $^ | \
	perl -i -lpe 's{^(\S+?).o:\s+(\S+?)\1.cpp}{$$2$$&}' > .depend
-include .depend
