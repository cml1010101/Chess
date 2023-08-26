#include <Point.hpp>
#include <ostream>
using namespace chess;
using namespace std;
ostream& operator<<(ostream& out, Point point)
{
    out << "(" << point.row << ", " << point.col << ")";
    return out;
}