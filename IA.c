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


Noeud* creerArbre(Plateau p,int tour,Plateau tabValCaseIA,Coord coup, int profondeur){
    //printf("nouveau Noeud tour : %d\n",tour);
    Noeud* n;
    n=creationNoeud();
    //printf("Coup a jouer : x=%d y=%d\n",coup.x+1,coup.y+1);
    //affichage (p,n->cj);
    //printf("Noeud cree\n");
    Enfants* courant;
    int nbCoups;
    //printf("avant la copie du plateau\n");
    copiePlateau(p,n->p);
    //printf("apres la copie du plateau\n");
    if (coup.x!=-1){
        //printf("avant le changement de couleur\n");
        changerCouleur(n->p, coup.x, coup.y, tour);
        //printf("apres le changement de couleur\n");
    }
    if(victoire(n->p,n->cj,tour)==0 && profondeur<4){//si ce n'est pas une victoire ou qu'on a pas atteint la profondeur max, on continue
        //printf("avant le calcul des coups\n");
        nbCoups=initialiserLesCoups(n->cj,n->p,tour+1);
        //printf("apres le calcul des coups\n");
        //printf("%d %d\n",n->cj[0].x,n->cj[0].y);
        if(nbCoups==0){//pas de coup jouable, un seul fils (passer son tour)
            //printf("pas de coups possible DEBUT\n");
            n->fils=creationEnfant();
            n->fils->prochainFils=NULL;
            n->fils->fils=creerArbre(n->p,tour+1,tabValCaseIA,n->cj[0],profondeur+1);
            n->fils->fils->precedent=n;
            n->score=n->fils->fils->score;
            //printf("pas de coups possible FIN\n");
        }else{//créer les fils avec tous les coups jouables
            //printf("coups possible DEBUT\n");
            n->fils=creationEnfant();
            courant=n->fils;
            courant->fils=creerArbre(n->p,tour+1,tabValCaseIA,n->cj[0],profondeur+1);
            //printf("coups possible DEBUT2222222\n");
            courant->fils->precedent=n;
            for (int i = 1; i < nbCoups; i++) {
                courant->prochainFils=creationEnfant();
                courant=courant->prochainFils;
                courant->fils=creerArbre(n->p,tour+1,tabValCaseIA,n->cj[i],profondeur+1);
                courant->fils->precedent=n;
                //printf("coups possible MILIEU\n");
            }
            courant->prochainFils=NULL;
            if (profondeur%2==0){
                //min
                n->score=min(n->fils);
            }else{
                //max
                n->score=max(n->fils);
            }
            //printf("coups possible FIN\n");
        }
    }else{//si c'est une fin de partie, on est a une feuille
        calculScore(n,tabValCaseIA,tour);
        n->fils=NULL;
        //printf("feuille\n");
    }
    //printf("RETURN\n");
    //printf("%d\n",n->score);
    return n;
}

void calculScore(Noeud* n,Plateau tabValCaseIA,int tour){
    int score1=0;
    int score2=0;
    int couleur;
    if (tour%2==1){
        couleur=1;
    }else{
        couleur=-1;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (n->p[i][j]==couleur){
                score1=score1+tabValCaseIA[i][j];
            }
            if (n->p[i][j]==couleur*-1){
                score2=score2+tabValCaseIA[i][j];
            }
        }
    }
    n->score=score1-score2;
}

int max(Enfants* e){
    int max=-2200;
    Enfants* courant=e;
    while (courant){
        if(max < courant->fils->score){
            max=courant->fils->score;

        }
        courant=courant->prochainFils;
    }
    return max;
}

int min(Enfants* e){
    int min=2404;
    Enfants* courant=e;
    while (courant){
        if(min > courant->fils->score){
            min=courant->fils->score;

        }
        courant=courant->prochainFils;
    }
    return min;
}

Coord meilleurCoup(Plateau actuel, Enfants* e, int max){
    Enfants* courant=e;
    Coord c;
    while (courant){
        if(max == courant->fils->score){
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (actuel[i][j]==0 && courant->fils->p[i][j]!=0){
                        c.x=i;
                        c.y=j;
                    }
                }
            }
            break;
        }
        courant=courant->prochainFils;
    }
    return c;
}