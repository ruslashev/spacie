CXX = clang++
OBJS = $(patsubst src/%.cpp, .objs/%.o, $(shell find src -type f -name '*.cpp' ))
CXXFLAGS = -Wall -Werror -g -std=c++0x
LDFLAGS = -lSDL2 -lGLEW -lGL
EXECNAME = spacie

all: objdir $(EXECNAME)
	./$(EXECNAME)

.objs/%.o: src/%.cpp
	@$(CXX) -c -o $@ $< $(CXXFLAGS)
	@echo "Compiling $<"

$(EXECNAME): $(OBJS)
	@$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "Linking to $@"

valgrind: objdir $(EXECNAME)
	valgrind --leak-check=full ./$(EXECNAME)

callgrind: objdir $(EXECNAME)
	@valgrind --tool=callgrind ./$(EXECNAME)
	@kcachegrind callgrind.out.$!

objdir:
	@mkdir -p .objs/opengl
	@mkdir -p .objs/physics

clean:
	-rm -f $(EXECNAME)
	-rm -rf .objs/

