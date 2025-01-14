#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include "EX_2.h"

/*----------------------E2------------------------*/
/*----------------------Q2.4------------------------*/
//via arbre 
Tas_Min_arbre* create_tas_ab(Cle_entier* cle){
    Tas_Min_arbre* noeud=(Tas_Min_arbre*)malloc(sizeof(Tas_Min_arbre));
    if(noeud==NULL){
        fprintf(stderr, "Erreur d'allocation de mémoire pour le noeud\n");
    }
    noeud->cle = cle;
    noeud->fg=NULL;
    noeud->fd=NULL;
    noeud->pfd=1;
    return noeud;
}

int hauteur(Tas_Min_arbre* ab){
    if (ab==NULL)
        return 0;
    int hfg=hauteur(ab->fg);
    int hfd=hauteur(ab->fd);
    return 1 + (hfg > hfd ? hfg : hfd);
}

int taille(Tas_Min_arbre* ab){
    if(ab==NULL) return 0;
    int tfg=taille(ab->fg);
    int tfd=taille(ab->fd);
    return 1 + tfg + tfd ;
}

Cle_entier* copie_cle(Cle_entier* cle){
    Cle_entier* copie = create_cle_entier_init();
    copie->u1 = cle->u1;
    copie->u2 = cle->u2;
    copie->u3 = cle->u3;
    copie->u4 = cle->u4;
    return copie;
}

void afficherarbre(Tas_Min_arbre* tas){
    if(tas==NULL) {
        printf("L'arbre est vide.\n");
        return ;
    }
    int i;
    for (i=1; i < tas->pfd; i++)
    {
        printf("|___ ");
    }
 
    print_cle(tas->cle);
    if (tas->fd) afficherarbre(tas->fd);
    if (tas->fg) afficherarbre(tas->fg);
}

Tas_Min_arbre* ajout_case_libre(Tas_Min_arbre* tas, Cle_entier* cle, int h){ //O(log n)
    //printf("cle = %d , pfd = %d, noeud = %d\n",tas->cle,tas->pfd,valeur);
    Tas_Min_arbre* newtas;
    Tas_Min_arbre* noeud = create_tas_ab(cle);
    if(tas == NULL) return noeud; //h = 0
    if(tas->pfd == 1 && tas->fg == NULL && tas->fd == NULL){ //un seul noeud
        //Ajout au fils gauche
        if(eg(noeud->cle, tas->cle)) return tas;
        else if(inf(tas->cle, noeud->cle)){
            noeud -> pfd = noeud -> pfd +1 ;
            tas->fg = noeud;
            //printf("1ajout de %d dans fils gauche de %d\n",noeud->cle,tas->cle);
            return tas;
        }
        else{
            tas -> pfd = tas -> pfd +1 ;
            noeud->fg = tas;
            //printf("2ajout de %d dans fils gauche de %d\n",tas->cle,noeud->cle);
            return noeud;
        }
    }
    //printf("here\n");
    if(tas->pfd < h-1 ){
        //printf("noeud = %d,pfd=%d < %d-1\n",tas->cle,tas->pfd,h);
        newtas = tas->fg;
        newtas = ajout_case_libre(newtas,cle,h);
        if(newtas == NULL){
            //printf("here2\n");
            newtas = tas->fd;
            newtas = ajout_case_libre(newtas,cle,h);
            //printf("here6\n");
                if(newtas == NULL) return NULL;
                else {
                    //printf("here7\n");
                    //printf("3ajout de %d dans fils droit de %d\n",tas->cle,noeud->cle);
                    tas->fd = newtas;
                    return tas;
                }
        }
        else {
            //printf("4ajout de %d dans fils gauche de %d\n",tas->cle,noeud->cle);
            tas->fg = newtas;
            return tas;
        }
    }
    else if(tas->pfd == h-1){
        //printf("here3");
        if(tas->fg == NULL){
            //printf("5ajout de %d dans fils gauche de %d\n",noeud->cle,tas->cle);
            noeud -> pfd = tas -> pfd +1 ;
            tas->fg = noeud;
            return tas;
        }
        else if(tas->fd == NULL){
            //printf("6ajout de %d dans fils droit de %d\n",noeud->cle,tas->cle);
            noeud -> pfd = tas -> pfd +1 ;
            tas->fd = noeud;
            return tas;
        }
        else return NULL;
    }
    else return NULL;
}


Tas_Min_arbre* indices_arbre_desequilibrer(Tas_Min_arbre* tas){ // il y en a un seul car la fonction est appelé à chaque ajout //O(h)
    Tas_Min_arbre* autretas;
    
    if(tas==NULL) return NULL;
    if(tas->fg == NULL && tas->fd == NULL) return NULL;
    if(tas->fg != NULL){
        if(inf(tas->fg->cle,tas->cle)) return tas;
        else {
            autretas = indices_arbre_desequilibrer(tas->fg);
            if(autretas == NULL){
                if(tas->fd != NULL){
                    if(inf(tas->fd->cle, tas->cle)) return tas;
                    else{
                        autretas = indices_arbre_desequilibrer(tas->fd);
                        return autretas;
                    }
                }
                else return NULL;
            }
            else return autretas;
        }
    }
    else{
        if(tas->fd != NULL){
            if(inf(tas->fd->cle, tas->cle)) return tas;
            else{
                autretas = indices_arbre_desequilibrer(tas->fd);
                return autretas;
            }
        }
        else return NULL;
    }
}


Tas_Min_arbre* equilibrer_arbre(Tas_Min_arbre* tas){
    Tas_Min_arbre* newtas; // tas au niveau duquel il ya déséquilibre
    Tas_Min_arbre* fils_newtas; // le fils avec lequel il ya déséquilibre
    Cle_entier* cle_tmp; //cle temporaire pour échange
    newtas = indices_arbre_desequilibrer(tas);
    while(newtas){ // déséquilibre un fils plus petit que le père
        // recupéré le fils avec lequel il ya déséquilibre
        if(newtas -> fg){
            if(inf(newtas->fg->cle, newtas-> cle)){
                fils_newtas = newtas->fg;
                //printf("déséquilibre avec fils = %d\n", newtas ->fg->cle);
            }
            else{
                fils_newtas = newtas->fd;
                //printf("déséquilibre avec fils = %d\n", fils_newtas->cle);
            }
        }
        else {
            fils_newtas = newtas->fd;
            //printf("déséquilibre avec fils = %d\n", fils_newtas->cle);
        }
        
        //print_cle(newtas->cle);printf("échange avec fils = ");print_cle(fils_newtas->cle);
        cle_tmp = newtas->cle;
        newtas-> cle = fils_newtas->cle;
        fils_newtas->cle = cle_tmp;
        
        //nouvelle vérification
        newtas = indices_arbre_desequilibrer(tas);
        //afficherarbre(tas);
    }
    //printf("newtas vide...equilibrage terminé\n");
    return tas;
    
}

