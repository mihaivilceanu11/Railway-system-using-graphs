#include "cost_minim.h"

int minDistance(int dist[], int sps[], int V)
{
   int v, min = inf, min_index;
         for ( v = 0; v < V; v++)
            if (sps[v] == 0 && dist[v] <= min) 
               {
                   min = dist[v];
                   min_index = v;
               }
   return min_index;
} 

void dijkstra(Graph *g, int s, int dist[])
{
   int i, j, u;
   int sps[g->V]; 
 
      for ( i = 0; i < g->V; i++)
         { 
            dist[i] = inf; 
            sps[i] = 0; 
         }
 
 dist[s] = 0; 
 
         for (j = 0; j < g->V-1; j++)
         {
            u = minDistance(dist, sps, g->V); 
            sps[u] = 1;
 
         for (i = 0; i < g->V; i++)
            {
                if (sps[i] == 0 && g->a[u][i]!=0 && 
                   dist[u] != inf && dist[u]+g->a[u][i] < dist[i])
                dist[i] = dist[u] + g->a[u][i];
            }
         }
 
        
} 
