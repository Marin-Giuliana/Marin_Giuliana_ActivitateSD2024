#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct Adapost {

	char* tipAnimal;
	int nrAnimale;
};

typedef struct Adapost Adapost;

Adapost creareAdapost(const char* tipAnimal, int nrAnimale)
{
	Adapost a;
	a.tipAnimal = (char*)malloc(sizeof(char) * (strlen(tipAnimal) + 1));
	strcpy(a.tipAnimal, tipAnimal);
	a.nrAnimale = nrAnimale;
	return a;
}

void afisareAdapost(Adapost a)
{
	printf("\n Tip animal: %s , Numar animale: %d.\n", a.tipAnimal, a.nrAnimale);
}


struct Nod {
	Adapost info;
	struct Nod* next;
};

typedef struct Nod Nod;

void push(Nod** foster, Adapost adapost)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->info = adapost;
	nou->next = *foster;
	*foster = nou;
}

Adapost pop(Nod** nodLista)
{
	if (*nodLista != NULL)
	{
		Adapost info = (*nodLista)->info;
		Nod* nodNou = (*nodLista);
		(*nodLista) = (*nodLista)->next;
		free(nodNou);
		return info;
	}
}

void afisareAdaposturi(Nod** stiva)
{
	Nod* aux = NULL;
	while (*stiva != NULL)
	{
		Adapost a = pop(stiva);
		afisareAdapost(a);
		push(&aux, a);
	}
	while (aux)
	{
		push(stiva, pop(&aux));
	}
}

int calculeazaNumarAnimale(Nod** stiva) {
	Nod* aux = NULL;
	int nrAnimale = 0;
	while (*stiva != NULL) {
		Adapost a = pop(stiva);
		nrAnimale += a.nrAnimale;
		push(&aux, a);
	}
	while (aux) {
		push(stiva, pop(&aux));
	}
	return nrAnimale;
}

void main()
{
	Adapost adapostPisici = creareAdapost("Pisici", 30);
	Adapost adapostCaini = creareAdapost("Caini", 20);
	Adapost adapostVulturi = creareAdapost("Pasari", 7);

	Nod* cap = NULL;

	push(&cap, adapostPisici);
	push(&cap, adapostCaini);
	push(&cap, adapostVulturi);
	afisareAdaposturi(&cap);
	printf("\n\n");
	afisareAdaposturi(&cap);
}