Tas_Min_arbre* ajout(Tas_Min_arbre* tas, Cle_entier* cle){
    int h = hauteur(tas);
    int taille_tas = taille(tas);
    if(taille_tas == pow(2,h)-1) h+=1;
    tas = ajout_case_libre(tas,cle,h); // valeur est ajouté à la premiere case vide
    //printf("tas après ajout simple de %d à la hauteur %d\n",valeur,h);
    //afficherarbre(tas);
    tas = equilibrer_arbre(tas);
    //afficherarbre(tas);
    return tas ;
}

Tas_Min_arbre* ajout_iteratifs(Tas_Min_arbre* tas, Ce_Cell* cles){
    Ce_Cell** cles_tmp = &cles;
    while(*cles_tmp){
        tas = ajout(tas,(*cles_tmp)->cle);
        (*cles_tmp) = (*cles_tmp)->suiv;
    }

    return tas;
}

Tas_Min_arbre* parent_dernier_element(Tas_Min_arbre* tas){ // O(log²(n))
    int htfg;
    int htfd;
    if(tas==NULL) return NULL;
    else if(tas->fg != NULL && tas->fd != NULL){
        htfg = hauteur(tas->fg);
        htfd = hauteur(tas->fd);
        if(htfg > htfd){
            if(tas->fg->fg && tas->fg->fd) return parent_dernier_element(tas->fg);
            else if(tas->fg->fg) return tas->fg;
            else return tas;
            
        }
        else{
            if(tas->fd->fg && tas->fd->fd) return parent_dernier_element(tas->fd);
            else if(tas->fg->fg) return tas->fg;
            else return tas;
        }
    }
    else if(tas->fg){
        if(tas->fg->fg == NULL && tas->fg->fd == NULL) {
            return tas;
        }
    }
    else return tas; //les deux fils sont nulls
}

//via arbre
//Complexité dans le pire des cas
/*
//SupprMin (Cours : complexité en O(log(n)) car on fait au plus h échanges
Notre tas binaire est basé sur un arbre binaire, il a donc une hauteur maximale de log2N avec N le nombre d'éléments du tas. Pour l'insertion d'un élément, on fait dans le pire des cas remonter le nœud jusqu'à la racine et donc on effectue log2N opérations. Pareil pour l'extraction du min/max, on fait dans le pire des cas log2N échanges, résultant dans les deux cas en une complexité en O(log2N).
 */

Tas_Min_arbre* supprMin(Tas_Min_arbre* tas){ // O(log(n))
    Tas_Min_arbre* par_dernier = parent_dernier_element(tas); // O(log²(n))
    if(tas == NULL) return NULL;
    else if(par_dernier->fd){
        tas->cle = par_dernier->fd->cle; // échange dernier-racine
        par_dernier->fd->cle = NULL;
        par_dernier->fd = NULL;
    }
    else if(par_dernier->fg){
        tas->cle = par_dernier->fg->cle; // échange dernier-racine
        par_dernier->fg->cle = NULL;
        par_dernier->fg = NULL;
    }
    else { 
        freeTas(tas);
        return NULL; 
    }
    tas = equilibrer_arbre(tas); // perlocate down depuis la racine O(log(n))
    return tas;
}


//via tableau :arr[i] ≤ arr[2i + 1] et arr[i] ≤ arr[2i + 2]
Tas_Min_tableau* initial_tab_tas(int capacite){ //O(1)
    Tas_Min_tableau* tas=(Tas_Min_tableau*)malloc(sizeof(Tas_Min_tableau));
    tas->capacite=capacite;
    tas->taille=0;
    tas->tab=(Cle_entier**)malloc(sizeof(Cle_entier*)*capacite);
    return tas;
}

void swap_tab(Cle_entier* a, Cle_entier* b){ //O(1)
    Cle_entier* tmp=create_cle_entier_init();
    tmp->u1 = a->u1;
    tmp->u2 = a->u2;
    tmp->u3 = a->u3;
    tmp->u4 = a->u4;

    a->u1 = b->u1;
    a->u2 = b->u2;
    a->u3 = b->u3;
    a->u4 = b->u4;
    
    b->u1 = tmp->u1;
    b->u2 = tmp->u2;
    b->u3 = tmp->u3;
    b->u4 = tmp->u4;
    free(tmp);
}

Cle_entier* getelm(Ce_Cell* lcle, int indice){//O(n)
    int i=0;
    Ce_Cell* lcp=lcle;
    while(lcle){
        //printf("i=%d\n",i);
        if(i==indice){
            return lcp->cle;
        }else{
            lcp=lcp->suiv;
            i++;
        }
    }
    return NULL;
}
void Ajout_Tab(Tas_Min_tableau* tas, Cle_entier* cle){ //O(log n)
    if(tas->taille>=tas->capacite){
        printf("Le tas est plein.\n");
        return;
    }
    //inserer la val à la fin du tab
    tas->tab[tas->taille] = cle;
    tas->taille +=1;
    int index=tas->taille-1;
    while(index > 0 && inf(tas->tab[index],tas->tab[(index-1)/2])){
        swap_tab(tas->tab[index],tas->tab[(index-1)/2]);
        index=(index-1)/2;
    }
}

int taille_lcle(Ce_Cell* lcle){ //O(n)
    Ce_Cell* tmp=lcle;
    int cpt=0;
    while(tmp){
        cpt++;
        tmp=tmp->suiv;
    }
    return cpt;
}

void Ajout_It_tab(Tas_Min_tableau* tas, Ce_Cell* lcle){ //O(nlogn)
    int rest=tas->capacite - tas->taille;
    Ce_Cell* tmp=lcle;
    while(tmp){
        if(rest>0){
            Ajout_Tab(tas,tmp->cle);
            rest--; 
        } 
        else{
            break;}
        tmp=tmp->suiv;
    }

}

