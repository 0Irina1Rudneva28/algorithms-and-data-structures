/*
Хагрид обожает различных магических существ, одним из его любимцев является Клювокрыл - гиппогриф 
(полуконь-полугрифон, при этом грифон сам сочетает в себе черты льва и орла). На третьем году обучения у 
учеников Хогвартса есть предмет "Уход за магическими существами", и вот настал первый урок, когда этот 
предмет будет вести Хагрид.
Если вы думаете, что Хагрид не готовился к этому уроку, то вы максимально не правы! Он долго изучал 
язык гиппогрифов и выяснил, что он в основном состоит из трех гласных (на письме Хагрид решил обозначать 
их круглыми, квадратными и фигурными скобками) и двух тонов: повышающийся, обозначается на письме тем, что 
соответствующая гласной скобка будет открывающей, и понижающийся~--- скобка будет закрывающейся. 
Также Хагрид выяснил, что перед попыткой напасть на какую-либо цель, гиппогрифы издают яростный крик, 
при этом только крик, чье написание по методике Хагрида будет образовывать правильную скобочную последовательность, 
является яростным.
Хагрид хоть и человек большой души, но может банально не успеть транскрибировать все звуки, издаваемые Клювокрылом, 
а это может сказаться непоправимо на здоровье одного хорохорящегося блондина.

  Формат ввода
Дан транскрибированный по методике выше крик Клювокрыла.
  Формат вывода
Выведите YES, если крик Клювокрыл свидетельствует о начале нападения, и NO – иначе.

  Пример 1
Ввод
()[]
Вывод
YES

  Пример 2
Ввод
([)]
Вывод
NO
*/

#include <iostream>

struct Node {
  Node(char n) {
    val = n;
    prev = nullptr;
  }
  char val;
  Node* prev;
};

struct Stack {
  Stack() { top = nullptr; }
  ~Stack() { Clear(); };
  void PushBack(char value) {
    Node* new_pr = new Node(value);
    new_pr->prev = top;
    top = new_pr;
    sz++;
  }
  void PopBack() {
    Node* tmp_pr = top;
    top = tmp_pr->prev;
    delete tmp_pr;
    sz--;
  }
  char Back() { return top->val; }
  int Size() { return sz; }
  void Clear() {
    while (sz != 0) {
      PopBack();
    }
  }
  Node* top;
  int sz = 0;
};

int main() {
  Stack stack;
  std::string line;
  std::getline(std::cin, line);
  unsigned long int a = line.size();
  for (unsigned long int i = 0; i < a; i++) {
    if (line[i] == '{' || line[i] == '(' || line[i] == '[') {
      stack.PushBack(line[i]);
    } else {
      if (line[i] == '}' && stack.sz != 0 && stack.Back() == '{') {
        stack.PopBack();
      } else if (line[i] == ']' && stack.sz != 0 && stack.Back() == '[') {
        stack.PopBack();
      } else if (line[i] == ')' && stack.sz != 0 && stack.Back() == '(') {
        stack.PopBack();
      } else if (line[i] == '}' || line[i] == ')' || line[i] == ']') {
        stack.PushBack(line[i]);
        break;
      }
    }
  }
  if (stack.Size() == 0) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  return 0;
}
