//
// Created by dydy2 on 19/11/2020.
//


#include "head.h"

void affichage (Plateau p,CoupsJouables tab){
    printf("    1   2   3   4   5   6   7   8  \n");
    printf("  ---------------------------------\n");
    for (int i = 0;i<8;i++){
        printf("%d ",i+1);
        for (int j = 0;j<8;j++){
            printf("|");
            if(p[j][i]==0){
                if(appartient(j,i,tab)==1){
                    printf(" * ");
                }else {
                    printf("   ");
                }
            }
            if(p[j][i]==1){
                printf(" B ");
            }
            if(p[j][i]==-1){
                printf(" N ");
            }
        }
        printf("|");
        printf(" %d\n",i+1);
        printf("  ---------------------------------\n");
    }
    printf("    1   2   3   4   5   6   7   8  \n");
}

//liste tous les coups jouables pour la couleur actuelle
int initialiserLesCoups(CoupsJouables tab,Plateau p,int tour){
    int couleur;
    if (tour%2==0){
        couleur=-1; //si c'est un tour pair alors c'est le tour des noirs
    }else{
        couleur=1;  //si c'est un tour impair alors c'est le tour des blancs
    }
    for(int i = 0;i<64;i++){    //initialise le tableau des coups a des valeurs impossibles
        tab[i].x=-1;
        tab[i].y=-1;
    }
    int k=0;
    //vérifie toutes les positions du plateau pour savoir si on peut poser un pion dans toutes les directions
    for (int i = 0;i<8;i++) {
        for (int j = 0; j < 8; j++) {
            if(p[j][i]==0){
                if((i>0 && p[j][i-1]==couleur*-1) || (i<7 && p[j][i+1]==couleur*-1) || (j>0 && p[j-1][i]==couleur*-1) ||
                    (j<7 && p[j+1][i]==couleur*-1) || (j<7 && i<7 && p[j+1][i+1]==couleur*-1) || (j<7 && i>0 && p[j+1][i-1]==couleur*-1)
                    || (j>0 && i<7 && p[j-1][i+1]==couleur*-1) || (j>0 && i>0 && p[j-1][i-1]==couleur*-1)){
                     if (peutManger(p,couleur, j, i)){
                         tab[k].x=j;
                         tab[k].y=i;
                         k++;
                     }

                }
            }
        }
    }
    if (k>0){
        return 1; //retourne 1 si il y a des coups possible
    }else{
        return 0; //retourne 0 si aucun coup n'est possible
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

int victoire(Plateau p){
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



//place le pion et change les couleurs
void changerCouleur(Plateau p, int x, int y, int tour ){
    int couleur; //-1 noir et 1 blanc
    bool manger=false; //si il peut manger ou non
    int i=1;

    if(tour%2==0){ //si c noir
        couleur = -1;
    }
    else{ //si c'est blanc
        couleur = 1;
    }

    p[x][y]=couleur; //on pose le pion

    //test a droite
    while (p[x+i][y]==couleur*-1 && x+i+1<8){
        i++;
    }
    if (x+i<8 && i!=1){
        if (p[x+i][y]==couleur){
            manger=true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x+i][y]==couleur*-1){
            p[x+i][y] = couleur;
            i++;
        }
    }
    manger = false;

    //test a gauche
    i=1;
    while (p[x-i][y]==couleur*-1 && x-i-1>=0){
        i++;
    }
    if (x-i>=0 && i!=1){
        if (p[x-i][y]==couleur){
            manger=true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x-i][y]==couleur*-1){
            p[x-i][y] = couleur;
            i++;
        }
    }
    manger = false;

    //test en haut
    i=1;
    while (p[x][y-i]==couleur*-1 && y-i-1>=0){
        i++;
    }
    if (y-i>=0 && i!=1){
        if (p[x][y-i]==couleur){
            manger = true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x][y-i]==couleur*-1){
            p[x][y-i] = couleur;
            i++;
        }
    }
    manger = false;

    //test en bas
    i=1;
    while (p[x][y+i]==couleur*-1 && y+i+1<8){
        i++;
    }
    if (y+i<8 && i!=1){
        if (p[x][y+i]==couleur){
            manger = true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x][y+i]==couleur*-1){
            p[x][y+i] = couleur;
            i++;
        }
    }
    manger = false;

    //test droite/bas
    i=1;
    while (p[x+i][y+i]==couleur*-1 && y+i+1<8 && x+i+1<8){
        i++;
    }
    if (y+i<8 && x+i<8 && i!=1){
        if (p[x+i][y+i]==couleur){
           manger = true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x+i][y+i]==couleur*-1){
            p[x+i][y+i] = couleur;
            i++;
        }
    }
    manger = false;

    //test gauche/bas
    i=1;
    while (p[x-i][y+i]==couleur*-1 && y+i+1<8 && x-i-1>=0){
        i++;
    }
    if (y+i<8 && x-i>=0 && i!=1){
        if (p[x-i][y+i]==couleur){
            manger = true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x-i][y+i]==couleur*-1){
            p[x-i][y+i] = couleur;
            i++;
        }
    }
    manger = false;

    //test gauche/haut
    i=1;
    while (p[x-i][y-i]==couleur*-1 && y-i-1>=0 && x-i-1>=0){
        i++;
    }
    if (y-i>=0 && x-i>=0 && i!=1){
        if (p[x-i][y-i]==couleur){
            manger = true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x-i][y-i]==couleur*-1){
            p[x-i][y-i] = couleur;
            i++;
        }
    }
    manger = false;

    //test droite/haut
    i=1;
    while (p[x+i][y-i]==couleur*-1 && y-i-1>=0 && x+i+1<8){
        i++;
    }
    if (y-i>=0 && x+i<8 && i!=1){
        if (p[x+i][y-i]==couleur){
            manger = true;
        }
    }
    if(manger == true){
        i=1;
        while (p[x+i][y-i]==couleur*-1){
            p[x+i][y-i] = couleur;
            i++;
        }
    }


}



