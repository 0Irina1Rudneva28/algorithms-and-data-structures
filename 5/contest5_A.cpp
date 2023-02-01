/*
Доминик решил пересмотреть свой автопарк и организовать информацию о нем. Для этого он присвоил каждой машине 
номер и приоритет. Доминик уверен, что если расположить машины как вершины в декартовом дерева поиска, то он 
сможет подбирать нужную тачку на гонку оптимально.
Так как Доминик, как и всегда, торопится на встречу с семьей, ему нужно построить дерево для хранения информации 
о машинах за линейное время от числа машин.
  Формат ввода
В первой строке записано число N — количество пар номер-приоритет. Далее следует N (1 ≤ N ≤ 50000) пар (ai, bi). 
Для всех пар |ai|, |bi| ≤ 30000. ai ≠ aj и bi ≠ bj для всех i ≠ j. Гарантируется, что пары отсортированы по возрастанию ai.

  Формат вывода
Если Доминик выбрал неверные приоритеты, и дерево построить невозможно, то выведите NO. Иначе выведите N строк, 
каждая из которых должна описывать вершину. Описание вершины состоит из трёх чисел: номер предка, номер левого сына 
и номер правого сына. Если у вершины отсутствует предок или какой-либо из сыновей, то выводите на его месте число 0.

Если подходящих деревьев несколько, выведите любое.

  Пример
Ввод	
7
0 5
1 3
2 2
3 9
4 11
5 4
6 6
Вывод
YES
2 0 0
3 1 0
0 2 6
6 0 5
4 0 0
3 4 7
6 0 0
*/

#include <iostream>
#include <vector>
struct Node {
  int key;
  int priority;
  int number;
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  Node(int key, int prior, int num) : key(key), priority(prior), number(num) {}
};

class Treap {
  void Clear() {
    for (size_t i = 0; i < nodes.size(); i++) {
      delete nodes[i];
    }
  }

 public:
  std::vector<Node*> nodes;
  ~Treap() { Clear(); };
  Node* Insert(Node* node, int key, int prior, int num) {
    if (node == nullptr) {
      node = new Node(key, prior, num);
      return node;
    }
    if (prior > node->priority) {
      Node* new_node = new Node(key, prior, num);
      new_node->left = node->right;
      if (node->right != nullptr) {
        node->right->parent = new_node;
      }
      new_node->parent = node;
      node->right = new_node;
      return new_node;
    }
    if (node->parent == nullptr) {
      node->parent = new Node(key, prior, num);
      node->parent->left = node;
      return node->parent;
    }
    return Insert(node->parent, key, prior, num);
  }
  void Print() {
    for (size_t i = 0; i < nodes.size(); i++) {
      std::cout << (nodes[i]->parent == nullptr ? 0 : nodes[i]->parent->number)
                << " "
                << (nodes[i]->left == nullptr ? 0 : nodes[i]->left->number)
                << " "
                << (nodes[i]->right == nullptr ? 0 : nodes[i]->right->number)
                << '\n';
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  Treap treap;
  Node* node = nullptr;
  int key, priority;
  for (int i = 0; i < n; i++) {
    std::cin >> key >> priority;
    node = treap.Insert(node, key, priority, i + 1);
    treap.nodes.push_back(node);
  }
  std::cout << "YES" << '\n';
  treap.Print();
}
