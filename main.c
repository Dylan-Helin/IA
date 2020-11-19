/**
GUERY Angèle
HELIN Dylan
**/

#include "head.h"


int main() {
    Plateau p;
    for (int i=0;i<8;i++){
        for (int j = 0;j<8;j++){
            p[i][j]=0;
        }
    }
    affichage(p);
}