//permet de placer un pion si c'est possible d'en placer un, l'utilisateur va entrer des coordonnées jusqu'a ce qu'elles soit valide
int placerPion(int tour, CoupsJouables tab, Plateau p){
    int i,x,y;
    bool possible = false;

    printf("\n veuillez rentrer la coordnonnee x\n");
    scanf("%d", &x);
    printf("\n veuillez rentrer la coordnonnee y\n");
    scanf("%d", &y);
    x=x-1;
    y=y-1;
    for (i=0; i<64; i++){
        if((tab[i].x == x) && (tab[i].y == y)){
            possible = true;
        }
    }

    if(possible==true){
        //place le pion et change les couleurs
        changerCouleur(p, x, y, tour);

        return tour+1; //passe au joueur suivant
    }
    else{
        printf("\n Impossible de poser un pion ici :( \n");
        tour = placerPion(tour, tab, p);
    }

}

int peutManger(Plateau p, int couleur, int x, int y){
    int peutManger=0;
    int i=1;
    //test a droite
    while (p[x+i][y]==couleur*-1 && x+i+1<8){
        i++;
    }
    if (x+i<8 && i!=1){
        if (p[x+i][y]==couleur){
            peutManger=1;
        }
    }
    //test a gauche
    i=1;
    while (p[x-i][y]==couleur*-1 && x-i-1>=0){
        i++;
    }
    if (x-i>=0 && i!=1){
        if (p[x-i][y]==couleur){
            peutManger=1;
        }
    }
    //test en haut
    i=1;
    while (p[x][y-i]==couleur*-1 && y-i-1>=0){
        i++;
    }
    if (y-i>=0 && i!=1){
        if (p[x][y-i]==couleur){
            peutManger=1;
        }
    }
    //test en bas
    i=1;
    while (p[x][y+i]==couleur*-1 && y+i+1<8){
        i++;
    }
    if (y+i<8 && i!=1){
        if (p[x][y+i]==couleur){
            peutManger=1;
        }
    }
    //test droite/bas
    i=1;
    while (p[x+i][y+i]==couleur*-1 && y+i+1<8 && x+i+1<8){
        i++;
    }
    if (y+i<8 && x+i<8 && i!=1){
        if (p[x+i][y+i]==couleur){
            peutManger=1;
        }
    }
    //test gauche/bas
    i=1;
    while (p[x-i][y+i]==couleur*-1 && y+i+1<8 && x-i-1>=0){
        i++;
    }
    if (y+i<8 && x-i>=0 && i!=1){
        if (p[x-i][y+i]==couleur){
            peutManger=1;
        }
    }
    //test gauche/haut
    i=1;
    while (p[x-i][y-i]==couleur*-1 && y-i-1>=0 && x-i-1>=0){
        i++;
    }
    if (y-i>=0 && x-i>=0 && i!=1){
        if (p[x-i][y-i]==couleur){
            peutManger=1;
        }
    }
    //test droite/haut
    i=1;
    while (p[x+i][y-i]==couleur*-1 && y-i-1>=0 && x+i+1<8){
        i++;
    }
    if (y-i>=0 && x+i<8 && i!=1){
        if (p[x+i][y-i]==couleur){
            peutManger=1;
        }
    }
    return peutManger;
}

void menuChoixJoueur(bool* j1, bool* j2){
    int a=0;
    while (a!=1 && a!=2){
        printf("Le joueur 1 est il un humain ou une IA ?\n1 : humain\n2 : IA\n");
        scanf("%d",&a);
    }
    if (a==1){
        *j1=false;
    }else{
        *j1=true;
    }
    a=0;
    while (a!=1 && a!=2){
        printf("Le joueur 2 est il un humain ou une IA ?\n1 : humain\n2 : IA\n");
        scanf("%d",&a);
    }
    if (a==1){
        *j2=false;
    }else{
        *j2=true;
    }

}

void afficherTourJoueur(int tour, Joueur j1){
    if (tour%2==0){//tour des noirs
        if (j1.couleur==-1){
            printf("Tour du joueur 1\n");
        }else{
            printf("Tour du joueur 2\n");
        }
    }else{//tour des blancs
        if (j1.couleur==1){
            printf("Tour du joueur 1\n");
        }else{
            printf("Tour du joueur 2\n");
        }
    }
}

void nbCouleur(Plateau p){
    int i,j;
    int noir=0;
    int blanc=0;
    for(i=0; i<8; i++){
        for(j=0; j<8; j++){
            if(p[i][j]==-1){
                noir++;
            }
            else{
                blanc++;
            }
        }
    }
    printf("\n Nombre de pion noir : %d \n Nombre de pion blanc : %d \n", noir, blanc);
}
