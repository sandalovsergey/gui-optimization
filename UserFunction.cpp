#include "UserFunction.h"
#include "UserException.h"


UserFunction::UserFunction(int arg_dimension) : arg_dimension(arg_dimension){

}

UserFunction::~UserFunction() {
	arg_dimension = -1;
	delete domain;
}

int UserFunction::getDimension() {
	return arg_dimension;
}

UserDomain* UserFunction::getDomain() {
	return domain;
}

void UserFunction::setDomain(UserDomain *domain) {
    delete UserFunction::domain;
    UserFunction::domain = domain;
}


OneDimensionFunction::OneDimensionFunction() : UserFunction(1) {
	domain = new UserDomain(vector<double>{-10}, vector<double>{10});
}

OneDimensionFunction::~OneDimensionFunction() {

}

double OneDimensionFunction::apply(const UserPoint &point) {
    try {
        if (point.isInDomain(*domain)) {
            vector<double> x = point.getX();
            return x[0] * x[0] * x[0] * x[0] - 10 * x[0] * x[0] * x[0] + 35 * x[0] * x[0] - 50 * x[0] + 24;
        } else {
            throw DomainException();
        }
    }
    catch (DomainException ex) {
        cout << point << " is not in domain!\n";
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

string OneDimensionFunction::getFormulae() {
    return "f(x) = x^4 - 10x^3 + 35x^2 - 50x + 24";
}

string OneDimensionFunction::getFuncFormulae() {
    return getFormulae();
}


RosenbrockFunction::RosenbrockFunction() : UserFunction(2){
    domain = new UserDomain(vector<double>{-2,-2}, vector<double>{2,2});
}

RosenbrockFunction::~RosenbrockFunction() {

}

double RosenbrockFunction::apply(const UserPoint &point) {
    try {
        if (point.isInDomain(*domain)) {
            vector<double> x = point.getX();
            return (1 - x[0]) * (1 - x[0]) + 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
        } else {
            throw DomainException();
        }
    }

    catch (DomainException ex) {
        cout << point << " is not in domain!\n";
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }

}

string RosenbrockFunction::getFormulae() {
    return "f(x,y) = (1-x)^2 + 100(y-x^2)^2";
}

string RosenbrockFunction::getFuncFormulae() {
    return getFormulae();
}


ThreeDimensionFunction::ThreeDimensionFunction() : UserFunction(3) {
    domain = new UserDomain(vector<double>{-10,-10,-10}, vector<double>{10,10,10});
}

ThreeDimensionFunction::~ThreeDimensionFunction() {

}

double ThreeDimensionFunction::apply(const UserPoint &point) {
    try {
        if (point.isInDomain(*domain)) {
            vector<double> x = point.getX();
            return -(-x[0] * x[0] - 5 * x[1] * x[1] - 3 * x[2] * x[2] + x[0] * x[1] - 2 * x[0] * x[2] +
                     2 * x[1] * x[2] +
                     11 * x[0] + 2 * x[1] + 18 * x[2] + 10);
        } else {
           throw DomainException();
        }
    }

    catch (DomainException ex) {
        cout << point << " is not in domain!\n";
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

string ThreeDimensionFunction::getFormulae() {
    return "f(x,y,z) = x^2 + 5y^2 + 3z^2 - xy + 2xz - 2yz - 11x - 2y - 18z - 10";
}

string ThreeDimensionFunction::getFuncFormulae() {
    return getFormulae();
}


FourDimensionFunction::FourDimensionFunction() :UserFunction(4){
    domain = new UserDomain(vector<double>{-3,-3,-3,-3}, vector<double>{3,3,3,3});
}

FourDimensionFunction::~FourDimensionFunction() {

}

double FourDimensionFunction::apply(const UserPoint &point) {
    try {
        if (point.isInDomain(*domain)) {
            vector<double> x = point.getX();
            return (x[0] - x[1]) * (x[0] - x[1]) + x[1] * x[1] + (1 - x[2]) * (1 - x[2]) +
                   (x[3] - cos(x[3])) * (x[3] - cos(x[3]));
        } else {
            throw DomainException();
        }
    }
    catch (DomainException ex) {
        cout << point << " is not in domain!" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }
}

string FourDimensionFunction::getFormulae() {
    return "f(x,y,z,u) = (x - y)^2 + y^2 + (1 - z)^2 + (u - cosu)^2";
}

string FourDimensionFunction::getFuncFormulae() {
    return getFormulae();
}
