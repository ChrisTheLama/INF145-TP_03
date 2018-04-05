/*===============================================================================================*/
/* 											INF145 - TP3										 */
/*===============================================================================================*/

/**************************************************************************************************
Titre				:	Travail pratique numero 3
Auteur				:	Christophe Lamarche & Guillaume Forget
Date de creation	:	26/03/2018
Dernier modification:	26/03/2018
Description			:
Programmes principal du TP3.


**************************************************************************************************/




#define _CRT_SECURE_NO_WARNINGS 

//Bibliotheques standards
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Biblioth�ques compl�mentaires
#include "m_traiteur.h"
#include "m_reconstruction.h"

/*===============================================================================================*/
//CONSTANTES

/*Nombre de fichier � traiter*/
#define NB_FICHIERS 2

/*longueur de la file dans un guichet*/
#define TAILLE_FILE 5

/*nombre de caract�res maximals dans les noms des fichiers*/
#define NOM_MAX 100

/*Noms des fichiers � traiter*/
const char NOMS_FICHIERS[NB_FICHIERS][NOM_MAX] = {
	"Image.jpg",
	"musique.wma",
	};

/*===============================================================================================*/
//FONCTIONS

/*retourne la position du fichier du bloc dans le tableau de regroupement*/
int position_regroupement(const t_regroupement reg[], int taille_reg, unsigned int f_identifiant);

/*reconstruit un fichier et lib�re son espace m�moire utilis�e*/
int refaire_fich(t_reconstruction *rec, t_regroupement *reg, char *nouveau_nom, unsigned int id_fichier);

/*fonction qui imprime les propri�t�s des guichets*/
void print_guichets(t_liste_g* guich);

/*fonction qui imprime les propri�t�s d'un guichet*/
void print_guichet(t_liste_g* guich);


/*===============================================================================================*/

/*===============================================================================================*/
/*le main mandat 2-2B pour traiter plusieurs fichiers en m�me temps*/
/*===============================================================================================*/
#if(1)
int main(void) {

	int i = 0, temps = 0;						// compteur boucle
	int position = 0;							// position du regroupement/reconstruction du bloc
	t_block block = { 0 };						// accueille chaque bloc des fichiers
	t_block block_recu = { 0 };					// bloc recu du traiteur
	unsigned int id_fichier[NB_FICHIERS];		// tableau d'id fichier
	t_regroupement reg[NB_FICHIERS];			// tableau de regroupement (pile)
	t_reconstruction rec[NB_FICHIERS];			// tableau de reconstruction des fichiers
	char copie_nom_fich[NB_FICHIERS][NOM_MAX];	// tableau de nom des nouveaux fichiers
	t_traiteur traiteur;

	//init traiteur
	traiteur = init_traiteur(TAILLE_FILE);
	
	//init d�coupe						
	init_decoupage();

	//boucle pour initialiser la m�moire pour chaque fichier
	for (i = 0; i < NB_FICHIERS; i++) {

		//incrire "Copie_de_
		strcpy(copie_nom_fich[i], "Copie_de_");

		//compl�ter avec le nom actuelle du fichier
		strcat(copie_nom_fich[i], NOMS_FICHIERS[i]);

		//ajouter un fichier
		id_fichier[i] = ajouter_fichier(NOMS_FICHIERS[i]);

		//init regroupement
		reg[i] = init_regroupement(id_fichier[i], GROSSEUR_REGROUPEMENT);

		//init reconstruction
		rec[i] = init_reconstruction(id_fichier[i], GROSSEUR_RECONSTRUCTION);
	}

	//boucle pour obtenir un bloc
	//ajouter � la pile regroupement
	do {
		temps++;

		//obtenir un bloc
		block = get_bloc();

		//mettre le bloc dans en attente dans un guichet
		entree_bloc(&traiteur, block, TAILLE_FILE);

		//sortir un bloc du traiteur
		block_recu = sortie_block(&traiteur);

		//printf("BLOC: ID: %u, No. %d temps; %d\n", block_recu.f_identifiant, block_recu.num_bloc, temps);

		// si on a recu un block
		if (block_recu.f_identifiant != 0) {

			//obtenir position du regroupement du bloc
			position = position_regroupement(reg, NB_FICHIERS, block_recu.f_identifiant);

			//empiler le bloc
			empiler_bloc(&reg[position], block_recu);

			//v�rifier si la pile doit �tre vider
			if (pile_blocs_pleine(&reg[position])) {

				//vider la pile
				ajouter_pile_blocs(&rec[position], &reg[position]);
			}
		}

	} while(get_nb_bloc_traiteur(&traiteur) != 0);


	
	for (position = 0; position < NB_FICHIERS; position++){

		//reconstruction des fichiers
		refaire_fich(&rec[position], &reg[position], copie_nom_fich[position], id_fichier[position]);

		//desctruction du regroupement
		free_pile_blocs(&reg[position]);
	}

	//destruction du traiteur
	free_traiteur(&traiteur);	

	system("pause");

	return EXIT_SUCCESS;
}
#endif
/*************************************************************************************************/

