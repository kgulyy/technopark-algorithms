/**
 * Дано число N < 10^6 и последовательность пар целых чисел из [-2^31 .. 2^31] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
 * Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
 * При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
 * Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
 * а во втором больше или равны x.
 * Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
 * Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
 *
 * 3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева.
 * Разница может быть отрицательна.
 */
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

struct CTreeNode {
  int key;
  int prior;
  CTreeNode* left;
  CTreeNode* right;

  CTreeNode(int key) : key(key) {
    prior = 0;
    left = NULL;
    right = NULL;
  }

  CTreeNode(int key, int prior) : key(key), prior(prior) {
    left = NULL;
    right = NULL;
  }

  virtual ~CTreeNode() {
    delete left;
    delete right;
  }
};

// Вставка в декартово дерево
void insertToTreap(CTreeNode*& root, int key, int prior);
// Разрезание декартового дерева по ключу
void splitTreap(CTreeNode* currentNode, int key, CTreeNode*& left, CTreeNode*& right);
// Вставка в бинарное дерево
void insertToBinaryTree(CTreeNode* root, int insertValue);
// Вычисление разницы высот деревьев
int calcTreeHeightDiff(CTreeNode* rootBinaryTree, CTreeNode* rootTreap);
// Вычисление высоты дерева
int calcTreeHeight(CTreeNode* root);

int main() {
  ifstream in("input.txt");
  size_t size = 0;
  in >> size;

  int key = 0;
  int prior = 0;
  in >> key >> prior;
  CTreeNode* rootTreap = new CTreeNode(key, prior);
  CTreeNode* rootBinaryTree = new CTreeNode(key);
  for (int i = 1; i < size; ++i) {
    in >> key >> prior;
    insertToTreap(rootTreap, key, prior);
    insertToBinaryTree(rootBinaryTree, key);
  }
  in.close();

  int result = calcTreeHeightDiff(rootBinaryTree, rootTreap);
  cout << result;

  delete rootTreap;
  delete rootBinaryTree;

  return 0;
}

void insertToTreap(CTreeNode*& root, int key, int prior) {
  CTreeNode* ptr = root;
  CTreeNode* parent = NULL;

  while (ptr != NULL && ptr->prior >= prior) {
    parent = ptr;
    if (key < ptr->key) {
      ptr = ptr->left;
    } else {
      ptr = ptr->right;
    }
  }

  CTreeNode* leftTree = NULL;
  CTreeNode* rightTree = NULL;
  splitTreap(ptr, key, leftTree, rightTree);

  CTreeNode* newNode = new CTreeNode(key, prior);

  if (parent == NULL) {
    root = newNode;
  } else if (key < parent->key) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  newNode->left = leftTree;
  newNode->right = rightTree;
}

void splitTreap(CTreeNode* currentNode, int key, CTreeNode*& left, CTreeNode*& right) {
  if (currentNode == NULL) {
    left = NULL;
    right = NULL;
  } else if (currentNode->key <= key) {
    splitTreap(currentNode->right, key, currentNode->right, right);
    left = currentNode;
  } else {
    splitTreap(currentNode->left, key, left, currentNode->left);
    right = currentNode;
  }
}

void insertToBinaryTree(CTreeNode* root, int insertValue) {
  CTreeNode* ptr = root;
  CTreeNode* parent = root;

  while (ptr != NULL) {
    parent = ptr;
    if (insertValue < ptr->key) {
      ptr = ptr->left;
    } else {
      ptr = ptr->right;
    }
  }

  CTreeNode* newNode = new CTreeNode(insertValue);

  if (insertValue < parent->key)
    parent->left = newNode;
  else
    parent->right = newNode;
}

int calcTreeHeightDiff(CTreeNode* rootBinaryTree, CTreeNode* rootTreap) {
  int heightTreap = calcTreeHeight(rootTreap);
  int heightBinaryTree = calcTreeHeight(rootBinaryTree);

  return heightBinaryTree - heightTreap;
}

int calcTreeHeight(CTreeNode* root) {
  if (root == NULL)
    return 0;

  queue<CTreeNode*> q;

  q.push(root);
  int height = 0;

  while (true) {
    size_t nodeCount = q.size();
    if (nodeCount == 0)
      return height;

    height++;

    while (nodeCount > 0) {
      CTreeNode* node = q.front();
      q.pop();
      if (node->left != NULL)
        q.push(node->left);
      if (node->right != NULL)
        q.push(node->right);
      nodeCount--;
    }
  }
}
