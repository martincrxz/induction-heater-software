/*
 * Created by Federico Manuel Gomez Peter
 * on 05/09/18.
 */

#include <cstdarg>
#include <sstream>
#include <string>

#include "exception.h"
/**
 * @param fmt = Formato al cual completar
 * @param ... = argumentos para completar fmt
 */
Exception::Exception(const char *fmt, ...) noexcept {
    va_list args, args_copy;
    va_start(args, fmt);
    va_copy(args_copy, args);

    try {
        std::size_t size = std::vsnprintf(nullptr, 0, fmt, args) + 1;

        this->msg_error.reserve(size);
        std::vsnprintf(&this->msg_error.front(), size, fmt, args_copy);

        va_end(args_copy);
        va_end(args);
    } catch (...) {
        va_end(args_copy);
        va_end(args);
    }
}

const char *Exception::what() const noexcept {
    return this->msg_error.c_str();
}
