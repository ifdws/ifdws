CC=gcc
all: bin bin/ifdws

bin:
	mkdir bin

bin/ifdws:
	$(CC) core/src/*.cpp src/*.cpp -lstdc++ -Icore/src -o bin/ifdws

clean:
	rm -r bin