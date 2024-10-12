#pragma once
#include <vector>
#include <map>
#include <windows.h>
#include "Shape.h"

class Board
{
public:
	Board(const int InWidth, const int InHeight, const int InBorderWidth);
	~Board() = default;

	void Draw();
	void Undo();
	void Clear();

	void Remove(std::shared_ptr<Shape>& shape);

	void AddShape(std::shared_ptr<Shape>& shape);
	void SetPixel(const int x, const int y, const std::string& color);

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	std::vector<std::string> Dump();
	std::vector<std::shared_ptr<Shape>> GetShapes() const { return shapes; }
private:
	void Initialize();
	std::map<std::string, int> colorMap = { {"black", 0}, {"gray", 8}, {"blue", 9}, {"green", 10}, {"cyan", 11}, {"red", 12}, {"magenta", 13}, {"yellow", 14}, {"white", 15}};
	std::vector<std::vector<std::tuple<char, int>>> board; // char, color
	std::vector<std::shared_ptr<Shape>> shapes;
	int width, height, borderWidth;
};
