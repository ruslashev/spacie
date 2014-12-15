CXX = clang++
OBJS = $(patsubst src/%.cpp, .objs/%.o, $(shell find src -type f -name '*.cpp' ))
CFLAGS = -Wall -Werror -g -std=c++0x
LDFLAGS = -lSDL2 -lGLEW
EXECNAME = spacie

all: objdir $(EXECNAME)
	./$(EXECNAME)

.objs/%.o: src/%.cpp
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXECNAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

objdir:
	@mkdir -p .objs/
	@mkdir -p .objs/opengl

clean:
	-rm -f .objs/*.o $(EXECNAME)

