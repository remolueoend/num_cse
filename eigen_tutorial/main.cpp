#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;

template <typename Scalar>
Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> eigenTypeDemo(unsigned int dim) {
    // general dynamic (variable sized) matrices:
    using dynMat_t = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    // dynamic (variable sized) column vector:
    using dynColVec_t = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
    // dynamic (variable sized) row vector:
    using dynRowVec_t = Eigen::Matrix<Scalar, 1, Eigen::Dynamic>;

    using index_t = typename dynMat_t::Index;
    using entry_t = typename dynMat_t::Scalar;

    // declare vectors of size 'dim' not yet initialized:
    dynColVec_t colvec(dim);
    dynRowVec_t rowvec(dim);

    for(index_t i=0; i < colvec.size(); i++) colvec[i] = (Scalar)i;
    for(index_t i=0; i < rowvec.size(); i++) rowvec[i] = (Scalar)1/(i+1);
    colvec[0] = (Scalar)3.14; rowvec[dim-1] = (Scalar)2.718;

    // form tensor product, a matrix, see section 1.3.1:
    dynMat_t vecprod = colvec * rowvec;
    const index_t nrows = vecprod.rows();
    const int ncols = vecprod.cols();

    std::cout << vecprod << std::endl;

    return vecprod;
}

template <typename MatType>
void blockAccess(Eigen::MatrixBase<MatType> &M) {
    using index_t = typename Eigen::MatrixBase<MatType>::Index;
    using entry_t = typename Eigen::MatrixBase<MatType>::Scalar;
    const index_t nrows(M.rows()); // number of rows
    const index_t ncols(M.cols()); // number of rows

    // block size half the size of the matrix:
    index_t p = nrows/2, q = ncols/2;
    for(index_t i = 0; i < std::min(p, q); i++) {
        std::cout << "Block (" << i << ',' << i << ',' << p << ',' << q << ") = " << M.block(i, i, p, q) << std::endl;
    }
}

int main() {
    MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);

    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mat = eigenTypeDemo<double>(5);
    blockAccess(mat);
}
