CXX=icpc
CXXFLAGS=-c -fopenmp
LDFLAGS=-fopenmp

OBJECTS=main.o merge-sort.o

merge: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o merge $(OBJECTS)

all:	merge

run:	all
	./merge

queue: all
	   echo 'cd $$PBS_O_WORKDIR ; ./merge $(TEST)' | qsub

clean:
	rm -f *.o merge *~ result* STD*
