/*
Распределяющая шляпа — крайне древний артефакт, способный по ее носителю понять, какой факультет 
ему подойдет для наиболее полного раскрытия характера. Но некто решил заколдовать шляпу, теперь она 
определяет уровень IQ носителя. Вам предстоит реализовать заколдованную шляпу, чтобы с оригинальной сняли проклятье.
У вас есть сама шляпа и набор действий, который будет с ней происходить. К шляпе стоит очередь из первокурсников 
Хогвартса, которая желает протестировать себя.
  Возможные действия:
«enqueue n» Добавить в внутреннюю очередь шляпы уровень интеллекта очередного первокурсника n (1 ≤ n ≤ 10^9) 
(значение n задается после команды). Шляпа должна сказать «ok».
«dequeue» Удалить из внутренней очереди шляпы уровень интеллекта последнего студента, которого она еще помнит. 
Шляпа должна сказать его значение.
«front» Шляпа должна сказать уровень интеллекта последнего студента, которого она еще помнит, не забывая его.
«size» Шляпа скажет, уровень интеллекта какого числа студентов она помнит.
«clear» Перезагрузка шляпы, она забывает все, что было до этого. Шляпа должна сказать «ok».
«min» Шляпа должна сказать уровень интеллекта самого неодаренного умственными способностями первокурсника. 
При этом, конечно же, не забыть его.
Перед исполнением операций «front», «dequeue» и «min» шляпа должна проверять, содержится ли в внутренней 
очереди хотя бы один элемент. Если шляпа помнит ноль студентов на момент таких запросов, то она должна 
вместо числового значения сказать слово «error».

  Формат ввода
В первой строке входных данных записано единственное число M (1 ≤ M ≤ 2 ⋅ 10^5) — количество команд.
В следующих М строках дано по одной команде из тех, что идут выше.
  Формат вывода
Для каждой команды выведите одну строчку — то, что скажет шляпа.

  Пример
Ввод
9
enqueue 2
front
dequeue
size
dequeue
enqueue 1
enqueue 2
size
min

Вывод
ok
2
2
0
error
ok
ok
2
1
*/

#include <algorithm>
#include <iostream>
#include <string>

struct Node {
  Node* next = nullptr;
  long long num = 0;
  long long m_iq = 0;
};

class Stack {
  Node* last_ = nullptr;
  long long size_ = 0;
 public:
  ~Stack() { Clear(); };
  void Insert(long long num);
  long long Pop();
  long long Front() const { return last_->num; };
  void Clear();
  long long Min();
  long long Size() { return size_; };
};

void Stack::Insert(long long num) {
  Node* node = new Node;
  node->num = num;
  if (size_ == 0) {
    node->m_iq = node->num;
    last_ = node;
  } else {
    node->m_iq = last_->m_iq > node->num ? node->num : last_->m_iq;
    node->next = last_;
    last_ = node;
  }
  size_++;
}
long long Stack::Pop() {
  long long num = last_->num;
  Node* next_last = last_->next;
  delete last_;
  last_ = next_last;
  size_--;
  if (size_ == 0) { last_ = nullptr; };
  return num;
}
void Stack::Clear() {
  while (size_ != 0) {
    Pop();
  }
}
long long Stack::Min() {
  if (size_ == 0) { return 10000000000; };
  return last_->m_iq;
}

class Queue {
  Stack stack_back_;
  Stack stack_front_;
 public:
  void Insert(long long num) { stack_back_.Insert(num); };
  long long Front();
  long long PopFront();
  void Clear();
  long long Size() { return stack_back_.Size() + stack_front_.Size(); };
  long long Min();
};

long long Queue::Front() {
  if (stack_back_.Size() + stack_front_.Size() == 0) { return 0; };
  if (stack_front_.Size() == 0) {
    while (stack_back_.Size() != 0) {
      stack_front_.Insert(stack_back_.Pop());
    }
  }
  return stack_front_.Front();
}
long long Queue::PopFront() {
  long long tmp = Front();
  if (stack_front_.Size() > 0) {
    stack_front_.Pop();
  }
  return tmp;
}
void Queue::Clear() {
  stack_back_.Clear();
  stack_front_.Clear();
}
long long Queue::Min() {
  long long min = 0;
  if (stack_back_.Size() + stack_front_.Size() != 0) { min = std::min(stack_back_.Min(), stack_front_.Min()); };
  return min;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long num_of, x;
  std::string str;
  std::cin >> num_of;
  Queue queue;
  for (long long i = 0; i < num_of; ++i) {
    std::cin >> str;
    if (str == "enqueue") {
      std::cin >> x;
      queue.Insert(x);
      std::cout << "ok" << '\n';
    } else if (str == "dequeue") { 
      long long tmp = queue.PopFront();
      if (!static_cast<bool>(tmp)) { 
        std::cout << "error" << '\n';
      } else {
        std::cout << tmp << '\n';
      }
    } else if (str == "front") {
      long long tmp = queue.Front();
      if (!static_cast<bool>(tmp)) { 
        std::cout << "error" << '\n';
      } else {
        std::cout << tmp << '\n';
      }
    } else if (str == "clear") {
      queue.Clear();
      std::cout << "ok" << '\n';
    } else if (str == "min") {
      long long min = queue.Min();
      if (min == 0) { 
        std::cout << "error" << '\n'; 
      } else {
        std::cout << min << '\n';
      }
    } else if (str == "size") { std::cout << queue.Size() << '\n'; };
  }
  return 0;
}