void Affiche_Tab(Tas_Min_tableau* tas){ //O(n)
    for(int i=0; i<tas->taille; i++){
        print_cle(tas->tab[i]);
    }
}

void liberer_tab(Tas_Min_tableau* tas){ //O(n)
    for(int i=0; i<tas->taille; i++){
        free(tas->tab[i]);
    }
    free(tas);
}

void entasserMin(Tas_Min_tableau* tas, int indice){ //O(log n)
    int plusPetit=indice;
    int gauche=2*indice+1;
    int droite=2*indice+2;
    if(gauche<tas->taille && inf(tas->tab[gauche],tas->tab[plusPetit])){
        plusPetit=gauche;
    }
    if(droite<tas->taille && inf(tas->tab[droite],tas->tab[plusPetit])){
        plusPetit=droite;
    }
    if(plusPetit!=indice){
        swap_tab(tas->tab[indice],tas->tab[plusPetit]);
        entasserMin(tas, plusPetit);
    }
    return;
}

Cle_entier* SupprMin(Tas_Min_tableau* tas){ //O(log n)
    if(tas->taille<=0){
        fprintf(stderr,"Le tas est vide, impposible de supprimer l'élément mininmun");
        exit(EXIT_FAILURE);
    }
    Cle_entier* elemin;
    elemin=tas->tab[0];
    tas->tab[0]=tas->tab[tas->taille-1];
    tas->taille--;
    entasserMin(tas,0);
    return elemin;
}

/*----------------------Q2.5------------------------*/
//via arbre
//un pseudo-code
/*Fonction construction(cles):
    taille = Longueur(cles)
    tas_res = tasVide : résultat de la construction
    
    tas_sous_arbre = tableauVide : tableau de sous arbre (tableau car le nombre de sous arbre est connu)
    nb_sous_arbre = pointeurEntier : pointeur, car le nombre de sous arbre varient au cours de la construction en fonction de la profondeur à laquelle on travaille
    *nb_sous_arbre = 0 : aucun sous-arbre crée

    lcle_inc = listeVide : pointeur sur la liste de clés, sur les éléments qui qui rendent le tas incomplet
    lcle_fils = listeVide : pointeur sur la liste de clés, sur les éléments qui seront utilisé pour formé les premiers sous abres
    lcle_sommets = listeVide : pointeur sur la liste de clés, sur les éléments qui seront utilisé comme sommets des sous arbres
    
    nb_elem_inc = 0 : nombre d'element qui rendent l'arbre incomplet
    nb_elem = 0 : nombre d'element qui formeront les premiers sous arbres
    id_dernier_sommet = 0 : indice du dernier element utilisé pour former les premiers sous-arbres, ensuite viennent les sommets
    n=0 : puissance de 2 qui correspond au tas complet (tas sans les nb_elem_inc)
    
    # Cas particulier taille ∈ {0,1,2}
    Si (taille==0) Alors 
        Retourner TasVide
    FinSI

    Si (taille==1) Alors 
        tas_res = creer_tas(lcle->cle); 
        Retourner TasVide
    FinSI

    Si (taille==2) Alors 
        tas_res = creer_tas(lcle->cle) 
        lcle = lcle->suiv //on recupère la seconde clé
        tas_res->fg = creer_tas(lcle->cle)
        tas_res = equilibrer_arbre(tas_res) // O(taille)
        Retourner tas_res
    FinSI

    #Initialisation de n 
    Tant que (taille >= pow(2,n)-1) Faire
        n := n+1
    FinTantQue

    n := n-1
    
    #Initialisation
    nb_elem_inc := taille-(pow(2,n)-1)
    nb_elem := ((taille-nb_elem_inc)/2)+1 // la moitier des valeurs parmis les valeurs restantes est utilisée comme premiers sommets des premiers sous arbres
    
    #Initialisation de la tab des premiers sous arbres
    tab_sous_arbre := (typeof(tab_sous_arbre))malloc(nb_elem*sizeof(*tab_sous_arbre))

    #Initialisation du pointeur sur les fils
    Pour j allant de 0 à nb_elem_inc : //on saute les elements qui rendent l'arbre incomplet
        lcle_fils = lcle_fils->suiv
    FinPour

    i = nb_elem_inc;
    id_dernier_fils = nb_elem+nb_elem_inc


    Tant que (i < id_dernier_fils) Faire

        #Initialisation des premiers sous arbre (sommets)
        cle_tmp = lcle_fils->cle; //un fils est utilisé comme sommet d'un sous arbre
        tas_tmp = create_tas_ab(lcle_fils->cle);

        #Initialisation des feuilles des premiers sous arbres
        Si (nb_elem_inc>0) Alors  // on prend une des valeurs parmis les nb_elem_inc
            cle_tmp = lcle_inc->cle 
            tas_tmp->fg = creer_tas(cle_tmp)
            tas_tmp->fg->pfd = n+1
            nb_elem_inc-=1
            lcle_inc = lcle_inc->suiv
        Fin Si

        Si (nb_elem_inc>0) Alors // on a une valeur pour un fils droit
            cle_tmp = lcle_inc->cle
            tas_tmp->fd = creer_tas(cle_tmp)
            tas_tmp->fd->pfd = n+1
            nb_elem_inc-=1
            lcle_inc = lcle_inc->suiv
        Fin Si

        #Initialisation de la profondeur des premiers sous arbre
        tas_tmp->pfd = n;

        #Initialisation du tableau de sous arbre : Ajout du sous arbre 
        tab_sous_arbre[*nb_sous_tas] = tas_tmp
        *nb_sous_tas = *nb_sous_tas+1

        #Initialisation du pointeur et de l'index
        lcle_fils = lcle_fils->suiv
        i+=1
    FinTantQue

    #Initialisation du pointeur sur les sommets 
    k=0
    Pour k allant de 0 à i: // on va a lcle+nb_elem+nb_elem_inc
        lcle_sommets = lcle_sommets->suiv
        i-=1
    FinPour

    Tant que (tab_sous_arbre) Faire
        tab_sous_arbre = construction_sous_arbre(tab_sous_arbre, nb_sous_tas, lcle_sommets) // on construit de nous sous arbre à partir des premiers
        Si (*nb_sous_arbre == 1) Alors
            break // on a construit un seul arbre à partir des sous arbre
    FInTantQue

    tas_res = tab_sous_arbre[0]
    tas_res = equilibrer_arbre(tas_res) //percolate_down depuis la racine complexité en O(log(n))
    Retourner tas_res;
}



Fonction construction_sous_arbre(Tas_Min_arbre** tab_sous_arbre, int* nb_sous_arbre,Ce_Cell* lcle_sommets){
    id_sous_tas = 0 //index sur les sous tas
    taille_tab = *nb_sous_arbre/2 // nombre de sous arbre obtenu après avoir uni les précédent deux par deux
    tab_sous_arbre_res = NULL //tableau de sous arbre résultant
    nb_sous_arbre_res = 0 // nombre de sous arbre résultant

    Si (*nb_sous_arbre==1) Alors 
        Retourner tab_sous_arbre // on a deja obtenu un seul arbre
    
    #Initialisation du tableau de sous arbre résultant
    tab_sous_arbre_res = (typeof(tab_sous_arbre_res))malloc(taille_tab*sizeof(*tab_sous_arbre_res));
    
    Tant que (taille_tab>0) Faire

        #Initialisation des sous arbres
        #sommet
        sommet_tmp = lcle_sommets->cle;
        tas_tmp = create_tas_ab(sommet_tmp);

        #Ajout fils
        tas_tmp->fg = tab_sous_arbre[id_sous_tas]
        tas_tmp->fd = tab_sous_arbre[id_sous_tas+1]

        //profondeurs
        tas_tmp->pfd = tas_tmp->fg->pfd-1
        tas_tmp->pfd = tas_tmp->fd->pfd-1

        #Initialisation du tableau de sous arbre : Ajout du sous arbre 
        tab_sous_arbre_res[nb_sous_arbre_res] = tas_tmp
        nb_sous_arbre_res+=1

        #Initialisation des sommets
        lcle_sommets = lcle_sommets->suiv; 
        
        #Initialisation de l'indice sur les sous arbre
        id_sous_tas+=2;

        #Initialisation du nombre de sous arbre à traité
        taille_tab-=1;
   FinTantQue

    //Initialisation du nombre de sous_arbre
    *nb_sous_arbre = nb_sous_arbre_res
    
    Retourner tab_sous_arbre_res;
}
*/
Tas_Min_arbre** construction_sous_arbre(Tas_Min_arbre** tab_sous_arbre, int* nb_sous_arbre,Ce_Cell** lcle_sommets){
    int id_sous_tas = 0;
    Tas_Min_arbre* tas_tmp = NULL;
    Cle_entier* sommet_tmp = NULL;
    int taille_tab = *nb_sous_arbre/2; // nombre de sous arbre unifier pour en faire des arbres
    Tas_Min_arbre** tab_sous_arbre_res = NULL; 
    int nb_sous_arbre_res = 0;
    //printf("id sommet %d\n",*id_sommets);
    //printf("nb sous arbre à l'arrivé  %d\n",*nb_sous_arbre);
    if(*nb_sous_arbre==1) return tab_sous_arbre;   
    tab_sous_arbre_res = (typeof(tab_sous_arbre_res))malloc(taille_tab*sizeof(*tab_sous_arbre_res));
    while(taille_tab>0){
        //printf("tour %d sommet = %d\n",id_sous_tas, *id_sommets);
        sommet_tmp = (*lcle_sommets)->cle;
        tas_tmp = create_tas_ab(sommet_tmp);
        tas_tmp->fg = tab_sous_arbre[id_sous_tas];
        tas_tmp->pfd = tas_tmp->fg->pfd-1;
        tas_tmp->fd = tab_sous_arbre[id_sous_tas+1];
        tas_tmp->pfd = tas_tmp->fd->pfd-1;
        tab_sous_arbre_res[nb_sous_arbre_res] = tas_tmp;
        
        (*lcle_sommets) = (*lcle_sommets)->suiv; 
        nb_sous_arbre_res+=1;
        id_sous_tas+=2;
        taille_tab-=1;
    }
    *nb_sous_arbre = nb_sous_arbre_res;
    //printf("lengh liste tas res = %d\n", nb_sous_arbre_res);
    
    return tab_sous_arbre_res;
}

