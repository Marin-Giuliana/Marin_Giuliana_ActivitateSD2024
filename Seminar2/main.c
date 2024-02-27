#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
/// vectorul este o structura liniara, contigua, omogena

struct Calculator {

	char* serie;
	float pret;
	int nrPorturi;
};

struct Calculator Initializare(const char* serie, float pret, int nrPorturi)
{
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
		strcpy(c.serie, serie);
	c.nrPorturi = nrPorturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(struct Calculator c)
{
	printf("Calculatorul cu seria %s, costa %5.2f si are %d porturi\n", c.serie, c.pret, c.nrPorturi);
}

void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare)
{
	if(nrCalculatoare>0 && vector != NULL)
	for (int i = 0; i < nrCalculatoare; i++)
	{
		afisareCalculator(vector[i]);
	}
}
//dangling pointer shallow copy=copiere de adrese
// deep copy alocare noua de memorie, linie 36, apoi copiam in el pe linia 37
struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalculatoareCopiate)
{
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator*) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++)
	{
		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (1 + streln(calculatoare[i].serie)));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
	return copiate;
}

struct Calculator* copiazaCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalculatoare, int pragNrPorturi, int* nrCalculatoarePorturi)
{
	*nrCalculatoarePorturi = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi)
		{
			(*nrCalculatoarePorturi)++;

		}
	}
	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoarePorturi));
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi)
			v[k++] = Initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);//DEEP COPY

	}
	return v;
}
void dezalocare(struct Calculator** vector, int* dim)
{

	for (int i = 0; i < (*dim); i++)
	{
		free((*vector)[i].serie);

	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

void main()
{
	int nrCalculatoare = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	for (int i = 0; i < nrCalculatoare; i++)
	{
		calculatoare[i] = Initializare("1234567890", i * 20 + 10, i + 1);

	}
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);
	printf("\n\n");
	int nrCalculatoareCopiate = 3;
	int nrCalculatoarePorturi = 0;
	struct Calculator* calculatoareCopiate = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);
	printf("\n\n");
	struct Calculator* calculatoarePorturi= copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);
	afisareVectorCalculatoare(calculatoarePorturi, nrCalculatoarePorturi);
	dezalocare(&calculatoare,&nrCalculatoare);
	//int v[10];//zona de memorie de pe stack, max 40 octeti
	//int* v1;//4 octeti
	//sa se afiseze primul calculator din vector care are pret dat
}