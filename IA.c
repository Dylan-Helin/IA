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

/*void destructionEnfant(Enfants e){
    free(e);
}*/

void copiePlateau(Plateau p1,Plateau p2){
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            p2[i][j]=p1[i][j];
        }
    }
}


Noeud* creerArbre(Plateau p,int tour,Plateau tabValCaseIA,Coord coup){
    Noeud* n;
    n=creationNoeud();
    Enfants* courant;
    int nbCoups;
    copiePlateau(p,n->p);
    if (coup.x!=-1){
        changerCouleur(n->p, coup.x, coup.y, tour);
        //printf("AAAAAAAAAAAAAA\n");
    }
    if(victoire(n->p)==0){//si ce n'est pas une victoire, on continue
        nbCoups=initialiserLesCoups(n->cj,n->p,tour+1);
        printf("%d %d\n",n->cj[0].x,n->cj[0].y);
        if(nbCoups==0){//pas de coup jouable, un seul fils (passer son tour)
            printf("pas de coups possible DEBUT\n");
            n->fils=creationEnfant();
            n->fils->prochainFils=NULL;
            n->fils->fils=creerArbre(n->p,tour+1,tabValCaseIA,n->cj[0]);
            n->fils->fils->precedent=n;
            //printf("pas de coups possible FIN\n");
        }else{//créer les fils avec tous les coups jouables
            printf("coups possible DEBUT\n");
            n->fils=creationEnfant();
            courant=n->fils;
            courant->fils=creerArbre(n->p,tour+1,tabValCaseIA,n->cj[0]);
            //printf("coups possible DEBUT2222222\n");
            courant->fils->precedent=n;
            for (int i = 1; i < nbCoups; i++) {
                courant->prochainFils=creationEnfant();
                courant=courant->prochainFils;
                courant->fils=creerArbre(n->p,tour+1,tabValCaseIA,n->cj[i]);
                courant->fils->precedent=n;
                //printf("coups possible MILIEU\n");
            }
            courant->prochainFils=NULL;
            //printf("coups possible FIN\n");
        }
    }else{//si c'est une fin de partie, on est a une feuille
        n->fils=NULL;
        printf("feuille\n");
    }
    printf("RETURN\n");
    return n;
}
