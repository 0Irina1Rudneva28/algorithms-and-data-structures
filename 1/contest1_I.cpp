/*
Трио Рон, Гарри и Гермиона попало в очередную западню. Для открытия двери им нужно осветить все  N приемников, 
стоящих в ряд. При этом заклятие «Люмос» способно покрыть светом отрезок длины ℓ. Хотя силы данной троицы и велики,
они не могут поддерживать одновременно более k активных заклинаний «Люмос».Найдите минимальное ℓ, чтобы трио могло 
выбраться.
  Формат ввода
На первой строке n (1≤n≤10^5) и k (1≤k≤n).На второй n чисел xi (∣∣xi∣∣≤10^9) — координаты приемников.

  Формат вывода
Минимальное такое ℓ, что точки можно покрыть k отрезками длины ℓ.
  Пример
Ввод	
6 2
1 2 3 9 8 7
Вывод
2
*/


#include <algorithm>
#include <iostream>

bool F(const long long array[], int n, int k, long long length) {
  long long id = -10000000001;
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (id < array[i]) {
      id = array[i] + length;
      count += 1;
    }
  }
  return (count <= k);
}

long long arr[100005];
int n, k;

int main() {
  std::cin >> n >> k;
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  std::sort(std::begin(arr), std::begin(arr) + n);
  long long l, r;
  l = -1;
  r = 10000000002;
  while (r - l > 1) {
    long long middle = (l + r) / 2;
    F(arr, n, k, middle) ? r = middle : l = middle;
  }
  std::cout << r;
}
