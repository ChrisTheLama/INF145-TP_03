/*-----------------------------------------------------------------------------------------------*/
/*  	                     par Christopher Lamarche et Guillaume Forget                        */
/*-----------------------------------------------------------------------------------------------*/
/*
Ce module inclus les fonctions pour la gestion des files chainee de t_block dans le module de
regroupement des guichets. Oermet de stocker les blocks qui sortent des guichets
*//*=============================================================================================*/
#include "m_file_chainee.h"
/*===============================================================================================*/

/*===============================================================================================*/
/*                                     CONSTANTES PRIVÉES                                        */
/*===============================================================================================*/



/*===============================================================================================*/
/*                                     FONCTIONS PRIVÉES                                         */
/*===============================================================================================*/

/*************************************************************************************************/
//  initialiser un noeud
/*************************************************************************************************/
static t_lien_block init_noeud(t_block bloc);
static t_lien_block init_noeud(t_block bloc) {

	//declaration d'un noeud
	t_lien_block noeud_temp = { 0 };

	//allocation de l'espace memoire du noeud
	noeud_temp = (t_lien_block)calloc(1, sizeof(struct noeud_block));

	if (noeud_temp != NULL) {

		//copie le bloc dans le noeud
		noeud_temp->data = bloc;
	}

	return noeud_temp;
}


/*===============================================================================================*/
/*                                    FONCTIONS PUBLIQUES                                        */
/*===============================================================================================*/

/*************************************************************************************************/
//  initialiser la file chainee de block
/*************************************************************************************************/
t_file_block_chainee init_file_block_chainee() {

	//declaration d'une file
	t_file_block_chainee file = { 0 };

	//retourne la file
	return file;
}

/*************************************************************************************************/
//  enfiler un block
/*************************************************************************************************/
int enfiler_block_chainee(t_file_block_chainee* file, t_block bloc) {

	//declaration d'un noeud temporaire
	t_lien_block noeud_temp;


	//creer un nouveau noeud
	noeud_temp = init_noeud(bloc);

	//si la creation du noeud est un echec
	if (noeud_temp == NULL) {
		return 0;
	}

	//si la file est vide
	if (file->nb_block < 1) {

		//ajouter le noeud e la file
		file->tete = noeud_temp;
		file->queue = noeud_temp;
	}
	else {	//si la file n'est pas vide

			//lien entre nouveau noeud et le dernier de la file
		noeud_temp->precedent = file->queue;

		//lien entre le dernier de la file et le nouveau noeud
		file->queue->suivant = noeud_temp;

		//enfiler le bloc e la suite de la file
		file->queue = noeud_temp;
	}

	//ajouter au nombre de bloc
	file->nb_block++;

	return 1;

}

/*************************************************************************************************/
//  defiler un block
/*************************************************************************************************/
t_block defiler_block_chainee(t_file_block_chainee* file) {
	t_block bloc = { 0 }; // bloc de reception
	t_lien_block tete_temp = { 0 };  

	//si la file est vide
	if (file->nb_block < 1) {
		return bloc;
	}

	//si la file a un element
	if (file->nb_block == 1) {

		//defiler un block
		bloc = file->tete->data;

		//libere la tete
		free(file->tete); 
		file->tete = NULL;		//On enleve les liens avec le noeud
		file->queue = NULL;		//on enleve les liens avec le noeud
	}

	//si la file a plus d'un element
	if (file->nb_block > 1) {

		//defiler un block
		bloc = file->tete->data;

		//changer la tete
		tete_temp = file->tete->suivant;

		//liberer la tete
		free(file->tete);

		//nouvelle tete
		file->tete = tete_temp;

		file->tete->precedent = NULL;
	}

	//soustraire au nombre de bloc
	file->nb_block--;

	//retourne un bloc
	return bloc;

}
/*************************************************************************************************/
/*===============================================================================================*/

/*================================== GET_NB_FILEG ================================================*/
/* INFORMATRICE
DESCRIPTION: Retourne le nombre de t_bloc dans la file de garde
PARAMETRE(s): l'adresse de la file de garde
SORTIE:	le nombre de t_bloc dans la file de garde
SPECS: La file doit etre initialisee
*/
int get_nb_fileg(const t_file_block_chainee* file) {
	return file->nb_block;
}
/*===============================================================================================*/

/*====================================== FREE_BLOCK_CHAINEE =====================================*/
/* MUTATRICE
DESCRIPTION: Libere l'espace memoire de la file de garde //vide au complet
PARAMETRE(s): l'adresse de la file de garde
SORTIE: Rien
SPECS: La file doit etre initialisee
*/
void free_block_chainee(t_file_block_chainee* file) {
	if (file->nb_block > 0) { //si il y a des block dans la file
		while (file->nb_block > 0) { //sur la totalite des blocs
			defiler_block_chainee(file); //on defile dans le vide
		}
	}
}
/*===============================================================================================*/