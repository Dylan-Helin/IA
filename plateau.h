//
// Created by dydy2 on 19/11/2020.
//

#ifndef IA_PLATEAU_H
#define IA_PLATEAU_H
#include <stdio.h>

typedef int Plateau[8][8];
typedef struct{
    int x;
    int y;
}Coord;
typedef Coord CoupsJouables[64];


void affichage (Plateau p,CoupsJouables tab); //affiche le plateau de jeu
int appartient (int x,int y, CoupsJouables tab); //renvoi 1 si les coordonnées données sont jouables 0 sinon
void initialiserLesCoups(CoupsJouables tab,Plateau p,int couleur); //liste tous les coups jouables pour la couleur actuelle
int victoire (Plateau p); //retourne 1 si les blancs gagnent, -1 pour les noirs et 0 si la partie continue
#endif //IA_PLATEAU_H
