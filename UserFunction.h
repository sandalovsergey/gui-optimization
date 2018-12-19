#pragma once
#include "UserPoint.h"

/**
 * \brief Functions in program
 *
 * The class 'UserFunction' describing interface of function which receive UserPoint as an argument
 */

class UserFunction {
public:
    /**
     * Constructor
     * @param arg_dimension argument dimension
     */
	explicit UserFunction(int arg_dimension);

	/**
	 * Base destructor
	 */
	virtual ~UserFunction();

	/**
	 * Get function argument dimension
	 * @return function argument dimension
	 */
	int getDimension();

	/**
	 * Get function domain
	 * @return function domain
	 */
	UserDomain* getDomain();

	/**
	 * Evaluate function value in certain point
	 * @param point where we evaluate function value
	 * @return function value in given point
	 */
	virtual double apply(const UserPoint& point) = 0;

	/**
	 * Get function formulae
	 * @return function formulae
	 */
	virtual string getFuncFormulae() = 0;

protected:
	int arg_dimension; ///< function argument dimension
	UserDomain* domain; ///< function domain
public:
    /**
     * Set given domain
     * @param domain to set from
     */
    void setDomain(UserDomain *domain);
};

/**
 * Class for one dimension function
 */

class OneDimensionFunction : public  UserFunction {
public:
    OneDimensionFunction();
    ~OneDimensionFunction();
    double apply(const UserPoint& point) override;
    static string getFormulae();
    string getFuncFormulae() override;

};

/**
 * Class for one Rosenbrock function
 */
class RosenbrockFunction : public UserFunction {
public:
	RosenbrockFunction();
	~RosenbrockFunction();
	double apply(const UserPoint& point) override;
	static string getFormulae();
	string getFuncFormulae() override;
};

/**
 * Class for three dimension function
 */

class ThreeDimensionFunction : public UserFunction {
public:
    ThreeDimensionFunction();
    ~ThreeDimensionFunction();
    double apply(const UserPoint &point) override;
    static string getFormulae();
    string getFuncFormulae() override;
};

/**
 * Class for four dimension function
 */

class FourDimensionFunction : public UserFunction {
public:
    FourDimensionFunction();
    ~FourDimensionFunction();
    double apply(const UserPoint &point ) override;
    static string getFormulae();
    string getFuncFormulae() override;
};