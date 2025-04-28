#include <cstddef>
#include <memory>

static void uptr() {
    const std::size_t size = 10;
    auto pArr = std::make_unique<int[]>(size);
    auto pValue = std::make_unique<double>();
}

int main() {
    uptr();
    return 0;
}