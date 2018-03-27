
/*---------------------------------------------------*/
/* 	  par Christophe Lamarche et Guillaume Forget  	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module file chain�e comprend les fonctions utiles pour le 
traitement d'une file chain�e de t_block.


*/
/*==========================================================*/

/*Si n'est pas encore d�fini*/
#ifndef DEF_FILE_CHAINEE
#define DEF_FILE_CHAINEE

/*=========================================================*/
//qui permet de d�sactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*=========================================================*/


/*=========================================================*/
// Librairies usuelles � inclure
#include "m_decoupage.h"

/*==========================================================*/
// LES CONSTANTES



/*==========================================================*/


/*==========================================================*/
// type qui d�fini un noeud dans la liste chain�e de block

typedef struct noeud_block t_noeud;

typedef t_noeud* t_lien_block;

struct noeud_block{

	t_block data;					//pointeur du block
		
	t_lien_block precedent;			//pointeur du bloc pr�c�dent

	t_lien_block suivant;			//pointeur du bloc suivant

};


// le type t_file_block_chainee est publique,
// il donne les propri�t�s d'un �l�ment d'une file de block
typedef struct {

	t_lien_block tete;				//position du d�but de la file

	t_lien_block queue;				//position de la fin de la file

	int nb_block;					//nombre d'�l�ment dans la file

}t_file_block_chainee;
/*==========================================================*/



// D�CLARATIONS DES FONCTIONS PUBLIQUES
/*==========================================================*/

/* MUTATRICE
enfile un block dans la file chain�e de block

PARAMETRE(s):	-la file
				-le block a ajouter

SORTIE: 1/0 r�ussite/�chec

SPECS: si la file est pleine, la fonction retourne 0 et le
block n'est pas enfiler
*/
void enfiler_block_chainee(t_file_block_chainee* file, t_block block);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
d�file un block dans la file chain�e de block

PARAMETRE(s):	-la file

SORTIE: un bloc

SPECS: 
*/
t_block defiler_block_chainee(t_file_block_chainee *file);
/*==========================================================*/

#endif



