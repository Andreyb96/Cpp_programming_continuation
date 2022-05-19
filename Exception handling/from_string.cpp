#include <string>
#include <sstream>
#include <typeinfo>
#include <exception>
#include <stdexcept>

class bad_from_string : public std::runtime_error {
public:
    explicit bad_from_string(const std::string& __arg) : std::runtime_error(__arg) {}
};


template<class T>
T from_string(const std::string& str) {
    if (str.empty()) {
        throw bad_from_string("ERROR: String is empty");
    }

    std::istringstream iss(str);
    T value;

    iss >> std::noskipws >> value;

    if (iss.fail()) {
        throw bad_from_string("ERROR: Invalid string \"" + str + "\" for type " + typeid(T).name() + ".");
    }

    if (iss.peek() != EOF) {
        throw bad_from_string("ERROR: String \"" + str + "\" wasn't completely read(EOF wasn't reached).");
    }

    return value;
}