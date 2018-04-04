/*-----------------------------------------------------------------------------------------------*/
/* 	                        par Christophe Lamarche et Guillaume Forget                      	 */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
/*Le module file chainee comprend les fonctions utiles pour le traitement d'une file chainee de
t_block. Cette file est utiliser pour entreposer les blocs qui sortent des guichets une fois
traite.
*/
/*===============================================================================================*/

/*Si n'est pas encore defini*/
#ifndef DEF_FILE_CHAINEE
#define DEF_FILE_CHAINEE

/*===============================================================================================*/
//qui permet de desactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*===============================================================================================*/

/*===============================================================================================*/
// Librairies e inclure
#include "m_decoupage.h"

/*===============================================================================================*/
// LES CONSTANTES


/*===============================================================================================*/

/*===============================================================================================*/
// type qui defini un noeud dans la liste chainee de block
typedef struct noeud_block t_noeud;

// type qui defini un lien.
typedef t_noeud* t_lien_block;

struct noeud_block {

	t_block data;					//pointeur du block

	t_lien_block precedent;			//pointeur du bloc precedent

	t_lien_block suivant;			//pointeur du bloc suivant

};

// le type t_file_block_chainee est publique,
// il donne les proprietes d'un element d'une file de block
typedef struct {

	t_lien_block tete;				//position du debut de la file

	t_lien_block queue;				//position de la fin de la file

	int nb_block;					//nombre d'element dans la file

}t_file_block_chainee;
/*===============================================================================================*/


/*************************************************************************************************/
//  initialiser la file chainee de block
t_file_block_chainee init_file_block_chainee();
/*************************************************************************************************/


// DeCLARATIONS DES FONCTIONS PUBLIQUES
/*===============================================================================================*/
/* MUTATRICE
DESCRIPTION: enfile un block dans la file chainee de block. Elle cree un nouveau noeud et ajoute
le bloc dans ce noeud. Comme c'est une file, le bloc est ajoute e la fin.

PARAMETRE(s):	-la file
-le block a ajouter

SORTIE: 1/0 reussite/echec

SPECS: retourne 0 si l'allocation de memoire echoue.
*/
int enfiler_block_chainee(t_file_block_chainee* file, t_block bloc);
/*===============================================================================================*/

/*===============================================================================================*/
/* MUTATRICE
DESCRIPTION: defile un block dans la file chainee de block. Elle copie les donnees dans le bloc
en parametre et detruit le noeud dans la chaine qui entreposais le bloc. Les donnees du bloc en
parametre seront ecrasees

PARAMETRE(s):	-la file
-un bloc

SORTIE:	le bloc recupere

SPECS: La fonction retourne 0 si la file est vide et qu'elle ne peut retourner un bloc.
*/
t_block defiler_block_chainee(t_file_block_chainee* file);
/*===============================================================================================*/

/*================================== GET_NB_FILEG ================================================*/
/* INFORMATRICE
DESCRIPTION: Retourne le nombre de t_bloc dans la file de garde 
PARAMETRE(s): l'adresse de la tete de la file de garde
SORTIE:	le nombre de t_bloc dans la file de garde
SPECS: La file doit etre initialisee
*/
int get_nb_fileg(t_file_block_chainee* file);
/*===============================================================================================*/

/*====================================== FREE_BLOCK_CHAINEE =====================================*/
/* MUTATRICE
DESCRIPTION: Libere l'espace memoire de la file de garde
PARAMETRE(s): l'adresse de la file de garde
SORTIE:	Rien
SPECS: La file doit etre initialisee
*/
void free_block_chainee(t_file_block_chainee* file);
/*===============================================================================================*/
#endif


