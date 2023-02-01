/*
Дана длинная последовательность целых чисел длины n. Требуется вывести в отсортированном виде её наименьшие k элементов.
Чтобы не пришлось считывать большую последовательность, её элементы задаются формулой. А именно, во входных данных 
содержатся числа a0,x,y. Тогда ai=(x⋅ai−1+y) (mod 2^30). Искомая последовательность — a1,a2,…,an.

  Формат ввода
В первой строке записаны n и k(1≤n≤10^7,1≤k≤1000).В следующей строке через пробел заданы значения a0,x,y(0≤a0,x,y<2^30).

  Формат вывода
Выведите k наименьших элементов последовательности в отсортированном виде.
  Пример
Ввод	
3 2
3 1 2
Вывод
5 7 

*/

#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
  unsigned long long sz_ = 0;
  void Exchange(int u, int v);
  void SiftUp(unsigned long long v);
  void SiftDown(unsigned long long v);
  std::vector<long long> arr_;
  std::vector<unsigned long> ptrs_;

 public:
  unsigned long long k = 0;
  void Insert(long long x);
  long long GetMin();
  long long ExtractMin();
};

void Heap::Exchange(int u, int v) {
  std::swap(arr_[v], arr_[u]);
  std::swap(ptrs_[v], ptrs_[u]);
}

void Heap::SiftUp(unsigned long long v) {
  int p = (v - 1) / 2;
  while (v != 0 && arr_[v] < arr_[p]) {
    Exchange(v, p);
    SiftUp(p);
  }
}

void Heap::SiftDown(unsigned long long v) {
  unsigned long long u = 2 * v + 1;
  if (2 * v + 2 < sz_ && arr_[2 * v + 2] < arr_[u]) {
    u = 2 * v + 2;
  }
  while (u < sz_ && arr_[u] < arr_[v]) {
    Exchange(u, v);
    SiftDown(u);
  }
}

void Heap::Insert(long long x) {
  arr_.push_back(x);
  ptrs_.push_back(k);
  SiftUp(sz_++);
}

long long Heap::GetMin() { return arr_[0]; }

long long Heap::ExtractMin() {
  long long min = arr_[0];
  Exchange(0, --sz_);
  ptrs_.pop_back();
  arr_.pop_back();
  SiftDown(0);
  return min;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Heap heap;
  unsigned long n, k;
  long long a, x, y;
  std::vector<long long> sort_arr;
  std::cin >> n >> k >> a >> x >> y;
  for (unsigned long i = 0; i < k; ++i) {
    a = (x * a + y + 1073741824) % 1073741824;
    heap.Insert(-a);
  }
  for (unsigned long i = k; i < n; i++) {
    a = (x * a + y + 1073741824) % 1073741824;
    if (-a > heap.GetMin()) {
      heap.ExtractMin();
      heap.Insert(-a);
    }
  }
  for (unsigned long i = 0; i < k; i++) {
    sort_arr.push_back(-heap.ExtractMin());
  }
  std::sort(sort_arr.begin(), sort_arr.end());
  for (unsigned long i = 0; i < k; i++) {
    std::cout << sort_arr[i] << " ";
  }
  std::cout << "\n";
  return 0;
}
