/*
У тренеров покемонов огромное множество самых разных зверьков. Хэш Кетчум и Мисти решили посмотреть, а какие у них общие?
Для удобства все покемоны пронумерованы, найдите общих покемонов с учетом кратности.

  Формат ввода
В первой строке дано число N(1≤N≤3⋅10^6)— число покемонов у Хэша. На следующей строке идут N чисел (1≤ai≤10^9)
 — номера покемонов, которые есть у Хэша.
В третьей и четвертой строке в том же формате и с теми же ограничениями описана коллекция Мисти.

  Формат вывода
Выведите пересечение коллекций в формате как в входном файле. Порядок не важен.
  Пример 1
Ввод	
5
1 2 1 3 10
3
1 1 11
Вывод
2
1 1 
  Пример 2
Ввод	
5
1 1 2 2 1
5
2 2 1 1 2
Вывод
4
2 2 1 1 
*/

#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long long n_first;
  std::cin >> n_first;
  std::unordered_map<long long, long long> arr;
  for (long long i = 0; i < n_first; i++) {
    long long x;
    std::cin >> x;
    (arr.find(x) != arr.end()) ? arr[x] += 1 : arr[x] = 1;
  }
  long long n_second;
  std::cin >> n_second;
  std::vector<long long> ans;
  for (long long i = 0; i < n_second; i++) {
    long long x;
    std::cin >> x;
    if (arr.find(x) != arr.end()) {
      if (arr[x] > 0) {
        arr[x] -= 1;
        ans.push_back(x);
      }
    }
  }
  std::cout << ans.size() << '\n';
  for (size_t i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << " ";
  }
}
