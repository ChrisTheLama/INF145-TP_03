#if(0)
/*=====================================================================================*/
/*                                 TP2 - Mains de test                                 */
/*=====================================================================================*/
/*Par Guillaume Forget - FORG13029406*/

/*Dans ce module, les mains de test pour les différentes fonctions des modules
m_decoupage, m_regroupement et m_reconstruction*/


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
/*                       Sequence de decoupage (madat #1)                              */
/*=====================================================================================*/

//initialisation du decoupage d'un seul fichier

#if(0)
int main(void) {

	t_block blocs[4000];		//tableau de 4000 blocs
	int i1 = 0;					//position d'écriture dans le tableau de bloc
	unsigned int id_fichier;	//Défini que le nom de notre fichier
	int i;						//compteur pour boucle

	//init découpage du fichier
	init_decoupage();

	//Sélection du fichier a découper
	id_fichier = ajouter_fichier("Guillaume_Forget.m4a");  

	do {

		//ajout d'un bloc
		blocs[i1] = get_bloc();

		//changement de position
		i1 += 1;

		// Permet d'afficher l'état du fichier à chaque 10 blocs
		if (i1 % 10 == 0) { 

			print_etat_fichier(id_fichier);
		}

	} while (blocs[i1 - 1].bloc_final == 0); //vérification si bloc est null

	//impression des blocs du fichier
	for (i = 0; i < i1; i += 10) {

		//affichage d'un bloc
		print_bloc(&blocs[i]);
	}

	//imprimer bloc final
	print_bloc(&blocs[i1 - 1]);

	// retire le fichier
	retirer_fichier(id_fichier);

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/

// initialisation du découpage de plusieurs fichiers

#if(0)
int main(void) {

	t_block blocs1[4000];		// tableau de bloc fichier 1
	t_block blocs2[4000];		// tableau de bloc fichier 2
	t_block block;				// un bloc
	int i1 = 0;					// position écriture bloc 1
	int i2 = 0;					// position écriture bloc 2
	unsigned int id_fichier1;	// id du fichier1 ouvert
	unsigned int id_fichier2;	// id du fichier2 ouvert
	int i = 0, y = 0;			//compteur bouble

	// initilisation du découpage
	init_decoupage();

	// Nom du premier fichier à découper ainsi que son fichier source
	id_fichier1 = ajouter_fichier("Guillaume_Forget.pdf");

	// Nom du deuxième fichier à découper ainsi que son fichier source
	id_fichier2 = ajouter_fichier("H2018-145-Tp2.docx"); 

	do {
		// ramasser un bloc
		block = get_bloc();

		// Boucle permettant d'identifier le fichier 1
		if (block.f_identifiant == id_fichier1) {

			blocs1[i1] = block;	//écriture du bloc dans le tableau du fichier 1 

			i1 += 1;	// changement de la position a écrire dans le tableau
		}
		else if (block.f_identifiant == id_fichier2) {		//Si bloc du fichier 2

			//écriture du bloc dans le tableau du fichier 2
			blocs2[i2] = block;	

			//changement de la position à écrire 
			i2 += 1;	
		}

		// Permet d'afficher l'état des fichiers à chaque 10 blocs
		if ((i1 + i2) % 10 == 0) {

			print_etat_fichier(id_fichier1);

			print_etat_fichier(id_fichier2);
		}

	} while (block.f_identifiant != 0);		// tant qu'il y a des blocs, la boucle continue

	//impression des blocs du fichier 1
	for (i = 0; i < i1; i += 10){

		//affichage d'un bloc
		print_bloc(&blocs1[i]);
	}

	//imprimer bloc final 1
	print_bloc(&blocs1[i1 - 1]);

	//impression des blocs du fichier 2
	for (y = 0; y < i2; y += 10) {

		//affichage d'un bloc
		print_bloc(&blocs2[y]);
	}

	//imprimer bloc final 2
	print_bloc(&blocs2[i2 - 1]);

	// Retire le fichier 1
	retirer_fichier(id_fichier1);

	// Retire le fichier 2
	retirer_fichier(id_fichier2);

	// Permet de vérifier si le fichier 1 a bien été retiré
	printf("\n%d\n", get_taille_fichier(id_fichier1));   

	// Permet de vérifier si le fichier 2 a bien été retiré
	printf("\n%d\n", get_taille_fichier(id_fichier2));

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/
/*                     Sequence de regroupement (madat #2)                             */
/*=====================================================================================*/

/*validation avec un l'ouverture d'un seul fichier*/
/*NOTE: CONSTANTE GROSSEUR_REGROUPEMENT DOIT  ÊTRE ASSEZ
GRANDE POUR CONTENIR TOUS LES BLOCS*/

#if(0)

int main(void) {

	t_block block;				// accueille chaque bloc qui sont coupé du fichier
	t_regroupement reg;			// regroupe les bloc du fichier
	t_block *tab_tmp;			// tableau de bloc pour le fichier
	unsigned int i = 0;			// compteur pour boucle 
	unsigned int id_fichier;	// id du fichier ouvert
	unsigned int continuer;		// variable pour boucle while
	
	//init découpe
	init_decoupage();

	//ajouter un fichier et récupérer id
	id_fichier = ajouter_fichier("Guillaume_Forget.pdf");
	
	//init regroupement
	reg = init_regroupement(id_fichier, GROSSEUR_REGROUPEMENT);

	//boucle pour obtenir un bloc
	//ajouter à la pile (regroupement) jusqu'au dernier bloc
	do {

		block = get_bloc();				//obtenir un bloc

		empiler_bloc(&reg, block);		//empile le bloc

	} while (block.f_identifiant);

	//retire le fichier une fois découpé
	retirer_fichier(id_fichier);

	//créer tab_tmp avec alloc dynamique
	tab_tmp = calloc(reg.nb_bloc, sizeof(t_block));

	//validation de la création du tableau dynamique
	if (tab_tmp == NULL) {

		//message d'erreur
		printf("Le tableau dynamique n'a pas pu être créé");

		system("pause");

		return EXIT_FAILURE;
	}

	//dépiler dans un tableau dynamique temporaire
	do {

		//dépile un bloc
		continuer = depiler_bloc(&reg, &tab_tmp[i]);

		//imprimer les résultats
		if (continuer) {

			print_bloc(&tab_tmp[i]); //affichage des blocs
		}

		i += 1;		//ingrémenter

	} while (continuer);

	//libérer la mémoire de la pile
	free_pile_blocs( &reg );

	//libère la mémoire du tableau
	free(tab_tmp);

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/

// validation du regroupement avec plusieurs fichiers
/*NOTE: CONSTANTE GROSSEUR_REGROUPEMENT DOIT  ÊTRE ASSEZ
GRANDE POUR CONTENIR TOUS LES BLOCS*/

#if(0)

int main(void) {

	t_block block;				// accueille chaque bloc des fichiers
	t_regroupement reg1;		// regroupe les blocs du fichier 1
	t_regroupement reg2;		// regroupe les bloc du fichier 2
	t_block *tab_tmp1;			//tableau pour vider la pile 1
	t_block *tab_tmp2;			//tableau pour vider la pile 2
	unsigned int i = 0, y = 0;	//compteur pour boucle 
	unsigned int id_fichier1;	//id du fichier 1
	unsigned int id_fichier2;	//id du fichier 2
	unsigned int continuer;		//condition pour while
	unsigned int x = 0;			//compteur pour boucle 

	//init découpe
	init_decoupage();

	//ajoute le fichier 1
	id_fichier1 = ajouter_fichier("H2018-145-Tp2.docx");

	//ajoute le fichier 2
	id_fichier2 = ajouter_fichier("Guillaume_Forget.pdf");

	//init regroupement fichier 1
	reg1 = init_regroupement(id_fichier1, GROSSEUR_REGROUPEMENT);

	//init regroupement fichier 2
	reg2 = init_regroupement(id_fichier2, GROSSEUR_REGROUPEMENT);

	//boucle pour obtenir un bloc
	do {

		block = get_bloc();		//obtenir un bloc

		//cherche à quel fichier le bloc appartient
		if (block.f_identifiant == reg1.f_identifiant) {

			empiler_bloc(&reg1, block);		//empile dans la pile du fichier 1
		}
		else if (block.f_identifiant == reg2.f_identifiant) {

			empiler_bloc(&reg2, block);		//empile dans la pile du fichier 2
		}

	} while (block.f_identifiant);

	//retire fichier 1
	retirer_fichier(id_fichier1);

	//retire fichier 2
	retirer_fichier(id_fichier2);

	//créer tab_tmp1 avec alloc dynamique
	tab_tmp1 = calloc(reg1.nb_bloc, sizeof(t_block));

	//créer tab_tmp2 avec alloc dynamique
	tab_tmp2 = calloc(reg2.nb_bloc, sizeof(t_block));

	//validation de la création du tableau dynamique
	if (tab_tmp1 == NULL || tab_tmp2 == NULL) {

		//message d'erreur
		printf("Le tableau dynamique n'a pas pu être créé");

		system("pause");

		return EXIT_FAILURE;	//exit code
	}

	//dépiler pile 1 dans un tableau dynamique temporaire
	do {

		//tant que la pile n'est pas vide, on dépile
		continuer = depiler_bloc(&reg1, &tab_tmp1[i]);

		i += 1;

	} while (continuer);


	//dépiler pile 2 dans un tableau dynamique temporaire
	do {

		//tant que la pile n'est pas vide, on dépile
		continuer = depiler_bloc(&reg2, &tab_tmp2[y]);

		y += 1;

	} while (continuer);

	//imprimer les blocks du tab_1
	x = 0; //commencer avec le bloc 0

	while (tab_tmp1[x].f_identifiant == id_fichier1){

		//imprimer bloc
		print_bloc(&tab_tmp1[x]);

		x++;
	}

	//imprimer les blocks du tab_2
	x = 0; //commencer avec le bloc 0

	while (tab_tmp2[x].f_identifiant == id_fichier2){

		//imprimer bloc
		print_bloc(&tab_tmp2[x]);

		x++;
	}

	//libérer la mémoire pile 1
	free_pile_blocs(&reg1);

	//libérer la mémoire pile 2
	free_pile_blocs(&reg2);

	//libérer tableau 1
	free(tab_tmp1);

	//libérer tableau 2
	free(tab_tmp2);

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/
/*                      Sequence de reconstruction (madat #3)                          */
/*=====================================================================================*/

/*validation avec l'ouverture d'un fichier*/

#if(1)

int main(void) {

	t_block block;						//accueille chaque bloc des fichiers un à un
	t_regroupement reg1;				//regroupe les blocs du fichier 1
	t_reconstruction rec1;				//tableau pour la reconstruction du fichier 1
	unsigned int id_fichier1;			//fichier 1
	char nom_fichier1[] =				//fichier 1 à copier
		"Guillaume_Forget.m4a";		
	char nouveau_nom_fichier1[100] =	//nom du nouveau fichier 1
		"copie_de_";	

	//création des noms de fichier pour la copie
	strcat(nouveau_nom_fichier1, nom_fichier1);

	//init découpe
	init_decoupage();

	//ajouter un fichier et récupérer id
	id_fichier1 = ajouter_fichier(nom_fichier1);

	//init regroupement
	reg1 = init_regroupement(id_fichier1, GROSSEUR_REGROUPEMENT);

	//init reconstruction
	rec1 = init_reconstruction(id_fichier1, GROSSEUR_RECONSTRUCTION);

	//boucle pour obtenir un bloc
	//ajouter à la pile regroupement
	do {
		block = get_bloc();

		empiler_bloc(&reg1, block);

		//vérifier si la pile 1 doit être vider
		if (pile_blocs_pleine(&reg1)) {

			//vider la pile 1
			ajouter_pile_blocs(&rec1, &reg1);
		}
	} while (block.f_identifiant);

	//vider les piles
	ajouter_pile_blocs(&rec1, &reg1);

	//libérer la mémoire des piles
	free_pile_blocs(&reg1);

	//retire les fichiers une fois découpés
	retirer_fichier(id_fichier1);

	//reconstruire les fichiers
	reconstruire_fich(&rec1, nouveau_nom_fichier1);

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/

#endif
