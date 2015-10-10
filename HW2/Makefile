CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall
LDFLAGS=-g 
LDLIBS=

SRCS= $(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: xwd

xwd: $(OBJS)
	$(CXX) $(LDFLAGS) -o xwd $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
