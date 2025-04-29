#include <cstddef>
#include <memory>

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