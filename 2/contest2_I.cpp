/*
Напишите программу, которая для заданного массива A=⟨a1,a2,…,an⟩ находит количество пар (i,j) таких, что i<j
 и ai>aj.Обратите внимание на то, что ответ может не влезать в int.

  Формат ввода
Первая строка входного файла содержит натуральное число n (1≤n≤100000) — количество элементов массива. 
Вторая строка содержит n попарно различных элементов массива A — целых неотрицательных чисел, не превосходящих 10^9.
  Формат вывода
В выходной файл выведите одно число — ответ на задачу.
  Пример 1
Ввод	
5
6 11 18 28 31
Вывод
0
  Пример 2
Ввод	
5
179 4 3 2 1
Вывод
10
*/

#include <iostream>
#include <vector>

std::vector<long long> arr;
void MergeSortLR(long long l, long long mid, long long r,
                 long long& cnt_invers) {
  std::vector<long long> l_arr;
  std::vector<long long> r_arr;
  int ind = l;
  int cnt1 = 0, cnt2 = 0;
  int a = mid + 1 - l;
  int b = r - mid;
  for (int i = 0; i < a; ++i) {
    l_arr.push_back(arr[l + i]);
  }
  for (int j = 0; j < b; ++j) {
    r_arr.push_back(arr[(mid + 1) + j]);
  }
  while ((a - cnt1 > 0) && (b - cnt2 > 0)) {
    if (r_arr[cnt2] - l_arr[cnt1] >= 0) {
      arr[ind++] = l_arr[cnt1++];
      cnt_invers += cnt2;
    } else {
      arr[ind++] = r_arr[cnt2++];
    }
  }
  while (b > cnt2) {
    arr[ind++] = r_arr[cnt2++];
  }
  while (a > cnt1) {
    cnt_invers += cnt2;
    arr[ind++] = l_arr[cnt1++];
  }
}

void MergeSort(long long l, long long r, long long& cnt_invers) {
  if (r - l <= 0) {
    return;
  }
  MergeSort(l, (l + r) / 2, cnt_invers);
  MergeSort((l + r) / 2 + 1, r, cnt_invers);
  MergeSortLR(l, (l + r) / 2, r, cnt_invers);
}

int main() {
  int n;
  long long cnt_invers = 0;
  long long x;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    arr.push_back(x);
  }
  MergeSort(0, --n, cnt_invers);
  std::cout << cnt_invers << "\n";
  return 0;
}
