#pragma once
#include "UserFunction.h"
#include "UserCriterion.h"

/**
 * \brief Optimization method
 *
 * The class 'UserMethod' describing the interface extremum calculation method
 */
class UserMethod
{
public:
    /**
     * Constructor
     * @param targetF optimizing function
     * @param criterion optimized criterion
     */
	UserMethod (UserFunction* targetF, UserCriterion* criterion);
	virtual ~UserMethod();

	/**
	 * Start computation method
	 * @param startPoint start point of computation
	 */
	virtual void start(UserPoint* startPoint) = 0;

	/**
	 * Step to the next iteration
	 */
	virtual void step() = 0;

	/**
	 * Print information about current iteration
	 */
	virtual void printIteration() = 0;

    vector<UserPoint> getPathToGoal();

protected:
    UserPoint* startPoint; ///< start point
	UserFunction* targetF; ///< function to optimize
	UserCriterion* criterion; ///< optimization criterion
    vector<UserPoint> pathToGoal = {};

};


/**
 * Class for Nelder-Mead method
 */

class NelderMeadMethod : public UserMethod
{
public:
	NelderMeadMethod(UserFunction* targetF, UserCriterion* criterion,
		double alpha = 1, double beta = 1, double gamma = 1);
	~NelderMeadMethod();
	void start(UserPoint* startPoint) override;
	void step() override;
	void printIteration() override;
    vector<UserPoint> getSimplex();
	void manualSetSimplex(vector<UserPoint> points);
    static string getMethodName();

protected:
	double alpha; ///< method params
	double beta; ///< method params
	double gamma; ///< method params
	vector<UserPoint> simplex; ///< current simplex of Nelder-MEad method

};

/**
 * Class for Random search method
 */

class RandomSearchMethod : public UserMethod {
public:
    RandomSearchMethod(UserFunction* targetF, UserCriterion* criterion, double prob = 0.5, double delta = 0.5, double alpha = 0.99);
    ~RandomSearchMethod();
    void start(UserPoint* startPoint) override;
    void step() override;
    void printIteration() override;
    static string getMethodName();

protected:
    double prob; ///< method params
    double delta; ///< method params
    double alpha; ///< method params
    UserPoint curApprox; ///< current approximation

private:
    /**
     * Intersect delta-ball with function domain
     * @param domain function domain
     */
    void getIntersec(UserDomain& domain);
};
