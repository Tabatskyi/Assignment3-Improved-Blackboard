#pragma once
#include "Board.h"

class Circle : public Shape
{
public:
	Circle(const std::vector<int>& params) : radius(params[0]), x(params[1]), y(params[2]), id(std::hash<std::string>{}(this->Dump())) {}
	~Circle() = default;
	void Draw(Board& board) const override;
	void Change(const std::vector<int>& params) override;

	std::string Dump() const override { return std::format("circle {} {} {}", radius, x, y); }
	unsigned long long GetId() const override { return id; }
	int GetRadius() const { return radius; }
	int GetX() const { return x; }
	int GetY() const { return y; }
private:
	int radius, x, y;
	unsigned long long id;
};