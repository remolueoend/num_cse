#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

template <typename Mat>
void replaceWithId(Eigen::DenseBase<Mat> &M) {
    using index_t = typename DenseBase<Mat>::Index;
    index_t n = M.cols();
    if(M.cols() != M.rows() || M.cols() % 2 != 0) {
        throw invalid_argument("matrix M_n,n is not square with n even.");
    }
    M.block(0,n/2,n/2,n/2) = MatrixXd::Identity(n/2, n/2);
}

VectorXd B_rotateVector(VectorXd &v) {
    using index_t = typename VectorXd::Index;;
    index_t len = v.size();
    index_t b_size = len - 1;
    VectorXd _v(len);
    _v.block(1,0, len-1,1) = v.block(0,0, len-1,1);
    _v[0] = v[len-1];

    return _v;
}

MatrixXd C_resizeMat(MatrixXd &M) {
    MatrixXd newM(M.rows() + 1, M.cols() + 1);
    MatrixXd lastCol(M.rows(), 1);
    MatrixXd lastRow(1, M.cols());

    newM << M, lastCol, lastRow, 1;

    return newM;
}

int A() {
    MatrixXd m(10, 10);
    replaceWithId(m);

    cout << "A):" << endl << m << endl;
}
int B() {
    VectorXd d(5);
    d[0] = 1;
    d[1] = 2;
    d[2] = 3;
    d[3] = 4;
    d[4] = 5;
    VectorXd _d = B_rotateVector(d);
    cout << "Before:" << endl << d << endl << "After:" << endl << _d << endl;
}
int C() {
    MatrixXd M(3, 4);
    M << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12;
    MatrixXd newM = C_resizeMat(M);

    cout << "M:" << endl << M << endl << "_M:" << endl << newM << endl;
}

using block_t = typename VectorXd::BlockXpr;
block_t myHead(VectorXd v, int i) {
    return v.block(0, 0, i, 1);
}
block_t myTail(VectorXd v, int i) {
    return v.block(v.size() - i, 0, i, 1);
}

int D() {
    VectorXd v(10);
    v << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;

    cout << "v: " << v << endl;
    cout << "head(5): " << endl << myHead(v, 5) << endl;
    cout << "tail(5): " << endl << myTail(v, 5) << endl;
}

int main() {
//    A();
//    B();
//    C();
    D();
}
