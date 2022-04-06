CXX=g++
NAME=new
SRC=$(wildcard src/*.cpp)
INCLUDES=-Iinclude -Ilib/vkfw/include
OBJS=$(patsubst src/%.cpp, out/%.o, $(SRC))
INCLUDE=$(wildcard include/*)




$(NAME): $(OBJS) $(INCLUDE)
	$(CXX) $(INCLUDES) $(OBJS) -o $(NAME) -g -lglfw

prepare:
	mkdir -p src out include tests/testList

out/%.o: src/%.cpp
	$(CXX) -o $@ -c $^ $(INCLUDES) -g 

clean:
	rm $(NAME) $(OBJS)

all: prepare $(OBJS) link
