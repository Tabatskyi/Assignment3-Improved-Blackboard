#pragma once
#include "Board.h"

class Circle : public Shape
{
public:
	Circle(const bool InFill, const std::string& InColor, const std::vector<int>& params) :
		fill(InFill), color(InColor), radius(params[0]), x(params[1]), y(params[2]), id(std::hash<std::string>{}(this->Dump())) {}
	~Circle() = default;
	void Draw(Board& board) const override;
	void Change(const std::vector<int>& params) override;
	void Paint(const std::string& InColor) override { color = InColor; }

	std::string Dump() const override { return std::format("circle {} {} {} {} {}", this->GetFill(), color, radius, x, y); }
	unsigned long long GetId() const override { return id; }
	int GetRadius() const { return radius; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	std::string GetColor() const { return color; }
	std::string GetFill() const { return fill ? "fill" : "frame"; }
private:
	bool fill;
	std::string color;
	int radius, x, y;
	unsigned long long id;
};