/*************************************************************************************************/
//  PAR   : Christophe Lamarche & Guillaume Forget     

/*************************************************************************************************/
/*
Le module m_complementaire.h offre l'initialisation et l'appel de la fonction rand(), les tests 
pour evaluer la quantite de memoire est decouper dans des fichiers ou la quantite de bloc non-vide 
dans un t_traiteur disponible dans le module m_traiteur. Il est possible d'analyser des valeurs 
talons dans un traiteur
fonctions : init_rand(), rand_s(), taille_restante_tot(), block_restante_tot(), statistique()
Il est necessaire de faire l'appel de init_rand avant l'utilisation de rand_s
*/

/**************************************************************************************************/

#ifndef  __MODULE__COMPLEMENTAIRE__
#define  __MODULE__COMPLEMENTAIRE__

/*************************************************************************************************/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS

// Librairies usuelles à inclure
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>

#include"m_reconstruction.h"
#include"m_traiteur.h"
/*************************************************************************************************/

/*===================================== LES CONSTANTES ==========================================*/
#define NBR_INIT			2			//Nombre de repetition pour l'initialisation
#define AFFICH_T_REC		1			//0->N'affiche pas le contenu des t_rec : Autre->OUI
#define REPET_AFFICH		100			//Recurence de l'affichage dans proc_decoup()||0->Aucun
#define PREF_NOM_COPIE		"copie_"	//prefixe du nom des copies du fichier 
/*===============================================================================================*/

/*************************************************************************************************/
/*************************************************************************************************/

/***************************************** NOM FONCTION ******************************************/
/*
DESCRIPTION :
PARAMETRES :
RETOUR :
SPECIFICATIONS :
*/

/*************************************************************************************************/

/****************************************** INIT_RAND ********************************************/
/*
DESCRIPTION : Initialise la fonction rand()
PARAMETRES : RIEN
RETOUR : RIEN
SPECIFICATIONS : AUCUNE
*/
void init_rand(void);
/*************************************************************************************************/

/******************************************** RAND_S *********************************************/
/*
DESCRIPTION : Retourne une valeur aleatoire entre minimum et un maximum
PARAMETRES : minimum que la valeur peut avoir (inclusivement)
			 maximum que la valeur peut avoir (exclusivement)
RETOUR : La valeur aleatoire entre les bornes
SPECIFICATIONS : Necessite l'appel de init_rand() avant l'appel de la fonction
*/
int rand_s(int min, int max);
/*************************************************************************************************/

/*=================================================================================================
TITRE :Taille_restante_tot
codee par Christophe Lamarche
description : retourne la quantite totale de la memoire a decouper pour tous les fichiers
In : Le tableau des identifiants des fichiers
Out : la taille restant a decouper
====================================================================*/
int taille_restante_tot(unsigned int* id, int nb_fichier);

/*==================================== BLOCK_RESTANTE_TOT =======================================*/
/*
Titre : Taille_restante_tot
description : retourne la quantite totale de la memoire a decouper pour tous les fichiers
In : Le tableau des traiteurs
	 la quantite de traiteur utilisee
Out : la taille de bloc dans les traiteurs
*/
/*===============================================================================================*/
int block_restante_tot(t_traiteur * traiteur, int qte_traiteur);

/*======================================= STATISTIQUE ===========================================*/
/*
Titre : statistique
description : fait la compilation et l'affichage des statiques des traiteurs
In :	Le tableau des traiteurs
		nombre de traiteur
		valeur volonte d'affichage (0 -> Aucun affichage ; 1 -> Affichage)
Out : l'unite de temps
CONDITION : 
*/
/*===============================================================================================*/
int statistique(t_traiteur * traiteur, int nb_traiteur, int affichage);

#endif
