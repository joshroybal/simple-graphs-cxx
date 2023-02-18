CXX = c++
CFLAGS = -std=c++98 -pedantic-errors -Wextra -Wall -Werror -O2 -g
LFLAGS =
HDR = graphs.hpp
SRC = graphs.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
BIN = driver

$(BIN): $(OBJ)
	$(CXX) -o $@ $^ $(LFLAGS)

%.o: %.cpp $(HDR)
	$(CXX) -c $< $(CFLAGS)

.PHONY : clean
clean:
	$(RM) $(BIN) $(OBJ) *~
