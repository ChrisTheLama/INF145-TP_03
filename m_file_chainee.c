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
t_file_block_chainee* init_file_block() {

	//d�claration d'une file
	t_file_block_chainee* file = { 0 };

	//cr�er 1er noeud
	file->tete = calloc(1, sizeof(t_noeud_block));
	file->queue = file->tete;

	//retourne la file
	return file;
}



/*==========================================================*/
//  d�truire un noeud
/*==========================================================*/
void free_noeud_block(t_noeud_block* noeud) {

	//lib�re l'espace m�moire de la file
	free(file->tab_block);

	//efface les donn�es de la file
	file->taille = 0;
	file->debut = 0;
	file->fin = 0;
	file->nb_block = 0;
	return;
}

/*==========================================================*/
//  enfiler un block
/*==========================================================*/
int enfiler_block_chainee(t_file_block_chainee* file, t_block block) {

	//si la file est vide
	if (file->tete == NULL){
		file = init_file_block();
		file->tete


	}




	//changer la position de fin de la file
	file->fin += 1 % file->taille;

	//enfiler un block
	file->tab_block[file->fin] = block;

	//changer nb de block dans la file
	file->nb_block += 1;

	return 1;		//enfilage r�ussi
	
	return 0;		//�chec de l'enfilage
}

/*==========================================================*/
//  d�filer un block
/*==========================================================*/
int defiler_block_chainee(t_file_block_chainee* file, t_block* block) {

	t_noeud_block *tete_temp = { 0 };

	//si la file n'est pas vide
	if (file->nb_block > 0) {

		//d�filer un block
		block = file->tete->data;

		//changer la t�te
		tete_temp = file->tete;
		
		//lib�rer la t�te
		free(file->tete);

		//nouvelle tete
		file->tete = tete_temp->suivant;

		return 1;		//d�filage r�ussi
	}

	return 0;		//�chec du d�filage
}


/*==========================================================*/
/*==========================================================*/






























