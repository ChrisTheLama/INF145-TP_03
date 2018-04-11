/*************************************************************************************************/
//  PAR   : Christophe Lamarche & Guillaume Forget     

/*************************************************************************************************/
/*
Le module de guichet fournit le type t_guichet et des fonctions en liens avec ce type.
Le module offre l'initialisation, l'empilement et le depilement de blocs dans une pile accessible
par le t_regroupement. De plus, il est possible d'analyser le contenu du nouveau type par les
fonctions : pile_blocs_nombre, pile_blocs_pleine, pile_blocs_taille et pile_blocs_vide.
Finalement, il est necessaire de libere la memoire de la pile du t_regroupement grace a
free_pile_blocs a la fin d'un programme si on utilise un t_regroupement.
*/

/**************************************************************************************************/

#ifndef  __MODULE__GUICHET__
#define  __MODULE__GUICHET__

/*************************************************************************************************/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS  
// Librairies usuelles à inclure
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"m_decoupage.h"
#include"m_file.h"
/*************************************************************************************************/

/*===================================== LES CONSTANTES ==========================================*/
#define TAILLE	20	//Taille de la matrice dynamique de t_guichet (TAILLE x TAILLE)
#define MINV	2	//Valeur minimale a l'interieur d'une case de la matrice dynamique
#define MAXV	5	//Valeur maximale a l'interieur d'une case de la matrice dynamique
/*===============================================================================================*/

/*************************************************************************************************/
/*************************************************************************************************/
typedef struct {

	t_file_block file; //une file d'attente
	t_block bloc_traite; //bloc en traitement
	int compte_rebours; //compte a rebours avant l'envoit du bloc
	int **matrice_temps; //pointeur vers une matrice dynamique

} t_guichet;

/***************************************** INIT_GUICHET ******************************************/
/* CONSTRUCTEUR
Description : recoit la taille de la file d'attente. Elle
construit le tableau dynamique necessaire pour la file et en cas de succes de l'allocation va fixer
la taille, le debut, la fint et le nombre d'elements (en cas d'echec de l'allocation, tous
les membres du t_file_block et du t_guichet seront nuls (0 ou NULL). Elle retourne le nouvel objet.
PARAMETRES : la taille de la file
RETOUR : Un t_guichet ayant les informations en entree
SPECIFICATIONS : la taille doit etre positif
*/
t_guichet init_guichet(int taille_file);
/*************************************************************************************************/

/************************************** get_nb_bloc_guichet **************************************/
/* INFORMATRICE
Description : Retourne le nombre de t_block non_vide dans le guichet (dans la file d'attente ET
celui en traitement
PARAMETRES : l'adresse du guichet evalue
RETOUR : le nombre de t_block dans le guichet
SPECIFICATIONS : Le guichet doit être initialise
*/
int get_nb_bloc_guichet(t_guichet* guich);
/*************************************************************************************************/

/*************************************** RECEPTION_BLOCK *****************************************/
/* MUTATRICE
Description : Si possible, insere le bloc dans la file du guichet et retourne 1, retour de 0 sinon
PARAMETRES :l'adresse du t_guichet
& le bloc
RETOUR : Renvoit un "1" si l'insertion a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
int reception_block(t_guichet* guich, t_block bloc);
/*************************************************************************************************/

/************************************* DONNER_BLOCK_TERMINE **************************************/
/* MUTATRICE
Description : Dont le fonctionnement est donné par l’algorithme suivant :
·         Si le compte à rebours est > 0,  le décrémenter de 1,
o   retourner un bloc vide.
·         Sinon (le compte à rebours est <= 0),
o   copier le bloc en traitement dans un bloc temporaire
o   défiler si possible un bloc de la file qui devient le nouveau bloc en traitement déterminer son
temps de traitement qui sera assigné à son compte à rebours
o   sinon, bloc en traitement = bloc vide et compte à rebours = 0
o   retourner le bloc temporaire
PARAMETRES : l'adresse du t_guichet
RETOUR : Retourne un t_block : vide si le compteur (compte_rebours) n'est pas a zero
celui en traitement si le compteur est à zero
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
t_block donner_block_termine(t_guichet * guich);
/*************************************************************************************************/

/***************************************** FREE_GUICHET ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique du guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
int free_guichet(t_guichet * guich);
/*************************************************************************************************/

/*************************************** guichet_case_vide ***************************************/
/* INFORMATRICE
Description : Informe si le guichet a un espace vide
PARAMETRES : l'adresse du guichet evalue
RETOUR : retourne '1' si il y a de l'espace dans le guichet, '0' sinon
SPECIFICATIONS : Le guichet doit être initialise
*/
int guichet_case_vide(t_guichet* guich);
/*************************************************************************************************/

#endif
