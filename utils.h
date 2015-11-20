#include <random>

/////////////
// utils.h //
/////////////
/**
 * Class with utility functions (will probably extend other classes as the network grows)
 */
double dRand(double fMin, double fMax)         
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

//GDP == Gross Domestic Product == Aggregate Output Level
double GDP_deflator(double nominal_GDP, double real_GDP){           //enter nominal GDP and real GDP with respect to a given year
	return nominal_GDP/real_GDP;                                      //return aggregate price level (GDP deflator)
}

//PCE == Personal Consumption Expenditures
double PCE_deflator(double nominal_PCE, double real_PCE){           //enter nominal PCE and real PCE with respect to a given year
	return nominal_PCE/real_PCE;                                      //return PCE deflator
}

//CPI == Consumer Price Index
double CPI_deflator(double nominal_CPI, double real_CPI){           //enter nominal CPI and real CPI with respect to a given year
	return nominal_CPI/real_CPI;                                      //return CPI deflator
}

//growth rate of the real GDP
double growth_rate(double present_GDP, double most_recent_GDP){     //enter this year's and last year's real GDP
	return (present_GDP - most_recent_GDP)*100/most_recent_GDP;	      //return the percentage of change of the variable (real GDP)
}

//inflation rate of the aggregate price level
double inflation_rate(double present_GDP_deflator, double most_recent_GDP_deflator){           //enter this year's and last year's GDP deflator
	return (present_GDP_deflator - most_recent_GDP_deflator)*100/most_recent_GDP_deflator;	    //return the percentage of change of the variable 
}

class utils {
	public:

		//random double generator courtesy of stackoverflow
		static double dRand(double fMin, double fMax)         
		{
		    double f = (double)rand() / RAND_MAX;
		    return fMin + f * (fMax - fMin);
		}

		//GDP == Gross Domestic Product == Aggregate Output Level
		static double GDP_deflator(double nominal_GDP, double real_GDP){           //enter nominal GDP and real GDP with respect to a given year
			return nominal_GDP/real_GDP;                                      //return aggregate price level (GDP deflator)
		}

		//PCE == Personal Consumption Expenditures
		static double PCE_deflator(double nominal_PCE, double real_PCE){           //enter nominal PCE and real PCE with respect to a given year
			return nominal_PCE/real_PCE;                                      //return PCE deflator
		}

		//CPI == Consumer Price Index
		static double CPI_deflator(double nominal_CPI, double real_CPI){           //enter nominal CPI and real CPI with respect to a given year
			return nominal_CPI/real_CPI;                                      //return CPI deflator
		}

		//growth rate of the real GDP
		static double growth_rate(double present_GDP, double most_recent_GDP){     //enter this year's and last year's real GDP
			return (present_GDP - most_recent_GDP)*100/most_recent_GDP;	      //return the percentage of change of the variable (real GDP)
		}

		//inflation rate of the aggregate price level
		static double inflation_rate(double present_GDP_deflator, double most_recent_GDP_deflator){           //enter this year's and last year's GDP deflator
			return (present_GDP_deflator - most_recent_GDP_deflator)*100/most_recent_GDP_deflator;	    //return the percentage of change of the variable 
		}
};