/**
GUERY Angèle
HELIN Dylan
**/

#include "head.h"

/**
 * affiche le plateau de jeu avec les pions placés et les coups possibles
 * @param p : le plateau de jeu
 * @param tab : le tableau des coups possibles
 */
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

/**
 * liste tous les coups jouables pour la couleur actuelle
 * @param tab : le tableau des coups jouables
 * @param p : le plateau de jeu
 * @param tour : le tour actuel
 * @return le nombre de coups jouables
 */
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
    return k;//retourne le nombre de coups jouables
}

/**
 * permet de dire si un coup appartient au tableau de coups jouables
 * @param x : la coordonnée x du coup
 * @param y : la coordonnée y du coup
 * @param tab : le tableau des coups jouables
 * @return 1 si le coup est jouable, 0 sinon
 */
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

/**
 * test si nous sommes dans une situation de victoire, d'égalité ou non
 * @param p : le plateau de jeu
 * @param tab : le tableau de coups jouables
 * @param tour : le tour actuel
 * @return 1 si les blancs gagnent, -1 si les noirs gagnent, 2 si il y a égalité et 0 si la partie continue
 */
int victoire(Plateau p,CoupsJouables tab, int tour){
    bool caseVide = false; //il reste des case vide ?
    bool bloque = false; //les deux joueurs ne peuvent plus jouer ?
    if(initialiserLesCoups(tab, p, tour)==0 && initialiserLesCoups(tab, p, tour+1)==0){
        bloque = true;
    }
    int s=0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if(p[j][i]==0 && caseVide == false){
                caseVide = true; //il y a encore des cases vides
            }
            if(p[j][i]!=0){
                s=s+p[j][i];
            }

        }
    }

    if (caseVide==true && bloque==false){
        return 0; //la partie continue
    }
    else{
        if(s>0){
            return 1; //blancs gagnent
        }
        else{
            if (s<0){
                return -1; //noir gagne
            }
            else{
                return 2; //egalité
            }
        }

    }

}

/**
 * initialise le plateau pour le commencement d'une partie
 * @param P : le plateau de jeu
 */
void initialisationPlateau (Plateau P){

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

/**
 * initialise les joueurs avec des valeurs données (IA ou non) et une couleur aléatoire
 * @param j1 : le joueur 1
 * @param j2 : le joueur 2
 * @param b1 : le booléen pour savoir si le joueur 1 est une IA (true) ou non (false)
 * @param b2 : le booléen pour savoir si le joueur 2 est une IA (true) ou non (false)
 */
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



/**
 * place le pion et change les couleurs
 * @param p : le plateau de jeu
 * @param x : la coordonnée x du coup joué
 * @param y : la coordonnée y du coup joué
 * @param tour : le tour actuel
 */
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



/**
 * permet de placer un pion si c'est possible d'en placer un, l'utilisateur va entrer des coordonnées jusqu'a ce qu'elles soit valides
 * @param tour : le tour actuel
 * @param tab : le tableau des coups possibles
 * @param p : le plateau de jeu
 * @return tour+1
 */
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

/**
 * test si a des coordonnées données il est possible de placer un pion
 * @param p : le plateau de jeu
 * @param couleur : la couleur du joueur actuel
 * @param x : la coordonnée x du pion à placer
 * @param y : la coordonnée y du pion à placer
 * @return 1 si le pion peut être placé et 0 sinon
 */
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

/**
 * laisse le choix à l'utilisateur de l'état des joueurs (IA ou Humain)
 * @param j1 : le joueur 1
 * @param j2 : le joueur 2
 */
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

/**
 * affiche le tour du joueur actuel
 * @param tour : le tour actuel
 * @param j1 : le joueur 1
 * @return 1 si il s'agit du tour du joueur 1 et 2 sinon
 */
int afficherTourJoueur(int tour, Joueur j1){
    int joueurActuel=0;
    if (tour%2==0){//tour des noirs
        if (j1.couleur==-1){
            printf("Tour du joueur 1\n");
            joueurActuel=1;
        }else{
            printf("Tour du joueur 2\n");
            joueurActuel=2;
        }
    }else{//tour des blancs
        if (j1.couleur==1){
            printf("Tour du joueur 1\n");
            joueurActuel=1;
        }else{
            printf("Tour du joueur 2\n");
            joueurActuel=2;
        }
    }
    return joueurActuel;
}

/**
 * compte le nombre de pions de chaque couleur sur le plateau
 * @param p : le plateau de jeu
 */
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
    printf("\nNombre de pion noir : %d \nNombre de pion blanc : %d \n", noir, blanc);
}
