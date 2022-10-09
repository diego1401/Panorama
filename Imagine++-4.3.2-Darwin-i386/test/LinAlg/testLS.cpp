// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// Test least-square linear system solving

#include <Imagine/LinAlg.h>
using namespace Imagine;

int main() {
    double a[] = {
        519, 130, 1, 0, 0, 0, 519, 130,
        0, 0, 0, 519, 130, 1, 0, 0,
        550, 130, 1, 0, 0, 0, 550, 130,
        0, 0, 0, 550, 130, 1, 0, 0,
        549, 159, 1, 0, 0, 0, 549, 159,
        0, 0, 0, 549, 159, 1, 0, 0,
        520, 160, 1, 0, 0, 0, 520, 160,
        0, 0, 0, 520, 160, 1, 0, 0,
        534, 330, 1, 0, 0, 0, 534, 330,
        0, 0, 0, 534, 330, 1, 0, 0
    };
    double b[] = {
        65, 128, 93, 129, 92, 160, 61, 157, 75, 323
    };

    double *c=a, *d=b;

    Matrix<double> A(10,8);
    Vector<double> B(10);
    for(int i=0; i<10; i++) {
        for(int j=0; j<8; j++)
            A(i,j) = *c++;
        B[i] = *d++;
    }
    std::cout << "A=" << A;
    std::cout << "B=" << B << std::endl << std::endl;

    B = linSolve(A, B);
    std::cout << "X=" << B << std::endl;
    std::cout << "AX=" << A*B << std::endl;

    std::cout << "GNU Octave answer:" << std::endl;
    double b2[] = {
        4.9008e-01, -7.2367e-03, -4.4396e+02,  8.1222e-02,
        9.7062e-01, -4.0463e+01,  4.9008e-01, -7.2367e-03};
    Vector<double> B2(8);
    d=b2;
    for(int i=0; i<8; i++)
        B2[i] = *d++;
    std::cout << "X=" << B2 << std::endl;
    std::cout << "AX=" << A*B2 << std::endl;
    return 0;
}
