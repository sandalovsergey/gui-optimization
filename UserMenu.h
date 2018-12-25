#include "UserDomain.h"
#include "UserFunction.h"
#include "UserCriterion.h"
#include "UserMethod.h"

/**
 * \brief Menu in program
 *
 * The class 'UserMenu' contains the description of the
 * basic preparatory steps for calculating the extreme value of the function
 */

class UserMenu {
protected:
    string funcChoice; ///< function chose case
    string criterionChoice; ///< criterion chose case
    string methodChoice; ///< method chose case
    string isRepeat = "y"; ///< should repeat program cycle
    UserFunction* f; ///< chosen function to optimize
    UserDomain* domain; ///< domain of chosen function
    UserPoint* startPoint; ///< start point computation
    UserCriterion* criterion; ///< chosen criterion for stop
    UserMethod* method; ///< chosen method to optimize
    string greatAnswer = "Summary: "; ///< description of chosen properties

public:
    /**
     * Run program menu
     */
    void runMenu();

    /**
     * Print menu title
     */
    void printTitle();

    /**
     * Logical
     * @return should repeat another cycle
     */
    bool isRepeatMenu();

    /**
     * Selection of the function
     */
    void functionSelection();

    /**
     * Selection of the domain
     */
    void domainSelection();

    /**
     * Selection of the start point
     */
    void startPointSelection();

    /**
     * Selection of the stopping criterion
     */
    void criterionSelection();

    /**
     * Selection of the opimization method
     */
    void methodSelection();

    /**
     * Get information
     */
    void summarize();

    /**
     * Logical: should repeat computation again
     * @return "y" or "n"
     */
    string isRepeatComputation();

};
