#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotheque.h"




int main()
{
	
	// Déclaration des variables.
	int choix_menu;
	t_bibliotheque bibli;

	
	// Initialisation de la fonction rand()
	//srand(time(NULL));

	// Initialisation de la bibliotheque
	initialiser_bibliotheque(&bibli);
	lire_fichier(&bibli);
	afficher_bibliotheque(&bibli);

	
	

	
	
	// ...

    do
    {
		
		// Gestion du menu.
        choix_menu = demander_choix_menu();
		
        switch(choix_menu)
        {
            case 1: afficher_bibliotheque(&bibli); break;
            case 2: lire_fichier(&bibli); break;
            case 3: modifier_livre(&bibli); break;
			case 4: retirer_livre(&bibli); break;
            case 5: emprunter_livre(&bibli); break;
            case 6: gerer_retours(&bibli); break;
            case 7: generer_rapport(&bibli); break;
            case 8: sauvegarder_fichier(&bibli); break;        
			case 9: trier_livres(&bibli); break;
			case 0: break; // Quitter.
            default: break;
        }
    }while(choix_menu != 0);
    
    return EXIT_SUCCESS;
}

void lire_fichier(t_bibliotheque * pBibli)
{
	FILE* fichier = NULL;
	fichier = fopen("biblio.txt", "r");
	

#if(SIMULATION == 0)
	simuler_lire_fichier(pBibli);


#else
	if (fichier != NULL)
	{
		int caractere = 0;
		int indiceChar = 0;
		int indiceLivre = -1;
		int premiereLigne = 1;
		int sauvegarderBibli = 0; //Eviter de sauvegarder un livre null
		int indiceLivreData = 0;

		int nbNewLineSuite = 0;
		char newLine = '\n';

		char ligne[TAILLE_MAX_LIGNE] = "";



		t_livre* livres = NULL;
		do
		{
			caractere = fgetc(fichier);
			//Si c'est un saut de ligne on sauvegarde les donnee et on reinitialise les variable
			if (caractere == newLine) {
				nbNewLineSuite++;
				//Premiere ligne du fichier
				if (premiereLigne == 1) {
					premiereLigne = 0;

					//Determine le interger lu
					int chiffre = atoi((ligne));
					printf("%d\n", chiffre);
					//Cree le tableau de livres
					livres = (t_livre*)malloc(chiffre * sizeof(t_livre));
					
				}
				//Deux newline de suite = nouveau livre
				else if (nbNewLineSuite == 2) {
					if (sauvegarderBibli) {
						//Enregistrer le livre dans la bibli
						int genre = livres[indiceLivre].genre;
						pBibli->livres[genre][pBibli->nb_livres[genre]] = livres[indiceLivre];
						pBibli->nb_livres[genre]++;

						
						indiceLivreData = 0;
					}
					sauvegarderBibli = 1; // apres le premier double saut dans le fichier on peut sauvegarder bibli (pcq le premier double saut est pour le nb de livres)
					indiceLivre++;
				}
				else if (indiceLivre >= 0)
				{
					//Determiner quelle donnee changer
					// atoi --> convert string to int
					switch (indiceLivreData)
					{
						//genre
					case 0:
						livres[indiceLivre].genre = atoi(ligne);
						break;
						//titre
					case 1:
						strcpy(livres[indiceLivre].titre, ligne);
						break;
						//prenom
					case 2:
						strcpy(livres[indiceLivre].auteur_prenom, ligne);
						break;
						//Nom
					case 3:
						strcpy(livres[indiceLivre].auteur_nom, ligne);
						break;
						//nb Pages
					case 4:
						livres[indiceLivre].nb_pages = atoi(ligne);
						break;
						//Isbn
					case 5:

						livres[indiceLivre].isbn = atoi(ligne);
						break;
						// disponibilitee
					case 6:
						livres[indiceLivre].bEmprunte = atoi(ligne);
						break;
					default:
						break;
					}
					indiceLivreData++;
				}
				//Reinitialiser
				memset(ligne, 0, sizeof(ligne));
				indiceChar = 0;
			}
			// On ajoute le caractere dans la ligne
			else
			{
				nbNewLineSuite = 0;
				ligne[indiceChar++] = caractere;
			}


		} while (caractere != EOF);

		free(livres);
		
	}
	else
	{
		// message d'erreur
		printf("Impossible d'ouvrir le fichier biblio.txt");
	}

	//fclose(fichier);

#endif
	
}

