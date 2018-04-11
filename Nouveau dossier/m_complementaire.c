/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_complementaire.h"

typedef struct {
	
	int bloc_in_file; //pointeur pour un tableau dynamique sur la quantite 
					  //maximale de bloc dans la file de garde
	int guichet_max;  //pointeur pour un tableau dynamique sur la quantite 
					  //maximale de guichet dans le traiteur
	int bloc_max;	 //pointeur pour un tableau dynamique sur la quantite 
					 //maximale de bloc dans le traiteur
}t_statistique;



/*===============================================================================================*/
/*===================================== FONCTIONS PUBLIQUE ======================================*/
/*===============================================================================================*/

/****************************************** INIT_RAND ********************************************/
/*
DESCRIPTION : Initialise la fonction rand()
PARAMETRES : RIEN
RETOUR : RIEN
SPECIFICATIONS : AUCUNE
*/
void init_rand(void) {
	srand((unsigned int)(time(NULL)*rand()));
}
/*************************************************************************************************/

/******************************************** RAND_S *********************************************/
/*
DESCRIPTION : Retourne une valeur aleatoire entre minimum et un maximum
PARAMETRES : minimum que la valeur peut avoir (inclusivement)
			 maximum que la valeur peut avoir (exclusivement)
RETOUR : La valeur aleatoire entre les bornes
SPECIFICATIONS : Necessite l'appel de init_rand() avant l'appel de la fonction
			   & la valeur max doit etre superieur a la valeur du minimum 
*/
int rand_s(int min, int max) {
	int random = 0;
	if (max - min >= RAND_MAX && max !=0) { //si les valeurs possibles sont superieures a RAND_MAX
		random = min + (rand() / (RAND_MAX+1))*(max - min);
	} else if (min == max || max == 0){ //si il n'y a pas de jeux
		random = min;
	} else { //si les valeurs possibles sont inferieurs a RAND_MAX
		random = min + rand() % (max - min);
	}

	return random;
}
/*************************************************************************************************/


/*=================================== TAILLE_RESTANTE_TOT =======================================*/
/*
Titre : Taille_restante_tot
description : retourne la quantite totale de la memoire a decouper pour tous les fichiers
In : Le tableau des identifiants des fichiers
Out : la taille restant a decouper
*/
int taille_restante_tot(unsigned int* id, int nb_fichier) {
	int taille = 0, i = 0; //compteur

	for (i = 0; i < nb_fichier; i++) //pour chaque fichier
		taille += get_taille_restante(*(id + i)); //calcule le nombre total de  

	return taille;
}
/*===============================================================================================*/

/*==================================== BLOCK_RESTANTE_TOT =======================================*/
/*
Titre : Taille_restante_tot
description : retourne la quantite totale de la memoire a decouper pour tous les fichiers
In : Le tableau des identifiants des fichiers
	 la quantite de traiteur utilisee
Out : la taille restant a decouper
*/
int block_restante_tot(t_traiteur * traiteur, int qte_traiteur) {
	int qte = 0, i = 0; //compteur

	for (i = 0; i < qte_traiteur; i++) //pour chaquee compteur
		qte += get_nb_bloc_traiteur(traiteur + i);	//on additionne le nombre de bloc non-vide dans 
													//le traiteur

	return qte;
}
/*===============================================================================================*/

/*======================================= STATISTIQUE ===========================================*/
/*
Titre : statistique
description : fait la compilation et l'affichage des statiques des traiteurs
In :	Le tableau des traiteurs
nombre de traiteur
valeur volonte d'affichage (0 -> Aucun affichage ; 1 -> Affichage)
Out : l'unite de temps
CONDITION : Pour liberer l'espace memoire allouee pour la fonction il faut activer l'affichage
*/
/*===============================================================================================*/
int statistique(t_traiteur * traiteur, int nb_traiteur, int affichage) {

	static int temps = 0; //nombre d'iteration , compteur de temps 
	static t_statistique* stat = NULL; //pointeur pour un tableau dynamique des statistiques
	int i = 0; //compteur

	if (stat == NULL) { //allocation des tableaux
		stat = calloc(nb_traiteur, sizeof(t_statistique));
	}

	temps++; //incrementation du compteur de temps

	for (i = 0; i < nb_traiteur; i++) { //pour chaque traiteur
		if(stat[i].bloc_in_file < get_nb_fileg(&(traiteur[i].file_garde))) //si la nouvelle valeur est 
			stat[i].bloc_in_file = get_nb_fileg(&(traiteur[i].file_garde));// plus grand 

		if(stat[i].guichet_max < get_nb_guichet(traiteur + i)) //si la nouvelle valeur est plus grand
			stat[i].guichet_max = get_nb_guichet(traiteur + i);

		if(stat[i].bloc_max < get_nb_bloc_traiteur(traiteur + i))//si la nouvelle valeur est plus grand
			stat[i].bloc_max = get_nb_bloc_traiteur(traiteur + i);
	}

	if (affichage != 0) { //si on veut afficher les statistiques
		for (i = 0; i < nb_traiteur; i++) { //pour chaque traiteur
			printf("\nTRAITEUR %d :"					, i); 
			printf("\nMAX BLOC DANS FILE : %d"			, stat[i].bloc_in_file);
			printf("\nMAX GUICHET DANS TRAITEUR : %d"	, stat[i].guichet_max);
			printf("\nMAX BLOC DANS TRAITEUR : %d\n"	, stat[i].bloc_max);
		}
		//liberation des tableaux des statistiques
		free(stat); stat = NULL;
	}

	return temps;
}