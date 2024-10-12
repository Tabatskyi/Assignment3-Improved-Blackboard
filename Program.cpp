#include <iostream>
#include <fstream>
#include <format>
#include <map>

#include "Line.h"
#include "Rect.h"
#include "Board.h"
#include "Shape.h"
#include "Parser.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Parallelogram.h"

static unsigned long long convertID(const std::string& id)
{
	unsigned long long convertedId;
	try
	{
		convertedId = std::stoull(id);
	}
	catch (const std::exception&)
	{
		return 0;
	}
	return convertedId;
}

static std::vector<int> convertParameters(const std::vector<std::string>& parameters)
{
	std::vector<int> convertedParameters;
	for (const std::string& parameter : parameters)
	{
		int convertedParameter;
		try
		{
			convertedParameter = stoi(parameter);
		}
		catch (const std::exception&)
		{
			return {};
		}
		convertedParameters.push_back(convertedParameter);
	}
	return convertedParameters;
}

static void add(std::string shapeType, std::vector<std::string> shapeParameters, std::unique_ptr<Board>& board)
{
	bool fill = shapeParameters[0] == "fill";
	std::string color = shapeParameters[1];
	std::vector<int> shapeIntParameters = convertParameters(std::vector<std::string>(shapeParameters.begin() + 2, shapeParameters.end()));
	size_t shapeParametersSize = shapeIntParameters.size();
	std::shared_ptr<Shape> shape;

	for (int parameter : shapeIntParameters)
	{
		if (parameter > board->GetHeight() && parameter > board->GetWidth())
		{
			std::cout << "Shape bigger than board or completely outside" << std::endl;
			return;
		}
	}
	
	if (shapeType == "circle" && shapeParametersSize == 3)
	{
		shape = std::make_shared<Circle>(fill, color, shapeIntParameters);
	}
	else if (shapeType == "square" && shapeParametersSize == 3)
	{
		shape = std::make_shared<Square>(fill, color, shapeIntParameters);
	}
	else if (shapeType == "line" && shapeParametersSize == 4)
	{
		shape = std::make_shared<Line>(color, shapeIntParameters);
	}
	else if (shapeType == "triangle" && shapeParametersSize == 4)
	{
		shape = std::make_shared<Triangle>(fill, color, shapeIntParameters);
	}
	else if (shapeType == "rectangle" && shapeParametersSize == 4)
	{
		shape = std::make_shared<Rect>(fill, color, shapeIntParameters);
	}
	else if (shapeType == "parallelogram" && shapeParametersSize == 5)
	{
		shape = std::make_shared<Parallelogram>(fill, color, shapeIntParameters);
	}
	else
	{
		std::cout << "Invalid shape" << std::endl;
		return;
	}

	for (std::shared_ptr<Shape> s : board->GetShapes())
	{
		if (s->Dump() == shape->Dump())
		{
			std::cout << "Shape already exists" << std::endl;
			return;
		}
	}

	board->AddShape(shape);
}

static void remove(std::shared_ptr<Shape>& shape, std::unique_ptr<Board>& board)
{
	if (shape == nullptr)
	{
		std::cout << "Shape not selected" << std::endl;
		return;
	}
	board->Remove(shape);
	std::cout << "Shape removed" << std::endl;
	return;
}

static void change(std::shared_ptr<Shape>& shape, std::vector<int> newParameters, std::unique_ptr<Board>& board)
{
	if (shape == nullptr)
	{
		std::cout << "Shape not selected" << std::endl;
		return;
	}
	try 
	{
		shape->Change(newParameters);
	}
	catch (const std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
		return;
	}
	board->Remove(shape);
	board->AddShape(shape);
	return;
}

static void save(const std::string& filename, const std::vector<std::string>& shapes)
{
	std::ofstream file(filename);
	if (file.is_open())
	{
		for (const std::string& shape : shapes)
			file << shape << std::endl;
		file.close();
	}
	else
		std::cout << "Unable to open file" << std::endl;
}

static std::unique_ptr<Board> load(const std::string& filename, std::unique_ptr<Parser>& parser)
{
	std::ifstream file(filename);
	std::vector<std::string> fileContent;

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			if (!line.empty())
				fileContent.push_back(line);
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return nullptr;
	}
	std::unique_ptr<Board> board;
	std::vector<std::string> boardParameters = parser->Parse(fileContent[0], " ");
	if (boardParameters[0] == "board" && boardParameters.size() == 4)
	{
		try 
		{
			board = std::make_unique<Board>(stoi(boardParameters[1]), stoi(boardParameters[2]), stoi(boardParameters[3]));
		}
		catch (const std::exception&)
		{
			std::cout << "Invalid board parameters" << std::endl;
			return nullptr;
		}
	}
	else
	{
		std::cout << "Invalid board parameters" << std::endl;
		return nullptr;
	}

	if (fileContent.size() == 1)
		return board;

	std::vector<std::string> shapes(fileContent.begin() + 1, fileContent.end());

	for (const std::string& shape : shapes)
	{
		std::vector<std::string> shapeParameters = parser->Parse(shape, " ");
		add(shapeParameters[0], std::vector<std::string>(shapeParameters.begin() + 1, shapeParameters.end()), board);
	}
	return board;
}

