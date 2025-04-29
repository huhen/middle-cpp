#include <jemalloc/jemalloc.h>
#include <cstddef>
#include <new>
#include <print>
#include <cstdlib>

static int32_t numAllocs{0}, numDeallocs{0}, numArrayAllocs{0}, numArrayDeallocs{0};

void* operator new(std::size_t sz) {
    void* ptr = malloc(sz);

    if (!ptr || sz == 0) {
        throw std::bad_alloc(); // required by [new.delete.single]/3
    }

    ++numAllocs;
    return ptr;
}

void operator delete(void* ptr) noexcept {
    ++numDeallocs;
    free(ptr);
}

void operator delete(void* ptr, std::size_t sz) noexcept {
    ++numDeallocs;
    free(ptr);
}

void* operator new[](std::size_t sz) {
    void* ptr = malloc(sz);

    if (!ptr || sz == 0) {
        throw std::bad_alloc(); // required by [new.delete.single]/3
    }

    ++numArrayAllocs;
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    ++numArrayDeallocs;
    free(ptr);
}

void operator delete[](void* ptr, std::size_t sz) noexcept {
    ++numArrayDeallocs;
    free(ptr);
}

class Image {
public:
    Image(unsigned int width, unsigned int height)
        : width_(width)
        , height_(height) {
    }

private:
    unsigned int width_;
    unsigned int height_;
};

class VectorOfImages {
public:
    ~VectorOfImages() {
        /* Ваш код здесь */
        std::destroy_n(GetValidStoragePtr(), endPos_);
    }

    Image* GetValidStoragePtr() {
        /* Ваш код здесь */
        return reinterpret_cast<Image*>(std::addressof(storage_));
    }

    void EmplaceBack(unsigned int width, unsigned int height) {
        if (endPos_ >= maxSize_) {
            throw std::bad_alloc{};
        }
        // Ваш код здесь
        std::construct_at(GetValidStoragePtr() + endPos_, width, height);
        ++endPos_;
    }

private:
    unsigned int endPos_ = 0;
    static const unsigned int maxSize_ = 20;
    // Ваш код здесь
    alignas(alignof(Image)) std::byte storage_[maxSize_ * sizeof(Image)];
};

int main() {
    const std::size_t len = 5;
    auto* arrPtrPN = (Image*)std::malloc(sizeof(Image) * len);
    // Ваш код здесь
    for (size_t i = 0; i < len; ++i) {
        // new (std::addressof(arrPtrPN[i])) Image(256, 256);
        std::construct_at(std::addressof(arrPtrPN[i]), 256, 256);
        // arrPtrPN[i].~Image();
        std::destroy_at(std::addressof(arrPtrPN[i]));
    }
    std::free(arrPtrPN);

    return 0;
}