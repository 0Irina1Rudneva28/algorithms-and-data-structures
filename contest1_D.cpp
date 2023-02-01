/*Гоблины Мглистых гор очень любях ходить к своим шаманам. Так как гоблинов много, к шаманам часто 
образуются очень длинные очереди. А поскольку много гоблинов в одном месте быстро образуют шумную 
толку, которая мешает шаманам проводить сложные медицинские манипуляции, последние решили установить 
некоторые правила касательно порядка в очереди.
Обычные гоблины при посещении шаманов должны вставать в конец очереди. Привилегированные же гоблины, 
знающие особый пароль, встают ровно в ее середину, причем при нечетной длине очереди они встают сразу за центром.
Так как гоблины также широко известны своим непочтительным отношением ко всяческим правилам и законам, 
шаманы попросили вас написать программу, которая бы отслеживала порядок гоблинов в очереди.

  Формат ввода
В первой строке входных данный записано число N (1 ≤ N ≤ 105) — количество запросов к программе. Следующие 
N строк содержат описание запросов в формате:
«+ i» — гоблин с номером i (1 ≤ i ≤ N) встает в конец очереди;
«* i» — привилегированный гоблин с номером i встает в середину очереди;
«-» — первый гоблин из очереди уходит к шаманам. Гарантируется, что на момент такого запроса очередь не пуста.
  Формат вывода
Для каждого запроса типа «-» программа должна вывести номер гоблина, который должен зайти к шаманам.

  Пример 1
Ввод
7
+ 1
+ 2
-
+ 3
+ 4
-
-
Вывод
1
2
3
  Пример 2
Ввод	
10
+ 1
+ 2
* 3
-
+ 4
* 5
-
-
-
-
Вывод
1
3
2
5
4
*/

#include <deque>
#include <iostream>

class GoblinsQueue {
  std::deque<int> begin_;
  std::deque<int> middle_;
 public:
  void InsertGoblin(int num);
  void InsertCool(int num);
  void Clear();
};

void GoblinsQueue::InsertGob(int num) {
  middle_.push_back(num);
  if (middle_.size() > begin_.size()) {
    begin_.push_back(middle_.front());
    middle_.pop_front();
  }
}

void GoblinsQueue::InsertCool(int num) {
  if (begin_.size() == middle_.size()) {
    begin_.push_back(num);
  } else {
    middle_.push_front(num);
  }
}

int GoblinsQueue::Clear() {
  int tmp = begin_.front();
  begin_.pop_front();
  if (middle_.size() > begin_.size()) {
    begin_.push_back(middle_.front());
    middle_.pop_front();
  }
  return tmp;
  }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long cmds;
  std::cin >> cmds;
  char ch;
  int x;
  GoblinsQueue goblinsQueue;
  for (long long i = 0; i < cmds; ++i) {
    std::cin >> ch;
    if (ch == '+') {
      std::cin >> x;
      goblinsQueue.InsertGob(x);
    } 
    if (ch == '*') {
      std::cin >> x;
      goblinsQueue.InsertCool(x);
    if {
      std::cout << goblinsQueue.Clear() << std::endl;
    }
  }
  return 0;
}
