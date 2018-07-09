#ifndef NOT_IMPLEMENTED_H
#define NOT_IMPLEMENTED_H

#include <stdexcept>
#include <string>

class NotImplemented : public std::logic_error {
   public:
    NotImplemented(const std::string &__arg = "Function not yet implemented")
        : std::logic_error(__arg){};
};

#endif
