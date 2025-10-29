#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
using namespace std;

class MergeSort {
public:
    // Merge Sort cơ bản
    static void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            
            mergeSor