#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "EX_5.h"

AB_Rech* arbre_vide(){
    return NULL;
}

AB_Rech* arbre_binaire(Cle_entier* e, AB_Rech* g, AB_Rech* d){
    AB_Rech* ab = malloc(sizeof(*ab));
    if(ab==arbre_vide()) {
        fprintf(stderr,"Erreur d'allocation de l'arbre de recherche.\n");
        exit(EXIT_FAILURE);
    }
    ab->cle = e;
    ab->fils_g = g;
    ab->fils_d = d;
    return ab;
}

bool est_arbre_vide(AB_Rech* ab){
    return (ab==arbre_vide());
}

Cle_entier* racine(AB_Rech* ab){
    if(est_arbre_vide(ab)) return NULL;
    else return ab->cle;
}

AB_Rech* sous_arbre_gauche(AB_Rech* ab){
    if(est_arbre_vide(ab)) return arbre_vide();
    else return ab->fils_g;
}

AB_Rech* sous_arbre_droit(AB_Rech* ab){
    if(est_arbre_vide(ab)) return arbre_vide();
    else return ab->fils_d;
}

AB_Rech* parent(AB_Rech* ab){
    if(est_arbre_vide(ab)) return arbre_vide();
    else return ab->parent;
} 

bool exists(AB_Rech* ab, Cle_entier* cle){
    if(est_arbre_vide(ab)) return false;
    if(eg(ab->cle,cle)) return true;
    if(inf(ab->cle,cle)) return exists(ab->fils_d,cle);
    else return exists(ab->fils_g,cle);
}

AB_Rech* ajout_AB_Rech(AB_Rech* ab,Cle_entier* cle){
    if(est_arbre_vide(ab)) return arbre_binaire(cle,arbre_vide(),arbre_vide());
    else if(eg(ab->cle,cle)) return ab;
    else if(inf(ab->cle,cle)) 
        return arbre_binaire(ab->cle,ab->fils_g,ajout_AB_Rech(ab->fils_d,cle));
    else
        return arbre_binaire(ab->cle,ajout_AB_Rech(ab->fils_g,cle),ab->fils_d);
}

AB_Rech* ajout_it_AB_Rech(AB_Rech* ab,Ce_Cell* lcle){
    Ce_Cell* lcle_tmp = lcle;
    while(lcle_tmp){
        ab = ajout_AB_Rech(ab,lcle_tmp->cle);
        lcle_tmp = lcle_tmp->suiv;
    }
    return ab;
}

Cle_entier* cle_aleatoire(Ce_Cell* cles){
    int r=(random() % 10) + 1;
    int p=(random() % 5) + 1;
    int pos_rand=0;
    int taille_liste = taille_lcle(cles);
    printf("taille liste = %d\n",taille_liste);
    Ce_Cell* cles_tmp = cles;
    if(r<p) return NULL;
    else{
        pos_rand = (random() % taille_liste);
        printf("pos rand = %d\n",pos_rand);
        for(int i=0;i<pos_rand;i++)cles_tmp = cles_tmp->suiv;
        printf("here");
        return cles_tmp->cle;
    }
    return NULL;
}
void afficher_ab_rech(AB_Rech* ab,int pfd){
    if(est_arbre_vide(ab)) return;
    for(int i=0;i<pfd;i++) printf("___");    
    printf("(%u, %u, %u, %u)\n", ab->cle->u1, ab->cle->u2, ab->cle->u3, ab->cle->u4);
    afficher_ab_rech(ab->fils_d,pfd+1);
    afficher_ab_rech(ab->fils_g,pfd+1);
    return ;
}

