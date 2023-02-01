/*
Реализуйте двоичную кучу.
Обработайте запросы следующих видов:
insert x — вставить целое число  x в кучу;
getMin — вывести значение минимального элемента в куче (гарантируется, что к этому моменту куча не пуста);
extractMin — удалить минимальный элемент из кучи, выводить его не нужно (гарантируется, что к этому моменту куча не пуста);
decreaseKey i Δ — уменьшить число, вставленное на i-м запросе, на целое число Δ≥0
 (гарантируется, что i-й запрос был осуществлён ранее, являлся запросом добавления, а добавленное на этом шаге 
 число всё ещё лежит в куче). Обратите внимание, число i равно номеру запроса среди всех запросов, а не только 
 среди запросов добавления!
Можете считать, что в любой момент времени все числа, хранящиеся в куче, попарно различны, а их количество не превышает 
10^5.
  Формат ввода
В первой строке содержится число q(1≤q≤10^6), означающее число запросов.В следующих q строках содержатся запросы в 
описанном выше формате. Добавляемые числа x и поправки Δ лежат в промежутке [−10^9,10^9], а Δ≥0.

  Формат вывода
На каждый запрос вида getMin выведите ответ в отдельной строке.
  Пример 1
Ввод
5
insert 5
decreaseKey 1 3
getMin
insert 1
getMin

Вывод
2
1
  Пример 2
Ввод	
5
insert 5
getMin
extractMin
insert 10
getMin

Вывод
5
10
*/

#include <iostream>
#include <vector>

class Heap {
  int sz_ = 0;
  void Exchange(int u, int v);
  void SiftUp(int v);
  void SiftDown(int v);

 public:
  Heap(int n);
  ~Heap();
  long long* arr;
  int* ptrs;
  int* numb;
  void Insert(long long x, int q);
  long long GetMin();
  void ExtractMin();
  void DecreaseKey(int ptr, long long delta);
  void Print(std::string str, int q);
};

Heap::Heap(int n) : arr(new long long[n]), ptrs(new int[n]), numb(new int[n]) {}

Heap::~Heap() {
  delete[] arr;
  delete[] ptrs;
  delete[] numb;
}

void Heap::Exchange(int u, int v) {
  long long k = numb[u];
  long long m = numb[v];
  std::swap(arr[v], arr[u]);
  std::swap(ptrs[k], ptrs[m]);
  std::swap(numb[v], numb[u]);
}

void Heap::SiftUp(int v) {
  int p = (v - 1) / 2;
  while (v != 0 && arr[v] < arr[p]) {
    Exchange(v, p);
    SiftUp(p);
  }
}

void Heap::SiftDown(int v) {
  int u = 2 * v + 1;
  if (2 * v + 2 < sz_ && arr[2 * v + 2] < arr[u]) {
    u = 2 * v + 2;
  }
  while (u < sz_ && arr[u] < arr[v]) {
    Exchange(u, v);
    SiftDown(u);
  }
}

void Heap::Insert(long long x, int q) {
  arr[sz_] = x;
  numb[sz_] = q;
  ptrs[q] = sz_;
  SiftUp(sz_++);
}

long long Heap::GetMin() { return arr[0]; }

void Heap::ExtractMin() {
  Exchange(0, --sz_);
  SiftDown(0);
}

void Heap::DecreaseKey(int ptr, long long delta) {
  arr[ptrs[ptr]] -= delta;
  SiftUp(ptrs[ptr]);
}

void Heap::Print(std::string str, int q) {
  if (str == "insert") {
    long long x;
    std::cin >> x;
    Insert(x, q);
  }
  if (str == "getMin") {
    std::cout << GetMin() << "\n";
  }
  if (str == "extractMin") {
    ExtractMin();
  }
  if (str == "decreaseKey") {
    long long delta;
    int i;
    std::cin >> i >> delta;
    DecreaseKey(--i, delta);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::string str;
  std::cin >> n;
  Heap heap(n);
  for (int q = 0; q < n; ++q) {
    std::cin >> str;
    heap.Print(str, q);
  }
  return 0;
}
