#include <random>
#include <ctime>


const int min_weight = 10;
const int max_weight = 1000;
const int infinity = 1000000000;



// ребро из 'u' в 'v' с весом 'w'
struct edge {
    int u, v, w;
};


// сгенерировать взвешенный орграф с 'n' вершинами и 'm' ребрами
edge* generate(int n, int m)
{
    edge* result = new edge[m];

    std::default_random_engine generator(time(NULL)); // инициализация зерна для генератора случайных чисел

    // равномерное распределение целых чисел
    std::uniform_int_distribution<int> vertex(0, n - 1);
    std::uniform_int_distribution<int> weight(min_weight, max_weight);

    int i = 0;
    while (i < m)
    {
        int u = vertex(generator);
        int v = vertex(generator);
        if (u != v)
        {
            int w = weight(generator);
            result[i] = { u, v, w };
            ++i;
        }
    }
    return result;
}


// найти кратчайшие пути в графе из вершины 'source' до всех вершин
int* bellman_ford(edge* graph, int n, int m, int source)
{
    int* dist = new int[n];

    // инициализация массива расстояний
    for (int i = 0; i < n; ++i)
    {
        dist[i] = infinity;
    }
    dist[source] = 0;

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int u = graph[j].u;
            int v = graph[j].v;
            int w = graph[j].w;

            if (dist[v] > dist[u] + w)
                dist[v] = dist[u] + w; // релаксация ребра
        }
    }
    return dist;
}


int main()
{

    int n = 1000, m = 100000, source = 0;
    int k = 10; // число экспериментов
    for (int i = 0; i < k; ++i)
    {      
        edge* graph = generate(n, m);

        clock_t start = clock();
        int* res = bellman_ford(graph, n, m, source);
        clock_t end = clock();
    
        printf("time in milliseconds: %d\n", end - start);
        delete[] graph;
        delete[] res;
    }
    

    return 0;
}