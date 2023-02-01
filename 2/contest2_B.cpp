/*
В этой задаче вам необходимо найти k-ую порядковую статистику (k-ое по неубыванию) числовой последовательности A, 
элементы которой задаются особым образом

  Формат ввода
Вам даны n, k, A0, A1 (1 ≤ k ≤ n ≤ 107, 0 ≤ Ai < 107 + 4321) — количество чисел в числовой последовательности, 
k из условия и первые два числа числовой последовательности.

  Формат вывода
Выведите k-ую порядковую статистику.

  Пример 1
Ввод
2 2 100 1000
Вывод
1000

  Пример 2
Ввод	
10 5 1 2
Вывод
321287
*/

#include <iostream>

long long Partition(long long* arr, long long l, long long r) {
  long long p = arr[r], i = l;
  for (long long j = l; j <= r - 1; j++) {
    if (p >= arr[j]) {
      std::swap(arr[i++], arr[j]);
    }
  }
  std::swap(arr[i], arr[r]);
  return i;
}

int KStat(long long* arr, long long l, long long r, long long k) {
  long long p = Partition(arr, l, r);
  if (l < p - k + 1) {
    return KStat(arr, l, p - 1, k);
  }
  if (l > p - k + 1) {
    return KStat(arr, p + 1, r, k - p + l - 1);
  }
  return arr[p];
}

int main() {
  long long n, k, a0, a1;
  std::cin >> n >> k >> a0 >> a1;
  long long* arr = new long long[n];
  arr[0] = a0;
  arr[1] = a1;
  for (long long i = 2; i < n; ++i) {
    arr[i] = (arr[i - 1] * 123 + arr[i - 2] * 45) % 10004321;
  }
  std::cout << KStat(arr, 0, n - 1, k) << std::endl;
  delete[] arr;
  return 0;
}
