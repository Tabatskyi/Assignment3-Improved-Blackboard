#pragma once
#include <iostream>
#include <string>
#include <format>

class Board;

class Shape
{
public:
	virtual ~Shape() = default;
	virtual void Draw(Board& board) const = 0;

	virtual unsigned long long GetId() const = 0;
	virtual std::string GetParameters() const = 0;
	virtual std::string Dump() const = 0;
};