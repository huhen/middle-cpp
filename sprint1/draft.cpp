#include <cstddef>
#include <memory>

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

    // Ваш код здесь
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

    void swap(Matrix& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
    }

    friend void swap(Matrix& lhs, Matrix& rhs) noexcept {
        lhs.swap(rhs);
    }

private:
    size_t rows_;
    size_t cols_;
    int* data_;
};

class Image {};

class Box {
public:
    Box()
        : imageData_(new Image{}) {
    }

    // Ваш код здесь
    ~Box() {
        // Cleanup code here
        delete imageData_;
    }

    Box(const Box& other)
        : imageData_(new Image(*other.imageData_)) {
        // Copy code here
    }

    Box(Box&& other) noexcept
        : imageData_(other.imageData_) {
        // Move code here
        other.imageData_ = nullptr;
    }

    Box& operator=(const Box& other) {
        // Copy assignment code here
        if (this != &other) {
            delete imageData_;
            imageData_ = new Image(*other.imageData_);
        }
        return *this;
    }

    Box& operator=(Box&& other) noexcept {
        // Move assignment code here
        if (this != &other) {
            delete imageData_;
            imageData_ = other.imageData_;
            other.imageData_ = nullptr;
        }
        return *this;
    }

private:
    Image* imageData_;
};

static void uptr() {
    const std::size_t size = 10;
    auto pArr = std::make_unique<int[]>(size);
    auto pValue = std::make_unique<double>();
}

int main() {
    uptr();
    return 0;
}