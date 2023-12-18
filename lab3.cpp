#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>
#define SIZE 10000
using namespace std;

struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats insertion_sort(vector<int>& arr)
{
    size_t n = arr.size();
    stats statics;
    for (size_t i = 1; i < n; ++i)
    {
        for (size_t j = i; j > 0; --j)
        {
            ++statics.comparison_count;
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
                ++statics.copy_count;
            }
            else
                break;
        }
    }
    return statics;
}

void quick_sort(vector<int>& arr, int left, int right, stats& s)
{
    int i = left, j = right;
    int main = arr[left];
    while (i <= j)
    {
        while (arr[i] < main)
        {
            s.comparison_count++;
            i++;
        }
        while (arr[j] > main)
        {
            s.comparison_count++;
            j--;
        }
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
            s.copy_count++;
        }
    }

    if (left < j)
        quick_sort(arr, left, j, s);
    if (i < right)
        quick_sort(arr, i, right, s);
}

stats quick_sort(vector<int>& arr, int size)
{
    stats statistics;
    if (size < 2)
    {
        return statistics;
    }
    quick_sort(arr, 0, size - 1, statistics);
    return statistics;
}

stats merge(vector<int>& arr, vector<int>& left, vector<int>& right, stats& statistics)
{
    size_t left_size = left.size();
    size_t right_size = right.size();
    size_t i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size)
    {
        statistics.comparison_count++;
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            ++i;
        }
        else
        {
            arr[k] = right[j];
            ++j;
        }
        statistics.copy_count++;
        ++k;
    }
    while (i < left_size)
    {
        arr[k] = left[i];
        ++i;
        statistics.copy_count++;
        ++k;
    }

    while (j < right_size)
    {
        arr[k] = right[j];
        ++j;
        statistics.copy_count++;
        ++k;
    }
    return statistics;
}

stats merge_sort(vector<int>& arr)
{
    size_t size = arr.size();
    stats statistics;
    if (size < 2)
    {
        return statistics;
    }
    size_t mid = size / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    statistics = merge_sort(left);
    statistics = merge_sort(right);
    merge(arr, left, right, statistics);
    return statistics;
}

vector<int> normal_vector(int size)
{
    vector<int> arr;
    for (int i = 0; i < size; ++i)
    {
        arr.push_back(i);
    }
    return arr;
}

vector<int> reverse_vector(int size)
{
    vector<int> arr;
    for (int i = size - 1; i >= 0; --i)
    {
        arr.push_back(i);
    }
    return arr;
}

vector<int> random_vector(int size)
{
    vector<int> arr;
    for (int i = 0; i < size; ++i)
    {
        arr.push_back(rand() % 100);
    }
    return arr;
}

// Iterators

template <class Iterator>
stats insertion_sort(Iterator begin, Iterator end)
{
    stats statics;
    for (Iterator i = begin; i != end; ++i)
    {
        for (Iterator j = i; j != begin; --j)
        {
            ++statics.comparison_count;
            if (*j < *(j - 1))
            {
                swap(*j, *(j - 1));
                ++statics.copy_count;
            }
            else
                break;
        }
    }
    return statics;
}

template <class Iterator>
void quick_sort(Iterator begin, Iterator end, stats& s)
{
    if (distance(begin, end) < 2)
    {
        return;
    }
    Iterator i = begin;
    Iterator main = prev(end);
    Iterator pivot = next(begin, distance(begin, end) / 2);
    iter_swap(pivot, main);
    pivot = main;
    for (Iterator j = begin; j != main; ++j)
    {
        if (*j < *main)
        {
            if (*i != *j)
            {
                iter_swap(i, j);
                s.copy_count++;
            }
            ++i;
        }
        s.comparison_count++;
    }
    iter_swap(i, main);
    s.copy_count++;
    quick_sort(begin, i, s);
    quick_sort(next(i), end, s);
}
template <class Iterator>
void merge(Iterator begin, Iterator mid, Iterator end, stats& statistics) {
    vector<int> temp(distance(begin, end));
    auto left = begin;
    auto right = mid;
    auto tempIter = temp.begin();

    while (left < mid && right < end) {
        statistics.comparison_count++;
        if (*left <= *right) {
            *tempIter++ = *left++;
        }
        else {
            *tempIter++ = *right++;
        }
        statistics.copy_count++;
    }

    while (left < mid) {
        *tempIter++ = *left++;
        statistics.copy_count++;
    }

    while (right < end) {
        *tempIter++ = *right++;
        statistics.copy_count++;
    }

    copy(temp.begin(), temp.end(), begin);
}
template <class Iterator>
stats merge_sort(Iterator begin, Iterator end) {
    stats statistics;
    if (distance(begin, end) < 2) {
        return statistics;
    }

    auto mid = begin + distance(begin, end) / 2;
    statistics = merge_sort(begin, mid);
    statistics = merge_sort(mid, end);
    merge(begin, mid, end, statistics);
    return statistics;
}

