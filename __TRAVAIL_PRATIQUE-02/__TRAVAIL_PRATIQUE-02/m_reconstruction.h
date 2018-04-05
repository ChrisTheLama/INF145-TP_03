/*************************************************************************************************/
//  PAR   : Christophe Lamarche & Frederic Thibault		     
/*************************************************************************************************/

/*
Le module de reconstruction de fichier en blocs disjoints fournit le type t_reconstruction et des
fonctions en liens avec ce type.

Le module offre l'initialisation du t_reconstruction, le redimensionnement de la memoire allouee
pour le tableau dynamique pointee par le t_reconstruction et l'ajout de blocs dans le tableau 
dynamique. De plus, il est possible de connaitre la quantite de blocs a l'interieur du tableau et
si le t_reconstruction a recu tous les blocs decoupes du fichier correspondant au t_reconstruction.
Si tous les blocs sont dans un t_reconstruction, il est possible de reconstruire le fichier de 
base. A la fin d'une utilisation d'un t_regroupement, il est primordial de liberer la memoire 
allouee pour ce type al
Le module offre l'empilement et le depilement de blocs dans une pile accessible par le
t_regroupement. De plus, il est possible d'analyser le contenu du nouveau type par les fonctions :
pile_blocs_nombre, pile_blocs_pleine, pile_blocs_taille et pile_blocs_vide.

Finalement, il est necessaire de libere la memoire de la pile du t_regroupement grace a
free_pile_blocs a la fin d'un programme si on utilise un t_regroupement.
*/

/*************************************************************************************************/

#ifndef  __MODULE__RECONSTRUCTION__
#define  __MODULE__RECONSTRUCTION__

/*************************************************************************************************/
//qui permet de désactiver certains warnings du compilateur
#define _CRT_SECURE_NO_WARNINGS  
// Librairies usuelles à inclure
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"m_decoupage.h"
#include"m_regroupement.h"
/*************************************************************************************************/


/*************************************************************************************************/
/*											CONSTANTE	   									     */
/*************************************************************************************************/


/*************************************************************************************************/

/*************************************************************************************************/
/*************************************************************************************************/
typedef struct {

	unsigned int id_fichier; // identifiant unique d'un fichier
	t_block* ptr_bloc; //pointeur donnant acces au tableau dynamique de t_block
	unsigned int taille_last_tab; //taille du tableau precedent
	unsigned int nbr_bloc_actu; //nombre de t_bloc actuellement présent
	unsigned int nbr_bloc_tot; //nobre total de t_block du fichier \
					//(qu'on obtient en recevant le dernier bloc du découpage)

} t_reconstruction;




/************************************ INIT_RECONSTRUCTION ****************************************/
/* MUTATRICE
Description : reçoit l’identifiant unique d’un fichier et la taille initiale de son tableau de 
	reconstruction. Il construit le tableau dynamique nécessaire et en cas de succès de 
	l’allocation, le tableau est traversé et les identifiants-fichier sont tous mis à 0 dans les 
	blocs puis la fonction fixe la taille, l’identifiant unique du fichier et le nombre total de 
	blocks à 0 	(en cas d’échec l’allocation, tous les membres du t_reconstruction serontnuls (0 
	ou NULL)). On retourne le nouvel objet.

PARAMETRES : l'identifiant du fichier 
			 taille initiale du tableau

RETOUR : un objet de type t_reconstruction 

SPECIFICATIONS : La taille pour l'initialisation doit etre de valeur positif
*/
t_reconstruction init_reconstruction(unsigned int id, int taille);
/*************************************************************************************************/

/**********************************	REDIM_RECONSTRUCTION *****************************************/
/* MUTATRICE
Description : Reçoit l’adresse d’une reconstruction et d’une taille, elle essaie de redimensionner
	son tableau en conservant les blocs présents (allouez un nouveau tableau et copiez-y tous les 
	blocs du tableau actuel avec memcpy). La fonction met l’identifiant fichier à 0 dans les
	nouvelles cases du tableau et ajuste les autres membres de la structure. On retourne 1 en cas 
	desuccès, 0 sinon.

PARAMETRES : un adresse d'un objet de type t_reconstruction
			 la nouvelle taille du tableau dynamique

RETOUR : 0 ->> le redimensionnement a echouer
		 1 ->> le redimensionnement a reussis

SPECIFICATIONS : La nouvelle taille doit être plus grand que l'ancienne tableau et doit etre
	positif.
*/
int redim_reconstruction(t_reconstruction * rec, int nouvelle_taille);
/*************************************************************************************************/


