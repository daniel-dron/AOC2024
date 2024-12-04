# Day 1

## Part 1

Given:

$$ L = \begin{bmatrix} x_1 & x_2 & x_3 & ... & x_n \end{bmatrix}  $$
$$ R = \begin{bmatrix} y_1 & y_2 & y_3 & ... & y_n \end{bmatrix}  $$

where L are the numbers on the left, and R are the numbers on the right

$$ L = sort(L) $$
$$ R = sort(R) $$

we can solve day 1 part 1 with:

$$\sum_{i = 1}^{n}(\left| x_i - y_i\right|)$$

<details>
<summary>Code (c++)</summary>

```c++
std::sort(left.begin(), left.end());
std::sort(right.begin(), right.end());

int distance = {};
for(const auto [l, r] : std::views::zip(left, right)) {
    distance += std::abs(l - r);
}
```
</details>

## Part 2

Given:

$$ L = \begin{bmatrix} x_1 & x_2 & x_3 & ... & x_n \end{bmatrix}  $$
$$ R = \begin{bmatrix} y_1 & y_2 & y_3 & ... & y_n \end{bmatrix}  $$

where L are the numbers on the left, and R are the numbers on the right, we can solve day 1 part 2 with:

$$ \sum_{i = 1}^{n} (x_i * \left| \lbrace r \in R : r = x_i \rbrace \right|) $$

An optimization can be done in code, using sorted L and R, by caching the value from the last summation iteration to reuse its contribution to the total sum, incase $x_i$ is the same.

<details>
<summary>Code (c++)</summary>
    
```c++
int sum = {};

int last_l = 0;
int last_s = 0;
for (auto l : left) {
    if (l == last_l) {
        sum += last_s;
    }

    last_l = l;

    int count = std::ranges::count(right, l);
    last_s = l * count;

    sum += last_s;
}
```
</details>

# Day 2

## Part 1

Given a report as a sequence S:

$$ S = \begin{pmatrix} s_1 & s_2 & s_3 & ... & s_n \\ \end{pmatrix} $$

a report is safe if and only if:

$$
Safe(S) =
\begin{cases}
1 & \text{if\ } \forall i \in [1, n-1] : (0 < \left| s_i - s_{i+1} \right| <= 3) \wedge  (sign(s_1 - s_2) = sign(s_i - s_{i+1}))), \\
0 & \text{otherwise}.
\end{cases}
$$

then, given a set of reports R, we can find the count of safe reports with:

$$ \sum_{s \in R} \text{Safe}(S)  $$

<details>
<summary>Code (c++)</summary>

I tried implementing it using a bit of functional modern c++. In the repo above, you can find a better optimized solution.
```c++
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
    std::ifstream file("day2.txt");
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
```
</details>


## Part 2

Building on Part 1, the definition of a report sequence and Safe(S) remain identical.

To account for the Problem Dampener safety check, a report is then Dampened Safe if and only if:

$$
DSafe(S) =
\begin{cases}
1 & \text{if\ } Safe(S), \\
1 & \text{if\ }, \exists j \in \left [ 1, n \right ] : Safe(S_{(j)})\\
0 & \text{otherwise}.
\end{cases}
$$

where,

$$ S_{(j)} = (x_i : i \in \left [ 1, n \right ] : i \neq j ) $$

So, given a set of reports R, we can find the count of safe reports with:

$$ \sum_{s \in R} DSafe(S)  $$

# Day 3

## Part 1

This one is a lot more complex due to being filled with imperative logic. I still tried my best, but I would be surprised if there wasn't 1001 things that could be done better.

Let M(i) be the function that checks and parses for mul(x, y):

$$
M(i) =
\begin{cases}
1 & \text{if\ } S[i, i+4] = "mul(" \ \wedge \\
& S[j] = "," \ \wedge \\
& S[k] = ")" \ \wedge \\
& \exists x, y \in [0, 999] \ \wedge \\
& \exists i, j \in [i+4, n-1] \ \text{where}\\
& \quad S[i+4, j] \  \text{matches} [0, 9]\{1, 3\}(x) \ \wedge \\
& \quad S[j + 1, k] \  \text{matches} [0, 9]\{1, 3\}(y) \ \wedge \\
0 & \text{otherwise}.
\end{cases}
$$

Then we can find the solution with:

$$ \sum_{i = 0}^{n}M(i) $$

where n is the length of characters in memory S.