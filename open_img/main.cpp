#include <opencv2/opencv.hpp>
#include <ncurses.h>
#include <thread>
#include <atomic>

// Флаг для завершения работы
std::atomic<bool> running(true);

// Функция для обработки видео
void processVideo() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Ошибка: не удалось открыть камеру!" << std::endl;
        running = false;
        return;
    }

    // Определяем параметры видеопотока
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    std::cout << "\033[1;31mframe_size.width: \033[0m" << frame_width << std::endl;
    std::cout << "\033[1;31mframe_size.height: \033[0m" << frame_height << std::endl;
    int fps = 30; // Количество кадров в секунду (можно изменить)

    // Определяем кодек и создаем объект VideoWriter для записи видео в формате MP4
    cv::VideoWriter video("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));
    // Проверяем, успешно ли создан объект VideoWriter
    if (!video.isOpened()) {
        std::cerr << "Ошибка: Не удалось создать видеофайл для записи" << std::endl;
        return;
    }

    while (running) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Ошибка: пустой кадр!" << std::endl;
            break;
        }

        // Записываем кадр в видеофайл
        video << frame;

        // Отображаем кадр в окне
        cv::imshow("Webcam Stream", frame);

        // Небольшая задержка для обновления окна
        cv::waitKey(1);
    }

    std::cout << "\033[1;32mНачинается освобождение ресурсов\033[0m"<< std::endl;

    cap.release();
    cv::destroyAllWindows();

    std::cout << "\033[1;32mОсвобождение ресурсов закончено\033[0m"<< std::endl;

}

// Функция для обработки ввода
void processInput() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (running) {
        int ch = getch();
        if (ch == 'q' || ch == 27) {
            running = false;
        }
    }

    endwin();
}

int main() {
    std::thread videoThread(processVideo);
    std::thread inputThread(processInput);

    videoThread.join();
    inputThread.join();

    return 0;
}
