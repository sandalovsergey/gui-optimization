#include "UserPoint.h"

/**
 * Class which describes different size exception
 */

class DiffSizeException : public exception {
public:
    /**
     * Get string message what happend
     * @return error message
     */
    char* what();

protected:
    int errorCode = -1;
public:
    int getErrorCode() const;
};


/**
 * Class which describes domain exception
 */

class DomainException : public exception {
public:
    /**
     * Get string message what happend
     * @return error message
     */
    char * what ();

protected:
    int errorCode = -2;
public:
    int getErrorCode() const;
};

/**
 * Class which describes out of bound exception
 */

class OutOfBoundException : public exception {
public:
    /**
     * Get string message what happend
     * @return error message
     */
    char* what();

protected:
    int errorCode = -3;
public:
    int getErrorCode() const;
};

/**
 * Class which describes incompatible point exception
 */

class IncompatiblePointException : public exception {
public:
    /**
     * Get string message what happend
     * @return error message
     */
    char* what();

protected:
    int errorCode = -4;
public:
    int getErrorCode() const;
};

/**
 * Class which describes add point operation exception
 */

class AddPointException : public exception {
public:
    /**
     * Get string message what happend
     * @return error message
     */
    char* what();

protected:
    int errorCode = -5;
public:
    int getErrorCode() const;
};

