#include <stdio.h>
#include "utility.h"

/// calculateTaxAmount
/// @brief Calculates the tax amount based on the initial cost and tax rate.
/// @param 	initialCost 	- The initial cost of the item. (i.e., $20,000.00)
/// @param 	taxRate 	- The applicable tax rate. (i.e., 0.07 for 7%)
/// @return The calculated tax amount.
double calculateTaxAmount(double initialCost, double taxRate)
{
    return initialCost * taxRate;
}

/// calculateFuelCost
/// @brief Calculates the total fuel cost over a specified number of years.
/// @param 	fuelCost 	- The annual fuel cost. (i.e., $1,500.00 per year)
/// @param 	years 		- The number of years. (i.e., 5 years)
/// @return The total fuel cost over the specified years.
double calculateFuelCost(double fuelCost, int years)
{
    return fuelCost * years;
}

/// calculateTotalCost
/// @brief Calculates the total cost including initial cost, fuel cost, and tax over a specified number of years.
/// @param 	initialCost 	- The initial cost of the item. (i.e., $20,000.00)
/// @param 	fuelCost 	- The total fuel cost over the specified years. (i.e., $7,500.00 for 5 years at $1,500.00 per year)
/// @param 	annualTaxCost 	- The annual tax cost. (i.e., $1,400.00 per year for tax)
/// @param 	years 		- The number of years. (i.e., 5 years)
/// @return The total cost over the specified years.
double calculateTotalCost(double initialCost, double fuelCost, double annualTaxCost, int years)
{
    return initialCost + fuelCost + (annualTaxCost * years);
}

/// printOutput
/// @brief Prints a summary of the calculated costs, including initial cost, fuel cost, tax cost, and total cost over a specified number of years.
/// @param 	initialCost 	- The initial cost of the item. (i.e., $20,000.00)
/// @param 	annualFuelCost 	- The annual fuel cost. (i.e., $1,500.00 per year)
/// @param 	annualTaxCost 	- The annual tax cost. (i.e., $1,400.00 per year)
/// @param 	totalCost 	- The total cost over the specified years. (i.e., $36,500.00 over 5 years)
void printOutput(double initialCost, double annualFuelCost, double annualTaxCost, double totalCost, int years)
{
    printf("================= Summary =================\n"
           "Initial price:                 $%.2f\n"
           "Annual fuel cost:              $%.2f\n"
           "Annual tax amount:             $%.2f\n"
           "Total cost over %d years:       $%.2f\n"
           "===========================================\n",
           initialCost, annualFuelCost, annualTaxCost, years, totalCost);
}
