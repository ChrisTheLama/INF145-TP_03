/*----------------------------------------------------*/
/*  	par Christopher Lamarche et Guillaume Forget  */
/*----------------------------------------------------*/
/*

*//*==========================================================*/
#include "m_file_chainee.h"





/*==========================================================*/
//CONSTANTES PRIVÉES





/*==========================================================*/



/*==========================================================*/
//  fonctions privées factorisant le procédé de découpage







/*==========================================================*/


/*==========================================================*/
// LES DÉFINITIONS DES FONCTIONS D'INTERFACE

/*==========================================================*/
//  initialiser la file chainée de block
/*==========================================================*/
t_file_block_chainee init_file_block_chainee() {

	//déclaration d'une file
	t_file_block_chainee file = { 0 };

	//retourne la file
	return file;
}


/*===============================================================================================*/
/*                                 CONSTRUCTEUR PRIVÉE                                           */
/*===============================================================================================*/
/*==========================================================*/
//  initialiser un noeud
/*==========================================================*/
static t_lien_block init_noeud(t_block bloc) {

	//déclaration d'un noeud
	t_lien_block noeud_temp = { 0 };

	//allocation de son espace mémoire
	noeud_temp = (t_lien_block) calloc(1, sizeof(struct noeud_block));

	if (noeud_temp != NULL) {
		noeud_temp->data = bloc;
	}

	return noeud_temp;
}
/*===============================================================================================*/

/*==========================================================*/
//  enfiler un block
/*==========================================================*/
void enfiler_block_chainee(t_file_block_chainee* file, t_block block) {

	//déclaration d'un noeud temporaire
	t_lien_block noeud_temp;


	//créer un nouveau noeud
	noeud_temp = init_noeud(block);

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

	return;
	
}

/*==========================================================*/
//  défiler un block
/*==========================================================*/
t_block defiler_block_chainee(t_file_block_chainee* file) {

	t_lien_block tete_temp = { 0 };
	t_block bloc = { 0 };

	//si la file est vide
	if (file->nb_block < 1){
		return bloc;
	}

	//si la file a un élément
	if (file->nb_block == 1){

		//défiler un block
		bloc = file->tete->data;

		//libère la tête
		free(file->tete);
	}

	//si la file a plus d'un élément
	if (file->nb_block > 1) {

		//défiler un block
		bloc = file->tete->data;

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
	return bloc;		
	
}


/*==========================================================*/
/*==========================================================*/






























