CXX=icpc

OBJECTS=merge-sort.o

merge: $(OBJECTS)
	$(CXX) -o merge $(OBJECTS)

all:	merge

run:	all
	./merge

clean:
	rm -f *.o merge *~ result*