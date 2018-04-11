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

//Bibliothèques complémentaires
#include "m_traiteur.h"
#include "m_reconstruction.h"
#include "m_complementaire.h"
/*===============================================================================================*/
//CONSTANTES
#define GROSSEUR_REGROUPEMENT		10
#define GROSSEUR_RECONSTRUCTION		10
/*Nombre de fichier à traiter*/
#define NB_FICHIERS					3

/*longueur de la file dans un guichet*/
#define TAILLE_FILE					5

/*nombre de caractères maximals dans les noms des fichiers*/
#define NOM_MAX						100

/*Nombre de t_traiteur utilise*/
#define NB_TRAITEUR					5

#define ON							1
#define OFF							0

/*Noms des fichiers à traiter*/
const char NOMS_FICHIERS[NB_FICHIERS][NOM_MAX] = {
	"Image.jpg",
	"musique.wma",
	"Image2.jpg",
};

/*===============================================================================================*/
//FONCTIONS

/*retourne la position du fichier du bloc dans le tableau de regroupement*/
int position_regroupement(const t_regroupement reg[], int taille_reg, unsigned int f_identifiant);

/*reconstruit un fichier et libère son espace mémoire utilisée*/
int refaire_fich(t_reconstruction *rec, t_regroupement *reg, char *nouveau_nom,
	unsigned int id_fichier);

/*===============================================================================================*/

/*===============================================================================================*/
/*le main mandat 2-2B pour traiter plusieurs fichiers en même temps*/
/*===============================================================================================*/
#if(1)
int main(void) {
	
	int v_rand = 0;								//valeur des appels de rand_s
	int i = 0, temps = 0;						//compteur boucle
	int position = 0;							//position du regroupement/reconstruction du bloc
	t_block block = { 0 };						//accueille chaque bloc des fichiers
	t_block block_recu = { 0 };					//bloc recu du traiteur
	t_block block_vide = { 0 };					//bloc vide
	unsigned int id_fichier[NB_FICHIERS];		//tableau d'id fichier
	t_regroupement reg[NB_FICHIERS];			//tableau de regroupement (pile)
	t_reconstruction rec[NB_FICHIERS];			//tableau de reconstruction des fichiers
	char copie_nom_fich[NB_FICHIERS][NOM_MAX];	//tableau de nom des nouveaux fichiers
	t_traiteur traiteur[NB_TRAITEUR];			//tableau de traiteur
	
	

	//init découpe						
	init_decoupage();

	//init m_random
	init_rand();


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
		
		//init traiteur
		
	}

	for(i=0;i<NB_TRAITEUR;i++)
		traiteur[i] = init_traiteur(TAILLE_FILE);

	//boucle pour obtenir un bloc
	//ajouter à la pile regroupement
	do {

		//obtenir un bloc
		block = get_bloc();

		//choix du traiteur recevant le bloc
		v_rand = rand_s(0,NB_TRAITEUR);
		//mettre le bloc dans en attente dans un guichet
		for (i = 0; i < NB_TRAITEUR; i++) {
			if (i == v_rand) //on implemente le  bloc du get_bloc dans le traiteur choisi
				entree_bloc(&(traiteur[i]), block, TAILLE_FILE);
			else //on implemente le bloc vide dans les autres traiteur
				entree_bloc(&(traiteur[i]), block_vide, TAILLE_FILE);
		}
		
		//choix du traiteur recevant le bloc 
		v_rand = rand_s(0, NB_TRAITEUR);
		//sortir un bloc du traiteur
		block_recu = sortie_block(&traiteur[v_rand]);

		temps = statistique(traiteur, NB_TRAITEUR, OFF);
		
		printf("BLOC: ID: %u, No. %d, traiteur: %d, temps: %d\n", block_recu.f_identifiant,
			block_recu.num_bloc, v_rand, temps);

		// si on a recu un block
		if (block_recu.f_identifiant != 0) {

			//obtenir position du regroupement du bloc
			position = position_regroupement(reg, NB_FICHIERS, block_recu.f_identifiant);

			//empiler le bloc
			empiler_bloc(&reg[position], block_recu);

			//vérifier si la pile doit être vider
			if (pile_blocs_pleine(&reg[position])) {

				//vider la pile
				ajouter_pile_blocs(&rec[position], &reg[position]);
			}
		}

	} while (taille_restante_tot(id_fichier, NB_FICHIERS) != 0 ||
		 block_restante_tot(traiteur, NB_TRAITEUR) != 0);

	temps = statistique(traiteur, NB_TRAITEUR, ON);

	for (position = 0; position < NB_FICHIERS; position++) {

		//reconstruction des fichiers
		refaire_fich(&rec[position], &reg[position], copie_nom_fich[position],
			id_fichier[position]);

		//desctruction du regroupement
		free_pile_blocs(&reg[position]);
	}

	//destruction du traiteur
	for(i=0; i < NB_TRAITEUR; i++)
		free_traiteur(traiteur+i);

	system("pause");

	return EXIT_SUCCESS;
}
#endif
/*************************************************************************************************/



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
		if (f_identifiant == reg[i].id_fichier) {
			//retourne sa position une fois trouvé
			return i;
		}
	}
	return -1;
}


/*************************************************************************************************/
//  reconstruction d'un fichier

/*Cette fonction reconstruit un fichier. Elle vide sa pile,
libère sa mémoire, retire le fichier et reconstruit le fichier
retourne 1 si toutes les étapes sont réussites.
*/
int refaire_fich(t_reconstruction *rec, t_regroupement *reg, char *nouveau_nom, 
	unsigned int id_fichier) {

	int valide;

	//vider la pile
	ajouter_pile_blocs(rec, reg);

	//libérer la mémoire de la pile
	free_pile_blocs(reg);

	//retire le fichier une fois découpé
	valide = retirer_fichier(id_fichier);

	//reconstruire le fichier
	valide = reconstruire_fich(rec, nouveau_nom);

	return valide;
}

