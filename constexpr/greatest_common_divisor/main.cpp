/**
   Euclidean greatest common divisor for more than two numbers at compile time
   Solution:
   The GCD of three or more numbers equals the product of the prime factors common to all the numbers,
   but it can also be calculated by repeatedly taking the GCDs of pairs of numbers.

   \see https://math.stackexchange.com/questions/1672249/greatest-common-divisor-of-more-than-two-numbers
*/

 #include <numeric>

template <typename T>
constexpr auto gcd(T m, T n)
{
   return std::gcd(m,n);
}

template <typename T, typename... U>
constexpr auto gcd(T m, U... ns)
{
   return gcd(m,gcd(ns...));
}

int main()
{
  static_assert(8==gcd(48,16,24,96));
  static_assert(1==gcd(1,2,3));
  static_assert(2==gcd(8,6,4,2,10,12,100));
}
