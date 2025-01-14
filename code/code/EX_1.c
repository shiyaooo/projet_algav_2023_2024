#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "EX_1.h"

/*---------------------E1----------------------------*/

/*----------------------Q1.1------------------------*/

Cle_entier* create_cle_entier_init(){ //O(1)
    Cle_entier* cle=malloc(sizeof(Cle_entier));
    if(cle==NULL){
        printf("Erreur d'allocation\n");
        return NULL;
    }
    cle->u1=0;
    cle->u2=0;
    cle->u3=0;
    cle->u4=0;
    return cle;
}
//Explication : on creer une structure composée de 4 entiers non signés sur 32 bits pour obtenir un entier codé  sur 128 bits
/*----------------------Q1.2------------------------*/

bool inf(Cle_entier* cle1, Cle_entier* cle2){ //O(1)
    if(cle1 == NULL || cle2 == NULL) return false;
    if(cle1->u4 < cle2->u4) return true;
    else if(cle1->u4 == cle2->u4){
        if(cle1->u3 < cle2->u3) return true;
        else if(cle1->u3 == cle2->u3){
           if(cle1->u2 < cle2->u2) return true;
           else if(cle1->u2 == cle2->u2){ 
                if(cle1->u1 < cle2->u1) return true;
                return false;
           }
           else return false;
        }
        else return false;
    }
    else return false;
}

/*----------------------Q1.3------------------------*/

bool eg(Cle_entier* cle1, Cle_entier* cle2){ //O(1)
    if(cle1 == NULL && cle2  == NULL) return true;
    if(cle1 == NULL || cle2 == NULL) return false;
    
    if (cle1->u1 != cle2->u1) return false;
    else if(cle1->u2 != cle2->u2) return false;
    else if(cle1->u3 != cle2->u3) return false;
    else if(cle1->u4 != cle2->u4) return false;
    else return true;
}

/*unsigned int hex_un_to_deci (char c){
    if(c>='A' && c<='F'){
        return c-65+10;
    }
    else if (c>='a' && c<='f'){
        return c-97+10;
    }
    return c-48;
}*/

char* complet0(char* hex){//O(n) 
    int length=strlen(hex);
    //printf("len %d\n",length);
    char* res = (char*)malloc(33 * sizeof(char));
    for (int i=0;i<(32-length);i++){
            res[i]='0';
            //printf("res=%c\n",res[i]);

    }
    res[32-length]='\0';
    //printf("res=%s\n",res);
    //printf("hex=%s\n",hex);
    strcat(res,hex);
    //printf("l=%d\n",strlen(hex));
    //printf("hex=%s\n",res);
    return res;
}

/*unsigned int hexa_to_decimal(char *hex){
    int length = strlen(hex);
    unsigned int num=0;
    for (int i=length-1; i>=0; i--){
        num += hex_un_to_deci(hex[i])*pow(16,length-i-1);}
    return num;
}*/

Cle_entier* hexa_to_cle_entier(char* hex){ //O(1)
    hex=complet0(hex);
    Cle_entier* cle = create_cle_entier_init();
    uint32_t* t=malloc(4 * sizeof(uint32_t));
    sscanf(hex,"%8x%8x%8x%8x",&t[0], &t[1], &t[2], &t[3]);
    //printf("%x\n",t[0]);
    cle->u1=t[3];
    cle->u2=t[2];
    cle->u3=t[1];
    cle->u4=t[0];
    free(t);
    return cle;
}

void print_cle(Cle_entier* cle){ ////O(1)
    if(cle) printf("%08x %08x %08x %08x\n", cle->u4, cle->u3, cle->u2, cle->u1);
}

Ce_Cell* create_cell_cle(Cle_entier* cle){ //O(1)
    Ce_Cell *lcle=malloc(sizeof(Ce_Cell));
    
    if(lcle==NULL){
        printf("Erreur d'allocation\n");
        return NULL;
    }
    
   /* if (cle == NULL) {
        printf("il n' y a pas de cle_entier\n");
        return NULL;
  }*/
   
    lcle->cle=cle;
    lcle->suiv=NULL;
    return lcle;
}

//création et insertion d'une clé à la fin d'une liste de clés
Ce_Cell* insert_cle_in_CELL(Cle_entier* cle, Ce_Cell* lcle){ //O(n)
    Ce_Cell* tmpcle;
    tmpcle=lcle;
    if(lcle==NULL){
        return create_cell_cle(cle);
    }else{while(tmpcle->suiv){
        tmpcle=tmpcle->suiv;
        }
        tmpcle->suiv=create_cell_cle(cle);

    }
    return lcle;
}

void supprimer_fin(Ce_Cell** lcle) { //O(n)
    if (*lcle == NULL) {
        fprintf(stderr, "La liste est vide, impossible de supprimer la fin.\n");
        exit(EXIT_FAILURE);
    }

    if ((*lcle)->suiv == NULL) {
        // Cas où il n'y a qu'un seul élément dans la liste
        free(*lcle);
        *lcle = NULL;
        return;
    }

    Ce_Cell* avant_dernier = *lcle;
    while (avant_dernier->suiv->suiv != NULL) {
        avant_dernier = avant_dernier->suiv;
    }

    //free(avant_dernier->suiv->cle);
    free(avant_dernier->suiv);
    avant_dernier->suiv = NULL;
}

void print_list_cle(Ce_Cell* lcle) { //O(n)
    Ce_Cell* tmpcle = lcle;

    while (tmpcle) {
        print_cle(tmpcle->cle);
        tmpcle = tmpcle->suiv;
    }
}

void free_list_cle(Ce_Cell* lcle) { //O(n)
    Ce_Cell* tmpcle;
    while (lcle) {
        tmpcle = lcle;
        lcle = lcle->suiv;
        free(tmpcle->cle); 
        free(tmpcle);
    }
}

Ce_Cell* read_file_cles(char* nomFichier){ //O(n²) n =nb de ligne.
    FILE* f =fopen(nomFichier,"r");
    if (f==NULL){
        fprintf(stderr,"erreur d'ouverture du fichier texte contenant les clés %s\n",nomFichier);
        return 0;
    }
    int taille_max=256;
    char buffer[taille_max];
    Ce_Cell* lcle=NULL;
    Cle_entier* cle;
    char* res=malloc((sizeof(char)*33));
    char* tmp=malloc((sizeof(char)*33));
    int i=0;
    while (fgets(buffer,256,f)!=NULL)
    {   
        //printf("len de buffer %ld\n",strlen(buffer));
        strncpy(res,buffer+2,32);
        res[strlen(res)]='\0';
        //printf("res=%s\n",res);
        sscanf(res,"%s",tmp);
        tmp[strlen(tmp)]='\0';
        //printf("tmp=%s, sa taille %ld\n", tmp, strlen(tmp));
        cle=hexa_to_cle_entier(tmp);
        lcle=insert_cle_in_CELL(cle, lcle);
        i+=1;
        //printf("file: res=%s\n",res);
    }
    //printf("i=%d\n",i);
    free(res);
    free(tmp);
    return lcle;
} ;





