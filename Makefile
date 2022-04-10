CXX=g++
NAME=new
SRC = $(wildcard src/*.cpp)
SRC +=$(wildcard src/gui/*.cpp)
INCLUDES=-Iinclude -Ilib/vkfw/include
OBJS=$(patsubst src/%.cpp, out/%.o, $(SRC))
INCLUDE=$(wildcard include/*)




$(NAME): $(OBJS) $(INCLUDE)
	$(CXX) $(INCLUDES) $(OBJS) -o $(NAME) -g -lglfw


out/gui:
	mkdir -p out/gui

folders: out/gui

out/%.o: src/%.cpp
	$(CXX) -o $@ -c $^ $(INCLUDES) -g 

clean:
	rm $(NAME) $(OBJS)

all: folders $(OBJS) link