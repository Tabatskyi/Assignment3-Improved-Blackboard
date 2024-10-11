#pragma once
#include "Shape.h"
#include "Board.h"

class Line : public Shape
{
public:
	Line(const std::vector<int>& params) : xA(params[0]), yA(params[1]), xB(params[2]), yB(params[3]), id(std::hash<std::string>{}(this->Dump())) {}
	~Line() = default;
	void Draw(Board& board) const override;
	void Change(const std::vector<int>& params) override;

	std::string Dump() const override { return std::format("line {} {} {} {}", xA, yA, xB, yB); }
	unsigned long long GetId() const override { return id; }
	int GetXA() const { return xA; }
	int GetYA() const { return yA; }
	int GetXB() const { return xB; }
	int GetYB() const { return yB; }
private:
	int xA, yA, xB, yB;
	unsigned long long id;
};