Tas_Min_arbre* construction(Ce_Cell* lcle){
    int taille = taille_lcle(lcle);
    Tas_Min_arbre* tas_res = NULL; //resultat
    Cle_entier* cle_tmp = NULL;
    Tas_Min_arbre* tas_tmp = NULL; //
    Tas_Min_arbre** tab_sous_arbre = NULL; 
    int* nb_sous_arbre = malloc(sizeof(int));
    Ce_Cell* lcle_tmp = lcle; // pointeurs sur la liste de cle
    Ce_Cell* lcle_inc = lcle; //pointeur sur les cles du tas qui le rendent incomplet
    Ce_Cell* lcle_fils = lcle; //pointeur sur les cles qui vont formées les premiers arbres
    Ce_Cell* lcle_sommets = lcle; //pointeur sur les cles qui vont formées des sommets
    int i=0;
    int nb_elem = 0; // le nombre d'element utilisé pour formé les premiers arbre
    int nb_elem_inc = 0; // le nombre d'élement qui rendent l'arbre incomplet
    int id_dernier_fils = 0; // indice du dernier element utilisé pour formé les premier arbre fils
    int n = 0; //puissance de 2 corespondant à la taille de l'arbre parfait
    *nb_sous_arbre = 0;
    if(taille == 0) return NULL;
    if(taille == 1){
        cle_tmp = lcle_tmp->cle;
        tas_res = create_tas_ab(cle_tmp);
        return tas_res;
    }
    if(taille == 2){
        cle_tmp = lcle_tmp->cle;
        tas_res = create_tas_ab(cle_tmp);

        lcle_tmp = lcle_tmp->suiv;
        cle_tmp = lcle_tmp->cle;
        tas_res->fg = create_tas_ab(cle_tmp);

        if(inf(tas_res->fg->cle, tas_res->cle)){ // clé du fils plus petite que celle du père
            cle_tmp = tas_res->cle;
            tas_res->cle = tas_res->fg->cle;

            tas_res->fg->cle = cle_tmp;
        }
        tas_res->fg->pfd = tas_res->pfd+1;
        return tas_res;
    }
    while(taille >= pow(2,n)-1) n+=1;
    n-=1;
    //printf("n = %d\n",n);
    nb_elem_inc = taille-(pow(2,n)-1);
    nb_elem = ((taille-nb_elem_inc)/2)+1; // la moitier des valeurs parmis les valeurs restantes est utilisée comme fils

    //printf("nb_elem = %d\n",nb_elem);
    //printf("nb_elem_inc = %d\n",nb_elem_inc);
    tab_sous_arbre = (typeof(tab_sous_arbre))malloc(nb_elem*sizeof(*tab_sous_arbre));

    i = nb_elem_inc; //on saute les elements qui rendent l'arbre incomplet
    for(int j=0; j<nb_elem_inc;j++)// on va a lcle+nb_elem_inc
        lcle_fils = lcle_fils->suiv;

    id_dernier_fils = nb_elem+nb_elem_inc;
    while(i<id_dernier_fils){
        //printf("tour %d\n",i-nb_elem_inc);
        cle_tmp = lcle_fils->cle;
        tas_tmp = create_tas_ab(cle_tmp);
        if(nb_elem_inc>0){ // on prend une des valeurs parmis les nb_elem_inc
            cle_tmp = lcle_inc->cle;
            tas_tmp->fg = create_tas_ab(cle_tmp);
            tas_tmp->fg->pfd = n+1;
            nb_elem_inc-=1;
            lcle_inc = lcle_inc->suiv;
        }
        if(nb_elem_inc>0){ 
            cle_tmp = lcle_inc->cle;
            tas_tmp->fd = create_tas_ab(cle_tmp);
            tas_tmp->fd->pfd = n+1;
            nb_elem_inc-=1;
            lcle_inc = lcle_inc->suiv;
        }
        tas_tmp->pfd = n;
        tab_sous_arbre[*nb_sous_arbre] = tas_tmp; 
        *nb_sous_arbre = *nb_sous_arbre+1;
        lcle_fils = lcle_fils->suiv;
        i+=1;
    }
    for(int k=0; k<i;k++)// on va a lcle+nb_elem_inc
        lcle_sommets = lcle_sommets->suiv;

    while(tab_sous_arbre){
        tab_sous_arbre = construction_sous_arbre(tab_sous_arbre, nb_sous_arbre, &lcle_sommets);
        if(*nb_sous_arbre == 1) break;
    }
    tas_res = tab_sous_arbre[0];
    tas_res = equilibrer_arbre(tas_res); //percolate_down depuis la racine complexité en O(log(n))
    free(tab_sous_arbre);
    return tas_res;
}

