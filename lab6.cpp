#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stack>

using namespace std;

const int INF = numeric_limits<int>::max();

int tsp(vector<vector<int>>& graph, int start, vector<int>& path) {
    int n = graph.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1 << start][start] = 0;

    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; ++v) {
                if (!(mask & (1 << v)) && graph[u][v] && dp[mask][u] != INF) {
                    dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + graph[u][v]);
                }
            }
        }
    }

    int min_cost = INF;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (i != start && graph[i][start]) {
            if (min_cost > dp[(1 << n) - 1][i] + graph[i][start]) {
                min_cost = dp[(1 << n) - 1][i] + graph[i][start];
                last = i;
            }
        }
    }

    int mask = (1 << n) - 1;
    path.push_back(last);
    while (mask != (1 << start)) {
        int prev = last;
        last = -1;
        for (int i = 0; i < n; ++i) {
            if (i != start && (mask & (1 << i)) && graph[i][prev] && dp[mask][prev] == dp[mask ^ (1 << prev)][i] + graph[i][prev]) {
                last = i;
                break;
            }
        }
        mask ^= (1 << prev);
        path.push_back(last);
    }
    path.push_back(start);

    reverse(path.begin(), path.end());
    return min_cost;
}

int main() {
    setlocale(LC_ALL, "Rus");
    int num_cities;
    cout << "Введите количество городов: ";
    cin >> num_cities;

    vector<vector<int>> graph(num_cities, vector<int>(num_cities));

    cout << "Введите расстояния между городами (0 - если маршрут внутри города):" << endl;
    for (int i = 0; i < num_cities; ++i) {
        for (int j = 0; j < num_cities; ++j) {
            cout << "Расстояние от города " << i << " к городу " << j << ": ";
            cin >> graph[i][j];

            while (graph[i][j] < 0) {
                cout << "Расстояние не может быть отрицательным. Введите положительное значение: ";
                cin >> graph[i][j];
            }
        }
    }

    int optimal_start = 0; // начальный город по умолчанию
    vector<int> path;
    int min_cost = tsp(graph, optimal_start, path);

    cout << "Оптимальный начальный город: " << optimal_start << endl;
    cout << "Минимальная стоимость маршрута: " << min_cost << endl;
   /* cout << "Маршрут: ";
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << " ";
    }
    cout << endl;*/

    return 0;
}