// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
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
// Функция для вывода вектора
void printVector(const std::vector<char> &vec) {
  std::cout << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i != vec.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

int main() {
  // Создаем дерево перестановок для символов '1', '2', '3'
  std::vector<char> items = {'1', '2', '3'};
  PMTree tree(items);

  std::cout << "Все перестановки:" << std::endl;
  auto all_perms = tree.getAllPerms();
  for (const auto &perm : all_perms) {
    printVector(perm);
  }

  std::cout << "\nЭксперимент с замерами времени:\n" << std::endl;

  // Тестируем getPerm1
  std::cout << "Метод getPerm1 (полный перебор):" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= 6; ++i) {
    auto perm = getPerm1(tree, i);
    std::cout << "Перестановка #" << i << ": ";
    printVector(perm);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Время выполнения: " << duration.count() << " мкс\n"
            << std::endl;

  // Тестируем getPerm2
  std::cout << "Метод getPerm2 (оптимизированный):" << std::endl;
  start = std::chrono::high_resolution_clock::now();
  for (int i = 1; i <= 6; ++i) {
    auto perm = getPerm2(tree, i);
    std::cout << "Перестановка #" << i << ": ";
    printVector(perm);
  }
  end = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Время выполнения: " << duration.count() << " мкс" << std::endl;

  return 0;
}
