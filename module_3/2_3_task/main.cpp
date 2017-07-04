/**
 * Дано число N < 10​^6 и последовательность целых чисел из [-2​^31​ .. 2​^31​] длиной N.
 * Требуется построить бинарное дерево, заданное наивным порядком вставки.
 * Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
 * то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
 * Рекурсия запрещена.
 *
 * 2_3. Выведите элементы в порядке post-order (снизу вверх).
 */
#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

// Узел двоичного дерева с данными типа int
struct CBinaryNode {
  int data;
  CBinaryNode* left;
  CBinaryNode* right;

  CBinaryNode(int data) : data(data) {
    left = NULL;
    right = NULL;
  }

  virtual ~CBinaryNode() {
    delete left;
    delete right;
  }
};

// Вставка в бинарное дерево
void insertToBinaryTree(CBinaryNode* root, int insertValue);
// Обратный обход дерева в глубину (снизу-вверх)
void traverseDFS(CBinaryNode* node);
// Обработчик вершины
void visit(CBinaryNode* node);

int main() {
  ifstream in("input.txt");
  size_t size = 0;
  in >> size;

  int number = 0;
  in >> number;
  CBinaryNode* root = new CBinaryNode(number);
  for (int i = 0; i < size - 1; ++i) {
    in >> number;
    insertToBinaryTree(root, number);
  }
  in.close();

  traverseDFS(root);

  delete root;

  return 0;
}

void insertToBinaryTree(CBinaryNode* root, int insertValue) {
  CBinaryNode* ptr = root;
  CBinaryNode* parent = root;

  while (ptr != NULL) {
    if (insertValue < (ptr->data)) {
      parent = ptr;
      ptr = ptr->left;
    } else {
      parent = ptr;
      ptr = ptr->right;
    }
  }

  CBinaryNode* newNode = new CBinaryNode(insertValue);

  if (insertValue < (parent->data))
    parent->left = newNode;
  else
    parent->right = newNode;
}

void traverseDFS(CBinaryNode* node) {
  stack<CBinaryNode*> stack;
  CBinaryNode* lastVisitedNode = NULL;

  while (!stack.empty() || node != NULL) {
    if (node != NULL) {
      stack.push(node);
      node = node->left;
    } else {
      CBinaryNode* topNode = stack.top();
      if (topNode->right != NULL && lastVisitedNode != topNode->right)
        node = topNode->right;
      else {
        visit(topNode);
        lastVisitedNode = stack.top();
        stack.pop();
      }
    }
  }
}

void visit(CBinaryNode* node) {
  cout << node->data << " ";
}