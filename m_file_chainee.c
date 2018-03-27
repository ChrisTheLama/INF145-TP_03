/*-----------------------------------------------------------------------------------------------*/
/*  	                     par Christopher Lamarche et Guillaume Forget                        */
/*-----------------------------------------------------------------------------------------------*/
/*
Ce module inclus les fonctions pour la gestion des files chainée de t_block dans le module de 
regroupement des guichets. Oermet de stocker les blocks qui sortent des guichets
*//*=============================================================================================*/
#include "m_file_chainee.h"

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

	//déclaration d'un noeud
	t_lien_block noeud_temp = { 0 };

	//allocation de l'espace mémoire du noeud
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
//  initialiser la file chainée de block
/*************************************************************************************************/
t_file_block_chainee init_file_block_chainee() {

	//déclaration d'une file
	t_file_block_chainee file = { 0 };

	//retourne la file
	return file;
}

/*************************************************************************************************/
//  enfiler un block
/*************************************************************************************************/
int enfiler_block_chainee(t_file_block_chainee* file, t_block bloc) {

	//déclaration d'un noeud temporaire
	t_lien_block noeud_temp;


	//créer un nouveau noeud
	noeud_temp = init_noeud(bloc);

	//si la création du noeud est un échec
	if (noeud_temp == NULL){
		return 0;
	}

	//si la file est vide
	if (file->nb_block < 1){

		//ajouter le noeud à la file
		file->tete = noeud_temp;
		file->queue = noeud_temp;
	}
	else{	//si la file n'est pas vide

		//lien entre nouveau noeud et le dernier de la file
		noeud_temp->precedent = file->queue;

		//lien entre le dernier de la file et le nouveau noeud
		file->queue->suivant = noeud_temp;

		//enfiler le bloc à la suite de la file
		file->queue = noeud_temp;
	}

	//ajouter au nombre de bloc
	file->nb_block++;

	return 1;
	
}

/*************************************************************************************************/
//  défiler un block
/*************************************************************************************************/
int defiler_block_chainee(t_file_block_chainee* file, t_block* bloc) {

	t_lien_block tete_temp = { 0 };

	//si la file est vide
	if (file->nb_block < 1){
		return 0;
	}

	//si la file a un élément
	if (file->nb_block == 1){

		//défiler un block
		*bloc = file->tete->data;

		//libère la tête
		free(file->tete);
	}

	//si la file a plus d'un élément
	if (file->nb_block > 1) {

		//défiler un block
		*bloc = file->tete->data;

		//changer la tête
		tete_temp = file->tete->suivant;
		
		//libèrer la tête
		free(file->tete);

		//nouvelle tete
		file->tete = tete_temp;

		file->tete->precedent = NULL;
	}

	//soustraire au nombre de bloc
	file->nb_block--;

	//retourne un bloc
	return 1;		
	
}
/*************************************************************************************************/
/*===============================================================================================*/






























