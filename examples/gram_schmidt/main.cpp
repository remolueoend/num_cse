#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

template <typename Derived>
Eigen::MatrixBase<Derived> gramschmidt(const MatrixBase<Derived> &A) {
    // first vector just gets normalized:
    MatrixBase<Derived> Q = A;
//    Q.col(0).normalize();
    for(unsigned int i = 1; i < Q.cols(); i++) {
        // replace inner loop over each previous vector in Q with fast
        // matrix-vector multiplication
        Q.col(i) -= Q.leftCols(i) * (Q.leftCols(i).adjoint() * A.col(i));
        // normalize vector, if possible. Otherwise columns of Q
        // must have been linearly dependent:
        if (Q.col(i).norm() <= 10e-9 * A.col(i).norm()) {
            std::cerr << "GS failed: A has lin. dep. columns" << endl;
            break;
        } else {
            Q.col(i).normalize();
        }
    }

    return Q;
}

int main() {
    MatrixXd M(3, 3);
    M << 1,1,1, 2,2,2, 3,3,3;
    MatrixXd Q = gramschmidt(M);
    cout << Q << endl;
    return 0;
}
