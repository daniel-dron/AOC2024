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
