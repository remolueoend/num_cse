#include <iostream>
#include <Eigen/Dense>
#include <chrono>

using namespace std;
using namespace Eigen;

void rowColAccessTiming(void) {
    const int K = 3; // number of repetitions
    const int N_min = 5; // min matrix size 32
    const int N_max = 13; // max matrix size 8192
    unsigned long n = (1L << N_min);
    /**
     * matrix times contains results:
     *      size | t1 (row access) | t2 (col access)
     *     N_min | ...
     *   N_min*2 | ...
     *       ...
     *     N_max | ...
     */
    MatrixXd times(N_max-N_min+1, 3);

    for(int I=N_min; I <= N_max; I++, n*=2) {
        MatrixXd A = MatrixXd::Random(n, n);
        double t1 = 1000;
        for(int k = 0; k <K; k++) {
            auto tic = chrono::high_resolution_clock::now();
            for(int j = 0; j < n-1; j++) A.row(j+1) -= A.row(j); // row access
            auto toc = chrono::high_resolution_clock::now();
            double t = (double)chrono::duration_cast<std::chrono::microseconds>(toc - tic).count()/1E6;
            t1 = min(t1, t);
        }

        double t2 = 1000.0;
        for(int k = 0; k <K; k++) {
            auto tic = chrono::high_resolution_clock::now();
            for(int j = 0; j < n-1; j++) A.col(j+1) -= A.col(j); // column access
            auto toc = chrono::high_resolution_clock::now();
            double t = (double)chrono::duration_cast<std::chrono::microseconds>(toc - tic).count()/1E6;
            t2 = min(t2, t);
        }

        times(I-N_min, 0) = n; times(I-N_min, 1) = t1; times(I-N_min, 2) = t2;
    }

    cout << times << endl;
}

int main() {
    rowColAccessTiming();
}
