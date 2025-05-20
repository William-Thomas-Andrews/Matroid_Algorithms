#include "UnionFind.hpp"

int main() {
    UnionFind union_find = UnionFind(20);
    union_find.union_operation(2, 3);
    union_find.union_operation(2, 4);
    union_find.union_operation(1, 3);
    union_find.print_data();
}