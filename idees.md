#infos initiales
- fait en CPP, car j'aime bien ca
- je fait ca seul


#Idees projet POO
- pour trouver le chemin, j'utilise un algo génétique
- vu que sur le sujet, des cercles sont dessinés comme obstacles, je pense qu'un système de case n'est pas adapté, il faut donc utiliser des hitbox "géométriques" -> moins opti par contre(enfin, je vois un moyen d'opti mais je suis pas sûr de le faire)

## fonctionnement algo génétique
- on génere l'ADN(les briques élémentaires qui seraient ici gauche droit haut bas?)
- on génere les "chromosomes" de base : un assemblement d'adn ?



- on évalue les scores(distance a vol d'oiseau entre l'endroit d'arrivée et juliette)
- on selectionne avec un aléatoire pondéré par leur score
- on mélange ces meilleurs
- on les modifie un peu(4% max)

## comment faire
 - un terrain en global
 - une fonction pour le remplir d'obstacles
    - pour ca : soit je crée directement l'interface graphique pour m'assurezr qu'il y ait un chemin possible lors des tests
    - soit je fait la solution de créer un chemin puis d'ajouter des obstacles hors de ce chemin
    - je vais probablement fiare le coup de l'interface graphique car ce sera simple(lol)
 - l'ADN : la distance "élémentaire" utilisée par l'algo sera paramétrable
 - ce qui me dérange, c'est le nombre de briques a mettre, que faire
  - quel est le nbr maximum/minimum a mettre(selon les obstables, on pourrait trés bien avoir a faire 3 fois la map en diagonal en distance)
  - est ce que tout les chromosomes ont la même distance parcourue?
  - si non, est ce que je détermine une "norme" du chromosome puis je met les déplacements puis je remplis avec des déplacements de 0, est ce que je met une taille (au niveau espace mémoire) égale a la norme, et donc il n'y a plus rien aprés le déplacement, est que que ils ont tous la même taille mais dans ce cas la j'ajoute dans l'ADN un déplacement nul?
  -je pense tenter le coup du fait qu'on peut se déplacer de 0

## l'interface 
- je connais (et maitrise un peu) 3 trucs qui peuvent faire une interface graphique en c++, allegro, Qt, et unreal engine.
- utiliser unreal engine est probablement pas trés sage car il va falloir faire plus que juste coller un programme console dessus
- Qt permettra d'avoir facilement des boutons en compagnie mais avec allegro, dessiner la carte et les chemins sera bien plus simple
- pour l'instant je vais dire allegro


## pour le code
 - une classe map, avec de quoi générer la map
 - du coup une classe d'objet géométrique
 - une classe pour gérer les chemins , qui gere aussi l'algo génétique?
 - une classe pour afficher?
 