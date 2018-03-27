/*===============================================================================================*/
/* 											INF145 - TP3										 */
/*===============================================================================================*/

/**************************************************************************************************
Titre				:	Travail pratique numero 3
Auteur				:	Christophe Lamarche & Guillaume Forget
Date de creation	:	26/03/2018
Dernier modification:	26/03/2018
Description			:
Programmes de test pour les modules de file et file chainee

Librairie necessaire: 
"m_decoupage.h"
"m_file_chainee.h"
"m_file.h"

**************************************************************************************************/


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
#include "m_file.h"
#include "m_file_chainee.h"

/*===============================================================================================*/
/*									DéFINITION DES CONSTANTES			                         */
/*===============================================================================================*/

#define TAILLE_FILE			200
#define AFFICH_T_REC		1				//0->N'affiche pas le contenu des t_rec : Autre->OUI
#define REPET_AFFICH		100				//Recurence de l'affichage dans proc_decoup()||0->Aucun
#define QTE_FICHIER			MAX_FICHIERS_DECOUPAGE 	//La quantite de fichier decoupe et reconstruit
#define TAILLE_PILE			15				//taille de la memoire allouee a la pile
#define TAILLE_TAB_REC_INI	45				//taille initiale du tableau dynamique de t_reconstruct
#define NOM_FICHIER_0		"pince_files.zip"	//nom du 0e fichier
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
/*											PROGRAMME PRINCIPAL									 */
/*===============================================================================================*/

/*************************************************************************************************/
//test de la file
#if(1)
int main(void) {

	t_block bloc = { 0 };
	t_block bloc_recept = { 0 };
	int id = 0;
	t_file_block blocs = { 0 };


	//init file
	blocs = init_file_block(TAILLE_FILE);

	//début du découpage
	init_decoupage();

	//ajouter fichier
	id = ajouter_fichier(NOM_FICHIER_0);

	do {

		//recevoir un bloc
		bloc = get_bloc();

		//mettre le bloc dans la file
		enfiler_block(&blocs, bloc);
		
	} while (bloc.bloc_final != 1);

	//fermer le fichier
	retirer_fichier(id);

	do {

		//aller chercher un bloc dans la file
		defiler_block(&blocs, &bloc_recept);

		//afficher si multiple de 2
		if (bloc_recept.num_bloc % 2 == 0) {

			print_bloc(&bloc_recept);
		}

	} while (bloc_recept.bloc_final != 1);

	//libérer la file
	free_file_block(&blocs);

	system("pause");
	return EXIT_SUCCESS;
}
#endif

/*************************************************************************************************/
//test de la file chainée de t_block
#if(0)
int main(void) {


	t_block bloc = { 0 };
	t_block bloc_recept = { 0 };
	int id = 0;
	t_file_block_chainee blocs = { 0 };

	//début du découpage
	init_decoupage();
	
	//ajouter fichier
	id = ajouter_fichier(NOM_FICHIER_0);

	do {
		
		//recevoir un bloc
		bloc = get_bloc();

		//mettre le bloc dans la file
		enfiler_block_chainee(&blocs, bloc);
			
	} while (bloc.bloc_final != 1);

	//fermer le fichier
	retirer_fichier(id);

	do{

		//aller chercher un bloc dans la file
		defiler_block_chainee(&blocs, &bloc_recept);

		//afficher si multiple de 2
		if (bloc_recept.num_bloc % 2 == 0){

			print_bloc(&bloc_recept);
		}

	} while (bloc_recept.bloc_final != 1);


	system("pause");
	return EXIT_SUCCESS;
}
#endif







