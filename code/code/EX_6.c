#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include<dirent.h>
#include "EX_6.h"

/*----------------------Q6.14------------------------*/
Words* create_list_word(char* cle){
    Words* lcle=malloc(sizeof(Words));
    if(lcle==NULL){
        printf("Erreur d'allocation\n");
        return NULL;
    }
   
    lcle->data=strdup(cle);
    //printf("lcle->data %s\n",lcle->data);
    lcle->suiv=NULL;
    return lcle;
}

Words* insert_word_in_List(char* cle, Words* lcle){
    if(lcle==NULL){
        return create_list_word(cle);
    }
    Words* tmpcle=lcle;
    while(tmpcle->suiv!=NULL){
        tmpcle=tmpcle->suiv;
    }
    tmpcle->suiv=create_list_word(cle);
    return lcle;
}

Words* insertWordsNotExist(char* cle, Words* lcle){
    // Vérifier si l'élément est déjà présent dans la liste
    Words* current = lcle;
    //if(lcle==NULL){return create_list_word(cle);}
    while (current != NULL) {
        if (strcmp(current->data, cle) == 0) {
            // L'élément est déjà présent, ne pas l'insérer à nouveau
            //printf("deja exist\n");
            return lcle;
        }
        current = current->suiv;
    }
    // L'élément n'est pas dans la liste, l'insérer
    //printf("word=%s\n",cle);
    return insert_word_in_List(cle, lcle);
}

// Fonction pour afficher la liste chaînée
void print_List_Word(Words* lw) {
    Words* current = lw;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->suiv;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire allouée pour la liste chaînée
void free_List_word(Words* lw) {
    Words* current = lw;
    Words* next;

    while (current != NULL) {
        next = current->suiv;
        free(current->data);
        free(current);
        current = next;
    }
}

   
Words* read_Files_Shakespeare(char* nomDossier){
    struct dirent *dir;

     DIR *d=opendir(nomDossier);
     if(!d){
        fprintf(stderr,"erreur d'ouverture du dossier %s\n",nomDossier);
        return NULL;
     }
    // Lire tous les fichiers dans le répertoire
    char word[256];
    Words* words=NULL;
    while((dir=readdir(d))!=NULL){
        // Assurez-vous de ne pas traiter les entrées spéciales "." et ".."
        if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
            //printf("file=%s\n",dir->d_name);
            char file_path[257];
            sprintf(file_path,"%s/%s",nomDossier,dir->d_name);
            file_path[strlen(file_path)]='\0';
            FILE* f =fopen(file_path,"r");
            if (f==NULL){
                fprintf(stderr,"erreur d'ouverture du fichier texte contenant les mots %s\n",file_path);
                return NULL;
            }

            int taille_max=256;
            char buffer[taille_max];
            
            while (fgets(buffer,256,f)!=NULL){
                sscanf(buffer,"%s",word);
                //inserer dans une liste de word apres comparer avec elm
                words=insertWordsNotExist(word,words);
                //words_initial=insert_word_in_List(word,words_initial);
            }
            //printf("words->data=%s\n",words->data);
            
            fclose(f);
        }
        
    }
    //print_List_Word(words);
    //print_list_cle(lcle);
    closedir(d);   
   
    return words;
}
   
Ce_Cell* word_en_Cell(Words* words){
    Ce_Cell* lcle=NULL;
    uint32_t hash[4];
    Cle_entier* cle=create_cle_entier_init();
    Words* tmp=words;
    while(tmp){
        MD5(tmp->data,strlen(tmp->data),hash);
        cle->u4=hash[0];
        cle->u3=hash[1];
        cle->u2=hash[2];
        cle->u1=hash[3];
        lcle=insert_cle_in_CELL(cle,lcle);
        cle=create_cle_entier_init();
        tmp=tmp->suiv;
    }
    return lcle;
} 

AB_Rech* construction_ABR(Ce_Cell* lcle){
    AB_Rech* abr=NULL;
    Ce_Cell* lcle_tmp=lcle;
    while(lcle_tmp){
        abr = ajout_AB_Rech(abr,lcle_tmp->cle);
        lcle_tmp = lcle_tmp->suiv;
    }
    return abr;
}  

void affichage_words(Words* words){
    FILE *f = fopen("words.txt", "a");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return;
    }
    if(!words) return;
    Words* tmp=words;
    while(tmp){
        fprintf(f,"%s\n", tmp->data);
        tmp=tmp->suiv;
    }
    fclose(f);
}