void simuler_lire_fichier(t_bibliotheque * pBibli)
{
	t_livre livre1;
	t_livre livre2;
	t_livre livre3;

	livre1.genre = INFORMATIQUE;
	strcpy(livre1.titre, "Les Ninjas de l'Info 2");
	strcpy(livre1.auteur_prenom, "Yannick");
	strcpy(livre1.auteur_nom, "Roy");
	livre1.nb_pages = 252;
	livre1.isbn = 369;
	livre1.bEmprunte = DISPONIBLE;
	pBibli->livres[INFORMATIQUE][pBibli->nb_livres[INFORMATIQUE]] = livre1;
	pBibli->nb_livres[INFORMATIQUE]++;

	livre2.genre = INFORMATIQUE;
	strcpy(livre2.titre, "Les fous du code");
	strcpy(livre2.auteur_prenom, "Hugues");
	strcpy(livre2.auteur_nom, "Saulnier");
	livre2.nb_pages = 355;
	livre2.isbn = 1001;
	livre2.bEmprunte = DISPONIBLE;
	pBibli->livres[INFORMATIQUE][pBibli->nb_livres[INFORMATIQUE]] = livre2;
	pBibli->nb_livres[INFORMATIQUE]++;

	livre3.genre = FICTION;
	strcpy(livre3.titre, "Un tableau de pointeurs");
	strcpy(livre3.auteur_prenom, "Pasdor");
	strcpy(livre3.auteur_nom, "Mi");
	livre3.nb_pages = 180;
	livre3.isbn = 1234;
	livre3.bEmprunte = DISPONIBLE;
	pBibli->livres[FICTION][pBibli->nb_livres[FICTION]] = livre3;
	pBibli->nb_livres[FICTION]++;
}

void super_pause()
{
	printf("Appuyez sur une touche pour continuer! \n");
	//_getch();
}

void retirer_sautligne(char * chaine)
{
	int pos = strlen(chaine) - 1;
	if (chaine != NULL && chaine[pos] == '\n')
		chaine[pos] = '\0'; // Si on trouve \n à la fin, on le remplace par \0
}
void initialiser_livre(t_livre* pLivre)
{
	pLivre->genre = AUCUN;
	strcpy(pLivre->titre, " N/A");
	strcpy(pLivre->auteur_prenom, "N/A");
	strcpy(pLivre->auteur_nom, "N/A");
	pLivre->nb_pages = 0;
	pLivre->isbn = -1;
	pLivre->bEmprunte = DISPONIBLE;
}
void initialiser_bibliotheque(t_bibliotheque* pBibli)
{
	for (int i = 0; i < NB_GENRES; ++i) 
	{
		(*pBibli).nb_livres[i] = 0;
		for (int j = 0; j < NB_LIVRES_MAX_RANGEE; ++j) 
		{
			t_livre livreInitial;
			initialiser_livre(&livreInitial);
			(*pBibli).livres[i][j] = livreInitial;
		}
	}

	initialiser_rapport(&(pBibli->rapport));
}


void initialiser_rapport(t_rapport* pRapport)
{
	pRapport->nb_emprunts = 0;
	pRapport->nb_livre = 0;
}

void sauvegarder_fichier(t_bibliotheque* pBibli)
{
	FILE* fichier = NULL;

	fichier = fopen("biblio.txt", "w");

	if (fichier != NULL)
	{
		// Determiner le nombre de livre
		int nbLivres = 0;
		for(int i =0; i < NB_GENRES; ++i)
		{
			nbLivres += pBibli->nb_livres[i];
		}
		//Ecrire le nb livre
		fprintf(fichier, "%d\n\n", nbLivres);

		//Iterer sur tous les livres de la bibliotheque et les sauvegarders
		for (int i = 0; i < NB_GENRES; ++i) 
		{
			int nbLivreGenre = pBibli->nb_livres[i];
			for (int j = 0; j < nbLivreGenre; ++j) 
			{
				t_livre livre = pBibli->livres[i][j];
				fprintf(fichier, "%d\n", livre.genre);
				fprintf(fichier, "%s\n", livre.titre);
				fprintf(fichier, "%s\n", livre.auteur_prenom);
				fprintf(fichier, "%s\n", livre.auteur_nom);
				fprintf(fichier, "%d\n", livre.nb_pages);
				fprintf(fichier, "%d\n", livre.isbn);
				fprintf(fichier, "%d\n\n", livre.bEmprunte);
			}
		}

		printf("La sauvegarde de la bibli a bien fonctionnee\n");
	}
	else
	{
		// message d'erreur
		printf("Impossible d'ouvrir le fichier biblio.txt\n");
	}
	fclose(fichier);

}

//Trier selon le isbn
void trier_livres(t_bibliotheque* pBibli)
{
	for (int i = 0; i < NB_GENRES; i++)
	{
		//Trier dans chaque genre
		for (int j = 0; j < pBibli->nb_livres[i]; j++)
		{
			t_livre plusPetit = pBibli->livres[i][j];
			for(int k = 1; k < pBibli->nb_livres[i]; ++k)
			{
				//si le livre actuel est plus petit, on swap
				if(pBibli->livres[i][k].isbn < plusPetit.isbn)
				{
					t_livre temp = plusPetit;
					pBibli->livres[i][k] = temp;

				}
			}
		}
	}
}

