Contributeurs:
Alexis MARIGNE, Alexandre MENET, Adrien ROUILLON

Le projet en C consiste à traiter une image. Nous pouvons appliquer un premier filtre en noir et blanc de 8 bits ainsi qu'un filtre de couleur en 24 bits. Pour faire ce projet, nous avons utilisé l'application clion et utilisé le langage de programmation en C. Pour pouvoir utiliser et tester notre projet, vous pouvez utiliser clion. Pour installer ce dernier, vous pouvez le faire depuis un moteur de recherche. Vous pourrez ensuite dans cette application créer un nouveau projet et importer les fichiers téléchargés sur GitHub. Pour télécharger les fichiers depuis gitHub, vous pouvez télécharger le fichier zip. Une fois l'installation de tous les fichiers finis, vous pourrez lancer la simulation depuis le fichier main et essayer les différents filtres. Ensuite, laissez-vous guider! Document technique.

Développement technique :

Pour la première partie :

Création du fichier bmp8.c/h

Implementation des fonctions :

-bmp8_loadImage()
-bmp8_saveImage()
-bmp8_printInfo()
-bmp8_negative()
-bmp8_brightness()
-bmp8_threshold()
-bmp8_applyFilter()

Création du fichier bmp8.h Création du struct : t_bmp8. Cette structure définie l'image en noir et blanc.

Pour la seconde partie :

Création du fichier bmp24.c/h Création du struct : t_bmp24. Cette structure définie l'image en couleur.

Implementation des fonctions :

-bmp24_loadImage()
-bmp24_saveImage()
-bmp24_printinfo()
-bmp24_sharpen()
-bmp24_emboss()
-bmp24_outline()
-bmp24_gaussianBlur()
-bmp24_boxBlur()

Pour la troisième partie :

Création du fichier historigram.c/h

Implementation des fonctions :

-bmp8_computeHistogram()
-computeCDF()
-bmp8_equalize()
-bmp24_computeHistorigram()
-bmp24_equalize()

Bug rencontré :

Bug de commit dû à l'oublie du gitignore

Répartition des tâches :

Partie 1 : Adrien Rouillon && Alexis Maringe Partie 2 : Adrien Rouillon && Alexis Maringe Partie 3 : Adrien rouillon Menu : Alexis Maringe Readme : Adrien Rouilon && Alexis Maringe