/*
AVL
Доминик проводит инвентаризацию (опять). Он уверен, что машины можно и нужно сравнить по числу миллисекунд для разгона 
от нуля до 100 км/ч. Он просит вас помочь ему, а именно, ваш алгоритм должен работать с множеством машин Доминика. 
Нужно реализовать следующие операции:
add(i)  — добавить в множество машин тачку с разгоном в i миллисекунд (если такая там уже есть, то Доминик отвлекся 
на семейные разговоры и подсунул вам второй раз ту же машину);
next(i)  — узнать машину с минимальным временем разгона, не меньшим i. Если искомая машина отсутствует, необходимо 
вывести -1 и попросить Доминика быть внимательнее.
  Формат ввода
Исходно множество машин пусто. Первая строка входного файла содержит число n — количество запросов Доминика (1 < n< 3 ⋅ 10^5).
Следующие n строк содержат операции. Каждая операция имеет вид:
+ i  — add(i)
? i  — next(i)
Если операция + идет во входном файле в начале или после другой операции +, то она задает операцию add(i). 
Если же она идет после запроса ?, и результат этого запроса был y, то выполняется операция add((i+y)%10^9). 
Это нужно, чтобы Доминик убедился в том, что вы достойный член семьи и не реализовали оффлайн алгоритм.
Во всех запросах и операциях добавления параметры лежат в интервале от 0 до 10^9.

  Формат вывода
Для каждого запроса выведите одно число — ответ на запрос.
  Пример
Ввод	
6
+ 1
+ 3
+ 3
? 2
+ 1
? 4
Вывод
3
4
*/

#include <iostream>

struct Node {
  long long data;
  Node* left;
  Node* right;
  Node* parent;
  int diff;
  Node(long long item, Node* parent);
};
class AVL {
  void SmallLeftTurn(Node* node);
  void SmallRightTurn(Node* node);
  void BigLeftTurn(Node* node);
  void BigRightTurn(Node* node);
  bool DoRotation(Node* node);

 public:
  Node* head = nullptr;
  ~AVL() {
    if (head != nullptr) {
      Delete(head);
    }
  }
  void Add(long long item);
  bool Contain(long long item);
  int GetHeadDiff() { return (head == nullptr) ? 0 : head->diff; };
  long long Next(long long item);
  Node* Find(long long item);
  void Delete(Node* n) {
    if (n != nullptr) {
      Node* r = n->right;
      Node* l = n->left;
      Delete(r);
      Delete(l);
      delete n;
    }
  }
};

Node::Node(long long item, Node* parent) : data(item), parent(parent) {
  left = nullptr;
  right = nullptr;
  diff = 0;
}
long long AVL::Next(long long item) {
  long long ans = 1000000001;
  Node* a = head;
  while (a != nullptr) {
    if (a->data < item) {
      a = a->right;
      continue;
    }
    ans = std::min(ans, a->data);
    a = a->left;
  }
  return (ans == 1000000001) ? -1 : ans;
}
Node* AVL::Find(long long item) {
  Node* runner = head;
  while (runner != nullptr && runner->data != item) {
    if (item < runner->data) {
      runner = runner->left;
    } else {
      runner = runner->right;
    }
  }
  return runner;
}
void AVL::Add(long long item) {
  if (head == nullptr) {
    head = new Node(item, nullptr);
  } else {
    Node* runner = head;
    while (true) {
      if (runner->data < item) {
        if (runner->right != nullptr) {
          runner = runner->right;
        } else {
          runner->right = new Node(item, runner);
          runner = runner->right;
          break;
        }
      } else {
        if (runner->left != nullptr) {
          runner = runner->left;
        } else {
          runner->left = new Node(item, runner);
          runner = runner->left;
          break;
        }
      }
    }
    while (true) {
      if (runner->parent == nullptr) {
        break;
      }
      if (runner->parent->left == runner) {
        runner->parent->diff += 1;
      } else {
        runner->parent->diff -= 1;
      }
      runner = runner->parent;
      if (DoRotation(runner)) {
        runner = runner->parent;
      }
      if (runner->diff == 0) {
        break;
      }
    }
  }
}

