#pragma once
#include "UserPoint.h"

/**
 * \brief Сriteria for stopping the computation
 *
 * The class 'UserCriterion' is intended to describe the interface criteria for stopping calculations
 */

class UserCriterion
{
public:

    /**
     * Base constructor
     */
	UserCriterion();

	/**
	 * Base virtual destructor
	 */
	virtual ~UserCriterion();

	/**
	 * Signal to stop computing
	 * @param next the following calculated values
	 * @return true if it is time to stop, false overwise
	 */
	virtual bool stop(double next) = 0;

	/**
	 * Get criterion name
	 * @return criterion name
	 */
	string getCriterionName();

	/**
	 * Get number of current iteration
	 * @return number of current iteration
	 */
	int getCurIteration();

protected:
	string criterionName; ///< criterion name
	int curIteration; ///< number of current iteration
};


/**
 * \brief Stop by the number of iterations
 *
 * The class 'NumberOfIterationCriterion' implements the stopping criterion by the number of iterations
 */

class NumberOfIterationCriterion : public UserCriterion
{
public:
	NumberOfIterationCriterion(int num = 100);
	~NumberOfIterationCriterion();
	bool stop(double next) override;

protected:
	int numberOfIteration; ///< number of iteration
};

/**
 * \brief Stop by the function value
 *
 *The class 'FunctionValueCriterion' implements the stopping criterion when
 * the difference modulo the neighboring mismatched values of the function is less than the specified accuracy
 */

class FunctionValueCriterion : public UserCriterion
{
public:
    FunctionValueCriterion(double eps = 10e-6);
    ~FunctionValueCriterion();
    bool stop(double next) override;

protected:
    double eps; ///< calculation accuracy
    double prev = numeric_limits<double>::max(); ///< previous calculated function values
};