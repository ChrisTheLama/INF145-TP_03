#if(1)
/*=====================================================================================*/
/*                                      TP2 - Mains                                    */
/*=====================================================================================*/
/*Par Guillaume Forget - FORG13029406*/

/*Dans ce module, le main pour traiter plusieurs fichiers en même temps*/
/*=====================================================================================*/

#define _CRT_SECURE_NO_WARNINGS 

//Bibliotheques standards
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Bibliothèques complémentaires
#include "m_decoupage.h"
#include "m_regroupement.h"
#include "m_reconstruction.h"

/*=====================================================================================*/
//CONSTANTES

/*Nombre de fichier à traiter*/
#define NB_FICHIERS 5

/*nombre de caractères maximals dans les noms des fichiers*/
#define NOM_MAX 100

/*Noms des fichiers à traiter*/
const char NOMS_FICHIERS[NB_FICHIERS][NOM_MAX] = {
	"Guillaume_Forget.pdf",
	"Guillaume_Forget.m4a",
	"H2018-145-Tp2.docx",
	"001.jpg",
	"test budget.xlsx"};

/*=====================================================================================*/
//FONCTIONS

/*retourne la position du fichier du bloc dans le tableau de regroupement*/
int position_regroupement(const t_regroupement reg[], int taille_reg, unsigned int f_identifiant);

/*reconstruit un fichier et libère son espace mémoire utilisée*/
int refaire_fich(t_reconstruction *rec, t_regroupement *reg, char *nouveau_nom, unsigned int id_fichier);

/*=====================================================================================*/
int main(void) {

	int i;										//compteur boucle
	int position;								// position du regroupement/reconstruction du bloc
	t_block block;								// accueille chaque bloc des fichiers
	unsigned int id_fichier[NB_FICHIERS];		// tableau d'id fichier
	t_regroupement reg[NB_FICHIERS];			// tableau de regroupement (pile)
	t_reconstruction rec[NB_FICHIERS];			// tableau de reconstruction des fichiers
	char copie_nom_fich[NB_FICHIERS][NOM_MAX];		//tableau de nom des nouveaux fichiers

	//init découpe						
	init_decoupage();

	//boucle pour initialiser la mémoire pour chaque fichier
	for (i = 0; i < NB_FICHIERS; i++) {

		//incrire "Copie_de_
		strcpy(copie_nom_fich[i], "Copie_de_");

		//compléter avec le nom actuelle du fichier
		strcat(copie_nom_fich[i], NOMS_FICHIERS[i]);

		//ajouter un fichier
		id_fichier[i] = ajouter_fichier(NOMS_FICHIERS[i]);

		//init regroupement
		reg[i] = init_regroupement(id_fichier[i], GROSSEUR_REGROUPEMENT);

		//init reconstruction
		rec[i] = init_reconstruction(id_fichier[i], GROSSEUR_RECONSTRUCTION);
	}

	//boucle pour obtenir un bloc
	//ajouter à la pile regroupement
	do {

		//obtenir un bloc
		block = get_bloc();

		//obtenir position du regroupement du bloc
		position = position_regroupement(reg, NB_FICHIERS, block.f_identifiant);

		//empiler le bloc
		empiler_bloc(&reg[position], block);

		//vérifier si la pile doit être vider
		if (pile_blocs_pleine(&reg[position])) {

			//vider la pile 1
			ajouter_pile_blocs(&rec[position], &reg[position]);
		}

		//si on reçoit le dernier bloc, on reconstruit le fichier
		if (block.bloc_final == 1) {

			//reconstruit le fichier
			refaire_fich(&rec[position], &reg[position], copie_nom_fich[position], id_fichier[position]);
		}

	} while (block.f_identifiant);

	system("pause");

	return EXIT_SUCCESS;
}
/***************************************************************************************/

/*==========================================================*/
//  position dans le tableau de regroupement
/*==========================================================*/
/*    rée et retourne un t_regroupement avec les valeurs de
l'id du fichier et la taille du tableau de bloc
*/
int position_regroupement(const t_regroupement reg[], int taille_reg, unsigned int f_identifiant) {

	int i;		//compteur boucle for

	//passe les regroupements pour trouver celui du bloc
	for (i = 0; i < taille_reg; i++) {

		//comparaison des id_fichier
		if (f_identifiant == reg[i].f_identifiant) {

			//retourne sa position une fois trouvé
			return i;
		}
	}
	return -1;
}
/***************************************************************************************/

/*==========================================================*/
//  reconstruction d'un fichier
/*==========================================================*/
/*Cette fonction reconstruit un fichier. Elle vide sa pile,
libère sa mémoire, retire le fichier et reconstruit le fichier
retourne 1 si toutes les étapes sont réussites.
*/
int refaire_fich(t_reconstruction *rec, t_regroupement *reg, char *nouveau_nom, unsigned int id_fichier) {
	
	int valide;

	//vider la pile
	valide = ajouter_pile_blocs(rec, reg);

	//libérer la mémoire de la pile
	free_pile_blocs(reg);

	//retire le fichier une fois découpé
	valide = retirer_fichier(id_fichier);

	//reconstruire le fichier
	valide = reconstruire_fich(rec, nouveau_nom);

	return valide;
}
#endif
