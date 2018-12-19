#include "UserDomain.h"
#include "UserException.h"

UserDomain::UserDomain(vector<double> leftBorders, vector<double> rightBorders) {
    try {
        if (leftBorders.size() != rightBorders.size()) {
            throw DiffSizeException();
        } else {
            (*this).rightBorders = rightBorders;
            (*this).leftBorders = leftBorders;
        }
    }

    catch (DiffSizeException ex) {
        cout << "Different left and right border size";
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}


UserDomain::~UserDomain() {

}

int UserDomain::getSizeBorders() const{
	return leftBorders.size();
}

vector<double> UserDomain::getLeftBorders() const{
	return leftBorders;
}

vector<double> UserDomain::getRightBorders() const{
	return rightBorders;
}

UserDomain::UserDomain(const UserDomain &domain) {
	(*this).leftBorders = domain.leftBorders;
	(*this).rightBorders = domain.rightBorders;
}

UserDomain &UserDomain::operator=(const UserDomain &domain) {
    try {
        if (domain.rightBorders.size() != (*this).rightBorders.size() ||
        domain.leftBorders.size() != (*this).leftBorders.size())
            throw DiffSizeException();
    }
    catch (DiffSizeException ex) {
        cout << "Wrong dimension of domain!";
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
        if (this != &domain) {
            leftBorders = domain.leftBorders;
            rightBorders = domain.rightBorders;
        }

    return *this;
}

void UserDomain::setLeftBordersIth(int i, double x) {
    try {
        if (i >= leftBorders.size())
            throw OutOfBoundException();
        else
            leftBorders[i] = x;
    }
    catch (OutOfBoundException ex) {
        cout << "\nvalue " << i << " is out of range" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

void UserDomain::setRightBordersIth(int i, double x) {
    try {
        if (i >= rightBorders.size())
            throw OutOfBoundException();
        else
            rightBorders[i] = x;
    }
    catch (OutOfBoundException ex) {
        cout << "\nvalue " << i << " is out of range" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

string UserDomain::toString() {
    string res = "";
    for(int i = 0; i < leftBorders.size(); ++i)
    {
        res = res + "x[" + to_string(i) + "] in " + "["
                + to_string(leftBorders[i]) + ";" + to_string(rightBorders[i]) + "] ";
    }

    return res;
}
