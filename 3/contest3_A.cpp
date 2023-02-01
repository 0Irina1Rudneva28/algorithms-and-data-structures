/*
В этой задаче Марк бежит марафон до нового альбома. Вам предстоит написать систему стимулирования его, 
чтобы альбом не вышел микстейпом. При этом у него много конкурентов, которые одновременно с ним бегут на фитах. 
Необходимо следить за прогрессом у всех исполнителей и посылать им мотивирующие уведомления. А именно, ваша 
программа должна обрабатывать следующие события:
RUN user page — сохранить факт того, что исполнитель под номером user написал page секунд. Если ранее такой 
исполнитель не встречался, необходимо его добавить. Гарантируется, что в рамках одного исполнителя записанные 
секунды в соответствующих ему событиях возрастают.
CHEER user — сообщить исполнителю user, какая доля существующих исполнителей (не считая его самого) записала 
меньшее число секунд, чем он. Если этот исполнитель на данный момент единственный, доля считается равной 1. 
Если для данного исполнителя пока не было ни одного события RUN, доля считается равной 0, а сам исполнитель 
не учитывается при вычислении долей для других до тех пор, пока для него не случится событие RUN.
  Формат ввода
В первой строке вводится количество запросов  Q — натуральное число, не превосходящее 10^5. В следующих Q
 строках в соответствии с описанным выше форматом вводятся запросы.
Гарантируется, что все вводимые числа целые и положительные, при этом номера исполнителей не превосходят 10^5, а 
суммарное время альбома не превосходит 42195 секунд.

  Формат вывода
Для каждого запроса CHEER user выведите единственное вещественное число от 0 до 1 — ответ на запрос.
Формат вывода этого числа — 6 значащих цифр. То есть std::setprecision(6), говоря на языке C++.

  Пример
Ввод	
12
CHEER 5
RUN 1 10
CHEER 1
RUN 2 5
RUN 3 7
CHEER 2
CHEER 3
RUN 3 10
CHEER 3
RUN 3 11
CHEER 3
CHEER 1

Вывод
0
1
0
0.5
0.5
1
0.5

Примечания
Данная задача (в оригинальной версии условия) предлагалась во втором этапе отбора в ШАД в 2019 году в качестве 
второй по сложности.
*/

#include <iomanip>
#include <iostream>

class STree {
  long long* arr_;
  std::pair<int, int>* data_;
  int sz_ = 1;
  void Exchange(int user, int delta);
  int Count(int v, int left, int right);

 public:
  STree();
  ~STree() {
    delete[] arr_;
    delete[] data_;
  }
  void Change(int n, int delta) { Exchange(sz_ + n - 1, delta); }
  int Search(int left, int right);
};

void STree::Exchange(int user, int delta) {
  if (user > 0) {
    arr_[user] += delta;
    Exchange(user / 2, delta);
  }
}
int STree::Count(int v, int left, int right) {
  if (v >= sz_ * 2 || (data_[v].first > right || data_[v].second < left)) {
    return 0;
  }
  if ((data_[v].second <= right) && (data_[v].first >= left)) {
    return arr_[v];
  }
  int left_tree = v * 2;
  int right_tree = v * 2 + 1;
  int ans = Count(left_tree, left, right) + Count(right_tree, left, right);
  return ans;
}
STree::STree() {
  while (sz_ < 42195 + 10000) {
    sz_ *= 2;
  }
  arr_ = new long long[sz_ * 2]{0};
  data_ = new std::pair<int, int>[sz_ * 2];
  data_[0] = {0, 0};
  for (int i = sz_; i < 2 * sz_; ++i) {
    data_[i].first = i + 1 - sz_;
    data_[i].second = i + 1 - sz_;
  }
  for (int i = sz_ - 1; i > 0; --i) {
    data_[i].first = data_[i * 2].first;
    data_[i].second = data_[i * 2 + 1].second;
  }
}
int STree::Search(int left, int right) { return Count(1, left, right); }

int main() {
  int n, i, user, page, x = 0;
  long double t;
  std::cin >> n;
  int* arr = new int[100001]{0};
  std::string str;
  STree s_tree;
  for (i = 0; i < n; ++i) {
    std::cin >> str;
    if (str == "RUN") {
      std::cin >> user >> page;
      if (arr[user] == 0) {
        ++x;
      } else {
        s_tree.Change(arr[user], -1);
      }
      arr[user] = page;
      s_tree.Change(arr[user], 1);
    } else if (str == "CHEER") {
      std::cin >> user;
      if (arr[user] == 0) {
        std::cout << 0 << '\n';
      } else {
        if (x != 1) {
          t = x - 1;
          if (arr[user] == 1) {
            std::cout << '0' << '\n';
          } else {
            std::cout << std::setprecision(6)
                      << s_tree.Search(1, arr[user] - 1) / t << '\n';
          }
        } else {
          std::cout << '1' << '\n';
        }
      }
    }
  }
  delete[] arr;
}
