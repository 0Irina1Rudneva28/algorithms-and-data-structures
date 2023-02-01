/* Реализовать стек.
  Обработайте следующие запросы:
push n: добавить число n в конец стека и вывести «ok»;
pop: удалить из стека последний элемент и вывести его значение, либо вывести «error», если стек был пуст;
back: сообщить значение последнего элемента стека, либо вывести «error», если стек пуст;
size: вывести количество элементов в стеке;
clear: опустошить стек и вывести «ok»;
exit: вывести «bye» и завершить работу.
  Формат ввода
В каждой строке входных данных задана одна операция над стеком в формате, описанном выше.
  Формат вывода
В ответ на каждую операцию выведите соответствующее сообщение.
  Пример
Ввод
push 1
back
exit

Вывод
ok
1
bye
*/

#include <iostream>

struct Node {
  Node(int n) {
    val = n;
    prev = nullptr;
  }
  int val;
  Node* prev;
};

class Stack {
 public:
  Stack() { top_ = nullptr; }
  ~Stack() { Clear(); };
  void PushBack(int value) {
    Node* new_pr = new Node(value);
    new_pr->prev = top_;
    top_ = new_pr;
    sz_++;
    std::cout << "ok" << std::endl;
  }
  int PopBack() {
    Node* tmp_pr = top_;
    int prev_x = tmp_pr->val;
    top_ = tmp_pr->prev;
    delete tmp_pr;
    sz_--;
    return prev_x;
  }
  int Back() { return top_->val; }
  int Size() { return sz_; }
  void Clear() {
    while (sz_ != 0) {
      PopBack();
    }
  }

 private:
  Node* top_;
  int sz_ = 0;
};

int main() {
  Stack stack;
  std::string line;
  while (line != "exit") {
    std::getline(std::cin, line);
    if (line.substr(0, 3) == "pop") {
      (stack.Size() == 0) ? std::cout << "error"
                                      << "\n"
                          : std::cout << stack.PopBack() << "\n";
    }
    if (line.substr(0, 4) == "push") {
      stack.PushBack(std::stoi(line.substr(5)));
    }
    if (line.substr(0, 4) == "back") {
      if (stack.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << stack.Back() << std::endl;
      }
    }
    if (line.substr(0, 4) == "size") {
      std::cout << stack.Size() << std::endl;
    }
    if (line.substr(0, 5) == "clear") {
      stack.Clear();
      std::cout << "ok" << std::endl;
    }
  }
  std::cout << "bye" << std::endl;
  return 0;
}
