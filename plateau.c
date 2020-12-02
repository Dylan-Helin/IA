//
// Created by dydy2 on 19/11/2020.
//


#include "head.h"

void affichage (Plateau p,CoupsJouables tab){
    printf("---------------------------------\n");
    for (int i = 0;i<8;i++){
        for (int j = 0;j<8;j++){
            printf("|");
            if(p[j][i]==0){
                if(appartient(j,i,tab)==1){
                    printf(" 0 ");
                }else {
                    printf("   ");
                }
            }
            if(p[j][i]==1){
                printf(" b ");
            }
            if(p[j][i]==-1){
                printf(" n ");
            }
        }
        printf("|\n");
        printf("---------------------------------\n");
    }
}

int initialiserLesCoups(CoupsJouables tab,Plateau p,int couleur){
    for(int i = 0;i<64;i++){
        tab[i].x=-1;
        tab[i].y=-1;
    }
    int k=0;
    for (int i = 0;i<8;i++) {
        for (int j = 0; j < 8; j++) {
            if(p[j][i]==0){
                if((i>0 && p[j][i-1]==couleur*-1) || (i<7 && p[j][i+1]==couleur*-1) || (j>0 && p[j-1][i]==couleur*-1) ||
                    (j<7 && p[j+1][i]==couleur*-1) || (j<7 && i<7 && p[j+1][i+1]==couleur*-1) || (j<7 && i>0 && p[j+1][i-1]==couleur*-1)
                    || (j>0 && i<7 && p[j-1][i+1]==couleur*-1) || (j>0 && i>0 && p[j-1][i-1]==couleur*-1)){
                    tab[k].x=j;
                    tab[k].y=i;
                    k++;
                }
            }
        }
    }
    if (k>0){
        return 1;
    }else{
        return 0;
    }
}

int appartient (int x,int y, CoupsJouables tab){
    for (int i = 0;i<64;i++){
        if(tab[i].x==-1 && tab[i].y==-1){
            break;
        }
        if(tab[i].x==x && tab[i].y==y){
            return 1;
        }
    }
    return 0;
}

int victoire (Plateau p){
    int s=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(p[j][i]==0){
                return 0;
            }else{
                s=s+p[j][i];
            }
        }
    }
    if(s>0){
        return 1;
    }else{
        if (s<0){
            return -1;
        }else{
            return 2;
        }
    }
}

void initialisationPlateau (Plateau P){ //initialise le plateau pour le comme,cement d'une partie

    int i,j;
    for (i=0; i<8; i++){
        for (j=0; j<8; j++){
            P[i][j]=0;
        }
    }

    P[3][3]=1;
    P[4][3]=-1;
    P[3][4]=-1;
    P[4][4]=1;

}

void initialisationJoueur(Joueur *j1, Joueur *j2, bool b1, bool b2){
    int a;
    j1->numero = 1; //joueur 1et 2
    j2->numero = 2;

    j1->IA = b1; //IA ou non IA en fonction de ce qui a été choisit
    j2->IA = b2;

    a = rand() % 2; //couleur aléatoire 1 si blanc -1 si noir
    if(a==0){
        a=-1;
    }

    j1->couleur = a;
    j2->couleur = a*(-1);

}




int pasCoupPossible(CoupsJouables tab, Plateau p, int tour){

    if(initialiserLesCoups(tab, p, tour)==0){
        tour = tour+1;
        printf("/n Vous ne pouvez rien placer, vous passez votre tour");
    }

    return tour;
}


void changerCouleur(Plateau P, int x, int y, int tour ){
    if(tour%2==0){ //si c noir



    }
    else{ //si c'est blanc



    }
}



//finir le premier if et mettre l'en tete et celui de la fonction précedente dans head.h
int placerPion(int tour, CoupsJouables tab, Plateau p){
    int i,x,y;
    bool possible = false;

    printf("/n veuillez rentrer la coordnonnée x");
    scanf("%d", &x);
    printf("/n veuillez rentrer la coordnonnée y");
    scanf("%d", &y);

    for (i=0; i<64; i++){
        if((tab[i].x == x) && (tab[i].y == y)){
            possible = true;
        }
    }

    if(possible==true){
        //placer le pion et changer les couleurs

        return tour+1; //passe au joueur suivant
    }
    else{
        printf("/n Impossible de poser un pion ici :( ");
        tour = placerPion(tour, tab, p);
    }

}