
/*----------------------------------------------------*/
/*  	par Christopher Lamarche et Guillaume Forget  */
/*----------------------------------------------------*/
/*

*//*==========================================================*/
#include "m_file.h"





/*==========================================================*/
//CONSTANTES PRIV�ES





/*==========================================================*/



/*==========================================================*/
//  fonctions priv�es factorisant le proc�d� de d�coupage







/*==========================================================*/


/*==========================================================*/
// LES D�FINITIONS DES FONCTIONS D'INTERFACE

/*==========================================================*/
//  initialiser la file de block
/*==========================================================*/
t_file_block init_file_block(int taille){

	//d�claration d'une file
	t_file_block temp_file = { 0 };

	//assigner l'espace m�moire correspondant
	temp_file.tab_block = (t_block*) calloc(taille, sizeof(t_block));

	if (temp_file.tab_block != NULL){

		//init taille
		temp_file.taille = taille;

		//init fin de la file
		temp_file.debut = -1; 
	}

	//retourne la file
	return temp_file;		
}

/*==========================================================*/
//  d�truire la file de block
/*==========================================================*/
void free_file_block(t_file_block* file) {

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
int enfiler_block(t_file_block* file, t_block block) {

	//si la file n'est pas pleine
	if (file->taille > file->nb_block){

		//changer la position de fin de la file
		file->fin += 1 % file->taille;

		//enfiler un block
		file->tab_block[file->fin] = block;

		//changer nb de block dans la file
		file->nb_block += 1;

		return 1;		//enfilage r�ussi
	}
	return 0;		//�chec de l'enfilage
}

/*==========================================================*/
//  d�filer un block
/*==========================================================*/
int defiler_block(t_file_block* file, t_block* block) {

	//si la file n'est pas vide
	if (file->nb_block > 0) {

		//d�filer un block
		*block = file->tab_block[file->debut];

		//changer position du d�but
		file->debut += 1 % file->taille;

		//changer nb de block dans la file
		file->nb_block -= 1;

		return 1;		//d�filage r�ussi
	}
	return 0;		//�chec du d�filage
}

/*==========================================================*/
/*==========================================================*/

