#pragma once
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <exception>
using namespace std;

/**
 * \brief Function domain
 *
 * The class 'UserDomain' describes UserFunction instance domain
 * In this application domain is n dimensional cell
 */
class UserDomain
{
public:
    /**
     * Base constructor
     * @param leftBorders vector of left borders
     * @param rightBorders vector of right borders
     */
	UserDomain(vector<double> leftBorders, vector<double> rightBorders);

	/**
	 * Copy constructor
	 * @param domain is object to copy from
	 */
	UserDomain(const UserDomain& domain);

	/**
	 * Base destructor
	 */
	~UserDomain();

	/**
	 * Get size of borders array
	 * @return size of borders array
	 */
	int getSizeBorders() const;

	/**
	 * Get left borders
	 * @return left borders
	 */
	vector<double> getLeftBorders() const;

	/**
	 * Get right borders
	 * @return right borders
	 */
	vector<double> getRightBorders() const;

	/**
	 * Set left borders ith coord
	 * @param i number of coord
	 * @param x value to set
	 */
    void setLeftBordersIth(int i, double x);

    /**
	 * Set right borders ith coord
	 * @param i number of coord
	 * @param x value to set
	 */
    void setRightBordersIth(int i, double x);

    /**
     * Natural operator= defenition
     * @param domain
     * @return
     */
    UserDomain& operator= (const UserDomain &domain);

    /**
     * Get string representation of domain
     * @return domain string representation
     */
    string toString();

protected:
	vector<double> leftBorders; ///< left borders of domain
	vector<double> rightBorders; ///< right borders of domain
};
