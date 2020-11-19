//
// Created by aguer on 05/11/2020.
//

#ifndef IA_HEAD_H
#define IA_HEAD_H

#include <stdbool.h>
#include <stdio.h>
#include "plateau.h"

typedef struct {
    int numero; //joueur 1 ou 2
    int couleur; //1 pour blanc, 2 pour noir (aléatoire en début de partie)
    bool IA; //true si c'est une IA (le jueur choisit ça dans les options ou en début de jeux)

}Joueur;


int tabValCaseIA[8][8]={
        {500, -150,30,10,10,30,-150,500},
        {-150,-250,0,0,0,0,-250,-150},
        {30,0,1,2,2,1,0,30},
        {10,0,2,16,16,2,0,10},
        {10,0,2,16,16,2,0,10},
        {30,0,1,2,2,1,0,30},
        {-150,-250,0,0,0,0,-250,-150},
        {500, -150,30,10,10,30,-150,500}
};


void initialisationPlateau (Plateau P);
void couleurAlea();



#endif //IA_HEAD_H
