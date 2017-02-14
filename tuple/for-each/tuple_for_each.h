#ifndef _TUPLE_FOR_EACH_H__
#define _TUPLE_FOR_EACH_H__

#include <tuple>
#include <utility>

namespace tuple_
{
    /**
        Variant 1
        enumerating elements in a tuple by means overloaded function template 
        
        \see http://cpplove.blogspot.com/2012/07/printing-tuples.html
   */
    namespace v1
    {
        template<std::size_t> struct int_type {};

        template <typename TUPLE_T, typename UnaryFunction, size_t TUPLE_ARG_REVERSE_POS>
        void visit(const TUPLE_T& t, UnaryFunction& f, int_type<TUPLE_ARG_REVERSE_POS>)
        {
            f(std::get<std::tuple_size<TUPLE_T>::value - TUPLE_ARG_REVERSE_POS>(t));
            visit(t, f, int_type<TUPLE_ARG_REVERSE_POS - 1>{});
        }

        template <typename TUPLE_T, typename UnaryFunction>
        void visit(const TUPLE_T& t, UnaryFunction& f, int_type<1>)
        {
            f(std::get<std::tuple_size<TUPLE_T>::value - 1>(t));
        }

        template <typename UnaryFunction, typename... Args>
        // requires C++0x concept::FunctionObject<UnaryFunction>, see http://en.cppreference.com/w/cpp/concept/FunctionObject
        // with only argument of any type: template <typename T> UnaryFunction::operator()(const T& arg) {...}
        UnaryFunction for_each(const std::tuple<Args...> t, UnaryFunction f)
        {
            visit(t, f, int_type<sizeof...(Args)>());
            return std::move(f);
        }

    } // namespace: v1


      /**
          Variant 2
          enumerating elements in a tuple by means partial specialization class template

          \see https://books.google.com.ua/books?id=9DEJKhasp7gC&pg=PA74&lpg=PA74&dq=I/O+for+Tuples+Chapter+5:+Utilities&source=bl&ots=_a2eJ5LwSI&sig=GmtHoo_u9a53dYxJHL3NwbW81ms&hl=en&sa=X&ved=0ahUKEwiGzOmlkY_SAhULr1QKHd1JDw4Q6AEIGjAA#v=onepage&q=I%2FO%20for%20Tuples%20Chapter%205%3A%20Utilities&f=false
      */
    namespace v2
    {
        /**
            helper: call callable object 'f' for an element with index IDX of tuple with MAX elements

            \param t - std::tuple<Args...>
            \param f - function object, to be applied to the every element in the tuple<Args...> [ArgFirst,...ArgLast]
                The signature of the function should be equivalent to the following:
                template <typename ArgType> func(ArgType&);
        */

        template <size_t IDX, size_t MAX, typename... Args>
        struct visitor
        {
            template<typename UnaryFunction>
            static void accept(const std::tuple<Args...>& t, UnaryFunction& f)
            { 
                f(std::get<IDX>(t)); 
                visitor<IDX+1,MAX,Args...>::accept(t,f);
            }
        };

        // partial specialization to end the recursion
        template <size_t MAX, typename... Args>
        struct visitor<MAX,MAX,Args...>
        {
            template<typename UnaryFunction>
            static void accept(const std::tuple<Args...>&, UnaryFunction& f) {}
        };

        template <typename UnaryFunction, typename... Args>
        UnaryFunction for_each(const std::tuple<Args...> t, UnaryFunction f)
        {
            visitor<0,sizeof...(Args),Args...>::accept(t,f);
            return std::move(f);
        }

    } // namespace: v2

} // namespace: tuple_


#endif // _TUPLE_FOR_EACH_H__
