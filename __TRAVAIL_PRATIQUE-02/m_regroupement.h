/*************************************************************************************************/
//  PAR   : Christophe Lamarche & Frederic Thibault		     

/*************************************************************************************************/
/*
Le module de regroupement de fichier en blocs disjoints fournit le type t_regroupement et des 
fonctions en liens avec ce type.

Le module offre l'initialisation, l'empilement et le depilement de blocs dans une pile accessible 
par le t_regroupement. De plus, il est possible d'analyser le contenu du nouveau type par les 
fonctions : pile_blocs_nombre, pile_blocs_pleine, pile_blocs_taille et pile_blocs_vide. 

Finalement, il est necessaire de libere la memoire de la pile du t_regroupement grace a 
free_pile_blocs a la fin d'un programme si on utilise un t_regroupement.
*/

/**************************************************************************************************/

#ifndef  __MODULE__REGROUPEMENT__
#define  __MODULE__REGROUPEMENT__

/*************************************************************************************************/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS  
// Librairies usuelles à inclure
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"m_decoupage.h"
/*************************************************************************************************/

/*************************************************************************************************/
/*************************************************************************************************/
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block (pile)
	unsigned int taille_tab; //taille du tableau dynamique
	unsigned int nbr_bloc; //nombre de t_bloc dans le tableau dynamique

} t_regroupement;


/***************************************** NOM FONCTION ******************************************/
/*
donne
PARAMETRES :
RETOUR :
SPECIFICATIONS :
*/
/*************************************************************************************************/

/*************************************** INIT_REGROUPEMENT ***************************************/
/* MUTATRICE
Description : recoit l'identifiant unique d'un fichier et la taille maximale de la pile. Elle 
	construit le tableau dynamique necessaire et en cas de succes de l'allocation va fixer la 
	taille, l'identifiant unique et le nombre de d'elements (en cas d'echec de l'allocation, tous 
	les membres du t_regroupement seront nuls (0 ou NULL). Elle retourne le nouvel objet.
PARAMETRES : l'identifiant d'un fichier
			 la taille du t_regroupement / pile
RETOUR : Un t_regroupement ayant les informations en entree
SPECIFICATIONS : la taille doit etre positif
*/
t_regroupement init_regroupement(unsigned int id, int taille);
/*************************************************************************************************/

/****************************************** EMPILER_BLOC *****************************************/
/* MUTATRICE
Description : Va empiler le block recu si les conditions necessaires sont satisfaites, elle copie 
	le bloc dans le tableau et retourne 1 si l'action reussit et 0 sinon.
PARAMETRES : l'adresse du t_regroupement, 
			 le bloc a empiler
RETOUR : Renvoit un "1" si l'empilement a reussit & "0" sinon.
SPECIFICATIONS : La pile doit être initialisee
*/
int empiler_bloc(t_regroupement * reg, t_block bloc);
/*************************************************************************************************/


/***************************************** DEPILER_BLOC ******************************************/
/*
Description : Va depiler un bloc si les conditions necessaires sont satisfaites, elle copie le 
	t_block du haut dans la reference recue en parametre et retourne 1 si l'action est reussi et 0
	sinon.
PARAMETRES :l'adresse du t_regroupement, 
			l'adresse du bloc qui recevra le bloc du t_regroupement
RETOUR : Renvoit un "1" si le depilement a reussit & "0" sinon.
SPECIFICATIONS : La pile doit être initialisee
*/
int depiler_bloc(t_regroupement * reg, t_block * bloc);
/*************************************************************************************************/

/*************************************** PILE_BLOCS_PLEINE ***************************************/
/* INFORMATRICE
Description : Evalue si la pile est pleine
PARAMETRES : l'adresse du t_regroupement
RETOUR : Retourne "1" si la pile est pleine et "0" sinon.
SPECIFICATIONS : La pile doit être initialisee
*/
int pile_blocs_pleine(const t_regroupement * reg);
/*************************************************************************************************/

/**************************************** PILE_BLOCS_VIDE ****************************************/
/* INFORMATRICE
Description : Evalue si la pile est vide
PARAMETRES : l'adresse du t_regroupement a evaluer
RETOUR : retourne "1" si la pile est vide et "0" sinon.
SPECIFICATIONS : La pile doit être initialisee
*/
int pile_blocs_vide(const t_regroupement * reg);
/*************************************************************************************************/

/*************************************** PILE_BLOCS_TAILLE ***************************************/
/* INFORMATRICE
Description : Informe le nombre de bloc que peut contenir le t_regroupement
PARAMETRES : L'adresse du t_regroupement evalue
RETOUR : Retourne le nombre maximum de t_block dans la pile.
SPECIFICATIONS : La pile doit être initialisee
*/
int pile_blocs_taille(const t_regroupement * reg);
/*************************************************************************************************/

/************************************** PILE_BLOCS_NOMBRE ****************************************/
/* INFORMATRICE
Description : Informe le nombre de blocs dans la pile au moment de l'evaluation
PARAMETRES : L'adresse du t_regroupement evalue
RETOUR : Retourne le nombre de t_block actuellement dans la pile	
SPECIFICATIONS : La pile doit être initialisee
*/
int pile_blocs_nombre(const t_regroupement * reg);
/*************************************************************************************************/

/************************************** FREE_PILE_BLOCS ******************************************/
/* INFORMATRICE
Description : libere le tableau dynamique et remet tous les membres à 0 ou NULL
PARAMETRES : L'adresse du t_regroupement a liberer
RETOUR : RIEN
SPECIFICATIONS : La pile doit être initialisee et il est necessaire de le faire pour chaque
	t_regroupement a la fin d'un programme si on fait l'appel de t_regroupement dans le programme 
*/
void free_pile_blocs(t_regroupement * reg);
/*************************************************************************************************/
#endif
/*************************************************************************************************/