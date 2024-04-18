#include "cell.h"
#include <iostream>
#include <sstream>

Cell::Cell()
    : mycell("")
{}

Cell::Cell(int rhv)
    : mycell{ std::to_string(rhv) }
{}

Cell::Cell(bool rhv)
    : mycell{ rhv ? "true" : "false" }
{}

Cell::Cell(char rhv)
    : mycell{ std::string(1, rhv) }
{}

Cell::Cell(double rhv)
    : mycell{ std::to_string(rhv) }
{}

Cell::Cell(std::string rhv)
    : mycell{ rhv }
{}


Cell::Cell(const std::vector<int>& rhv)
{
    mycell = "{";
    for (int i = 0; i < rhv.size(); ++i) {
        mycell += std::to_string(rhv[i]) + " ,";
    }
    
    mycell.pop_back();
    mycell += "}";
}

Cell::Cell(const Cell& rhv)
    : mycell{ rhv.mycell }
{}

Cell::Cell(Cell&& rhv) noexcept
    : mycell(std::move(rhv.mycell))
{}


Cell::operator int()
{
    try {
        int x = std::stoi(mycell);
        return x;
    }
    catch (...) {
        return 0;
    }
}

Cell::operator double()
{
    try {
        double x = std::stod(mycell);
        return x;
    }
       catch (...) {
        return 0.0;
    }
}

Cell::operator std::string() const
{
    return mycell;
}

Cell::operator bool()
{
    return !mycell.empty();
}

Cell::operator char()
{
    if (!mycell.empty()) {
        return mycell[0];
    }
    else {
        return '\0';
    }
}

Cell::operator std::vector<int>()
{
    std::vector<int> result;
    std::string tmp = mycell;
    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == '{' || tmp[i] == '}' || tmp[i] == ',') {
            tmp[i] = ' ';
        }
    }
    std::stringstream strs(tmp);
    int num;
    while (strs >> num) {
        result.push_back(num);
    }
    return result;
}

Cell& Cell::operator= (const Cell& rhv)
{
    if (this != &rhv) {
        mycell = rhv.mycell;
    }
    return *this;
}

Cell& Cell::operator= (Cell&& rhv) noexcept
{
    if (this != &rhv) {
        mycell = std::move(rhv.mycell);
    }
    return *this;
}

Cell& Cell::operator= (int a)
{
    mycell = (int)a;
    return *this;
}

Cell& Cell::operator= (double a)
{
    mycell = (double)a;
    return *this;
}


Cell& Cell::operator=(char rhv)
{
    mycell = rhv;
    return *this;
}

Cell& Cell::operator= (bool rhv)
{
    mycell = rhv ? "true" : "false";
    return *this;
}
Cell& Cell::operator= (std::string str)
{
    mycell = str;
    return *this;
}

Cell& Cell ::operator= (const std::vector<int>& rhv)
{
    mycell = "{";
    for (int i  = 0; i < rhv.size(); ++i) {
        mycell += std::to_string(rhv[i]) + " ,";
    }
    mycell.pop_back();
    mycell += "}";
    return *this;
}

bool operator== (const Cell& oth1, const Cell& oth2)
{
    return 1;
}

bool operator!= (const Cell& oth1, const Cell& oth2)
{
    return 1;
}


std::ostream& operator<< (std::ostream& out, const Cell& rhv)
{
    out << std::string(rhv);

    return out;
}


std::istream& operator>> (std::istream& in, Cell& rhv)
{
    std::string str;
    in >> str;

    rhv = Cell(str);
    return in;
}