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
t_file_block_chainee* init_file_block() {

	//déclaration d'une file
	t_file_block_chainee* file = { 0 };

	//créer 1er noeud
	file->tete = calloc(1, sizeof(t_noeud_block));
	file->queue = file->tete;

	//retourne la file
	return file;
}



/*==========================================================*/
//  détruire un noeud
/*==========================================================*/
void free_noeud_block(t_noeud_block* noeud) {

	//libére l'espace mémoire de la file
	free(file->tab_block);

	//efface les données de la file
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

	return 1;		//enfilage réussi
	
	return 0;		//échec de l'enfilage
}

/*==========================================================*/
//  défiler un block
/*==========================================================*/
int defiler_block_chainee(t_file_block_chainee* file, t_block* block) {

	t_noeud_block *tete_temp = { 0 };

	//si la file n'est pas vide
	if (file->nb_block > 0) {

		//défiler un block
		block = file->tete->data;

		//changer la tête
		tete_temp = file->tete;
		
		//libèrer la tête
		free(file->tete);

		//nouvelle tete
		file->tete = tete_temp->suivant;

		return 1;		//défilage réussi
	}

	return 0;		//échec du défilage
}


/*==========================================================*/
/*==========================================================*/






























