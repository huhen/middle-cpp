#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::jthread worker([](std::stop_token st) {
        for (int i = 0; i < 5; ++i) {
            if (st.stop_requested()) {
                std::cout << "Остановка потока\n";
                return;
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Работаю... " << i << "\n";
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(3));
    worker.request_stop(); // Запрос остановки
} // Деструктор worker автоматически вызывает join()