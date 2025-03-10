#include <iostream>
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>
#include <stdexcept>


/**
 * @brief 
 * 
 * @param target сумма, которую ищем
 * @param nums отсортированный массив 
 * @return массив элементов сумма которых равна target  
 */
std::vector<int> two_sum(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while(left < right) {
        int sum = nums[left] + nums[right];
        if (sum == target)
            return std::vector<int>({nums[left], nums[right]});
        else if (sum < target)
            left++;
        else if (sum > target)
            right++;
    }
}

/**
 * @brief развернуть массив
 * 
 * @param nums упорядоченный массив
 * @param idx_left номер элемента, с которого нужно развернуть
 * @param idx_right номер элемента, по который нужно развернуть
 */
void reverse_array(std::vector<int>& nums, int idx_left = 0, int idx_right = 0) {
    int left = 0;
    int right = nums.size() - 1;

    while(left < right) {
        std::swap(nums[left], nums[right]);
        left++;
        right--;
    }
}

/**
 * @brief Необходимо развернуть справа налево
 * часть массива, которая указана вторым параметром.
 * 
 * @example 1, 2, 3, 4, 5, 6, 7 -> 5, 6, 7, 1, 2, 3, 4
 * @param nums упорядоченный массив
 * @param k индекс "разворотного" элемента. Если k больше nums.size() -- ошибка
 * так как пользователю надо больше ответственности. 
 */
void reverse_part_array(std::vector<int>& nums, int k) {
    if (k > nums.size())
        throw std::invalid_argument("k is more than nums.size()");

    reverse_array(nums, 0, nums.size() - 1);
    reverse_array(nums, 0, k - 1);
    reverse_array(nums, k, nums.size() - 1);
}

/**
 * @brief функция, которая объединит эти два массива
 * в один отсортированный. (доп аллокация)
 * 
 * @param nums1 отсортированный массив 1
 * @param nums2 отсортированный массив 2
 * @return единый массив
 */
std::vector<int> merge_sorted_arrays(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    std::vector<int> result;
    int i = 0;
    int j = 0;

    while(i < nums1.size() && j < nums2.size()) {
        if (nums1[i] < nums2[j]) {
            result.push_back(nums1[i]);
            i++;
        } else if (nums1[i] == nums2[j]) {
            result.push_back(nums1[i]);
            i++;
            j++;
        } else {
            result.push_back(nums2[j]);
            j++;
        }
    }

    for(int idx = i; idx < nums1.size(); idx++)
        result.push_back(nums1[idx]);
    for(int idx = j; idx < nums2.size(); idx++)
        result.push_back(nums2[idx]);

    return result;
}

void merge_sorted_arrays_without_allocs(std::vector<int>& nums1, std::vector<int>& nums2) {
    int i = nums1.size() - 1;
    int j = nums2.size() - 1;

    for (int idx = 0; idx < nums2.size(); idx++)
        nums1.push_back(0);

    int k = nums1.size() - 1; // size уже измен и равен nums1.size() + nums2.size()

    while (j > -1) {
        if (i > -1 && nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
}

void sort_01_array(std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;

    while(left < right) {
        if (arr[left] == 0)
            left++;
        else if (arr[right] == 1)
            right--;
        else {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
}

void flag_Nederland(std::vector<int>& arr) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;

    while(mid >= high) {
        if (arr[mid] == 0) {
            std::swap(arr[mid], arr[low]);
            mid++;
            low++;
        } else if (arr[mid] == 1) {
            mid++;
        } else if (arr[mid] == 2) {
            std::swap(arr[mid], arr[high]);
            high--;
            // не mid++ потому что на его место может прийти как 0, так и 1
        }
    }
}

void shift_even_num(std::vector<int>& arr) {
    int even_idx = 0;
    for(auto& i : arr) {
        if (i % 2 == 0) {
            std::swap(i, arr[even_idx]);
            even_idx++;
        }
    }
}

void zero_end(std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;

    while(left < right) {
        if (arr[left] == 0){
            std::swap(arr[left], arr[right]);
            if (arr[left] != 0) // остаемся на месте если на место лефта пришел ноль
                left++;
            right--;
        } else
            left ++;
    }
}

int main() {

    std::vector<int> r1 = {1,7,8} ;
    std::vector<int> r2 = {3, 0, 8, 0, 0, 11, 12};
    std::vector<int> io = {1, 0, 0, 0, 1, 1};
    zero_end(r2);
    for (auto i : r2)
        std::cout << i << " ";

    return 0;
}