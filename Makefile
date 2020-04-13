all : sim.o
	g++ -o sim sim.o

sim.o : sim.cc
	g++ -g -c sim.cc

clean : 
	rm sim.o sim
