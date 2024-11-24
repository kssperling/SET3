// Задача A1i

//
// #include <iostream>
// #include <cmath>
// #include <random>
// #include <fstream>
//
// // Функция проверки, попадает ли точка в круг
// bool isInCircle(double x, double y, double cx, double cy, double r) {
//     return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
// }
//
// // Метод Монте-Карло
// double monteCarlo(double xMin, double xMax, double yMin, double yMax,
//                       int numPoints, double& relative) {
//     // Настройка генератора случайных чисел
//     std::mt19937 rng(42);
//     std::uniform_real_distribution<double> distX(xMin, xMax);
//     std::uniform_real_distribution<double> distY(yMin, yMax);
//
//     int count = 0;
//     for (int i = 0; i < numPoints; ++i) {
//         double x = distX(rng);
//         double y = distY(rng);
//
//         // Проверяем, попадает ли точка в пересечение трёх окружностей
//         if (isInCircle(x, y, 1.0, 1.0, 1.0) &&
//             isInCircle(x, y, 1.5, 2.0, std::sqrt(5.0) / 2) &&
//             isInCircle(x, y, 2.0, 1.5, std::sqrt(5.0) / 2)) {
//             ++count;
//         }
//     }
//
//     double rectangle = (xMax - xMin) * (yMax - yMin);
//     double estimated = (static_cast<double>(count) / numPoints) * rectangle;
//
//     // Точное значение площади
//     double exactArea = 0.25 * M_PI + 1.25 * std::asin(0.8) - 1;
//
//     // Вычисление относительного отклонения
//     relative = std::abs(estimated - exactArea) / exactArea;
//
//     return estimated;
// }
//
//
// int main() {
//     // Параметры прямоугольной области (широкой и узкой)
//     double xMinWide = 0.0, xMaxWide = 3.0, yMinWide = 0.0, yMaxWide = 3.0;
//     double xMinNarrow = 0.5, xMaxNarrow = 2.5, yMinNarrow = 0.5, yMaxNarrow = 2.5;
//
//     // Диапазон количества точек
//     int start = 100, end = 100000, step = 500;
//
//     for (int numPoints = start; numPoints <= end; numPoints += step) {
//         double relativeErrorWide, relativeErrorNarrow;
//
//         // Широкая область
//         double estimatedAreaWide = monteCarlo(
//             xMinWide, xMaxWide, yMinWide, yMaxWide, numPoints, relativeErrorWide);
//
//         // Узкая область
//         double estimatedAreaNarrow = monteCarlo(
//             xMinNarrow, xMaxNarrow, yMinNarrow, yMaxNarrow, numPoints, relativeErrorNarrow);
//
//
//         // Вывод прогресса
//         std::cout << "Точки: " << numPoints << " | Широкая область: " << estimatedAreaWide
//                   << " | Узкая область: " << estimatedAreaNarrow << "\n";
//     }
//
//     return 0;
// }













//---------------------------------------------------------------------------------------------------------------
// Задача A2i