/**************************************** AJOUTER_BLOC *******************************************/
/* MUTATRICE
Description : Si les conditions nécessaires sont satisfaites, on copie le bloc dans le tableau à sa 
	position et on retourne 1 si l’action réussit, 0 sinon. On redimensionne le t_reconstruction si
	nécessaire.

PARAMETRES : l'adresse d'un objet de type t_reconstruction
			 le t_bloc a ajouter
RETOUR : 0 ->> l'ajout a echouer
		 1 ->> l'ajout est reussi

SPECIFICATIONS : AUCUNE
*/
int ajouter_bloc(t_reconstruction * rec, t_block bloc);
/*************************************************************************************************/

/************************************* AJOUTER_PILE_BLOCS ****************************************/
/* MUTATRICE
Description : Si les deux structures sont du même fichier, la fonction va dépiler tous les blocs du
	regroupement pour les ajouter à la reconstruction (avec la fonction ajouter_bloc).

PARAMETRES : l'adresse d'un objet de type t_reconstruction
			 l'adresse d'un objet de type t_regroupement

RETOUR : RIEN
SPECIFICATIONS : AUCUNE
*/
void ajouter_pile_blocs(t_reconstruction *rec, t_regroupement * reg);
/*************************************************************************************************/

/******************************** BLOC_DANS_RECONSTRUCTION ***************************************/
/*  INFORMATRICE
Description : Retourne le nombre actuel de blocs du fichier dans la structure.

PARAMETRES : l'adresse d'un objet de type t_reconstruction

RETOUR : le nombre de bloc dans l'objet t_reconstruction

SPECIFICATIONS :
*/
int bloc_dans_reconstruction(const t_reconstruction * rec);
/*************************************************************************************************/

/********************************** ETAT_RECONSTRUCTION ******************************************/
/* INFORMATRICE
Description : Retourne 1 si tous les blocs du fichier sont dans la structure et 0 sinon. Ceci se 
	produit lorsque le nombre de t_block actuellement présents devient égal au nombre total de 
	t_block du fichier.

PARAMETRES : l'adresse de l'objet de type t_reconstruction du fichier

RETOUR : 0 ->> il reste des blocs a ajouter dans l'objet t_reconstruction du fichier
		 1 ->> tous les blocs du fichier sont dans l'objet t_reconstruction du fichier

SPECIFICATIONS : Le t_reconstruction doit etre valide
*/
int etat_reconstruction(t_reconstruction * rec);
/*************************************************************************************************/

/*********************************** RECONSTRUIRE_FICH *******************************************/
/* MUTATRICE
Description : Si la reconstruction est prête (avec etat_reconstruction) et le fichier binaire est 
	bien ouvert en écriture, tous les blocs d’octets des t_block sont écrits, en ordre, dans le 
	fichier puis le fichier est fermé. La fonction libère les tableaux dynamiques d’octets dans 
	tous les t_block et libère aussi le tableau de t_block dans la structure. Elle retourne 1 en 
	cas de succès et 0 sinon.

PARAMETRES : L'objet de type t_reconstruction du fichier
			 Le nom du nouveau fichier
RETOUR : 0 ->> la reconstruction a echouer
		 1 ->> la reconstruction est réussi

SPECIFICATIONS : Le nom du nouveau fichier doir avoir la même terminaison que le fichier d'origine
ex: nom_d'orgine : "abcdef.jpg" ==> nouveau_nom : "ghijkl.jpg"
	nom_d'orgine : "HELLO_world.mp3" ==> nouveau_nom : "ERROR404.mp3"

*/
int reconstruire_fich(t_reconstruction *rec, const char * nom_nouv_fichier);
/*************************************************************************************************/

/*************************************** FREE_REC_TAB ********************************************/
/*
Description : libere le tableau dynamique et remet tous les membres à 0 ou NULL

PARAMETRES : l'adrese de l'objet de type de t_reconstruction

RETOUR : RIEN

SPECIFICATIONS : Le t_reconstruction ne doit pas avoir ete libere auparavant.

*/
void free_rec_tab(t_reconstruction * rec);
#endif
/*************************************************************************************************/


