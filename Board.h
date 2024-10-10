#pragma once
#include <vector>
#include "Shape.h"

class Board
{
public:
	Board(const unsigned int InWidth, const unsigned int InHeight, const unsigned int InBorderWidth);
	~Board() = default;

	void Draw();
	void Undo();
	void Clear();

	void AddShape(std::shared_ptr<Shape> shape);
	void SetPixel(const unsigned int x, const unsigned int y);

	unsigned int GetWidth() const { return width; }
	unsigned int GetHeight() const { return height; }

	std::vector<std::string> Dump();
	std::vector<std::shared_ptr<Shape>> GetShapes() const { return shapes; }
private:
	void Initialize();

	std::vector<std::vector<char>> board;
	std::vector<std::shared_ptr<Shape>> shapes;
	unsigned int width, height, borderWidth;
};
