#ifndef AGDATAANDSTATISTICS_H
#define AGDATAANDSTATISTICS_H

#include <iostream>
#include <map>
#include "AGSchool.h"
#include "AGPosition.h"

class AGDataAndStatistics
{
public:
	AGDataAndStatistics()
	{
		//srand((unsigned int)time(NULL));
	};

	/**
	 * parameters
	 */
	float speedTimePerKm;
	float carPreference;

	/**
	 * from General element from XML file.
	 */
	int inhabitants;
	int households;
	int limitAgeChildren;
	int limitAgeRetirement;
	int limitEndAge;
	float carRate;
	float unemployement;
	int maxFootDistance;
	int incomingTraffic;
	int outgoingTraffic;
	float freeTimeActivityRate;

	std::map<int, float> beginWorkHours;				//<hour, probability> (number only used in term of PROPORTION: it should be normalized)
	std::map<int, float> endWorkHours;					//<hour, probability> (number only used in term of PROPORTION: it should be normalized)
	std::map<int, AGPosition> busStations;				//<id, position>
	//std::map<SchoolType, int> schoolCapacity;
	std::map<int, float> population;						//<bracket's end age, number> (number only used in term of PROPORTION: it should be normalized)
	//std::map<int, float> childrenAccompagniment;		//<bracket's end age, probability>

	/**
	 * computed values used during processing
	 */
	int workPositions;
	float factorInhabitants;
	float factorWorkPositions;

	/**
	 * data used for household generation
	 * has to be computed before.
	 */
	//probability of picking an old-people household (compared to working and have children adults)
	float oldAgeHhProb;
	//probability of having a second adult (old in case of old householders) in the household.
	float secondPersProb;
	//this s the mean number of children pro household (not old). This value is used in the Poisson-lay for determining the number of children in each family
	float meanNbrChildren;

	/**
	 * numbers not needed but interesting for statistics and TESTING
	 */
	//int childrenNbr;
	//int oldPeopleNbr;
	int AdultNbr;
	int householdsNbr;
	int workingPeople;
	//households far from public transports
	int hhFarFromPT;

	/**
	 * function returning a random number between the two given numbers: [n;m[ (m cannot occur)
	 * it returns 0 if m < n
	 */
	int getRandom(int n, int m);
	/**
	 * function returning a random age between the two numbers satisfying the previous constrains
	 * this number is in relation to the distribution of the population through the brackets (population's list)
	 * if the given numbers are both greater than limitEndAge, it returns 0
	 * if m is greater than limitEndAge, m=limitEndAge
	 * returns -1 if conditions are not satisfied
	 */
	int getRandomPopDistributed(int n, int m);
	/**
	 * function evaluating the POISSON's lay (probability lay)
	 * it returns the number of children with a probability of POISSON in a household
	 * is given the mean of the distribution
	 */
	int getPoissonsNumberOfChildren(float mean);
	/**
	 * these functions return the number of people having more (or less) than the given age
	 * (inclusive for getPeopleOlderThan ; exclusive for getPeopleYoungerThan)
	 * getPeopleOlderThan(n) + getPeopleYoungerThan(n) = inhabitants
	 * these first two function are based on the third one.
	 */
	int getPeopleOlderThan(int age);
	int getPeopleYoungerThan(int age);
	float getPropYoungerThan(int age);
	/**
	 * function consolidating statistics:
	 * normalizes the maps with probabilities
	 * completes data which have to be computed before use
	 */
	void consolidateStat();
	/**
	 * function returning a random value corresponding to this distribution:
	 * -mean is given
	 * -max variation of the mean (|possible value - mean| <= maxVar
	 * -the mean is the most probable
	 * -the probability distribution function is a "scaled exponential" distribution
	 * from mean-maxVar to mean and from mean to mean+maxVar
	 */
	float getInverseExpRandomValue(float mean, float maxVar);

private:
	//number used as seed in random number generation
	//int randomNbr;
	/**
	 * returns the POISSON's probability (exp(-m)*m^k/k!)
	 * @arg: mean of the distribution
	 * @arg: number of occurrences
	 */
	float poisson(float mean, int occ);
	/**
	 * recursive mathematical function returning the factorial of n: n!
	 */
	int factorial(int n);

	//function normalizing the map's probabilities: Sum(floats) = 1
	void normalizeMapProb(std::map<int, float> *myMap);

};

#endif
