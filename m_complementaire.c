/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_complementaire.h"

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
			 maximum que la valeur peut avoir (inclusivement)
RETOUR : La valeur aleatoire entre les bornes
SPECIFICATIONS : Necessite l'appel de init_rand() avant l'appel de la fonction
			   & la valeur max doit etre superieur a la valeur du minimum 
*/
int rand_s(int min, int max) {
	int random = 0;
	if (max - min >= RAND_MAX) { //si les valeurs possibles sont superieures a RAND_MAX
		random = min + (rand() / (RAND_MAX))*(max - min);
	} else if (min == max){ //si il n'y a pas de jeux
		random = min;
	} else { //si les valeurs possibles sont inferieurs a RAND_MAX
		random = min + rand() % (max - min);
	}

	return random;
}
/*************************************************************************************************/

/*===============================================================================================*/
/*
Titre : proc_decoup
description :
Cette fonction fait l'affichage les informations d'un bloc decoupe
In : L'adresse du bloc
Out : Rien
*/
/*===============================================================================================*/
void affich_decoup(t_block *bloc)
{
	static int affich_rep = 0;

	affich_rep++;
	if (affich_rep == REPET_AFFICH) {
		// affichage du numero du bloc
		printf("\nBLOC#%u\t(TRANSMIS) ", bloc->num_bloc);
		// affichage de l'addresse / ID
		printf("\tID:%u", bloc->f_identifiant);
		//	taille du decoupage
		printf("\tTaille : %i\toctets", (bloc->taille_bloc));
		// taille restant a decouper
		printf("\tRESTANT : %i\toctets\n", get_taille_restante(bloc->f_identifiant));

		affich_rep = 0;
	}

	return;
}

/*===============================================================================================*/
/*
Titre : get_pos
description :
Cette fonction determine l'indice / position du t_regroupement ayant le meme identifiant que le
bloc en entree
In : L'adresse du bloc
L'adresse du t_regroupement
Out : La position
*/
/*===============================================================================================*/
int get_pos(t_block* bloc, t_regroupement* reg) {
	int pos = 0;//position/indice ou l'identifiant du t_regroupement est le meme que celui du bloc
	int i = 0; // compteur

	for (i = 0; i < QTE_FICHIER; i++) { // pour tout les t_regroupement
		if (bloc->f_identifiant == (reg + i)->id_fichier) // si l'identifiant du t_regroupement 
														  //est le meme que celui du bloc
			pos = i; //tansfert de la bonne position
	}
	return pos; //retourne la position
}

/*===============================================================================================*/
/*
Titre : nom_de_copie
description :
Cette fonction determine le nom de la copie du fichier en traitement correspondant
In : L'adresse du pointeur du nom de la copie
L'adresse du pointeur du t_regroupement
Out : La position
*/
/*===============================================================================================*/
void nom_de_copie(char ** nom_copie, char ** nom_fich) {
	for (int i = 0; i < QTE_FICHIER; i++) {
		nom_copie[i] = (char*)calloc(strlen(nom_fich[i]) + strlen(PREF_NOM_COPIE) + 1, sizeof(char));
		//on offre l'espace necessaire pour le nom de la copie du fichier // le +1 est pour le "\0"
		strcpy(nom_copie[i], PREF_NOM_COPIE); //on insere le prefixe de nom_copie
		strcat(nom_copie[i], nom_fich[i]);//on rajoute le nom du fichier au nom du fichier de copie
	}
	return;
}

/*===============================================================================================*/
/*
Titre : free_nom_copie
description :
Cette fonction libere les tableaux dynamiques alloues pour les noms des copies
In : L'adresse du pointer du nom
Out : Rien
*/
/*===============================================================================================*/
void free_nom_copie(char ** nom_copie) {
	if (nom_copie != NULL) {
		free(*(nom_copie));
		*nom_copie = NULL; // liberation des tableau des noms des copies
	}
	return;
}

/*===============================================================================================*/
/*
Titre : affich_contenu_rec
description :
Cette fonction affiche le contenu des t_reconstruction utilises
In : L'adresse du tableau de t_reconstruction
Out : Rien
*/
/*===============================================================================================*/
void affich_contenu_rec(t_reconstruction* rec) {
	int k = 0; //compteur pour le
	if (AFFICH_T_REC != 0) { // affichage si desire
		for (int i = 0; i < QTE_FICHIER; i++) { // pour chaque fichier / t_reconstruction
			for (int j = 0; j < (int)(rec + i)->nbr_bloc_actu; j++) { // pour chaque bloc dans le \
																	  //t_reconstruction
				k++; //incrementation du compteur
				if (k == REPET_AFFICH) { // lorsque l'exigence pour l'affiche est completer
					print_bloc((rec[i]).ptr_bloc + j); // affichage du bloc
					k = 0; //reinitialisation
				}
			}
		}
	}
	return;
}

/*=================================== TAILLE_RESTANTE_TOT =======================================*/
/*
Titre : Taille_restante_tot
description : retourne la quantite totale de la memoire a decouper pour tous les fichiers
In : Le tableau des identifiants des fichiers
Out : la taille restant a decouper
*/
int taille_restante_tot(unsigned int* id) {
	int taille = 0, i = 0;

	for (i = 0; i < QTE_FICHIER; i++)
		taille += get_taille_restante(*(id + i));

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
	int qte = 0, i = 0;

	for (i = 0; i < qte_traiteur; i++)
		qte += get_nb_bloc_traiteur(traiteur + i);

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
CONDITION : on ne peut plus appeler la fonction a la suite que affichage == 1
*/
/*===============================================================================================*/
int statistique(t_traiteur * traiteur, int nb_traiteur, int affichage) {
	static int temps = 0; //nombre d'iteration
	static int* bloc_in_file = NULL; //pointeur pour un tableau dynamique sur la quantite 
									 //maximale de bloc dans la file de garde
	static int* guichet_max = NULL;  //pointeur pour un tableau dynamique sur la quantite 
									 //maximale de guichet dans le traiteur
	static int* bloc_max = NULL;	 //pointeur pour un tableau dynamique sur la quantite 
									 //maximale de bloc dans le traiteur

	int i = 0; //compteur

	if (temps == 0) {
		bloc_in_file = calloc(nb_traiteur, sizeof(int)); 
		guichet_max = calloc(nb_traiteur, sizeof(int));
		bloc_max = calloc(nb_traiteur, sizeof(int));
	}

	temps++;

	for (i = 0; i < nb_traiteur; i++) {
		if(bloc_in_file[i] < get_nb_fileg(&(traiteur[i].file_garde))) 
			bloc_in_file[i] = get_nb_fileg(&(traiteur[i].file_garde)); 

		if(guichet_max[i] < get_nb_guichet(traiteur + i))
			guichet_max[i] = get_nb_guichet(traiteur + i);

		if(bloc_max[i] < get_nb_bloc_traiteur(traiteur + i))
			bloc_max[i] = get_nb_bloc_traiteur(traiteur + i);
	}

	if (affichage != 0) {
		for (i = 0; i < nb_traiteur; i++) {
			printf("\nTRAITEUR %d :", i);
			printf("\nMAX BLOC DANS FILE : %d", bloc_in_file[i]);
			printf("\nMAX GUICHET DANS TRAITEUR : %d", guichet_max[i]);
			printf("\nMAX BLOC DANS TRAITEUR : %d\n", bloc_max[i]);
		}
		free(bloc_in_file); bloc_in_file = NULL;
		free(guichet_max); guichet_max = NULL;
		free(bloc_max); bloc_max = NULL;
	}

	return temps;
}
