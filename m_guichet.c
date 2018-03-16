/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_guichet.h"

/*===============================================================================================*/
/*                                       - AIDE-MEMOIRE -
typedef struct {

t_file_block* file; //pointeur d'une file d'attente
t_block bloc_traite; //bloc en traitement
int compte_rebours; //compte a rebours avant l'envoit du bloc
int ** matrice_temps; //pointeur vers une matrice dynamique

} t_guichet;

*/
/*===============================================================================================*/

/*===============================================================================================*/
/*===================================== FONCTIONS PUBLIQUE ======================================*/
/*===============================================================================================*/

/***************************************** INIT_GUICHET ******************************************/
/* CONSTRUCTEUR
Description : recoit la taille de la file d'attente. Elle
construit le tableau dynamique necessaire pour la file et en cas de succes de l'allocation va fixer
la taille, le debut, la fint et le nombre d'elements (en cas d'echec de l'allocation, tous
les membres du t_file_block et du t_guichet seront nuls (0 ou NULL). Elle retourne le nouvel objet.
PARAMETRES : la taille de la file
RETOUR : Un t_guichet ayant les informations en entree
SPECIFICATIONS : la taille doit etre positif
*/
/*************************************************************************************************/
t_guichet init_guichet(int taille_file) {
	t_guichet guich = { 0 };

	if (taille_file > 0) {
		guich.file = init_file_block(taille_file).tab_block;
		guich.matrice_temps = init_mat_temps();
	}
	return guich;
}

/************************************** get_nb_bloc_guichet **************************************/
/* INFORMATRICE
Description : Retourne le nombre de t_block non_vide dans le guichet (dans la file d'attente ET
celui en traitement
PARAMETRES : l'adresse du guichet evalue
RETOUR : le nombre de t_block dans le guichet
SPECIFICATIONS : Le guichet doit être initialise
*/
/*************************************************************************************************/
int get_nb_bloc_guichet(t_guichet* guich) {
	return (guich->bloc_traite.taille_bloc == 0) ? guich->file->nb_block :
		guich->file->nb_block + 1;
}

/*************************************** RECEPTION_BLOCK *****************************************/
/* MUTATRICE
Description : Si possible, insere le bloc dans la file du guichet et retourne 1, retour de 0 sinon
PARAMETRES :l'adresse du t_guichet
& le bloc
RETOUR : Renvoit un "1" si l'insertion a reussit & "0" sinon.
SPECIFICATIONS : La file doit être initialisee
*/
/*************************************************************************************************/
int reception_block(t_guichet* guich, t_block bloc) {
	return enfiler_block(guich->file, bloc); //La verification de la taille est dans la fonction
}

/************************************* DONNER_BLOCK_TERMINE **************************************/
/* MUTATRICE
Description : Dont le fonctionnement est donné par l’algorithme suivant :
·         Si le compte à rebours est > 0,  le décrémenter de 1,
o   retourner un bloc vide.
·         Sinon (le compte à rebours est <= 0),
o   copier le bloc en traitement dans un bloc temporaire
o   défiler si possible un bloc de la file qui devient le nouveau bloc en traitement déterminer son
temps de traitement qui sera assigné à son compte à rebours
o   sinon, bloc en traitement = bloc vide et compte à rebours = 0
o   retourner le bloc temporaire
PARAMETRES : l'adresse du t_guichet
RETOUR : Retourne un t_block : vide si le compteur (compte_rebours) n'est pas a zero
celui en traitement si le compteur est à zero
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
/*************************************************************************************************/
t_block donner_block_termine(t_guichet * guich) {
	t_block bloc_tempo = { 0 }, bloc_vide = { 0 };

	if (guich->compte_rebours > 0) {
		guich->compte_rebours--;
		return bloc_vide;
	}
	else {
		bloc_tempo = guich->bloc_traite;
		if (defiler_block(guich->file, &(guich->bloc_traite))) {
			guich->compte_rebours = determiner_temps(guich);
			return bloc_tempo;
		}
		else {
			guich->compte_rebours = 0;
			return bloc_vide;
		}
	}
}

