/// @author            Trey Rubino
/// @major             Computer Science and Mathematics
/// @creationdate      2024-08-30
/// @duedate           2024-09-09
/// @course            CSC 328 010
/// @professor         Dr. Schwesinger
/// @project           #1
/// @filename          main.c
/// @brief             Takes command line arguments to calculate total cost plus annual fuel 
///                    and take of a new house.           '

#include <stdio.h>
#include "utility.h"
#include "parse.h"

int main(int argc, char* argv[])
{
        double initialCost = 0, annualFuelCost = 0, taxRate = 0;
        int years = 5;

        parser(argc, argv, &initialCost, &annualFuelCost, &taxRate, &years);

        double annualTaxAmount = calculateTaxAmount(initialCost, taxRate);
        double totalFuelCost = calculateFuelCost(annualFuelCost, years);
        double totalCost = calculateTotalCost(initialCost, totalFuelCost, annualTaxAmount, years);

        printOutput(initialCost, annualFuelCost, annualTaxAmount, totalCost, years);

        return 0;
}
