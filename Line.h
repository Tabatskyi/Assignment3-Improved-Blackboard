#pragma once
#include "Shape.h"
#include "Board.h"

class Line : public Shape
{
public:
	Line(const std::vector<int>& params) : xA(params[0]), yA(params[1]), xB(params[2]), yB(params[3]), id(std::hash<std::string>{}(this->GetParameters())) {}
	~Line() = default;
	void Draw(Board& board) const override;

	unsigned long long GetId() const override { return id; }
	std::string GetParameters() const override { return std::format("Line, from X{}, Y{} to X{}, Y{}", xA, yA, xB, yB); }
	std::string Dump() const override { return std::format("line {} {} {} {}", xA, yA, xB, yB); }
private:
	int xA, yA, xB, yB;
	unsigned long long id;
};