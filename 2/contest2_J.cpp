/*
Вам дан массив a[] из N целых чисел. Надо для каждого элемента найти число элементов справа строго меньших данного.

  Формат ввода
На первой строке идет число N (1 ≤ N ≤ 10^5), на второй строке идет массив a[], элементы которого не превосходят по 
модулю 10^9.

  Формат вывода
Выведите массив b[], где b[i] равно числу элементов с большим, чем i, индексом и значением строго меньшим, чем a[i].

  Пример 1
Ввод	
4
5 2 6 1
Вывод
2 1 1 0 
  Пример 2
Ввод	
1
-1
Вывод
0 
  Пример 3
Ввод	
2
-1 -1
Вывод
0 0
*/

#include <iostream>
#include <vector>

std::vector<int> arr;
void MergeSort(int l, int r, std::vector<int>& merge_arr, std::vector<int>& ind,
               std::vector<int>& res) {
  if (r - l > 0) {
    int m = (r + l) / 2;
    int i = l;
    int j = m + 1;
    int k = i;
    int cnt = 0;
    MergeSort(l, m, merge_arr, ind, res);
    MergeSort(m + 1, r, merge_arr, ind, res);
    while (m - i + 1 > 0) {
      while (r - j + 1 > 0 && arr[ind[i]] > arr[ind[j]]) {
        merge_arr[k++] = ind[j++];
        ++cnt;
      }
      res[ind[i]] += cnt;
      merge_arr[k++] = ind[i++];
    }
    while (r - j >= 0) {
      merge_arr[k++] = ind[j++];
    }
    for (int i = l; i <= r; ++i) {
      ind[i] = merge_arr[i];
    }
  }
}

std::vector<int> CntLSmaller() {
  int size = arr.size();
  std::vector<int> res(size, 0);
  std::vector<int> merge_arr(size, 0);
  std::vector<int> ind;
  for (int i = 0; i < size; ++i) {
    ind.push_back(i);
  }
  MergeSort(0, --size, merge_arr, ind, res);
  return res;
}

int main() {
  int n, x;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    arr.push_back(x);
  }
  std::vector<int> ans = CntLSmaller();
  for (int i = 0; i < n; ++i) {
    std::cout << ans[i] << " ";
  }
}
