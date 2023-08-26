#ifndef POINT_HPP
#define POINT_HPP
#include <initializer_list>
#include <vector>
#include <string>
namespace chess
{
    class Point
    {
    public:
        int row, col;
        inline Point()
        {
            row = -1;
            col = -1;
        }
        Point(int row, int col)
        {
            this->row = row;
            this->col = col;
        }
        Point(std::initializer_list<int> meta)
        {
            this->row = meta.begin()[0];
            this->col = meta.begin()[1];
        }
        Point(std::vector<int> meta)
        {
            this->row = meta[0];
            this->col = meta[1];
        }
        inline friend Point operator+(Point a, Point b)
        {
            return {a.row + b.row, a.col + b.col};
        }
        inline friend Point operator-(Point a, Point b)
        {
            return {a.row - b.row, a.col - b.col};
        }
        inline friend Point operator*(Point a, int b)
        {
            return {a.row * b, a.col * b};
        }
        inline friend Point operator/(Point a, int b)
        {
            return {a.row / b, a.col / b};
        }
        inline friend Point operator+(Point a, std::initializer_list<int> meta)
        {
            return {a.row + meta.begin()[0], a.col + meta.begin()[1]};
        }
        inline friend Point operator-(Point a, std::initializer_list<int> meta)
        {
            return {a.row - meta.begin()[0], a.col - meta.begin()[1]};
        }
        inline operator bool()
        {
            return (row >= 0 && row < 8) && (col >= 0 && col < 8);
        }
        inline friend bool operator==(Point a, Point b)
        {
            return a.row == b.row && a.col == b.col;
        }
        inline static Point parse(std::string str)
        {
            return {str[1] - '1', (str[0] >= 'a') ? (str[0] - 'a') : (str[0] - 'A')};
        }
        inline operator std::string()
        {
            char* buffer = new char[3];
            buffer[0] = col + 'a';
            buffer[1] = row + '1';
            buffer[2] = 0;
            return std::string(buffer);
        }
    };
}
#endif