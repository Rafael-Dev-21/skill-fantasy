# nome do projeto
PROJ_NAME=skillfantasy

# código fonte
CXX_SOURCE=$(wildcard ./src/*.cc);

# cabeçalhos
HXX_SOURCE=$(wildcard ./src/*.hh);

# objetos
OBJ=$(subst .cc,.o,$(subst src,obj,$(CXX_SOURCE)))

# compilador
CXX=clang++

# marcas do compilador
CXX_FLAGS=-W         \
          -Wall      \
          -std=c++11

# comando usado para limpar o alvo
RM= rm -rf



#
# compilação e linkagem
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME).exe: $(OBJ)
	@ echo 'Building binary using MinGW linker: $@'
	$(CXX) -I./pdcurses -L./pdcurses.dll --target=x86_64-win32 $^ -o $@
	@ echo 'Finished building binary: $@'

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using clang++ linker: $@'
	$(CXX) -lncurses $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./obj/%.o: ./src/%.cc ./src/%.hh
	@ echo 'Building target using clang++ compiler: $<'
	$(CXX) -c $< $(CXX_FLAGS) -o $@
	@ echo ' '

./obj/main.o: ./src/main.cc
	@ echo 'Building target using clang++ compiler: $<'
	$(CXX) -c $< $(CXX_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p obj

clean:
	@ $(RM) ./obj/*.o $(PROJ_NAME) *~
	@rmdir obj

.PHONY: all clean
