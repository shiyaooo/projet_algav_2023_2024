#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include "EX_3.h"

/*----------------------Q3.10------------------------*/
//les primitives pour tas binomiale
TournoisB* create_tournoisB(Cle_entier* cle){//O(1)
    TournoisB* noeud=(TournoisB*)malloc(sizeof(TournoisB));
    if(noeud==NULL){
        fprintf(stderr, "Erreur d'allocation de mémoire pour le noeud\n");
    }
    noeud->cle = cle;
    noeud->degre=0;
    noeud->enfant=malloc(sizeof(TournoisB)*noeud->degre);
    return noeud;
    
}

bool estVideTournoisB(TournoisB* t){//O(1)
    if(t) return false;
    else return true;
}


// Fonction pour fusionner deux arbres binomiaux de même degré
TournoisB* mergeFB_meme_degre(TournoisB* a, TournoisB* b) {
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }

    // Fusionner deux tas binomiaux de même degré
    if (inf(a->cle,b->cle)) {
        a->degre++; // Incrémenter le degré après la fusion
        a->enfant=realloc(a->enfant, a->degre*sizeof(TournoisB));
        a->enfant[a->degre-1]=*b;
        return a;
    } else {
        
        b->degre++; // Incrémenter le degré après la fusion
        b->enfant=realloc(b->enfant, b->degre*sizeof(TournoisB));
        b->enfant[b->degre-1]=*a;        
        return b;
    }
}





 void afficher_tournoisB(TournoisB* tb){//O(n)
    if(tb==NULL) {return ;}
    else{
        printf("%08x %08x %08x %08x\n",tb->cle->u4,tb->cle->u3,tb->cle->u2,tb->cle->u1);
        printf("degre: %d\n",tb->degre);
        for(int i=0; i<tb->degre; i++){
            afficher_tournoisB(&(tb->enfant[i]));
        }
    }
}



TB_Cell* Decapite_TB (TournoisB* tb){//O(degre)
    TB_Cell* fb=NULL;
    if(!tb){
        return NULL;
    }

    TournoisB* tmp=NULL;
    for(int i=0; i<tb->degre; i++){
        tmp=&(tb->enfant[i]);
        fb=InsererEnTete(tmp,fb);
    }
    free(tb);   
    return fb;
}

