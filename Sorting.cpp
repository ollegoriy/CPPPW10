#include <iostream>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& arr) {
        if (arr.size() <= 1) return;
        vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        vector<int> right(arr.begin() + arr.size() / 2, arr.end());

        thread leftThread(&MergeSort::Sort, this, ref(left));
        thread rightThread(&MergeSort::Sort, this, ref(right));

        leftThread.join();
        rightThread.join();

        Merge(arr, left, right);
    }

private:
    void Merge(vector<int>& arr, const vector<int>& left, const vector<int>& right) {
        auto a = left.begin();
        auto b = right.begin();
        auto c = arr.begin();

        while (a != left.end() && b != right.end()) {
            if (*a <= *b) {
                *c++ = *a++;
            }
            else {
                *c++ = *b++;
            }
        }

        while (a != left.end()) {
            *c++ = *a++;
        }

        while (b != right.end()) {
            *c++ = *b++;
        }
    }
};

int main() 
{
    setlocale(LC_ALL, "ru");

    vector<int> arr(10);

    cout << "Введите 10 целых чисел для сортировки: ";
    for (int i = 0; i < 10; ++i) {
        cin >> arr[i];
    }

    MergeSort sorter;

    auto sortFunction = [&sorter](vector<int>& array) {
        sorter.Sort(array);
        };

    thread mergeSortThread(sortFunction, ref(arr));
    mergeSortThread.join();

    cout << "Отсортированный массив: ";
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
