// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef SALARIED_H
#define SALARIED_H

#include "employee.h"
using namespace std;


class SalariedEmployee : public Employee
{
public:
    SalariedEmployee(const std::string& salaried_name, const std::string& salaried_ssn_ID, const std::string& salaried_pay);
    ~SalariedEmployee() override;
    bool SalariedInvariant() const;
    //employee pay is a string in order for it to have its value tested to see if it's a double before inputting//
    void display() override;
    long double computePay() override;
};

#endif
