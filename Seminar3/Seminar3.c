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

	copie[(*dimensiune)] = aeroport;//shallow copy, nu mai facem stergerea, la deep copy trb sa facem si stergerea

	for (int i = 0; i < (*dimensiune); i++)
	{
		copie[i] = vector[i];
	}
	if(vector)
	free(vector);
	(*dimensiune)++;
	return copie;
}


struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi)
{
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f != NULL)
	{
		char buffer[100];
		while (fgets(buffer, 99, f) != NULL)//fgets -pt liniile din fisier -> returneaza un pointer la char, adresa la care a citit 
		{
			struct Aeroport aeroport;
			char delimitator[] = ",\n";
			char* token = strtok(buffer, delimitator);//lista de separatori
			aeroport.id = atoi(token); //ascii to integer
			token = strtok(NULL, delimitator);
			aeroport.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroport.nume, token);

			token = strtok(NULL, delimitator);
			aeroport.nrTerminale = atoi(token);// atol, atoi functii de convertire

			vectorAeroporturi = adaugaAeroport(vectorAeroporturi, aeroport, nrAeroporturi);

		}
		fclose(f);
	}
	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport)
{
	printf("Aeroportul cu ID %d cu numele %s are %d terminale.\n", aeroport->id, aeroport->nume, aeroport->nrTerminale);////fiind pointer trb si dereferentiere, se pune sageata

}
void afisareVectorAeroporturi(struct Aeroport* aeroporturi, int dim)
{
	printf("Afisare vector: \n");

	for (int i = 0; i < dim; i++)
	{
		afisareAeroport(&aeroporturi[i]);
	}
}

void main()
{

	int dimensiune = 0;
	struct Aeroport* aeroporturi = NULL;
	aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);
	afisareVectorAeroporturi(aeroporturi, dimensiune);

}