#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


struct Aeroport
{
	int id;
	char* nume;
	int nrTerminale;
};

struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport, int* dimensiune)
{
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++)
	{
		copie[i] = vector[i];
	}
	if (vector)
		free(vector);
	(*dimensiune)++;
	return copie;
}


void citireMatriceFisier(const char* numeFisier, int* nrAeroporturiLinii,
	int nrClustere,struct Aeroport** aeroporturi)
{
	FILE* f = fopen(numeFisier, "r");

	if (f != NULL)
	{
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL)
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);
			aeroport.id = atoi(token); 
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);
			int poz = aeroport.nrTerminale % 2;
			aeroporturi[poz] = adaugaAeroport(aeroporturi[poz], aeroport, &(nrAeroporturiLinii[poz]));

		}
		fclose(f);
	}
}

void afisareAeroport(struct Aeroport* aeroport)
{
	if (aeroport != NULL)
	{
		printf("%d. %s are %d terminale.\t", aeroport->id, aeroport->nume, aeroport->nrTerminale);
	}
	else
		(printf("Nu exista acest aeroport!"));
}
void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim)
{
	printf("Afisare vector: \n");

	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

void afisareMatrice(struct Aeroport** matrice, int nrClustere, int* nrColoane)
{
	for (int i = 0; i < nrClustere; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			afisareAeroport(&matrice[i][j]);
		}
		printf("\n");
	}
}
//functie pentru a calcula media nr de terminale din aeroporturi,
// in functie de paritatea nr terminalelor
float mediaTerminale(struct Aeroport** matrice, int* nrAeroporturiLinii, int paritate)
{
		paritate = paritate % 2;
		int suma = 0;
		for (int i = 0; i < nrAeroporturiLinii[paritate]; i++)
		{
			suma += matrice[paritate][i].nrTerminale;

		}
		if (nrAeroporturiLinii[paritate])
		{
			return suma / nrAeroporturiLinii[paritate];
		}
		return 0;
}

struct Aeroport* cautaAeroportID(struct Aeroport** matrice, int* nrColoane, int nrLinii, int Id)
{
	for (int i = 0; i < nrLinii; i++)
	{
		for (int j = 0; j < nrColoane[i]; j++)
		{
			if (matrice[i][j].id == Id)
				return &(matrice[i][j]);

		}
	}
	return NULL;
}
void dezalocareVector(struct Aeroport** aeroporturi, int* dim)
{
	if (aeroporturi == NULL || *aeroporturi == NULL || dim==NULL) 
	{
		return NULL;
	}
	for (int i = 0; i < (*dim); i++)
	{
		free((*aeroporturi)[i].nume);
	}
	free(*aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}

void dezalocareMatrice(struct Aeroport*** matrice, int** nrColoane, int* nrClustere)
{
	for (int i = 0; i < (*nrClustere); i++)
	{
		dezalocareVector(&((*matrice)[i]), (*nrColoane)[i]);
	}
	free(*matrice);
	(*matrice) = NULL;
	free(*nrColoane);
	(*nrColoane) = NULL;
	(*nrClustere) = 0;
}

void main()
{
	struct Aeroport** aeroporturi;
	int nrLinii = 2;
	int* nrColoane = (int*)malloc(sizeof(int) * nrLinii);
	aeroporturi = (struct Aeroport**)malloc(sizeof(struct Aeroport*)* nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		nrColoane[i] = 0;
		aeroporturi[i] = NULL;
	}
	citireMatriceFisier("aeroporturi.txt", nrColoane, nrLinii, aeroporturi);
	afisareMatrice(aeroporturi, nrLinii, nrColoane);
	float medie1=mediaTerminale(aeroporturi, nrColoane, 12);
	printf("Media paritate: para: %.2f", medie1);
	float medie2 = mediaTerminale(aeroporturi, nrColoane, 11);
	printf("\n");
	printf("Media paritate: impara: %.2f", medie2);
	printf("\n\n");
	afisareAeroport(cautaAeroportID(aeroporturi, nrColoane, nrLinii, 11));
	dezalocareMatrice(&aeroporturi, &nrColoane, &nrLinii);
}
//matricea este un tablou bidimensional cu date omogene
//vector de vectori