double measureTime_exists(bool (*function)(AB_Rech*,Cle_entier*),AB_Rech* abr,Cle_entier* cle){
    clock_t start, end;
    //bool b=false;
    start = clock();
    //b=function(abr,cle);
    function(abr,cle);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void verif_exist_abr_rech(int* sizes,int repetitions){
    int len=longueur(sizes);
    srand(time(NULL));
    FILE *dataFileExists = fopen("time_data_exist_abr.txt", "w");
    if (!dataFileExists) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }

    // Répéter les mesures pour chaque taille
    for(int i=0; i < len ;i++){
        //printf("i=%d\n",i);
        int size=sizes[i];
        
        double totalExistsTime = 0.0; 
        int nb_echantillons = 200;

        // Répéter les mesures plusieurs fois pour obtenir une moyenne
        for(int j=1; j<=repetitions; j++){
            // Générer des données aléatoires
            Ce_Cell* jeu_cles= NULL;
            AB_Rech* abr = NULL;
            Cle_entier* cle_aleat=NULL;
            double timeExistsTime = 0.0;
            //Tas_Min_arbre* tasAjout = NULL;
            //Ce_Cell* tmp;
            //clock_t start, end;
            jeu_cles = read_file_cles(echanger_entier(j,size));
            abr = ajout_it_AB_Rech(abr,jeu_cles);
            
            
            printf("here\n");
            for(int k=0; k<nb_echantillons;k++){
                cle_aleat = cle_aleatoire(jeu_cles);
                timeExistsTime += measureTime_exists(exists,abr,cle_aleat);
            }
            totalExistsTime+= timeExistsTime/nb_echantillons;
            //printf("rp = %d\n",j);
            /*FILE* f =fopen(echanger_entier(j,size),"r");
            FILE* f =fopen(nomFichier,"r");
            int taille_max=256;
            char buffer[taille_max];
            Ce_Cell* lcle=NULL;
            Cle_entier* cle;
            char res[33];
            char tmp[33];
            int i=0;
            while (fgets(buffer,256,f)!=NULL)
            {   
                //printf("len de buffer %ld\n",strlen(buffer));
                strncpy(res,buffer+2,32);
                res[strlen(res)]='\0';
                //printf("res=%s\n",res);
                //sscanf(res,"%s",tmp);
                //tmp[strlen(tmp)]='\0';
                //printf("tmp=%s, sa taille %ld\n", tmp, strlen(tmp));
                cle=hexa_to_cle_entier(res);
                lcle=insert_cle_in_CELL(cle, lcle);
                i+=1;
                printf("%d\n",i);
                if(i==49999)return lcle;
                //printf("file: res=%s\n",res);
            }
                while(i<size){
                    printf("%d\n",i);
                    
                    
                    print_cle(jeu_cles->cle);
                    free(jeu_cles->cle);
                    tmp = jeu_cles;
                    jeu_cles = jeu_cles->suiv;
                    free(tmp);
                    i++;
                }*/
            //liberer_tab(tasAjout);
           
            // Mesurer le temps de Construction_tab
            //totalConsTime += measureTime_cons_ab(construction, jeu_cles);
            
            // Assurez-vous de libérer la mémoire allouée
            //free_list_cle(jeu_cles);
        }
        
        double averageExistsTime = totalExistsTime / repetitions; 
        printf("aveExt= %f\n",averageExistsTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileExists, "%d %.7f\n", size, averageExistsTime);  
            
    }
            
    fclose(dataFileExists);

    return;
 }

void graphe_exists_abr(){
     // Générer le script gnuplot pour le tracé d'Union_tab
    FILE *gnuplotScriptExists = fopen("plot_script_exists_abr.gnu", "w");
    if (!gnuplotScriptExists) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour Exists_arbre");
        return ;
    }

    fprintf(gnuplotScriptExists, "set title 'Temps d Exists_arbre en fonction de la taille'\n");
    fprintf(gnuplotScriptExists, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptExists, "set yrange [1e-6:5e-6]\n");
    fprintf(gnuplotScriptExists, "set ylabel 'Temps d Exists_arbre (s)'\n");
    fprintf(gnuplotScriptExists, "plot 'time_data_exist_abr.txt' with linespoints title 'Exists_arbre'\n");



    fclose(gnuplotScriptExists);

    return;

}
