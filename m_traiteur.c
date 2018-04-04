/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_traiteur.h"

/*===============================================================================================*/
/*                                       - AIDE-MEMOIRE -
typedef struct {

t_liste_g* liste_guichet; //La tete de la liste chainee double de Guichet
t_file_block_chainee file_garde; //Liste double (en file)
int nbr_gichet;
int nbr_block;

} t_traiteur;
*/
/*===============================================================================================*/

/*===============================================================================================*/
/*===================================== FONCTIONS PRIVEES =======================================*/
/*===============================================================================================*/


/*===============================================================================================*/
/*===================================== FONCTIONS PUBLIQUE ======================================*/
/*===============================================================================================*/
/***************************************** INIT_TRAITEUR ******************************************/
/* CONSTRUCTEUR
Description : Construit un traiteur dont la liste et la file sont initialement vides
PARAMETRES : taille de la file du guichet
RETOUR : Un t_traiteur initialise
SPECIFICATIONS : Aucune
*/
t_traiteur init_traiteur(int taille) {
	t_traiteur traitr = {0};

	traitr.liste_guichet = init_liste_g(taille);
	traitr.nbr_gichet = 1;
	traitr.file_garde = init_file_block_chainee();

	return traitr;
}
/*************************************************************************************************/

/**************************************** GET_NB_GUICHET *****************************************/
/* INFORMATRICE
Description : Retourne le nombre de guichets actuellement dans la liste du traiteur
PARAMETRES : l'adresse du traiteur evalue
RETOUR : le nombre de guichet dans le traiteur
SPECIFICATIONS : Le traiteur doit être initialise
*/
int get_nb_guichet(t_traiteur * traiteur) {
	return get_nb_lguichet(traiteur->liste_guichet);
}
/**************************************************************************************************/

/************************************ GET_NB_BLOC_TRAITEUR ****************************************/
/* INFORMATRICE
Description : Retourne le nombre total de t_block non-vides dans ses guichets plus ceux présents
dans sa file de
PARAMETRES : L'adresse du t_traiteur
RETOUR : le nombre de t_bloc non-vides
SPECIFICATIONS : La file doit être initialisee
*/
int get_nb_bloc_traiteur(t_traiteur * traiteur) {
	int nb_bloc = 0;

	nb_bloc += get_bloc_lguichet(traiteur->liste_guichet);
	nb_bloc += get_nb_fileg(traiteur->liste_guichet);

	return nb_bloc;
}
/*************************************************************************************************/

/****************************************** ENTREE_BLOC ******************************************/
/* MUTATRICE
Description : Cette fonction va :
· déclencher donner_block_termine pour chacun des guichets du traiteur pour mettre dans
sa file de garde tous les blocs non-vides traités qui ont été obtenus.
· si le bloc reçu en paramètre est non-vide,
o sélectionner un guichet qui acceptera d’enfiler le bloc (vous avez la responsabilité de la
stratégie de choix).
o si la précédente est impossible à réaliser et toutes les files sont pleines, créer et ajouter
un guichet à la liste du traiteur et mettez-y le bloc.
PARAMETRES : L'adresse du traiteur
			 le bloc a integre
RETOUR : Rien
SPECIFICATIONS : Le traiteur doit etre initialise
*/
void entree_bloc(t_traiteur * traiteur, t_block bloc, int taille) {
	t_block block = { 0 };
	t_liste_g * ptr_lg = traiteur->liste_guichet;
	t_guichet guich = { 0 };
	int re = 0;

	while (ptr_lg != NULL) {
		block = donner_block_termine(&(ptr_lg->data));

		if (block.taille_bloc != 0) { //lorsquqe le bloc emis n'est pas vide
			enfiler_block_chainee(&(traiteur->file_garde), block); //enfiler le bloc dans la file \
																	 de garde
			traiteur->nbr_block = traiteur->file_garde.nb_block; //maintenir le comteur a jour
		}

		ptr_lg = ptr_lg->g_apres; //on va au prochain guichet
	}

	if (bloc.taille_bloc != 0) { //si le bloc recu en parametre
		ptr_lg = chercher_g_vide(traiteur->liste_guichet); //on va chercher un guichet avec un \
														   espace libre
		if (ptr_lg == NULL) {
			re = ajouter_g_fin(traiteur->liste_guichet, taille); //ajouter un nouveau noeud
			traiteur->nbr_gichet++;
			ptr_lg = chercher_g_fin(traiteur->liste_guichet); //aller chercher l'adresse du \
																dernier noeud
		}

		re = reception_block(&(ptr_lg->data), bloc); //on enfile le bloc dans le guichet
	}
}
/*************************************************************************************************/

/*************************************** SORTIE_BLOCK ********************************************/
/* MUTATRICE
Description : Si la file de garde du traiteur n’est pas vide, la fonction retourne le bloc non-vide
qu’elle en extrait du début de la file. Sinon retour d’un bloc vide.
PARAMETRES : adresse du traiteur
RETOUR : un t_bloc (vide si la file est vide)
SPECIFICATIONS : le traiteur doit être initialise
*/
t_block sortie_block(t_traiteur * traiteur) {

	return defiler_block_chainee(&(traiteur->file_garde));
}
/*************************************************************************************************/

/***************************************** FREE_TRAITEUR *****************************************/
/* MUTATRICE
Description : Libere l'espace memoire du traiteur
PARAMETRES : l'adresse du t_traiteur
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : L traiteur doivent être initialise
*/
int free_traiteur(t_traiteur * traiteur) {
	
	free_liste_g(traiteur->liste_guichet);
	free_file_block(&(traiteur->file_garde));
	return 1;
}
/*************************************************************************************************/
