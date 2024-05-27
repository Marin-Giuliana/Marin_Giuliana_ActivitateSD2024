#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<malloc.h>
#include<string.h>
//arbore: graf conex aciclic
//arbore binar: fiecare parinte are maxim 2 descendenti
//stanga: mai mic decat ce e in radacina, dreapta: mai mare decat ce e in radacina
//fiec nod trb sa retina adresa fiilor
//inordine:radacina la mijloc, stanga, radacina, dreapta
//preordine: radacina, stanga, dreapta
//postordine: stranga, dreapta, radacina

typedef struct Elev Elev;
typedef struct Nod Nod;


struct Elev
{
	int id;
	int nrMedii;
	float* medii;
};

struct Nod
{
	Elev info;
	Nod* st;
	Nod* dr;
};

//functie care insereaza in arbore, care sa respecte principiul(STANGA mic, DREAPTA mare)
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
		int grad = gradEchilibru((*radacina));
		//gradul de echilibru are mereu valori intre[-2,2]: 0,1,2,-2
		if (grad == 2)
		{
			if (gradEchilibru((*radacina)->st) == 1)//poate sa fie doar 1 sau -1 gradul de radacina de stanga
			{
				(*radacina) = rotireDreapta((*radacina));
			}
			else
			{
				(*radacina)->st = rotireStanga((*radacina)->st);
				(*radacina) = rotireDreapta((*radacina));
			}
		}
		if (grad == -2)
		{
			if (gradEchilibru((*radacina)->dr) == 1) //situatia complexa:incepem cu partea unde avem dezechilibrul, vom folosi ca pivot nodul radacinii de dreapta
			{
				(*radacina)->dr = rotireStanga((*radacina));
			}
			(*radacina) = rotireStanga((*radacina));
		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		//trebuie sa initializam toate atributele nodului
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;
		//si st si dr sunt null=>nod frunza
		*radacina = nod;
	}
}



Elev citireElev(FILE* fp)
{
	Elev e;
	fscanf(fp, "%d", &e.id);
	fscanf(fp, "%d", &e.nrMedii);
	//foloseam buffer cand nu stiam cat spatiu trebuie sa alocam, aici stim
	e.medii = malloc(sizeof(float) * e.nrMedii);//ii aloc spatiu
	//citim din fisier toate mediile:
	for (int i = 0; i < e.nrMedii; i++)
	{
		fscanf(fp, "%f", &(e.medii[i]));
	}
	return e;
}

//functie care sa citeasca din fisier elevii
Nod* citireFisier(char* numeFisier)
{
	Nod* arbore = NULL;

	//returneaza un arbore
	if (!numeFisier)
	{
		return NULL;
	}
	else
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
	return arbore;
}

void afisareElev(Elev e)
{
	printf("Elevul cu id-ul %d are mediie ", e.id);
	for (int i = 0; i < e.nrMedii; i++)
	{
		printf("%5.2f", e.medii[i]);
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

//functie care calculeaza media generala a tuturor elevilor, a clasei
float calculeazaSumaNote(Nod* arbore, int* nrNote)
{
	if (arbore != NULL)
	{
		float suma = 0;
		//radacina
		for (int i = 0; i < arbore->info.nrMedii; i++)
		{
			suma += arbore->info.medii[i];
		}
		(*nrNote) += arbore->info.nrMedii; //procesarea radacinii
		//stanga
		float SumaS = calculeazaSumaNote(arbore->st, nrNote);
		//dreapta
		float SumaD = calculeazaSumaNote(arbore->dr, nrNote);
		return suma + SumaS + SumaD;
	}
	else
	{
		return 0;
	}
}

float calculeazaMedieGenerala(Nod* arbore)
{
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);
	if (nrNote > 0)
	{
		return suma / nrNote;
	}
	else
	{
		return 0;
	}
}

Nod* rotireDreapta(Nod* radacina)
{
	Nod* nod;
	//avem dezechilibru la stanga
	nod = radacina->st;
	radacina->st = nod->dr;
	nod->dr = radacina;
	return nod;
}

// analogie cu metoda paharelor pentru rotatii

Nod* rotireStanga(Nod* radacina)
{
	//avem dezechilibru la dreapta
	Nod* nod;
	nod = radacina->dr;
	radacina->dr = nod->st;
	nod->st = radacina;
	return nod;

}

void afisarePreOrder(Nod* radacina)
{
	if (radacina)
	{
		afisareElev(radacina->info);
		afisarePreOrder(radacina->st);
		afisarePreOrder(radacina->dr);
	}
}

int inaltime(Nod* radacina)
{

	if (radacina == NULL)
		return 0;
	else
	{
		int inaltimeSt = inaltime(radacina->st);
		int inaltimeDr = inaltime(radacina->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
		/*if (inaltimeSt > inaltimeDr)
		{
			return 1 + inaltimeSt;
		}
		else
		{
			return 1 + inaltimeDr;
		}*/
	}
}

int gradEchilibru(Nod* radacina)
{
	int inaltimeSt = inaltime(radacina->st);
	int inaltimeDr = inaltime(radacina->dr);
	return inaltimeSt - inaltimeDr;
}

void stergereArbore(Nod** radacina)
{
	if (*radacina)
	{
		stergereArbore(&((*radacina)->st));//il dereferentiem prin steluta, am nevoie de adresa, pun &
		stergereArbore(&((*radacina)->dr));
		free((*radacina)->info.medii);
		free((*radacina));
		(*radacina) = NULL;
	}
}

void main()
{
	//ne declaram un arbore
	Nod* arbore = citireFisier("Elevi.txt");

	afisarePreOrder(arbore);

	afisareInOrder(arbore); //sunt sortate dupa id

	printf("Media este: %5.2f", calculeazaMedieGenerala(arbore));

	stergereArbore(&arbore);
	afisarePreOrder(arbore);
}