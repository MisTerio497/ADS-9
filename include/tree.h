// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <iostream>
#include <string>
#include <vector>

std::vector<char> remove(const std::vector<char> &list, char item) {
  std::vector<char> result;
  for (auto i : list) {
    if (i != item) {
      result.push_back(i);
    }
  }
  return result;
}

struct Node {
  char value;
  std::vector<Node *> children;
  explicit Node(char val) : value(val) {}
};
class PMTree {
  void addNode(Node *&parent, std::vector<char> children) {
    for (auto child : children) {
      Node *newNode = new Node(child);
      parent->children.push_back(newNode);
      addNode(newNode, remove(children, child));
    }
  }
  void free(Node *node) {
    for (auto child : node->children) {
      free(child);
    }
    delete node;
  }
  void print(Node *node, int depth = 0) {
    std::cout << std::string(depth, ' ') << node->value << std::endl;
    for (auto child : node->children) {
      print(child, depth + 1);
    }
  }
  void travel(Node *node, std::vector<char> path,
              std::vector<std::vector<char>> &result) {
    if (!node)
      return;
    path.push_back(node->value);

    if (node->children.empty()) {
      result.push_back(path);
      return;
    }
    for (auto child : node->children) {
      travel(child, path, result);
    }
  }

 public:
  std::vector<Node *> root;
  explicit PMTree(const std::vector<char> &list) {
    for (auto item : list) {
      Node *newNode = new Node(item);
      root.push_back(newNode);
      addNode(newNode, remove(list, item));
    }
  }
  ~PMTree() {
    for (auto node : root) {
      free(node);
    }
  }
  void print() {
    for (auto node : root) {
      print(node);
    }
  }
  std::vector<std::vector<char>> getAllPerms() {
    std::vector<std::vector<char>> result;
    for (auto node : root) {
      travel(node, {}, result);
    }
    return result;
  }
};
std::vector<char> getPerm1(PMTree &tree, int num);
std::vector<char> getPerm2(PMTree &tree, int num);

#endif // INCLUDE_TREE_H_
