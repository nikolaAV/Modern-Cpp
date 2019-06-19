#include <iostream>
#include <variant>
#include <string>

/**
   How about modelling a state machine with std::variant? For example door’s state:
   \see https://www.bfilipek.com/2018/06/variant.html
        https://www.youtube.com/watch?v=ojZbFIQSdl8

*/

namespace state
{
   struct opened {};
   struct closed {};
   struct locked {};
   using  type = std::variant<opened, closed, locked>;
}  // end of namespace state

namespace event
{
   struct do_nothing {
      template <typename T>
      state::type operator()(T) const noexcept(noexcept(T{})){ return T{}; }
   };

   /**
      Table of allowed transitions
      ------------------------------------
      Current State  Event    Target State   
      ------------------------------------
      opened         close    closed
      closed         open     opened
      closed         lock     locked
      locked         unlock   closed
   */

   struct open : do_nothing {
      using do_nothing::operator();
      state::type operator()(state::closed) const noexcept { return state::opened{}; }
   };

   struct close : do_nothing {
      using do_nothing::operator();
      state::type operator()(state::opened) const noexcept { return state::closed{}; }
   };

   struct lock : do_nothing {
      using do_nothing::operator();
      state::type operator()(state::closed) const noexcept { return state::locked{}; }
   };

   struct unlock : do_nothing {
      using do_nothing::operator();
      state::type operator()(state::locked) const noexcept { return state::closed{}; }
   };

   struct unknown : do_nothing {
      using do_nothing::operator();
   };
}  // end of namespace event

using namespace std;

// https://github.com/nikolaAV/Modern-Cpp/tree/master/lambda/lambda_overloaded
template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...)->overloaded<Ts...>;

std::ostream& operator<<(std::ostream& out, const state::type& s) {
   std::visit(overloaded{
          [&](const state::opened&) { out << "state::opened"; }
         ,[&](const state::closed&) { out << "state::closed"; }
         ,[&](const state::locked&) { out << "state::locked"; }
      }, s);
   return out;
}

int main()
{
   string input;
   state::type s;
   for (;;) {
      cout << "--> " << s << endl;
      cout << "enter an event (or exit) you want to send: ";
      cin >> input;

      if("exit"==input)
         return 0;
      if("close"==input)
         s = visit(event::close{},s);
      else if("open" == input)
         s = visit(event::open{},s);
      else if ("lock" == input)
         s = visit(event::lock{},s);
      else if ("unlock" == input)
         s = visit(event::unlock {},s);
      else
         s = visit(event::unknown{},s);
   }
}
