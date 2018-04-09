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

#ifndef  __MODULE__LISTE__GUICHET__
#define  __MODULE__LISTE__GUICHET__

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
#include"m_guichet.h"
/*************************************************************************************************/

/*===================================== LES CONSTANTES ==========================================*/

/*===============================================================================================*/

/*************************************************************************************************/
/*************************************************************************************************/
typedef struct liste_g t_liste_g;

struct liste_g {

	t_guichet data;
	t_liste_g * g_avant;
	t_liste_g * g_apres;

};


/***************************************** NOM FONCTION ******************************************/
/*
donne
PARAMETRES :
RETOUR :
SPECIFICATIONS :
*/
/*************************************************************************************************/

/***************************************** INIT_LISTE_G ******************************************/
/* CONSTRUCTEUR
Description : recoit la taille de la file d'attente. Elle
construit le tableau dynamique necessaire pour la file et en cas de succes de l'allocation va fixer
la taille, le debut, la fint et le nombre d'elements (en cas d'echec de l'allocation, tous
les membres du t_file_block et du t_guichet seront nuls (0 ou NULL). Elle retourne le nouvel objet.
PARAMETRES : RIEN
RETOUR : Un t_guichet ayant les informations en entree
SPECIFICATIONS : la taille doit etre positif
*/
t_liste_g* init_liste_g(int taille);
/*************************************************************************************************/

/**************************************** GET_NB_GUICHET *****************************************/
/* INFORMATRICE
Description : Retourne le nombre de t_block non_vide dans le guichet (dans la file d'attente ET
celui en traitement
PARAMETRES : l'adresse du guichet evalue
RETOUR : le nombre de t_block dans le guichet
SPECIFICATIONS : Le guichet doit être initialise
*/
int get_nb_lguichet(t_liste_g* l_guich_tete);
/**************************************************************************************************/

/**************************************** CHERCHER_G_FIN ******************************************/
/* INFORMATRICE
Description : Donne l'adresse du dernier noeud de la chaine
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit un "1" si l'insertion a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
t_liste_g * chercher_g_fin(t_liste_g* l_guich);
/*************************************************************************************************/

/**************************************** CHERCHER_G_DEBUT ***************************************/
/* INFORMATRICE
Description : Donne l'adresse du dernier noeud de la chaine
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit un "1" si l'insertion a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
t_liste_g * chercher_g_debut(t_liste_g* l_guich);
/*************************************************************************************************/

/**************************************** AJOUTER_G_FIN ******************************************/
/* MUTATRICE
Description : Ajouter un noeud (t_liste_g) a la fin de la chaine
PARAMETRES : adresse de la fin de l_guich  (NULL si nouvelle liste)
RETOUR : L'addresse de la nouvelle fin de l_guich
SPECIFICATIONS : La file doit être initialisee
*/
t_liste_g* ajouter_g_fin(t_liste_g* fin_l_guich, int taille);
/*************************************************************************************************/

/**************************************** ENLEVER_G_DEBUT ****************************************/
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
t_liste_g * enlever_g_debut(t_liste_g* l_guich);
/*************************************************************************************************/

/***************************************** FREE_NOEUD_LG ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique du guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
int free_noeud_lg(t_liste_g * l_guich);
/*************************************************************************************************/

/***************************************** FREE_LISTE_G ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique du guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
int free_liste_lg(t_liste_g * l_guich);
/*************************************************************************************************/

/************************************** CHERCHER_DATA_G ******************************************/
/* MUTATRICE
Description :
PARAMETRES : l'adresse du t_liste_g
RETOUR : Le guichet dans la liste t_liste_g
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
t_guichet chercher_data_g(t_liste_g * l_guich);
/*************************************************************************************************/

/**************************************** CHERCHER_G_VIDE ****************************************/
/* INFORMATRICE
Description : Donne l'adresse du dernier noeud de la chaine
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit l'adresse du premier noeud avec de l'espace dans le guichet
SPECIFICATIONS : La file doit être initialisee
*/
t_liste_g * chercher_g_vide(t_liste_g* l_guich);
/*************************************************************************************************/

/**************************************** GET_BLOC_LGUICHET **************************************/
/* INFORMATRICE
Description : Retourne le nombre total de t_block non-vides dans sa liste de guichet
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit le nombre de t_bloc non-vide
SPECIFICATIONS : La file doit être initialisee
*/
int get_bloc_lguichet(t_liste_g* l_guich);
/*************************************************************************************************/

#endif
