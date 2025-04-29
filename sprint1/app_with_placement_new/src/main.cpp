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

int main() {
    const std::size_t len = 5;
    auto* arrPtrPN = (Image*)std::malloc(sizeof(Image) * len);
    // Ваш код здесь
    for (size_t i = 0; i < len; ++i) {
        new (std::addressof(arrPtrPN[i])) Image(256,256);
        arrPtrPN[i].~Image();
    }
    std::free(arrPtrPN);
    
    return 0;
}