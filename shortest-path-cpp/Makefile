CC := clang++ -std=c++11 -g
CFLAGS := -Iinclude -Wno-duplicate-decl-specifier -Wno-parentheses

all: bin/shortest_path bin/self_test bin/repl_test

bin/shortest_path: bin/tools.o bin/shortest_path.o bin/run.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/self_test: bin/tools.o bin/shortest_path.o bin/test.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/repl_test: bin/tools.o bin/shortest_path.o bin/repl.o
	@mkdir -p bin
	$(CC) $(CFLAGS) -o $@ $^

bin/tools.o: src/tools.cc include/graph.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/shortest_path.o: src/shortest_path.cc include/pairing_heap.hpp include/graph.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/run.o: test/run.cc include/graph.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/test.o: test/test.cc include/graph.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

bin/repl.o: test/repl.cc include/graph.hh
	@mkdir -p bin
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f bin/*.o
	rm -f include/*.~ include/*~ src/*.~ src/*~ test/*.~ test/*~
	rm -f *.~ *~
