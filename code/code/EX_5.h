#ifndef EX_5_H
#define EX_5_H
#include "EX_2.h"

typedef struct ab_rech{
    Cle_entier* cle;
    struct ab_rech* fils_g;
    struct ab_rech* fils_d;
    struct ab_rech* parent;
}AB_Rech;

AB_Rech* arbre_vide();
AB_Rech* arbre_binaire(Cle_entier* e, AB_Rech* g, AB_Rech* d);
bool est_arbre_vide(AB_Rech* ab);
Cle_entier* racine(AB_Rech* ab);
AB_Rech* sous_arbre_gauche(AB_Rech* ab);
AB_Rech* sous_arbre_droit(AB_Rech* ab);
AB_Rech* parent(AB_Rech* ab);
bool exists(AB_Rech* ab, Cle_entier* cle);
AB_Rech* ajout_AB_Rech(AB_Rech* ab,Cle_entier* cle);
AB_Rech* ajout_it_AB_Rech(AB_Rech* ab,Ce_Cell* lcle);
void afficher_ab_rech(AB_Rech* ab,int pfd);
Cle_entier* cle_aleatoire(Ce_Cell* cles);
void verif_exist_abr_rech(int* sizes,int repetitions);
double measureTime_exists(bool (*function)(AB_Rech*,Cle_entier*),AB_Rech* abr,Cle_entier* cle);
void graphe_exists_abr();
#endif