void afficher_bibliotheque(t_bibliotheque* pBibli)
{	
	for (int i = 0; i < NB_GENRES; i++)
	{
		for (int j = 0; j < pBibli->nb_livres[i]; j++)
		{
			t_livre livre;
			livre = pBibli->livres[i][j];
			afficher_livre(livre);
		}
	}
}

void generer_rapport(t_bibliotheque* pBibli)
{
	
	initialiser_rapport(&(pBibli->rapport));//initialiser pour ne pas voir le double a chaque fois quon genere le rapport

	int i;
	int j;
	
	
	int nb_livre_total=0;
	for (i = 0; i < NB_GENRES; ++i)
	{
		
		pBibli->rapport.nb_livre += pBibli->nb_livres[i];// rajoute le nb de livre dans XY genre 
	}

	int nb_emprunt_total=0;

for (i = 0; i < NB_GENRES; ++i) {
		for (j = 0; j < pBibli->nb_livres[i]; ++j) {
			if ((pBibli->livres[i][j]).bEmprunte == EMPRUNT) 
			{
				
			

			pBibli->rapport.nb_emprunts += 1;// si un livre est emprunte, le nb_emprunts +=1
			
			}
		}
	}


	printf("\n#################\n");
	printf("Nb de livres: %d\n", pBibli->rapport.nb_livre);
	printf("Nb Emprunts: %d\n", pBibli->rapport.nb_emprunts);
	printf("#################\n");  //affichage du rapport
}
void retirer_livre(t_bibliotheque* pBibli)
{
	int ISBN;
	printf("\nEntrer le ISBN du livre a retirer : ");
	scanf("%d", &ISBN);

	//Trouver le livre avec ISBN
	t_livre livre;
	int livre_trouve = 0;
	int i;
	int j;
	int temp_i;
	int temp_j;
	for ( i = 0; i < NB_GENRES; ++i) {
		for ( j = 0; j < pBibli->nb_livres[i]; ++j) {
			if ((pBibli->livres[i][j]).isbn == ISBN) {
				livre = pBibli->livres[i][j];
				temp_i = i;
				temp_j = j;
				livre_trouve = 1;
				break;
			}
		}
	}
	// decaler le tableau et "ecraser" le livre retire par le fait meme
	if (livre_trouve==1)
	{
		i = temp_i;
		j = temp_j;

		for (j; j < pBibli->nb_livres[i]; ++j)
		{
			if(j== NB_LIVRES_MAX_RANGEE-1)//Dans le cas ou les 100 livres sont utilise, je ne peux pas copier le livre (10) pour ecraser le livre 99
			 // car celui-ci nexiste pas dans notre tableau, ainsi je reinitialise le livre 99
			{
				initialiser_livre(&(pBibli->livres[i][NB_LIVRES_MAX_RANGEE-1]));
				
			}
			else
			{ 
			pBibli->livres[i][j] = pBibli->livres[i][j + 1];
			}
		}

			pBibli->nb_livres[i]--;
	//Le livre n'existe pas, on sort de la fonction
	}
	else
	{
		printf("Ce livre n'existe pas");
		return;
	}


	//----------------------------------------------
}

void emprunter_livre(t_bibliotheque* pBibli)
{

	
		int isbn;
		printf("Entrer le ISBN du livre a emprunter : ");
		scanf("%d", &isbn);

		t_livre* livre = trouver_livre(pBibli, isbn);
		if (livre != NULL)
			livre->bEmprunte = 1;
}

t_livre* trouver_livre(t_bibliotheque * bibli, int isbn)
{
	t_livre* livre = NULL;
	int livre_trouve = 0;
	for (int i = 0; i < NB_GENRES; ++i) {
		for (int j = 0; j < bibli->nb_livres[i]; ++j) {
			if ((bibli->livres[i][j]).isbn == isbn) {
				//Pointer du livre
				livre = &(bibli->livres[i][j]);
				livre_trouve = 1;
				break;
			}
		}
	}
	return livre;
}

void gerer_retours(t_bibliotheque* pBibli)
{
	gerer_lundi_matin_retours(pBibli, &(pBibli->retours));
	retourner_livres(pBibli, &(pBibli->retours));
}

