/*----------------------------------------------------*/
/* 	par Guillaume Forget */
/*----------------------------------------------------*/

//inclus le header
#include "m_reconstruction.h"


/*==========================================================*/
//  initialiser le module de reconstruction
/*==========================================================*/
/*cr�e et retourne un t_reconstruction avec les valeurs de
l'id du fichier et la taille du tableau de bloc 
*/
t_reconstruction init_reconstruction(unsigned int id, int taille) {

	//initialise une reconstruction de type t_reconstruction � 0
	t_reconstruction reconstruction = { 0 };

	//cr�e un tablau de taille donn�e de type t_reconstruction
	reconstruction.tab_bloc = (t_block *)calloc(taille, sizeof(t_block));

	//rempli la reconstruction si l'allocation est r�ussit
	if (reconstruction.tab_bloc != NULL) {

		reconstruction.f_identifiant = id;		//remplie l'id du fichier dans le t_regroupement

		reconstruction.taille_tab = taille;		//rempli la taille dans le t_regroupement
	}
	return reconstruction;
}
/*==========================================================*/


/*==========================================================*/
//  redimensionner le module de reconstruction
/*==========================================================*/
/*la fonction ajoute plus d'espace pour stoker les blocs.
*/
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille) {

	t_block *nouveau_tab;		//adresse nouveau tableau de blocks

	//initialise un nouveau tableau de la nouvelle taille
	nouveau_tab = (t_block *)calloc(nouvelle_taille, sizeof(t_block));

	//v�rifie que la cr�ation du nouveau reconstruction � fonctionn�
	if (nouveau_tab != NULL) {
		
		//copier les donn�es dans le nouveau tableau
		memcpy(nouveau_tab, rec->tab_bloc, rec->nb_bloc * sizeof(t_block) );
	
		//supprimer l'ancier tableau
		free(rec->tab_bloc);

		//renvoit la nouvelle taille
		rec->taille_tab = nouvelle_taille;

		//retourner le nouveau tableau
		rec->tab_bloc = nouveau_tab;

		return 1;
	}
	return 0;
}
/*==========================================================*/


/*==========================================================*/
//  ajoute un bloc dans le module de reconstruction
/*==========================================================*/
/*la fonction ajoute le bloc qu'elle re�oit dans la 
reconstruction. ingr�mente le nombre de bloc dans la 
reconstruction
*/
int ajouter_bloc(t_reconstruction * rec, t_block bloc) {

	//v�rifie que la place du bloc est vide
	if (rec->tab_bloc[bloc.num_bloc].f_identifiant == NULL){

		rec->tab_bloc[bloc.num_bloc] = bloc;		//copie le bloc

		rec->nb_bloc += 1;		//modification du nombre de bloc

		return 1;				//retourne 1
	}
	return 0;		//la place n'est pas vide, retourne 0
}
/*==========================================================*/


/*==========================================================*/
//  ajoute une pile de bloc dans le module de reconstruction
/*==========================================================*/
/*la fonction ajoute lla pile de bloc qu'elle re�oit dans la
reconstruction. 
*/
int ajouter_pile_blocs(t_reconstruction * rec, t_regroupement *reg) {

	int valide;		//variable pour v�rification
	t_block bloc;	//un bloc

	//redimensionner le tableau s'il n'est pas assez gros pour d�piler la pile
	while ((rec->taille_tab - rec->nb_bloc) < (reg->nb_bloc)) {

		//extension du tableau
		valide = redim_reconstruction(rec, rec->taille_tab + GROSSEUR_AJOUT);

		//validation de l'ajout de cases au tableau
		if(!valide){
			return 0;
		}
	}

	//copie des donn�es
	while (!pile_blocs_vide(reg)) {

		//d�piler un bloc
		valide = depiler_bloc(reg, &bloc);

		//validation du d�pillage d'un bloc
		if (!valide){
			return 0;
		}

		//ajouter un bloc
		valide = ajouter_bloc(rec, bloc);

		//validation de l'ajout du bloc
		if (!valide) {
			return 0;
		}
	}
	return 1;
}
/*==========================================================*/


/*==========================================================*/
//  retourne le nombre de bloc dans la reconstruction
/*==========================================================*/
/*retourne le nombre de bloc dans la reconstruction
*/
int blocs_dans_reconstruction(const t_reconstruction * rec) {

	return rec->nb_bloc;	//retourne le nombre de bloc dans la reconstruction
}
/*==========================================================*/


/*==========================================================*/
//  v�rifie que la reconstruction est pr�te
/*==========================================================*/
/*retourne 1 si le nombre de bloc dans la reconstruction est 
�gale au nombre de bloc pour reconstruire le fichier.
*/
int etat_reconstruction(const t_reconstruction * rec) {

	//v�rifier que ce bloc est le bloc final
	if (rec->nb_bloc_total >0){

		return 1;
	}

	return 0;
} 
/*==========================================================*/


/*==========================================================*/
//  reconstruit le fichier
/*==========================================================*/
/*la fonction cr�e une copie du fichier pr�sent dans la 
reconstruction
*/
int reconstruire_fich(t_reconstruction * rec, const char *nom_fichier) {
	
	unsigned int terminer = 0;		//pour arreter la boucle
	unsigned int i = 0;				//compteur de bloc
	FILE *fich;						//pointeur du fichier

	//ouverture du fichier
	fich = fopen(nom_fichier, "wb");

	//v�rification de l'ouverture du fichier
	if (fich == NULL){
		return 0;
	}

	do{
		//�criture d'un bloc
		fwrite(rec->tab_bloc[i].buffer, sizeof(unsigned char), rec->tab_bloc[i].taille_bloc, fich);

		//lib�re rle bloc qui vient d'�tre �crit
		free(rec->tab_bloc[i].buffer);

		//v�rifier si le dernier bloc
		terminer = rec->tab_bloc[i].bloc_final;

		i++; //ingr�menter le bloc � �crire

	} while (!terminer);
	
	//effacer la m�moire dynamique
	free(rec->tab_bloc);

	//fermer le fichier
	fclose(fich);

	return 1;
}