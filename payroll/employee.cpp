// dbc-demo - A Design by Contract demonstration project
// Copyright (C) 2020 Dr.-Ing. Jens Hannemann - j.hannemann@ieee.org
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <employee.h>
#include <assertexcept.h>

#include <utility>

bool Employee::invariant() const
{
    BOOST_ASSERT_MSG(false, "Invariant not implemented");
    return true;
}
Employee::~Employee()
{

}
Employee::Employee(std::string name, SSN ssn_ID, const std::string& pay) : employee_ssn(ssn_ID)
{
    char *end;
 employee_ssn=SSN(std::move(ssn_ID));
 employee_name=std::move(name);
 employee_pay= std::strtod(pay.c_str(),&end);
}
long double Employee::computePay()
{
 return employee_pay;
}

void Employee::display()
{
  std::cout<<"Payroll from Base Class"<<std::endl;
}

void Employee::final_print()
{
    display();
}
