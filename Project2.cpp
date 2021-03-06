// Made December 9th 2018 by Noah Fulton
//the goal of this program is to make a functional binary tree that can use hashes to see its histories



#include "pch.h"
#include "Tree.h"
#include <iostream>

//print every Node's data besides histories
void printData(Tree &binary)
{
	std::vector <std::string> temp;
	binary.getData(temp);
	for (size_t i = 0; i < temp.size(); i++)
	{
		std::cout << temp[i] << std::endl;
	}

}

//print every node's history hashes
void printHistories(Tree &binary)
{
	std::vector <std::string> temp;
	binary.getHistories(temp);
	for (size_t i = 0; i < temp.size(); i += 3)
	{
		std::cout << temp[i] << std::endl;
		std::cout << temp[i + 1] << std::endl;
		std::cout << temp[i + 2] << std::endl << std::endl << std::endl;
	}
}


int main()
{
	std::cout << "This is a level iterating binary tree." << std::endl;
	std::cout << "Type the letter N for a new node. Type letter C to change a node. Type D to print all data or Type O to print data on one node. Type H to see all history hashes." << std::endl;
	std::cout << "Type anything else to close this program" << std::endl;
	Tree binary;
	std::string inputData;
	bool loopAgain;
	do
	{
		loopAgain = false;
		std::cin >> inputData;
		//check which input is used.
		if (inputData == "N")
		{
			std::cout << "What is the Node's data?" << std::endl;
			std::cin >> inputData;
			binary.addNode(inputData);

			loopAgain = true;
		}
		else if (inputData == "C")
		{
			std::cout << "What is the ID of the node?" << std::endl;
			std::string secondInput;
			std::cin >> inputData;
			std::cout << "What do you want its new raw event to be?" << std::endl;
			std::cin >> secondInput;
			binary.changeNode(inputData, secondInput);
			loopAgain = true;
		}
		else if (inputData == "D")
		{
			printData(binary);
			loopAgain = true;
		}
		else if (inputData == "H")
		{
			printHistories(binary);
			loopAgain = true;
		}
		else if (inputData == "O")
		{
			std::cout << "Which node are you looking for?" << std::endl;
			std::cin >> inputData;
			binary.getData(inputData);
			loopAgain = true;
		}
	} while (loopAgain);
	


}

