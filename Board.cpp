#include "Board.h"

Board::Board(const int InWidth, const int InHeight, const int InBorderWidth) : width(InWidth), height(InHeight), borderWidth(InBorderWidth)
{
	if (width == 0 || height == 0 || borderWidth >= width || borderWidth >= height)
		throw std::invalid_argument("Invalid board dimensions");
	Initialize();
}

void Board::Initialize()
{
	board.resize(height);
	for (int i = 0; i < height; ++i)
	{
		board[i].resize(width);
		for (int j = 0; j < width; ++j)
		{
			if (i < borderWidth || (i >= height - borderWidth && i <= height))
				board[i][j] = std::make_tuple('=', 15);
			else if (j < borderWidth || (j >= width - borderWidth && j <= width))
				board[i][j] = std::make_tuple('|', 15);
			else
				board[i][j] = std::make_tuple(' ', 0);
		}
	}
}

void Board::SetPixel(const int x, const int y, const std::string& color)
{
	if (x < borderWidth || x >= width - borderWidth || y < borderWidth || y >= height - borderWidth)
		return;

	int colorIndex;
	if (colorMap.find(color) == colorMap.end())
		colorIndex = 0;
	else
		colorIndex = colorMap[color];

	board[y][x] = std::make_tuple(toupper(color[0]), colorIndex);
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

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j) 
		{
			char c = std::get<0>(board[i][j]);
			int color = std::get<1>(board[i][j]);
			SetConsoleTextAttribute(hConsole, color);
			std::cout << c;
		}
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