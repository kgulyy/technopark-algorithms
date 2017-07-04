/**
 * 4_1. Солдаты. В одной военной части решили построить в одну шеренгу по росту.
 * Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
 * а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
 * Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту –
 * сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик,
 * который заметил интересную особенность – все солдаты в части разного роста.
 * Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
 * а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
 * Требуемая скорость выполнения команды - O(log n).
 * Формат входных данных.
 * Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000).
 * В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй
 * (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата,
 * стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
 * Формат выходных данных.
 * На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции,
 * на которую должен встать этот солдат (все стоящие за ним двигаются назад).
 *
 * !!! Данное решение не выполняется за лагорифмическое время
 */
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// структура для представления узлов дерева
struct Node {
  int key;
  int height;
  int nodes;
  Node* left;
  Node* right;

  Node(int key) : key(key), height(1), nodes(1), left(NULL), right(NULL) {}

  virtual ~Node() {
    delete left;
    delete right;
  }
};

int height(Node* node) {
  return node != NULL ? node->height : 0;
}

int balanceFactor(Node* node) {
  return height(node->right) - height(node->left);
}

void recalcHeight(Node* node) {
  int hl = height(node->left);
  int hr = height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

// правый поворот вокруг p
Node* rotateRight(Node* p) {
  Node* q = p->left;
  p->left = q->right;
  q->right = p;
  recalcHeight(p);
  recalcHeight(q);
  return q;
}

// левый поворот вокруг q
Node* rotateLeft(Node* q) {
  Node* p = q->right;
  q->right = p->left;
  p->left = q;
  recalcHeight(q);
  recalcHeight(p);
  return p;
}

// балансировка узла p
Node* balance(Node* p) {
  recalcHeight(p);
  if (balanceFactor(p) == 2) {
    if (balanceFactor(p->right) < 0)
      p->right = rotateRight(p->right);
    return rotateLeft(p);
  }
  if (balanceFactor(p) == -2) {
    if (balanceFactor(p->left) > 0)
      p->left = rotateLeft(p->left);
    return rotateRight(p);
  }
  return p; // балансировка не нужна
}

int nodes(Node* p) {
  return p ? p->nodes : 0;
}

// вставка ключа k в дерево с корнем p
Node* insert(Node* p, int key, int& pos) {
  if (p == NULL) return new Node(key);
  ++p->nodes;
  if (key < p->key) {
    pos += nodes(p->right) + 1;
    p->left = insert(p->left, key, pos);
  } else {
    p->right = insert(p->right, key, pos);
  }

  return balance(p);
}

// поиск узла с минимальным ключом в дереве p
Node* findMin(Node* p) {
  return p->left ? findMin(p->left) : p;
}

// удаление узла с минимальным ключом из дерева p
Node* removeMin(Node* p) {
  if (p->left == 0)
    return p->right;
  p->left = removeMin(p->left);
  --p->nodes;

  return balance(p);
}

// удаление ключа k из дерева p
Node* remove(Node* p, int k) {
  if (!p) return 0;
  if (k < p->key)
    p->left = remove(p->left, k);
  else if (k > p->key)
    p->right = remove(p->right, k);
  else //  k == p->key
  {
    Node* q = p->left;
    Node* r = p->right;
    p->left = NULL;
    p->right = NULL;
    delete p;
    if (!r) return q;
    Node* min = findMin(r);
    min->right = removeMin(r);
    min->left = q;
    return balance(min);
  }
  return balance(p);
}

enum Command {
  INSERT = 1,
  REMOVE = 2,
};

int main() {
  ifstream cin("input.txt");
  size_t size = 0;
  cin >> size;

  Node* root = NULL;
  size_t command = 0;
  int key = 0;
  vector<int> v;
  vector<int> result;

  for (int i = 0; i < size; ++i) {
    int pos = 0;
    cin >> command >> key;
    switch (command) {
      case INSERT: {
        root = insert(root, key, pos);
        result.push_back(pos);

        vector<int>::const_iterator it = v.begin() + pos;
        v.insert(it, key);
        break;
      }
      case REMOVE: {
        int element = v[key];
        root = remove(root, element);

        vector<int>::const_iterator it = v.begin() + key;
        v.erase(it);
        break;
      }
      default: break;
    }
  }
  cin.close();

  for (int i = 0; i < result.size(); ++i) {
    cout << result[i] << endl;
  }

  delete root;

  return 0;
}