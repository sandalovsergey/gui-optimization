#include "UserCriterion.h"

UserCriterion::UserCriterion() : curIteration(0) {

}

UserCriterion::~UserCriterion() {
	criterionName = nullptr;
}

string UserCriterion::getCriterionName() {
	return criterionName;
}

int UserCriterion::getCurIteration() {
	return curIteration;
}

NumberOfIterationCriterion::NumberOfIterationCriterion(int num) : UserCriterion(), numberOfIteration(num) {
	criterionName = "Number of iteration criterion";
}

NumberOfIterationCriterion::~NumberOfIterationCriterion() {
	numberOfIteration = curIteration = -1;
}

bool NumberOfIterationCriterion::stop(double next) {
	++curIteration;

	if (curIteration >= numberOfIteration)
		return true;
	else
		return false;
}

FunctionValueCriterion::FunctionValueCriterion(double eps) : UserCriterion(), eps(eps) {
    criterionName = "Function Value Criterion";
}

FunctionValueCriterion::~FunctionValueCriterion() {
    eps = curIteration = -1;
}

bool FunctionValueCriterion::stop(double next) {
    ++curIteration;

    if(next < prev) {
        if(abs(next - prev) < eps)
            return true;

        else {
            prev = next;
            return false;
        }
    }

    else
        return false;
}