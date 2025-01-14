#ifndef EX_3_H
#define EX_3_H
#include "EX_2.h"

typedef struct tournoisB{
    Cle_entier* cle; // Valeur stockée dans le nœud
    int degre;
    struct tournoisB* enfant; // Pointeur vers le premier enfant, un tableau
} TournoisB;


//File Binomiale
typedef struct tb_cell{
    TournoisB* tb;
    struct tb_cell* suiv;
}TB_Cell;

TournoisB* create_tournoisB(Cle_entier* cle);
bool estVideTournoisB(TournoisB* t);
int degreTournoisB(TournoisB* t);
void afficher_tournoisB(TournoisB* tb);
TournoisB *mergeFB_meme_degre(TournoisB *tree1, TournoisB *tree2);
TB_Cell* Decapite_TB (TournoisB* tb);
TB_Cell* InsererEnTete(TournoisB* tb, TB_Cell* tete);
bool estVideFilB(TB_Cell* fb);
void afficherFileB(TB_Cell* fb);
TB_Cell* insert_in_FB(TournoisB* tb, TB_Cell* fb);
TB_Cell* create_FileB(TournoisB* tb);
TournoisB* degreMin_FilB(TB_Cell* fb);
void Reste_FilB(TB_Cell** f);
void AjoutMin_FB (TournoisB* tb, TB_Cell** fb);
void Trie(TB_Cell** fb);

TB_Cell* Union_FilB(TB_Cell* fb1, TB_Cell* fb2);
TB_Cell* UFret(TB_Cell* fb1, TB_Cell* fb2, TournoisB* tb);
TB_Cell* ajout_cle_FB(Cle_entier* cle, TB_Cell* fb);
TB_Cell* construction_FB(Ce_Cell* lcle);
TournoisB* findMinTB(TB_Cell* fb) ;
void supp_TB_in_FB(TB_Cell** fb);
TB_Cell* SupprMin_FilB(TB_Cell* fb);

double measureTime_cons_FB(TB_Cell* (*function)(Ce_Cell*),Ce_Cell* data);
void Comparer_FB_Cons(int* sizes,int repetitions);
void graphe_FB_Cons();

double measureTime_union_FB(TB_Cell * (*function)(TB_Cell *, TB_Cell * ),TB_Cell * fb1, TB_Cell * fb2);
void verf_FB_union(int *sizes, int *lnb, int repetitions);
void graphe_FB_un();
#endif