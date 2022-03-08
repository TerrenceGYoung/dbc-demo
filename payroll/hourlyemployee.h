// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef HOURLY_H
#define HOURLY_H

#include "employee.h"
#include "../ssn/ssn.h"

class HourlyEmployee : public Employee {
private:
    long double employee_hours;
public:
        ~HourlyEmployee() override;
        HourlyEmployee(const std::string& hourly_name, const std::string& hourly_ssn_ID, const std::string& hourly_hours, const std::string& hourly_pay);
        long double computePay() override;
     // class HourlyEmployee//
     //CLion did not allow me to override the base function so I made another//
    bool HourlyInvariant() const;
    void display() override;
}; // class HourlyEmployee

#endif
