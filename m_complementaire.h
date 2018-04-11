/*************************************************************************************************/
//  PAR   : Christophe Lamarche & Guillaume Forget     

/*************************************************************************************************/
/*
Le module de guichet fournit le type t_guichet et des fonctions en liens avec ce type.
---------------------------->>  A MODIFIER     <<--------------------------------------------------
Le module offre l'initialisation, l'empilement et le depilement de blocs dans une pile accessible
par le t_regroupement. De plus, il est possible d'analyser le contenu du nouveau type par les
fonctions : pile_blocs_nombre, pile_blocs_pleine, pile_blocs_taille et pile_blocs_vide.
Finalement, il est necessaire de libere la memoire de la pile du t_regroupement grace a
free_pile_blocs a la fin d'un programme si on utilise un t_regroupement.
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
#define QTE_FICHIER			1//MAX_FICHIERS_DECOUPAGE 	//La quantite de fichier decoupe et reconstruit
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

/*=================================================================================================
TITRE :Taille_restante_tot
codee par Christophe Lamarche
description : retourne la quantite totale de la memoire a decouper pour tous les fichiers
In : Le tableau des identifiants des fichiers
Out : la taille restant a decouper
====================================================================*/
int taille_restante_tot(unsigned int* id);

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
