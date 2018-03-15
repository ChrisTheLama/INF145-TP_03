/*-----------------------------------------------------------------------------------------------*/
/* 	                         par Christophe Lamarche & Frederic Thibault    	                 */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_reconstruction.h"

/*======================================= CONSTANTE =============================================*/

#define AUGMENTE_TAB	100

/*=================================================================================================*/
/*=================================================================================================*/
/*=================================================================================================*/
/*									  - AIDE-MEMOIRE - 
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
	unsigned int taille_last_tab; //taille du tableau precedent
	unsigned int nbr_bloc_actu; //nombre de t_bloc actuellement présent
	unsigned int nbr_bloc_tot; //nombre total de t_block du fichier \
	(qu'on obtient en recevant le dernier bloc du découpage)

} t_reconstruction;
*/

/*==================================== FONCTION LOCALE ==========================================*/
/*===============================================================================================*/
/*
int rec_to_petite(t_reconstruction *rec, t_block *bloc)
Description : Evalue si la taille du tableau du t_reconstruction est assez pour recevoir les blocs
	du fichier correspondant dans la pile. En sachant que lors de l'empilage le blocs sur le dessus
	correspond au bloc ayant le plus grand numero. Alors on peut dire que si le numero du bloc est
	est plus grand que la taille alors la taille ne pourra pas recevoir la totalite des blocs du 
	fichier.
*/
/*===============================================================================================*/
int rec_to_petite(t_reconstruction *rec, t_block *bloc);
int rec_to_petite(t_reconstruction *rec, t_block *bloc) {
	if (((bloc)->num_bloc) > rec->taille_last_tab) {
		return 1;
	}
	else { return 0; }
}
/*===============================================================================================*/
/*=================================== FONCTIONS PUBLIQUE ========================================*/

/*===============================================================================================*/
/* 
t_reconstruction init_reconstruction(unsigned int id, int taille)
Description: reçoit l’identifiant unique d’un fichier et la taille initiale de son tableau de 
	reconstruction.Il construit le tableau dynamique nécessaire et en cas de succès de 
	l’allocation, le tableau est traversé et les identifiants - fichier sont tous mis à 0 dans les 
	blocs puis la fonction fixe la taille, l’identifiant unique du	fichier et le nombre total de 
	blocks à 0 (en cas d’échec l’allocation, tous les membres du t_reconstruction seront nuls(0 ou 
	NULL)).On retourne le nouvel objet.
*/
/*===============================================================================================*/
t_reconstruction init_reconstruction(unsigned int id, int taille) {
	t_reconstruction rec;
	
rec.ptr_bloc = (t_block *)calloc(taille, sizeof(t_block));

if (rec.ptr_bloc == NULL) {
	rec.id_fichier = 0;
	rec.ptr_bloc = NULL;
	rec.taille_last_tab = 0;
	rec.nbr_bloc_actu = 0;
	rec.nbr_bloc_tot = 0;
}
else {
	rec.id_fichier = id;
	//		rec.ptr_bloc => adresse du tableau dynamique
	rec.taille_last_tab = taille;
	rec.nbr_bloc_actu = 0;
	rec.nbr_bloc_tot = 0;
}

return rec;
}
/*===============================================================================================*/
/*
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille)
Description: Reçoit l’adresse d’une reconstruction et d’une taille, elle essaie de redimensionner 
	son tableau	en conservant les blocs présents(allouez un nouveau	tableau et copiez - y tous les
	blocs du tableau actuel	avec memcpy).La fonction met l’identifiant fichier à 0 dans les 
	nouvelles cases du tableau et ajuste les autres membres de la structure.On retourne 1 en cas de
	succès, 0 sinon
*/
/*===============================================================================================*/
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille) {
	int i = 0; // compteur
	t_block *ptr_new_tab = NULL; // pointeur du nouveau tableau dynamique

	ptr_new_tab = calloc(nouvelle_taille, sizeof(t_block)); //allocation du nouveau tableau

	if (ptr_new_tab == NULL) { // si l'allocation a echoue
		return (int) 0; //l'allocation a echoue
	}
	else {

		for (i = 0; i < (rec->taille_last_tab); i++) {
			*(ptr_new_tab + i) = *(rec->ptr_bloc + i);  //copie de chaque bloc dans l'ancien \
														tableau vers le nouveau
		}

		rec->taille_last_tab = nouvelle_taille; // transfert de la nouvelle taille dans le t_rec
		free_rec_tab(rec->ptr_bloc);  // liberation de l'espace memoire de l'ancien tableau
		rec->ptr_bloc = ptr_new_tab; // transfere l'adresse du nouveau tableau dans \
										le pointeur de rec;
		return (int)1; //l'allocation a reussi
	}
}

