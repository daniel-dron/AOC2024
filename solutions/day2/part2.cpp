#include <algorithm>
#include <fstream>
#include <span>
#include <string>
#include <vector>
#include <sstream>

bool is_report_safe_basic(std::span<const int> report) {
    if (report.size() < 2) return false;
    
    const bool is_decreasing = report[0] > report[1];
    
    return std::adjacent_find(report.begin(), report.end(), 
        [is_decreasing](int a, int b) {
            const auto diff = a - b;
            return diff == 0 || std::abs(diff) > 3 || is_decreasing != (diff > 0);
        }) == report.end();
}

bool is_report_safe(const std::vector<int>& report) {
    if (is_report_safe_basic(report)) {
        return true;
    }
    
    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modified_report;
        modified_report.reserve(report.size() - 1);
        
        for (size_t j = 0; j < report.size(); ++j) {
            if (j != i) {
                modified_report.push_back(report[j]);
            }
        }
        
        if (is_report_safe_basic(modified_report)) {
            return true;
        }
    }
    
    return false;
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