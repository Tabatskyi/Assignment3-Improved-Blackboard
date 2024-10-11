#pragma once
#include "Shape.h"
#include "Board.h"
#include "Line.h"

class Triangle : public Shape
{
public:
	Triangle(const bool InFill, const std::string& InColor, const std::vector<int>& params) :
		fill(InFill), color(InColor), base(params[0]), height(params[1]), x(params[2]), y(params[3]), id(std::hash<std::string>{}(this->Dump())) {}
	~Triangle() = default;
	void Draw(Board& board) const override;
	void Change(const std::vector<int>& params) override;

	std::string Dump() const override { return std::format("triangle {} {} {} {} {} {}", this->GetFill(), color, base, height, x, y); }
	unsigned long long GetId() const override { return id; }
	int GetBase() const { return base; }
	int GetHeight() const { return height; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	std::string GetColor() const { return color; }
	std::string GetFill() const { return fill ? "fill" : "frame"; }
private:
	bool fill;
	std::string color;
	int base, height, x, y;
	unsigned long long id;
};