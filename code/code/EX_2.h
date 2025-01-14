#ifndef EX_2_H
#define EX_2_H
#include "EX_1.h"

//via arbre
typedef struct tas_ab{
    Cle_entier* cle;
    struct tas_ab* fg;
    struct tas_ab* fd;
    int pfd;
} Tas_Min_arbre;

//via tableau
typedef struct tas_min_tableau {
    int capacite; //case possible
    int taille;  //taille réelle
    //Ce_Cell* lcle;
    Cle_entier** tab;
} Tas_Min_tableau; 

//Q2.4
//via arbre
Tas_Min_arbre* create_tas_ab(Cle_entier* cle);
int hauteur(Tas_Min_arbre* ab);
int taille(Tas_Min_arbre* ab);
void afficherarbre(Tas_Min_arbre* tas1);
Tas_Min_arbre* ajout(Tas_Min_arbre* tas, Cle_entier* cle);
Tas_Min_arbre* ajout_iteratifs(Tas_Min_arbre* tas, Ce_Cell* cles);
Tas_Min_arbre* parent_dernier_element(Tas_Min_arbre* tas);
Tas_Min_arbre* supprMin(Tas_Min_arbre* tas);
//via tableau
Tas_Min_tableau* initial_tab_tas(int capacite);
void swap_tab(Cle_entier* a, Cle_entier* b);
int taille_lcle(Ce_Cell* lcle);
Cle_entier* getelm(Ce_Cell* lcle, int indice);
void Ajout_Tab(Tas_Min_tableau* tas, Cle_entier* cle);
void Ajout_It_tab(Tas_Min_tableau* tas, Ce_Cell* lcle); //O(n log n)
void Affiche_Tab(Tas_Min_tableau* tas);
void entasserMin(Tas_Min_tableau* tas, int indice);
Cle_entier* SupprMin(Tas_Min_tableau* tas);
void liberer_tab(Tas_Min_tableau* tas);
//Q2.5
//via arbre
Tas_Min_arbre** construction_sous_arbre(Tas_Min_arbre** tab_sous_arbre, int* nb_sous_arbre,Ce_Cell** lcle_sommets);
Tas_Min_arbre* construction(Ce_Cell* lcle);
//via tableau
Tas_Min_tableau* Construction_tab(Ce_Cell* lcle);//O(n)
void remonter(Cle_entier** tab, int indice, int taille);
//Q2.6
//via arbre
void tas_en_liste(Tas_Min_arbre* tas, Ce_Cell** lcle);
Tas_Min_arbre* unionTas(Tas_Min_arbre* Tas1, Tas_Min_arbre* Tas2);
void freeTas(Tas_Min_arbre* tas);
//via tableau
Tas_Min_tableau* Union_tab(Tas_Min_tableau* tas1, Tas_Min_tableau* tas2);//O(m+n)
Cle_entier **fusion(Cle_entier **T1, int n1, Cle_entier **T2, int n2) ;
//Q2.8
//via tableau
int longueur(int* l);
char* echanger_entier(int k,int nb);
double measureTime_it(void (*function)(Tas_Min_tableau*, Ce_Cell*), Tas_Min_tableau* tas,Ce_Cell* data);
double measureTime_cons(Tas_Min_tableau * (*function)(Ce_Cell*),Ce_Cell* data);
void Comparer_tab(int* sizes,int repetitions);
void graphe_tab();
//via arbre
double measureTime_ajout_it(Tas_Min_arbre* (*function)(Tas_Min_arbre*, Ce_Cell*), Tas_Min_arbre* tas,Ce_Cell* data);
double measureTime_cons_ab(Tas_Min_arbre * (*function)(Ce_Cell*),Ce_Cell* data);
void Comparer_arbre(int* sizes,int repetitions);
void graphe_arbre();
//Q2.8
//via tableau
double measureTime_union(Tas_Min_tableau * (*function)(Tas_Min_tableau *, Tas_Min_tableau * ),Tas_Min_tableau * tas1, Tas_Min_tableau * tas2);
void verf_tab_union(int *sizes,  int *lnb, int repetitions);
void graphe_tab_un();
//via arbre
double measureTime_union_ab(Tas_Min_arbre * (*function)(Tas_Min_arbre*, Tas_Min_arbre*),Tas_Min_arbre* tas1, Tas_Min_arbre* tas2);
void verf_arbre_union(int *sizes, int *lnb, int repetitions);
void graphe_union_arbre();
#endif