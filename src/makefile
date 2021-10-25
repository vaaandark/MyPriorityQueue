objects = test.o FibonacciHeap.o

example: $(objects)
	cc -o my_priority_queue $(objects)

test.o: FibonacciHeap.h

.PYONY: clean

clean:
	rm my_priority_queue $(objects)