void affichage_CE_CELL(Ce_Cell* lcle){
    FILE *f = fopen("hash.txt", "a");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return;
    }
    if(!lcle) return;
    Ce_Cell* tmp=lcle;
    while(tmp){
        fprintf(f,"0x%08x%08x%08x%08x\n", tmp->cle->u4,tmp->cle->u3, tmp->cle->u2, tmp->cle->u1);
        tmp=tmp->suiv;
    }
    fclose(f);
}

/*----------------------Q6.15------------------------*/
int hasDuplicate(Ce_Cell* lce) {

    Ce_Cell* current = lce;
    // Utiliser un ensemble (ici, une liste chaînée) pour stocker les éléments rencontrés
    Ce_Cell* set = NULL;

    while (current != NULL) {
        // Vérifier si l'élément est déjà dans l'ensemble
        Ce_Cell* checkNode = set;
        while (checkNode != NULL) {
            if (eg(checkNode->cle, current->cle)==1) {
                // L'élément est déjà présent, c'est un doublon
                printf("il possede une collision pour MD5\n");
                return 1;
            }
            checkNode = checkNode->suiv;
        }

        // Ajouter l'élément à l'ensemble
        set=insert_cle_in_CELL(current->cle,set);

        current = current->suiv;
    }

    // Aucun doublon trouvé
    printf("il n'y pas les ensembles des mots différents de l’œuvre de Shakespeare qui sont en collision pour MD5\n");
    return 0;
}

/*----------------------Q6.16------------------------*/

double measureTime_suppr_min_fb(TB_Cell * (*function)(TB_Cell *),TB_Cell * fb){
    clock_t start, end;
    TB_Cell* result;
    start = clock();
    result=function(fb); 
    end = clock();
    free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}


double measureTime_suppr_min_tab(Cle_entier* (*function)(Tas_Min_tableau*), Tas_Min_tableau* tas){
    clock_t start, end;
    Cle_entier* result;
    start = clock();
    result=function(tas);
    end = clock();
    free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double measureTime_suppr_min_tm(Tas_Min_arbre* (*function)(Tas_Min_arbre *),Tas_Min_arbre * tas){
    clock_t start, end;
    Tas_Min_arbre* result;
    start = clock();
    result=function(tas);
    end = clock();
    free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}


void comparer_temps_suppr_cons(){
    srand(time(NULL));

    FILE *dataFileCons = fopen("time_data_cons_cmp.txt", "w");
    if (!dataFileCons) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }
    FILE *dataFileSupprMin = fopen("time_data_supp_min_cmp.txt", "w");
    if (!dataFileSupprMin) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }


    // Répéter les mesures
    double consFbTime = 0.0;
    double supprMinFbTime = 0.0;

    double consTmTime = 0.0; 
    double supprMinTmTime = 0.0; 

    double consTabTime = 0.0; 
    double supprMinTabTime = 0.0; 
    
    // Générer des données
    Ce_Cell* jeu_cles= NULL;
    
    // Liste de cles
    Words* lw=read_Files_Shakespeare("./Shakespeare");
    jeu_cles=word_en_Cell(lw);
    //jeu_cles=read_file_cles("./cles_alea/jeu_1_nb_cles_1000.txt");

    // Mesurer le temps de Construction Fb
    TB_Cell* fb = construction_FB(jeu_cles);
    consFbTime += measureTime_cons_FB(construction_FB, jeu_cles);

    // Mesurer le temps de SupprMin Fb
    supprMinFbTime += measureTime_suppr_min_fb(SupprMin_FilB, fb);
    
    // Mesurer le temps de Construction TasMin arbre
    consTmTime += measureTime_cons_ab(construction, jeu_cles);

    // Mesurer le temps de SupprMin TasMin arbre
    Tas_Min_arbre* tas_abr = construction(jeu_cles);
    supprMinTmTime += measureTime_suppr_min_tm(supprMin, tas_abr);

    // Mesurer le temps de Construction TasMin tableau
    consTabTime += measureTime_cons(Construction_tab, jeu_cles);

    // Mesurer le temps de SupprMin TasMin tableau
    Tas_Min_tableau* tas_tb = Construction_tab(jeu_cles);
    supprMinTabTime += measureTime_suppr_min_tab(SupprMin, tas_tb);
    
    // Assurez-vous de libérer la mémoire allouée
    //printf("liste de cle taille:%d\n",taille_lcle(jeu_cles));
    //free_list_cle(jeu_cles);
    
    printf("timeConsFb = %f, timeConsTm= %f, timeConsTab= %f\n",consFbTime,consTmTime, consTabTime); 
    printf("timeSupprMinFb = %f, timeSupprMinTm= %f, timeSupprMinTab= %f\n",supprMinFbTime,supprMinTmTime, supprMinTabTime); 

    // Écrire les données dans les fichiers
    fprintf(dataFileCons, "%f %f %f\n", consTabTime ,consTmTime,consFbTime);
    fprintf(dataFileSupprMin, "%f %f %f\n", supprMinTabTime, supprMinTmTime, supprMinFbTime);
    
    
    fclose(dataFileCons);
    fclose(dataFileSupprMin);

    return;
 }

