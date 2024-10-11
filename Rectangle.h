#pragma once
#include "Parallelogram.h"

class Rectangle : public Parallelogram
{
public:
    Rectangle(const std::vector<int>& params) :
        Parallelogram({params[2], params[3], params[2] + params[0], params[3] + params[1], params[0]}),
        width(params[0]), height(params[1]), x(params[2]), y(params[3]), id(std::hash<std::string>{}(this->GetParameters())) {}
    ~Rectangle() = default;

	void Change(const std::vector<int>& params) override 
        { width = params[0]; height = params[1]; x = params[2]; y = params[3]; Parallelogram::Change({ x, y, x + width, y + height, width }); }

    unsigned long long GetId() const override { return id; }
	std::string GetParameters() const override { return std::format("Rectangle, start at {}, {} with base width {} and height {}", x, y, width, height); }
	std::string Dump() const override { return std::format("rectangle {} {} {} {}", width, height, x, y); }
private:
    int width, height, x, y;
	unsigned long long id;
};