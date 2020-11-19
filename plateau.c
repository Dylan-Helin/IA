//
// Created by dydy2 on 19/11/2020.
//

#include "plateau.h"

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

void initialiserLesCoups(CoupsJouables tab,Plateau p,int couleur){
    for(int i = 0;i<64;i++){
        tab[i].x=-1;
        tab[i].y=-1;
    }
    int k=0;
    for (int i = 0;i<8;i++) {
        for (int j = 0; j < 8; j++) {
            if(p[j][i]==0){
                if((i>0 && p[j][i-1]==couleur*-1) || (i<7 && p[j][i+1]==couleur*-1) || (j>0 && p[j-1][i]==couleur*-1) || (j<7 && p[+1][i]==couleur*-1)){
                    tab[k].x=j;
                    tab[k].y=i;
                }
            }
        }
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