//
// #include <chrono>
// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <random>
//
//
// class ArrayGenerator {
// public:
//     static std::vector<int> generateRandomArray(int size, int minValue, int maxValue) {
//         std::vector<int> array(size);
//         std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
//         std::uniform_int_distribution<int> dist(minValue, maxValue);
//         for (int &val : array) {
//             val = dist(rng);
//         }
//         return array;
//     }
//
//     static std::vector<int> generateReversedArray(int size) {
//         std::vector<int> array(size);
//         for (int i = 0; i < size; ++i) {
//             array[i] = size - i;
//         }
//         return array;
//     }
//
//     static std::vector<int> generateNearlySortedArray(int size, int swaps) {
//         std::vector<int> array(size);
//         for (int i = 0; i < size; ++i) {
//             array[i] = i;
//         }
//
//         std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
//         for (int i = 0; i < swaps; ++i) {
//             int idx1 = rng() % size;
//             int idx2 = rng() % size;
//             std::swap(array[idx1], array[idx2]);
//         }
//         return array;
//     }
// };
//
//
// void merge(std::vector<int>& array, int left, int mid, int right) {
//     int n1 = mid - left + 1;
//     int n2 = right - mid;
//
//     std::vector<int> L(n1), R(n2);
//
//     for (int i = 0; i < n1; ++i) L[i] = array[left + i];
//     for (int i = 0; i < n2; ++i) R[i] = array[mid + 1 + i];
//
//     int i = 0, j = 0, k = left;
//     while (i < n1 && j < n2) {
//         if (L[i] <= R[j]) {
//             array[k++] = L[i++];
//         } else {
//             array[k++] = R[j++];
//         }
//     }
//
//     while (i < n1) array[k++] = L[i++];
//     while (j < n2) array[k++] = R[j++];
// }
//
// void mergeSort(std::vector<int>& array, int left, int right) {
//     if (left >= right) return;
//     int mid = left + (right - left) / 2;
//     mergeSort(array, left, mid);
//     mergeSort(array, mid + 1, right);
//     merge(array, left, mid, right);
// }
//
//
// void insertionSort(std::vector<int>& array, int left, int right) {
//     for (int i = left + 1; i <= right; ++i) {
//         int key = array[i];
//         int j = i - 1;
//         while (j >= left && array[j] > key) {
//             array[j + 1] = array[j];
//             --j;
//         }
//         array[j + 1] = key;
//     }
// }
//
// void hybridMergeSort(std::vector<int>& array, int left, int right, int threshold) {
//     if (right - left + 1 <= threshold) {
//         insertionSort(array, left, right);
//         return;
//     }
//
//     int mid = left + (right - left) / 2;
//     hybridMergeSort(array, left, mid, threshold);
//     hybridMergeSort(array, mid + 1, right, threshold);
//     merge(array, left, mid, right);
// }
//
//
// class SortTester {
// public:
//     template <typename SortFunction>
//     static long long measureTime(SortFunction sortFunc, std::vector<int> array) {
//         auto start = std::chrono::high_resolution_clock::now();
//         sortFunc(array);
//         auto end = std::chrono::high_resolution_clock::now();
//         return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//     }
//
//     static void testSorts(int size, int threshold) {
//         ArrayGenerator generator;
//
//         std::vector<int> randomArray = generator.generateRandomArray(size, 0, 6000);
//         std::vector<int> reversedArray = generator.generateReversedArray(size);
//         std::vector<int> nearlySortedArray = generator.generateNearlySortedArray(size, 10);
//
//         std::cout << "Array size: " << size << ", Threshold: " << threshold << std::endl;
//
//         auto measure = [](std::string label, auto sortFunc, std::vector<int> array) {
//             long long time = measureTime(sortFunc, array);
//             std::cout << label << ": " << time << " ns" << std::endl;
//         };
//
//         measure("Merge Sort (Random)",
//                 [](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); },
//                 randomArray);
//
//         measure("Hybrid Sort (Random)",
//                 [threshold](std::vector<int>& arr) { hybridMergeSort(arr, 0, arr.size() - 1, threshold); },
//                 randomArray);
//
//         measure("Merge Sort (Reversed)",
//                 [](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); },
//                 reversedArray);
//
//         measure("Hybrid Sort (Reversed)",
//                 [threshold](std::vector<int>& arr) { hybridMergeSort(arr, 0, arr.size() - 1, threshold); },
//                 reversedArray);
//
//         measure("Merge Sort (Nearly Sorted)",
//                 [](std::vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); },
//                 nearlySortedArray);
//
//         measure("Hybrid Sort (Nearly Sorted)",
//                 [threshold](std::vector<int>& arr) { hybridMergeSort(arr, 0, arr.size() - 1, threshold); },
//                 nearlySortedArray);
//
//         std::cout << "---------------------------------------------" << std::endl;
//     }
// };
//
// int main() {
//     int sizes[] = {500, 1000, 2000, 5000, 10000};
//     int thresholds[] = {5, 10, 20, 30, 50};
//
//     for (int size : sizes) {
//         for (int threshold : thresholds) {
//             SortTester::testSorts(size, threshold);
//         }
//     }
//
//     return 0;
// }
