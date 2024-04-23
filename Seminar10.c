#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Elev Elev;
struct Elev {
	int id;
	int nrMedii;
	float* medii;
};

typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* st;
	Nod* dr;
};

void inserareArbore(Nod** radacina, Elev e)
{
	if ((*radacina) != NULL)
	{
		if ((*radacina)->info.id > e.id)
		{
			inserareArbore(&((*radacina)->st), e);
		}
		else
		{
			inserareArbore(&((*radacina)->dr), e);
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		*radacina = nod;
		//shallow copy
	}
	// inserarea in arbore binar se face in nodul frunza
}

Elev citireElev(FILE* fp)
{
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.nrMedii);
	e.medii = malloc(sizeof(float) * e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++)
	{
		fscanf(fp, "%f", &(e.medii[i]));//%5.2f ptr afisare
	}
	return e;
}
Nod* citireFisier(char* numeFisier)
{
	Nod* arbore = NULL;
	if (numeFisier != NULL)
		//trb sa luam mai intai situatia favorabila de obicei
	{
		FILE* fp = fopen(numeFisier, "r");
		int nrElevi;
		fscanf(fp, "%d", &nrElevi);
		for (int i = 0; i < nrElevi; i++)
		{
			Elev e = citireElev(fp);
			inserareArbore(&arbore, e);
		}
		fclose(fp);
	}
	else
	{
		return NULL;
	}

	return arbore;
}

void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %d are mediile:", e.id);
	for (int i = 0; i < e.nrMedii; i++)
	{
		printf("%5.2f  ", e.medii[i]);
	}
	printf("\n");
}

void afisareInOrder(Nod* arbore)
{
	if (arbore != NULL)
	{
		afisareInOrder(arbore->st);
		afisareElev(arbore->info);
		afisareInOrder(arbore->dr);
	}
}
//calculeaza media pentru un elev
float  calculeazaMedieElev(Elev e)
{
	if (e.nrMedii > 0)
	{
		float suma = 0;
		for (int i = 0; i < e.nrMedii; i++)
		{
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	else
	{
		printf("Elevul nu are medii!");
	}
}
//calculeaza media generala a tuturor elevilor
float calculeazaSumaNote(Nod* arbore, int* nrNote)
{
	if (arbore != NULL)//de fiecare data!
	{
		float suma = 0;
		//Divide et Impera
		//R
		for (int i = 0; i < arbore->info.nrMedii; i++)
		{
			suma += arbore->info.medii[i];
		}
		(*nrNote) += arbore->info.nrMedii;
		//S
		float sumaS = calculeazaSumaNote(arbore->st, nrNote);
		//D
		float sumaD = calculeazaSumaNote(arbore->dr, nrNote);
		return suma + sumaD + sumaS;
	}
	else
	{
		return 0.0;
	}
}

float calculeazaMedieGenerala(Nod* arbore)
{
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	printf("\n\n%d", nrNote);
	if (nrNote > 0)
	{
		return suma / nrNote;
	}
	else
	{
		return 0;
	}

}
void main()
{
	Nod* arbore = citireFisier("Elevi.txt");
	afisareInOrder(arbore);//sortare binara, sorteaza crescator dupa ID
	printf("Media este %5.2f ", calculeazaMedieGenerala(arbore));
}