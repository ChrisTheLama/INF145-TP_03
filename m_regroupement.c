/*----------------------------------------------------*/
/* 	par Guillaume Forget */
/*----------------------------------------------------*/

//inclus le header
#include "m_regroupement.h"



/*==========================================================*/
//  initialiser le module de regroupement
/*==========================================================*/
/*cr�e et retourne un t_regroupement avec les valeurs de
l'id du fichier et la taille du tableau de bloc
*/
t_regroupement init_regroupement(unsigned int id, int taille) {

	//initialise un regroupement de type t_regroupement � 0
	t_regroupement regroupement = { 0 }; 

	//cr�e un tablau de taille donn�e de type t_regroupement
	regroupement.pile = (t_block *)calloc(taille, sizeof(t_block));

	//remplie le t_regroupement si l'allocation est r�ussit
	if (regroupement.pile != NULL) {

		//rempli l'id du fichier dans le t_regroupement
		regroupement.f_identifiant = id;	

		//rempli la taille dans le t_regroupement
		regroupement.taille_tab = taille;	
	}

	return regroupement;	//valeur de retour
}
/*==========================================================*/


/*==========================================================*/
//  empile un bloc
/*==========================================================*/
/*ajoute un bloc`� la pile de bloc dans le regroupement
*/
int empiler_bloc(t_regroupement * reg, t_block bloc) {

	//v�rifie si un ploc peut �tre ajout� � la pile
	if ((reg->f_identifiant == bloc.f_identifiant) && (pile_blocs_pleine(reg) == 0)) {

		//ajout du bloc dans le tableau
		reg->pile[reg->nb_bloc] = bloc;

		//changement du nombre de bloc dans le tableau
		reg->nb_bloc += 1;

		return 1; //retourne 1 pour op�ration r�ussie
	}
	return 0; //retourne 0 pour op�ration avort�e
}
/*==========================================================*/


/*==========================================================*/
//  d�pile un bloc du regroupement
/*==========================================================*/
/*retourne un bloc � partir de la pile de regroupement
*/
int depiler_bloc(t_regroupement * reg, t_block * bloc) {

	//v�rifie si la pile est vide
	if (pile_blocs_vide(reg)) {

		return 0;
	}
	else{

		//d�pile le bloc
		*bloc = reg->pile[--reg->nb_bloc];		

		return 1;
	}
}
/*==========================================================*/


/*==========================================================*/
//  v�rifie si la pile est pleine
/*==========================================================*/
/* retourne 1 si la pile est pleine
*/
int pile_blocs_pleine(const t_regroupement * reg) {

	//v�rifie si la pile est pleine
	if (reg->taille_tab > reg->nb_bloc) {

		return 0;	//la pile n'est pas pleine
	}
	else{

		return 1;	//la pile est pleine
	}
}
/*==========================================================*/


/*==========================================================*/
//  v�rifie si la pile est vide
/*==========================================================*/
/* retourne 1 si la pile est vide
*/
int pile_blocs_vide(const t_regroupement * reg) {

	//v�rifie si la pile est vide
	if (reg->nb_bloc == 0) {

		return 1;	//la pile est vide
	}
	else{

		return 0;	//la pile n'est pas vide
	}
}
/*==========================================================*/


/*==========================================================*/
//  retourne la taille du regroupement
/*==========================================================*/
/* retourne la taille maximale de bloc que peut contenir le
regroupement
*/
int pile_blocs_taille(const t_regroupement * reg) {

	return reg->taille_tab;		//nombre de bloc
}
/*==========================================================*/


/*==========================================================*/
//  retourne le nombre de bloc 
/*==========================================================*/
/* retourne le nombre de bloc dans la pile de regroupement
*/
int pile_blocs_nombre(const t_regroupement * reg) {

	return reg->nb_bloc;	//nombre de bloc dans la pile
}
/*==========================================================*/


/*==========================================================*/
//  retourne le id fichier
/*==========================================================*/
/* retourne le id du fichier du regroupement
*/
unsigned int obtenir_id_fichier(const t_regroupement * reg) {

	return reg->f_identifiant;		//id du fichier de la pile
}
/*==========================================================*/


/*==========================================================*/
//  lib�re le regroupement
/*==========================================================*/
/* lib�re le tableau dynamique et rempli les champs de NULL
*/
void free_pile_blocs(t_regroupement * reg) {

	free(reg->pile);	//lib�rer la m�moire

	//mettre � 0 les valeurs du t_regroupement
	reg->pile = NULL; 

	reg->f_identifiant = NULL;

	reg->nb_bloc = NULL;

	reg->taille_tab = NULL;

	return 1;
}
/*==========================================================*/