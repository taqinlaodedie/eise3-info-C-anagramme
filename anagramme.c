#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct s_lettre
{
	char nom;
	int nombre;
};

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

int main(void)
{
	char *chaine = "neon";
	char out[4];
	struct s_lettre *tab = creerTableauCompeurLettre(chaine);
	afficheTableauCompteurLettre(chaine, tab);
	for(; *chaine; chaine++) {
		anagramme(tab, 4, out, out);
	}
	free(tab);

	return 0;
}