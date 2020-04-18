vpath %.h ./include
vpath %.o ./build
vpath lib% ./lib

CC			:=  g++
CFLAGS_lib		:=  -L./lib -lSim
CFLAGS_inc		:= 	-I./include
objdir			:= 	./build
libdir			:=	./lib
libobjs 		:= 	libGraph.o libScore.o
src			:=	./src/sim.cc
srcobj			:=	sim.o

.PHONY: clean

all: $(objdir)/libGraph.o $(objdir)/libScore.o $(libdir)/libSim.a $(objdir)/$(srcobj) sim

$(objdir)/libGraph.o : $(libdir)/libGraph.cc
	mkdir -p $(objdir)
	$(CC) $(CFLAGS_inc) -c $< -o $@

$(objdir)/libScore.o : $(libdir)/libScore.cc
	$(CC) -c $< -o $@

$(libdir)/libSim.a: ./build/libGraph.o
	ar crs $@ $^

$(objdir)/$(srcobj): $(src)
	$(CC) $(CFLAGS_inc) -c $< -o $@

sim : $(src)
	$(CC) $(objdir)/$(srcobj) $(CFLAGS_lib) $(CFLAGS_inc) -o $@

clean : 
	rm sim build/* lib/libSim.a
