#include <string>
#include <stdexcept>

namespace hamming {
    unsigned int compute(std::string a, std::string b) {

        if (a.length() != b.length()) {
            throw std::domain_error{"strings of different length"};
        }

        unsigned int differences = 0;
        for (auto i = 0; i < a.length(); i++) {
            if (a.at(i) != b.at(i)) {
                differences += 1;
            }
        }

        return differences;
    }
}
