#pragma once
#include <vector>
#include "Shape.h"

class Board
{
public:
	Board(const int InWidth, const int InHeight, const int InBorderWidth);
	~Board() = default;

	void Draw();
	void Undo();
	void Clear();

	void AddShape(std::shared_ptr<Shape> shape);
	void SetPixel(const int x, const int y);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	std::vector<std::string> Dump();
	std::vector<std::shared_ptr<Shape>> GetShapes() const { return shapes; }
private:
	void Initialize();

	std::vector<std::vector<char>> board;
	std::vector<std::shared_ptr<Shape>> shapes;
	int width, height, borderWidth;
};
