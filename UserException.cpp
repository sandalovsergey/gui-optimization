#include "UserException.h"

char* DiffSizeException::what() {
    return "Different size exception";
}

int DiffSizeException::getErrorCode() const {
    return errorCode;
}

char* DomainException::what() {
    return "Domain exception";
}

int DomainException::getErrorCode() const {
    return errorCode;
}

char* OutOfBoundException::what() {
    return "Out of bound exception";
}

int OutOfBoundException::getErrorCode() const {
    return errorCode;
}

char* IncompatiblePointException::what() {
    return "Incompatible point exception";
}

int IncompatiblePointException::getErrorCode() const {
    return errorCode;
}


char* AddPointException::what() {
    return "Add point exception";
}

int AddPointException::getErrorCode() const {
    return errorCode;
}