bool AVL::Contain(long long item) { return Find(item) != nullptr; }
void AVL::SmallLeftTurn(Node* node) {
  Node* b = node->right;
  node->right = b->left;
  if (node->right != nullptr) {
    node->right->parent = node;
  }
  b->left = node;
  b->parent = node->parent;
  node->parent = b;
  if (b->parent != nullptr) {
    if (b->parent->left == node) {
      b->parent->left = b;
    } else {
      b->parent->right = b;
    }
  } else {
    head = b;
  }
  if (b->diff == -1) {
    node->diff = 0;
    b->diff = 0;
  } else if (b->diff == 0) {
    node->diff = -1;
    b->diff = +1;
  }
}
void AVL::SmallRightTurn(Node* node) {
  Node* b = node->left;
  node->left = b->right;
  if (node->left != nullptr) {
    node->left->parent = node;
  }
  b->right = node;
  b->parent = node->parent;
  node->parent = b;
  if (b->parent != nullptr) {
    if (b->parent->left == node) {
      b->parent->left = b;
    } else {
      b->parent->right = b;
    }
  } else {
    head = b;
  }
  if (b->diff == 1) {
    node->diff = 0;
    b->diff = 0;
  } else if (b->diff == 0) {
    b->diff = -1;
    node->diff = 1;
  }
}
void AVL::BigRightTurn(Node* node) {
  Node* b = node->left;
  Node* c = b->right;
  node->left = c->right;
  if (node->left != nullptr) {
    node->left->parent = node;
  }
  b->right = c->left;
  if (b->right != nullptr) {
    b->right->parent = b;
  }
  c->parent = node->parent;
  if (node->parent != nullptr) {
    if (node->parent->left == node) {
      node->parent->left = c;
    } else {
      node->parent->right = c;
    }
  } else {
    head = c;
  }
  c->right = node;
  node->parent = c;
  c->left = b;
  b->parent = c;
  if (c->diff == 1) {
    node->diff = -1;
    b->diff = 0;
  } else if (c->diff == 0) {
    node->diff = 0;
    b->diff = 0;
  } else if (c->diff == -1) {
    node->diff = 0;
    b->diff = 1;
  }
  c->diff = 0;
}
void AVL::BigLeftTurn(Node* node) {
  Node* b = node->right;
  Node* c = b->left;
  node->right = c->left;
  if (node->right != nullptr) {
    node->right->parent = node;
  }
  b->left = c->right;
  if (b->left != nullptr) {
    b->left->parent = b;
  }
  c->parent = node->parent;
  if (node->parent != nullptr) {
    if (node->parent->left == node) {
      node->parent->left = c;
    } else {
      node->parent->right = c;
    }
  } else {
    head = c;
  }
  c->left = node;
  node->parent = c;
  c->right = b;
  b->parent = c;
  if (c->diff == 1) {
    node->diff = 0;
    b->diff = -1;
  } else if (c->diff == 0) {
    node->diff = 0;
    b->diff = 0;
  } else if (c->diff == -1) {
    node->diff = 1;
    b->diff = 0;
  }
  c->diff = 0;
}
bool AVL::DoRotation(Node* node) {
  bool fl = false;
  if (node->diff == 2) {
    if (node->left->diff == 1 || node->left->diff == 0) {
      SmallRightTurn(node);
      fl = true;
    } else if (node->left->diff == -1) {
      BigRightTurn(node);
      fl = true;
    }
  } else if (node->diff == -2) {
    if (node->right->diff == -1 || node->right->diff == 0) {
      SmallLeftTurn(node);
      fl = true;
    } else if (node->right->diff == 1) {
      BigLeftTurn(node);
      fl = true;
    }
  }
  return fl;
}
long long y;
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  AVL tree;
  int n;
  long long x;
  char command;
  std::cin >> n;
  char prev = '+';
  for (int i = 0; i < n; ++i) {
    std::cin >> command >> x;
    if (command == '+') {
      if (prev == '?' && command == '+' &&
          tree.Find((x + y) % 1000000000) == nullptr) {
        tree.Add((x + y) % 1000000000);
      } else {
        if (tree.Find(x) == nullptr) {
          tree.Add(x);
        }
      }
    } else if (command == '?') {
      y = tree.Next(x);
      std::cout << y << '\n';
    }
    prev = command;
  }
  return 0;
}