//via tableau
//un pseudo-code
/*Fonction Construction_tab(cles):
    taille = Longueur(cles)

    # Commencer à partir du premier indice non-feuille (le dernier indice avec des enfants)
    debut = (taille - 2) / 2
    
    # Initialiser le tas avec la longueur de clés
    tas = initial_tab_tas(taille)
    creer un tableau de element
    i=0
    Tant que lcle Non NULL:
        tas->tab[i]=lcle->cle
        i=i+1 
        lcle=lcle->next

    # Effectuer des remontées à partir du dernier indice non-feuille jusqu'à la racine
    Pour i de debut à 0:
        Remonter(tas->tab, i, taille)
    tas->taille=taille
    Retourner tas

Fonction Remonter(tab, indice, taille):
    temp = tab[indice]
    enfant = 2 * indice + 1

    Tant que enfant < taille:
        # Comparer avec le plus petit enfant
        Si enfant + 1 < taille et tab[enfant + 1] < tab[enfant]:
            enfant = enfant + 1

        # Si le plus petit enfant est plus petit que temp, le déplacer vers le haut
        Si tab[enfant] < temp:
            tab[indice] = tab[enfant]
            indice = enfant
            enfant = 2 * indice + 1
        Sinon, arrêter la boucle

    # Placer temp à la position correcte dans le tas
    tas[indice] = temp
*/


Tas_Min_tableau* Construction_tab(Ce_Cell* lcle){ //O(n)
    int taille=taille_lcle(lcle);
    int indice=(taille-2)/2;
    Tas_Min_tableau* tas=initial_tab_tas(taille);
    Ce_Cell* tmp=lcle;
    int i=0;
    while(tmp){
        tas->tab[i]=tmp->cle;
        tmp=tmp->suiv;
        i++;
    }

    for(int i=indice; i>=0; --i){
        remonter(tas->tab,i, taille);
    }
    tas->taille=taille;
    //tas->lcle=lcle;
    return tas;
}
void remonter(Cle_entier** tab, int indice, int taille){ //O(log n)
    Cle_entier* tmp= tab[indice];
    Cle_entier* nv=create_cle_entier_init();
    nv->u1=tmp->u1;
    nv->u2=tmp->u2;
    nv->u3=tmp->u3;
    nv->u4=tmp->u4;
    //printf("tmp av: %u %u %u %u\n",tmp->u1,tmp->u2, tmp->u3, tmp->u4 );
    //printf("nv av: %u %u %u %u\n",nv->u1,nv->u2, nv->u3, nv->u4 );
    int in_enfant=2* indice+1;
    //printf("indice=%d, enf=%d\n", indice,in_enfant);
    while(in_enfant<taille){
        if(in_enfant+1 < taille && inf(tab[in_enfant+1],tab[in_enfant])){
            in_enfant=in_enfant+1;
           //printf("in_enfant: %d\n",in_enfant);
        }
        if(inf(tab[in_enfant],tab[indice])){ 
            tab[indice]->u1=tab[in_enfant]->u1;
            tab[indice]->u2=tab[in_enfant]->u2;
            tab[indice]->u3=tab[in_enfant]->u3;
            tab[indice]->u4=tab[in_enfant]->u4;
            indice=in_enfant;
            in_enfant=2*indice+1;
        }else{break;}
    } 
    //printf("tmp ap: %u %u %u %u\n",tmp->u1,tmp->u2, tmp->u3, tmp->u4 );
    //printf("nv ap: %u %u %u %u\n",nv->u1,nv->u2, nv->u3, nv->u4 );
    tab[indice]->u1=nv->u1;
    tab[indice]->u2=nv->u2;
    tab[indice]->u3=nv->u3;
    tab[indice]->u4=nv->u4;
    free(nv);
}


