#pragma once
#include "UserDomain.h"

/**
 * \brief Point in Euclidean space
 * \author Sergey Sandalov
 * \version 1.4
 *
 * The class 'UserPoint' describing the representation of a point in Euclidean space
 */

class UserPoint {
public:

    /**
     * Constructor that sets point from vector
     * @param x is input vector
     */
	UserPoint(vector<double> x);

	/**
	 * Copy constructor
	 * @param point  is object to copy from
	 */
	UserPoint(const UserPoint& point);

	/**
	 * Base destructor
	 */
	~UserPoint();

	/**
	 * Natural operator= definition
	 * @param point
	 * @return
	 */
	UserPoint& operator= (const UserPoint &point);

    /**
     * Natural operator+= definition
     * @param point
     * @return
     */
	UserPoint& operator+= (const UserPoint &point);

    /**
     * Natural operator-= definition
     * @param point
     * @return
     */
	UserPoint& operator-= (const UserPoint &point);

    /**
     * Natural operator*= definition
     * @param i is real number
     * @return
     */
	UserPoint& operator*= (double i);

	/**
	 * Get point description
	 * @return A string point representation
	 */
    string toString();

    /**
     * Natural operator+ definition
     * @param point1
     * @param point2
     * @return
     */
	friend UserPoint operator+(const UserPoint & point1, const UserPoint & point2);

    /**
     * Natural operator- definition
     * @param point1
     * @param point2
     * @return
     */
	friend UserPoint operator-(const UserPoint & point1, const UserPoint & point2);

    /**
     * Natural operator* definition
     * @param alpha
     * @param point1
     * @return
     */
	friend UserPoint operator*(double alpha, const UserPoint & point1);

    /**
     * Natural operator<< definition
     * @return
     */
	friend ostream& operator<< (ostream& s, const UserPoint& point);

	/**
	 * Get point dimension
	 * @return A point dimension
	 */
	int getDim() const;

	/**
	 * Get point's coords
	 * @return A vector of coords
	 */
	vector<double> getX() const;

	/**
	 * Check if point is in given domain
	 * @param domain
	 * @return true if it is, and false otherwise
	 */
	bool isInDomain(const UserDomain &domain) const;

	/**
	 * Replace i-th coord by given value
	 * @param i is number of coord to change
	 * @param delta is given value to change to
	 */
	void changeIthCoord(int i, double delta);


	void setIthCoord(int i, double delta);

protected:
	vector<double> x; ///< vector of point coord
};