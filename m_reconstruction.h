/*---------------------------------------------------*/
/*    	par Guillaume Forget 	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module de reconstruction offre le type t_reconstruction et 
plusieurs fonctions pour recréer le fichier à partir des blocs 
créés.

Le module a besoin des modules précédents m_decoupage 
et m_regroupement

Le module offre plusieurs fonctions qui modifient le
système de reconstruction(mutatrices) et d'autres le renseigent 
sans modifications (informatrices).

*/
/*==========================================================*/

#ifndef M_RECONSTRUCTION
#define M_RECONSTRUCTION 1


//modules complémentaires
#include "m_decoupage.h"
#include "m_regroupement.h"
#include <string.h>


/*==========================================================*/
// LES CONSTANTES

//Grosseur initiale de la reconstruction
#define GROSSEUR_RECONSTRUCTION 50

//Grosseur ajoutée à chaque agrandissement
#define GROSSEUR_AJOUT 100

/*==========================================================*/

/*==========================================================*/
// LES TYPE DEF
/*type t_reconstruction publique pour contenir les données pour
la reconstruction*/
typedef struct {

	unsigned int f_identifiant;		//identifiant unique du fichier

	t_block * tab_bloc;				//l'adresse du tableau dynamique contenant les blocs

	unsigned int taille_tab;		//taille du tablau créant le tableau

	unsigned int nb_bloc;			//nombre de bloc dans le tableau

	unsigned int nb_bloc_total;		//nombre de bloc total du fichier

}t_reconstruction; //structure de regroupement des blocs pour un fichier
/*==========================================================*/



// DÉCLARATIONS DES FONCTIONS PUBLIQUES

/*==========================================================*/
/* MUTATRICE
reçoit l'identifiant du fichier et la taille initiale du 
tableau. construit une structure de t_reconstruction.

PARAMETRE(s):
-id du fichier
-nombre initial de bloc contenu dans la reconstruction

SORTIE:
un t_regroupement de la taille donnée et avec l'id du fichier.
si l'opération est un échec, retourne un t_reconstruction vide.

SPECS: rien
*/
t_reconstruction init_reconstruction(unsigned int id, int taille);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
reçoit un t_regroupement et une nouvelle taille et 
redimensionne le t_reconstruction avec la nouvelle taille.

PARAMETRE(s):
-regroupement de reconstruction
-nouvelle taille

SORTIE:
1/0 selon réussite

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
1/0 selon réussite

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
1/0 selon réussite

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
le nombre de bloc présent dans la reconstruction

SPECS:
*/
int blocs_dans_reconstruction(const t_reconstruction * rec);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
retourne si la reconstruction à tous les blocs du fichier

PARAMETRE(s):
-regroupement de reconstruction

SORTIE:
1 si tous les blocs sont là et 0 sinon

SPECS:
*/
int etat_reconstruction(const t_reconstruction * rec);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
Écrit tout les blocs dans un fichier binaire si la 
reconstruction est prête. ouvre le fichier et vérifie que 
l'ouverture en écriture est réussit.

PARAMETRE(s):
-regroupement de reconstruction
-un fichier

SORTIE:
1/0 selon réussite

SPECS: libère les espaces de t_bloc
*/
int reconstruire_fich(t_reconstruction * rec, const char *nom_fichier);
/*==========================================================*/


#endif