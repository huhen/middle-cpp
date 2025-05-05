#include <memory>
#include <print>
#include <string>
#include <vector>

class Widget : public std::enable_shared_from_this<Widget> {

    Widget(std::string_view name, std::shared_ptr<Widget> parent) : name(name_), parent(parent_) {}

    // Метод для создания дочернего виджета
    std::shared_ptr<Widget> CreateChild(std::string_view childName) {
        auto child = std::make_shared<Widget>(childName, shared_from_this());
        children_.push_back(child);
        return child;
    }

    // Метод для отображения иерархии виджетов
    void PrintHierarchy(int level = 0) const {
        const std::string indent(level * 2, ' ');

        if (parent_) {
            std::print("{} - {} (Parent: {})\n", indent, name_, parent_->name_);
        } else {
            std::print("{} - {}", indent, name_);
        }

        for (const auto &child : children_) {
            child->PrintHierarchy(level + 1);
        }
    }

private:
    std::string name_;
    std::weak_ptr<Widget> parent_;                   // Слабая ссылка на родителя
    std::vector<std::shared_ptr<Widget>> children_;  // Список дочерних виджетов
};

int main() {
    auto root = std::make_shared<Widget>("Root");  // Главное окно

    // Создание дочерних виджетов
    auto child1 = root->CreateChild("Child1");
    auto child2 = root->CreateChild("Child2");

    // Создание дочерних виджетов для Child1
    child1->CreateChild("Grandchild1");
    child1->CreateChild("Grandchild2");

    // Вывод иерархии виджетов
    root->PrintHierarchy();

    return 0;
}