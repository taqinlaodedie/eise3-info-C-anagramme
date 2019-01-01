#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct s_lettre
{
	char nom;
	int nombre;
};
struct s_dico {
  char estMot;
  char estFeuille;
  char estAnagramme;
  struct s_dico *suite[26];
};
char chaine[100];
int indice = 0;

struct s_lettre *creerTableauCompeurLettre(char *chaine)
{
	int compteur[256] = {0};
	int nb_diff = 0;

	for(; *chaine; chaine++) {//si contenu de pointeur chaine n'est pas 0, decaler la position
		compteur[*chaine] ++;
		if(compteur[*chaine] > 0) {
			//chercher le nombre de differentes caracteres
			nb_diff ++;
		}
	}

	struct s_lettre *tab = malloc((nb_diff + 1) * sizeof(struct s_lettre));
	//rend le pointeur utilisable comme une tableau
	assert(tab);
	tab[0].nom = '\0';
	tab[0].nombre = nb_diff;

	int j = 1;
	//remplir la tableau
	for(int i = 0; i < 256; i++) {
		if(compteur[i] > 0) {
			tab[j].nom = i;
			tab[j].nombre = compteur[i];
			j ++;
		}
	}

	return tab;
}

void afficheTableauCompteurLettre(char *chaine, struct  s_lettre *tab)
{
	printf("%s : ", chaine);
	assert(tab);
	for(int i = 1; i < tab[0].nombre; i++) {
		printf("- %c:%d -", tab[i].nom, tab[i].nombre);
	}
	printf("\n");
}

void anagramme(struct s_lettre *tab, int taille, char *chaineAnagramme, char *debAnagramme)
{
	int i;

	for(int i = 1; i <= tab[0].nombre; i++) {
		if(taille == 0) {
			printf("%s\n",debAnagramme);
			break;
		}
		else if(tab[i].nombre > 0) {
			chaineAnagramme[0] = tab[i].nom;
			tab[i].nombre --;
			anagramme(tab, --taille, ++chaineAnagramme, debAnagramme);
			taille ++;
			chaineAnagramme --;
			tab[i].nombre ++;
		}
	}
}

struct s_dico *creerNoeudDico(char estFeuille, char estMot)
{
	struct s_dico *dico = NULL;
	dico = malloc(sizeof(struct s_dico));

	if(dico == NULL) {
		printf("Erreur d'allocation pour dico\n");
		return NULL;
	}

	dico->estMot = estMot;
	dico->estFeuille = estFeuille;
	dico->estAnagramme = 0;
}

void insererMot(char *mot, struct s_dico *dictionnaire)
{
	int i = 0, j = 0;
	struct s_dico *dico = dictionnaire;
	char *lettre = strdup(mot);

	while(*lettre) {
		i = *lettre - 'a';
		if(dico->suite[i] == NULL) {
			dico->suite[i] = creerNoeudDico(0, 0);
			dico->estFeuille = 0;
		}
		dico = dico->suite[i];
		lettre ++;
	}

	dico->estMot = 1; //fin du mot
	dico->estFeuille = 1;

	while(j < 26) {
		if(dico->suite[j] != NULL) {
      		dico->estFeuille = 0;
      		break;
    	}
    	j ++;
	}
}

struct s_dico *creerDictionnaire(char *nomFichier) 
{
	struct s_dico *dico = creerNoeudDico(0, 0);
	char tmp[100];
	FILE *f = fopen(nomFichier, "r");

	while(fscanf(f, "%s", tmp) != EOF) {
		insererMot(tmp, dico);
	}
	fclose(f);

	return dico;
}

void afficherDictionnaire(struct s_dico *dictionnaire)
{
	struct s_dico *dico = dictionnaire;

	if(dico->estMot == 1) {
		chaine[indice] = '\0';
		printf("%s\n", chaine);
	}

	for(int i = 0; i < 26; i++) {
		if(dico->suite[i] != NULL) {
			chaine[indice] = 'a' + i;
			indice ++;
			afficherDictionnaire(dico->suite[i]);
			indice --;
		}
	}
}

/*
int main(void)
{
	char *chaine = "neon";
	char out[100];
	struct s_lettre *tab = creerTableauCompeurLettre(chaine);
	afficheTableauCompteurLettre(chaine, tab);
	anagramme(tab, 4, out, out);
	
	free(tab);

	return 0;
}
*/

int main(void)
{
	struct s_dico *dico = creerDictionnaire("dico.txt");

	afficherDictionnaire(dico);

	return 0;
}