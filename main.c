/*===============================================================================================*/
/* 											INF145 - TP2										 */
/*===============================================================================================*/

/**************************************************************************************************
Titre				:	Travail pratique numero 2
Auteur				:	Christophe Lamarche & Frederic Thibault
Date de creation	:	05/02/2018
Dernier modification:	08/03/2018
Description			:
Ce programme fait le traitement, la division et le transport de fichiers par la division par bloc. 
A la suite de la receptions des bloc du fichier, le fichier est reconstruit sous un nouveau fichier

Librairie necessaire: "m_decoupage.h"
					  "m_regroupement.h"
					  "m_reconstruction.h"
**************************************************************************************************/


/*===============================================================================================*/
/*
Ce programme repond aux exigences du travail pratique numero 2 pour le cours de INF145 - 
Programmation avance et langage C.
*/
/*===============================================================================================*/

//Permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 

/*===============================================================================================*/
/*											LIBRAIRIES											 */
/*===============================================================================================*/

// Librairies usuelles à inclure 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>
#include<string.h>

// Librairies supplémentaire à inclure
#include "m_decoupage.h"
#include "m_regroupement.h"
#include "m_reconstruction.h"
//Librairies supplementaire du tp03
#include "m_guichet.h"
/*===============================================================================================*/
/*									DÉFINITION DES CONSTANTES			                         */
/*===============================================================================================*/

#define TAILLE_FILE			6
#define AFFICH_T_REC		1				//0->N'affiche pas le contenu des t_rec : Autre->OUI
#define REPET_AFFICH		100				//Recurence de l'affichage dans proc_decoup()||0->Aucun
#define QTE_FICHIER			MAX_FICHIERS_DECOUPAGE 	//La quantite de fichier decoupe et reconstruit
#define TAILLE_PILE			15				//taille de la memoire allouee a la pile
#define TAILLE_TAB_REC_INI	45				//taille initiale du tableau dynamique de t_reconstruct
#define NOM_FICHIER_0		"affiche.jpg"	//nom du 0e fichier
#define NOM_FICHIER_1		"musique.wma"	//nom du 1e fichier
#define NOM_FICHIER_2		"TP2.pdf"		//nom du 2e fichier
#define NOM_FICHIER_3		"math.png"		//nom du 3e fichier
#define NOM_FICHIER_4		"Image.jpg"		//nom du 4e fichier
#define NOM_FICHIER_5		"affiche5.jpg"	//nom du 5e fichier
#define NOM_FICHIER_6		"affiche6.jpg"	//nom du 6e fichier
#define NOM_FICHIER_7		"affiche7.jpg"	//nom du 7e fichier
#define NOM_FICHIER_8		"affiche8.jpg"	//nom du 8e fichier
#define NOM_FICHIER_9		"affiche9.jpg"	//nom du 9e fichier
#define NOM_FICHIER_10		"affiche10.jpg"	//nom du 10e fichier
#define NOM_FICHIER_11		"affiche11.jpg"	//nom du 11e fichier
#define NOM_FICHIER_12		"affiche12.jpg"	//nom du 12e fichier
#define NOM_FICHIER_13		"affiche13.jpg"	//nom du 13e fichier
#define NOM_FICHIER_14		"affiche14.jpg"	//nom du 14e fichier
#define NOM_FICHIER_15		"affiche15.jpg"	//nom du 15e fichier
#define NOM_FICHIER_16		"affiche16.jpg"	//nom du 16e fichier
#define NOM_FICHIER_17		"affiche17.jpg"	//nom du 17e fichier
#define NOM_FICHIER_18		"affiche18.jpg"	//nom du 18e fichier
#define NOM_FICHIER_19		"affiche19.jpg"	//nom du 19e fichier
#define PREF_NOM_COPIE		"copie_"		//prefixe du nom des copies du fichier

