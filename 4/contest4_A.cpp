/*
Нужно реализовать структуру данных множество, способную быстро выполнять следующие операции:

«+ N» — добавить число N в множество. Не гарантируется, что N отсутствует в множестве.
«- N» — удалить число N из множества. Не гарантируется, что N имеется в множестве.
«? N» — узнать, есть ли число N в множестве.
  Формат ввода
В первой строке идет число N (1 ≤ N ≤ 10^6) — число запросов к множеству. Далее идет N запросов на N строках в формате выше.
Все числа из запросов лежат в отрезке [0, 10^9]

  Формат вывода
Для каждого запроса третьего типа вывести YES, если ответ положителен, и NO — иначе.

  Пример
Ввод
10
+ 0
+ 1
+ 2
? 2
+ 2
? 2
- 2
? 2
- 0
? 0

Вывод
YES
YES
NO
NO
*/

#include <iostream>
#include <vector>

class HashTable {
 private:
  long long cap_;
  std::vector<long long>* arr_;

 public:
  HashTable(long long n) {
    long long size = n;
    this->cap_ = size;
    arr_ = new std::vector<long long>[cap_];
  }

  void Insert(long long v) {
    long long index = HashFoo(v);
    arr_[index].push_back(v);
  }
  void Erase(long long v) {
    long long index = HashFoo(v);
    std::vector<long long>::iterator i;
    for (i = arr_[index].begin(); i != arr_[index].end(); i++) {
      if (*i == v) {
        break;
      }
    }
    if (i != arr_[index].end()) {
      arr_[index].erase(i);
    }
  }
  bool Find(long long v) {
    long long index = HashFoo(v);
    std::vector<long long>::iterator i;
    for (i = arr_[index].begin(); i != arr_[index].end(); i++) {
      if (*i == v) {
        return true;
      };
    }
    return false;
  }
  long long HashFoo(long long key) { return (key % cap_); }

  ~HashTable() { delete[] arr_; }
};

int main() {
  const long long kSise = 1e6 + 7;
  long long n;
  std::cin >> n;

  HashTable h(kSise);

  for (long long i = 0; i < n; i++) {
    char c;
    long long x;

    std::cin >> c >> x;

    if (c == '+') {
      if (!h.Find(x)) {
        h.Insert(x);
      }
    } else if (c == '-') {
      h.Erase(x);
    } else {
      std::cout << (h.Find(x) ? "YES" : "NO") << '\n';
    }
  }
}