/*----------------------Q2.6------------------------*/
/*----------------------Q2.6------------------------*/
//via arbre
//un pseudo code
/*

    Fonction tas_en_liste(tas,lcle):
        Si (tas==NULL) Alors 
            Retourner 
        FinSI
        
        (*lcle)->cle = tas->cle // recuperer la cle du tas
        
        Si (tas->fg!=NULL) Alors 
            (*lcle)->suiv = create_cell_cle(NULL) // alloue la queue de liste pour une insertion
            (*lcle) = (*lcle)->suiv;
            Retourner tas_en_liste(tas->fg,(lcle));
        FinSI
        Si (tas->fg!=NULL) Alors 
            (*lcle)->suiv = create_cell_cle(NULL) // alloue la queue de liste pour une insertion
            (*lcle) = (*lcle)->suiv;
            Retourner tas_en_liste(tas->fg,(lcle));
        FinSI

    --------------------------------------------------------

    Fonction unionTas(tas1,tas2):
        union_tas = résultat de l'union
        lcle = create_cell_cle(NULL) : allocation d'une liste pour recuperer les cles
        lcle_tmp = lcle : pointeur sur la liste qui sera construite

        Si (tas1==NULL) Alors 
            Retourner tas2
        FinSI

        Si (tas2==NULL) Alors 
            Retourner tas1
        FinSI
        
        tas_en_liste(tas1,&lcle_tmp) // on recupere les cles du tas1 en 0(taille(tas1))
        lcle_tmp->suiv = create_cell_cle(NULL) //  lcle_tmp possede une cle, on alloue la queue de liste, on insere dans la queue
        lcle_tmp = lcle_tmp->suiv
        tas_en_liste(tas2,&lcle_tmp) // on recupere les cles du tas2 en 0(taille(tas2))
        
        union_tas = construction(lcle) // on construit le tas en 0(taille(tas1)+taille(tas2))
    
        Retourner union_tas;
*/
void tas_en_liste(Tas_Min_arbre* tas, Ce_Cell** lcle){
    if(tas == NULL) return;
    (*lcle)->cle = tas->cle;
    if(tas->fg){
        (*lcle)->suiv = create_cell_cle(NULL);
        (*lcle) = (*lcle)->suiv;
        tas_en_liste(tas->fg,(lcle));
    }
    if(tas->fd){
        (*lcle)->suiv = create_cell_cle(NULL);
        (*lcle) = (*lcle)->suiv;
        tas_en_liste(tas->fd,(lcle));
    }
    return ;
}

Tas_Min_arbre* unionTas(Tas_Min_arbre* tas1, Tas_Min_arbre* tas2){
    Tas_Min_arbre* union_tas = NULL;
    Ce_Cell* lcle = create_cell_cle(NULL);
    Ce_Cell* lcle_tmp = lcle;
    if(tas1 == NULL)return tas2;
    if(tas2 == NULL)return tas1;
    
    tas_en_liste(tas1,&lcle_tmp); // on recupere les cles du tas1 en 0(taille(tas1))
    lcle_tmp->suiv = create_cell_cle(NULL);
    lcle_tmp = lcle_tmp->suiv;
    tas_en_liste(tas2,&lcle_tmp); // on recupere les cles du tas2 en 0(taille(tas2))
    union_tas = construction(lcle); // on construit le tas en 0(taille(tas1)+taille(tas2))
    return union_tas;
}

void freeTas(Tas_Min_arbre* tas){
    if(tas==NULL) return;
    free(tas->fg);
    free(tas->fd);
    free(tas);
    tas=NULL;
    return;
}

//via tableau
//un pseudo-code
/*Fonction Union_tab(tas1, tas2):
    taille = tas1->taille + tas2->taille

    # Creer une nouvelle liste tels que fusion les 2 tab de tas 
    tab= fusion(tas1->tab, tas1->taille, tas2->tab,  tas2->taille)
    
    # Initialiser un tas avec la longueur de lcle
    tas = initial_tab_tas(taille)
    tas->tab=tab
    # Réorganiser le tas fusionné pour s'assurer qu'il satisfait la propriété du tas min
    Pour i de (taille-2)/2 à 0:
        Remonter(cles, i, taille)
    tas->taille=taille
    Retourner tas

Fonction fusion(tab1, n1, tab2, n2):
    # Creer une nouvelle tableau de cle
    tab[n1+n2]

    #concatener tab1 et tab2
    tab=tab1+tab2

    Retourner lcle
*/

Tas_Min_tableau* Union_tab(Tas_Min_tableau* tas1, Tas_Min_tableau* tas2){ //O(m+n)
    int taille=tas1->taille+tas2->taille;
    Cle_entier** tab=fusion(tas1->tab,tas1->taille, tas2->tab, tas2->taille);
    //print_list_cle(lcle);
    Tas_Min_tableau *tas=initial_tab_tas(taille);
    tas->tab=tab;
    for(int i=(taille-2)/2; i>=0; i--){
        remonter(tas->tab, i, taille);
    }
    tas->taille=taille;
    //tas->lcle=lcle;
    //printf("tas->lcl:\n");
    return tas;
}

Cle_entier **fusion(Cle_entier **T1, int n1, Cle_entier **T2, int n2) { //O(n1+n2)
    Cle_entier **T = (Cle_entier **)malloc((n1 + n2) * sizeof(Cle_entier *));

    // Copier les éléments de T1 dans T
    for (int i = 0; i < n1; i++) {
        T[i] = T1[i];
    }

    // Copier les éléments de T2 dans T à partir de l'index n1
    for (int i = 0; i < n2; i++) {
        T[n1 + i] = T2[i];
    }

    return T;
}


/*----------------------Q2.8------------------------*/
// Fonction pour mesurer le temps d'exécution d'une fonction donnée
int longueur(int* l){
    int i=0;
    int cpt=0;
    
    while(l[i]!=0){
            cpt++;
            i++;
    }
    return cpt;
}