int main()
{
	std::string input;
	std::unique_ptr<Board> board;
	std::unique_ptr<Parser> parser = std::make_unique<Parser>();
	std::shared_ptr<Shape> selectedShape;

	do
	{
		if (board == nullptr)
			std::cout << "Initialize board with command: init width height borderWidth. Or load existing board" << std::endl;

		std::vector<std::string> parsedInput;
		std::cout << ">";
		getline(std::cin, input);

		if (input.empty())
			continue;

		parsedInput = parser->Parse(input, " ");

		std::string command = parsedInput[0];

		if (command == "init" && parsedInput.size() == 4) 
		{
			try 
			{
				board = std::make_unique<Board>(stoi(parsedInput[1]), stoi(parsedInput[2]), stoi(parsedInput[3]));
			}
			catch (const std::exception&)
			{
				std::cout << "Invalid board parameters" << std::endl;
			}
			continue;
		}
		else if (command == "load" && parsedInput.size() == 2)
		{
			board = load(parsedInput[1], parser);
			continue;
		}
		else if (command == "shapes")
		{
			std::cout << "Available shapes: " << std::endl;
			std::cout << "line startPointX startPointY endPointX endPointY" << std::endl;
			std::cout << "circle radius centerPointX centerPointY" << std::endl;
			std::cout << "triangle base height startPointX startPointY" << std::endl;
			std::cout << "parallelogram startPointX startPointY endPointX endPointY baseWidth" << std::endl;
			std::cout << "rectangle base height startPointX startPointY" << std::endl;
			std::cout << "square side startPointX startPointY" << std::endl;
		}
		else if (command == "help")
		{
			std::cout << "Commands: draw: draws board, add: adds specified shape, list: lists all added shapes, shapes: lists all available shapes, save: saves board state to file, load: loads board state from file, help, quit" << std::endl;
		}
		else if (command == "quit")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		
		if (board == nullptr)  // if board is not exist skip iteration
			continue;

		if (command == "draw")
		{
			board->Draw();
		}
		else if (command == "list")
		{
			std::cout << "Shapes:" << std::endl;
			for (std::shared_ptr<Shape> shape : board->GetShapes())
				if (std::shared_ptr<Line> line = std::dynamic_pointer_cast<Line>(shape))
					std::cout << std::format("ID: {} \n\t Type: Line, Color: {}, Start: ({}, {}), End: ({}, {})", line->GetId(), line->GetColor(), line->GetXA(), line->GetYA(), line->GetXB(), line->GetYB()) << std::endl;
				else if (std::shared_ptr<Circle> circle = std::dynamic_pointer_cast<Circle>(shape))
					std::cout << std::format("ID: {} \n\t Type: Circle, {}, Color: {}, Radius: {}, Center: ({}, {})", circle->GetId(), circle->GetFill(), circle->GetColor(), circle->GetRadius(), circle->GetX(), circle->GetY()) << std::endl;
				else if (std::shared_ptr<Triangle> triangle = std::dynamic_pointer_cast<Triangle>(shape))
					std::cout << std::format("ID: {} \n\t Type: Triangle, {}, Color: {}, Base: {}, Height: {}, Start: ({}, {})", triangle->GetId(), triangle->GetFill(), triangle->GetColor(), triangle->GetBase(), triangle->GetHeight(), triangle->GetX(), triangle->GetY()) << std::endl;
				else if (std::shared_ptr<Rect> rectangle = std::dynamic_pointer_cast<Rect>(shape))
					std::cout << std::format("ID: {} \n\t Type: Rectangle, {}, Color: {}, Base: {}, Height: {}, Start: ({}, {})", rectangle->GetId(), rectangle->GetFill(), rectangle->GetColor(), rectangle->GetWidth(), rectangle->GetHeight(), rectangle->GetX(), rectangle->GetY()) << std::endl;
				else if (std::shared_ptr<Square> square = std::dynamic_pointer_cast<Square>(shape))
					std::cout << std::format("ID: {} \n\t Type: Square, {}, Color: {}, Side: {}, Start: ({}, {})", square->GetId(), square->GetFill(), square->GetColor(), square->GetSide(), square->GetX(), square->GetY()) << std::endl;
				else if (std::shared_ptr<Parallelogram> parallelogram = std::dynamic_pointer_cast<Parallelogram>(shape))
					std::cout << std::format("ID: {} \n\t Type: Parallelogram, {}, Color: {}, Base: {}, Start: ({}, {}), End: ({}, {})", parallelogram->GetId(), parallelogram->GetFill(), parallelogram->GetColor(), parallelogram->GetWidth(), parallelogram->GetX0(), parallelogram->GetY0(), parallelogram->GetX1(), parallelogram->GetY1()) << std::endl;
		}
		else if (command == "clear")
		{
			board->Clear();
		}
		else if (command == "save" && parsedInput.size() == 2)
		{
			save(parsedInput[1], board->Dump());
		}
		else if (command == "add" && parsedInput.size() > 5)
		{
			add(parsedInput[1], std::vector<std::string>(parsedInput.begin() + 2, parsedInput.end()), board);
		}
		else if (command == "select" && parsedInput.size() == 2)
		{
			unsigned long long id = convertID(parsedInput[1]);
			for (std::shared_ptr<Shape> s : board->GetShapes())
				if (s->GetId() == id)
				{
					selectedShape = s;
					std::cout << std::format("Shape {} selected", id) << std::endl;
					break;
				}
			if (selectedShape == nullptr)
				std::cout << "Shape not found" << std::endl;
		}
		else if (command == "remove")
		{
			remove(selectedShape, board);
			selectedShape = nullptr;
		}
		else if (command == "paint" && parsedInput.size() == 2)
		{
			if (selectedShape == nullptr)
			{
				std::cout << "Shape not selected" << std::endl;
				continue;
			}
			selectedShape->Paint(parsedInput[1]);
		}
		else if (command == "edit" && parsedInput.size() > 3)
		{
			change(selectedShape, convertParameters(std::vector<std::string>(parsedInput.begin() + 1, parsedInput.end())), board);
		}
		else
			std::cout << "Invalid command" << std::endl;
		
	} while (input != "quit");
	return 0;
}