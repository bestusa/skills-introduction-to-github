#include <iostream>
#include <random>
#include <vector>

struct SearchResult {
    bool found;
    int index;
    long long comparisons;
};

SearchResult linearSearch(const std::vector<int>& data, int key) {
    SearchResult result{false, -1, 0};

    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
        result.comparisons++;
        if (data[i] == key) {
            result.found = true;
            result.index = i;
            return result;
        }
    }

    return result;
}

SearchResult binarySearch(const std::vector<int>& data, int key) {
    SearchResult result{false, -1, 0};
    int left = 0;
    int right = static_cast<int>(data.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        result.comparisons++;
        if (data[mid] == key) {
            result.found = true;
            result.index = mid;
            return result;
        }

        result.comparisons++;
        if (data[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

SearchResult randomizedSearch(const std::vector<int>& data, int key, std::mt19937& rng) {
    SearchResult result{false, -1, 0};
    const int n = static_cast<int>(data.size());

    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) {
        indices[i] = i;
    }

    // Fisher-Yates shuffle to visit each index at most once.
    for (int i = n - 1; i > 0; --i) {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(rng);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int pos = 0; pos < n; ++pos) {
        int idx = indices[pos];
        result.comparisons++;
        if (data[idx] == key) {
            result.found = true;
            result.index = idx;
            return result;
        }
    }

    return result;
}

void printResult(const char* name, const SearchResult& result) {
    std::cout << name << '\n';
    std::cout << "  Found: " << (result.found ? "yes" : "no") << '\n';
    std::cout << "  Index: " << result.index << '\n';
    std::cout << "  Comparisons: " << result.comparisons << "\n\n";
}

int main() {
    const int N = 100000;
    std::vector<int> data(N);
    for (int i = 0; i < N; ++i) {
        data[i] = i + 1;
    }

    int key;
    std::cout << "Dataset contains integers 1.." << N << ".\n";
    std::cout << "Enter key to search: ";
    std::cin >> key;

    std::random_device rd;
    std::mt19937 rng(rd());

    SearchResult linear = linearSearch(data, key);
    SearchResult binary = binarySearch(data, key);
    SearchResult random = randomizedSearch(data, key, rng);

    std::cout << "\nSearch results for key " << key << ":\n\n";
    printResult("Linear search", linear);
    printResult("Binary search", binary);
    printResult("Randomized search (without repetition)", random);

    return 0;
}
