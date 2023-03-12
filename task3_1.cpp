/*
Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины. Для каждой вершины определите расстояние до самой удаленной от нее вершины.
Время работы должно быть O(n).

Формат ввода
В первой строке записано количество вершин n ≤ 10000. Затем следует n - 1 строка, описывающая ребра дерева.
Каждое ребро - это два различных целых числа - индексы вершин в диапазоне [0, n-1].
Индекс корня – 0. В каждом ребре родительской вершиной является та, чей номер меньше.

Формат вывода
Выход должен содержать n строк. В i-ой строке выводится расстояние от i-ой вершины до самой удаленной от нее.

Ввод:       Вывод: 
3           2
0 1         1
1 2         2
*/

#include <iostream>
#include <vector>

struct Node {
  std::vector<int> children;
  int top_son = -1;
  int top_height = 0;
  int second_height = 0;
  int way_through_parent = 0;
};

int max_of_three(int top, int second, int parent) {
  return std::max(top, std::max(second, parent));
}

std::vector<Node> tree_constructor(int n) {
  std::vector<Node> tree(n);
  for (int i = 0; i < n - 1; i++) {
    int a = 0; 
    int b = 0; 
    std::cin >> a >> b;
    if (a > b) std::swap(a, b);
    tree[a].children.push_back(b);
  }
  return tree;
}

void set_top_height(std::vector<Node>& tree, int curr = 0) {
  for (int child : tree[curr].children) {
    set_top_height(tree, child);
    if (tree[child].top_height + 1 > tree[curr].top_height) {
      tree[curr].top_height = tree[child].top_height + 1;
      tree[curr].top_son = child;
    }
  }
}

void set_second_height(std::vector<Node>& tree, int curr = 0) {
  for (int child : tree[curr].children) {
    set_second_height(tree, child);
    if (child == tree[curr].top_son) continue;
    tree[curr].second_height = std::max(tree[child].top_height + 1, tree[curr].second_height);
  }
}

void set_way_through_parent(std::vector<Node>& tree, int curr = 0) {
  for (int child : tree[curr].children) {
    if (child == tree[curr].top_son) {
      tree[child].way_through_parent = std::max(tree[curr].second_height + 1, tree[curr].way_through_parent + 1);
    } else {
      tree[child].way_through_parent = std::max(tree[curr].top_height + 1, tree[curr].way_through_parent + 1);
    }
    set_way_through_parent(tree, child);
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Node> tree = tree_constructor(n);
  set_top_height(tree);
  set_second_height(tree);
  set_way_through_parent(tree);
  for (auto Node : tree) {
    std::cout << max_of_three(Node.top_height, Node.second_height, Node.way_through_parent) << '\n';
  }
  return 0;
}
