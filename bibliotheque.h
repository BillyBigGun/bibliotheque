#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

//#include "t_pile.h"

#define NB_LIVRES_MAX_RANGEE        100
#define NB_GENRES                   6
#define BIBLIO_FICHIER				"biblio.txt"

#define TAILLE_TITRE	80
#define TAILLE_NOM		30	
#define TAILLE_PRENOM	30
#define TAILLE_MAX_LIGNE 100

#define MAX_ISBN		9999

#define SIMULATION      1

#define EMPRUNT         1
#define DISPONIBLE      0

typedef enum { AUCUN = 0, FICTION = 1, HISTOIRE = 2, SCIENCE = 3, ENFANTS = 4, INFORMATIQUE = 5 } t_genre;

typedef struct
{
	int nb_livre;
	int nb_emprunts;
} t_rapport;

typedef struct t_livre t_livre;
struct t_livre
{
	t_genre genre;
	int nb_pages;
	char auteur_prenom[TAILLE_PRENOM];
	char auteur_nom[TAILLE_NOM];
	char titre[TAILLE_TITRE];
	int isbn;
	int bEmprunte; // 1: Le livre a ete emprunte, 0: le livre est disponible.
	t_livre * suivant;
};

typedef struct 
{
	t_livre * premier;
} t_pile;


typedef struct
{
	t_livre livres[NB_GENRES][NB_LIVRES_MAX_RANGEE];
	int nb_livres[NB_GENRES];
	t_pile retours;
	t_rapport rapport;
} t_bibliotheque;


// Affiche les choix du menu et retourne le choix de l'utilisateur
int demander_choix_menu();

// Initialises les donnees de la bibliotheque, soit en initialisant tous les livres et mettre le nombre de livre = 0
void initialiser_bibliotheque(t_bibliotheque * pBibli);
// Initialise un livre en mettant tous ses parametres a des valeurs par defaut
void initialiser_livre(t_livre * pLivre);
// Initialise le rapport en mettant le nb de livres et d'emprunt = 0
void initialiser_rapport(t_rapport * pRapport);

// Permet de sauvegarder les informations de la bibliotheque dans un fichier texte
void sauvegarder_fichier(t_bibliotheque * pBibli);
// Permet de lire un fichier texte et d'initialiser la bibliotheque avec ces informations
void lire_fichier(t_bibliotheque * pBibli);

// Fonction pour initialiser la bibliotheque avec des valeurs par defauts
void simuler_lire_fichier(t_bibliotheque * pBibli);

// Permet de trier les livres de la bibliotheque selon leur ISBN
void trier_livres(t_bibliotheque * pBibli);

// Permet d'afficher tous les livres et leurs informations contenu dans la bibliotheque
void afficher_bibliotheque(t_bibliotheque * pBibli);

// Permet de creer un rapport en fonction des informations courante de la bibliotheque et d'afficher ces informations
void generer_rapport(t_bibliotheque *pBibli);

// Demande quel livre emprunter et rend ce livre indisponible en mettant le parametres bEmprunter = EMPRUNT si possible 
void emprunter_livre(t_bibliotheque * pBibli);

// Permet d'enlever le saut de ligne a la fin d'une chaine de caractere pour permettre un meilleur affichage
void retirer_sautligne(char * chaine);
// Bonne question
void super_pause();

// Permet d'afficher un livre[x][y] dans la bibliotheque
void afficher_livre(t_livre livre);
// Permet de trouver un livre dans la bibliotheque selon son ISBN
t_livre* trouver_livre(t_bibliotheque* pBibli, int isbn);
// Demande le livre a retirer dans la bibliotheque a l'utilisateur et le retire si possible
void retirer_livre(t_bibliotheque* pBibli);
// Demande le livre a modifier dans la bibliotheque a l'utilisateur et le modifie si possible
void modifier_livre(t_bibliotheque* bibli);

//------------------------------------------------------
//				Fonction de la pile
//------------------------------------------------------
// Permet de retourner tous les livres emprunter dans la bibliotheque
void gerer_retours(t_bibliotheque* pBibli);
// Permet d'empiler tous les livres emprunter
void gerer_lundi_matin_retours(t_bibliotheque* bibli, t_pile* pPileRetours);
// Permet de depiler tous les livres emprunter et les replacer dans la biblioteque en mettant le parametre bEmprunter = DISPONIBLE
void retourner_livres(t_bibliotheque* bibli, t_pile* pPileRetours);
// Permet d'initialiser ue pile avec ses valeurs par defaut (pointer = NULL)
void init_pile(t_pile* pile);
// Fonction fondamentale d'une pile permettant d'empiler un livre
void empiler(t_pile* pile, t_livre *livre);
// Fonction fondamentale d'une pile permettant de depiler un livre
t_livre* depiler(t_pile* pile);

#endif