
/*---------------------------------------------------*/
/* 	  par Christophe Lamarche et Guillaume Forget  	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module file chainée comprend les fonctions utiles pour le 
traitement d'une file chainée de t_block.


*/
/*==========================================================*/

/*Si n'est pas encore défini*/
#ifndef DEF_FILE_CHAINEE
#define DEF_FILE_CHAINEE

/*=========================================================*/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*=========================================================*/


/*=========================================================*/
// Librairies usuelles à inclure
#include "m_decoupage.h"

/*==========================================================*/
// LES CONSTANTES



/*==========================================================*/


/*==========================================================*/
// type qui défini un noeud dans la liste chainée de block
typedef struct {

	t_block *data;				//pointeur du block
		
	t_block *precedent;			//pointeur du bloc précédent

	t_block *suivant;			//pointeur du bloc suivant

}t_noeud_block;


// le type t_file_block_chainee est publique,
// il donne les propriétés d'un élément d'une file de block
typedef struct {

	t_noeud_block *tete;						//position du début de la file

	t_noeud_block *queue;						//position de la fin de la file

	int nb_block;					//nombre d'élément dans la file

}t_file_block_chainee;
/*==========================================================*/



// DÉCLARATIONS DES FONCTIONS PUBLIQUES
/*==========================================================*/

/* MUTATRICE
enfile un block dans la file chainée de block

PARAMETRE(s):	-la file
				-le block a ajouter

SORTIE: 1/0 réussite/échec

SPECS: si la file est pleine, la fonction retourne 0 et le
block n'est pas enfiler
*/
int enfiler_block_chainee(t_file_block_chainee* file, t_block block);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
défile un block dans la file chainée de block

PARAMETRE(s):	-la file
				-le block dépilé

SORTIE: 1/0 réussite/échec

SPECS: si la file est vide, la fonction retourne 0 et le
block n'est pas défiler
*/
int defiler_block_chainee(t_file_block_chainee *file, t_block *block);
/*==========================================================*/

#endif



