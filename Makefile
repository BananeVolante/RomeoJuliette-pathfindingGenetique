FLAGS :=-Wall -g -Wextra -std=c++17 
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
SRCPATH := src
EXEC := program

SRC := $(wildcard $(SRCPATH)/*.cpp)
HEADERS := $(wildcard $(SRCPATH)/*.h)
OBJ := $(SRC:.cpp=.o)


all: program

program: $(OBJ)
	g++ -o  $@ $^ $(FLAGS) $(SFML_LIBS)

%.o: %.cpp %.h
	g++ -o $@ -c $< $(FLAGS)

.PHONY: clean mrproper

clean:
	rm -rf $(SRCPATH)/*.o

mrproper: clean
	rm -rf $(EXEC)
