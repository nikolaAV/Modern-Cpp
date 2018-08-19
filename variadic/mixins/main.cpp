#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

namespace fw // framework
{

template<typename... Mixins>
class Point : public Mixins...
{
   double x_{0}, y_{0};
public:
   Point() = default;
   Point(double x, double y) : x_{x}, y_{y} {}
   double getx() const noexcept { return x_; }
   double gety() const noexcept { return y_; }
   // ...
};

template <typename... Mixins>
ostream& operator << (ostream& out, const Point<Mixins...>& p){
   return out << "{" << p.getx() << "," << p.gety() << "}";
}

template <typename P>
class Polygon
{
   vector<P> points_;   
public:
   P& operator +=(const P& p) {
      points_.push_back(p);
      return points_.back();
   }
   template <typename F>
   void for_each(F f) {
      for(auto&& p:points_) 
         f(p);
   }
   void draw() {
      for_each([](const P& p) {cout << p << " "; });
      cout << endl;
   }
};

}  // namespace fw, framework

// ------- user-defined "points" -----------

class Label
{
   string label_{"unlabeled"};
public:
   Label() = default;
   void           setlabel(const char* l)   {label_=l;}
   const string&  getlabel() const noexcept { return label_;}
};

class Color
{                        //     red           green       blue
   using rgb_type = tuple<unsigned char,unsigned char,unsigned char>;
   rgb_type rgb_ {0,0,0};
public:
   Color() = default;
   void  setrgb(const rgb_type& rgb) noexcept { rgb_ = rgb; }
   auto  getrgb() const noexcept     { return rgb_;}
};

int main()
{
   using namespace fw;

   {  // client1 uses a pure points 
      Polygon<Point<>> p;
      p += {0,0};
      p += {1,2};
      p += {1,4};
      // ...
      p.draw();
   }

   {  // client2 uses labeled points 
      Polygon<Point<Label>> p;
      (p += {0,0}).setlabel("l1");
      (p += {1,2}).setlabel("l2");
      (p += {1,4}).setlabel("l3");
      // ...
      p.draw();
      p.for_each([](auto&& e){
         cout << e.getlabel().c_str() << ", ";
      });
      cout << endl;
   }

   {  // client3 uses coloured points 
      Polygon<Point<Color>> p;
      (p += {0,0}).setrgb({255,255,255});
      (p += {1,2}).setrgb({127,128,129});
      (p += {1,4}).setrgb({1,127,254});
      // ...
      p.draw();
      p.for_each([](auto&& e){
         const auto [r,g,b] = e.getrgb();
         cout << "{" << (int)r << "," << (int)g << "," << (int)b << ",}"; 
      });
      cout << endl;
   }

   {  // client4 uses coloured and labeled points 
      Polygon<Point<Color,Label>> p;
      auto& p1 = p += {0,0};
            p1.setrgb({255,255,255});
            p1.setlabel("l1");
      auto& p2 = p += {1,2};
            p2.setrgb({127,128,129});
            p2.setlabel("l2");
      auto& p3 = p += {1,4};
            p3.setrgb({1,127,254});
            p3.setlabel("l3");
      // ...
      p.draw();
      p.for_each([](auto&& e){
         const auto [r,g,b] = e.getrgb();
         cout << e.getlabel().c_str() << "{" << (int)r << "," << (int)g << "," << (int)b << ",}; "; 
      });
      cout << endl;
   }
}