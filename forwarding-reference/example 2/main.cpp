#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class Letter
{
    using long_data = vector<int>;

    long_data   content_;
    size_t      stamp_ = 0;
    size_t      exemplarNo_= 0;

    Letter()                  : content_(1000), exemplarNo_(1)
        {
            cout << "Letter default ctor" << endl;
        }
    Letter(const Letter& rhd) : content_(rhd.content_),  stamp_(rhd.stamp_), exemplarNo_(rhd.exemplarNo_+1)
        {
            cout << "Letter copy ctor" << endl;
        }
    Letter& operator=(const Letter& rhd)
        {
            Letter tmp(rhd);
            this->swap(tmp);
            return *this;
        }

    void swap(Letter& rhd) noexcept
        {
            content_.swap(rhd.content_);
            std::swap(stamp_,rhd.stamp_);
            std::swap(exemplarNo_,rhd.exemplarNo_);
        }

    Letter(Letter&&) = delete;
    Letter& operator=(Letter&&) = delete;

friend class Envelope;
friend ostream& operator<<(ostream&, const Letter&);
};

ostream& operator<<(ostream& out, const Letter& l)
{
    out << "stamp: " << l.stamp_ << ", exemplarNo: " << l.exemplarNo_;
    return out;
}

class Envelope
{
    unique_ptr<Letter>  body_;

public:
    Envelope() : body_(new Letter{}) {}
    Envelope(const Envelope& rhd) : body_(new Letter(*rhd.body_)) {}
    Envelope(Envelope&& rhd) noexcept : body_() { body_.reset(rhd.body_.release()); }
    Envelope& operator=(const Envelope& rhd) noexcept
        {
            Envelope copy {rhd};
            this->swap(copy);
            return *this;
        }
    Envelope& operator=(Envelope&& rhd) noexcept
        {
            this->swap(rhd);
            return *this;
        }
    void swap(Envelope& rhd) noexcept { body_.swap(rhd.body_); }

    size_t  stamp() const   { return body_->stamp_; }
    void    stamp(size_t n) { body_->stamp_ = n; }

friend ostream& operator<<(ostream&, const Envelope&);
};

ostream& operator<<(ostream& out, const Envelope& e)
{
    out << *e.body_;
    return out;
}

class Postman
{
    using bag = vector<Envelope>;
    bag     letters     = {};
    size_t  letterNo_   = 100;

public:
/*
    void deliver(const Envelope& e)
    {
        Envelope copy {e};
        copy.stamp(++letterNo_);
        letters.push_back(copy);
        cout << "[Postman] Envelope("  << letters.back() << ") was sent" << endl;
    }

    void deliver(Envelope&& e)
    {
        Envelope copy {std::move(e)};
        copy.stamp(++letterNo_);
        letters.push_back(std::move(copy));
        cout << "[Postman] Envelope("  << letters.back() << ") was sent" << endl;
    }
*/
    template <typename EnvelopeT>
    void deliver_generic(EnvelopeT&& e)
    {
        Envelope copy {std::forward<EnvelopeT>(e)};
        copy.stamp(++letterNo_);
        letters.push_back(std::forward<EnvelopeT>(copy));
        cout << "[Postman] Envelope("  << letters.back() << ") was sent" << endl;
    }
};


int main(int /*argc*/, char** /*argv[]*/)
{
    Postman     ps;
/*
    {
        cout << "--- test1: copy semantics ---" << endl;
        Envelope letter;
        ps.deliver(letter); // a copy will be sent
        // original variable 'letter' is used here ...
    }

    {
        cout << "--- test2: move semantics detected by compiler ---" << endl;
        ps.deliver(Envelope{}); // unnamed exemplar, it can be moved without apprehension
    }

    {
        cout << "--- test3: move semantics forced programmatically ---" << endl;
        Envelope letter;
        ps.deliver(std::move(letter));
        // a programmer takes the responsibility for "letter is no more used"
    }
*/
    {
        cout << "--- test4: copy + move semantics implemented as generic with detection at call point ---" << endl;
        Envelope letter;
        ps.deliver_generic(letter); // copying, because of 'letter' can be used later

        ps.deliver_generic(Envelope{}); // no doubt, unnamed temporary object can be moved safely

        ps.deliver_generic(std::move(letter)); // no instruction below, 'letter' cannot be used later
    }


    cout << "Press any key + <enter> to exit" << endl;
    cin.get();
    return 0;
}
