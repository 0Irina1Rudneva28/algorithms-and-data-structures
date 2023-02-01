#include <fstream>
#include <iomanip>
#include<iostream>
#include<vector>

struct  RedBlackNode {
  long long key;
  std::string color;
  RedBlackNode* left = nullptr;
  RedBlackNode* right = nullptr;
  RedBlackNode* parent = nullptr;
  RedBlackNode(long long key, std::string color, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right) : 
	  key(key), color(color), parent(parent), left(left), right(right) {}
};

class  RedBlackTree {
  RedBlackNode* root;
  void leftRotate(RedBlackNode*& root, RedBlackNode* x);
  void rightRotate(RedBlackNode*& root, RedBlackNode* y);
  void insert(RedBlackNode*& root, RedBlackNode* node);
  void InsertFixUp(RedBlackNode*& root, RedBlackNode* node);
  void destory(RedBlackNode*& node);
  void remove(RedBlackNode*& root, RedBlackNode* node);
  void removeFixUp(RedBlackNode*& root, RedBlackNode* node, RedBlackNode* parent);
  RedBlackNode* search(RedBlackNode* node, long long key) const;
  //void print(RedBlackNode* node)const;
  void inOrder(RedBlackNode* tree)const;

 public:
  RedBlackTree();
  ~RedBlackTree();
  void Insert(long long key);
  void Remove(long long key);
  RedBlackNode* Search(long long key);
  long long Next(long long key);
  long long Prev(long long key);
};

RedBlackTree::RedBlackTree() : root(NULL) { root = nullptr; }

RedBlackTree::~RedBlackTree() { destory(root); }

