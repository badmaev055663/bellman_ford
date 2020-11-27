#include <random>
#include <ctime>

const int min_weight = 10;
const int max_weight = 1000;
const int infinity = 100000000;

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

    edge graph[4];
    graph[0] = { 0, 1, 5 };
    graph[1] = { 0, 2, 10 };
    graph[2] = { 1, 2, 3 };
    graph[3] = { 1, 0, 7 };
    int* res = bellman_ford(graph, 3, 4, 1);
    for (int i = 0; i < 3; ++i)
    {
        printf("from vertex 1 to vertex %d: %d\n", i, res[i]);
    }
    delete[] res;
    return 0;
}