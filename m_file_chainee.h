/*-----------------------------------------------------------------------------------------------*/
/* 	                        par Christophe Lamarche et Guillaume Forget                      	 */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
/*Le module file chainée comprend les fonctions utiles pour le traitement d'une file chainée de 
t_block. Cette file est utiliser pour entreposer les blocs qui sortent des guichets une fois 
traité.
*/
/*===============================================================================================*/

/*Si n'est pas encore défini*/
#ifndef DEF_FILE_CHAINEE
#define DEF_FILE_CHAINEE

/*===============================================================================================*/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*===============================================================================================*/

/*===============================================================================================*/
// Librairies à inclure
#include "m_decoupage.h"

/*===============================================================================================*/
// LES CONSTANTES


/*===============================================================================================*/

/*===============================================================================================*/
// type qui défini un noeud dans la liste chainée de block
typedef struct noeud_block t_noeud;

// type qui défini un lien.
typedef t_noeud* t_lien_block;

struct noeud_block{

	t_block data;					//pointeur du block
		
	t_lien_block precedent;			//pointeur du bloc précédent

	t_lien_block suivant;			//pointeur du bloc suivant

};

// le type t_file_block_chainee est publique,
// il donne les propriétés d'un élément d'une file de block
typedef struct {

	t_lien_block tete;				//position du début de la file

	t_lien_block queue;				//position de la fin de la file

	int nb_block;					//nombre d'élément dans la file

}t_file_block_chainee;
/*===============================================================================================*/

// DÉCLARATIONS DES FONCTIONS PUBLIQUES
/*===============================================================================================*/
/* MUTATRICE
DESCRIPTION: enfile un block dans la file chainée de block. Elle crée un nouveau noeud et ajoute 
le bloc dans ce noeud. Comme c'est une file, le bloc est ajouté à la fin.

PARAMETRE(s):	-la file
				-le block a ajouter

SORTIE: 1/0 réussite/échec

SPECS: retourne 0 si l'allocation de mémoire échoue.
*/
int enfiler_block_chainee(t_file_block_chainee* file, t_block bloc);
/*===============================================================================================*/

/*===============================================================================================*/
/* MUTATRICE
DESCRIPTION: défile un block dans la file chainée de block. Elle copie les données dans le bloc 
en paramètre et détruit le noeud dans la chaine qui entreposais le bloc. Les données du bloc en 
paramètre seront écrasées

PARAMETRE(s):	-la file
				-un bloc

SORTIE:	0/1 selon réussite ou échec

SPECS: La fonction retourne 0 si la file est vide et qu'elle ne peut retourner un bloc.
*/
int defiler_block_chainee(t_file_block_chainee* file, t_block* bloc);
/*===============================================================================================*/

#endif



