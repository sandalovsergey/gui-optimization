#include "UserMethod.h"
#include "UserException.h"
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<> getKsi1(0.0, 1.0);

UserMethod::UserMethod(UserFunction* targetF, UserCriterion* criterion)
	: targetF(targetF), criterion(criterion) {
    numOfIter = 0;
}

UserMethod::~UserMethod() {
	startPoint = nullptr;
	targetF = nullptr;
	criterion = nullptr;
}

vector<UserPoint> UserMethod::getPathToGoal() {
    return pathToGoal;
}

int UserMethod::getNumOfIter() {
    return numOfIter;
}

UserPoint* UserMethod::getEndPoint() {
    return endPoint;
}

double UserMethod::getFEnd() {
    return fEnd;
}

void NelderMeadMethod::start(UserPoint* startPoint) {
    try {
        if (startPoint->getDim() != targetF->getDimension()) {
            throw IncompatiblePointException();
        }
    }
    catch (IncompatiblePointException ex) {
        cout << *startPoint << " incompatible with function " << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }

    try {
        if (!startPoint->isInDomain(*(targetF->getDomain()))) {
            throw DomainException();
        }
    }
    catch(DomainException ex) {
        cout << *startPoint << " is not in domain!" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }

	(*this).startPoint = startPoint;

    double h = 0.1; //Построение симплекса
    for(int i = 0; i < targetF->getDomain()->getRightBorders().size(); ++i)
        h = min(h, abs(targetF->getDomain()->getRightBorders()[i] - startPoint->getX()[i]));

    h*=0.7;

	simplex.push_back(*startPoint);
	UserPoint tmp(*startPoint);
	for (int i = 1; i < startPoint->getDim() + 1; ++i) {
		tmp.changeIthCoord(i - 1, h);
		simplex.push_back(tmp);
		tmp.changeIthCoord(i - 1, -h);
	}
}

NelderMeadMethod::NelderMeadMethod(UserFunction* targetF, UserCriterion* criterion,
	double a, double b, double c) : UserMethod(targetF, criterion), alpha(a), beta(b), gamma(c) {
}

void NelderMeadMethod::manualSetSimplex(vector<UserPoint> points) {

	for (int i = 0; i < points.size(); ++i) {
		simplex[i] = points[i];
	}
}

NelderMeadMethod::~NelderMeadMethod() {
	alpha = beta = gamma = -1;
	simplex = {};
}

void NelderMeadMethod::printIteration() {
    if(criterion->getCurIteration() % 10 == 0) {
        cout << criterion->getCurIteration() << ") Current simplex: \n";
        for (int i = 0; i < simplex.size(); ++i) {
            cout << simplex[i] << "\n";
        }
        cout << endl;
    }
}
vector<UserPoint> NelderMeadMethod::getSimplex() {
	return simplex;
}

void Sort(vector<UserPoint>& smpl, vector<double>& f)
{
	double f1;
	vector<double> vector1(smpl[0].getDim());
	UserPoint v1(vector1);

	for (int i = 1; i <= smpl.size() - 1; i++)
		for (int j = i; j >= 1; j--)
			if (f[j - 1]>f[j])
			{
				f1 = f[j];
				v1 = smpl[j];
				f[j] = f[j - 1];
				smpl[j] = smpl[j - 1];
				f[j - 1] = f1;
				smpl[j - 1] = v1;
			}
			else break;
}

void NelderMeadMethod::step() {
/*	cout << "Start simplex: ";
	for (int i = 0; i < simplex.size(); ++i)
		cout << simplex[i] << " ";
    cout << "\n\n" << endl; */

	int N_DIM = simplex.size() - 1;
	vector<double> f(N_DIM + 1);
	double f_h, f_g, f_l, f_r, f_e, f_s, tempD;
	vector<double> start(N_DIM);
	UserPoint x_h(start), x_g(start), x_l(start), x_r(start), x_e(start), x_s(start), x_c(start), tempV(start);
	int i;
	bool flag;
	bool isRepeat = true;

	for (i = 0; i <= N_DIM; i++) f[i] = targetF->apply(simplex[i]);    // Вычисление значений функции на начальном симплексе


	while (isRepeat)    // Проверка на условие выхода
	{
		// Шаг 1. Сортировка
		Sort(simplex, f); //!
		x_h = simplex[N_DIM];
		f_h = f[N_DIM];
		x_g = simplex[N_DIM - 1];
		f_g = f[N_DIM - 1];
		x_l = simplex[0];
		f_l = f[0];

		// Шаг 2. Вычисление центра тяжести симплекса
        UserDomain domain(targetF->getDomain()->getLeftBorders(), targetF->getDomain()->getRightBorders());

		x_c = UserPoint(start);
		for (i = 0; i < N_DIM; i++) x_c += simplex[i];
		x_c = (1.0 / N_DIM) * x_c; //!

		while (!x_c.isInDomain(domain))
		    x_c *= 0.9;

		// 3Шаг . Отражение
		x_r = (1 + alpha) * x_c - alpha * x_h;
        while (!x_r.isInDomain(domain))
            x_r *= 0.9;
		f_r = targetF->apply(x_r);

		// Шаг 4.
		if (f_r <= f_l) {    // Шаг 4a.
			x_e = (1 - gamma) * x_c + gamma * x_r;
            while (!x_e.isInDomain(domain))
                x_e *= 0.9;

			f_e = targetF->apply(x_e);
			if (f_e < f_l) {
				simplex[N_DIM] = x_e;
				f[N_DIM] = f_e;
			} else {
				simplex[N_DIM] = x_r;
				f[N_DIM] = f_r;
			}
		}
		if ((f_l < f_r) && (f_r <= f_g)) {    // Шаг 4.b
			simplex[N_DIM] = x_r;
			f[N_DIM] = f_r;
		}
		flag = false;
		if ((f_h >= f_r) && (f_r > f_g)) {    // Шаг 4c.
			flag = true;
			tempD = f_h;
			tempV = x_h;
			simplex[N_DIM] = x_r;
			f[N_DIM] = f_r;
			x_r = tempV;
			f_r = tempD;
		}
		// Шаг 4d.
		if (f_r > f_h) flag = true;
		if (flag) {    // Шаг 5. Сжатие
			x_s = beta * x_h + (1 - beta) * x_c;
            while (!x_s.isInDomain(domain))
                x_s *= 0.9;

			f_s = targetF->apply(x_s);
			if (f_s < f_h) {    // 6.
				tempD = f_h;
				tempV = x_h;
				simplex[N_DIM] = x_s;
				f[N_DIM] = f_s;
				x_s = tempV;
				f_s = tempD;
			} else {    // Шаг 7. Глобальное сжатие
				for (i = 0; i <= N_DIM; i++) {
                    simplex[i] = x_l + 0.5 * (simplex[i] - x_l);
                    while (!simplex[i].isInDomain(domain))
                        simplex[i] *= 0.9;
                }
			}
		}
		isRepeat = !criterion->stop(f_l);

      //  printIteration();

        pathToGoal.push_back(simplex[0]);
        ++numOfIter;
	}

    endPoint = new UserPoint(pathToGoal[pathToGoal.size() - 1]);
    fEnd = targetF->apply(*endPoint);

 //   cout << "\nExtreme point x* is " << simplex[0] << endl;
 //   cout << "f(x*) = " << f_l << endl;
}

