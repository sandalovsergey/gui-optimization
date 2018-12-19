#include "UserMenu.h"
#include "UserFunction.h"
#include <cstdlib>

void UserMenu::runMenu() {
    printTitle();

    while(isRepeatMenu()){
        functionSelection();
        domainSelection();
        startPointSelection();
        criterionSelection();
        methodSelection();
        summarize();

        method->start(startPoint);
        method->step();

        isRepeat = isRepeatComputation();
    }

}

void UserMenu::printTitle() {
    cout << "This program is seeking out for a minimum of a function." << endl;
}

bool UserMenu::isRepeatMenu() {
    return isRepeat == "y" ? true : false;
}

void UserMenu::functionSelection() {
    cout << "\n\n     Function     \n";
    cout << "Select function from the list. Press: " << endl;
    cout << "1 - " << OneDimensionFunction::getFormulae() << endl;
    cout << "2 - " << RosenbrockFunction::getFormulae() << endl;
    cout << "3 - " << ThreeDimensionFunction::getFormulae() << endl;
    cout << "4 - " << FourDimensionFunction::getFormulae() << endl;
    cout << "\nYour answer: ";

    cin >> funcChoice;
    while(funcChoice != "1" && funcChoice != "2" && funcChoice != "3" && funcChoice != "4") {
        cout << "Wrong input! Choose from 1,2,3 or 4" << endl;
        cout << "Your answer: ";
        cin >> funcChoice;
    }

    switch (stoi(funcChoice)) {
        case 1:
            f = new OneDimensionFunction();
            break;
        case 2:
            f = new RosenbrockFunction();
            break;
        case 3:
            f = new ThreeDimensionFunction();
            break;
        case 4:
            f = new FourDimensionFunction();
            break;
    }

    cout << "You choose " << f->getFuncFormulae() << endl;
    greatAnswer = greatAnswer + "\nfunction: " + f->getFuncFormulae();
}

void UserMenu::domainSelection() {
    cout << "\n\n     Domain     \n";
    cout << "Press 's' to select appropriate function domain(must include 0 from R^" << f->getDimension() << ") or press 'd' to set default" << endl;
    cout << "Default domain for selected function is " + f->getDomain()->toString();
    cout << " \nYour answer: ";
    string domainChoice;
    cin >> domainChoice;
    while(domainChoice != "s" && domainChoice != "d")
    {
        cout << "Wrong choose! Press s or d" << endl;
        cout << "Your answer: ";
        cin >> domainChoice;
    }

    domain = new UserDomain(*(f->getDomain()));

    if(domainChoice == "s") {
        cout << "Example: f(x[0], x[1]) = x[0] + x[1]. "
                "Domain: "
                "x[0] from: -1, "
                "x[0] to: 1; "
                "x[1] from: -5, "
                "x[1] to: 5;" << endl;

        cout << "Domain: " << endl;

        vector<double> leftBorders;
        vector<double> rightBorders;


        for (int i = 0; i < f->getDimension(); ++i) {
            double tmp;
            cout << "x[" << i << "] from: ";
            cin >> tmp;
            leftBorders.push_back(tmp);
            cout << "x[" << i << "] to: ";
            cin >> tmp;
            rightBorders.push_back(tmp);

            if (rightBorders[i] < leftBorders[i])
                swap(rightBorders[i], leftBorders[i]);
        }

        delete domain;
        domain = new UserDomain(leftBorders, rightBorders);

        vector<double> z(f->getDimension(), 0);
        UserPoint zero(z);
        if(!zero.isInDomain(*domain)) {
            cout << "\n0 must be in domain! Set to default!\n";
            delete domain;
            domain = new UserDomain(*(f->getDomain()));
        }


    }

    cout << "Selected domain: " << domain->toString() << endl;
    greatAnswer = greatAnswer + "\ndomain: " + domain->toString();

    for(int i = 0; i < domain->getRightBorders().size(); ++i) {
        domain->setRightBordersIth(i, domain->getRightBorders()[i] + 0.1);
        domain->setLeftBordersIth(i, domain->getLeftBorders()[i] - 0.1);
    }

    f->setDomain(domain);
}

void UserMenu::startPointSelection() {
    cout << "\n\n     Start point     \n";
    cout << "Select start point P in current function domain within R^" << f->getDimension() << endl;
    vector<double> coords;
    bool flag;
    do{
        flag = false;
        for (int i = 0; i < f->getDimension(); ++i) {
            double tmp;
            cout << "P[" << i << "] = ";
            cin >> tmp;
            coords.push_back(tmp);
        }

        startPoint = new UserPoint(coords);
        if(!startPoint->isInDomain(*(f->getDomain())))
        {
            delete startPoint;
            coords = {};
            cout << "This point is not in domain! Repeat input\n";
            flag = true;
        }
    }while (flag);

    cout << "P is " << *startPoint << endl;

    greatAnswer = greatAnswer + "\nstart point: " + startPoint->toString();
}

void UserMenu::criterionSelection() {
    cout << "\n\n Criterion     \n";
    cout << "\nSelect stop criterion. Press: \n"
            "1 - Number of iteration criterion\n"
            "2 - Function value criterion\n";

    cout << "\nYour answer: ";

    cin >> criterionChoice;
    while(criterionChoice != "1" && criterionChoice != "2") {
        cout << "Wrong input! Choose from 1 or 2" << endl;
        cout << "Your answer: ";
        cin >> criterionChoice;
    }

    switch (stoi(criterionChoice)) {
        case 1:
            cout << "Input number of iteration: ";
            int num;
            cin >> num;
            criterion = new NumberOfIterationCriterion(num);
            if(num < 0)
                num = -num;
            greatAnswer = greatAnswer + "\ncriterion: NumOfIt with " + to_string(num) + " iteration";
            break;
        case 2:
            cout << "Input accuracy: ";
            double eps;
            cin >> eps;
            if(eps < 0)
                eps = -eps;
            criterion = new FunctionValueCriterion(eps);
            greatAnswer = greatAnswer + "\ncriterion: FunVal with eps = " + to_string(eps);
            break;
    }
}

void UserMenu::methodSelection() {
    cout << "\n\n     Optimization method     \n";
    cout << "Select method for optimization. Press: \n"
            "1 - Nelder-Mead method\n"
            "2 - Random search method\n";
    cout << "\nYour answer: ";

    cin >> methodChoice;
    while(methodChoice != "1" && methodChoice != "2") {
        cout << "Wrong input! Choose from 1 or 2" << endl;
        cout << "Your answer: ";
        cin >> methodChoice;
    }

    switch (stoi(methodChoice)) {
        case 1:
            method = new NelderMeadMethod(f,criterion);
            greatAnswer = greatAnswer + "\nmethod: Nelder Mead";
            break;
        case 2:
            cout << "Input probability to get to into the ball (0 < p < 1): " << endl;
            cout << "Your answer: ";
            double p;
            cin >> p;
            while(p <= 0 || p >= 1) {
                cout << "Wrong input! p from (0;1)" << endl;
                cout << "Your answer: ";
                cin >> p;
            }
            method = new RandomSearchMethod(f, criterion, p);
            greatAnswer = greatAnswer + "\nmethod: Random search";
            break;
    }
}

void UserMenu::summarize() {
    cout << "\n\n" + greatAnswer + "\n\n";
}

string UserMenu::isRepeatComputation() {
    string res;

    cout << "\n\nDo you want to repeat computation again?(y/n)";
    cin >> res;
    while(res != "y" && res != "n")
    {
        cout << "Wrong choose! Press 'y' or 'n'" << endl;
        cout << "Your answer: ";
        cin >> res;
    }

    return res;
}


