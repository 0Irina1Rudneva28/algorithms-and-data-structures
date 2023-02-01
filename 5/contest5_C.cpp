/*
Splay
Очередная гонка, в этот раз вам предстоит разработать модуль соответствия гонщик-тачка. Каждый гонщик имеет 
свой уникальный позывной и машину, для которой водитель придумал уникальное имя. Гарантируется, что все имена
и позывные попарно различны.
  Формат ввода
Программа получает на вход количество участников в виде позывной гонщика —имя машины N (0 ≤ N ≤ 10^5). 
Далее следует N строк, каждая строка содержит ровно два слова.
Затем идет число Q (1 ≤ Q ≤ 10^5) — количество запросов к модулю. Далее на каждой следующей из Q строк идет слово, 
к которому надо вывести, если на входе имя, соответствующий позывной гонщика, иначе — имя машины, соответствующей гонщику.

  Формат вывода
Программа должна вывести на отдельных строках результаты запросов.

  Пример
Ввод	
3
car plane
mouse cat
base stream
3
plane
stream
base

Вывод
car
base
stream
*/

#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
  std::pair<std::string, std::string> key;
  TreeNode* parent = nullptr;
  TreeNode* left = nullptr;
  TreeNode* right = nullptr;
  TreeNode(std::string racer, std::string car);
};

class SplayTree {
  TreeNode* root_;
  size_t tree_arg_;
  void Zig(TreeNode* x);
  void ZigZig(TreeNode* x);
  void ZigZag(TreeNode* x);
  void Splay(TreeNode* x);
  TreeNode* FindNode(std::string x);
  void DeleteNode(TreeNode*& node);

 public:
  SplayTree(size_t tree_arg) : root_(nullptr), tree_arg_(tree_arg) {}
  ~SplayTree() { DeleteNode(root_); }
  std::string Find(std::string str);
  void Insert(std::string racer, std::string car);
};

TreeNode::TreeNode(std::string racer, std::string car) {
  key.first = racer;
  key.second = car;
}

void SplayTree::Zig(TreeNode* x) {
  TreeNode* p = x->parent;
  if (p->left == x) {
    TreeNode* b_tree = x->right;
    x->parent = nullptr;
    x->right = p;
    p->parent = x;
    p->left = b_tree;
    if (b_tree != nullptr) {
      b_tree->parent = p;
    }
  } else {
    TreeNode* b_tree = x->left;
    x->parent = nullptr;
    x->left = p;
    p->parent = x;
    p->right = b_tree;
    if (b_tree != nullptr) {
      b_tree->parent = p;
    }
  }
}

void SplayTree::ZigZig(TreeNode* x) {
  TreeNode* p = x->parent;
  TreeNode* g = p->parent;
  if (p->left == x) {
    TreeNode* b_tree = x->right;
    TreeNode* c_tree = p->right;
    x->parent = g->parent;
    x->right = p;
    p->parent = x;
    p->left = b_tree;
    p->right = g;
    g->parent = p;
    g->left = c_tree;
    if (x->parent != nullptr) {
      (x->parent->left == g) ? x->parent->left = x : x->parent->right = x;
    }
    if (b_tree != nullptr) {
      b_tree->parent = p;
    }
    if (c_tree != nullptr) {
      c_tree->parent = g;
    }
  } else {
    TreeNode* b_tree = p->left;
    TreeNode* c_tree = x->left;
    x->parent = g->parent;
    x->left = p;
    p->parent = x;
    p->left = g;
    p->right = c_tree;
    g->parent = p;
    g->right = b_tree;
    if (x->parent != nullptr) {
      (x->parent->left == g) ? x->parent->left = x : x->parent->right = x;
    }
    if (b_tree != nullptr) {
      b_tree->parent = g;
    }
    if (c_tree != nullptr) {
      c_tree->parent = p;
    }
  }
}

