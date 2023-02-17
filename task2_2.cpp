/*
Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду. 
Каждый вышележащий слой пирамиды должен быть не больше нижележащего.

На вход подается количество кубиков N.

Вывести число различных пирамид из N кубиков.

Ввод:       Вывод: 
3           3

5           7

7           15
*/

#include <iostream>
#include <vector> 

long long pyramid_count(long long n, long long m, std::vector<std::vector<long long>>& DP) {
    if (n < 0 || m <= 0) return 0;
    if (DP[n][m] != 0) return DP[n][m];
    DP[n][m] = pyramid_count(n - m, m, DP) + pyramid_count(n, m - 1, DP);
    return DP[n][m];
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::vector<std::vector<long long>> DP(n + 1, std::vector<long long>(n + 1));
    for (long long i = 1; i < n + 1; i++) {
        DP[0][i] = 1;
        DP[1][i] = 1;
        DP[i][1] = 1;
    } 
    std::cout << pyramid_count(n, n, DP) << '\n';
    return 0;
}


