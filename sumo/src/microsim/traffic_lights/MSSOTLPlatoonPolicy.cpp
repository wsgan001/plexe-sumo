/****************************************************************************/
/// @file    MSSOTLPlatoonPolicy.cpp
/// @author  Gianfilippo Slager
/// @author  Federico Caselli
/// @date    Feb 2010
/// @version $Id: MSSOTLPlatoonPolicy.cpp 0 2010-02-18 12:40:00Z gslager $
///
// The class for SOTL Platoon logics
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright 2001-2009 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/

#include "MSSOTLPlatoonPolicy.h"


MSSOTLPlatoonPolicy::MSSOTLPlatoonPolicy(const std::map<std::string, std::string>& parameters) :
		MSSOTLPolicy("Platoon", parameters)
{
  init();
}

MSSOTLPlatoonPolicy::MSSOTLPlatoonPolicy(MSSOTLPolicyDesirability *desirabilityAlgorithm) :
		MSSOTLPolicy("Platoon", desirabilityAlgorithm)
{
	getDesirabilityAlgorithm()->setKeyPrefix("PLATOON");
	init();
}

MSSOTLPlatoonPolicy::MSSOTLPlatoonPolicy(MSSOTLPolicyDesirability *desirabilityAlgorithm,
		const std::map<std::string, std::string>& parameters) :
		MSSOTLPolicy("Platoon", desirabilityAlgorithm, parameters)
{
	getDesirabilityAlgorithm()->setKeyPrefix("PLATOON");
	init();
}

bool MSSOTLPlatoonPolicy::canRelease(int elapsed, bool thresholdPassed, bool pushButtonPressed,
		const MSPhaseDefinition* stage, int vehicleCount)
{
//  DBG(std::ostringstream str; str << "invoked MSTLPlatoonPolicy::canRelease()"; WRITE_MESSAGE(str.str()););
  DBG(
      std::ostringstream str;
      str << "MSSOTLPlatoonPolicy::canRelease elapsed " << elapsed << " threshold " << thresholdPassed << " pushbutton " << pushButtonPressed << " vcount " << vehicleCount
          <<" minD " << stage->minDuration << " maxD " << stage->maxDuration; str << " will return " << ((thresholdPassed && ((vehicleCount == 0) || (elapsed >= stage->maxDuration)))?"true":"false");
      WRITE_MESSAGE(str.str());
  );
  if (elapsed >= stage->minDuration)
  {
    if (pushButtonLogic(elapsed, pushButtonPressed, stage))
      return true;
    if (thresholdPassed)
    {
      //If there are no other vehicles approaching green lights
      //or the declared maximum duration has been reached
      return ((vehicleCount == 0) || (elapsed >= stage->maxDuration));
    } else
    {
      if (sigmoidLogic(elapsed, stage, vehicleCount))
        return true;
    }
  }
  return false;
}

void MSSOTLPlatoonPolicy::init()
{
   SigmoidLogic::init("MSSOTLPlatoonPolicy", this);
   PushButtonLogic::init("MSSOTLPlatoonPolicy", this);
}
