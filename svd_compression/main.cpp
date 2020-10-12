/***********************************************************************************************************
 * Very naive implementation of BMP compression using SVD decomposition and matrix
 * compression. The resulting image itself is not smaller regarding its file
 * size, but the matrix representing the compressed image data could be saved in
 * a more efficient format resulting in a smaller file size, but this is not in the scope of this program.
 *
 * Makes use of http://www.partow.net/programming/bitmap/index.html for reading and writing BMP images.
 **********************************************************************************************************/

#include <Eigen/Dense>
#include <Eigen/SVD>
#include <iostream>
#include "bitmap/bitmap_image.hpp"

using namespace std;
using namespace Eigen;

using svd_t = tuple<MatrixXd, VectorXd, MatrixXd>;

svd_t get_svd(const MatrixXd &A) {
  JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);
  MatrixXd U = svd.matrixU(), V = svd.matrixV();
  VectorXd sv = svd.singularValues();

  return svd_t(U, sv, V);
}

MatrixXd compress(svd_t svd, MatrixXd::Index k) {
  MatrixXd U_k = get<0>(svd).leftCols(k);
  MatrixXd S_k = get<1>(svd).head(k).asDiagonal();
  MatrixXd V_k = get<2>(svd).leftCols(k);

  MatrixXd A_k = U_k * S_k * V_k.transpose();

  return A_k;
}

int main() {
  bitmap_image img("lena_gray.bmp");
  MatrixXd M(img.height(), img.width());
  for(unsigned int r = 0; r < img.height(); r++) {
    for (unsigned int c = 0; c < img.width(); c++) {
      M(r, c) = img.get_pixel(r, c).blue;
    }
  }

  cout << "image moved to matrix" << endl;

  svd_t svd = get_svd(M);
  MatrixXd A_3 = compress(svd, img.width() * 0.1);

  cout << "compression done" << endl;

  for (unsigned int r = 0; r < img.height(); r++) {
    for (unsigned int c = 0; c < img.width(); c++) {
      unsigned int color = A_3(r, c);
      img.set_pixel(r, c, color, color, color);
    }
  }

  cout << "wrote back to image" << endl;

  img.save_image("compressed.bmp");

  cout << "image saved" << endl;
}
