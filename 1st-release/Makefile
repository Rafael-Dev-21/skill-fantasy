SRCS := $(shell find src -type f -name "*.cc")
OBJS := $(patsubst src/%.cc, .obj/%.o, $(SRCS))

CXFLAGS := -g -ggdb3

all: build run clean

run: build
	./bin/1st-release

build: bin/1st-release

bin/1st-release: $(OBJS) | bin
	c++ -o $@ $^ -O0 $(CXFLAGS) -lncursesw

.obj/%.o: src/%.cc src/%.hh | .obj
	c++ $(CXFLAGS) -o $@ -c $<

.obj/client.o: src/client.cc | .obj
	c++ $(CXFLAGS) -o $@ -c $<

.obj:
	mkdir .obj

bin:
	mkdir bin

clean:
	rm -rf .obj bin
