#if(0)
/*=====================================================================================*/
/*                                 TP2 - Mains de test                                 */
/*=====================================================================================*/
/*Par Guillaume Forget - FORG13029406*/

/*Dans ce module, les mains de test pour les diff�rentes fonctions des modules
m_decoupage, m_regroupement et m_reconstruction*/


#define _CRT_SECURE_NO_WARNINGS 

//Bibliotheques standards
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//Biblioth�ques compl�mentaires
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
	int i1 = 0;					//position d'�criture dans le tableau de bloc
	unsigned int id_fichier;	//D�fini que le nom de notre fichier
	int i;						//compteur pour boucle

	//init d�coupage du fichier
	init_decoupage();

	//S�lection du fichier a d�couper
	id_fichier = ajouter_fichier("Guillaume_Forget.m4a");  

	do {

		//ajout d'un bloc
		blocs[i1] = get_bloc();

		//changement de position
		i1 += 1;

		// Permet d'afficher l'�tat du fichier � chaque 10 blocs
		if (i1 % 10 == 0) { 

			print_etat_fichier(id_fichier);
		}

	} while (blocs[i1 - 1].bloc_final == 0); //v�rification si bloc est null

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

// initialisation du d�coupage de plusieurs fichiers

#if(0)
int main(void) {

	t_block blocs1[4000];		// tableau de bloc fichier 1
	t_block blocs2[4000];		// tableau de bloc fichier 2
	t_block block;				// un bloc
	int i1 = 0;					// position �criture bloc 1
	int i2 = 0;					// position �criture bloc 2
	unsigned int id_fichier1;	// id du fichier1 ouvert
	unsigned int id_fichier2;	// id du fichier2 ouvert
	int i = 0, y = 0;			//compteur bouble

	// initilisation du d�coupage
	init_decoupage();

	// Nom du premier fichier � d�couper ainsi que son fichier source
	id_fichier1 = ajouter_fichier("Guillaume_Forget.pdf");

	// Nom du deuxi�me fichier � d�couper ainsi que son fichier source
	id_fichier2 = ajouter_fichier("H2018-145-Tp2.docx"); 

	do {
		// ramasser un bloc
		block = get_bloc();

		// Boucle permettant d'identifier le fichier 1
		if (block.f_identifiant == id_fichier1) {

			blocs1[i1] = block;	//�criture du bloc dans le tableau du fichier 1 

			i1 += 1;	// changement de la position a �crire dans le tableau
		}
		else if (block.f_identifiant == id_fichier2) {		//Si bloc du fichier 2

			//�criture du bloc dans le tableau du fichier 2
			blocs2[i2] = block;	

			//changement de la position � �crire 
			i2 += 1;	
		}

		// Permet d'afficher l'�tat des fichiers � chaque 10 blocs
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

	// Permet de v�rifier si le fichier 1 a bien �t� retir�
	printf("\n%d\n", get_taille_fichier(id_fichier1));   

	// Permet de v�rifier si le fichier 2 a bien �t� retir�
	printf("\n%d\n", get_taille_fichier(id_fichier2));

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/
/*                     Sequence de regroupement (madat #2)                             */
/*=====================================================================================*/

/*validation avec un l'ouverture d'un seul fichier*/
/*NOTE: CONSTANTE GROSSEUR_REGROUPEMENT DOIT  �TRE ASSEZ
GRANDE POUR CONTENIR TOUS LES BLOCS*/

#if(0)

int main(void) {

	t_block block;				// accueille chaque bloc qui sont coup� du fichier
	t_regroupement reg;			// regroupe les bloc du fichier
	t_block *tab_tmp;			// tableau de bloc pour le fichier
	unsigned int i = 0;			// compteur pour boucle 
	unsigned int id_fichier;	// id du fichier ouvert
	unsigned int continuer;		// variable pour boucle while
	
	//init d�coupe
	init_decoupage();

	//ajouter un fichier et r�cup�rer id
	id_fichier = ajouter_fichier("Guillaume_Forget.pdf");
	
	//init regroupement
	reg = init_regroupement(id_fichier, GROSSEUR_REGROUPEMENT);

	//boucle pour obtenir un bloc
	//ajouter � la pile (regroupement) jusqu'au dernier bloc
	do {

		block = get_bloc();				//obtenir un bloc

		empiler_bloc(&reg, block);		//empile le bloc

	} while (block.f_identifiant);

	//retire le fichier une fois d�coup�
	retirer_fichier(id_fichier);

	//cr�er tab_tmp avec alloc dynamique
	tab_tmp = calloc(reg.nb_bloc, sizeof(t_block));

	//validation de la cr�ation du tableau dynamique
	if (tab_tmp == NULL) {

		//message d'erreur
		printf("Le tableau dynamique n'a pas pu �tre cr��");

		system("pause");

		return EXIT_FAILURE;
	}

	//d�piler dans un tableau dynamique temporaire
	do {

		//d�pile un bloc
		continuer = depiler_bloc(&reg, &tab_tmp[i]);

		//imprimer les r�sultats
		if (continuer) {

			print_bloc(&tab_tmp[i]); //affichage des blocs
		}

		i += 1;		//ingr�menter

	} while (continuer);

	//lib�rer la m�moire de la pile
	free_pile_blocs( &reg );

	//lib�re la m�moire du tableau
	free(tab_tmp);

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/

// validation du regroupement avec plusieurs fichiers
/*NOTE: CONSTANTE GROSSEUR_REGROUPEMENT DOIT  �TRE ASSEZ
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

	//init d�coupe
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

		//cherche � quel fichier le bloc appartient
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

	//cr�er tab_tmp1 avec alloc dynamique
	tab_tmp1 = calloc(reg1.nb_bloc, sizeof(t_block));

	//cr�er tab_tmp2 avec alloc dynamique
	tab_tmp2 = calloc(reg2.nb_bloc, sizeof(t_block));

	//validation de la cr�ation du tableau dynamique
	if (tab_tmp1 == NULL || tab_tmp2 == NULL) {

		//message d'erreur
		printf("Le tableau dynamique n'a pas pu �tre cr��");

		system("pause");

		return EXIT_FAILURE;	//exit code
	}

	//d�piler pile 1 dans un tableau dynamique temporaire
	do {

		//tant que la pile n'est pas vide, on d�pile
		continuer = depiler_bloc(&reg1, &tab_tmp1[i]);

		i += 1;

	} while (continuer);


	//d�piler pile 2 dans un tableau dynamique temporaire
	do {

		//tant que la pile n'est pas vide, on d�pile
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

	//lib�rer la m�moire pile 1
	free_pile_blocs(&reg1);

	//lib�rer la m�moire pile 2
	free_pile_blocs(&reg2);

	//lib�rer tableau 1
	free(tab_tmp1);

	//lib�rer tableau 2
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

	t_block block;						//accueille chaque bloc des fichiers un � un
	t_regroupement reg1;				//regroupe les blocs du fichier 1
	t_reconstruction rec1;				//tableau pour la reconstruction du fichier 1
	unsigned int id_fichier1;			//fichier 1
	char nom_fichier1[] =				//fichier 1 � copier
		"Guillaume_Forget.m4a";		
	char nouveau_nom_fichier1[100] =	//nom du nouveau fichier 1
		"copie_de_";	

	//cr�ation des noms de fichier pour la copie
	strcat(nouveau_nom_fichier1, nom_fichier1);

	//init d�coupe
	init_decoupage();

	//ajouter un fichier et r�cup�rer id
	id_fichier1 = ajouter_fichier(nom_fichier1);

	//init regroupement
	reg1 = init_regroupement(id_fichier1, GROSSEUR_REGROUPEMENT);

	//init reconstruction
	rec1 = init_reconstruction(id_fichier1, GROSSEUR_RECONSTRUCTION);

	//boucle pour obtenir un bloc
	//ajouter � la pile regroupement
	do {
		block = get_bloc();

		empiler_bloc(&reg1, block);

		//v�rifier si la pile 1 doit �tre vider
		if (pile_blocs_pleine(&reg1)) {

			//vider la pile 1
			ajouter_pile_blocs(&rec1, &reg1);
		}
	} while (block.f_identifiant);

	//vider les piles
	ajouter_pile_blocs(&rec1, &reg1);

	//lib�rer la m�moire des piles
	free_pile_blocs(&reg1);

	//retire les fichiers une fois d�coup�s
	retirer_fichier(id_fichier1);

	//reconstruire les fichiers
	reconstruire_fich(&rec1, nouveau_nom_fichier1);

	system("pause");

	return EXIT_SUCCESS;
}
#endif

/*=====================================================================================*/

#endif
