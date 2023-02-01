/*
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 10^6. Отсортировать массив методом 
поразрядной сортировки LSD по байтам.

  Формат ввода
В первой строке вводится количество чисел в массиве N. Далее идут на N строках N чисел.
  Формат вывода
Выведите этот массив, отсортированный в порядке неубывания.
  Пример 1
Ввод	
3
4
1000000
7

Вывод
4
7
1000000
  Пример 2
Ввод	
5
9244894871689
9521193378807
1748929606960
1006499032553
3289527480072

Вывод
1006499032553
1748929606960
3289527480072
9244894871689
9521193378807
*/

#include <iostream>
#include <vector>

int GetByte(unsigned long long number, size_t n) {
  return number >> (sizeof(long long) * n) & 0xFF;
}

void CountSort(unsigned long long* data, size_t n, const size_t kByte) {
  size_t b = 256;
  std::vector<size_t> counters(b, 0);
  for (size_t i = 0; i < n; ++i) {
    ++counters[GetByte(data[i], kByte)];
  }
  for (size_t i = 1; i < b; ++i) {
    counters[i] += counters[i - 1];
  }
  unsigned long long* tmp = new unsigned long long[n];
  for (size_t i = n - 1;; --i) {
    tmp[--counters[GetByte(data[i], kByte)]] = data[i];
    if (i == 0) {
      break;
    }
  }
  for (size_t i = 0; i < n; ++i) {
    data[i] = tmp[i];
  }
  delete[] tmp;
}

void LSDSort(unsigned long long* arr, size_t n) {
  size_t total_bytes = sizeof(long long);
  for (size_t i_byte = 0; i_byte < total_bytes; ++i_byte) {
    CountSort(arr, n, i_byte);
  }
}

int main() {
  size_t n;
  std::cin >> n;
  unsigned long long* array = new unsigned long long[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  LSDSort(array, n);
  for (size_t i = 0; i < n; ++i) {
    std::cout << array[i] << '\n';
  }
  delete[] array;
  return 0;
}
