#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii_graf.c"
#include "functii_graf.h"
#include "cost_minim.c"
#include "cost_minim.h"

int main()
{
    int m, i, j, n, costuri[520][520];
    int total = 0, Max, Min;
    int distanta1, distanta2, l, c, dist_max;;
    int distanta[520];
    char fisiere[101][10], *orase[521], o[50];
    char *aux1, *aux2, *aux_d1, *aux_d2, city1[50], city2[50], c1[50], c2[50];
    char oras1[50], oras2[50];
    char w[10], *o1;
    FILE *f;
    Graph *graf_orientat, *graf_neorientat, *graf_costuri;
    
    

      n = 0; //contorul numarului de statii unice(noduri din graf)
      m = 0; // contorul numarului de fisiere

//Citirea numelor fisierelor    
  
    f = fopen("_all_files.txt", "r+");

        while(fscanf(f, "%s", w) != EOF)
           { 
               strcpy(fisiere[m], w);
                m++;
           }

    fclose(f);

//Citirea oraselor din primul fisier 

    f = fopen(fisiere[0], "r+");
        while(fgets(o, 50, f))
        {
            o1 = strtok(o, ",");
            orase[n] = malloc(strlen(o1) + 1);
            strcpy(orase[n], o1); 
            n++;
        }
    fclose(f);


//Citirea celorlalte orase cu verificarea unicitatii 

for(i = 1; i < m; i++)
      {
          f = fopen(fisiere[i], "r+");
            while(fgets(o, 50, f))
            {
                o1 = strtok(o, ",");
                if(cautare(orase, n, o1) == 0)
                {
                    orase[n] = malloc(strlen(o) + 1);
                    strcpy(orase[n], o1);
                    n++;
                }
            }
        fclose(f);
       
      }

//Crearea grafului orientat si neorientat

    graf_orientat = graph_create(n);
    graf_neorientat = graph_create(n);

    for(i = 0; i < m; i++)
      {
          f = fopen(fisiere[i], "r+");
            fgets(c1, 50, f);
            aux1 = strtok(c1, ",");
            strcpy(city1, aux1);
            while(fgets(c2, 50, f))
            {
               aux2 = strtok(c2, ",");
               strcpy(city2, aux2); 
               adaugare_graf_neorientat(graf_neorientat, n, orase, city1, city2); 
               adaugare_graf_orientat(graf_orientat, n, orase, city1, city2);
               strcpy(city1, city2);
            }
        fclose(f);
       
      }

//Crearea grafului de costuri

    graf_costuri = graph_create(n);

     for(i = 0; i < m; i++)
      {
          f = fopen(fisiere[i], "r+");
            fgets(oras1, 50, f);
            aux1 = strtok(oras1, ",");
            strcpy(city1, aux1);
            while(fgets(oras2, 50, f))
            {
               aux2 = strtok(oras2, ",");
               strcpy(city2, aux2); 
               adaugare_graf_neorientat(graf_costuri, n, orase, city1, city2); 
               strcpy(city1, city2);
            }
        fclose(f);
       
      }

        for(i = 0; i < 520; i++)
            for(j = 0; j < 520; j++)
                costuri[i][j] = 0;
        
     for(i = 0; i < m; i++)
      {
          f = fopen(fisiere[i], "r+");
            fgets(oras1, 50, f);
            aux1 = strtok(oras1, ",");
            aux_d1 = strtok(NULL, " ,");
            distanta1 = atoi(aux_d1);
            strcpy(city1, aux1);
        while(fgets(oras2, 50, f))
        {
             aux2 = strtok(oras2, ",");
             aux_d2 = strtok(NULL, " ,");
             distanta2 = atoi(aux_d2);
             strcpy(city2, aux2);

              l = get_index(orase, n, city2);
              c = get_index(orase, n, city1);

              if(costuri[l][c] == 0)
            {
                  costuri[l][c] = distanta2 - distanta1;
                  costuri[c][l] = distanta2 - distanta1;
             }
            strcpy(city1, city2);
            distanta1 = distanta2;
        }
      }

   for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(costuri[i][j] == 0)
                costuri[i][j] = inf;

    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i == j)
                costuri[i][j] = 0;
        
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            graf_costuri->a[i][j] = costuri[i][j];

