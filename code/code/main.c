#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "EX_1.h"
#include "EX_2.h"
#include "EX_3.h"
#include "EX_4.h"
#include "EX_5.h"
#include "EX_6.h"

int main(void){
    printf("-----------EXERCICE 1------------\n");
    printf("-----------TEST DE CONVERSION HEXADECIMAL EN CLE------------\n");
    Cle_entier* ex= hexa_to_cle_entier("39591f2098da9e59");
    printf ("%x\n",ex->u1);
    printf ("%x\n",ex->u2);
    printf ("%x\n",ex->u3);
    printf ("%x\n",ex->u4);
    Ce_Cell* lc1=read_file_cles("./exm1.txt");
    Cle_entier* c1=lc1->cle;
    printf("%x\n",c1->u4);
    Cle_entier* c2=lc1->suiv->suiv->suiv->suiv->cle;
    printf("u1=%x\n",c2->u1);
    printf("c1 est inferieur que c2:%d\n",inf(c1,c2));
    printf("c1 est egale a c2:%d\n",eg(c1,c2));   
    
    printf("-----------EXERCICE 2------------\n");

    Ce_Cell* lcle = read_file_cles("./jeu_de_cles_ajout_iteratifs.txt");

    printf("-----------TEST CREATION TAS MIN (NOEUD)------------\n");

    Tas_Min_arbre* ab = create_tas_arbre(lcle->cle);
    printf("Tas ab à la création : \n\n");afficher_tas_arbre(ab,0);
    printf("-----------------------\n");

    //test ajout d'un éléments dans un tas min
   printf("\n-----------TEST AJOUTS------------\n");
   printf("Tas ab avant ajout : \n\n");afficher_tas_arbre(ab,0);
   printf("-----------------------\n");
   ajout_tas_arbre(&ab,lcle->suiv->suiv->cle);
   ajout_tas_arbre(&ab,lcle->suiv->suiv->suiv->cle);
   ajout_tas_arbre(&ab,lcle->suiv->suiv->suiv->suiv->cle);
   printf("Tas ab après ajout : \n\n");afficher_tas_arbre(ab,0);
   

   printf("\n-----------TEST AJOUTS ITERATIFS------------\n");
   Ce_Cell* lcle1 = read_file_cles("./jeu_de_cles_ajout_iteratifs1.txt");
   Ce_Cell* lcle2 = read_file_cles("./jeu_de_cles_ajout_iteratifs2.txt");

   //test d'ajout itératif d'éléments dans un tas min
   free_tas_arbre(ab);
   ab=NULL;
   printf("Tas ab avant ajouts itétratifs : \n\n");afficher_tas_arbre(ab,0);
   printf("\n");
   ajout_iteratif_tas_arbre(&ab,lcle1);
   printf("Tas ab après ajouts itétratifs des clés : \n\n");
   print_list_cle(lcle1);
   printf("\n");
   afficher_tas_arbre(ab,0);
    
   printf("----------------------------------------------\n");
   Tas_Min_arbre* ab2=NULL;
   printf("Tas ab2 avant ajouts itétratifs : \n\n");afficher_tas_arbre(ab2,0);
   printf("\n");
   ajout_iteratif_tas_arbre(&ab2,lcle2);
   printf("Tas ab2 après ajouts itétratifs des clés : \n\n");
   print_list_cle(lcle2);
   printf("\n");
   afficher_tas_arbre(ab2,0);

   
   printf("\n-----------TEST SUPPRESSION DE LA RACINE------------\n");
   Cle_entier* cle_suppr=NULL;
   free_tas_arbre(ab);
   ab=NULL;
   printf("Tas ab avant suppression de la racine : \n\n");afficher_tas_arbre(ab,0);
   printf("\n");
   cle_suppr = suppr_min_tas_arbre(&ab);
   printf("Tas ab après suppression de la racine : \n\n");
   afficher_tas_arbre(ab,0);
    
   printf("----------------------------------------------\n");
   
   printf("Tas ab2 avant suppression de la racine : \n\n");afficher_tas_arbre(ab2,0);
   printf("\n");
   cle_suppr = suppr_min_tas_arbre(&ab2);
   printf("Tas ab2 après suppression de la racine : \n\n");
   afficher_tas_arbre(ab2,0);
   printf("\n");
   printf("Cle supprimée :"); print_cle(cle_suppr);

   
   printf("\n-----------TEST CONSTRUCTION DE TAS MIN EN O(n)------------\n");
   
   free_tas_arbre(ab);
   ab=NULL;
   printf("Tas ab avant construction : \n\n");afficher_tas_arbre(ab,0);
   printf("\n");
   ab = construction_tas_arbre(lcle1);
   printf("Tas ab après construction avec les clés : \n\n");
   print_list_cle(lcle1);
   printf("\n");
   afficher_tas_arbre(ab,0);

   printf("\n-----------TEST DE L'UNION DE DEUX TAS MIN------------\n");
   Tas_Min_arbre *union_ab;
   printf("Les arbres à unir : \n\n");
   afficher_tas_arbre(ab,0);
   printf("-------------\n");
   afficher_tas_arbre(ab2,0);
   printf("\n");
   union_ab = union_tas_arbre(ab,ab2);
   printf("Résultat de l'union : \n\n");
   afficher_tas_arbre(union_ab,0);
    
    //print_list_cle(lc1);
    Tas_Min_tableau* tas1= initial_tab_tas(10);
    Ajout_Tab(tas1,lc1->cle);
    Ajout_Tab(tas1,getelm(lc1,1));
    Ajout_Tab(tas1,getelm(lc1,2));
    Ajout_Tab(tas1,getelm(lc1,3));
    Ajout_Tab(tas1,getelm(lc1,4));
    Ajout_Tab(tas1,getelm(lc1,5));
    Ajout_Tab(tas1,getelm(lc1,6));
    printf("cap=%d, taille=%d\n",tas1->capacite,tas1->taille);
    Affiche_Tab(tas1);
    Ce_Cell* lc2=read_file_cles("./exm2.txt");
    printf("\n");
    print_list_cle(lc2);
    printf("\n");
    printf("ajout iteratif tab\n");
    Ajout_It_tab(tas1, lc2);
    Affiche_Tab(tas1);
    Cle_entier* elemin=SupprMin(tas1);
    printf("suuprimer la cle minimun: %x %x %x %x\n",elemin->u4,elemin->u3, elemin->u2, elemin->u1 );
    Affiche_Tab(tas1);
    printf("\n\n");

    Ce_Cell* lc3=read_file_cles("./exm3.txt");
    //print_list_cle(lc3);    
    //printf("\n");

    Tas_Min_tableau* tas2=Construction_tab(lc3);
    Affiche_Tab(tas2);
    printf("\n");

    
    Tas_Min_tableau* tas3=Union_tab(tas1,tas2);
    Affiche_Tab(tas3);


    //EX3
    printf("-----------EXERCICE 3------------\n");
    Ce_Cell* lc4=read_file_cles("./exm1.txt");
    print_list_cle(lc4);
    TournoisB* tb1=create_tournoisB(lc4->cle);
    TournoisB* tb2=create_tournoisB(lc4->suiv->cle);
    tb1=mergeFB_meme_degre(tb1,tb2);
    //printf("dpth=%d\n", tb1->enfant->pfd);
    print_cle(tb1->enfant->cle);
    printf("\n");
    afficher_tournoisB(tb1);
    printf("\n");
    TB_Cell* fb = create_FileB(tb1);
    TournoisB* tb3=create_tournoisB(lc4->suiv->suiv->cle);
    TournoisB* tb4=create_tournoisB(lc4->suiv->suiv->suiv->cle);    
    TournoisB* tb5=create_tournoisB(lc4->suiv->suiv->suiv->suiv->cle);
    TournoisB* tb6=create_tournoisB(lc4->suiv->suiv->suiv->suiv->suiv->cle);
    TournoisB* tb7=create_tournoisB(lc4->suiv->suiv->suiv->suiv->suiv->suiv->cle);
    mergeFB_meme_degre(tb3,tb4);
    afficher_tournoisB(tb3);
    printf("\n");
    mergeFB_meme_degre(tb5,tb6);
    mergeFB_meme_degre(tb3,tb5);
    afficher_tournoisB(tb5);
    printf("\n");
    fb= insert_in_FB(tb5, fb);
    afficherFileB(fb);
    printf("deg %d\n",tb3->degre);
    TournoisB* deg_min;
    deg_min = degreMin_FilB(fb);
    printf("-----------------------degMin:---------------\n");
    afficher_tournoisB(deg_min);
    printf("--------------------FB reste----------------- \n"); 
    Reste_FilB(&fb);
    afficherFileB(fb);

    printf("-------------------FB ajoutMin------------------ \n");
    AjoutMin_FB(tb7,&fb);
    afficherFileB(fb);

    printf("-------------------creer une file binomiale------------------ \n");
    printf("\n");
    Ce_Cell* lc5=read_file_cles("./exm2.txt");
    TournoisB* t1=create_tournoisB(lc5->cle);
    printf("fb2:\n");
    afficher_tournoisB(t1);
    printf("\n");
    TB_Cell* fb2 = create_FileB(t1);
    TournoisB* t2=create_tournoisB(lc5->suiv->cle);
    TournoisB* t3=create_tournoisB(lc5->suiv->suiv->cle);    
    TournoisB* t4=mergeFB_meme_degre(t2,t3);
    printf("t4\n");
    afficher_tournoisB(t4);
    printf("\n");
    fb2=insert_in_FB(t4,fb2);
    printf("new fb2:\n");
    afficherFileB(fb2);

    printf("\n");
    printf("-----------------------union fb et fb2---------------\n");
    TB_Cell* fb3 =Union_FilB(fb,fb2);
    afficherFileB(fb3);

    printf("\n");
    printf("-----------------Construction fb4--------------------\n");
    Ce_Cell* lc6=read_file_cles("./exm3.txt");
    TB_Cell* fb4=construction_FB(lc6);
    afficherFileB(fb4);
    //Supprimer
    printf("\n");
    printf("----------------Cherche le min de TB dans fb4------------\n");
    TournoisB* mintb=findMinTB(fb4);
    afficher_tournoisB(mintb);

    printf("\n");
    printf("-----------------SuppMin---------------------- \n");
    TB_Cell* fb5=SupprMin_FilB(fb4);
    afficherFileB(fb5);

    
    //EX4
    printf("\n-----------EXERCICE 4------------\n");
    char* original_message= "Et l’unique cordeau des trompettes marines";
    uint64_t original_length = strlen(original_message) ;
    printf("long de msg: %ld\nmessdage: %s\n",original_length,original_message);

    uint32_t hash[4];
    MD5(original_message,original_length,hash);
    printf("Message après le MD5:\n");
    for (int i = 0; i < 4; i++) {
        printf("%08x", hash[i]);
    }
    printf("\n");

    printf("\n-----------EXERCICE 5------------\n");
    printf("-----------TEST ARBRE VIDE (PRIMITIVE)------------\n");
    Cle_entier* cl;
    AB_Rech* ab_r = arbre_vide();
    AB_Rech* ab_r2 = arbre_vide();
    AB_Rech* ab_r3 = arbre_vide();
    if(ab_r==NULL)printf("Larbre est vide.\n"); 

    printf("-----------TEST ARBRE BINAIRE (PRIMITIVE)------------\n");
    Ce_Cell* llc5=read_file_cles("./jeu_de_cles_ajout_iteratifs.txt");
    ab_r = arbre_binaire(llc5->cle,NULL,NULL);
    afficher_ab_rech(ab_r,0);
    printf("\n\n");

    printf("-----------TEST EST ARBRE VIDE (PRIMITIVE)------------\n"); 
    if(est_arbre_vide(ab_r) == false)printf("Larbre n'est pas vide.\n"); 
    ab_r = arbre_vide();
    if(est_arbre_vide(ab_r))printf("Larbre est vide.\n"); 
    printf("\n\n");

    printf("-----------TEST RACINE (PRIMITIVE)------------\n"); 
    ab_r = arbre_binaire(llc5->cle,NULL,NULL);
    printf("Racine : "); print_cle(racine(ab_r));
    printf("\n\n");

    printf("-----------TEST SOUS ARBRE DROIT (PRIMITIVE)------------\n"); 
    ab_r2 = arbre_binaire(llc5->suiv->suiv->cle,NULL,NULL);
    if(inf(ab_r->cle,ab_r2->cle)) ab_r->fils_d = ab_r2; 
    printf("Sous arbre droit : "); afficher_ab_rech(sous_arbre_droit(ab_r),1);
    printf("\n\n");

    printf("-----------TEST SOUS ARBRE GAUCHE (PRIMITIVE)------------\n"); 
    ab_r3 = arbre_binaire(llc5->suiv->cle,NULL,NULL);
    if(inf(ab_r3->cle,ab_r->cle)) ab_r->fils_d = ab_r3; 
    ab_r->fils_g = ab_r3; 
    printf("Sous arbre gauche : "); afficher_ab_rech(sous_arbre_gauche(ab_r),1);
    printf("\n\n");

    

    printf("-----------TEST SOUS PARENT (PRIMITIVE)------------\n"); 
    ab_r3->parent = ab_r;
    ab_r2->parent = ab_r;
    printf("Parent de : "); afficher_ab_rech(ab_r2,1); printf(" = "); print_cle(parent(ab_r3)->cle);
    printf("\n\n");

    printf("-----------TEST EXISTS------------\n"); 
    cl = ab_r2->cle;
    print_cle(ab_r2->cle);
    afficher_ab_rech(ab_r,0);
    if(exists(ab_r,cl)){
        printf("L'arbre \n");
        afficher_ab_rech(ab_r,0);
        printf(" contient ");
        print_cle(cl);
    }
    printf("\n\n");

    printf("-----------TEST AJOUT------------\n"); 
    printf("Arbre initiale : \n");
    afficher_ab_rech(ab_r,0);
    cl = llc5->suiv->suiv->suiv->suiv->cle;
    ab_r = ajout_AB_Rech(ab_r,cl);
    printf("\nAjout de : "); print_cle(cl);
    printf("\n");
    afficher_ab_rech(ab_r,0);
    printf("\n\n");

    printf("-----------TEST AJOUT ITERATIF------------\n"); 
    printf("Arbre initiale : \n");
    afficher_ab_rech(ab_r,0);
    printf("\nAjout itératif de : "); print_list_cle(llc5);
    ab_r = ajout_it_AB_Rech(ab_r,lc5);
    printf("\n");
    afficher_ab_rech(ab_r,0);
    
    printf("-----------EXERCICE 6------------\n");
    
    printf("-----------Q6.14------------\n"); 
    Words* lwords=read_Files_Shakespeare("./Shakespeare");
    printf("\n");
    Ce_Cell* lclew=word_en_Cell(lwords);
    print_list_cle(lclew);
    affichage_words(lwords);
    affichage_CE_CELL(lclew);
    printf("ABR avec lcw\n");
    AB_Rech* abr=construction_ABR(lclew);
    afficher_ab_rech(abr,0);

    printf("-----------Q6.15------------\n"); 
     printf("\nis_collision: ");
    int is_d=hasDuplicate(lclew);
    printf("%d\n",is_d);


    return 0;
}
//dans execution: gcc EX_1.c main.c -o main -lm