char* echanger_entier(int k, int nb){
    char* fs=(char*)malloc(sizeof(char)*100);
    strcpy(fs, "./cles_alea/jeu_");
    char c=k+'0';
    strcat(fs, &c);
    fs[17]='\0';
    strcat(fs,"_nb_cles_");
    char cp[8];
    sprintf(cp, "%d", nb);
    //printf("cp= %s\n",cp);
    strcat(fs,cp);
    strcat(fs,".txt");
    //printf("fs=%s\n",fs);
    fs[strlen(fs)]='\0';
    return fs;
}
//via arbre
double measureTime_ajout_it(Tas_Min_arbre* (*function)(Tas_Min_arbre*, Ce_Cell*), Tas_Min_arbre* tas,Ce_Cell* data){
    clock_t start, end;
    start = clock();
    function(tas,data);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double measureTime_cons_ab(Tas_Min_arbre * (*function)(Ce_Cell*),Ce_Cell* data){
    clock_t start, end;
    start = clock();
    function(data);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void Comparer_arbre(int* sizes,int repetitions){
    int len=longueur(sizes);
    srand(time(NULL));
    FILE *dataFileAjout = fopen("time_data_ajout_iteratif_arbre.txt", "w");
    if (!dataFileAjout) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }

    FILE *dataFileCons = fopen("time_data_cons_arbre.txt", "w");
    if (!dataFileCons) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }
    // Répéter les mesures pour chaque taille
    for(int i=0; i < len ;i++){
        int size=sizes[i];
        double totalAjoutItTime = 0.0;
        double totalConsTime = 0.0; 

        // Répéter les mesures plusieurs fois pour obtenir une moyenne
        for(int j=1; j<=repetitions; j++){
            // Générer des données aléatoires
            Ce_Cell* jeu_cles= NULL;
            
            // Liste de cle de chaque fichiee
            jeu_cles=read_file_cles(echanger_entier(j,size));

            // Mesurer le temps d'Ajout_It_tab
            Tas_Min_arbre* tasAjout = NULL;
            totalAjoutItTime += measureTime_ajout_it(ajout_iteratifs, tasAjout, jeu_cles);
            //liberer_tab(tasAjout);
    
            
            // Mesurer le temps de Construction_tab
            totalConsTime += measureTime_cons_ab(construction, jeu_cles);
            
            // Assurez-vous de libérer la mémoire allouée
            free_list_cle(jeu_cles);
        }
        
        double averageAjoutItTime = totalAjoutItTime / repetitions;  
        double averageConsTime = totalConsTime / repetitions; 
        printf("aveAjt= %f, aveCont= %f\n",averageAjoutItTime,averageConsTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileAjout, "%d %f\n", size, averageAjoutItTime);
        fprintf(dataFileCons, "%d %f\n", size, averageConsTime);  
            
    }
            
    fclose(dataFileAjout);
    fclose(dataFileCons);

    return;
 }

void graphe_arbre(){
// Générer le script gnuplot pour le tracé d'Ajout_It_tab
    FILE *gnuplotScriptAjout = fopen("plot_script_ajout_It_arbre.gnu", "w");
    if (!gnuplotScriptAjout) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour ajout_It_arbre");
        return ;
    }

    fprintf(gnuplotScriptAjout, "set title 'Temps d Ajout_It_arbre en fonction de la taille'\n");
    fprintf(gnuplotScriptAjout, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptAjout, "set ylabel 'Temps d Ajout_It_arbre (s)'\n");
    fprintf(gnuplotScriptAjout, "plot 'time_data_ajout_iteratif_arbre.txt' with linespoints title 'Ajout_It_arbre'\n");

    // Générer le script gnuplot pour le tracé de Construction_tab
    FILE *gnuplotScriptCons = fopen("plot_script_cons_arbre.gnu", "w");
    if (!gnuplotScriptCons) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour Construction_arbre");
        return ;
    }
    fprintf(gnuplotScriptCons, "set title 'Temps de Construction_arbre en fonction de la taille'\n");
    fprintf(gnuplotScriptCons, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptCons, "set ylabel 'Temps de Construction_arbre (s)'\n");
    fprintf(gnuplotScriptCons, "plot 'time_data_cons_arbre.txt' with linespoints title 'Construction_arbre'\n");
    
    // Générer le script gnuplot pour le tracé d'Ajout_It_tab et le tracé de Construction_tab
    FILE* gnuplotScriptCompare=fopen("plot_comparer_ab.gnu","w");
    if (!gnuplotScriptCompare) {
        perror("Erreur lors de l'ouverture du script Gnuplot ");
        return ;
    }
    fprintf(gnuplotScriptCompare, "set title 'Temps d executee en fonction de la taille'\n");
    fprintf(gnuplotScriptCompare, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptCompare, "set ylabel 'Temps d executee(s)'\n");
    fprintf(gnuplotScriptCompare, "plot 'time_data_ajout_iteratif_arbre.txt' with linespoints title 'Ajout_It_arbre',");
    fprintf(gnuplotScriptCompare,"'time_data_cons_arbre.txt' with linespoints title 'Construction_arbre'\n");

    fclose(gnuplotScriptAjout);
    fclose(gnuplotScriptCons);
    fclose(gnuplotScriptCompare);

    return;

}

