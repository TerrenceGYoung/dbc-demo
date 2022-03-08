// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include "../ssn/ssn.h"

class Employee {
protected:
    bool invariant() const;
    std::string employee_name;
    SSN employee_ssn;
    long double employee_pay;

public:
    virtual void final_print();
    virtual void display();
    virtual ~Employee();
    Employee(std::string name, SSN ssn_ID, const std::string& pay);
    virtual long double computePay();
}; // class Employee

#endif // EMPLOYEE_H
