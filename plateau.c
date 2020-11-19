//
// Created by dydy2 on 19/11/2020.
//

#include <stdlib.h>
#include "head.h"
#include "time.h"

void affichage (Plateau p){
    printf("---------------------------------\n");
    for (int i = 0;i<8;i++){
        for (int j = 0;j<8;j++){
            printf("|");
            if(p[j][i]==0){
                printf("   ");
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


void initialisationPlateau (Plateau P){ //initialise le plateau pour le comme,cement d'une partie

    P[4][4]=1;
    P[5][4]=-1;
    P[4][5]=-1;
    P[5][5]=1;

}

void couleurAlea(){
    int a;
    srand (time (NULL));
    a = rand() % 2;
    if(a==0){
        a=-1;
    }
    printf("%d", a);

}