//via tableau
double measureTime_it(void (*function)(Tas_Min_tableau*, Ce_Cell*), Tas_Min_tableau* tas,Ce_Cell* data){
    clock_t start, end;
    start = clock();
    function(tas,data);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double measureTime_cons(Tas_Min_tableau * (*function)(Ce_Cell*),Ce_Cell* data){
    clock_t start, end;
    start = clock();
    function(data);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void Comparer_tab(int* sizes,int repetitions){
    int len=longueur(sizes);
    srand(time(NULL));
    FILE *dataFileAjout = fopen("time_data_ajout_tab.txt", "w");
    if (!dataFileAjout) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }

    FILE *dataFileCons = fopen("time_data_cons_tab.txt", "w");
    if (!dataFileCons) {
        perror("Erreur lors de l'ouverture du fichier");
        return ;
    }
    // Répéter les mesures pour chaque taille
    for(int i=0; i < len ;i++){
        //printf("i=%d\n",i);
        int size=sizes[i];
        double totalAjoutTime = 0.0;
        double totalConsTime = 0.0; 

        // Répéter les mesures plusieurs fois pour obtenir une moyenne
        for(int j=1; j<=repetitions; j++){
            // Générer des données aléatoires
            Ce_Cell* jeu_cles= NULL;
            
            // Liste de cle de chaque fichiee
            jeu_cles=read_file_cles(echanger_entier(j,size));

            // Mesurer le temps d'Ajout_It_tab
            Tas_Min_tableau* tasAjout = initial_tab_tas(size);
            totalAjoutTime += measureTime_it(Ajout_It_tab, tasAjout, jeu_cles);
            //liberer_tab(tasAjout);
    
            
            // Mesurer le temps de Construction_tab
            totalConsTime += measureTime_cons(Construction_tab, jeu_cles);
            
            // Assurez-vous de libérer la mémoire allouée
            free_list_cle(jeu_cles);
        }
        
        double averageAjoutTime = totalAjoutTime / repetitions;  
        double averageConsTime = totalConsTime / repetitions; 
        //printf("aveAjt= %f, aveCont= %f\n",averageAjoutTime,averageConsTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileAjout, "%d %f\n", size, averageAjoutTime);
        fprintf(dataFileCons, "%d %f\n", size, averageConsTime);  
            
    }
            
    fclose(dataFileAjout);
    fclose(dataFileCons);

    return;
 }

void graphe_tab(){
     // Générer le script gnuplot pour le tracé d'Ajout_It_tab et le tracé de Construction_tab
    FILE* gnuplotScriptCompare=fopen("plot_comparer.gnu","w");
    if (!gnuplotScriptCompare) {
        perror("Erreur lors de l'ouverture du script Gnuplot");
        return ;
    }
    fprintf(gnuplotScriptCompare, "set title 'Temps d executee en fonction de la taille'\n");
    fprintf(gnuplotScriptCompare, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptCompare, "set ylabel 'Temps d executee(s)'\n");
    //fprintf(gnuplotScriptCompare, "set yrange [1e-6:1e-1]\n");
    //fprintf(gnuplotScriptCompare, "set ytics ('10^{-6}' 1e-6, '10^{-5}' 1e-5, '10^{-4}' 1e-4, '10^{-3}' 1e-3, '10^{-2}' 1e-2, '10^{-1}' 1e-1)\n");   
    fprintf(gnuplotScriptCompare, "plot 'time_data_ajout_tab.txt' with linespoints title 'Ajout_It_tab',");
    fprintf(gnuplotScriptCompare,"'time_data_cons_tab.txt' with linespoints title 'Construction_tab'\n");

    fclose(gnuplotScriptCompare);

    return;

}


/*----------------------Q2.9------------------------*/
// Fonction pour mesurer le temps d'exécution d'une fonction donnée
//via arbre
double measureTime_union_ab(Tas_Min_arbre * (*function)(Tas_Min_arbre*, Tas_Min_arbre*),Tas_Min_arbre* tas1, Tas_Min_arbre* tas2){
    clock_t start, end;
    start = clock();
    function(tas1,tas2);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void verf_arbre_union(int *sizes, int *lnb, int repetitions){
    int len=longueur(sizes);
    int taille=longueur(lnb);
    srand(time(NULL));
    
    FILE *dataFileUnion = fopen("time_data_union_arbre.txt", "w");
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
            Tas_Min_arbre* tas1 = construction(jeu_cles1);
            Tas_Min_arbre* tas2 = construction(jeu_cles2);
            totalUnionTime += measureTime_union_ab(unionTas, tas1, tas2);
            //free(tas1);
            //free(tas2);
    
            
            // Assurez-vous de libérer la mémoire allouée
            //free_list_cle(jeu_cles1);
            //free_list_cle(jeu_cles2);
        }
        
        double averageUniontTime = totalUnionTime / repetitions;  
        printf("aveUnt= %f \n",averageUniontTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileUnion, "%d %f\n", size, averageUniontTime);  
            
    }
            
    fclose(dataFileUnion);

    return;
 }


void graphe_union_arbre(){
     // Générer le script gnuplot pour le tracé d'Union_tab
    FILE *gnuplotScriptUnion = fopen("plot_script_union_arbre.gnu", "w");
    if (!gnuplotScriptUnion) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour Union_arbre");
        return ;
    }

    fprintf(gnuplotScriptUnion, "set title 'Temps d Union_arbre en fonction de la taille'\n");
    fprintf(gnuplotScriptUnion, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptUnion, "set ylabel 'Temps d Union_arbre (s)'\n");
    fprintf(gnuplotScriptUnion, "plot 'time_data_union_arbre.txt' with linespoints title 'Union_arbre'\n");



    fclose(gnuplotScriptUnion);

    return;

}

//via tableau
double measureTime_union(Tas_Min_tableau * (*function)(Tas_Min_tableau *, Tas_Min_tableau * ),Tas_Min_tableau * tas1, Tas_Min_tableau * tas2){
    clock_t start, end;
    start = clock();
    Tas_Min_tableau* result=function(tas1, tas2);
    end = clock();
    liberer_tab(result);
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

void verf_tab_union(int *sizes, int *lnb, int repetitions){
    int len=longueur(sizes);
    int taille=longueur(lnb);
    srand(time(NULL));
    
    FILE *dataFileUnion = fopen("time_data_union_tab.txt", "w");
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
            Tas_Min_tableau* tas1 = Construction_tab(jeu_cles1);
            Tas_Min_tableau* tas2 = Construction_tab(jeu_cles2);
            totalUnionTime += measureTime_union(Union_tab, tas1, tas2);
            //free(tas1);
            //free(tas2);
    
            
            // Assurez-vous de libérer la mémoire allouée
            //free_list_cle(jeu_cles1);
            //free_list_cle(jeu_cles2);
        }
        
        double averageUniontTime = totalUnionTime / repetitions;  
        printf("aveUnt= %f \n",averageUniontTime); 

        // Écrire les données dans les fichiers
        fprintf(dataFileUnion, "%d %f\n", size, averageUniontTime);  
            
    }
            
    fclose(dataFileUnion);

    return;
 }


void graphe_tab_un(){
     // Générer le script gnuplot pour le tracé d'Union_tab
    FILE *gnuplotScriptUnion = fopen("plot_script_union_tab.gnu", "w");
    if (!gnuplotScriptUnion) {
        perror("Erreur lors de l'ouverture du script Gnuplot pour Union_tab");
        return ;
    }

    fprintf(gnuplotScriptUnion, "set title 'Temps d Union_tab en fonction de la taille'\n");
    fprintf(gnuplotScriptUnion, "set xlabel 'Taille de la liste'\n");
    fprintf(gnuplotScriptUnion, "set ylabel 'Temps d Union_tab (s)'\n");
    fprintf(gnuplotScriptUnion, "plot 'time_data_union_tab.txt' with linespoints title 'Union_tab'\n");



    fclose(gnuplotScriptUnion);

    return;

}