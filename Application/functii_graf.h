#ifndef FUNCTII_GRAF_H
#define FUNCTII_GRAF_H

int inf = __INT_MAX__;

typedef struct Graph
{
    int V;
    int E;
    int **a;
}Graph;

int cautare(char *a[], int n, char b[]);

int get_index(char *b[], int n, char city[]);

Graph *graph_create(int n);

void adaugare_graf_orientat(Graph *graph, int n, char *orase[], char oras1[], char oras2[]);

void adaugare_graf_neorientat(Graph *graph, int n, char *orase[], char oras1[], char oras2[]);

#endif