string NelderMeadMethod::getMethodName() {
    return "Nelder Mead method";
}

RandomSearchMethod::RandomSearchMethod(UserFunction *targetF, UserCriterion *criterion, double prob, double delta, double alpha)
: UserMethod(targetF, criterion), prob(prob), delta(delta), alpha(alpha), curApprox(vector<double>{0}){
}

RandomSearchMethod::~RandomSearchMethod() {
    delta = -1;
}

void RandomSearchMethod::printIteration() {
    if(criterion->getCurIteration() % 10 == 0) {
        cout << criterion->getCurIteration() << ") ";
        cout << curApprox << " ";
        cout << endl;
    }
}

void RandomSearchMethod::start(UserPoint *startPoint) {
    try {
        if (startPoint->getDim() != targetF->getDimension()) {
            throw IncompatiblePointException();
        }
    }
    catch (IncompatiblePointException ex) {
        cout << *startPoint << " incompatible with function " << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }

    try {
        if (!startPoint->isInDomain(*(targetF->getDomain()))) {
            throw DomainException();
        }
    }
    catch(DomainException ex) {
        cout << *startPoint << " is not in domain!" << endl;
        cout << ex.what() << endl;
        exit(ex.getErrorCode());
    }

    (*this).startPoint = startPoint;

}

void RandomSearchMethod::getIntersec(UserDomain& domain){
    vector<double> leftBorders = targetF->getDomain()->getLeftBorders();
    vector<double> rightBorders = targetF->getDomain()->getRightBorders();
    for (int i = 0; i < leftBorders.size(); ++i) {
        domain.setLeftBordersIth(i, max(leftBorders[i], curApprox.getX()[i] - delta));
        domain.setRightBordersIth(i,min(rightBorders[i], curApprox.getX()[i] + delta));
    }
}

float getKsi() {
    //return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return getKsi1(generator);
    //return (float) rand() / RAND_MAX;
}

void RandomSearchMethod::step() {

    //srand (static_cast <unsigned> (time(0)));

    curApprox = *startPoint;
    pathToGoal.push_back(curApprox);
    UserPoint y_i(curApprox);
    double p = prob;
    double ksi;
    bool fromDelta;
    bool isRepeat = true;
    double min_f = targetF->apply(curApprox);

    UserDomain ballX(curApprox.getX(), curApprox.getX());
    getIntersec(ballX);

    while(isRepeat) {

        fromDelta = false;
        ksi = getKsi();

        if (ksi < p) {
            for (int i = 0; i < y_i.getDim(); ++i) {
                ksi = getKsi();
                ksi = ballX.getLeftBorders()[i] + (ballX.getRightBorders()[i] - ballX.getLeftBorders()[i]) * ksi;
                y_i.setIthCoord(i, ksi);
            }
            fromDelta = true;
        } else {
            for (int i = 0; i < y_i.getDim(); ++i) {
                ksi = getKsi();
                ksi = targetF->getDomain()->getLeftBorders()[i] + (targetF->getDomain()->getRightBorders()[i] -
                                                                     targetF->getDomain()->getLeftBorders()[i]) * ksi;
                y_i.setIthCoord(i,ksi);
            }
        }

        if (targetF->apply(y_i) < targetF->apply(curApprox)) {
            curApprox = y_i;
            min_f = targetF->apply(curApprox);
            if (fromDelta) {
                delta *= alpha;
            }

            getIntersec(ballX);

            pathToGoal.push_back(curApprox);
        }

        isRepeat = !criterion->stop(min_f);
      //  printIteration();
        ++numOfIter;


    }

  //  cout << "\nExtreme point x* is " << curApprox << endl;
  //  cout << "f(x*) = " << min_f << endl;

    endPoint = new UserPoint(pathToGoal[pathToGoal.size() - 1]);
    fEnd = targetF->apply(*endPoint);
}

string RandomSearchMethod::getMethodName() {
    return "Random search method";
}

