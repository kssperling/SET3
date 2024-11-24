// Задача A1i


#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

// Функция проверки, попадает ли точка в круг
bool isInCircle(double x, double y, double cx, double cy, double r) {
    return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

// Метод Монте-Карло
double monteCarlo(double xMin, double xMax, double yMin, double yMax,
                      int numPoints, double& relative) {
    // Настройка генератора случайных чисел
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> distX(xMin, xMax);
    std::uniform_real_distribution<double> distY(yMin, yMax);

    int count = 0;
    for (int i = 0; i < numPoints; ++i) {
        double x = distX(rng);
        double y = distY(rng);

        // Проверяем, попадает ли точка в пересечение трёх окружностей
        if (isInCircle(x, y, 1.0, 1.0, 1.0) &&
            isInCircle(x, y, 1.5, 2.0, std::sqrt(5.0) / 2) &&
            isInCircle(x, y, 2.0, 1.5, std::sqrt(5.0) / 2)) {
            ++count;
        }
    }

    double rectangle = (xMax - xMin) * (yMax - yMin);
    double estimated = (static_cast<double>(count) / numPoints) * rectangle;

    // Точное значение площади
    double exactArea = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1;

    // Вычисление относительного отклонения
    relative = std::abs(estimated - exactArea) / exactArea;

    return estimated;
}


int main() {
    // Параметры прямоугольной области (широкой и узкой)
    double xMinWide = 0.0, xMaxWide = 3.0, yMinWide = 0.0, yMaxWide = 3.0;
    double xMinNarrow = 0.5, xMaxNarrow = 2.5, yMinNarrow = 0.5, yMaxNarrow = 2.5;

    // Диапазон количества точек
    int start = 100, end = 100000, step = 500;

    for (int numPoints = start; numPoints <= end; numPoints += step) {
        double relativeErrorWide, relativeErrorNarrow;

        // Широкая область
        double estimatedAreaWide = monteCarlo(
            xMinWide, xMaxWide, yMinWide, yMaxWide, numPoints, relativeErrorWide);

        // Узкая область
        double estimatedAreaNarrow = monteCarlo(
            xMinNarrow, xMaxNarrow, yMinNarrow, yMaxNarrow, numPoints, relativeErrorNarrow);


        // Вывод прогресса
        std::cout << "Точки: " << numPoints << " | Широкая область: " << estimatedAreaWide
                  << " | Узкая область: " << estimatedAreaNarrow << "\n";
    }

    return 0;
}
