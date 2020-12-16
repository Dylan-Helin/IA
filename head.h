/**
GUERY Angèle
HELIN Dylan
**/

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



void initialisationPlateau (Plateau P); //initialise le plateau de jeu
void initialisationJoueur(Joueur *j1, Joueur *j2, bool b1, bool b2); //initialise les joueurs avec un etat donné (IA ou Humain) et une couleur aléatoire
void changerCouleur(Plateau p, int x, int y, int tour ); //place un pion et change les couleur des pions mangés
int placerPion(int tour, CoupsJouables tab, Plateau p); //place un pion et redemande les coordonnées tant qu'elles ne sont pas valides
void nbCouleur(Plateau p); //compte le nombre de pions de chaque couleur





void affichage (Plateau p,CoupsJouables tab); //affiche le plateau de jeu
int appartient (int x,int y, CoupsJouables tab); //renvoi 1 si les coordonnées données sont jouables 0 sinon
int initialiserLesCoups(CoupsJouables tab,Plateau p,int tour); //liste tous les coups jouables pour la couleur actuelle
int victoire(Plateau p,CoupsJouables tab, int tour); //retourne 1 si les blancs gagnent, -1 pour les noirs et 0 si la partie continue
int peutManger(Plateau p, int couleur, int x, int y); //permet de dire si a des coordonnées données un pion peut en manger d'autres
void menuChoixJoueur(bool* j1, bool* j2); //permet à l'utilisateur de choisir si les joueurs sont des IA ou des Humains
int afficherTourJoueur(int tour, Joueur j1); //affiche le tour du joueur actuel

typedef struct Noeud Noeud;
typedef struct Enfants Enfants;

struct Noeud{
    Plateau p;
    CoupsJouables cj;
    int score;
    Enfants* fils;
    struct Noeud* precedent;
};

struct Enfants{
    Noeud* fils;
    struct Enfants* prochainFils;
};



Noeud* creationNoeud(); //instancie un noeud

Enfants* creationEnfant(); //instancie un Enfant

void copiePlateau(Plateau p1,Plateau p2); //copie le plateau p1 dans p2
Noeud* creerArbre(Plateau p,int tour,Plateau tabValCaseIA,Coord coup, int profondeur); //crée l'arbre des noeud et y applique l'algorithme Min-Max
void calculScore(Noeud* n,Plateau tabValCaseIA,int tour); //calcule le score d'un noeud donnée grace au tableau des valeurs des cases
int max(Enfants* e); //récupère le score max parmi les enfants
int min(Enfants* e); //récupère le score min parmi les enfants
Coord meilleurCoup(Plateau actuel, Enfants* e, int max); //détermine le meilleur coup à jouer

#endif //IA_HEAD_H
