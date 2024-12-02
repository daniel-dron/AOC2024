# Day 1

## Part 1

Given:

![equation](https://latex.codecogs.com/svg.image?L=%5Cbegin%7Bbmatrix%7Dx_1&x_2&x_3&...&x_n%5C%5C%5Cend%7Bbmatrix%7D)

![equation](https://latex.codecogs.com/svg.image?R=%5Cbegin%7Bbmatrix%7Dy_1&y_2&y_3&...&y_n%5C%5C%5Cend%7Bbmatrix%7D)

and `L = sort(L), R = sort(R)`

we can solve day 1 part 1 with:

![equation](https://latex.codecogs.com/svg.image?%5Csum_%7Bi=1%7D%5E%7Bn%7D(%5Cleft%7Cx_i-y_i%5Cright%7C))

```c++
std::sort(left.begin(), left.end());
std::sort(right.begin(), right.end());

int distance = {};
for(const auto [l, r] : std::views::zip(left, right)) {
    distance += std::abs(l - r);
}
```

## Part 2

![equation](https://latex.codecogs.com/svg.image?L=%5Cbegin%7Bbmatrix%7Dx_1&x_2&x_3&...&x_n%5C%5C%5Cend%7Bbmatrix%7D)

![equation](https://latex.codecogs.com/svg.image?R=%5Cbegin%7Bbmatrix%7Dy_1&y_2&y_3&...&y_n%5C%5C%5Cend%7Bbmatrix%7D)

and `L = sort(L), R = sort(R)`

we can solve day 1 part 2 with:

![equation](https://latex.codecogs.com/svg.image?%5Csum_%7Bi=1%7D%5E%7Bn%7D(x_i*%5Cleft%7C%5Cleft%5C%7Br%5Cin%20R:r=x_i%5Cright%5C%7D%5Cright%7C))

An optimization can be done in code by caching the value from the last summation iteration to reuse incase `l` is the same.

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