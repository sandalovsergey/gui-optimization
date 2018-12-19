#include <c++/sstream>
#include "UserPoint.h"
#include "UserException.h"


UserPoint::UserPoint(vector<double> v) {
	x = v;
}

UserPoint::UserPoint(const UserPoint& point){
	x = point.x;
}

UserPoint::~UserPoint() {

}

UserPoint& UserPoint:: operator= (const UserPoint& point) {
	if (this != &point) {
		x = point.x;
	}

	return *this;
}

UserPoint& UserPoint:: operator+= (const UserPoint& point) {
    try {
        if (x.size() == point.x.size()) {
            for (int i = 0; i < x.size(); ++i)
                x[i] += point.x[i];

            return *this;
        } else {
            throw AddPointException();
        }
    }
    catch (AddPointException ex) {
        cout << point << " and " << (*this) << " have different dim" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

UserPoint& UserPoint:: operator-= (const UserPoint& point) {
    try {
        if (x.size() == point.x.size()) {
            for (int i = 0; i < x.size(); ++i)
                x[i] -= point.x[i];

            return *this;
        } else {
            throw AddPointException();
        }
    }
    catch (AddPointException ex) {
        cout << point << " and " << (*this) << " have different dim" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

UserPoint operator+ (const UserPoint& point1, const UserPoint& point2) {
	UserPoint tmp(point1);
	tmp += point2;
	return tmp;
}

UserPoint operator- (const UserPoint& point1, const UserPoint& point2) {
	UserPoint tmp(point1);
	tmp -= point2;
	return tmp;
}

UserPoint operator*(double alpha, const UserPoint & point1) {
	UserPoint tmp(point1);
	tmp *= alpha;
	return tmp;
}



UserPoint& UserPoint:: operator*= (double val) {
	for (int i = 0; i < x.size(); ++i)
		x[i] *= val;

	return *this;
}

ostream & operator<<(ostream & s, const UserPoint & point)
{
	cout << "Point{";
	for (int i = 0; i < point.x.size(); ++i) {
		if (i == point.x.size() - 1)
			cout << point.x[i] << "}";
		else
			cout << point.x[i] << ", ";
	}

	return s;
}

int UserPoint::getDim() const {
	return x.size();
}

vector<double> UserPoint::getX() const {
	return x;
}

bool UserPoint::isInDomain(const UserDomain &domain) const{
	if (x.size() == domain.getSizeBorders()) {
		for (int i = 0; i < x.size(); ++i) {
			if (x[i] < domain.getLeftBorders()[i] || x[i] > domain.getRightBorders()[i])
				return false;
		}
		return true;
	} else {
		return false;
	}
}

void UserPoint::changeIthCoord(int i, double delta) {
    try {
        if (i < 0 || i > x.size() - 1)
            throw OutOfBoundException();
    }
    catch (OutOfBoundException ex) {
        cout << "\nvalue " << i << " is out of range" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
	x[i] += delta;

}

void UserPoint::setIthCoord(int i, double delta) {
    try {
        if (i < 0 || i > x.size() - 1)
            throw OutOfBoundException();
    }
    catch (OutOfBoundException ex) {
        cout << "\nvalue " << i << " is out of range" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }

    x[i] = delta;
}

string UserPoint::toString() {
    string res = "";

    res = res + "Point{";
    for (int i = 0; i < x.size(); ++i) {
        if (i == x.size() - 1)
            res = res + to_string(x[i]) + "}";
        else
            res = res + to_string(x[i]) + ", ";
    }

    return res;
}
