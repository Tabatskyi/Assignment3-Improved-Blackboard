#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <format>

class Board;

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void Draw(Board& board) const = 0;
	virtual void Change(const std::vector<int>& params) = 0;

	virtual unsigned long long GetId() const = 0;
	virtual std::string Dump() const = 0;
};