/*===============================================================================================*/
/* 
int ajouter_bloc(t_reconstruction * rec, t_block bloc)
Description: Si les conditions nécessaires sont	satisfaites, on copie le bloc dans le tableau à sa
	position et on retourne 1 si l’action réussit, 0 sinon.	On redimensionne le t_reconstruction 
	si nécessaire.
*/
/*===============================================================================================*/
int ajouter_bloc(t_reconstruction * rec, t_block bloc) {
	//Note : on est certain que l'identifiant du bloc transmis est le meme que celui du t_reconst
	while(rec_to_petite(rec,&bloc)) { // verification qu'il reste de l'espace dans le tableau
		redim_reconstruction(rec, (bloc.num_bloc + AUGMENTE_TAB)); // redimensionner du tableau
	}

	*((rec->ptr_bloc)+bloc.num_bloc) = bloc; // on incorpore le bloc a la position du numero du bloc \
									   dans le tableau de reconstruction
	
	if ((rec->ptr_bloc + bloc.num_bloc)->taille_bloc != 0) { //si la valeur de la taille de bloc a ete modifiee
		rec->nbr_bloc_actu++; //augmentation du nombre de bloc dans le tableau de reconstruction
	
		if (bloc.bloc_final == 1) {
			rec->nbr_bloc_tot = bloc.num_bloc + 1;
		}
		return (int)1; // l'ajout a reussi
	}
	return (int)0; //l'ajout a echouer
}

/*===============================================================================================*/
/* void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg)
Description: Si les deux structures sont du même fichier,	la fonction va dépiler tous les blocs 
	du regroupement pour les ajouter à la reconstruction(avec la fonction ajouter_bloc).
*/
/*===============================================================================================*/
void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg) {
	int reussite = 0; // variable sur l'indice du bloc transfere
	t_block bloc; //recepteur du bloc transfere

	//Si le bloc pret a etre depile a le meme identifiant que celui du t_reconstruction
	if ((reg->ptr_bloc + (pile_blocs_nombre(reg))-1)->f_identifiant == rec->id_fichier) {
		while (pile_blocs_vide(reg) == 0) {
			reussite = depiler_bloc(reg, &bloc);  // depile le t_regroupement
			if (reussite == 1) { // si un bloc a ete depile
				reussite--; // remet reussite = 0 
				while (ajouter_bloc(rec, bloc) == 0) {} // on s'assure que le bloc est bien ajoute au t_reconstruction
			}
		}
	}
	return;
}

/*===============================================================================================*/
/*
int bloc_dans_reconstruction(const t_reconstruction * rec)
Description: Retourne le nombre actuel de blocs du fichier dans la structure.
*/
/*===============================================================================================*/
int bloc_dans_reconstruction(const t_reconstruction * rec) {
	return rec->nbr_bloc_actu; //renvoit le nombre de bloc dans le t_reconstruction
}

/*===============================================================================================*/
/*
int etat_reconstruction(t_reconstruction * rec)
Description: Retourne 1 si tous les blocs du fichier sont dans la structure et 0 sinon.Ceci se 
	produit lorsque le nombre de t_block actuellement presents devient égal au nombre total de 
	t_block du fichier
*/
/*===============================================================================================*/
int etat_reconstruction(t_reconstruction * rec) {
	if (get_taille_restante(rec->id_fichier) == 0) { //si on a fini de couper le fichier en bloc
		if (rec->nbr_bloc_actu == get_nb_blocs_emis(rec->id_fichier)) { 
			//si la quantite de bloc dans la reconstruction est egale a la quantite de bloc \
			  emis pour le fichier
			return (int) 1;
		}
	}
	return (int)0;
}

/*===============================================================================================*/
/*
int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier)
Description: Si la reconstruction est prête(avec etat_reconstruction) et le fichier binaire est 
	bien ouvert	en écriture, tous les blocs d’octets des t_block sont écrits, en ordre, dans le
	fichier puis le fichier est fermé.La fonction libère les tableaux dynamiques d’octets dans tous
	les t_block et libère aussi le tableau de t_block dans la structure. Elle retourne 1 en cas de
	succès et 0 sinon
*/
/*===============================================================================================*/
int reconstruire_fich(t_reconstruction *rec, const char * nom_fichier) {
	int i = 0; //compteur des differents blocs dans le tableau de reconstruction
	int succes = 0; // 0 ->> la reconstruction n'est pas fini \
					  1 ->> la reconstruction est fini
	FILE * ptr_fich = NULL; // pointeur du fichier

	ptr_fich = fopen(nom_fichier, "wb"); // ouvrir le nouveau fichier
										 // & creation
	
	if (ptr_fich != NULL) { // si l'ouverture du fichier est reussi)
		while (i < (bloc_dans_reconstruction(rec))) { //si on a fait la transcription de tous les \
											blocs dans le tableau de reconstruction
			fwrite((rec->ptr_bloc + i)->buffer, (rec->ptr_bloc + i)->taille_bloc, 1, ptr_fich);
			// ecriture du contenu du bloc dans le fichier
			i++; // incrementation du bloc observe
		}
		succes = 1; // ecriture reussi
	} else { // erreur d'ouverture du fichier
		printf("** ERREUR D'OUVERTURE DU NOUVEAU FICHIER **");
	}

	fclose(ptr_fich); ptr_fich = NULL;// fermer le fichier

	return succes;
}
/*===============================================================================================*/
/*
void free_rec_tab(t_reconstruction * reg)
Description: libere le tableau dynamique et remet tous les membres à 0 ou NULL
*/
/*===============================================================================================*/
void free_rec_tab(t_reconstruction * rec) {
	if (rec->ptr_bloc != NULL) { // si le tableau du rec n'a pas deja ete libere
		free(rec->ptr_bloc); rec->ptr_bloc = NULL; // liberer le tableau et le pointeur
	}
	return;
}
/*===============================================================================================*/
