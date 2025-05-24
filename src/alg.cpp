// Copyright 2022 NNTU-CS
#include <vector>
#include "../include/tree.h"

std::vector<char> getPerm1(PMTree &tree, int num) {
  int n = tree.root.size();

  int fac = 1;
  for (int i = 2; i <= n; ++i)
    fac *= i;

  if (num > fac || num <= 0)
    return {};

  std::vector<std::vector<char>> result = tree.getAllPerms();
  return result[num - 1];
}

std::vector<char> getPerm2(PMTree &tree, int k) {
  std::vector<char> result;
  std::vector<Node *> currentNodes = tree.root;

  int n = currentNodes.size();
  int fac = 1;
  for (int i = 2; i <= n; ++i)
    fac *= i;

  if (k > fac || k <= 0)
    return {};

  --k;

  while (!currentNodes.empty()) {
    int n = currentNodes.size();
    int fac = 1;
    for (int i = 2; i <= n - 1; ++i)
      fac *= i;

    int index = k / fac;
    k %= fac;

    Node *selected = currentNodes[index];
    result.push_back(selected->value);
    currentNodes.erase(currentNodes.begin() + index);
  }

  return result;
}
