# POO2RomeoJuliette

A pathfinding algorithm using a genetic algorithm. Initially a school project.

## How to use

Requires SFML(libsfml-dev package on debian)

./program
start with default parameters : 

> screenSize = 1920 * 1080
> mapSize = 1920*1080
> startPoint = {0,0}; endPoint = {1920,1080};
> pathLen = 1000; 
> pathNumber = 10;
> baseElement = 10;
> mutationChance = 4

or

./program screenSizeX screenSizeY mapSizeX mapSizeY startPointX startPointY pathLength NumberOfPaths baseElement mutationChance

start with all parameters
note that screen size and map size can be different, the screen will be deformed to fit the map