/*===============================================================================================*/
/*									DÉCLARATION DES SOUS-PROGRAMMES				                 */
/*===============================================================================================*/
/*=================================================================================================
TITRE : prog_decoup
codee par Christophe Lamarche
Cette fonction fait le decoupage d'un bloc d'un fichier et affiche les informations de celui-ci 
Parametres : L'adresse du t_bloc qui fait la reception du bloc decoupe
Hypotheses : L'appel de la fonction init_decoupage() doit avoir été fait auparavant
			 Il est possible de changer la recurrence de l'affichage a l'aide de la constante 
			 REPET_AFFICH
Valeur de retour : RIEN
Exemples d'appel : 
t_bloc bloc;
init_decoupage;
porc_decoup(&bloc);
=================================================================================================*/
void affich_decoup(t_block * bloc);

/*=================================================================================================
TITRE : get_pos
codee par Christophe Lamarche
Cette fonction determine la position / l'indice du t_regroupement possedant le meme identifiant que 
	le bloc.
Parametres : L'adresse du t_bloc di decoupage de fichier
			 L'adresse du tableau t_regroupement
Hypotheses : AUCUNE
Valeur de retour : la position du t_regroupement ayant le meme identifiant que le bloc
=================================================================================================*/
int get_pos(t_block* bloc, t_regroupement* reg);