void gerer_lundi_matin_retours(t_bibliotheque* bibli, t_pile* pPileRetours)
{
	//regarder tous les livres de la bibli
	for (int i = 0; i < NB_GENRES; ++i) {
		for (int j = 0; j < bibli->nb_livres[i]; ++j) {
			if ((bibli->livres[i][j]).bEmprunte == EMPRUNT) {
				//empiler le livre qui a ete emprunte

				empiler(pPileRetours, &(bibli->livres[i][j]));

			}
		}
	}

}
void retourner_livres(t_bibliotheque* bibli, t_pile* pPileRetours)
{
	
		if (pPileRetours == NULL)
		{
			return;
		}
		t_livre* actuel = pPileRetours->premier;

		while (actuel != NULL)
		{
			actuel->bEmprunte = DISPONIBLE;
			depiler(pPileRetours);
		}
	
}

void init_pile(t_pile* pile)
{
	pile->premier = NULL;
}
	
void empiler(t_pile* pile, t_livre *livre)
{
		
	if (pile == NULL )
	{	
		printf("probleme pile ");
		return;
	}

		//gestion de la pile
		livre->suivant = pile->premier;
		pile->premier = livre;
			
}

t_livre* depiler(t_pile* pile)
{
	if (pile == NULL || pile->premier == NULL)
	{
		printf("probleme depile");
		return NULL;
	}
	
	//gestion de la pile
	t_livre* livre_1;
	livre_1 = pile->premier;
	pile->premier = pile->premier->suivant;
	return livre_1;
}


int demander_choix_menu()
{
	
	int choix_menu;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("         Bibliotheque 145 inc.\n");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("1 - Afficher Bibliotheque.\n");
	printf("2 - Lire Fichier Bibliotheqe\n");
	printf("3 - Modifier Livre\n");
	printf("4 - Retirer Livre\n");
	printf("5 - Emprunter Livre\n");
	printf("6 - Retourner Livres (Lundi Matin)\n");
	printf("7 - Generer Rapport\n");
	printf("8 - Sauvegarder Bibliotheque\n");
	printf("9 - Trier Libres (bonus)\n");
	printf("0 - Quitter\n");
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	scanf("%d", &choix_menu);
	return choix_menu;

}
void afficher_livre(t_livre livre)
{
	
	printf("------------------------------------\n");
	printf("Titre: %s\n", livre.titre);
	printf("Auteur: %s ", livre.auteur_prenom);
	printf("%s\n", livre.auteur_nom);
	printf("Genre: %d\n", livre.genre);
	printf("Pages: %d\n", livre.nb_pages);
	printf("ISBN: %d\n", livre.isbn);
	printf("Emprunte: %d\n", livre.bEmprunte);
	printf("------------------------------------\n");
}
void modifier_livre(t_bibliotheque* bibli)
{

	int ISBN;
	printf("\nEntrer le ISBN du livre a modifier : ");
	scanf("%d", &ISBN);
	//Trouver le livre avec ISBN
	t_livre* livre=NULL;
	int livre_trouve = 0;
	for (int i = 0; i < NB_GENRES; ++i) {
		for (int j = 0; j < bibli->nb_livres[i]; ++j) {
			if ((bibli->livres[i][j]).isbn == ISBN) {
				//Pointer du livre
				livre = &(bibli->livres[i][j]);
				livre_trouve = 1;
			}
		}
	}
	if (livre != NULL)
		afficher_livre(*livre);
	//Le livre n'existe pas, on sort de la fonction
	else
	{
		printf("Ce livre n'existe pas");
		return;
	}
	int genre, nombre_page;
	char titre[TAILLE_TITRE], nom[TAILLE_NOM], prenom[TAILLE_PRENOM];
	printf("\nEntrez le nouveau genre: ");
	scanf("%d", &genre);

	//Buffer pour le enter
	char buffer[10];
	fgets(buffer, 10, stdin);

	//Entrer des string
	printf("\nEcrivez le nouveau titre du livre: ");
	fgets(titre, TAILLE_TITRE, stdin);
	printf("\nEcrivez le nouveau nom de l'auteur: ");
	fgets(nom, TAILLE_NOM, stdin);
	printf("\nEcrivez le nouveau prenom de l'auteur: ");
	fgets(prenom, TAILLE_PRENOM, stdin);
	printf("\nEntrez le nouveau nombre de pages: ");
	scanf("%d", &nombre_page);

	retirer_sautligne(nom);
	retirer_sautligne(prenom);
	retirer_sautligne(titre);

	livre->genre = genre;
	strcpy(livre->auteur_nom, nom);
	strcpy(livre->auteur_prenom, prenom);
	strcpy(livre->titre, titre);
	livre->nb_pages = nombre_page;

	printf("\nVous avez modifie le livre avec le ISBN: %d", ISBN);
	printf("\n\nAppuye sur une touche pour continuer!");

	//2 scanf pour que ca fonctionne (1 pour )
	char ch;
	scanf("%c", &ch);
	scanf("%c", &ch);

}