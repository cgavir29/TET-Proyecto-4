CXX=mpiicpc
CXXFLAGS=-c -qopenmp
LDFLAGS=-qopenmp

OBJECTS=main.o merge-sort.o

merge: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o merge $(OBJECTS)

all:	merge

run:	all
	./merge

queue: all
	   echo 'cd $$PBS_O_WORKDIR ; mpirun -machinefile $$PBS_NODEFILE ./merge $(TEST)' | qsub

clean:
	rm -f *.o merge *~ result* STD*
