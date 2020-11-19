//
// Created by aguer on 05/11/2020.
//

#ifndef IA_HEAD_H
#define IA_HEAD_H

#include <stdbool.h>

typedef struct Joueur {
    int numero; //joueur 1 ou 2
    int couleur; //1 pour blanc, 2 pour noir (aléatoire en début de partie)
    bool IA; //true si c'est une IA (le jueur choisit ça dans les options ou en début de jeux)

};






#endif //IA_HEAD_H


