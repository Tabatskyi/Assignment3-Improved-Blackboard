#pragma once
#include "Shape.h"
#include "Board.h"
#include "Line.h"

class Triangle : public Shape
{
public:
	Triangle(const std::vector<int>& params) : base(params[0]), height(params[1]), x(params[2]), y(params[3]), id(std::hash<std::string>{}(this->GetParameters())) {}
	~Triangle() = default;
	void Draw(Board& board) const override;
	void Change(const std::vector<int>& params) override;

	unsigned long long GetId() const override { return id; }
	std::string GetParameters() const override { return std::format("Triangle, base {}, height {}, start at X{}, Y{}", base, height, x, y); }
	std::string Dump() const override { return std::format("triangle {} {} {} {}", base, height, x, y); }
private:
	int base, height, x, y;
	unsigned long long id;
};