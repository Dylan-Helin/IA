//
// Created by aguer on 05/11/2020.
//

#ifndef IA_HEAD_H
#define IA_HEAD_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "time.h"


typedef struct {
    int numero; //joueur 1 ou 2
    int couleur; //1 pour blanc, -1 pour noir (aléatoire en début de partie)
    bool IA; //true si c'est une IA (le joueur choisit ça dans les options ou en début de jeux)
}Joueur;

typedef int Plateau[8][8];

typedef struct{
    int x;
    int y;
}Coord;
typedef Coord CoupsJouables[64];

typedef struct Enfants{
    Noeud fils;
    struct Enfants* prochainFils;
} Enfants;


void initialisationPlateau (Plateau P);
void initialisationJoueur(Joueur *j1, Joueur *j2, bool b1, bool b2);
void changerCouleur(Plateau p, int x, int y, int tour );
int placerPion(int tour, CoupsJouables tab, Plateau p);
void nbCouleur(Plateau p);





void affichage (Plateau p,CoupsJouables tab); //affiche le plateau de jeu
int appartient (int x,int y, CoupsJouables tab); //renvoi 1 si les coordonnées données sont jouables 0 sinon
int initialiserLesCoups(CoupsJouables tab,Plateau p,int tour); //liste tous les coups jouables pour la couleur actuelle
int victoire(Plateau p); //retourne 1 si les blancs gagnent, -1 pour les noirs et 0 si la partie continue
int peutManger(Plateau p, int couleur, int x, int y);
void menuChoixJoueur(bool* j1, bool* j2);
void afficherTourJoueur(int tour, Joueur j1);


#endif //IA_HEAD_H
