// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "salariedemployee.h"

#include <assertexcept.h>

#include "../ssn/ssn.h"
#include <string>
#include <utility>
#include <cmath>
#include <cstdlib>
using namespace std;

bool SalariedEmployee::SalariedInvariant() const
{
    //Checking members to see if they have values//
    //employee pay should not be less than or equal to zero or not a number//
    BOOST_ASSERT( ( std::abs(0.0 - employee_pay) < 1.0 / 10000000 )==false&&(isnan(employee_pay)==false));
    //employee_name cannot be empty//
    BOOST_ASSERT(!employee_name.empty()==true);
    //SSN cannot be empty//
    string ssn_output=employee_ssn.str();
    BOOST_ASSERT(ssn_output.empty()==false);
    //SSN should have a valid value and size//
    //note: code copied over from SSN class//
    BOOST_ASSERT(std::regex_match(ssn_output, employee_ssn.inputRegex()));
                   //  Valid SSN //
    BOOST_ASSERT(employee_ssn.str().size() == 9 || employee_ssn.str().size() == 11);
                    // "SSN has the right size")//

    //name should not contain any non UTF8 characters and must be composed of english characters//
    std::regex english_characters ("^[a-zA-Z[:space:]]*$");
    BOOST_ASSERT(std::regex_match(employee_name,english_characters));

    return true;
}


SalariedEmployee::~SalariedEmployee()
{
    std::cout <<"\\"<<employee_name<<"\\"" payroll log removed." << std::endl;
}

SalariedEmployee::SalariedEmployee(const std::string& salaried_name, const std::string& salaried_ssn_ID, const std::string& salaried_pay)
        : Employee(salaried_name, SSN(salaried_ssn_ID), salaried_pay)
{
    //PRECONDITION SECTION//

    //variable used for the conversion of string inputs using the strtod function//
    char *end;
    //assert that none of the string inputs are empty//
    BOOST_ASSERT((salaried_name.empty()==false)&&(salaried_pay.empty()==false)&&(salaried_ssn_ID.empty()==false));


    //Validating the Pay input//
    //--assert that the string that parameter salaried_pay contains could be converted into  a valid double value//
    BOOST_ASSERT(salaried_pay.find_first_not_of("1234567890."));

    //--assert that salaried_pay and salaried_pay's values are greater than 0 (meaning they were given a value) and are also valid doubles//
    BOOST_ASSERT((std::fabs(0.0 - (std::strtod(salaried_pay.c_str(),&end))) < 1.0 / 10000000)==false&&isnan(std::strtod(salaried_pay.c_str(),&end))==false);

    //Validating the SSN Input//

    //--assert that SSN is a string that isn't empty//
    BOOST_ASSERT(salaried_ssn_ID.empty()==false);

    //--assert that the input of the ssn is composed of a set of numbers and dashes//
    BOOST_ASSERT(salaried_ssn_ID.find_first_not_of("1234567890-"));

    //--assert that the hourly ssn id isn't too big or too small an input//
    BOOST_ASSERT(salaried_ssn_ID.size() == 9 || salaried_ssn_ID.size() == 11);


   

    employee_ssn=SSN(salaried_ssn_ID);
    employee_pay=std::strtod(salaried_pay.c_str(),&end);
    employee_name=salaried_name;

    //POST CONDITION SECTION//

    //post-condition: name and ssn are initialized//
    BOOST_ASSERT(employee_name.empty()==false&&employee_ssn.str().empty()==false);
    //post-condition: pay was initialized//
    BOOST_ASSERT((std::fabs(0.0 - employee_pay) < 1.0 / 10000000)==false);
    //Finally, the invariant//
    BOOST_ASSERT(SalariedInvariant());
}
long double SalariedEmployee::computePay()
{
    BOOST_ASSERT(SalariedInvariant());
    //precondition: pay is a valid double greater than zero (the default value of doubles) //
    BOOST_ASSERT((std::abs(0.0 - (employee_pay)) < 1.0 / 10000000)==false&&isnan(employee_pay)==false);
    return employee_pay;
    BOOST_ASSERT(SalariedInvariant());
}

void SalariedEmployee::display()
{
    BOOST_ASSERT(SalariedInvariant());
    //employee_pay is a proper double//
    BOOST_ASSERT((std::fabs(0.0 - employee_pay) < 1.0 / 10000000)==false&&isnan(employee_pay)==false);
    //assure that employee name has a value//
    BOOST_ASSERT(employee_name.empty()==false);

    std::cout<<"Employee Name: "<<employee_name<<std::endl;
    std::printf("Employee Pay: %.2Lf\n",computePay());
    std::cout<<"-------------------------------"<<std::endl;

    BOOST_ASSERT(SalariedInvariant());
}