# c-filesystem-tp

## Réalisation

TP réalisé sur une journée + soutenance à son terme

## Enoncé

Écrire un programme qui prend en paramètre un chemin de fichier et qui ira lire son contenu,
et qui pour chaque ligne présent dans ce contenu créera un nouveau fichier pour y écrire
cette ligne.

Les nouveaux fichiers devront être créés à l’exécution du programme, et devront être
nommés par ordre numérique: 1.txt, 2.txt etc.

Si le fichier source est vide (aucun caractère), n’existe pas ou n’est pas lisible, un fichier
0.txt sera créé avec comme contenu “J’ai tout compris au C.”

Les seuls fonctions externes autorisés sont: open, close, read, write, malloc, realloc, free, stat et la librairie math.

> Ajout personnel de la librairie ***stdarg*** pour la création de fonctions variadiques.
