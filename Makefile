all: simple
	./simple

simple: simple.cxx
	g++ -Wall -o simple simple.cxx

simple.cxx: simple.winxed winxedxx.winxed winxedxx.h
	winxed -L /home/julian/winxed winxedxx.winxed simple.winxed > simple.cxx

clean:
	rm -f simple
	rm -r simple.cxx
