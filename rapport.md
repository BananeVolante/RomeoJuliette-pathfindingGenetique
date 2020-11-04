Geometrics forms : initially intended to work only with geometric forms and to consider the path as an ensemble of segments, however, checking if 2 segments/1 segment and a circle ... collide is hard, so i suppose that the path is composed of points for now

a propos de la fonction SQUARE : je suis conscient que la fonction pow existe, et aprés un peu de recherche il semblerait que sur certaines implémentations, elles fonctionne différemment pour des puissances communes, comme 2 et -1, je pourrait donc l'utiliser sans que cela coûte bien plus que ma macro, cependant, je ne suis pas certain que ce soit le cas pour toutes les implémentations, donc je ne l'ai pas fait

La classe Map et le fait que addForm est privé : 
    - J'ai voulu que ce soit la classe map qui soit responsable de la destruction des objets, afin de ne pas oublier
        Il m'a donc parru évident de la rendre du coup responsable de la création de ces mêmes objets, et j'ai donc empeché l'utilisateur de fournir ses propres objets afin qu'il n'y ait pas de comportement étrange