#ifndef EX_6_H
#define EX_6_H
#include "EX_1.h"
#include "EX_2.h"
#include "EX_3.h"
#include "EX_4.h"
#include "EX_5.h"
#include <dirent.h>

typedef struct words{
    char* data;
    struct words* suiv;  
}Words;

//struct dirent *dir;

Words* create_list_word(char* cle);
Words* insert_word_in_List(char* cle, Words* lcle);
Words* insertWordsNotExist(char* cle, Words* lcle);
void print_List_Word(Words* lw);
void free_List_word(Words* lw) ;
Words* read_Files_Shakespeare(char* nomDossier);
Ce_Cell* word_en_Cell(Words* words);
AB_Rech* construction_ABR(Ce_Cell* lcle);
void affichage_words(Words* words);
void affichage_CE_CELL(Ce_Cell* lcle);
int hasDuplicate(Ce_Cell* lce) ;

double measureTime_suppr_min_fb(TB_Cell * (*function)(TB_Cell *),TB_Cell * fb);
double measureTime_suppr_min_tab(Cle_entier* (*function)(Tas_Min_tableau*), Tas_Min_tableau* tas);
double measureTime_suppr_min_tm(Tas_Min_arbre* (*function)(Tas_Min_arbre *),Tas_Min_arbre * tas);
void comparer_temps_suppr_cons();
void graphe_temps_suppr_cons();

double measureTime_ajout_fb(TB_Cell * (*function)(Cle_entier*, TB_Cell *),Cle_entier* cle, TB_Cell * fb);
double measureTime_ajout_tm_abr(Tas_Min_arbre * (*function)(Tas_Min_arbre*, Cle_entier*),Tas_Min_arbre* tas, Cle_entier* cle);
double measureTime_ajout_tm_tab(void (*function)(Tas_Min_tableau*,Cle_entier*), Tas_Min_tableau* tas, Cle_entier* cle);
void comparer_temps_ajout(Ce_Cell* cles);
void graphe_temps_ajout();

void verf_union();
void graphe_union();

#endif