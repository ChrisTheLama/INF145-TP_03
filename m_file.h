
/*---------------------------------------------------*/
/* 	  par Christophe Lamarche et Guillaume Forget  	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module file comprend les fonctions utiles pour le traitement 
d'une file de t_block.


*/
/*==========================================================*/

/*Si n'est pas encore défini*/
#ifndef DEF_FILE
#define DEF_FILE

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
// le type t_file_block est publique,
// il donne les propriétés d'un élément d'une file de block
typedef struct {

	t_block *tab_block;		//pointeur de la file

	int taille;				//taille maximale de la file

	int debut;				//position du début de la file

	int fin;				//position de la fin de la file

	int nb_block;			//nombre d'élément dans la file

}t_file_block;
/*==========================================================*/



// DÉCLARATIONS DES FONCTIONS PUBLIQUES
/*==========================================================*/
/* MUTATRICE
initialiser la file de block, une action obligée pour
ensuite obtenir l'ensemble des services offerts par le module

PARAMETRE(s): taille de la file

SORTIE: 1 pour réussite/ 0 pour échec

SPECS:
*/
t_file_block init_file_block(int taille);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
détruit la file de block et libère son espace mémoire

PARAMETRE(s): la file à détruire

SORTIE: rien

SPECS: la file doit être vide puisque la fonction ne libère pas 
l'espace mémoire des blocks qu'elle pourrait contenir
*/
void free_file_block(t_file_block* file);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
enfile un block dans la file

PARAMETRE(s):	-la file
				-le block a ajouter

SORTIE: 1/0 réussite/échec

SPECS: si la file est pleine, la fonction retourne 0 et le 
block n'est pas enfiler
*/
int enfiler_block(t_file_block* file, t_block block);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
défile un block dans la file

PARAMETRE(s):	-la file
				-le block dépilé

SORTIE: 1/0 réussite/échec

SPECS: si la file est vide, la fonction retourne 0 et le
block n'est pas défiler
*/
int defiler_block(t_file_block* file, t_block* block);
/*==========================================================*/

#endif
