#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

//Marin Giuliana-> M si G
struct Magazin 
{
    int idProdus;
    int nrProduse;
    char* denumireProdus;
    float* preturi;
};

struct Magazin citire() 
{
    struct Magazin articol;
    articol.denumireProdus = (char*)malloc(50 * sizeof(char));

    printf("Introduceti id-ul articolului: ");
    scanf("%d", &articol.idProdus);

    printf("Introduceti denumirea categoriei de produse: ");
    scanf("%s", articol.denumireProdus);

    printf("Introduceti numarul de produse: ");
    scanf("%d", &articol.nrProduse);

    articol.preturi = (float*)malloc(articol.nrProduse * sizeof(float));
    for (int i = 0; i < articol.nrProduse; i++) 
    {
        printf("Introduceti pretul produsului %d: ", i + 1);
        scanf("%f", &articol.preturi[i]);
    }

    return articol;
}

void eliberareMemorie(struct Magazin* articol)
{
    free(articol->denumireProdus);
    free(articol->preturi);
}

struct Magazin* creareVector(int size)
{
    struct Magazin* vector = (struct Magazin*)malloc(size * sizeof(struct Magazin));
    if (vector == NULL)
        printf("EROARE");
    else
        return vector;
}

struct Magazin* copiere(struct Magazin* vector, int size, int* newsize)
{

    struct Magazin* vectornou = creareVector(size);
    *newsize = 0;
    for (int i = 0; i < size; i++)
    {
        if (vector[i].nrProduse >10)
        {
            vectornou[*newsize] = vector[i];
            (*newsize)++;
        }
    }
    return vectornou;
}

float mediePreturi(struct Magazin articol)
{
    float suma = 0;
    for (int i = 0; i < articol.nrProduse; i++) 
    {
        suma += articol.preturi[i];
    }
    return suma / articol.nrProduse;
}

struct Magazin* mutare(struct Magazin* vector, int size, int* newsize)
{
    struct Magazin* vectornou = creareVector(size);
    *newsize = 0;
    for (int i = 0; i < size; i++)
    {
        if(vector[i].idProdus%5==0)
        {
            vectornou[*newsize] = vector[i];
            (*newsize)++;
        }
    }
    if (vectornou == NULL)
        printf("Nu exista produse de acest tip\n");
    else
        return vectornou;
}
struct Magazin* concatenare(struct Magazin* vector1, int size1, struct Magazin* vector2, int size2, int* newsize)
{
    struct Magazin* vectornou = creareVector(size1 + size2);
    *newsize = 0;
   for (int i = 0; i < size1; i++)
    {
        vectornou[*newsize] = vector1[i];
        (*newsize)++;
    }
    for (int i = 0; i < size2; i++)
    {
        vectornou[*newsize] = vector2[i];
        (*newsize)++;
    }
    return vectornou;
}


void modificaStoc(struct Magazin* articol, int nouNrProduse) 
{
    articol->nrProduse = nouNrProduse;
    free(articol->preturi);
    articol->preturi = (float*)malloc(articol->nrProduse * sizeof(float));
    for (int i = 0; i < articol->nrProduse; i++)
    {
        printf("Introduceti pretul produsului %d: ", i + 1);
        scanf("%f", &articol->preturi[i]);
    }
}

void afisare(struct Magazin articol)
{
    printf("ID produs: %d\n", articol.idProdus);
    printf("Denumire: %s\n", articol.denumireProdus);
    printf("Stoc: %d\n", articol.nrProduse);
    printf("Preturi:");
    for (int i = 0; i < articol.nrProduse; i++) 
    {
        printf(" %.2f", articol.preturi[i]);
    }
    printf("\n");
}
void main() 
{
    int size=6;
    struct Magazin* vector = creareVector(size);
    for (int i = 0; i < size; i++)
    {
        printf("Introduceti informatiile pentru categoria de produse %d\n", i + 1);
            vector[i] = citire();
    }
    printf("Afisarea primului vector:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Categorie Produs %d\n", i + 1);
        afisare(vector[i]);
    }
    int newsize = 0;
    struct Magazin* vectorconditie = copiere(vector, size, &newsize);
    for (int i = 0; i < newsize; i++)
    {
        printf("Categoria produsului %d\n", i + 1);
        afisare(vectorconditie[i]);
    }
    int size11 = 4;
    struct Magazin* vector11 = creareVector(size11);
    int size2 = 3;
    struct Magazin* vector2 = creareVector(size2);
    int newsizec=0;
    struct Magazin* vectorConcatenat = concatenare(vector11, size11, vector2, size2, &newsizec);

    printf("Afisarea vectorului concatenat:\n");
    for (int i = 0; i < newsizec; i++)
    {
        printf("Categoria produsului %d\n", i + 1);
        afisare(vectorConcatenat[i]);
    }
    free(vectorConcatenat);
    int size3 = 5;
    struct Magazin* vector3 = creareVector(size3);
    int newsize2 = 0;
    struct Magazin* vectorMutat = mutare(vector3, size3, &newsize2);
    if (vectorMutat != NULL) {
        printf("Afisarea produselor mutate:\n");
        for (int i = 0; i < newsize2; i++) {
            printf("Categorie Produs %d\n", i + 1);
            afisare(vectorMutat[i]);
        }
        free(vectorMutat);
    }
    for (int i = 0; i < newsize; i++)
        eliberareMemorie(&vector[i]);
    free(vector);
}
