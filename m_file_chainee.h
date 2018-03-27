/*-----------------------------------------------------------------------------------------------*/
/* 	                        par Christophe Lamarche et Guillaume Forget                      	 */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
/*Le module file chain�e comprend les fonctions utiles pour le traitement d'une file chain�e de 
t_block. Cette file est utiliser pour entreposer les blocs qui sortent des guichets une fois 
trait�.
*/
/*===============================================================================================*/

/*Si n'est pas encore d�fini*/
#ifndef DEF_FILE_CHAINEE
#define DEF_FILE_CHAINEE

/*===============================================================================================*/
//qui permet de d�sactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS
/*===============================================================================================*/

/*===============================================================================================*/
// Librairies � inclure
#include "m_decoupage.h"

/*===============================================================================================*/
// LES CONSTANTES


/*===============================================================================================*/

/*===============================================================================================*/
// type qui d�fini un noeud dans la liste chain�e de block
typedef struct noeud_block t_noeud;

// type qui d�fini un lien.
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
/*===============================================================================================*/

// D�CLARATIONS DES FONCTIONS PUBLIQUES
/*===============================================================================================*/
/* MUTATRICE
DESCRIPTION: enfile un block dans la file chain�e de block. Elle cr�e un nouveau noeud et ajoute 
le bloc dans ce noeud. Comme c'est une file, le bloc est ajout� � la fin.

PARAMETRE(s):	-la file
				-le block a ajouter

SORTIE: 1/0 r�ussite/�chec

SPECS: retourne 0 si l'allocation de m�moire �choue.
*/
int enfiler_block_chainee(t_file_block_chainee* file, t_block bloc);
/*===============================================================================================*/

/*===============================================================================================*/
/* MUTATRICE
DESCRIPTION: d�file un block dans la file chain�e de block. Elle copie les donn�es dans le bloc 
en param�tre et d�truit le noeud dans la chaine qui entreposais le bloc. Les donn�es du bloc en 
param�tre seront �cras�es

PARAMETRE(s):	-la file
				-un bloc

SORTIE:	0/1 selon r�ussite ou �chec

SPECS: La fonction retourne 0 si la file est vide et qu'elle ne peut retourner un bloc.
*/
int defiler_block_chainee(t_file_block_chainee* file, t_block* bloc);
/*===============================================================================================*/

#endif



