CFLAGS = -Wno-endif-labels -Werror -Wall
LDFLAGS = 
PROG = skill_fantasy
CXX = clang++

DIRS = src/state/*.cc src/system/*.cc

all: $(PROG)

$(PROG): src/*
	$(CXX) $(CFLAGS) src/main.cc $(DIRS) -o $(PROG)

clean:
	rm $(PROG)
