#include "spreadsheet.h"

SpreadSheet::SpreadSheet()
    : SpreadSheet(2, 2)
{}

SpreadSheet::SpreadSheet(size_t size)
    : SpreadSheet(size, size)
{}

SpreadSheet::SpreadSheet(size_t row, size_t col)
    : s_row{ row }
    , s_col{ col }
    , s_arr{ new Cell* [s_row] }
{
    for (int i = 0; i  < s_row; ++i) {
        s_arr[i] = new Cell[s_col];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
    : s_row{ rhv.s_row }
    , s_col{ rhv.s_col }
    , s_arr{ new Cell* [s_row] }
{
    for (int i = 0; i < s_row; ++i) {
        s_arr[i] = new Cell[s_col];
    }
    for (int i = 0; i < s_row; ++i) {
        for (int j = 0; j < s_col; ++j) {
            s_arr[i][j] = rhv.s_arr[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
    : s_row{ rhv.s_row }
    , s_col{ rhv.s_col }
    , s_arr{ new Cell * [s_row] }
{
    rhv.s_row  = 0;
    rhv.s_col = 0;
    rhv.s_arr = nullptr;
}

const SpreadSheet& SpreadSheet::operator= (const SpreadSheet& rhv)
{
    if (this != &rhv) {
        for (int i = 0; i < s_row; ++i) {
            delete[] s_arr[i];
        }
        delete s_arr;
        s_row = rhv.s_row;
        s_col  = rhv.s_col;
        s_arr = new Cell* [ s_row];

        for (int i = 0; i < s_row; ++i) {
            s_arr[i] = new Cell[s_col];
        }

        for (int i = 0; i < s_row; ++i) {
            for (int j = 0; j < s_col; ++i) {
                s_arr[i][j] = rhv.s_arr[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator= (SpreadSheet&& rhv)
{
    if (this != &rhv) {
        for (int i = 0; i < s_row; ++i) {
            delete[] s_arr[i];
        }
        delete s_arr;
        s_row = rhv.s_row;
        s_col = rhv.s_col;
        s_arr =  rhv.s_arr;
        rhv.s_arr = nullptr;
    }
    return *this;
}

void SpreadSheet::clear() noexcept
{
    for (int i = 0; i < s_row; ++i) {
        delete[] s_arr[i];
    }
    delete[] s_arr;
    s_arr = nullptr;
    s_col = 0;
    s_row = 0;
}

size_t SpreadSheet::row() const
{
    return s_row;
}

size_t SpreadSheet::col() const
{
    return s_col;
}

void SpreadSheet::resizeRow(int new_row, int value)
{
    int size = s_row + new_row;
    Cell** tmp = new Cell * [size];
    for (int i = 0; i < size; ++i) {
        tmp[i] = new Cell[s_col];
    }
    for (int i = 0; i < s_row; ++i) {
        for (int j = 0; j < s_col; ++j) {
            tmp[i][j] = s_arr[i][j];
        }
    }
    for (int i = s_row; i < size; ++i) {
        for (int j = 0; j < s_col; ++j) {
            tmp[i][j] = value;
        }
    }
    for (int i = 0; i < s_row; ++i) {
        delete[] s_arr[i];
    }
    delete[] s_arr;
    s_arr = tmp;
    s_row = size;
    tmp = nullptr;
}

void SpreadSheet::resizeCol(int new_col, int value)
{
    int size = s_col + new_col;
    Cell** tmp = new Cell * [s_row];
    for (int i = 0; i < s_row; ++i) {
        tmp[i] = new Cell[size];
    }
    for (int i = 0; i < s_row; ++i) {
        for (int j = 0; j < s_col; ++j) {
            tmp[i][j] = s_arr[i][j];
        }
    }
    for (int i = 0; i < s_row; ++i) {
        for (int j = s_col; j < size; ++j) {
            tmp[i][j] = value;
        }
    }
    for (int i = 0; i < s_row; ++i) {
        delete[] s_arr[i];
    }
    delete[] s_arr;
    s_arr = tmp;
    s_col = size;
    tmp = nullptr;
}

void SpreadSheet::resize(int newrow, int newcol, int val)
{
    resizeRow(newrow, val);
    resizeCol(newcol, val);
}

void SpreadSheet::mirrorH()
{
    for (int i = 0; i < s_row / 2; ++i) {
        for (int j = 0; j < s_col; ++j) {
            std::swap(s_arr[i][j], s_arr[s_row - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorV()
{
    for (int i = 0; i < s_row; ++i) {
        for (int j = 0; j < s_col / 2; ++j) {
            std::swap(s_arr[i][j], s_arr[i][s_col - j - 1]);
        }
    }
}

void SpreadSheet::mirrorD()
{
    for (int i = 1; i  < s_row; ++i) {
        for (int j = 0; j <  i; ++j) {
            std::swap(s_arr[i][j], s_arr[j][i]);
        }
    }
}

void SpreadSheet::mirrorSD()
{
    for (int i = 0; i < s_row; ++i) {
        for (int j = 0; j < s_col - i; ++j) {
            std::swap(s_arr[i][j], s_arr[s_row - 1 - j][s_col - 1 - i]);
        }
    }
}

void SpreadSheet::rotate(size_t count)
{
    bool f = false;
    if (count < 0) {
        
        f = true;
        count *= -1;
    }
    count = count % 4;
    if (count == 0) {
        return;
    }
    if (!f) {
        for (int i = 0; i <count; ++i) {
            mirrorH();
            mirrorD();
        }
    }
    else {
        for (int i = 0; i < count; ++i) {
            mirrorV();
            mirrorD();
        }
    }
}

void SpreadSheet::removeRow(size_t row)
{
    if (row >= s_row) {
        throw std::out_of_range( "Invalid index!");
    }

    row -=1;
    Cell** tmp = new Cell * [s_row - 1];
    for (int i = 0, k = 0; i < s_row; ++i) {
        if (i == row) {
            continue;
        }
        tmp[k] = new Cell[s_col];
        for (int j = 0; j < s_col; ++j) {
            tmp[k][j] = s_arr[i][j];
        }
        ++k;
    }

    for (int i = 0; i < s_row; ++i) {
        delete[] s_arr[i];
    }
    delete[] s_arr;

    s_arr = tmp;
    --s_row;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows)
{
    auto it = rows.end();
    while (it != rows.begin()) {
        --it;
        removeRow(*it);
    }
}

void SpreadSheet::removeCol(size_t col)
{
    if (col >= s_col) {
        throw std::out_of_range("Invalid index!");
    }

    col -= 1;

    Cell** temp = new Cell* [s_row];
    for (int i = 0; i < s_row; ++i) {
        temp[i] = new Cell[s_col - 1];
        for (int j = 0, k = 0; j < s_col; ++j) {
            if (j == col){
                continue;
            }
            temp[i][k++] = s_arr[i][j];
        }
    }

    for (int i = 0; i < s_row; ++i) {
        delete[] s_arr[i];
    }
    delete[] s_arr;

    s_arr = temp;
    --s_col;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols)
{
    auto it = cols.end();
    while ( it != cols.begin()) {
        --it;
        removeCol(*it);
    }
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet slicedSt;
    size_t numrows = rows.size();
    size_t numcols = cols.size();
    slicedSt.s_row = numrows;
    slicedSt.s_col = numcols;
    slicedSt.s_arr = new Cell * [numrows];

    size_t rowindex = 0;
    for (auto row : rows) {
        size_t colindex = 0;
        slicedSt.s_arr[rowindex]  = new Cell[ numcols];
        for (auto col : cols) {
            slicedSt.s_arr[rowindex][colindex] = s_arr[row - 1][col - 1];
            colindex++;
        }
        rowindex++;
    }
    return slicedSt;
}

SpreadSheet::~SpreadSheet()
{ 
    clear();
}

Proxy SpreadSheet::operator[] (size_t index)
{
    return  Proxy(s_arr[index]);
}

const Proxy SpreadSheet::operator[] (size_t  index) const
{
    return Proxy(s_arr[index]);
}

Proxy::Proxy(Cell* ptr)
    : c_ptr{ ptr }
{}

Cell& Proxy::operator[] (size_t index)
{
    return c_ptr[index];
}

const Cell& Proxy::operator[] (size_t index) const
{
    return c_ptr[index];
}

std::ostream& operator<<  (std::ostream& out, const SpreadSheet& rhv)
{
    int width = 7;
    double widthtable = rhv.col() * 8.2;
    int h_line = 1;
    for (size_t i = 0; i < rhv.row(); ++i)
    {
        for (size_t k = 0; k < widthtable; ++k)
        {
            out << std::setw(1) << "-";
        }
        out << "\n";
        for (size_t j = 0; j < rhv.col(); ++j)
        {
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << rhv[i][j];
        }
        out << std::setw(h_line) << "|";
        out << "\n";
    }
    for (size_t k = 0; k < widthtable; ++k)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    if ((lhs.col() != rhs.col()) || (lhs.row() != rhs.row())) {
        return false;
    }
    for (int i = 0; i < lhs.row(); ++i) {
        for (int j = 0; j < lhs.col(); ++j) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    return !(lhs == rhs);
}
