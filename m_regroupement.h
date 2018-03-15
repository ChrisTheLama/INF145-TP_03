/*---------------------------------------------------*/
/*    	par Richard Boudreault et Guillaume Forget 	 */
/*---------------------------------------------------*/

/*==========================================================*/
/*
Le module de regroupement offre le type t_regroupement et 
plusieurs fonctions liées. 

Le module a besoin des modules précédents m_decoupage

Le module offre plusieurs fonctions qui modifient le
système de regroupement(mutatrices) et d'autres le renseigent
sans modifications (informatrices).

*/
/*==========================================================*/



#ifndef M_REGROUPEMENT
#define M_REGROUPEMENT 1

//inclus le module complémentaire
#include "m_decoupage.h"


/*==========================================================*/
// LES CONSTANTES

//Grosseur maximale de la pile de regroupement
#define GROSSEUR_REGROUPEMENT 20

/*==========================================================*/


// LES TYPE DEF
/*type t_regroupement publique pour contenir les données pour
le regroupement des données aquises du fichier*/
typedef struct {

	unsigned int f_identifiant; //identifiant unique du fichier

	t_block * pile;      //l'adresse du tableau dynamique contenant les blocs

	unsigned int taille_tab;   //taille du tablau créant la pile

	unsigned int nb_bloc;   //nombre de bloc dans la pile 

}t_regroupement; //structure de regroupement des blocs pour un fichier




// DÉCLARATIONS DES FONCTIONS PUBLIQUES

/*==========================================================*/
/* MUTATRICE
initialise un tableau dynamique de grandeur "taille" pour le
stokage des blocs.

PARAMETRE(s): 
-id du fichier
-nombre maximal de bloc contenu dans le regroupement

SORTIE:
un t_regroupement avec l'id du fichier et le nombre de bloc max 
si l'initialisation est réussit et un t_regroupement vide si 
l'initialisation est imposible.

SPECS: 
rien
*/
t_regroupement init_regroupement(unsigned int id, int taille);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
ajoute le bloc dans le tableau dynamique de bloc du 
t_regroupement

PARAMETRE(s):
-un regroupement de bloc d'un fichier
-un bloc a jouter dans le regroupement de bloc

SORTIE:
1 pour réussite et 0 pour échec

SPECS:
il doit y avoir un espace libre dans le tableau de bloc
*/
int empiler_bloc(t_regroupement * reg, t_block bloc);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
prend un bloc dans la pile de regroupement de bloc et le 
retourne dans "bloc"

PARAMETRE(s):
-un regroupement de bloc
-un bloc vide pour stocker le bloc extrait

SORTIE:
-1/0 pour réussite ou échec

SPECS: il doit y avoir au moins un bloc dans la pile
*/
int depiler_bloc(t_regroupement * reg, t_block * bloc);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
vérifie si la pile de regroupement de bloc est pleine

PARAMETRE(s): un regroupement de bloc

SORTIE: 1 si la pile est pleine et 0 sinon

SPECS: rien
*/
int pile_blocs_pleine(const t_regroupement * reg);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
vérifie si la pile de regroupement de bloc est vide

PARAMETRE(s): un regroupement de bloc

SORTIE: 1 si la pile est vide et  sinon

SPECS: rien
*/
int pile_blocs_vide(const t_regroupement * reg);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
retourne le maximum du bloc possible dans la pile

PARAMETRE(s): le regroupement de bloc

SORTIE: le nombre maximal de bloc dans la pile

SPECS: rien
*/
int pile_blocs_taille(const t_regroupement * reg);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
retourne le nombre de bloc dans la pile

PARAMETRE(s): un regroupement de bloc

SORTIE: le nombre de bloc dans la pile

SPECS: rien
*/
int pile_blocs_nombre(const t_regroupement * reg);
/*==========================================================*/

/*==========================================================*/
/* INFORMATRICE
retourne l'id du fichier du regroupement de bloc

PARAMETRE(s): un regroupement de bloc

SORTIE: l'id du fichier du regroupement de bloc

SPECS: rien
*/
unsigned int obtenir_id_fichier(const t_regroupement * reg);
/*==========================================================*/

/*==========================================================*/
/* MUTATRICE
libère l'espace du regroupement de bloc

PARAMETRE(s): un regroupement de bloc

SORTIE: rien

SPECS: rien
*/
void free_pile_blocs(t_regroupement * reg);
/*==========================================================*/


#endif