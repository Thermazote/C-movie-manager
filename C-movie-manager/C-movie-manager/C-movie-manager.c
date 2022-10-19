#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SUCCESS 0
#define FILE_ERROR 1
#define MATCH_CONTENT_ERROR 2


typedef struct _movie {
    char name[20];
    int date;
    float price;
    float discount;
} movie;

typedef struct _cinema {
    char cinemaName[20];
    movie moviesList[5];
} cinema;


int main()
{
    int C;
    int M;
    printf("Enter number of cinema: ");
    scanf_s("%d", &C);
    printf("Enter number of movies in each cinema: ");
    scanf_s("%d", &M);

    FILE* f;
    fopen_s(&f, "moviesList.txt", "r");

    if (f == NULL) {
        return FILE_ERROR;
    }

    cinema cinemaList[5];

    int cinemaNumber = 0;
    while (!feof(f) && cinemaNumber < C) {
        // read cinema name:
        if (fscanf_s(f, "%s", cinemaList[cinemaNumber].cinemaName, 20) != 1) return MATCH_CONTENT_ERROR;

        // read movies in cinema
        int movieNumber = 0;
        while (!feof(f) && movieNumber < M) {
            char* name = cinemaList[cinemaNumber].moviesList[movieNumber].name;
            int* date = &(cinemaList[cinemaNumber].moviesList[movieNumber].date);
            float* price = &(cinemaList[cinemaNumber].moviesList[movieNumber].price);
            float* discount = &(cinemaList[cinemaNumber].moviesList[movieNumber].discount);
            if (fscanf_s(f, "%s %d %f %f", name, 20, date, price, discount) != 4) return MATCH_CONTENT_ERROR;

            movieNumber++;
        }

        cinemaNumber++;
    }

    printf("Cinema name: %s\nFirst movie name: %s\b", cinemaList[0].cinemaName, cinemaList[0].moviesList[0].name);
    return SUCCESS;
}