void RedBlackTree::leftRotate(RedBlackNode*& root, RedBlackNode* x) {
  RedBlackNode* y = x->right;
  x->right = y->left;
  if (y->left != NULL) {
	y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL) {
	root = y;
  } else {
	(x == x->parent->left) ? x->parent->left = y : x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void RedBlackTree::rightRotate(RedBlackNode*& root, RedBlackNode* y) {
  RedBlackNode* x = y->left;
  y->left = x->right;
  if (x->right != NULL) {
	x->right->parent = y;
  }
  x->parent = y->parent;
  if (y->parent == NULL) {
	root = x;
  } else {
    (y == y->parent->right) ? y->parent->right = x : y->parent->left = x;
  }
  x->right = y;
  y->parent = x;
}

void RedBlackTree::Insert(long long key) {
  RedBlackNode* z = new RedBlackNode(key, "Red", NULL, NULL, NULL);
  insert(root, z);
}

void RedBlackTree::insert(RedBlackNode*& root, RedBlackNode* node) {
  RedBlackNode* x = root;
  RedBlackNode* y = NULL;
  while (x != NULL) {
    y = x;
    x = (node->key > x->key) ? x->right : x->left;
  }
  node->parent = y;
  if (y != NULL) {
    (node->key > y->key) ? y->right = node : y->left = node;
  } else {
	root = node;
  }
  node->color = "Red";
  InsertFixUp(root, node);
}

void RedBlackTree::InsertFixUp(RedBlackNode*& root, RedBlackNode* node) {
  RedBlackNode* parent;
  parent = node->parent;
  while (node != RedBlackTree::root && parent->color == "Red") {
    RedBlackNode* gparent = parent->parent;
	if (gparent->left == parent) {
	  RedBlackNode* uncle = gparent->right;
      if (uncle != NULL && uncle->color == "Red") {
        parent->color = "Black";
        uncle->color = "Black";
        gparent->color = "Red";
        node = gparent;
        parent = node->parent;
      } else {
        if (parent->right == node) {
          leftRotate(root, parent);
          std::swap(node, parent);
        }
        rightRotate(root, gparent);
        gparent->color = "Red";
		parent->color = "Black";
        break;
      }
    } else {
      RedBlackNode* uncle = gparent->left;
      if (uncle != NULL && uncle->color == "Red") {
        gparent->color = "Red";
		parent->color = "Black";
		uncle->color = "Black";
        node = gparent;
        parent = node->parent;
      } else {
        if (parent->left == node) {
          rightRotate(root, parent);
          std::swap(parent, node);
        }
        leftRotate(root, gparent);
        parent->color = "Black";
        gparent->color = "Red";
        break;
      }
    }
  }
  root->color = "Black";
}

void RedBlackTree::destory(RedBlackNode*& node) {
  if (node == NULL) {
    return;
  }
  destory(node->left);
  destory(node->right);
  delete node;
  node = nullptr;
}

void RedBlackTree::Remove(long long key) {
  RedBlackNode* deletenode = search(root, key);
  if (deletenode != NULL) {
    remove(root, deletenode);
  }
}

void RedBlackTree::remove(RedBlackNode*& root, RedBlackNode* node)
{
  RedBlackNode* child, * parent;
  std::string color;
  if (node->left != NULL && node->right != NULL) {
    RedBlackNode* replace = node;
    replace = node->right;
    while (replace->left != NULL) {
      replace = replace->left;
    }
    if (node->parent != NULL) {
      (node->parent->left == node) ? node->parent->left = replace : node->parent->right = replace;
	} else {
      root = replace;
	}
	child = replace->right;
	parent = replace->parent;
	color = replace->color;
	if (parent == node) {
      parent = replace;
    } else {
	  if (child != NULL) {
        child->parent = parent;
	  }
      parent->left = child;
      replace->right = node->right;
      node->right->parent = replace;
    }
    replace->parent = node->parent;
    replace->color = node->color;
    replace->left = node->left;
    node->left->parent = replace;
	if (color == "Black") {
      removeFixUp(root, child, parent);
	}
    delete node;
    return;
  }
  child = (node->left != NULL) ? node->left : node->right;
  parent = node->parent;
  color = node->color;
  if (child != nullptr) {
    child->parent = parent;
  }
  if (parent != nullptr) {
    (node == parent->left) ? parent->left = child : parent->right = child;
  } else {
    RedBlackTree::root = child;
  }
  if (color == "Black") {
    removeFixUp(root, child, parent);
  }
  delete node;
}

void RedBlackTree::removeFixUp(RedBlackNode*& root, RedBlackNode* node, RedBlackNode* parent) {
  RedBlackNode* othernode;
  while ((!node) || node->color == "Black" && node != RedBlackTree::root) {
    if (parent->left == node) {
      othernode = parent->right;
      if (othernode->color == "Red") {
        othernode->color = "Black";
        parent->color = "Red";
        leftRotate(root, parent);
        othernode = parent->right;
      } else {
        if (!(othernode->right) || othernode->right->color == "Black") {
          othernode->left->color = "Black";
          othernode->color = "Red";
          rightRotate(root, othernode);
          othernode = parent->right;
        }
        othernode->color = parent->color;
        parent->color = "Black";
        othernode->right->color = "Black";
        leftRotate(root, parent);
        node = root;
        break;
      }
    } else {
      othernode = parent->left;
      if (othernode->color == "Red") {
        othernode->color = "Black";
        parent->color = "Red";
        rightRotate(root, parent);
        othernode = parent->left;
      }
      if ((!othernode->left || othernode->left->color == "Black") && (!othernode->right || othernode->right->color == "Black")) {
        othernode->color = "Red";
        node = parent;
        parent = node->parent;
      } else {
        if (!(othernode->left) || othernode->left->color == "Black") {
          othernode->right->color = "Black";
          othernode->color = "Red";
          leftRotate(root, othernode);
          othernode = parent->left;
        }
        othernode->color = parent->color;
        parent->color ="Black";
        othernode->left->color = "Black";
        rightRotate(root, parent);
        node = root;
        break;
      }
    }
  }
  if (node != nullptr) {
    node->color = "Black";
  }
}

RedBlackNode* RedBlackTree::Search(long long key) { return search(root, key); }

RedBlackNode* RedBlackTree::search(RedBlackNode* node, long long key) const {
  if (node == NULL || node->key == key) {
    return node;
  } else {
    return (key > node->key) ? search(node->right, key) : search(node->left, key);
  }
}

long long RedBlackTree::Next(long long key) {
  long long ans = 1000000001;
  RedBlackNode* a = root;
  while (a != NULL) {
    if (a->key < key) {
      a = a->right;
      continue;
    }
    ans = std::min(ans, a->key);
    a = a->left;
  }
  return (ans == 1000000001) ? -1000000001 : ans;
}

long long RedBlackTree::Prev(long long key) {
    long long ans = -1000000001;
    RedBlackNode* a = root;
    while (a != NULL) {
        if (a->key > key) {
            a = a->left;
            continue;
        }
        ans = std::max(ans, a->key);
        a = a->right;
    }
    return (ans == -1000000001) ? 1000000001 : ans;
}

int main() {
  int n;
  std::string str;
  std::cin >> n;
  long long x;
  RedBlackTree tree;
  for (int i = 0; i < n; ++i) {
    std::cin >> str >> x;
    if (str == "insert") {
      tree.Insert(x);
    } else if (str == "delete") {
      tree.Remove(x);
    } else if (str == "exists") {
      RedBlackNode* tmp = tree.Search(x);
      if (tmp != nullptr) {
        std::cout << "true" << '\n';
      } else {
        std::cout << "false" << '\n';
      }
    } else if (str == "next") {
      long long tmp = tree.Next(x);
      if (tmp == -1000000001) {
        std::cout << "none" << '\n';
      } else {
        std::cout << tmp << '\n';
      }
    } else if (str == "prev") {
      long long tmp = tree.Prev(x);
      if (tmp == 1000000001) {
        std::cout << "none" << '\n';
      } else {
        std::cout << tmp << '\n';
      }
    }
  }
  return 0;
}