TB_Cell* InsererEnTete(TournoisB* tb, TB_Cell* tete) {//O(1)
    // Créer un nouveau nœud
    if(tete==NULL){
        return create_FileB(tb);
    }
    TB_Cell* nouveauFB = (TB_Cell*)malloc(sizeof(TB_Cell));
    if (nouveauFB == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser le nouveau nœud
    nouveauFB->tb = tb;
    nouveauFB->suiv = tete;

    // Mettre à jour la tête de la liste
    return nouveauFB;
}


//File Binomiale
bool estVideFilB(TB_Cell* fb){//O(1)
    if(fb==NULL) return true;
    else return false;
}

TB_Cell* create_FileB(TournoisB* tb){//O(1)
    TB_Cell* fb=(TB_Cell*)malloc(sizeof(TB_Cell));
    if (fb == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le File binomial\n");
        exit(EXIT_FAILURE);
    }
    fb->tb=tb;
    fb->suiv=NULL;
    return fb;
}

//inserer a la fin
TB_Cell* insert_in_FB(TournoisB* tb, TB_Cell* fb){//O(n)
    TB_Cell* tmp=fb;
    if(fb==NULL){
        return create_FileB(tb);
    }else{
        while(tmp->suiv){
            tmp=tmp->suiv;
        }
        tmp->suiv=create_FileB(tb);
    }
    //Trie(&fb);
    return fb;
}

TournoisB* degreMin_FilB(TB_Cell* fb){//O(1)
    //TournoisB* tb=create_tournoisB(fb->tb->cle);
    return fb->tb;
}


void Reste_FilB(TB_Cell** fb){//O(1)
    if (*fb == NULL) {
        // Si la liste est vide, rien à supprimer
        return;
    }

    // Sauvegarder la référence au nœud à supprimer
    //TournoisB* min= degreMin_FilB(*fb);
    TB_Cell* temp = *fb;

    // Mettre à jour la tête pour pointer vers le deuxième nœud
    *fb = (*fb)->suiv;

    // Libérer la mémoire du nœud supprimé
    free(temp);
}

void afficherFileB(TB_Cell* fb){//O(n)
    if(fb==NULL) return ;
    TB_Cell* fb_tmp=fb;
    int i=0;
    while(fb_tmp){
        printf("TB %d\n",i);
        afficher_tournoisB(fb_tmp->tb);
        //printf("\n");
        i++;
        fb_tmp = fb_tmp->suiv;
    }
    printf("il y a %d tb\n",i);
    return;
}

//Hypothese : le tournoi est de degre inferieur au MinDeg de la file
void AjoutMin_FB (TournoisB* tb, TB_Cell** fb){//O(1)
    TB_Cell* newFb=create_FileB(tb);
    if (newFb == NULL) {
        fprintf(stderr, "Échec de l'allocation de mémoire pour le nouveau nœud.\n");
        exit(EXIT_FAILURE);
    }
    newFb->suiv=*fb;
    *fb=newFb;

    return;
}

//trier la liste de TB avec leur degre
void Trie(TB_Cell** fb) {//O(n²)
    TB_Cell *sorted, *current;

    sorted = NULL;
    current = *fb;

    while (current != NULL) {
        TB_Cell* next = current->suiv;

        // Insérer le nœud courant dans la liste triée
        if (sorted == NULL || sorted->tb->degre >= current->tb->degre) {
            current->suiv = sorted;
            sorted = current;
        } else {
            TB_Cell* temp = sorted;
            while (temp->suiv != NULL && temp->suiv->tb->degre < current->tb->degre) {
                temp = temp->suiv;
            }
            current->suiv = temp->suiv;
            temp->suiv = current;
        }

        current = next;
    }

    *fb = sorted;
}


/*----------------------Q3.11------------------------*/


//Union
TB_Cell* Union_FilB(TB_Cell* fb1, TB_Cell* fb2){//O(log(n + m))
    return UFret(fb1,fb2,NULL);
}

TB_Cell* UFret(TB_Cell* fb1, TB_Cell* fb2, TournoisB* tb){//O(log(n + m))
    TB_Cell* fb;
    if (estVideTournoisB(tb)){
        if(estVideFilB(fb1)){
            return fb2;
        }
        if(estVideFilB(fb2)){
            return fb1;
        }else{
            TournoisB* t1=degreMin_FilB(fb1); 
            TournoisB* t2=degreMin_FilB(fb2);
            //TB_Cell* fb;
            if(t1->degre<t2->degre){
                Reste_FilB(&fb1);
                fb=Union_FilB(fb1,fb2);
                AjoutMin_FB(t1,&fb);
                return fb;
            }
            if(t2->degre<t1->degre){
                Reste_FilB(&fb2);
                fb=Union_FilB(fb2,fb1);
                AjoutMin_FB(t2,&fb);
                return fb;
            }
            if(t1->degre==t2->degre){
                Reste_FilB(&fb1);
                Reste_FilB(&fb2);
                return UFret(fb1,fb2,mergeFB_meme_degre(t1,t2)); 
            }        
        }
    }else{//tb pas vide
        if (estVideFilB(fb1)){
            return Union_FilB(create_FileB(tb),fb2);
        }
        if (estVideFilB(fb2)){
            return Union_FilB(create_FileB(tb),fb1);
        }else{
            TournoisB* t1=degreMin_FilB(fb1);
            TournoisB* t2=degreMin_FilB(fb2);
            if((tb->degre<t1->degre) && (tb->degre < t2->degre)){
                fb=Union_FilB(fb1,fb2);
                AjoutMin_FB(tb, &fb);
                return fb;
            }
            if(tb->degre == t1->degre && tb->degre == t2->degre){
                Reste_FilB(&fb1);
                Reste_FilB(&fb2);
                fb=UFret((fb1),fb2,mergeFB_meme_degre(t1,t2));
                AjoutMin_FB(tb,&fb);
                return fb;
            }
            if(tb->degre == t1->degre && tb->degre < t2->degre){
                Reste_FilB(&fb1);
                return UFret(fb1,fb2, mergeFB_meme_degre(t1,tb));
            }
            if(tb->degre < t1->degre && tb->degre == t2->degre){
                Reste_FilB(&fb2);
                return UFret(fb2,fb1,mergeFB_meme_degre(t2,tb));
            }
        }
    }
    return fb;
}

//Ajout 
TB_Cell* ajout_cle_FB(Cle_entier* cle, TB_Cell* fb){////O(log(n))
    TournoisB* tb = create_tournoisB(cle);
    TB_Cell* fb1 = create_FileB(tb);
    return Union_FilB(fb1,fb);
}

//Construction
TB_Cell* construction_FB(Ce_Cell* lcle){//O(n)
    TB_Cell* fb_res=NULL;
    Ce_Cell* lcle_tmp=lcle;
    while(lcle_tmp){
        fb_res = ajout_cle_FB(lcle_tmp->cle,fb_res);
        lcle_tmp = lcle_tmp->suiv;
    }
    return fb_res;
}

//SupprMin
TournoisB* findMinTB(TB_Cell* fb) {//O(log n) car il y log n arbre
    if ( fb== NULL) {
        return NULL;
    }

    TournoisB* min_TB = fb->tb;
    TB_Cell* current = fb->suiv;

    while (current != NULL) {
        if (inf(current->tb->cle, min_TB->cle)) {
            min_TB = current->tb;
        }
        current = current->suiv;
    }

    return min_TB;
}
void supp_TB_in_FB(TB_Cell** fb){//O(log n)
    TournoisB* tb_min= findMinTB(*fb);
    TB_Cell* temp = *fb;
    TB_Cell* prev = NULL;

    // Recherche de l'élément à supprimer
    while (temp && !eg(temp->tb->cle,tb_min->cle)) {
        prev = temp;
        temp = temp->suiv;
    }

     // Si l'élément n'est pas trouvé
    if (temp == NULL) {
        printf("Trouve pas min degre");
        return;
    }
    // Si l'élément à supprimer est en tête de liste
    if (prev == NULL) {
        *fb = temp->suiv;
    } else {
        prev->suiv = temp->suiv;
    }

    free(temp); // Libération de la mémoire de l'élément supprimé

    return ;
}

TB_Cell* SupprMin_FilB(TB_Cell* fb){//O(log n)
    if(!fb->tb){//fb->tb==NULL
        return NULL;
    }
    TournoisB* min_TB=findMinTB(fb);
    supp_TB_in_FB(&fb);
    TB_Cell* tmp =Decapite_TB(min_TB);
    return Union_FilB(fb,tmp);
}

/*----------------------Q3.12------------------------*/
double measureTime_cons_FB(TB_Cell* (*fun)(Ce_Cell*), Ce_Cell* data){
    clock_t start, end;
    start = clock();
    //printf(" \n");
    TB_Cell* fb= fun(data);
    end = clock();
    free(fb);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void Comparer_FB_Cons(int* sizes,int repetitions){
    int len=longueur(sizes);
    srand(time(NULL));

    FILE *dataFileCons = fopen("time_data_cons_filb.txt", "w");
    if (!dataFileCons) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }printf("hhh\n");

    // Répéter les mesures pour chaque taille
    for(int i=0; i < len ;i++){
        //printf("i=%d\n",i);
        int size=sizes[i];
        double totalConsTime = 0.0; 

        // Répéter les mesures plusieurs fois pour obtenir une moyenne
        for(int j=1; j<=repetitions; j++){
            // Générer des données aléatoires
            Ce_Cell* jeu_cles= NULL;
            
            // Liste de cle de chaque fichiee
            jeu_cles=read_file_cles(echanger_entier(j,size));    
            
            // Mesurer le temps de 
            totalConsTime += measureTime_cons_FB(construction_FB, jeu_cles);

            // Assurez-vous de libérer la mémoire allouée
            free_list_cle(jeu_cles);
        }
        
        double averageConsTime = totalConsTime / repetitions; 
        printf("aveCont= %f\n",averageConsTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileCons, "%d %f\n", size, averageConsTime);  
            
    }
            
    fclose(dataFileCons);

    return;
 }

void graphe_FB_Cons(){
    // Générer le script gnuplot pour le tracé de Construction_tab
    FILE *gnuplotScriptCons = fopen("plot_script_cons_filb.gnu", "w");
    if (!gnuplotScriptCons) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour construction_FB");
        return ;
    }

    fprintf(gnuplotScriptCons, "set title 'Temps de construction_FB en fonction de la taille'\n");
    fprintf(gnuplotScriptCons, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptCons, "set ylabel 'Temps de construction_FB (s)'\n");
    fprintf(gnuplotScriptCons, "plot 'time_data_cons_filb.txt' with linespoints title 'construction_FB'\n");

    fclose(gnuplotScriptCons);

    return;

}