void graphe_temps_suppr_cons(){

    // Générer le script gnuplot pour le tracé de Construction
    FILE *gnuplotScriptCons = fopen("plot_script_cons_cmp.gnu", "w");
    if (!gnuplotScriptCons) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour cons_cmp");
        return ;
    }
    
    fprintf(gnuplotScriptCons, "set title 'Temps de Construction '\n");
    fprintf(gnuplotScriptCons, "set style data histograms\n");
    fprintf(gnuplotScriptCons, "set ylabel 'Temps'\n");
    fprintf(gnuplotScriptCons, "unset xtics\n");
    fprintf(gnuplotScriptCons, "set logscale y\n");
    fprintf(gnuplotScriptCons, "set yrange [1e-7:10]\n");
    fprintf(gnuplotScriptCons, "set ytics ('10^{-7}' 1e-7,'10^{-6}' 1e-6, '10^{-5}' 1e-5, '10^{-4}' 1e-4, '10^{-3}' 1e-3, '10^{-2}' 1e-2, '10^{-1}' 1e-1, '10^{0}' 1, '10^{1}' 10)\n");   
    fprintf(gnuplotScriptCons, "set boxwidth 1\n");
    fprintf(gnuplotScriptCons, "set style histogram cluster gap 1\n");
    fprintf(gnuplotScriptCons, "set style fill solid border -1\n");
    fprintf(gnuplotScriptCons, "set key top right\n");
    fprintf(gnuplotScriptCons, "plot 'time_data_cons_cmp.txt' using 1:xtic(1) title 'tas_min_tab', '' using 2 title 'tas_min_ab', '' using 3 title 'file_binomiale'\n");


     // Générer le script gnuplot pour le tracé de Suppr_Min
    FILE *gnuplotScriptSupprMin = fopen("plot_script_suppr_min_cmp.gnu", "w");
    if (!gnuplotScriptSupprMin) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour suppr_min_cmp");
        return ;
    }

    fprintf(gnuplotScriptSupprMin, "set title 'Temps de Suppr_Min'\n");
    fprintf(gnuplotScriptSupprMin, "set style data histograms\n");
    fprintf(gnuplotScriptSupprMin, "unset xtics\n");
    fprintf(gnuplotScriptSupprMin, "set ylabel 'Temps'\n");
    fprintf(gnuplotScriptSupprMin, "set logscale y\n");
    fprintf(gnuplotScriptSupprMin, "set yrange [1e-7:10]\n");
    fprintf(gnuplotScriptSupprMin, "set ytics ('10^{-7}' 1e-7,'10^{-6}' 1e-6, '10^{-5}' 1e-5, '10^{-4}' 1e-4, '10^{-3}' 1e-3, '10^{-2}' 1e-2, '10^{-1}' 1e-1, '10^{0}' 1, '10^{1}' 10)\n");   
    fprintf(gnuplotScriptSupprMin, "set boxwidth 1\n");
    fprintf(gnuplotScriptSupprMin, "set style histogram cluster gap 1\n");
    fprintf(gnuplotScriptSupprMin, "set style fill solid border -1\n");
    fprintf(gnuplotScriptSupprMin, "set key top right\n");
    fprintf(gnuplotScriptSupprMin, "plot 'time_data_supp_min_cmp.txt' using 1:xtic(1) title 'tas_min_tab', '' using 2 title 'tas_min_ab', '' using 3 title 'file_binomiale'\n");



    fclose(gnuplotScriptCons);
    fclose(gnuplotScriptSupprMin);

    return;

}

