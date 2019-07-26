/*
 * Created by Federico Manuel Gomez Peter
 * on 05/09/18.
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <exception>
#include <string>
/**
 * Recibe en su constructor un string con el formato (al estilo del formato
 * que recibe printf), y una cantidad indefinida de parámetros adicionales,
 * para agregarselos al esqueleto de fmt.
 */
class Exception : public std::exception {
 private:
    std::string msg_error;

 public:
    explicit Exception(const char* fmt, ...) noexcept;
    Exception() = delete;
    virtual const char* what() const noexcept;
    virtual ~Exception() noexcept = default;
};


#endif  // __EXCEPTION_H__
