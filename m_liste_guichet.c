/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_liste_guichet.h"

/*===============================================================================================*/
/*                                       - AIDE-MEMOIRE -
typedef t_guichet	t_element;
typedef t_liste_g*	t_ptr;

typedef struct {

t_element data;
t_ptr g_avant;
t_ptr g_apres;

} t_liste_g;
*/
/*===============================================================================================*/

/*===============================================================================================*/
/*===================================== FONCTIONS PRIVEES =======================================*/
/*===============================================================================================*/


/*===============================================================================================*/
/*===================================== FONCTIONS PUBLIQUE ======================================*/
/*===============================================================================================*/

/***************************************** INIT_LISTE_G ******************************************/
/* CONSTRUCTEUR
Description : recoit le t_guich qui sera des donné. Elle initialise les parametres du t_liste_g
PARAMETRES : t_guichet 
RETOUR : Une adresse d'un t_liste_g ayant les informations en entree
SPECIFICATIONS : Aucun
*/
t_liste_g* init_liste_g(t_guichet guich) {
	t_liste_g* l_guich = NULL;

	l_guich = (t_ptr)malloc(sizeof(t_liste_g)); //allocation de memoire pour le noeud 
	if (l_guich == NULL) return l_guich; //retourne un t_liste_g vide

	l_guich->data = guich; //initialisation
	l_guich->g_avant = NULL; //initialisation 
	l_guich->g_apres = NULL; //initialisation

	return l_guich;
}
/*************************************************************************************************/

/**************************************** GET_NB_GUICHET *****************************************/
/* INFORMATRICE
Description : Retourne le nombre de t_liste_g non_vide dans la chaine dynamique (dans la file 
d'attente ET celui en traitement
PARAMETRES : l'adresse du t_liste_g en tete 
RETOUR : le nombre de t_liste_g dans la chaine
SPECIFICATIONS : 
*/
int get_nb_guichet(t_liste_g* l_guich_tete) { 
	int qte = 0;
	t_ptr ptr = l_guich_tete;

	do {
		qte++; //incrementation du compteur
		ptr = ptr->g_apres; //on traite le prochain noeud
	} while (ptr != NULL); //tant que le prochain noeud n'est pas NULL (fin de la chaine)

	return qte;
}
/*************************************************************************************************/

/**************************************** CHERCHER_G_FIN *****************************************/
/* INFORMATRICE
Description : Donne l'adresse du dernier noeud de la chaine
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit un "1" si l'insertion a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
t_ptr chercher_g_fin(t_liste_g* l_guich) {
	t_ptr ptr = l_guich;
	
	while (ptr->g_apres != NULL) { //tant qu'on a pas le dernier noeud
		ptr = ptr->g_apres; //on va vers le prochain
	}

	return ptr;
}
/*************************************************************************************************/

/************************************** CHERCHER_G_DEBUT *****************************************/
/* INFORMATRICE
Description : Donne l'adresse du dernier noeud de la chaine
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit un "1" si l'insertion a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
t_ptr chercher_g_debut(t_liste_g* l_guich) {
	t_ptr ptr = l_guich;

	while (ptr->avant != NULL) { //tant qu'on a pas le dernier noeud
		ptr = ptr->avant; //on va vers le prochain
	}

	return ptr;
}
/*************************************************************************************************/

/**************************************** AJOUTER_G_FIN ******************************************/
/* MUTATRICE
Description : Ajouter un noeud (t_liste_g) a la fin de la chaine 
PARAMETRES : l_guich  (NULL si nouvelle liste)
RETOUR : Renvoit un "1" si l'ajout a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
int ajouter_g_fin(t_liste_g* l_guich, t_guichet guich) {
	t_ptr ptr = NULL;
	t_ptr n_l_guich = NULL;

	n_l_guich = init_liste_g(guich);
	if (n_l_guich == NULL) return 0; //si l'initialisation a echoue
	
	if (l_guich != NULL)
		ptr = chercher_g_fin(l_guich); //aller chercher le dernier noeud
	
	//ajout
	ptr->g_apres = n_l_guich;
	n_l_guich->avant = ptr;

	return 1;
}
/*************************************************************************************************/

/**************************************** ENLEVER_G_DEBUT ****************************************/
/* MUTATRICE
Description : ¸Enleve le premier noeud de la liste
PARAMETRES : l'adresse du t_guichet
RETOUR : Retourne l'adresse de la nouvelle tete & NULL si la chaine est vite
SPECIFICATIONS : 
*/
t_ptr enlever_g_debut(t_liste_g* l_guich) {
	t_ptr ptr = NULL, ptr_tete = NULL;
	
	if (l_guich != NULL) {
		ptr = chercher_g_debut(l_guich); //aller chercher le dernier noeud
		return NULL;
	}

	ptr_tete = ptr->g_apres; //nouvelle adresse de la tete
	
	free_liste_g(ptr); //liberation de la tete du noeud
	
	return ptr_tete;
}
/*************************************************************************************************/

/***************************************** FREE_LISTE_G ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique du guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
int free_liste_g(t_liste_g * l_guich) {
	free(l_guich); l_guich = NULL; //liberation de la memoire
	return 1;
}
/*************************************************************************************************/

/**************************************** CHERCHER_G_VIDE ****************************************/
/* INFORMATRICE
Description : Donne l'adresse du dernier noeud de la chaine
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit l'adresse du premier noeud avec de l'espace dans le guichet (NULL si aucune case
	vide
SPECIFICATIONS : La file doit être initialisee
*/
t_ptr chercher_g_vide(t_liste_g* l_guich) {
	t_liste_g* ptr = l_guich;
	int i = 0;

	ptr = chercher_g_debut(l_guich);

	while (guichet_case_vide(ptr) == 0 && ptr != NULL) { //tant qu'un guichet n'a pas un espace \
														  vide dans sa file
		ptr = ptr->g_apres;
	}

	return ptr;
}
/*************************************************************************************************/
