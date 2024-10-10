#include <iostream>
#include <fstream>
#include <format>

#include "Line.h"
#include "Board.h"
#include "Shape.h"
#include "Parser.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Parallelogram.h"

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

static void add(std::string shapeType, std::vector<int> shapeParameters, std::unique_ptr<Board>& board)
{
	int shapeParametersSize = shapeParameters.size();
	std::shared_ptr<Shape> shape;

	for (int parameter : shapeParameters)
		if (parameter > board->GetHeight() && parameter > board->GetWidth())
		{
			std::cout << "Shape bigger than board or completely outside" << std::endl;
			return;
		}
	
	if (shapeType == "circle" && shapeParametersSize == 3)
	{
		shape = std::make_shared<Circle>(shapeParameters[0], shapeParameters[1], shapeParameters[2]);
	}
	else if (shapeType == "square" && shapeParametersSize == 3)
	{
		shape = std::make_shared<Square>(shapeParameters[0], shapeParameters[1], shapeParameters[2]);
	}
	else if (shapeType == "line" && shapeParametersSize == 4)
	{
		shape = std::make_shared<Line>(shapeParameters[0], shapeParameters[1], shapeParameters[2], shapeParameters[3]);
	}
	else  if (shapeType == "triangle" && shapeParametersSize == 4)
	{
		shape = std::make_shared<Triangle>(shapeParameters[0], shapeParameters[1], shapeParameters[2], shapeParameters[3]);
	}
	else if (shapeType == "rectangle" && shapeParametersSize == 4)
	{
		shape = std::make_shared<Rectangle>(shapeParameters[0], shapeParameters[1], shapeParameters[2], shapeParameters[3]);
	}
	else if (shapeType == "parallelogram" && shapeParametersSize == 5)
	{
		shape = std::make_shared<Parallelogram>(shapeParameters[0], shapeParameters[1], shapeParameters[2], shapeParameters[3], shapeParameters[4]);
	}
	else
	{
		std::cout << "Invalid shape" << std::endl;
		return;
	}

	for (std::shared_ptr<Shape> s : board->GetShapes())
		if (s->GetId() == shape->GetId())
		{
			std::cout << "Shape already exists" << std::endl;
			return;
		}

	board->AddShape(shape);
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
		add(shapeParameters[0], convertParameters(std::vector<std::string>(shapeParameters.begin() + 1, shapeParameters.end())), board);
	}
	return board;
}

int main()
{
	std::string input;
	std::unique_ptr<Board> board;
	std::unique_ptr<Parser> parser = std::make_unique<Parser>();

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
				std::cout << std::format("ID: {}\n\t{}", shape->GetId(), shape->GetParameters()) << std::endl;
		}
		else if (command == "undo")
		{
			board->Undo();
		}
		else if (command == "clear")
		{
			board->Clear();
		}
		else if (command == "save" && parsedInput.size() == 2)
		{
			save(parsedInput[1], board->Dump());
		}
		else if (command == "add" && parsedInput.size() > 3)
		{
			std::vector<std::string> shapeParameters(parsedInput.begin() + 1, parsedInput.end());
			add(shapeParameters[0], convertParameters(std::vector<std::string>(shapeParameters.begin() + 1, shapeParameters.end())), board);
		}
		else
			std::cout << "Invalid command" << std::endl;
		
	} while (input != "quit");
	return 0;
}