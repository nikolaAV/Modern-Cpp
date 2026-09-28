#include <cassert>
#include <concepts>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

/**
 * @brief Checks whether a type supports obtaining its iterator range.
 * @tparam T The type to check.
 *
 * The expression must support both `std::begin` and `std::end` for an lvalue
 * of type `T`.
 */
template <typename T>
concept Range = requires(T& range) {
    std::begin(range);
    std::end(range);
};

/**
 * @brief Checks whether a value of type `U` can be assigned to an lvalue of type `T`.
 * @tparam T The type of the assignment target.
 * @tparam U The type of the value assigned to the target.
 */
template <typename T, typename U>
concept Assignable = requires(T& left, U right) {
    left = right;
};

/**
 * @brief Checks whether elements of a range can be assigned to a value of type `U`.
 * @tparam R The range type.
 * @tparam U The type of the assignment target.
 *
 * The element expression is obtained from a constant lvalue of type `R`.
 */
template <typename R, typename U>
concept ElementAssignableTo = Range<R> && requires(R const& range) {
    requires Assignable<U, decltype(*std::begin(range))>;
};

/**
 * @brief Returns the sum of the elements in a range, starting with an initial value.
 * @tparam R The range type.
 * @tparam U The accumulator and result type.
 * @param range The range whose elements are accumulated.
 * @param init The initial accumulator value.
 * @return The result of accumulating the range elements into `init`.
 */
template <Range R, typename U>
    requires ElementAssignableTo<R, U>
U accumulate(R const& range, U init) {
    return std::accumulate(std::begin(range), std::end(range), init);
}

int main() {
    const std::vector values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const std::set ordered_values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    assert(accumulate(values, 0) == 45);
    assert(accumulate(ordered_values, 0.f) == 45.f);
}