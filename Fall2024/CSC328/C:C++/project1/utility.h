/// utility.h
#ifndef UTILITY_H
#define UTILITY_H

double calculateTaxAmount(double initialCost, double taxRate);
double calculateFuelCost(double fuelCost, int years);
double calculateTotalCost(double initialCost, double fuelCost, double annualTaxCost, int years);
void printOutput(double initialCost, double annualFuelCost, double annualTaxCost, double totalCost, int years);

#endif
