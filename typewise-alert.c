#include "typewise-alert.h"
#include <stdio.h>


TempLimit TempLimitCoolingType[3] = {
  {0,35},
  {0,45},
  {0,40}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerLimit = TempLimitCoolingType[coolingType].lowerLimit;
  int upperLimit = TempLimitCoolingType[coolingType].upperLimit;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
      printf("To: %s\n", recepient);
  switch(breachType) {
    case TOO_LOW:
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
