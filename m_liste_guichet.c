/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_liste_guichet.h"

/*===============================================================================================*/
/*                                       - AIDE-MEMOIRE -
typedef t_guichet	t_element;
typedef t_liste_g*	t_liste_g *;
typedef struct {
t_element data;
t_liste_g * g_avant;
t_liste_g * g_apres;
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
Description : recoit le t_guich qui sera des donné. Elle initialise les parametres d'un element
(noeud) (t_liste_g)
PARAMETRES : taille de la file du guichet
RETOUR : Une adresse d'un t_liste_g ayant les informations en entree
SPECIFICATIONS : Aucun
*/
t_liste_g* init_liste_g(int taille) {
	t_liste_g* l_guich = NULL; //pointeur sur le noeud de la liste

	l_guich = (t_liste_g *)calloc(1, sizeof(t_liste_g)); //allocation de memoire pour le noeud 
	if (l_guich == NULL) return l_guich; //retourne un t_liste_g vide

	l_guich->data = init_guichet(taille); //Initialisation d'un guichet vide

	l_guich->g_avant = NULL; //initialisation a NULL
	l_guich->g_apres = NULL; //initialisation a NULL

	return l_guich;
}
/*************************************************************************************************/

/**************************************** GET_NB_LGUICHET *****************************************/
/* INFORMATRICE
Description : Retourne le nombre de t_liste_g non_vide dans la chaine dynamique (dans la file
d'attente ET celui en traitement
PARAMETRES : l'adresse du t_liste_g en tete
RETOUR : le nombre de t_liste_g dans la chaine
SPECIFICATIONS :
*/
int get_nb_lguichet(t_liste_g* l_guich_tete) {
	int qte = 0; //compteur de guichet / noeud dans la liste
	t_liste_g * ptr = l_guich_tete; //pointeur pour la navigation dans la liste

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
t_liste_g * chercher_g_fin(t_liste_g* l_guich) {
	t_liste_g * ptr = l_guich; //pointeur pur la navigation dans la liste

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
t_liste_g * chercher_g_debut(t_liste_g* l_guich) {
	t_liste_g * ptr = l_guich; //pointeur pour la navigation dans la liste de guichet

	while (ptr->g_avant != NULL) { //tant qu'on a pas le dernier noeud
		ptr = ptr->g_avant; //on va vers le prochain
	}

	return ptr;
}
/*************************************************************************************************/

/**************************************** AJOUTER_G_FIN ******************************************/
/* MUTATRICE
Description : Ajouter un noeud (t_liste_g) a la fin de la chaine
PARAMETRES : adresse de la fin de l_guich  (NULL si nouvelle liste)
RETOUR : L'addresse de la nouvelle fin de l_guich
SPECIFICATIONS : La file doit être initialisee
*/
t_liste_g* ajouter_g_fin(t_liste_g* fin_l_guich, int taille) {
	t_liste_g * ptr = NULL; //pointeur pour la navigation dans la liste
	t_liste_g * n_l_guich = NULL; //nouveau noeud dans la liste

	n_l_guich = init_liste_g(taille);
	if (n_l_guich == NULL) return 0; //si l'initialisation a echoue

	if (fin_l_guich != NULL) //on s'assure que la liste existe 
		ptr = fin_l_guich; //aller chercher le dernier noeud

	//ajout
	ptr->g_apres = n_l_guich; //on ajoute a la fin le pointeur vers le noeud
	n_l_guich->g_avant = ptr; //on ajoute un lien du nouveau noeud vers la liste

	return n_l_guich;
}
/*************************************************************************************************/

/**************************************** ENLEVER_G_DEBUT ****************************************/
/* MUTATRICE
Description : ¸Enleve le premier noeud de la liste
PARAMETRES : l'adresse de la tete du t_liste_g 
RETOUR : Retourne l'adresse de la nouvelle tete & NULL si la chaine est vide
SPECIFICATIONS :
*/
t_liste_g * enlever_g_debut(t_liste_g* l_guich) {
	t_liste_g *ptr = l_guich; //pointeur pour la navigation dans la liste
	t_liste_g *ptr_tete = NULL; //pointeur de la nouvelle tete de la liste

	if (l_guich == NULL) //si le dernier noeud
		return NULL; 

	ptr_tete = ptr->g_apres; //nouvelle adresse de la tete

	free_noeud_lg(ptr); //liberation de la tete du noeud

	return ptr_tete;
}
/*************************************************************************************************/

/***************************************** FREE_NOEUD_LG ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique du guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
int free_noeud_lg(t_liste_g * l_guich) {
	free(l_guich); l_guich = NULL; //liberation de la memoire
	return 1;
}
/*************************************************************************************************/

/***************************************** FREE_LISTE_G ******************************************/
/* MUTATRICE
Description : Libere l'entierete de la liste de guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
int free_liste_lg(t_liste_g * l_guich) {
	t_liste_g* ptr_liste = l_guich;

	while (ptr_liste != NULL) //on libere tant qu'on a des guichet
		ptr_liste = enlever_g_debut(ptr_liste); //libere la tete et renvoit l'adresse de la \
												//nouvelle tete
	return 1;
}
/*************************************************************************************************/

/************************************** CHERCHER_DATA_G ******************************************/
/* MUTATRICE
Description :
PARAMETRES : l'adresse du t_liste_g
RETOUR : Le guichet dans la liste t_liste_g
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
t_guichet chercher_data_g(t_liste_g * l_guich) {
	return l_guich->data;
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
t_liste_g * chercher_g_vide(t_liste_g* l_guich) {
	t_liste_g* ptr = l_guich; //pointeur de navigation dans la liste de guichet

	while (ptr != NULL && guichet_case_vide(&(ptr->data)) == 0) { //tant qu'un guichet n'a pas un 
																  //espace vide dans sa file
		ptr = ptr->g_apres;
	}

	return ptr;
}
/*************************************************************************************************/

/**************************************** GET_BLOC_LGUICHET **************************************/
/* INFORMATRICE
Description : Retourne le nombre total de t_block non-vides dans sa liste de guichet
PARAMETRES : L'adresse de la tête de la liste
RETOUR : Renvoit le nombre de t_bloc non-vide
SPECIFICATIONS : La file doit être initialisee
*/
int get_bloc_lguichet(t_liste_g* l_guich) {
	t_liste_g * ptr = l_guich; //pointeur pour la navigation dans la liste
	int nb_guichet = 0; //compteur

	while (ptr != NULL) { //pour tout les noeuds
		nb_guichet += get_nb_bloc_guichet(&(ptr->data)); //Le nombre de bloc dans le noeud
		ptr = ptr->g_apres; //on va au prochain noeud
	}

	return nb_guichet;
}
