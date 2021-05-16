# infos initiales
- fait en CPP, car j'aime bien ca
- je fait ca seul


# Idees projet POO
- pour trouver le chemin, j'utilise un algo génétique
- vu que sur le sujet, des cercles sont dessinés comme obstacles, je pense qu'un système de case n'est pas adapté, il faut donc utiliser des hitbox "géométriques" -> moins opti par contre(enfin, je vois un moyen d'opti mais je suis pas sûr de le faire)

## fonctionnement algo génétique
- on génere l'ADN(les briques élémentaires qui seraient ici gauche droit haut bas?)
- on génere les "chromosomes" de base : un assemblement d'adn ?



- on évalue les scores(distance a vol d'oiseau entre l'endroit d'arrivée et juliette)
- on selectionne avec un aléatoire pondéré par leur score
  - Pour le crossOver, j'ai trié une liste en fonction du score +- un pourcentage
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
  - je pense tenter le coup du fait qu'on peut se déplacer de 0
  
  - problème : il ne calcule que le point d'arrivée, du coup , a partir du moment où le dernier point du chemin est a l'arrivée, le chemin devient "optimal", et touts les chemins vont se transformer et celui ci
    - J'ai donc 2 solutions pour régler ca : Soit je lance le programme, puis une fois que un chemin arrive a l'arrivée, je réduit la taille des chemins, jusqu'a convergence .Soit je commence avec un petit chemin, puis je l'agrandit a chaque fois que ca converge, jusqu'a ce qu'un point d'arrivée soit trouvé.
      - solution 1  : 
        - Je pense qu'on trouvera un chemin rapidement
        - Cependant, les 1ers calculs risquent d'être long
        - Il est possible qu'on commence avec un chemin trop court -> on ne trouvera jamais le chemin
      - Solution 2 : 
        - Une fois qu'on aura trouvé un chemin, il sera plus ou moins optimal
        - Les 1ers calculs seront rapides, et ceux a la fin seront au moins aussi rapides que la sol 1
        - La longueur de base peut être calculée automatiqueent en fonction de la taille du terrain et de la taille élémentaire
      - Sol 2 semble meilleure


## l'interface 
- je connais (et maitrise un peu) 3 trucs qui peuvent faire une interface graphique en c++, allegro, Qt, et unreal engine.
- utiliser unreal engine est probablement pas trés sage car il va falloir faire plus que juste coller un programme console dessus
- Qt permettra d'avoir facilement des boutons en compagnie mais avec allegro, dessiner la carte et les chemins sera bien plus simple
- allegro, c'est cool, mais c'est du c, donc je pense que je doit voir ailleurs, je suis pas sûr que ce soit accepté par le prof
- on va dire sfml, j'ai entendu du bien de ca

## SFML
   - il me faut je pense, une fonction sur une classe, (sur map?) chargée de transformer les coordonées du programme en coordonées de la fenetre, je verrais ca aprés
   - bah, au final, une classe faisant interface entre mon code et sfml semble pas mal. Elle aurait pourra
      - récuperer la liste des obstacles avant la boucle d'affichage pour cacher les shapes de sfml
      - prendre a chaque boucles les chemins pour les afficher
      - transformer les coordonées programme en coordonées fenetre
      - J'ai envie de l'appeller SFMLDrawer, avec drawer qui signifie dessinateur, mais aussi tiroir, parce que il y a plein de trucs dedans et je sais pas où les mettre sinon

## SFMLDrawer 
   - j'ai rencontré un problème : comment déterminer le type des éléments dans ma liste d'obstacle : 
      - utiliser des fonctions type typeof, rajouter un .getType a GeometricObject : c'est moche
      - Au lieu de maintenir 1 liste d'obstacles, maintenir 1 liste de rectangle, 1 de cercle.... : c'est moche
      - ne pas remplir la liste d'obstacle directement, mais faire appel a SFMLDrawer qui remplira sa liste de shape et fera appel a Map : c'est pas fou mais j'ai choisi ca
      - ca m'a posé un autre problème : j'avais l'intention de générer une map aléatoire grâce a la classe map, or faire ca m'empeche de le faire, c'est SFMLDrawer qui doit s'en occuper, ca me dérange mais ca reste mieux que les autres solutions, je laisse non implémenté pour l'instant
  - J'ai envie de le faire envelopper le pathManager

## Path
   - Une classe dont la seule donnée interessante sera une liste de mouvements
     - cette liste a une taille fixe (du coup c'est un tableau pas une liste)
     - le tableau est remplis de structures point qui représentent le déplacement pour chaque "gêne"
     - Ca me semble pas super opti , mais je vois pas de meilleure solution
   - ca risque de prendre pas mal d'espace mémoire, mais bon
   - je pense que c'est la map qui devrait évaluer la distance du chemin
   - la map devrait déterminer si un path est valide
   - Au final , Path n'a aucune méthode et a juste le tableau des briques, pas besoin de faire une classe. Apres un peu de recherche, je pourrais utiliser std::array, et utiliser using pour lui donner un nom.
   - Au final, le retour, si j'ai envie d'avoir une taille d'ADN modifiable dans le programme, je croit pas que je puisse utiliser a la fois un using et un std::array. Voulant conserver le std::array, je vais juste faire une classe Path qui hérite de std::array, sauf qu'on peut pas vraiment en hériter...
   - bon, bon ,bon, je vais juste utiliser un tableau pour l'instant...  pour l'instant...
   - I'm back, je fait une classe avec un tableau dedans, cette classe ne prend pas en compte la longueur de la brique elementaire, je sais pas trop pourquoi mais ca me semble mieux
## PathManager
   - une classe pour ....... manage des paths!!!!!!
   - possède la liste des path gérés
   - peut les mélanger, modifier, demander a la map si ils sont valides, s'occupe de la séléction
   - Je vais aussi lui donner la map pour qu'il vérifie si un path est valide


## pour le code
 - une classe map, avec de quoi générer la map + pt de départ et d'arrivée
 - du coup une classe d'objet géométrique
 - une classe pour gérer les chemins , qui gere aussi l'algo génétique? 
 - une classe pour afficher? -> je m'en occupe
 - je pensais au début faire que les path pouvaient aller en diagonale, mais j'ai un feeling que c'est pas une bonne idée

## L'optimisation
- plus ou moins inexistante
- Je suis conscient que je fait pas mal de choses en double, cependant cela ce fait dans différentes parties du programme, et si je voulait éviter de faire le calcul 2 fois, ca nécessiterait de les lier, ce que je ne veut pas faire
- L'exemple est le calcul du point final, qui est obtenu indirectement en dessinant le chemin, Cependant je le recalcule pour obtenir le score.
- Si je veut optimise(et j'aurais probablement la flemme), je m'en occuperait une fosi que tout fonctionnera
- Utiliser la distance au carré au lieu de la distance, je croit que calculer des racines c'est pas fou
- Le programme a tendance a se bloquer(quand il se trouve face a un truc trop mauvais), lorsqu'il fait ca je peux soit relancer la sim, soit augmenter peu a peu le taux de random

- Biaiser l'aléatoire du choix des mouvements : si l'objectif est en haut a droite, booster les chances d'aller a droite et en haut
- empecher de revenir sur ses pas -> j'ai tenté, mais je me suis rendu compte que c'était plus compliqué que ca
  - en effet, si un déplacement m'emmène dans une impasse, mon seul choix est de revenir en arrière, je doit donc détecter les impasses si je veux faire ça, je vais voir ailleurs pour l'instant
- empecher la remise des chemins


## l'écran de parametres

 - je vais opter pour une solution assez limitée, mais qui suffira
 - En fait, j'ai oublié un truc qui s'appelle les arguments de programmes, j'ai pas le temps de faire un écran de parametres donc je fait les arguments a la console