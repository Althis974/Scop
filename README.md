# Scop

## Sujet


### I.    Il n’y a pas de mal à se faire du bien

De temps en temps, il n’est pas pour déplaire de flâter son ego. Nous allons donc
réaliser une petite application pour se brosser dans le sens du poil.

C’est l’occasion d’attaquer tout doucement un peu d’OpenGL. Ce projet est organisé
pour vous faire mettre les mains dans le cambouis. Il y a donc quelques restrictions dans
ce but.


### II.   Ce qu’il faut réaliser

Votre objectif est de réaliser un petit programme qui affiche un objet 3D conçu au
moyen d’un logiciel de modélisation, comme Blender par exemple. L’objet 3D est stocké
dans un fichier au format .obj . Vous devrez vous charger du parsing à minima pour
obtenir le rendu demandé.

Dans une fenêtre, votre objet 3D doit s’afficher, en perspective (c’est à dire que ce qui
est loin doit être plus petit), en tournant sur lui-même autour de ce qui semble être son
axe de symétrie principal (en gros, le milieu de l’objet quoi...). Par un jeu de couleur, il
doit être possible de distinguer les différentes facettes. L’objet peut être déplacé sur les
trois axes, dans les deux directions.

Enfin, une texture doit pouvoir être appliquée basiquement sur l’objet lorsqu’on appuye sur une touche dédiée, et la même touche permet de revenir à l’affichage des couleurs.
Une transition douce est demandée entre les deux.


Les contraintes techniques sont les suivantes :

- Coder sur les dumps à la norme, en C : l’API première OpenGL est en C, frottezvous y. Certaines surcouches de certains langages font plein de choses automatiquement, ça serait trop facile.

- Avoir un Makefile normal (tout ce que vous avez l’habitude d’y mettre)

- Utiliser de l’OpenGL MODERNE : en version 4.0 minimum, avec des shaders
obligatoirement.

- N’utiliser des librairies externes (autre qu’OpenGL, libm et la lib C) QUE pour
la gestion de la fenêtre et des évènements. Vous avez le droit d’utiliser votre libft.
Dans le doute, utilisez la MinilibX avec son extension OpenGL. Pas de librairie
pour loader l’objet 3D, ni pour vous faire les matrices, ou charger les shaders.


Comme il s’agit d’un programme d’auto-congratulation, il est indispensable que vous
puissiez présenter en soutenance au moins le logo de 42 fourni avec ce sujet, tournant autour de son axe central (attention, pas autour de l’un des bords), avec des niveaux de gris
comme couleurs pour les facettes, et une texture de poneys, licornes ou chatons, au choix.

Lors de la soutenance, d’autres objets 3D seront bien sûr testés.

## How to

```
make
```

```
./scop <.obj file>
```

## Fonctionnalités

 <table>
   <tr>
       <td>Q (A) / D</td>
       <td>Déplacer caméra sur l'axe X</td>
   </tr>
   <tr>
       <td>Z (W) / S</td>
       <td>Déplacer caméra sur l'axe Y</td>
   </tr>
   <tr>
       <td>A (Q) / E</td>
       <td>Déplacer caméra sur l'axe Z</td>
   </tr>
   <tr>
       <td>J / L</td>
       <td>Déplacer modèle sur l'axe X</td>
   </tr>
   <tr>
       <td>I / K</td>
       <td>Déplacer modèle sur l'axe Y</td>
   </tr>
   <tr>
       <td>U / O</td>
       <td>Déplacer modèle sur l'axe Z</td>
   </tr>
   <tr>
       <td>T</td>
       <td>Appliquer les textures</td>
   </tr>
     <tr>
       <td>C</td>
       <td>Changer de couleur</td>
   </tr>
   <tr>
       <td>N</td>
       <td>Modifier interpolation</td>
   </tr>
   <tr>
       <td>ESC</td>
       <td>Quitter le programme</td>
   </tr>
</table>

## Exemples

### 42 Kittens
![img](https://i.imgur.com/ssperNS.png)

### Teapot
![img](https://i.imgur.com/hvOyfxD.png)

### Charizard Fire
![img](https://i.imgur.com/zFVbisM.png)

### NightFury with interpolation
![img](https://i.imgur.com/SGMtYry.png)

### Crash in color with interpolation
![img](https://i.imgur.com/7njXXXk.png)

### Gun Water
![img](https://i.imgur.com/GHx5vLv.png)
