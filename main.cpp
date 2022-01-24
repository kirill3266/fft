#include <fstream>
#include "fft.h"
#include "BigInt.h"

int main() {
    std::fstream f1("C:\\Users\\kakir\\CLionProjects\\Ann\\Input.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!f1.is_open()) std::cout << "Fopen error!" << std::endl;
    BigInt A(f1);
    BigInt B(f1);
    BigInt Res;
    std::cout << A << std::endl << B << std::endl;

    multiply(A, B, Res);
    f1.clear();
    f1 << "\n" << Res;
    f1.close();
    return 0;
}