double measureTime_ajout_fb(TB_Cell * (*function)(Cle_entier*, TB_Cell *),Cle_entier* cle, TB_Cell * fb){
    clock_t start, end;
    TB_Cell* result;
    start = clock();
    result=function(cle,fb);
    end = clock();
    free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double measureTime_ajout_tm_abr(Tas_Min_arbre * (*function)(Tas_Min_arbre*, Cle_entier*),Tas_Min_arbre* tas, Cle_entier* cle){
    clock_t start, end;
    Tas_Min_arbre* result;
    start = clock();
    result=function(tas,cle);
    end = clock();
    free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double measureTime_ajout_tm_tab(void (*function)(Tas_Min_tableau*,Cle_entier*), Tas_Min_tableau* tas, Cle_entier* cle){
    clock_t start, end;
    start = clock();
    function(tas,cle);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void comparer_temps_ajout(Ce_Cell* cles){
    int len = taille_lcle(cles);
    srand(time(NULL));

    FILE *dataFileAjout = fopen("time_data_ajout_cmp.txt", "w");
    if (!dataFileAjout) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }

    // Répéter les mesures 
    double ajoutFbTime = 0.0;
    double ajoutTmTime = 0.0;
    double ajoutTabTime = 0.0;
    
    // Générer des données
    Ce_Cell* jeu_cles= NULL;
    Ce_Cell* cles_tmp = cles;
    Cle_entier* cle = NULL;

    // Liste de cle de chaque fichiee
    jeu_cles=word_en_Cell(read_Files_Shakespeare("./Shakespeare"));

    //Initialisation d'une file binomiale
    TB_Cell* fb = construction_FB(jeu_cles);

    //Initialisation d'un tas min (arbre)
    Tas_Min_arbre* tas_abr = construction(jeu_cles);
    //Initialisation d'un tas min (tableau)
    Tas_Min_tableau* tas_tab = initial_tab_tas(len+taille_lcle(jeu_cles)+2);
    Ajout_It_tab(tas_tab,jeu_cles);
    for(int i=0; i<len; i++){
        cle = cles_tmp->cle;

        // Mesurer le temps d'Ajout dans une file binomiale
        ajoutFbTime += measureTime_ajout_fb(ajout_cle_FB, cle, fb);

        // Mesurer le temps d'Ajout dans un tas min
        ajoutTmTime += measureTime_ajout_tm_abr(ajout, tas_abr, cle);             
                
        // Mesurer le temps d'Ajout dans un tas tableau
        ajoutTabTime += measureTime_ajout_tm_tab(Ajout_Tab, tas_tab, cle);
        
        cles_tmp = cles_tmp->suiv;

        printf("ajoutTabTime: %.7f\n",ajoutTabTime);
        printf("ajoutTmTime: %.7f\n",ajoutTmTime);
        printf("ajoutTabTime: %.7f\n",ajoutTabTime);

    }
    // Moyenne
    double aveAjoutFbTime = ajoutFbTime/len;
    double aveAjoutTmTime = ajoutTmTime/len;
    double aveAjoutTabTime = ajoutTabTime/len;

    printf("aveAjoutFb = %f\n",aveAjoutFbTime); 
    printf("aveAjoutTm = %f\n",aveAjoutTmTime); 
    printf("aveAjoutTab = %f\n",aveAjoutTabTime); 

    // Écrire les données dans les fichiers
    fprintf(dataFileAjout, "%f %f %f\n", ajoutTabTime ,ajoutTmTime, ajoutFbTime);
    
    
    fclose(dataFileAjout);
    // Assurez-vous de libérer la mémoire allouée
    //freeTas(tas_abr);
    free_list_cle(jeu_cles);

    return;
 }



void graphe_temps_ajout(){

    // Générer le script gnuplot pour le tracé de Construction
    FILE *gnuplotScriptAjout = fopen("plot_script_ajout_cmp.gnu", "w");
    if (!gnuplotScriptAjout) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour ajout_cmp");
        return ;
    }

    fprintf(gnuplotScriptAjout, "set title 'Temps d Ajout'\n");
    fprintf(gnuplotScriptAjout, "set style data histograms\n");
    fprintf(gnuplotScriptAjout, "unset xtics\n");
    fprintf(gnuplotScriptAjout, "set ylabel 'Temps(s)'\n");
    fprintf(gnuplotScriptAjout, "set logscale y\n");
    fprintf(gnuplotScriptAjout, "set yrange [1e-7:10]\n");
    fprintf(gnuplotScriptAjout, "set ytics ('10^{-7}' 1e-7,'10^{-6}' 1e-6, '10^{-5}' 1e-5, '10^{-4}' 1e-4, '10^{-3}' 1e-3, '10^{-2}' 1e-2, '10^{-1}' 1e-1, '10^{0}' 1, '10^{1}' 10)\n");   
    fprintf(gnuplotScriptAjout, "set boxwidth 1\n");
    fprintf(gnuplotScriptAjout, "set style histogram cluster gap 1\n");
    fprintf(gnuplotScriptAjout, "set style fill solid border -1\n");
    fprintf(gnuplotScriptAjout, "set key top right\n");
    fprintf(gnuplotScriptAjout, "plot 'time_data_ajout_cmp.txt' using 1:xtic(1) title 'tas_min_tab', '' using 2 title 'tas_min_ab', '' using 3 title 'file_binomiale'\n");
    

    fclose(gnuplotScriptAjout);

    return;

}

void verf_union(){
    srand(time(NULL));

    FILE *dataFileUnion = fopen("time_data_union_cmp.txt", "w");
    if (!dataFileUnion) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }

    // Répéter les mesures 
    double unionFbTime = 0.0;

    double unionTmTime = 0.0;

    double unionTabTime = 0.0;
    
    // Générer des données
    Ce_Cell* jeu_cles1= NULL;
    Ce_Cell* jeu_cles2= NULL;
    
    // Liste de cle de chaque fichiee
    jeu_cles1=word_en_Cell(read_Files_Shakespeare("./Shakespeare"));
    jeu_cles2=read_file_cles("./jeu_de_cles_ajout_iteratifs.txt");
    
    // Mesurer le temps d'Union de deux files binomiales
    TB_Cell* fb1 = construction_FB(jeu_cles1);
    TB_Cell* fb2 = construction_FB(jeu_cles2);
    unionFbTime += measureTime_union_FB(Union_FilB, fb1, fb2);

    // Mesurer le temps d'Union de deux tas min
    Tas_Min_arbre* tas_abr1 = construction(jeu_cles1);
    Tas_Min_arbre* tas_abr2 = construction(jeu_cles2);
    unionTmTime += measureTime_union_ab(unionTas, tas_abr1, tas_abr2);            
            
    // Mesurer le temps d'Union de deux tas tableau
    Tas_Min_tableau* tas_tab1 = Construction_tab(jeu_cles1);
    Tas_Min_tableau* tas_tab2 = Construction_tab(jeu_cles2);
    unionTabTime += measureTime_union(Union_tab, tas_tab1, tas_tab2);

    // Assurez-vous de libérer la mémoire allouée
    freeTas(tas_abr1);
    freeTas(tas_abr2);
    //free_list_cle(jeu_cles1);
    //free_list_cle(jeu_cles2);
    
    printf("timeUnionFb = %f\n",unionFbTime); 
    printf("timeUnionTm = %f\n",unionTmTime); 
    printf("timeUnionTab = %f\n",unionTabTime); 

    // Écrire les données dans les fichiers
    fprintf(dataFileUnion, "%f %f %f\n", unionTabTime,unionTmTime, unionFbTime);
    
    
    fclose(dataFileUnion);
    return;
 }

