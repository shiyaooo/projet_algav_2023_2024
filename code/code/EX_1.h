#ifndef EX_1_H 
#define EX_1_H 
#include <stdint.h>
typedef struct cle_entier{
    uint32_t u1; // bit de poids faible
    uint32_t u2;
    uint32_t u3;
    uint32_t u4;  // bits de poids forts 
}Cle_entier;

typedef struct ce_cell{
    Cle_entier* cle;
    struct ce_cell* suiv;  
}Ce_Cell;

Cle_entier* create_cle_entier_init();
bool inf(Cle_entier* cle1, Cle_entier* cle2);
bool eg(Cle_entier* cle1, Cle_entier* cle2);
char* complet0(char* hex);
Cle_entier* hexa_to_cle_entier(char* hex);
void print_cle(Cle_entier* cle);
Ce_Cell* create_cell_cle(Cle_entier* cle);
Ce_Cell* insert_cle_in_CELL(Cle_entier* cle, Ce_Cell* lcle);
void supprimer_fin(Ce_Cell** lcle);
void print_list_cle(Ce_Cell* lcle);
void free_list_cle(Ce_Cell* lcle);
Ce_Cell* read_file_cles(char* nomFichier);

#endif
