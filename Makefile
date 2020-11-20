FLAGS :=-Wall -g -Wextra -std=c++17
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
SRCPATH := src
OBJPATH := objectFiles


all: createOBJDir main

createOBJDir: 
	mkdir -p $(OBJPATH)

main: GeometricForms.o Map.o main.o SFMLDrawer.o PathManager.o Path.o
	g++ $(OBJPATH)/GeometricForms.o $(OBJPATH)/Map.o $(OBJPATH)/main.o $(OBJPATH)/SFMLDrawer.o $(OBJPATH)/PathManager.o $(OBJPATH)/Path.o -o program $(SFML_LIBS)

GeometricForms.o: $(SRCPATH)/GeometricForms.cpp $(SRCPATH)/GeometricForms.h
	g++ -c $(FLAGS) $(SRCPATH)/GeometricForms.cpp -o $(OBJPATH)/$@

Map.o: $(SRCPATH)/Map.cpp $(SRCPATH)/Map.h
	g++ -c $(FLAGS) $(SRCPATH)/Map.cpp -o $(OBJPATH)/$@

main.o: $(SRCPATH)/main.cpp
	g++ -c $(FLAGS) $(SRCPATH)/main.cpp -o $(OBJPATH)/$@

SFMLDrawer.o: $(SRCPATH)/SFMLDrawer.cpp $(SRCPATH)/SFMLDrawer.h
	g++ -c $(FLAGS) $(SRCPATH)/SFMLDrawer.cpp -o $(OBJPATH)/$@

PathManager.o: $(SRCPATH)/PathManager.cpp $(SRCPATH)/PathManager.h
	g++ -c $(FLAGS) $(SRCPATH)/PathManager.cpp -o $(OBJPATH)/$@

Path.o: $(SRCPATH)/Path.cpp $(SRCPATH)/Path.h
	g++ -c $(FLAGS) $(SRCPATH)/Path.cpp -o $(OBJPATH)/$@

clean:
	rm -f $(OBJPATH)/*