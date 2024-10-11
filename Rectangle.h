#pragma once
#include "Parallelogram.h"

class Rectangle : public Parallelogram
{
public:
    Rectangle(const bool InFill, const std::string& InColor, const std::vector<int>& params) :
		fill(InFill), color(InColor), Parallelogram(fill, color, {params[2], params[3], params[2] + params[0], params[3] + params[1], params[0]}),
        width(params[0]), height(params[1]), x(params[2]), y(params[3]), id(std::hash<std::string>{}(this->Dump())) {}
    ~Rectangle() = default;

	void Change(const std::vector<int>& params) override 
    { 
		if (params.size() != 4)
			throw std::invalid_argument("Invalid number of parameters");
        width = params[0]; height = params[1]; x = params[2]; y = params[3]; 
        Parallelogram::Change({ x, y, x + width, y + height, width }); 
    }

	std::string Dump() const override { return std::format("rectangle {} {} {} {} {} {}", this->GetFill(), color, width, height, x, y); }
    unsigned long long GetId() const override { return id; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	std::string GetColor() const { return color; }
	std::string GetFill() const { return fill ? "fill" : "frame"; }
private:
	bool fill;
	std::string color;
    int width, height, x, y;
	unsigned long long id;
};