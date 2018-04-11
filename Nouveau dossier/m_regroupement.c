/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_regroupement.h"

/*===============================================================================================*/
/*                                       - AIDE-MEMOIRE -
typedef struct {
unsigned int id_fichier; // identifiant unique d'un fichier
t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
unsigned int taille_tab; //taille du tableau dynamique
unsigned int nbr_bloc; //nombre de t_bloc dans le tableau dynamique
} t_regroupement;
t_regroupement * reg ----> pointeur vers le regroupement
*/
/*===============================================================================================*/

/*===============================================================================================*/
/*===================================== FONCTIONS PUBLIQUE ======================================*/
/*===============================================================================================*/

/*===============================================================================================*/
/*
t_regroupement init_regroupement (unsigned int id, int taille)
Description : recoit l'identifiant unique d'un fichier et la taille maximale de la pile.
Elle construit le tableau dynamique necessaire et en cas de succes de
l'allocation va fixer la taille, l'identifiant unique et le nombre de d'elements
(en cas d'echec de l'allocation, tous les membres du t_regroupement seront nuls
(0 ou NULL). Elle retourne le nouvel objet
*/
/*===============================================================================================*/

t_regroupement init_regroupement(unsigned int id, int taille)
{
	t_regroupement objet = { 0 }; //initialisation d'un objet t_regroupement
	
	// allocation dynamique de la memoire necessaire pour le t_regroupement lors de son initiation
	if (taille > 0) {
		objet.ptr_bloc = (t_block *)calloc(taille, sizeof(t_block));
	}
	//Remplissage du t_regroupement de l'id et de sa taille
	if (objet.ptr_bloc != NULL){
		objet.taille_tab = taille;
		objet.id_fichier = id;
		objet.nbr_bloc = 0;
	}
	else { printf("ERREUR : lors de l'allocation dynamique du t_regroupement");} //message d'erreur

	return objet; //retour du t_regroupement
}
/*===============================================================================================*/
/*
int empiler_bloc (t_regroupement * reg, t_block bloc)
Description : Va empiler le block recu si les conditions necessaires sont satisfaites, elle
copie le bloc dans le tableau et retourne 1 si l'action reussit et 0 sinon.
*/
/*===============================================================================================*/

int empiler_bloc(t_regroupement * reg, t_block bloc)
{
		//verification de l'etat de la pile
		if (pile_blocs_pleine(reg) != 0) //si la pile est pleine
		{
			return (int)0; //retourne que le push a failli
		}
		else //sinon
		{
			// Depose (push) les informations du bloc dans la case mémoire de la pile
			// (prend en compte que la première espace mémoire est la case 0
			*(reg->ptr_bloc + pile_blocs_nombre(reg)) = bloc;
			// informe du depot du bloc dans la pile
			(reg->nbr_bloc)++;
			// le push est complete
			return (int)1; //retourne la reussite du push
		}
}

/*===============================================================================================*/
/*	
int depiler_bloc (t_regroupement * reg, t_bloc * bloc)
Description : Va depiler un bloc si les conditions necessaires sont satisfaites, elle copie le
t_block du haut dans la reference recue en parametre et retourne 1 si l'action
est reussi et 0 sinon.
*/
/*===============================================================================================*/

int depiler_bloc(t_regroupement * reg, t_block * bloc)
{
	if ((pile_blocs_vide(reg)) != 0)
	{
		return (int)0;//le pop a failli -- La pile est vide
	}
	else
	{
		// on enleve un bloc dans la pile
		(reg->nbr_bloc)--;

		// on transmet les informations dans le bloc
		*bloc = *(reg->ptr_bloc + reg->nbr_bloc);
		return (int)1; // le pop a ete reussis
	}
}

/*===============================================================================================*/
/*	
int pile_blocs_pleine (const t_regroupement * reg)
Description : Retourne 1 si la pile est pleine et 0 sinon.
*/
/*===============================================================================================*/
int pile_blocs_pleine(const t_regroupement * reg)
{	//si le nombre de bloc dans la pile correspond a sa taille donc la pile est pleine sinon non.
	return (pile_blocs_nombre(reg) == (pile_blocs_taille(reg))) ? ((int)1) : ((int)0);
}

/*===============================================================================================*/
/*	
int pile_blocs_vide (const t_regroupement * reg)
Description : retourne 1 si la pile est vide et 0 sinon.
*/
/*===============================================================================================*/
int pile_blocs_vide(const t_regroupement * reg)
{//si la quantite de bloc dans la pile est 0 donc la pile est vide, sinon non.
	return (pile_blocs_nombre(reg) == 0) ? (int)1 : (int)0;
}

/*===============================================================================================*/
/*	
int pile_blocs_taille (const t_regroupement * reg)
Description : Retourne le nombre maximum de t_block dans la pile.
*/
/*===============================================================================================*/
int pile_blocs_taille(const t_regroupement * reg)
{	//retourne la taille du tableau alloue pour la pile
	return  reg->taille_tab;
}

/*===============================================================================================*/
/*	
int pile_blocs_nombre (const t_regroupement * reg)
Description : Retourne le nombre de t_block actuellement dans la pile
*/
/*===============================================================================================*/
int pile_blocs_nombre(const t_regroupement * reg)
{//retourne le nombre de bloc dans la pile
	return reg->nbr_bloc;
}

/*===============================================================================================*/
/*	
void free_pile_blocs (t_regroupement * reg)
Description : libere le tableau dynamique et remet tous les membres à 0 ou NULL
*/
/*===============================================================================================*/
void free_pile_blocs(t_regroupement * reg)
{//liberation de la pile et le lien vers le tableau supprime
	free(reg->ptr_bloc); reg->ptr_bloc = NULL;
}

