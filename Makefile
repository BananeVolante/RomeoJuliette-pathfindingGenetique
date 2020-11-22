FLAGS :=-Wall -g -Wextra -std=c++17 
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
SRCPATH := src
EXEC := program

SRC := $(wildcard $(SRCPATH)/*.cpp)
OBJ := $(SRC:.c=.o)

all: program

program: $(OBJ)
	g++ -o $@ $^ $(FLAGS) $(SFML_LIBS) 

%.o: %.c 
	g++ -o $@ -c $< $(FLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
