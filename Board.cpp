#include "Board.h"

Board::Board(const unsigned int InWidth, const unsigned int InHeight, const unsigned int InBorderWidth) : width(InWidth), height(InHeight), borderWidth(InBorderWidth)
{
	if (width == 0 || height == 0 || borderWidth >= width || borderWidth >= height)
		throw std::invalid_argument("Invalid board dimensions");
	Initialize();
}

void Board::Initialize()
{
	board.resize(height);
	for (unsigned int i = 0; i < height; ++i)
	{
		board[i].resize(width);
		for (unsigned int j = 0; j < width; ++j)
		{
			if (i < borderWidth || (i >= height - borderWidth && i <= height))
				board[i][j] = '=';
			else if (j < borderWidth || (j >= width - borderWidth && j <= width))
				board[i][j] = '|';
			else
				board[i][j] = ' ';
		}
	}
}

void Board::SetPixel(const unsigned int x, const unsigned int y)
{
	if (x < borderWidth || x >= width - borderWidth || y < borderWidth || y >= height - borderWidth)
		return;
	board[y][x] = '*';
}

void Board::AddShape(std::shared_ptr<Shape> shape)
{
	shapes.push_back(shape);
}

void Board::Undo()
{
	if (shapes.size() > 0)
		shapes.pop_back();
}

void Board::Clear()
{
	shapes.clear();
}

void Board::Draw()
{
	Initialize();
	for (std::shared_ptr<Shape> shape : shapes)
		shape->Draw(*this);

	for (unsigned int i = 0; i < height; ++i)
	{
		for (unsigned int j = 0; j < width; ++j)
			std::cout << board[i][j];
		std::cout << std::endl;
	}
}

std::vector<std::string> Board::Dump()
{
	std::vector<std::string> dump;
	dump.push_back(std::format("board {} {} {}", width, height, borderWidth));
	for (std::shared_ptr<Shape> shape : shapes)
		dump.push_back(shape->Dump());
	return dump;
}