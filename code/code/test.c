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
    printf("EX2\n");
    //-----------------------------Q2.8------------------------------
    //int sizes[]= {1000, 5000, 10000, 20000, 50000, 80000, 120000, 200000, 0};
    //via arbre
    //int repetitions=5;
    //via arbre
    //temps_ajout_iteratif_tas_arbre(sizes,repetitions);
    //graphe_ajout_iteratif_tas_arbre();
    //system("gnuplot -persist plot_script_ajout_It_arbre.gnu.gnu");

    //temps_construction_tas_arbre(sizes,repetitions);
    //graphe_construction_tas_arbre();
    //system("gnuplot -persist plot_script_cons_arbre.gnu.gnu");

    //via tableau
    //Comparer_tab(sizes,5);
    //graphe_tab();
    //system("gnuplot -persist plot_comparer.gnu");

    //-----------------------------Q2.9------------------------------
    //int sizes2[] = {2000, 6000, 15000, 30000, 0};
    //int sizes2[]={2000, 6000, 15000, 30000, 70000, 140000,170000, 250000, 0};
    //via arbre
    //verf_arbre_union(sizes2,sizes,5);
    //graphe_union_arbre();
    //system("gnuplot -persist plot_script_union_arbre.gnu");
    
    //via tableau
    //verf_tab_union(sizes2,sizes,5);
    //graphe_tab_un();
    //system("gnuplot -persist plot_script_union_tab.gnu");

    printf("\nEX3\n");
    //-----------------------------Q3.12------------------------------
    printf("\n");
    //int sizes[] = {1000, 5000, 10000, 20000, 50000, 0};
    //int sizes[] = {1000, 5000, 10000, 20000, 50000, 80000, 120000, 200000, 0};
    //Comparer_FB_Cons(sizes,5);
    //graphe_FB_Cons();
    //Exécuter gnuplot pour générer le graphique de construction_FB
    //system("gnuplot -persist plot_script_cons_filb.gnu");
    
    //-----------------------------Q3.13------------------------------
    //int sizes2[] = {6000, 15000, 25000, 30000,70000, 0};
    //int sizes2[]={2000, 6000, 15000, 30000, 70000, 140000,170000, 250000, 0};
    //verf_FB_union(sizes2,sizes,5);
    //graphe_FB_un();
    //system("gnuplot -persist plot_script_union_filb.gnu");


    printf("\nEX5\n");
    //-----------------------------Q6.14------------------------------
    //verif_exist_abr_rech(sizes,5);
    //graphe_exists_abr();
    //system("gnuplot -persist plot_script_exists_abr.gnu");
    
    printf("\nEX6\n");
    //-----------------------------Q6.14------------------------------
    //Words* lwords=read_Files_Shakespeare("./Shakespeare");
    //printf("\n");
    //Ce_Cell* lclew=word_en_Cell(lwords);
    //print_list_cle(lclew);
    //affichage_words(lwords);

    //affichage_CE_CELL(lclew);

    //-----------------------------Q6.15------------------------------
    //printf("\n");
    //int is_d=hasDuplicate(lclew);
    //printf("%d\n",is_d);

    //-----------------------------Q6.16------------------------------
    //Construnction
    //comparer_temps_suppr_cons();
    //graphe_temps_suppr_cons();
    //system("gnuplot -persist plot_script_cons_cmp.gnu");

    //SupprMin
    //system("gnuplot -persist plot_script_suppr_min_cmp.gnu");

    //Ajout
    //Ce_Cell* la=read_file_cles("./exm4.txt");
    //comparer_temps_ajout(la);
    //graphe_temps_ajout();
    //system("gnuplot -persist plot_script_ajout_cmp.gnu");

    //Union
    //verf_union();
    //graphe_union();
    //system("gnuplot -persist plot_script_cmp.gnu");
    
    return 0;
}