//Distanta minima si distanta maxima intre doua statii consecutive

Min = inf;
        for(i = 0; i < graf_costuri->V; i++)
            for(j = 0; j < graf_costuri->V; j++)
                if(i != j && graf_costuri->a[i][j] != inf)
                        if(graf_costuri->a[i][j] < Min)
                            Min = graf_costuri->a[i][j];
    
        for(i = 0; i < graf_costuri->V; i++)
            for(j = 0; j < graf_costuri->V; j++)
                if(graf_costuri->a[i][j] == Min)
                    {
                        f = fopen("min.txt", "w+");
                        fprintf(f, "Distanta minima este de %d km intre %s si %s.", Min, orase[i], orase[j]);
                        fclose(f);
                        break;
                    }

Max = 0;
    for(i = 0; i < graf_costuri->V; i++)
            for(j = 0; j < graf_costuri->V; j++)
                if(i != j && graf_costuri->a[i][j] != inf)
                        if(graf_costuri->a[i][j] > Max)
                            Max = graf_costuri->a[i][j];

    for(i = 0; i < graf_costuri->V; i++)
            for(j = 0; j < graf_costuri->V; j++)
                if(graf_costuri->a[i][j] == Max)
                    {
                        f = fopen("max.txt", "w+");
                        fprintf(f, "Distanta maxima este de %d km intre %s si %s.", Max, orase[i], orase[j]);
                        fclose(f);
                        break;
                    }

//Totalul

total = 0;

for(i = 0; i < graf_costuri->V; i++) 
    for(j = i + 1; j < graf_costuri->V; j++)
        if(graf_costuri->a[i][j] != inf)
            total = total + graf_costuri->a[i][j];

    f = fopen("total.txt", "w+");
        fprintf(f, "In total sunt %d km de cale ferata.", total);
    fclose(f);

//Drumul de cost minim intre Bucuresti si Craiova

    for(i = 0; i < graf_costuri->V; i++) 
        for(j = 0; j < graf_costuri->V; j++)
            if(graf_costuri->a[i][j] == inf)
                graf_costuri->a[i][j] = 0;

    dijkstra(graf_costuri, 0, distanta);

    int index_Craiova = get_index(orase, n, "Craiova");
    f = fopen("ruta.txt", "w+");
    fprintf(f, "Drumul de cost minim intre Bucuresti si Craiova este de %d km.", distanta[index_Craiova]);
    fclose(f);

//Statia cea mai indepartata de Bucuresti

int Max_dist = distanta[0];

    for(i = 0; i < n; i++)
        if(distanta[i] > Max_dist)
            Max_dist = distanta[i];
    
    for(i = 0; i < n; i++)
        if(distanta[i] == Max_dist)
             {
                 f = fopen("departe.txt", "w+");
                 fprintf(f, "Statia cea mai indepartata de Bucuresti este %s, la %d km.", orase[i], Max_dist);
                 fclose(f);
             }

//Distanta maxima intre doua statii pe drumul de cost minim  

    int **distante_totale = (int **)malloc(n * sizeof(int *)); 

        for (i = 0; i < n; i++) 
            distante_totale[i] = (int *)malloc(n * sizeof(int)); 

        for(i = 0; i < n; i++)
            dijkstra(graf_costuri, i, distante_totale[i]);

        dist_max = distante_totale[0][0];
        for(i = 0; i < n; i++) 
           for(j = 0; j < n; j++)
                if(distante_totale[i][j] > dist_max)
                        dist_max = distante_totale[i][j];
            
 for(i = 0; i < n; i++) 
     for(j = 0; j < n; j++)
        if(distante_totale[i][j] == dist_max)
          {
             f = fopen("drum_lung.txt", "w+");
             fprintf(f, "%s si %s se afla la distanta maxima de %d km.", orase[i], orase[j], dist_max);
             fclose(f);
             break;
          }


f = fopen("output.txt", "w+");
fprintf(f, "%d %d\n", graf_orientat->V, graf_orientat->E);
for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
        if(graf_orientat->a[i][j] != 0)
            fprintf(f, "%d %d %d\n", i, j, graf_costuri->a[i][j]);
    fclose(f);
return 0;
}