/*===============================================================================================*/
/*												TEST											 */
/*===============================================================================================*/

/*************************************************************************************************/
//test de la file
#if(0)
int main(void) {

	t_block bloc = { 0 };
	t_block bloc_recept = { 0 };
	int id = 0;
	t_file_block blocs = { 0 };


	//init file
	blocs = init_file_block(TAILLE_FILE);

	//d�but du d�coupage
	init_decoupage();

	//ajouter fichier
	id = ajouter_fichier(NOM_FICHIER_0);

	do {

		//recevoir un bloc
		bloc = get_bloc();

		//mettre le bloc dans la file
		enfiler_block(&blocs, bloc);

	} while (bloc.bloc_final != 1);

	//fermer le fichier
	retirer_fichier(id);

	do {

		//aller chercher un bloc dans la file
		defiler_block(&blocs, &bloc_recept);

		//afficher si multiple de 2
		if (bloc_recept.num_bloc % 2 == 0) {

			print_bloc(&bloc_recept);
		}

	} while (bloc_recept.bloc_final != 1);

	//lib�rer la file
	free_file_block(&blocs);

	system("pause");
	return EXIT_SUCCESS;
}
#endif

/*************************************************************************************************/
//test de la file chain�e de t_block
#if(0)
int main(void) {


	t_block bloc = { 0 };
	t_block bloc_recept = { 0 };
	int id = 0;
	t_file_block_chainee blocs = { 0 };

	//d�but du d�coupage
	init_decoupage();

	//ajouter fichier
	id = ajouter_fichier(NOM_FICHIER_0);

	do {

		//recevoir un bloc
		bloc = get_bloc();

		//mettre le bloc dans la file
		enfiler_block_chainee(&blocs, bloc);

	} while (bloc.bloc_final != 1);

	//fermer le fichier
	retirer_fichier(id);

	do {

		//aller chercher un bloc dans la file
		defiler_block_chainee(&blocs, &bloc_recept);

		//afficher si multiple de 2
		if (bloc_recept.num_bloc % 2 == 0) {

			print_bloc(&bloc_recept);
		}

	} while (bloc_recept.bloc_final != 1);


	system("pause");
	return EXIT_SUCCESS;
}
#endif



/*===============================================================================================*/
/*											FONCTIONS											 */
/*===============================================================================================*/

/*************************************************************************************************/
//  position dans le tableau de regroupement

/*retourne un t_regroupement avec les valeurs de
l'id du fichier et la taille du tableau de bloc
*/
int position_regroupement(const t_regroupement reg[], int taille_reg, unsigned int f_identifiant) {

	int i;		//compteur boucle for

				//passe les regroupements pour trouver celui du bloc
	for (i = 0; i < taille_reg; i++) {

		//comparaison des id_fichier
		if (f_identifiant == reg[i].f_identifiant) {

			//retourne sa position une fois trouv�
			return i;
		}
	}
	return -1;
}


/*************************************************************************************************/
//  reconstruction d'un fichier

/*Cette fonction reconstruit un fichier. Elle vide sa pile,
lib�re sa m�moire, retire le fichier et reconstruit le fichier
retourne 1 si toutes les �tapes sont r�ussites.
*/
int refaire_fich(t_reconstruction *rec, t_regroupement *reg, char *nouveau_nom, unsigned int id_fichier) {

	int valide;

	//vider la pile
	valide = ajouter_pile_blocs(rec, reg);

	//lib�rer la m�moire de la pile
	free_pile_blocs(reg);

	//retire le fichier une fois d�coup�
	valide = retirer_fichier(id_fichier);

	//reconstruire le fichier
	valide = reconstruire_fich(rec, nouveau_nom);

	return valide;
}



void print_guichets(t_liste_g* guich) {

	int pos = 0;

	while (guich->g_apres != NULL){
		printf("Guichet %d:\n", pos);
		print_guichet(&guich->data);
		printf("\n");
		guich = guich->g_apres;
	}
	return;
}



void print_guichet(t_guichet* guich) {
	printf("Temps avant de sortir le prochain block: %d\n", guich->compte_rebours);
	printf("Nombre de block en file: %d", guich->file.nb_block);
	return;
}




