/***************************************** FREE_GUICHET ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique du guichet
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
/*************************************************************************************************/
int free_guichet(t_guichet * guich) {
	free_file_block(guich->file);
	free_mat(guich);
}

/*===============================================================================================*/
/*===================================== FONCTIONS PRIVEES =======================================*/
/*===============================================================================================*/

/*************************************** INIT_MAT_TEMPS ******************************************/
/* CONSTRUCTEUR
Description : Sert à obtenir l’allocation dynamique de la matrice carrée (TAILLE x TAILLE) puis à 
	la remplir de valeurs aléatoires dans l’intervalle [MINV..MAXV] défini par les constantes 
	appropriées.  Cette fonction ne sera utilisée que par la fonction init_guichet.
PARAMETRES : AUCUN
RETOUR : l'Adresse du pointeur de la matrice (NULL si l'allocation a echouee)
SPECIFICATIONS : AUCUNE
*/
/*************************************************************************************************/
static int ** init_mat_temps(void);
static int ** init_mat_temps(void) {
	int ** ptr_mat = NULL; //initialisation du pointeur
	int i = 0, j = 0; //Compteur pour les boucles
	
	srand(time(NULL)); //initialisation de la fonction rand()

	ptr_mat = (int**)calloc(TAILLE, sizeof(int*));
	if (ptr_mat == NULL)
		return NULL;

	for (i = 0; i < TAILLE; i++) {
		ptr_mat[i] = (int*)calloc(TAILLE, sizeof(int));
		if (ptr_mat[i] == NULL)
			return NULL;
	}

	//Remplissage de la matrice
	for (i = 0; i < TAILLE; i++) {
		for (j = 0; j < TAILLE; j++) {
			ptr_mat[i][j] = (MINV + rand()) % MAXV;
		}
	}
	
	return ptr_mat;
}

/************************************** DETERMINER_TEMPS *****************************************/
/* INFORMATRICE
Description : Sert à déterminer le temps de traitement d’un bloc dans le guichet, le temps est 
	obtenu de la somme des valeurs d’une ligne de la matrice de la colonne 0 jusqu’à la colonne 
	d’arrêt qui ne dépend que de la taille du bloc admis au traitement.
PARAMETRES : AUCUN
RETOUR : l'Adresse du pointeur de la matrice (NULL si l'allocation a echouee)
SPECIFICATIONS : AUCUNE
*/
/*************************************************************************************************/
static int determiner_temps(t_guichet * guich);
static int determiner_temps(t_guichet * guich){
	if (guich->bloc_traite.taille_bloc != 0 && guich->matrice_temps != NULL) { 
	//on s'assure que le bloc en traitement n'est pas un block vide et que la matrcice existe	
		int somme = 0, ligne = 0, col_arr = 0;
		int i = 0;

		ligne = (int)(guich->bloc_traite.f_identifiant) % TAILLE;
		col_arr = (int)((guich->bloc_traite.taille_bloc) / TAILLE_MAX_BLOCK) * TAILLE;

		for (i = 0; i < col_arr; i++) {
			somme += (guich->matrice_temps)[ligne][i];
		}

		return somme;
	}
}

/***************************************** FREE_MAT ******************************************/
/* MUTATRICE
Description : Libere les tableaux dynamique de la matrice dynamique
PARAMETRES : l'adresse du t_guichet
RETOUR : "1" si les liberations se sont faits et "0" sinon
SPECIFICATIONS : La file et le guichet doivent être initialises
*/
/*************************************************************************************************/
void free_mat(t_guichet* guich);
void free_mat(t_guichet* guich) {
	int i = 0, j = 0;

	for (i = 0; i < TAILLE; i++) {
		free(guich->matrice_temps[i]); guich->matrice_temps[i] = NULL;
	}
	
	free(guich->matrice_temps); guich->matrice_temps = NULL;

	return;
}
