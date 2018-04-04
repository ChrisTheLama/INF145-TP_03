/*-----------------------------------------------------------------------------------------------*/
/*								par Christophe Lamarche & Frederic Thibault			   		     */
/*-----------------------------------------------------------------------------------------------*/

/*===============================================================================================*/
#include "m_guichet.h"

/*===============================================================================================*/
/*                                       - AIDE-MEMOIRE -
typedef struct {

t_file_block file; //pointeur d'une file d'attente
t_block bloc_traite; //bloc en traitement
int compte_rebours; //compte a rebours avant l'envoit du bloc
int ** matrice_temps; //pointeur vers une matrice dynamique

} t_guichet;

*/
/*===============================================================================================*/

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
static int **init_mat_temps(void);

static int **init_mat_temps(void) {

	int **ptr_mat = NULL; //initialisation du pointeur
	int i = 0, j = 0; //Compteur pour les boucles

	srand((int)time(NULL)); //initialisation de la fonction rand()

	ptr_mat = (int**)malloc(TAILLE * sizeof(int*)); //tableau de pointeur de taille TAILLE
	if (ptr_mat == NULL) printf("ERREUR POINTEUR POINTEUR DU TAB DYNAMIQUE");

	for (i = 0; i < TAILLE; i++) {
		ptr_mat[i] = (int*)malloc(TAILLE * sizeof(int));
		if (ptr_mat[i] == NULL) printf("ERREUR POINTEUR %d DU TAB DYNAMIQUE",i);
	}

	//Remplissage de la matrice
	for (i = 0; i < TAILLE; i++) {
		for (j = 0; j < TAILLE; j++) {
			ptr_mat[i][j] = (int) (MINV + (rand() % (MAXV-MINV)));
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
RETOUR : Le temps d'attente pour le bloc
SPECIFICATIONS : AUCUNE
*/
/*************************************************************************************************/
static int determiner_temps(t_guichet * guich);
static int determiner_temps(t_guichet * guich) {
	if (guich->bloc_traite.taille_bloc != 0 && guich->matrice_temps != NULL) {
		//on s'assure que le bloc en traitement n'est pas un block vide et que la matrcice existe	
		int somme = 0, ligne = 0, col_arr = 0;
		int i = 0;

		ligne = (int)((guich->bloc_traite.f_identifiant) % TAILLE);
		col_arr = (int) (((float)(guich->bloc_traite.taille_bloc) / TAILLE_MAX_BLOCK) * TAILLE);

		for (i = 0; i <= col_arr; i++) {
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
static int free_mat(t_guichet* guich);
static int free_mat(t_guichet* guich) {
	int compteur = 0;

	for (compteur = 0; compteur < TAILLE; compteur++) {
		free(guich->matrice_temps[compteur]);
		guich->matrice_temps[compteur] = NULL;
	}

	free(guich->matrice_temps); guich->matrice_temps = NULL;
	return 1;
}

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
		guich.file = init_file_block(taille_file);
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
	return (guich->bloc_traite.taille_bloc == 0) ? guich->file.nb_block :
		guich->file.nb_block + 1;
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
	return enfiler_block(&(guich->file), bloc); //La verification de la taille est dans la fonction
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
		//defiler_block(&(guich->file), &(guich->bloc_traite)); 

		if (defiler_block(&(guich->file), &(guich->bloc_traite))) {
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
	
	free_mat(guich);
	free_file_block(&(guich->file));
	 
	return 1;
}

/*************************************** GUICHET_CASE_VIDE ***************************************/
/* INFORMATRICE
Description : Informe si le guichet a un espace vide
PARAMETRES : l'adresse du guichet evalue
RETOUR : retourne '1' si il y a de l'espace dans le guichet, '0' sinon
SPECIFICATIONS : Le guichet doit être initialise
*/
int guichet_case_vide(t_guichet* guich) {
	int i = 0;
	while (guich->file.tab_block[i].taille_bloc != 0 && i < guich->file.taille) {
		i++;
	}
	if (i>= guich->file.taille){
		return 0;
	}
	else { return 1; }
}
/*************************************************************************************************/