void graphe_union(){
    // Générer le script gnuplot pour le tracé d'Union_tab
    FILE *gnuplotScriptUnion = fopen("plot_script_cmp.gnu", "w");
    if (!gnuplotScriptUnion) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour Union");
        return ;
    }

    fprintf(gnuplotScriptUnion, "set title 'Temps d Union'\n");
    fprintf(gnuplotScriptUnion, "set style data histograms\n");
    fprintf(gnuplotScriptUnion, "unset xtics\n");
    fprintf(gnuplotScriptUnion, "set ylabel 'Temps(s)'\n");
    fprintf(gnuplotScriptUnion, "set logscale y\n");
    fprintf(gnuplotScriptUnion, "set yrange [1e-7:10]\n");
    fprintf(gnuplotScriptUnion, "set ytics ('10^{-7}' 1e-7,'10^{-6}' 1e-6, '10^{-5}' 1e-5, '10^{-4}' 1e-4, '10^{-3}' 1e-3, '10^{-2}' 1e-2, '10^{-1}' 1e-1, '10^{0}' 1, '10^{1}' 10)\n");   
    fprintf(gnuplotScriptUnion, "set boxwidth 1\n");
    fprintf(gnuplotScriptUnion, "set style histogram cluster gap 1\n");
    fprintf(gnuplotScriptUnion, "set style fill solid border -1\n");
    fprintf(gnuplotScriptUnion, "set key top right\n");
    fprintf(gnuplotScriptUnion, "plot 'time_data_union_cmp.txt' using 1:xtic(1) title 'tas_min_tab', '' using 2 title 'tas_min_ab', '' using 3 title 'file_binomiale'\n");

    fclose(gnuplotScriptUnion);

    return;
}