void SplayTree::ZigZag(TreeNode* x) {
  TreeNode* p = x->parent;
  TreeNode* g = p->parent;
  if (p->right == x) {
    TreeNode* b_tree = x->left;
    TreeNode* c_tree = x->right;
    x->parent = g->parent;
    x->left = p;
    x->right = g;
    p->parent = x;
    p->right = b_tree;
    g->parent = x;
    g->left = c_tree;
    if (x->parent != nullptr) {
      (x->parent->left == g) ? x->parent->left = x : x->parent->right = x;
    }
    if (b_tree != nullptr) {
      b_tree->parent = p;
    }
    if (c_tree != nullptr) {
      c_tree->parent = g;
    }
  } else {
    TreeNode* b_tree = x->left;
    TreeNode* c_tree = x->right;
    x->parent = g->parent;
    x->left = g;
    x->right = p;
    p->parent = x;
    p->left = c_tree;
    g->parent = x;
    g->right = b_tree;
    if (x->parent != nullptr) {
      (x->parent->left == g) ? x->parent->left = x : x->parent->right = x;
    }
    if (b_tree != nullptr) {
      b_tree->parent = g;
    }
    if (c_tree != nullptr) {
      c_tree->parent = p;
    }
  }
}

void SplayTree::Splay(TreeNode* x) {
  while (x->parent != nullptr) {
    TreeNode* p = x->parent;
    TreeNode* g = p->parent;
    if (g == nullptr) {
      Zig(x);
    } else if (g->left == p && p->left == x) {
      ZigZig(x);
    } else if (g->right == p && p->right == x) {
      ZigZig(x);
    } else {
      ZigZag(x);
    }
  }
  root_ = x;
}

TreeNode* SplayTree::FindNode(std::string x) {
  TreeNode* ret = nullptr;
  TreeNode* curr = root_;
  TreeNode* prev = nullptr;
  while (curr != nullptr) {
    prev = curr;
    if ((tree_arg_ == 1 && x < curr->key.first) ||
        (tree_arg_ == 2 && x < curr->key.second)) {
      curr = curr->left;
    } else if ((tree_arg_ == 1 && x > curr->key.first) ||
               (tree_arg_ == 2 && x > curr->key.second)) {
      curr = curr->right;
    } else {
      ret = curr;
      break;
    }
  }
  if (ret != nullptr) {
    Splay(ret);
  } else if (prev != nullptr) {
    Splay(prev);
  }
  return ret;
}

void SplayTree::DeleteNode(TreeNode*& node) {
  if (node == nullptr) {
    return;
  }
  DeleteNode(node->left);
  DeleteNode(node->right);
  delete node;
  node = nullptr;
}

std::string SplayTree::Find(std::string str) {
  TreeNode* tmp = FindNode(str);
  if (tree_arg_ == 1) {
    return (tmp != nullptr) ? tmp->key.second : "error";
  }
  return (tmp != nullptr) ? tmp->key.first : "error";
}

void SplayTree::Insert(std::string racer, std::string car) {
  if (root_ == nullptr) {
    root_ = new TreeNode(racer, car);
    return;
  }
  TreeNode* curr = root_;
  while (curr != nullptr) {
    std::string x = (tree_arg_ == 1) ? racer : car;
    std::string y = (tree_arg_ == 1) ? curr->key.first : curr->key.second;
    if (x < y) {
      if (curr->left == nullptr) {
        TreeNode* new_node = new TreeNode(racer, car);
        curr->left = new_node;
        new_node->parent = curr;
        Splay(new_node);
        return;
      }
      curr = curr->left;
    }
    if (x > y) {
      if (curr->right == nullptr) {
        TreeNode* new_node = new TreeNode(racer, car);
        curr->right = new_node;
        new_node->parent = curr;
        Splay(new_node);
        return;
      }
      curr = curr->right;
    }
    if (x == y) {
      Splay(curr);
      return;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, q;
  std::string racer, car, str;
  SplayTree splay_tree1(1);
  SplayTree splay_tree2(2);
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> racer >> car;
    splay_tree1.Insert(racer, car);
    splay_tree2.Insert(racer, car);
  }
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> str;
    std::string ans1 = splay_tree1.Find(str);
    std::string ans2 = splay_tree2.Find(str);
    if (ans1 != "error") {
      std::cout << ans1 << std::endl;
    } else if (ans2 != "error") {
      std::cout << ans2 << std::endl;
    }
  }
  return 0;
}
