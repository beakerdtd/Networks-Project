#include <random>
Class agent;

/////////////
// utils.h //
/////////////
/**
 * Class with utility functions (will probably extend other classes as the network grows)
 */
class utils {
	public:
		void borrow_lend(agent* A, agent* B);         //function to come

		double dRand(double fMin, double fMax)         //better random number generator
		{
			std::default_random_engine generator;
			std::uniform_real_distributon<double> distribution(fMin, fMax);
		    return distribution(generator);
		}
}