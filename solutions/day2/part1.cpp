#include <algorithm>
#include <fstream>
#include <span>
#include <string>
#include <vector>
#include <sstream>

bool is_report_safe(std::span<const int> report) {
    if (report.size() < 2) return false;
    
    const bool is_decreasing = report[0] > report[1];
    
    return std::adjacent_find(report.begin(), report.end(), 
        [is_decreasing](int a, int b) {
            const auto diff = a - b;
            return diff == 0 || std::abs(diff) > 3 || is_decreasing != (diff > 0);
        }) == report.end();
}

int main() {
    std::ifstream file("data.txt");
    std::vector<std::vector<int>> reports;
    
    for (std::string line; std::getline(file, line);) {
        std::vector<int> nums;
        std::istringstream iss(line);
        for (int n; iss >> n;) {
            nums.push_back(n);
        }
        reports.push_back(std::move(nums));
    }
    
    const auto safe_count = std::count_if(reports.begin(), reports.end(),
        [](const auto& report) { return is_report_safe(report); });
    
    printf("safe: %ld\n", safe_count);
}

/*
This approach is technically better for memory reasons.
No allocations in a loop.
It has O(1) space instead of O(n) when it comes to storing the report values.
Might have better cache efficiency as each report line is not stored in a
different allocation.
And doesn't have memory constraints on the entire input (only per line, which
scales better) as the input is being read and parsed at the same time.

constexpr size_t MAX_NUMBERS = 100;

bool is_report_safe(const std::array<int, MAX_NUMBERS>& report, size_t size) {
    if (size < 2) return false;
    
    bool is_decreasing = report[0] > report[1];
    
    for (size_t i = 0; i < size - 1; i++) {
        int diff = report[i] - report[i + 1];
        
        if (diff == 0 || std::abs(diff) > 3) {
            return false;
        }
        
        if (is_decreasing != (diff > 0)) {
            return false;
        }
    }
    
    return true;
}

int main() {
    std::ifstream file("day2.txt");
    std::string line;
    int safe_count = 0;
    
    while (std::getline(file, line)) {
        std::array<int, MAX_NUMBERS> report{};
        std::istringstream iss(line);
        size_t size = 0;
        int num;
        
        while (iss >> num && size < MAX_NUMBERS) {
            report[size++] = num;
        }
        
        if (is_report_safe(report, size)) {
            safe_count++;
        }
    }
    
    std::printf("safe: %d\n", safe_count);
    return 0;
}
*/