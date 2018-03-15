/*---------------------------------------------------*/
/*    	par Guillaume Forget 	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module de reconstruction offre le type t_reconstruction et 
plusieurs fonctions pour recr�er le fichier � partir des blocs 
cr��s.

Le module a besoin des modules pr�c�dents m_decoupage 
et m_regroupement

Le module offre plusieurs fonctions qui modifient le
syst�me de reconstruction(mutatrices) et d'autres le renseigent 
sans modifications (informatrices).

*/
/*==========================================================*/

#ifndef M_RECONSTRUCTION
#define M_RECONSTRUCTION 1


//modules compl�mentaires
#include "m_decoupage.h"
#include "m_regroupement.h"
#include <string.h>


/*==========================================================*/
// LES CONSTANTES

//Grosseur initiale de la reconstruction
#define GROSSEUR_RECONSTRUCTION 50

//Grosseur ajout�e � chaque agrandissement
#define GROSSEUR_AJOUT 100

/*==========================================================*/

/*==========================================================*/
// LES TYPE DEF
/*type t_reconstruction publique pour contenir les donn�es pour
la reconstruction*/
typedef struct {

	unsigned int f_identifiant;		//identifiant unique du fichier

	t_block * tab_bloc;				//l'adresse du tableau dynamique contenant les blocs

	unsigned int taille_tab;		//taille du tablau cr�ant le tableau

	unsigned int nb_bloc;			//nombre de bloc dans le tableau

	unsigned int nb_bloc_total;		//nombre de bloc total du fichier

}t_reconstruction; //structure de regroupement des blocs pour un fichier
/*==========================================================*/



// D�CLARATIONS DES FONCTIONS PUBLIQUES

/*==========================================================*/
/* MUTATRICE
re�oit l'identifiant du fichier et la taille initiale du 
tableau. construit une structure de t_reconstruction.

PARAMETRE(s):
-id du fichier
-nombre initial de bloc contenu dans la reconstruction

SORTIE:
un t_regroupement de la taille donn�e et avec l'id du fichier.
si l'op�ration est un �chec, retourne un t_reconstruction vide.

SPECS: rien
*/
t_reconstruction init_reconstruction(unsigned int id, int taille);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
re�oit un t_regroupement et une nouvelle taille et 
redimensionne le t_reconstruction avec la nouvelle taille.

PARAMETRE(s):
-regroupement de reconstruction
-nouvelle taille

SORTIE:
1/0 selon r�ussite

SPECS: rien
*/
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
ajouter un bloc dans le tableau de reconstruction si possible

PARAMETRE(s):
-regroupement de reconstruction
-un bloc

SORTIE:
1/0 selon r�ussite

SPECS: il doit y avoir assez de place pour ajouter un bloc
*/
int ajouter_bloc(t_reconstruction * rec, t_block bloc);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
ajoute tous les blocs de la pile de regroupement dans la 
reconstruction. modifie la taille du regroupement de 
reconstruction au besoin.

PARAMETRE(s):
-regroupement de reconstruction
-pile de regroupement

SORTIE:
1/0 selon r�ussite

SPECS: rien
*/
int ajouter_pile_blocs(t_reconstruction * rec, t_regroupement *reg);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICES
retourne le nombre de bloc dans la reconstruction

PARAMETRE(s):
-regroupement de reconstruction

SORTIE:
le nombre de bloc pr�sent dans la reconstruction

SPECS:
*/
int blocs_dans_reconstruction(const t_reconstruction * rec);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
retourne si la reconstruction � tous les blocs du fichier

PARAMETRE(s):
-regroupement de reconstruction

SORTIE:
1 si tous les blocs sont l� et 0 sinon

SPECS:
*/
int etat_reconstruction(const t_reconstruction * rec);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
�crit tout les blocs dans un fichier binaire si la 
reconstruction est pr�te. ouvre le fichier et v�rifie que 
l'ouverture en �criture est r�ussit.

PARAMETRE(s):
-regroupement de reconstruction
-un fichier

SORTIE:
1/0 selon r�ussite

SPECS: lib�re les espaces de t_bloc
*/
int reconstruire_fich(t_reconstruction * rec, const char *nom_fichier);
/*==========================================================*/


#endif