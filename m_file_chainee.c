/*----------------------------------------------------*/
/*  	par Christopher Lamarche et Guillaume Forget  */
/*----------------------------------------------------*/
/*

*//*==========================================================*/
#include "m_file_chainee.h"





/*==========================================================*/
//CONSTANTES PRIV�ES





/*==========================================================*/



/*==========================================================*/
//  fonctions priv�es factorisant le proc�d� de d�coupage







/*==========================================================*/


/*==========================================================*/
// LES D�FINITIONS DES FONCTIONS D'INTERFACE

/*==========================================================*/
//  initialiser la file chain�e de block
/*==========================================================*/
t_file_block_chainee init_file_block_chainee() {

	//d�claration d'une file
	t_file_block_chainee file = { 0 };

	//retourne la file
	return file;
}


/*===============================================================================================*/
/*                                 CONSTRUCTEUR PRIV�E                                           */
/*===============================================================================================*/
/*==========================================================*/
//  initialiser un noeud
/*==========================================================*/
static t_lien_block init_noeud(t_block bloc) {

	//d�claration d'un noeud
	t_lien_block noeud_temp = { 0 };

	//allocation de son espace m�moire
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

	//d�claration d'un noeud temporaire
	t_lien_block noeud_temp;


	//cr�er un nouveau noeud
	noeud_temp = init_noeud(block);

	//si la file est vide
	if (file->nb_block < 1){

		//ajouter le noeud � la file
		file->tete = noeud_temp;
		file->queue = noeud_temp;
	}
	else{	//si la file n'est pas vide

		//lien entre nouveau noeud et le dernier de la file
		noeud_temp->precedent = file->queue;

		//lien entre le dernier de la file et le nouveau noeud
		file->queue->suivant = noeud_temp;

		//enfiler le bloc � la suite de la file
		file->queue = noeud_temp;
	}

	//ajouter au nombre de bloc
	file->nb_block++;

	return;
	
}

/*==========================================================*/
//  d�filer un block
/*==========================================================*/
t_block defiler_block_chainee(t_file_block_chainee* file) {

	t_lien_block tete_temp = { 0 };
	t_block bloc = { 0 };

	//si la file est vide
	if (file->nb_block < 1){
		return bloc;
	}

	//si la file a un �l�ment
	if (file->nb_block == 1){

		//d�filer un block
		bloc = file->tete->data;

		//lib�re la t�te
		free(file->tete);
	}

	//si la file a plus d'un �l�ment
	if (file->nb_block > 1) {

		//d�filer un block
		bloc = file->tete->data;

		//changer la t�te
		tete_temp = file->tete->suivant;
		
		//lib�rer la t�te
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






























