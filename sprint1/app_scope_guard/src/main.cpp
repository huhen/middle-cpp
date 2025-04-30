#include <cstddef>
#include <new>
#include <print>
#include <cstdlib>

#include <boost/scope/scope_success.hpp>
#include <boost/scope/scope_fail.hpp>
#include <boost/scope/defer.hpp>

#include <format>
#include <iostream>

class FinancialOperation {
public:
    explicit FinancialOperation(int id)
        : id_(id) {
    }
    int id() const {
        return id_;
    }

private:
    int id_;
};

template <>
struct std::formatter<FinancialOperation> {
    // Поддержка общих модификаторов форматирования (например, {:5}, {:.2})
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        auto it = ctx.begin();
        if (it != ctx.end() && *it != '}') {
            throw std::format_error("Invalid format");
        }
        return it;
    }

    // Форматирует объект в строку
    template <typename FormatContext>
    auto format(const FinancialOperation& op, FormatContext& ctx) -> decltype(ctx.out()) {
        return std::format_to(ctx.out(), "FinOp#{}", op.id());
    }
};

class DataBase {
public:
    void PushBack(const FinancialOperation& op);
    FinancialOperation PopBack();
};

class LocalStorage {
public:
    void PushBack(const FinancialOperation& op);
    FinancialOperation PopBack();
};

class GuiOpList {
public:
    void PushBack(const FinancialOperation& op);
    FinancialOperation PopBack();
};

class THandler {
public:
    void InsertOperation(const FinancialOperation& op) {
        using hr_clock = std::chrono::high_resolution_clock;

        boost::scope::scope_success successGuard{[&op] {std::cout << std::format("Operation {} was successfully inserted!\n", op.id()); }};

        boost::scope::defer_guard calculateTime{[startTime = hr_clock::now()] {
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(hr_clock::now() - startTime);
            std::print("Duration: {} ms\n", duration.count());
        }};

        localStorage.PushBack(op);
        boost::scope::scope_fail guard1{[&] { localStorage.PopBack(); }};

        db.PushBack(op);
        boost::scope::scope_fail guard2{[&] { db.PopBack(); }};

        guiOpList.PushBack(op);
        boost::scope::scope_fail guard3{[&] { guiOpList.PopBack(); }};
    }

private:
    LocalStorage localStorage;
    DataBase db;
    GuiOpList guiOpList;
};

int main() {
    FinancialOperation op(123);

    THandler handler;
    handler.InsertOperation(op);

    return 0;
}