template <class Iterator>
stats quick_sort(Iterator begin, Iterator end)
{
    stats statistics;
    if (distance(begin, end) < 2)
    {
        return statistics;
    }
    quick_sort(begin, end, statistics);
    return statistics;
}

vector<int> generate_random_vector(size_t n) {
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(rand() % 100);
    }
    return result;
}

vector<int> generate_sorted_vector(size_t n) {
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(i);
    }
    return result;
}

vector<int> generate_inverted_vector(size_t n) {
    vector<int> result;
    for (int i = n - 1; i >= 0; --i) {
        result.push_back(i);
    }
    return result;
}

int main() {
    //Insertion sort for 100 random arrays, 1 sorted and 1 inverted 
    {
        cout << "Insertion sort for 100 random arrays, 1 sorted and 1 inverted" << endl << endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            vector<int> arr = generate_random_vector(SIZE);
            stats tmp = insertion_sort(arr.begin(),arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        cout << "size: " << SIZE << endl;
        cout << "Average comparison quantity: " << sum_comparison / 100 << endl;
        cout << "Average copy quantity: " << sum_copy / 100 << endl << endl;

        vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = insertion_sort(sorted.begin(),sorted.end());
        cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << endl;
        cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << endl << endl;

        vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = insertion_sort(inverted.begin(),inverted.end());
        cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << endl;
        cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << endl << endl;
    }
    //Quick sort for 100 random arrays, 1 sorted and 1 inverted
    {
        cout << "Quick sort for 100 random arrays, 1 sorted and 1 inverted" << endl << endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {
            //cout << "Number of array: " << i << endl;
            vector<int> arr = generate_random_vector(SIZE);
            stats tmp = quick_sort(arr.begin(), arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        cout << "size: " << SIZE << endl;
        cout << "Average comparison quantity: " << sum_comparison / 100 << endl;
        cout << "Average copy quantity: " << sum_copy / 100 << endl << endl;

        vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = quick_sort(sorted.begin(), sorted.end());
        cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << endl;
        cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << endl << endl;

        vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = quick_sort(inverted.begin(), inverted.end());
        cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << endl;
        cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << endl << endl;
    }
    //Merge sort for 100 random arrays, 1 sorted and 1 inverted
    {
        cout << "Merge sort for 100 random arrays, 1 sorted and 1 inverted" << endl << endl;
        size_t sum_comparison = 0, sum_copy = 0;
        for (int i = 0; i < 100; ++i) {

            vector<int> arr = generate_random_vector(SIZE);
            stats tmp = merge_sort(arr.begin(),arr.end());
            sum_comparison += tmp.comparison_count;
            sum_copy += tmp.copy_count;
        }
        cout << "size: " << SIZE << endl;
        cout << "Average comparison quantity: " << sum_comparison / 100 << endl;
        cout << "Average copy quantity: " << sum_copy / 100 << endl << endl;

        vector<int> sorted = generate_sorted_vector(SIZE);
        stats sorted_stats = merge_sort(sorted.begin(), sorted.end());
        cout << "comparison quantity for sorted vector: " << sorted_stats.comparison_count << endl;
        cout << "copy quantity for sorted vector: " << sorted_stats.copy_count << endl << endl;

        vector<int> inverted = generate_inverted_vector(SIZE);
        stats inverted_stats = merge_sort(inverted.begin(), inverted.end());
        cout << "comparison quantity for inverted vector: " << inverted_stats.comparison_count << endl;
        cout << "copy quantity for inverted vector: " << inverted_stats.copy_count << endl << endl;
    }
    return 0;
}