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

#ifndef  __MODULE__TRAITEUR__
#define  __MODULE__TRAITEUR__

/*************************************************************************************************/
//qui permet de d�sactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS  
// Librairies usuelles � inclure
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"m_decoupage.h"
#include"m_file.h"
#include"m_file_chainee.h"
#include"m_guichet.h"
#include"m_liste_guichet.h"
/*************************************************************************************************/

/*===================================== LES CONSTANTES ==========================================*/

/*===============================================================================================*/

/*************************************************************************************************/
/*************************************************************************************************/

typedef struct {

	t_liste_g* liste_guichet; //Liste chainee double de Guichet
	t_file_block_chainee file_garde; //Liste double (en file) 
	int nbr_gichet;
	int nbr_block;

} t_traiteur;


/***************************************** NOM FONCTION ******************************************/
/*
donne
PARAMETRES :
RETOUR :
SPECIFICATIONS :
*/
/*************************************************************************************************/

/***************************************** INIT_TRAITEUR ******************************************/
/* CONSTRUCTEUR
Description : Construit un traiteur dont la liste et la file sont initialement vides
PARAMETRES : taille de la file du guichet
RETOUR : Un t_traiteur initialise
SPECIFICATIONS : Aucune
*/
t_traiteur init_traiteur(int taille);
/*************************************************************************************************/

/**************************************** GET_NB_GUICHET *****************************************/
/* INFORMATRICE
Description : Retourne le nombre de guichets actuellement dans la liste du traiteur
PARAMETRES : l'adresse du traiteur evalue
RETOUR : le nombre de guichet dans le traiteur
SPECIFICATIONS : Le traiteur doit �tre initialise
*/
int get_nb_guichet(t_traiteur * traiteur);
/**************************************************************************************************/

/************************************ GET_NB_BLOC_TRAITEUR ****************************************/
/* INFORMATRICE
Description : Retourne le nombre total de t_block non-vides dans ses guichets plus ceux pr�sents
dans sa file de
PARAMETRES : L'adresse du t_traiteur
RETOUR : le nombre de t_bloc non-vides
SPECIFICATIONS : La file doit �tre initialisee
*/
int get_nb_bloc_traiteur(t_traiteur * traiteur);
/*************************************************************************************************/

/****************************************** ENTREE_BLOC ******************************************/
/* MUTATRICE
Description : Cette fonction va :
� d�clencher donner_block_termine pour chacun des guichets du traiteur pour mettre dans
sa file de garde tous les blocs non-vides trait�s qui ont �t� obtenus.
� si le bloc re�u en param�tre est non-vide,
o s�lectionner un guichet qui acceptera d�enfiler le bloc (vous avez la responsabilit� de la
strat�gie de choix).
o si la pr�c�dente est impossible � r�aliser et toutes les files sont pleines, cr�er et ajouter
un guichet � la liste du traiteur et mettez-y le bloc.
PARAMETRES : L'adresse du traiteur
le bloc a integre
RETOUR : Rien
SPECIFICATIONS : Le traiteur doit etre initialise
*/
void entree_bloc(t_traiteur * traiteur, t_block bloc, int taille);
/*************************************************************************************************/

/*************************************** SORTIE_BLOCK ********************************************/
/* MUTATRICE
Description : Si la file de garde du traiteur n�est pas vide, la fonction retourne le bloc non-vide
qu�elle en extrait du d�but de la file. Sinon retour d�un bloc vide.
PARAMETRES : adresse du traiteur
RETOUR : un t_bloc
SPECIFICATIONS : le traiteur doit �tre initialise
*/
t_block sortie_block(t_traiteur * traiteur);
/*************************************************************************************************/

/***************************************** FREE_TRAITEUR *****************************************/
/* MUTATRICE
Description : Libere l'espace memoire du traiteur
PARAMETRES : l'adresse du t_traiteur
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : L traiteur doivent �tre initialise
*/
int free_traiteur(t_traiteur * traiteur);
/*************************************************************************************************/
#endif
