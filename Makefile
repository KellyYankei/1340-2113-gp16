CXX = g++
CXXFLAGS = -I lib/ncurses/include -I lib/ncurses/include/ncursesw -L lib/ncurses/lib -pedantic-errors -std=c++11

TARGET = pyramid

$(TARGET): pyramid.o actions.o structures.o saveload.o reverse.o printing.o judgement.o board.o tutorial.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) pyramid.o actions.o structures.o saveload.o reverse.o printing.o judgement.o board.o tutorial.o -lncurses

pyramid.o: source/pyramid.cpp source/actions.h source/structures.h source/saveload.h source/printing.h source/judgement.h source/tutorial.h
	$(CXX) $(CXXFLAGS) -c source/pyramid.cpp -lncurses

board.o: source/board.cpp source/board.h 
	$(CXX) $(CXXFLAGS) -c source/board.cpp -lncurses

actions.o: source/actions.cpp source/actions.h source/structures.h
	$(CXX) $(CXXFLAGS) -c source/actions.cpp

structures.o: source/structures.cpp source/structures.h
	$(CXX) $(CXXFLAGS) -c source/structures.cpp

saveload.o: source/saveload.cpp source/structures.h source/actions.h
	$(CXX) $(CXXFLAGS) -c source/saveload.cpp

reverse.o: source/reverse.cpp source/saveload.h source/actions.h source/structures.h
	$(CXX) $(CXXFLAGS) -c source/reverse.cpp

printing.o: source/printing.cpp source/structures.h
	$(CXX) $(CXXFLAGS) -c source/printing.cpp

judgement.o: source/judgement.cpp source/structures.h
	$(CXX) $(CXXFLAGS) -c source/judgement.cpp

tutorial.o: source/tutorial.cpp source/judgement.h source/printing.h source/structures.h
	$(CXX) $(CXXFLAGS) -c source/tutorial.cpp

clean:
	rm -f $(TARGET) *.o save*.txt

.PHONY: clean
