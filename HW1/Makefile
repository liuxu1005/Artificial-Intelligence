CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall
LDFLAGS=-g 
LDLIBS=

SRCS= $(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: search

search: $(OBJS)
	$(CXX) $(LDFLAGS) -o search $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
