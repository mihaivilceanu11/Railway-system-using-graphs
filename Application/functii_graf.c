#include "functii_graf.h"

int cautare(char *a[], int n, char b[])
{
    int i;
    for(i = 0; i < n; i++)
        if(strcmp(a[i], b)==0)
            return 1;
        
        return 0;
}

int get_index(char *b[], int n, char city[])
{
    int i;
    for(i = 0; i < n; i++)
        if(strcmp(b[i], city) == 0)
            return i;
}

Graph *graph_create(int n)
{
    Graph *graph = malloc(sizeof(Graph));

    graph->V = n;
    graph->E = 0;

    graph->a = malloc(graph->V*sizeof(int*));

    for(int i = 0; i < n; i++)
        graph->a[i] = calloc(graph->V, sizeof(int));

        return graph;
}

void adaugare_graf_orientat(Graph *graph, int n, char *orase[], char oras1[], char oras2[])
{
    int l, c;

    l = get_index(orase, n, oras2);
    c = get_index(orase, n, oras1);

    if(graph->a[l][c] == 0)
    {
        graph->a[l][c] = 1;
        graph->E = graph->E + 1;
    }
}

void adaugare_graf_neorientat(Graph *graph, int n, char *orase[], char oras1[], char oras2[])
{
        int l, c;

        l = get_index(orase, n, oras2);
        c = get_index(orase, n, oras1);

        if(graph->a[l][c] == 0)
        {
            graph->a[l][c] = 1;
            graph->a[c][l] = 1;
            graph->E = graph->E + 2;
        }

}
