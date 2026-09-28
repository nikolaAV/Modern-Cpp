#include <cassert>
#include <concepts>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

/**
 * @brief Returns the sum of the elements in a range, starting with an initial value.
 * @tparam R The range type.
 * @tparam U The accumulator and result type.
 * @param range The range whose elements are accumulated.
 * @param init The initial accumulator value.
 * @return The result of accumulating the range elements into `init`.
 */
template <typename R, typename U>
    requires std::ranges::input_range<const R> &&
             std::assignable_from<U&, std::ranges::range_reference_t<const R>>
U accumulate(const R& range, U init) {
    return std::accumulate(std::ranges::begin(range), std::ranges::end(range), init);
}

int main() {
    const std::vector values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::set ordered_values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    assert(accumulate(values, 0) == 45);
    assert(accumulate(ordered_values, 0.f) == 45.f);
}
