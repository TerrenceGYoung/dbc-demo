// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <vector>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <memory>

#include <assertexcept.h>
#include <employee.h>
#include <hourlyemployee.h>
#include <salariedemployee.h>
int main() {
    try {
        std::vector<std::unique_ptr<Employee>> payroll;
        std::ifstream file("../payroll/payroll.csv");
        //../ssn/ssn.h"//
        std::vector<std::string> strings;
        std::string line;
        // build and process payroll

        //get the input from the file and put it into line//
        while(!file.eof())
        {
                getline(file,line);
                if(!line.empty())
                {
                    //use istringstream and the following loop to split up lines of input by whitespace//

                    istringstream iss(line);
                    std::vector<std::string> split_input;
                    std::string input_holder;
                    for(std::string s;iss>>s;)
                    {
                        split_input.push_back(s);
                    }

                    //inputs in order:first_name--0, last_name--1,ID--2, account_type--3,hours--4, pay--5//
                    if(split_input[3]=="hourly")
                    {
                        //std::string name, SSN ssn_ID, std::string pay, std::string rate//
                        SSN ssn_input=SSN(split_input[2]);
                        payroll.push_back((std::make_unique<HourlyEmployee>((split_input[0]+" "+split_input[1]),split_input[2],split_input[4],split_input[5])));
                    }
                    else if(split_input[3]=="salaried")
                    {
                        SSN ssn_input=SSN(split_input[2]);
                        payroll.push_back(std::make_unique<SalariedEmployee>((split_input[0]+" "+split_input[1]),split_input[2],split_input[4]));
                    }
                }
                else
                {
                    cout<<"end of file"<<endl;
                }
        }

        cout<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"PRINTING OF PAYROLL LOGS"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<endl;

        //print from payroll//
        for(auto & i : payroll)
        {
            i->final_print();
        }

        cout<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"DELETION OF PAYROLL LOGS"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<endl;

        //empty out the vector//
        for(unsigned long int i=0;i<(payroll.size());i++)
        {
            Employee * tempEmployee;
            tempEmployee=payroll[i].release();
            delete tempEmployee;
            payroll.pop_back();
        }



    }
    catch (AssertException& e) {
        std::cerr << "Assertion Exception caught: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (std::runtime_error& e) {
        std::cerr << "Standard exception caught: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "Unknown exception caught\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


