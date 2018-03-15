
/*---------------------------------------------------*/
/* 	  par Christophe Lamarche et Guillaume Forget  	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module file comprend les fonctions utiles pour le traitement 
d'une file de t_block.


*/
/*==========================================================*/

/*Si n'est pas encore d�fini*/
#ifndef DEF_FILE
#define DEF_FILE

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
// le type t_file_block est publique,
// il donne les propri�t�s d'un �l�ment d'une file de block
typedef struct {

	t_block *tab_block;		//pointeur de la file

	int taille;				//taille maximale de la file

	int debut;				//position du d�but de la file

	int fin;				//position de la fin de la file

	int nb_block;			//nombre d'�l�ment dans la file

}t_file_block;
/*==========================================================*/



// D�CLARATIONS DES FONCTIONS PUBLIQUES
/*==========================================================*/
/* MUTATRICE
initialiser la file de block, une action oblig�e pour
ensuite obtenir l'ensemble des services offerts par le module

PARAMETRE(s): taille de la file

SORTIE: 1 pour r�ussite/ 0 pour �chec

SPECS:
*/
t_file_block init_file_block(int taille);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
d�truit la file de block et lib�re son espace m�moire

PARAMETRE(s): la file � d�truire

SORTIE: rien

SPECS: la file doit �tre vide puisque la fonction ne lib�re pas 
l'espace m�moire des blocks qu'elle pourrait contenir
*/
void free_file_block(t_file_block* file);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
enfile un block dans la file

PARAMETRE(s):	-la file
				-le block a ajouter

SORTIE: 1/0 r�ussite/�chec

SPECS: si la file est pleine, la fonction retourne 0 et le 
block n'est pas enfiler
*/
int enfiler_block(t_file_block* file, t_block block);
/*==========================================================*/



/*==========================================================*/
/* MUTATRICE
d�file un block dans la file

PARAMETRE(s):	-la file
				-le block d�pil�

SORTIE: 1/0 r�ussite/�chec

SPECS: si la file est vide, la fonction retourne 0 et le
block n'est pas d�filer
*/
int defiler_block(t_file_block* file, t_block* block);
/*==========================================================*/

#endif
