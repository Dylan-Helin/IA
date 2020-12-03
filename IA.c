/**
GUERY Angèle
HELIN Dylan
**/

#include "head.h"

Enfants* creationEnfant(){
    Enfants* e;
    e=(Enfants*) malloc(sizeof(Enfants) );
    return e;
}

void destructionEnfant(Enfants e){
    free(e);
}