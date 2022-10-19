#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define SUCCESS 0
#define FILE_ERROR 1
#define MATCH_CONTENT_ERROR 2

typedef struct {
    char name[20];
    int date;
    float price;
    float discount;
} movie;

typedef struct {
    char cinemaName[20];
    movie moviesList[5];
} cinema;

typedef enum _ACTION {
    EXIT = 1,
    DISPLAY_FILMS,
    DISPLAY_CINEMA,
    FIND_MOVIE,
} ACTION;

void displayFilmsInCinema(cinema* cinemaList, const char* cinemaName, int cinemaCount, int moviesCount);
void displayCinema(cinema* cinemaList, int cinemaCount);
void findClosestDateMovie(cinema* cinemaList, const char * movieName, int targetDate, int cinemaCount, int moviesCount);

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

    
    ACTION act;
    char cinemaName[20];
    char movieName[20];
    int date;
    do
    {
        putchar('\n');
        printf("Enter action:\n1. Exit\n2. Display films from cinema\n3. Display all cinema\n4. Find film by name closest to date\nYour choice: ");
        scanf_s("%d", &act);
        putchar('\n');

        switch (act)
        {
        case EXIT:
            return SUCCESS;
        case DISPLAY_FILMS:
            printf("Enter cinema name: ");
            scanf_s("%s", cinemaName, 20);
            displayFilmsInCinema(cinemaList, cinemaName, C, M);
            break;
        case DISPLAY_CINEMA:
            displayCinema(cinemaList, C);
            break;
        case FIND_MOVIE:
            printf("Enter movie name: ");
            scanf_s("%s", movieName, 20);
            printf("Enter target date (0 - 100): ");
            scanf_s("%d", &date);
            findClosestDateMovie(cinemaList, movieName, date, C, M);
            break;
        default:
            printf("Wrong action number\n");
            break;
        }
    } while (true);
}


void displayFilmsInCinema(cinema* cinemaList, const char* cinemaName, int cinemaCount, int moviesCount)
{
    for (int i = 0; i < cinemaCount; i++) {
        if (strcmp(cinemaList[i].cinemaName, cinemaName) == 0) {
            printf("Films in %s:\n", cinemaName);
            for (int j = 0; j < moviesCount; j++) {
                printf("%d. \"%s\"\n", j + 1, cinemaList[i].moviesList[j].name);
            }
            return;
        }
    }
    
    printf("Cinema with name \"%s\" is not found in the collection\n", cinemaName);
}

void displayCinema(cinema* cinemaList, int cinemaCount)
{
    printf("All cinema: \n");
    for (int i = 0; i < cinemaCount; i++) {
        printf("%d. %s\n", i + 1, cinemaList[i].cinemaName);
    }
}

void findClosestDateMovie(cinema* cinemaList, const char* movieName, int targetDate, int cinemaCount, int moviesCount)
{
    int cinemaNumber;
    int closestDistance = 100;
    bool movieExists = false;

    for (int i = 0; i < cinemaCount; i++) {
        for (int j = 0; j < moviesCount; j++) {
            if (strcmp(cinemaList[i].moviesList[j].name, movieName) == 0) {
                int distance = abs(cinemaList[i].moviesList[j].date - targetDate);
                if (distance < closestDistance) {
                    closestDistance = distance;
                    cinemaNumber = i;

                    if (!movieExists) movieExists = true;
                }
            }
        }
    }

    if (!movieExists) {
        printf("Movie with name \"%s\" is not found in any cinema\n", movieName);
    }
    else {
        printf("Closest \"%s\" to date \"%d\" is in \"%s\"\n", movieName, targetDate, cinemaList[cinemaNumber].cinemaName);
    }
}