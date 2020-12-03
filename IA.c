/**
GUERY Angèle
HELIN Dylan
**/

#include "head.h"

Noeud* creationNoeud(){
    Noeud* n;
    n=(Noeud*)malloc(sizeof(Noeud));
    return n;
}

/*void detruireNoeud(Noeud n){
    free(n);
}*/

Enfants* creationEnfant(){
    Enfants* e;
    e=(Enfants*) malloc(sizeof(Enfants) );
    return e;
}

void destructionEnfant(Enfants e){
    free(e);
}

Noeud creerArbre(Plateau p,int tour){
    Noeud n;

    return n;
}
