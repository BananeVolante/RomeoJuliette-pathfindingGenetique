FLAGS :=-Wall -g
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system
SRCPATH := src
OBJPATH := objectFiles


all: main

main: GeometricForms.o Map.o main.o SFMLDrawer.o
	g++ $(OBJPATH)/GeometricForms.o $(OBJPATH)/Map.o $(OBJPATH)/main.o $(OBJPATH)/SFMLDrawer.o -o program $(SFML_LIBS)

GeometricForms.o: $(SRCPATH)/GeometricForms.cpp $(SRCPATH)/GeometricForms.h
	g++ -c $(FLAGS) $(SRCPATH)/GeometricForms.cpp -o $(OBJPATH)/$@

Map.o: $(SRCPATH)/Map.cpp $(SRCPATH)/Map.h
	g++ -c $(FLAGS) $(SRCPATH)/Map.cpp -o $(OBJPATH)/$@

main.o: $(SRCPATH)/main.cpp
	g++ -c $(FLAGS) $(SRCPATH)/main.cpp -o $(OBJPATH)/$@

SFMLDrawer.o: $(SRCPATH)/SFMLDrawer.cpp $(SRCPATH)/SFMLDrawer.h
	g++ -c $(FLAGS) $(SRCPATH)/SFMLDrawer.cpp -o $(OBJPATH)/$@

clean:
	rm -f $(OBJPATH)/*