/*=================================================================================================
TITRE : nom_de_copie
codee par Christophe Lamarche
Cette fonction fait le decoupage d'un bloc d'un fichier et affiche les informations de celui-ci
Parametres : L'adresse du pointeur du nom de la copie
			 L'adresse du pointeur du t_regroupement
Hypotheses : Le tableau des nom de copie doit avoir ete fait auparavant 
Valeur de retour : RIEN
=================================================================================================*/
void nom_de_copie(char ** nom_copie, char ** nom_fich);
/*=================================================================================================
TITRE : free_nom_copie
codee par Christophe Lamarche
Cette fonction libere les tableaux dynamiques alloues pour les noms des copies
Parametres : L'adresse du pointeur du nom de la copie
Hypotheses : on libere le nom a la fin du programme ou apres son appel apres la reconstruction du
	fichier.
Valeur de retour : RIEN
=================================================================================================*/
void free_nom_copie(char ** nom_copie);
/*=================================================================================================
TITRE :affich_contenu_rec
codee par Christophe Lamarche
Cette fonction affiche le contenu des t_reconstruction utilises.
Parametres : L'adresse du tableau du t_reconstruction
hypothese : Aucune
Valeur de retour : RIEN
=================================================================================================*/
void affich_contenu_rec(t_reconstruction* rec);
/*===============================================================================================*/
/*											PROGRAMME PRINCIPAL									 */
/*===============================================================================================*/
#if(1)
int main(void) {
	
	t_block bloc = { 0 };
	t_block bloc_recept = { 0 };
	t_guichet guich = { 0 };
	int id = 0;

	init_decoupage();
	guich = init_guichet(TAILLE_FILE);

	id = ajouter_fichier(NOM_FICHIER_0);

	do{
		if (get_nb_bloc_guichet(&guich) != (TAILLE_FILE+1)) {
			bloc = get_bloc();
			reception_block(&guich, bloc);
		}

		bloc_recept=donner_block_termine(&guich);

		if (bloc_recept.taille_bloc != 0) print_bloc(&bloc_recept);
	} while (get_taille_restante(id) || (guich.bloc_traite.taille_bloc != 0));
	
	free_guichet(&guich);
	retirer_fichier(id);

	system("pause");
	return EXIT_SUCCESS;
}
#endif
#if(0)
int main(void)
{
	int i = 0, j = 0; // compteur
	int pos = 0, id = 0;
	char *nom_fich[] = {NOM_FICHIER_0,
						NOM_FICHIER_1,
						NOM_FICHIER_2,
						NOM_FICHIER_3,
						NOM_FICHIER_4,
						NOM_FICHIER_5,
						NOM_FICHIER_6,
						NOM_FICHIER_7,
						NOM_FICHIER_8,
						NOM_FICHIER_9,
						NOM_FICHIER_10,
						NOM_FICHIER_11,
						NOM_FICHIER_12, 
						NOM_FICHIER_13,
						NOM_FICHIER_14,
						NOM_FICHIER_15,
						NOM_FICHIER_16, 
						NOM_FICHIER_17,
						NOM_FICHIER_18,
						NOM_FICHIER_19 };// nom des fichiers  
	char *nom_copie[QTE_FICHIER]; //nom des copies des fichiers
	t_block bloc = { 0 }; // bloc pour la division
	t_regroupement reg[QTE_FICHIER] = { 0 }; // regroupement / pile
	t_reconstruction rec[QTE_FICHIER] = { 0 }; // t_reconstruction
	
/*===============================================================================================*/
/*================================= Creation des noms des copies ================================*/
/*===============================================================================================*/
	nom_de_copie(nom_copie,nom_fich);
/*===============================================================================================*/
/*======================================= Initialisation  =======================================*/
/*===============================================================================================*/
	init_decoupage(); // commande d'initiation
	//ajout des fichiers & initialisation des reg et des rec
	
	//initialisation des t_regroupement et des t_reconstruction
	for (i = 0; i < QTE_FICHIER; i++) {
		id = ajouter_fichier(nom_fich[i]); // ajout du fichier
		
		if (id == NULL) { //si l'ajout a echoue
			printf("ERREUR DE L'AJOUT DU FICHIER #%d", i); // message d'erreur
		}
		else { //si l'ajout du fichier est reussi
			reg[i] = init_regroupement(id, TAILLE_PILE); // initialisation du t_reg
			rec[i] = init_reconstruction(id, TAILLE_TAB_REC_INI); // initialisation du t_rec
		}
	}

/*===============================================================================================*/
/*=================================== Traitement des fichiers ===================================*/
/*===============================================================================================*/
	
	do {
		
		bloc = get_bloc(); // decoupe un bloc dans un fichier
		pos = get_pos(&bloc, &reg); //on determine quel est le t_regroupement ayant le meme id
		
		if (bloc.f_identifiant != 0) {
			//on s'assure que le bloc est empiler dans la pile
			while (empiler_bloc(reg + pos, bloc) == 0) {}
			affich_decoup(&bloc); // affichage du bloc decoupe
		}
		
		if (pile_blocs_pleine(reg + pos)) //si la pile est pleine 
			ajouter_pile_blocs(rec + pos, reg + pos); // on transfert le contenu de la pile dans \
													  le tableau de t_reconstruction
		
		if (bloc.f_identifiant == 0) {// lorsque tous les fichiers ont fini d'etre decoupes
			for (i = 0; i < QTE_FICHIER; i++) // pour toutes les piles
				ajouter_pile_blocs(rec + i, reg + i); //on s'assure que toutes les piles sont vide
		}
	} while (bloc.f_identifiant != 0); // tant que le bloc recu n'est pas vide

/*===============================================================================================*/
/*=========================== Affichage du contenu des t_reconstruction =========================*/
/*===============================================================================================*/
	affich_contenu_rec(rec);
/*===============================================================================================*/
/*================================== Reconstruction des fichiers ================================*/
/*===============================================================================================*/
	//reconstruction des fichiers
	for (i = 0; i < QTE_FICHIER; i++) { // pour chaque fichier
		reconstruire_fich(rec+i,nom_copie[i]); //reconsruire le ieme fichier
	}

/*===============================================================================================*/
/*============================== Liberation des memoires dynamiques =============================*/
/*===============================================================================================*/
	//libere les tableaux dynammiques des divisions des fichiers et des t_reconstructions
	for (i = 0; i < QTE_FICHIER; i++) {
		retirer_fichier((rec[i]).id_fichier); // liberation du fichier 
		
		free_pile_blocs(reg + i); //liberation du t_regroupement / pile
		free_rec_tab(rec+i,i); //libere le tableau dynamique du ieme fichier
		free_nom_copie(nom_copie + i);
	}

	// on termine avec le standard... "APPUYEZ UNE TOUCHE.."
	printf("\n\n");
	system("PAUSE");

	// et ÇA, c'est le retour d'un 0 au système d'exploitation.
	return EXIT_SUCCESS;
}
#endif
/*************************************************************************************************/

/*===============================================================================================*/
/*									DÉFINITION DES SOUS-PROGRAMMES								 */
/*===============================================================================================*/

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
		if (bloc->f_identifiant == (reg + i)->id_fichier) // si l'identifiant du t_regroupement \
			est le meme que celui du bloc
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
			for (int j = 0; j < (rec + i)->nbr_bloc_actu; j++) { // pour chaque bloc dans le \
																 t_reconstruction
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
