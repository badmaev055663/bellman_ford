#include <random>
#include <ctime>
#include <climits>


const int min_weight = 10;    // минимально возможный вес ребра
const int max_weight = 1000;  // максимально возможный вес ребра


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

    int i = 0; // счетчик сгенерированных ребер
    while (i < m)
    {
        int u = vertex(generator); // случайная вершина 'u'
        int v = vertex(generator); // случайная вершина 'v'
        if (u != v)
        {
            int w = weight(generator); // присваиваем ребру из 'u' в 'v' случайный вес 'w'
            result[i] = { u, v, w };
            ++i;
        }
    }
    return result;
}


/* найти кратчайшие пути в графе из вершины 'source' до всех вершин
 * 'graph' - входной граф
 * 'n' - число вершин в нем
 * 'm' - число ребер
 * 'source' - вершина-источник
 */
int* bellman_ford(edge* graph, int n, int m, int source)
{
    int* dist = new int[n];

    // инициализация массива расстояний 'бесконечностями'
    for (int i = 0; i < n; ++i)
    {
        dist[i] = INT_MAX;
    }
    dist[source] = 0; // расстояние от источника до себя равно 0

    // итерации до тех пор, пока в массиве расстояний происходят изменения 
    for (;;)
    {
        bool changed = false; // отслеживать изменения в графе
        for (int j = 0; j < m; ++j)
        {
            int u = graph[j].u;
            int v = graph[j].v;
            int w = graph[j].w;

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w; // релаксация ребра
                changed = true; // произошла релаксация
            }
        }
        if (changed == false) break;
    }
    return dist;
}

// провести тест 'k' раз со случайными графами с 'n' вершинами и 'm' ребрами
// выводит среднее время за 'k' испытаний
void test(int n, int m, int k)
{
    double mean = 0.0; // среднее времени выполнения
  
    for (int i = 0; i < k; ++i)
    {
        edge* graph = generate(n, m);
        int source = rand() % n; // случайная вершина становится источником

        clock_t start = clock();
        int* res = bellman_ford(graph, n, m, source);
        clock_t end = clock();
        clock_t delta_time = end - start;

        mean += delta_time;   

        delete[] graph;
        delete[] res;
    }
    mean /= k; // подсчет среднего 
    printf("mean time in milliseconds: %.1lf\n", mean);
}


int main()
{
    int n = 10000;   // количество вершин
    int m = 1000000;  // количество ребер 
    int k = 20;      // число испытаний при фиксированном размере входа

    test(n, m, k);         // начальный тест
    test(n * 2, m, k);     // тест с удвоенным количеством вершин 
    test(n, m * 2, k);     // тест с удвоенным количеством ребер
    test(n * 2, m * 2, k); // тест с удвоенным количеством и вершин и ребер
    return 0;
}