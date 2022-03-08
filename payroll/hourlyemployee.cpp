// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <hourlyemployee.h>
#include <assertexcept.h>

#include <utility>
#include <cstdlib>
#include <cmath>
#include <cstdlib>
using namespace std;

bool HourlyEmployee::HourlyInvariant() const
{

        //Checking members to see if they have values//

    BOOST_ASSERT(( ( std::fabs(0.0 - employee_hours) < (1.0 / 10000000 ))==false)&&(isnan(employee_hours)==false));
        //employee pay should not be less than or equal to zero or not a number//
    BOOST_ASSERT(( ( std::fabs(0.0 - employee_pay) < (1.0 / 10000000 ))==false)&&(isnan(employee_pay)==false));
    //employee hours should not be less than or equal to zero or not a number//

        //employee_name cannot be empty//
        BOOST_ASSERT(!employee_name.empty()==true);
        //SSN cannot be empty//
        BOOST_ASSERT(employee_ssn.str().empty()==false);
        //SSN should have a valid value and size//
        //code copied over from SSN class//
        BOOST_ASSERT(std::regex_match(employee_ssn.str(), employee_ssn.inputRegex()));
        //  Valid SSN //
        BOOST_ASSERT(employee_ssn.str().size() == 9 || employee_ssn.str().size() == 11);
        // "SSN has the right size")//
        //name should not contain any non UTF8 characters and must be composed of english characters//
        std::regex english_characters ("^[a-zA-Z[:space:]]*$");
        BOOST_ASSERT(std::regex_match(employee_name,english_characters));

    return true;
}




HourlyEmployee::~HourlyEmployee()
{
    std::cout <<"\\"<<employee_name<<"\\"" payroll log removed." << std::endl;
}

HourlyEmployee::HourlyEmployee(const std::string& hourly_name, const std::string& hourly_ssn_ID, const std::string& hourly_hours, const std::string& hourly_pay): Employee(hourly_name, SSN(hourly_ssn_ID), hourly_pay)
        {
            //PRECONDITION SECTION//

            //variable used for the conversion of string inputs using the strtod function//
            char *end;
            //assert that none of the string inputs are empty//
            BOOST_ASSERT((hourly_name.empty()==false)&&(hourly_pay.empty()==false)&&(hourly_ssn_ID.empty()==false)&&(hourly_hours.empty()==false));


            //Validating the Pay input//
            //--assert that the string that parameter hourly_pay contains could be converted into  a valid double value//
            BOOST_ASSERT(hourly_pay.find_first_not_of("1234567890."));

            //--assert that hourly_pay and hourly_pay's values are greater than 0 (meaning they were given a value) and are also valid doubles//
            BOOST_ASSERT((std::fabs(0.0 - (std::strtod(hourly_pay.c_str(),&end))) < 1.0 / 10000000)==false&&isnan(std::strtod(hourly_pay.c_str(),&end))==false);

            //Validating the SSN Input//

            //--assert that SSN is a string that isn't empty//
            BOOST_ASSERT(hourly_ssn_ID.empty()==false);

            //--assert that the input of the ssn is composed of a set of numbers and dashes//
            BOOST_ASSERT(hourly_ssn_ID.find_first_not_of("1234567890-"));

            //--assert that the hourly ssn id isn't too big or too small an input//
            BOOST_ASSERT(hourly_ssn_ID.size() == 9 || hourly_ssn_ID.size() == 11);


            //Validating the Hours input//
            //--assert that the double hourly_hours is a valid double//
            BOOST_ASSERT(hourly_hours.find_first_not_of("1234567890."));

            //--assert the double is greater than 0 and is also a number//
            BOOST_ASSERT((std::fabs(0.0 - (std::strtod(hourly_hours.c_str(),&end))) < 1.0 / 10000000)==false&&isnan(std::strtod(hourly_hours.c_str(),&end))==false);

            employee_ssn=SSN(hourly_ssn_ID);
            employee_pay=std::strtod(hourly_pay.c_str(),&end);
            employee_name=hourly_name;
            employee_hours=std::strtod(hourly_hours.c_str(),&end);

            //POST CONDITION SECTION//

            //post-condition: name and ssn are initialized//
            BOOST_ASSERT(employee_name.empty()==false&&employee_ssn.str().empty()==false);
            //post-condition: pay was initialized//
            BOOST_ASSERT((std::fabs(0.0 - employee_pay) < 1.0 / 10000000)==false);
            //Finally, the invariant//
            BOOST_ASSERT(HourlyInvariant());
        }

long double HourlyEmployee::computePay()
{
    //Preconditions//
    //assert if employee_pay is a double or int value, as well as employee_hours, and both are non zero//
    BOOST_ASSERT(HourlyInvariant());
    //employee_hours is a proper double//
    BOOST_ASSERT((std::fabs(0.0 - employee_hours) < 1.0 / 10000000)==false&&isnan(employee_hours)==false);
    //employee_pay is a proper double//
    BOOST_ASSERT((std::fabs(0.0 - employee_pay) < 1.0 / 10000000)==false&&isnan(employee_pay)==false);


    long double payment=employee_pay*employee_hours;

    //postconditions//
    //assert that the result has a value and is a proper double value//
    BOOST_ASSERT((std::fabs(0.0 - payment) < 1.0 / 10000000)==false&&isnan(employee_hours)==false);
    //assert that the end result (payment) is equal or close enough to the expected value//
    BOOST_ASSERT((std::fabs((employee_pay*employee_hours) - payment) < 1.0 / 10000000)==true&&isnan(payment)==false);
    BOOST_ASSERT(HourlyInvariant());
    return payment;
}

void HourlyEmployee::display()
{
    BOOST_ASSERT(HourlyInvariant());
    //preconditions//
    //employee_hours is a proper double//
    BOOST_ASSERT((std::fabs(0.0 - employee_hours) < 1.0 / 10000000)==false&&isnan(employee_hours)==false);
    //employee_pay is a proper double//
    BOOST_ASSERT((std::fabs(0.0 - employee_pay) < 1.0 / 10000000)==false&&isnan(employee_pay)==false);
    //assure that employee name has a value/
    BOOST_ASSERT(employee_name.empty()==false);
    std::cout<<"Employee Name: "<<employee_name<<std::endl;
    std::printf("Employee Pay: %.2Lf\n",computePay());
    std::cout<<"-------------------------------"<<std::endl;
    BOOST_ASSERT(HourlyInvariant());
}
// class HourlyEmployee


