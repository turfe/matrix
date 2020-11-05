#include <iostream>
#include "matrix.h"


int main() {
    int n = 0;
    std::cin >> n;

    Matrix<int> m(n);
    std::cin >> m;

    std::cout << m << std::endl;
    std::cout << m.determinant() << std::endl;

    return 0;
}