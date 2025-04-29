#include <cstring>
#include <utility>

class Matrix {
public:
    Matrix(size_t rows, size_t cols)
        : rows_(rows)
        , cols_(cols)
        , data_(new int[rows * cols]{}) {
    }

    ~Matrix() {
        delete[] data_;
    }

    Matrix(const Matrix& rhd)
        : rows_(rhd.rows_)
        , cols_(rhd.cols_)
        , data_(new int[rhd.rows_ * rhd.cols_]) {
        std::memcpy(data_, rhd.data_, rows_ * cols_ * sizeof(int));
    }

    Matrix& operator=(const Matrix& rhd) {
        if (this != &rhd) {
            delete[] data_;

            rows_ = rhd.rows_;
            cols_ = rhd.cols_;

            data_ = new int[rhd.rows_ * rhd.cols_];
            std::memcpy(data_, rhd.data_, rows_ * cols_ * sizeof(int));
        }
        return *this;
    }

    Matrix(Matrix&& rhd) noexcept
        : rows_(std::exchange(rhd.rows_, 0))
        , cols_(std::exchange(rhd.cols_, 0))
        , data_(std::exchange(rhd.data_, nullptr)) {
    }

    Matrix& operator=(Matrix&& rhd) noexcept {
        if (this != &rhd) {
            rows_ = std::exchange(rhd.rows_, 0);
            cols_ = std::exchange(rhd.cols_, 0);
            delete[] data_;
            data_ = std::exchange(rhd.data_, nullptr);
        }
        return *this;
    }

    void swap(Matrix& rhd) noexcept {
        std::swap(data_, rhd.data_);
        std::swap(rows_, rhd.rows_);
        std::swap(cols_, rhd.cols_);
    }

    friend void swap(Matrix& lhd, Matrix& rhd) noexcept {
        lhd.swap(rhd);
    }

    // Copy-And-Swap — создаём итоговый результат во временном объекте, а в конце перемещаем его на место оригинального
    // объекта
    void Extend(const Matrix& rhd) {
        Matrix res{rows_ + rhd.rows_, cols_ + rhd.cols_};

        for (size_t i = 0; i < rhd.rows_ * rhd.cols_; ++i) {
            /* код для увеличения размера матрицы с использованием другой матрицы */
        }

        *this = std::move(res);
    }

    // Copy-And-Swap — создаём итоговый результат во временном объекте, а в конце перемещаем его на место оригинального
    // объекта
    void Shrink(const Matrix& rhd) {
        Matrix res{rows_ / 2, cols_ / 2};

        for (size_t i = 0; i < rhd.rows_ * rhd.cols_ / 2; ++i) {
            /* код для уменьшения размера матрицы с использованием другой матрицы */
        }

        *this = std::move(res);
    }

    size_t rows_;
    size_t cols_;
    int* data_;
};

// namespace std {
//     template <>
//     void swap(Matrix& lhs, Matrix& rhs) noexcept {
//         lhs.swap(rhs);
//     }
// } // namespace std

Matrix MultiplyMatrix(const Matrix& m1, const Matrix& m2) {
    Matrix res{m1.cols_, m2.rows_};

    /* код перемножения матриц */

    return res;
}

int main() {
    Matrix m1(3, 5);
    Matrix m2(5, 3);

    using std::swap;
    swap(m1, m2);

    /* код заполнения матриц значениями */

    Matrix m3 = MultiplyMatrix(m1, m2);

    return 0;
}