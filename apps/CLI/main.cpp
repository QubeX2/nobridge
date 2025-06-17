
#include "vect.h"

int main() {
    mkrl::VecT<float, 3> vec1{0.1, 0.2, 0.3};

    std::println("Len: {}", vec1.length());
    std::cout << vec1 << std::endl;

    return 0;
}
