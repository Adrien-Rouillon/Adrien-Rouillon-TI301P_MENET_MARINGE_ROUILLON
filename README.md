# Projet : Analyse de Graphes de Markov
## Contributeurs: Alexis MARINGE, Alexandre MENET, Adrien ROUILLON

Le projet en C consiste à traiter et analyser des chaînes de Markov. Nous pouvons charger des graphes, vérifier leurs probabilités, les visualiser via le site Mermaid, et analyser leurs connexions grâce à Tarjan, ainsi que leurs matrices de transition.

## Execution du projet
Pour executer le projet, vous dever dans le main appeler une des fonctions qui est au dessus.

## Document technique

### Partie 1 : Gestion des graphes et Utils

Différentes fonctions utilisées :
* **readGraph()** : lecture d'un fichier .txt pour créer une liste d'adjascence
* **display_adj_list()** : affichage du graphe dans la console
* **is_markov_graph()** : vérification de la propriété de Markov (somme des probabilités = 1)
* **createDiagram()** : préparation de la structure pour l'export
* **writeDiagram()** : génération du fichier pour la visualisation sur Mermaid

### Partie 2 : Algorithme de Tarjan et diagramme de Hasse

Implémentation des fonctions Tarjan :
* **listAdj_to_TarjanVtx()** : convertir la liste d'adjacence classique en un tableau de structure **t_tarjanVtx**
* **tarjan_parkour()** : effectue un parcours, met à jours les numéros accessibles pour identifier les cycles, crée une nouvelle classe lorsqu'une racine de composante est identifiée
* **tarjan()** : initialise les structures et lance **tarjan_parkour** sur tous les sommets non visités pour garantir que tout le graphe est traité
* **print_partition()** : affiche le résultat final sous forme de liste de composantes

Implémentation des fonctions Hasse :
* **find_class_vertex** : recherche l'index de la classe à laquelle appartient un sommet donné
* **create_diagram_hasse** : construit le graphe réduit en reliant les classes entre elles si une arête existe entre leurs sommets respectifs
* **removeTransitiveLinks()** : supprime les liens redondants
* **print_diagram_hasse()** : affiche dans la console les classes et la liste finale des liens simplifiés
* **add_link()** : gestion dynamique du tableau de liens
* **existing_link()** : gestion dynamique du tableau de liens

### Partie 3 : Calculs matriciels

* **create_matrix()** : fonction d'allocation dynamique de mémoire pour les matrices 2D
* **create_empty_matrix** :  fonction d'allocation dynamique de mémoire pour les matrices 2D
* **adj_list_to_matrix()** : transforme la liste d'adjacence en une matrice de transition
* **multiply_matrix()** : effectue le produit de deux matrices carrées, utilisée pour calculer les puissances de la matrice de transition
* **diff_matrix()** : calcule de la comme des différences absolues entre deux matrices, sert de critère d'arrêt pour déterminer si la distribution de probabilité a convergé vers un état stable
* **subMatrix()** : extrait une sous-matrice carrée correspondant aux sommets d'une classe donnée, permet d'analyser les propriétés d'une composante isolée du reste du graphe