/*----------------------Q3.13------------------------*/
double measureTime_union_FB(TB_Cell * (*function)(TB_Cell *, TB_Cell * ),TB_Cell * fb1, TB_Cell * fb2){
    clock_t start, end;
    TB_Cell* result;
    start = clock();
    result=function(fb1, fb2);
    end = clock();
    free(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void verf_FB_union(int *sizes, int *lnb, int repetitions){
    int len=longueur(sizes);
    int taille=longueur(lnb);
    srand(time(NULL));
    
    FILE *dataFileUnion = fopen("time_data_union_filb.txt", "w");
    if (!dataFileUnion) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }
    // Répéter les mesures pour chaque taille
    for(int i=0; i < len ;i++){
        //printf("i=%d\n",i);
        int size=sizes[i];
        printf("size=%d\n",size);
        double totalUnionTime = 0.0;

        // Répéter les mesures plusieurs fois pour obtenir une moyenne
        for(int j=0; j<repetitions; j++){
            // Générer des listes de cle de fichier
            int j1=(random() % 5) + 1;
            int i1=random()% taille;
            int n1=lnb[i1];

            int j2=(random() % 5) + 1;
            int i2=random()% taille;
            int n2=lnb[i2];

            
            while(((j1==j2) && (n1==n2)) || ((n1+n2)!=size) || (n2>size) || (n1>size)){
                j1=(random() % 5) + 1;
                i1=random()% taille;
                n1=lnb[i1];
                j2=(random() % 5) + 1;
                i2=random() % len;
                n2=lnb[i2];
            }

            printf("n1= %d\n",n1);
            char* f1=echanger_entier(j1,n1);

            printf("n2= %d\n",n2);
            char* f2=echanger_entier(j2,n2);

            Ce_Cell* jeu_cles1=read_file_cles(f1);
            Ce_Cell* jeu_cles2=read_file_cles(f2);
            // Mesurer le temps d'Union_tab
            TB_Cell* fb1 = construction_FB(jeu_cles1);
            TB_Cell* fb2 = construction_FB(jeu_cles2);
            //afficherFileB(fb2);
            //afficherFileB(tmp);
            totalUnionTime += measureTime_union_FB(Union_FilB, fb1, fb2);
            //printf("hhhhhhhhhhhhhhhhhhhhhhhh\n");

            //free(tas1);
            //free(tas2);
    
            
            // Assurez-vous de libérer la mémoire allouée
            //free_list_cle(jeu_cles1);
            //free_list_cle(jeu_cles2);
        }
        
        double averageUniontTime = totalUnionTime / repetitions;  
        printf("aveUnt= %.8f \n",averageUniontTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileUnion, "%d %.8f\n", size, averageUniontTime);  
            
    }
            
    fclose(dataFileUnion);

    return;
 }


void graphe_FB_un(){
     // Générer le script gnuplot pour le tracé d'Union_tab
    FILE *gnuplotScriptUnion = fopen("plot_script_union_filb.gnu", "w");
    if (!gnuplotScriptUnion) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour Union_FilB");
        return ;
    }

    fprintf(gnuplotScriptUnion, "set title 'Temps d Union_FilB en fonction de la taille'\n");
    fprintf(gnuplotScriptUnion, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptUnion, "set ylabel 'Temps d Union_FilB (s)'\n");
    fprintf(gnuplotScriptUnion, "set yrange [2.4e-6:7e-6]\n");
    fprintf(gnuplotScriptUnion, "set xrange [2000:180000]\n");
    fprintf(gnuplotScriptUnion, "plot 'time_data_union_filb.txt' with linespoints title 'Union_FilB'\n");



    fclose(gnuplotScriptUnion);

    return;

}