/*
Очередная игра в квиддич. Когтевранцы выбирают, кто будет представлять их факультет на столь важном событии. Всего есть 
N кандидатов, у каждого метла летает с максимальной скоростью ai. В силу определенных правил формирования команды,
можно выбрать обладателей метел с номерами  1,2,…,l,r,r+1,…,N. Когтевранцы уверены, что скорость команды определяется 
как скорость самой медленной метлы в команде.
  Формат ввода
В первой строке идет число N(1≤N≤10^5) — число кандидатов.Во второй строке идут N чисел ai(−10^9≤ai≤10^9)
 — скорости метел (не спрашивайте, что такое отрицательная скорость, вы же всего лишь маглы, вам не понять).
Далее на отдельной строке идет число Q(1≤Q≤10^6) — число запросов скорости команды от капитана.Вход завершается 
Q строками по два числа li,ri(1≤li≤ri≤N) — границы i-го запроса.
  Формат вывода
Выведите Q строк — ответы на запросы.
  Пример
Ввод
5
5 1 4 2 3
6
1 5
1 4
2 4
3 3
3 5
1 3

Вывод
3
2
1
1
1
2
*/

#include <algorithm>
#include <iostream>

int long long a[100000];
std::pair<int long long, int long long> min_raw[100000];

void PreCalc(const int long long kNum) {
  int long long m_speed = 10000000000;
  for (int long long i = 0; i < kNum; ++i) {
    if (a[i] < m_speed) {
      m_speed = a[i];
    }
    min_raw[i].first = m_speed;
  }
  m_speed = 10000000000;
  for (int long long i = kNum - 1; i >= 0; --i) {
    if (a[i] < m_speed) {
      m_speed = a[i];
    }
    min_raw[i].second = m_speed;
  }
}
int long long Query(const int long long kLeft, const int long long kRight) {
  int long long m_speed =
      std::min(min_raw[kLeft].first, min_raw[kRight].second);
  return m_speed;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int long long num_of;
  std::cin >> num_of;
  for (int i = 0; i < num_of; ++i) {
    std::cin >> a[i];
  }
  PreCalc(num_of);
  int num_of_query;
  std::cin >> num_of_query;
  int long long left, right;
  for (int i = 0; i < num_of_query; ++i) {
    std::cin >> left >> right;
    std::cout << Query(--left, --right) << '\n';
  }
  return 0;
}
