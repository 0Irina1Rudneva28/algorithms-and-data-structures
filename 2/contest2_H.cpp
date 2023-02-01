/*
Нужно с помощью быстрой сортировки отсортировать массив.
Запрещено инклудить algorithm!

  Формат ввода
В первой строке дано число N (1 ≤ N ≤ 10^5). Далее во втрой строке идет N чисел, каждое с новой строки.
Числа не превосходят по модулю 10^9.
  Формат вывода
Вывести отсортированный по неубыванию массив.
  Пример
Ввод	
5
5
2
3
1
4
Вывод
1 2 3 4 5 
*/

#include <iostream>
#include <vector>

int Partition(std::vector<long long>& vector, int lo, int hi) {
  int i = lo;
  int j = hi + 1;
  while (true) {
    while (vector[++i] < vector[lo]) {
      if (i == hi) {
        break;
      }
    }
    while (vector[--j] > vector[lo]) {
      if (j == lo) {
        break;
      }
    }
    if (i >= j) {
      break;
    }
    std::swap(vector[i], vector[j]);
  }
  std::swap(vector[lo], vector[j]);
  return j;
}

void QuickSort(std::vector<long long>& vector, int lo, int hi) {
  if (hi <= lo) {
    return;
  }
  int j = Partition(vector, lo, hi);
  QuickSort(vector, lo, j - 1);
  QuickSort(vector, j + 1, hi);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  long long x;
  std::vector<long long> arr;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    arr.push_back(x);
  }
  QuickSort(arr, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << ' ';
  }
  return 0;
}
