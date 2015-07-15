#ifndef PHONE_NUMBER_PHONE_NUMBER_H
#define PHONE_NUMBER_PHONE_NUMBER_H

#include <string>
#include <boost/format.hpp>

using namespace std;

class phone_number {
   public:
    phone_number(const string number);
    string number() const;
    string area_code() const;

    explicit operator string() const;

   private:
    string number_;
};

#endif  // PHONE_NUMBER_PHONE_NUMBER_H
