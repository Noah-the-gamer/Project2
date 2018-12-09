#pragma once
#include <string>
#include <list>
#include <vector>




class Node
{
public:
	int left = NULL;
	int right = NULL;
	//node initialization
	Node(std::string ParId, std::string Event, int index, bool child)
	{
		Id = Hash(ParId + RawEvent);
		RawEvent = Event;
		ParIndex = index;
		leftChild = child;
		left = NULL;
		right = NULL;
	}

	//return the node's ID
	std::string getId()
	{
		return Id;
	}
	
	//Get data to hash
	std::string getDataNoHist()
	{
		return RawEvent + Id + ParentId + LHash + RHash;
	}

	//set RHash
	void setLHash(std::string Data)
	{
		LHash = Hash(Data);
		LHist.push_front(LHash);
	}

	std::string getLHash()
	{
		return LHash;
	}

	//set LHash
	void setRHash(std::string Data)
	{
		RHash = Hash(Data);
		RHist.push_front(RHash);
	}

	//return the current RHash
	std::string getRHash()
	{
		return RHash;
	}

	//return the parent index
	int getParIndex()
	{
		return ParIndex;
	}

	//return if the node is a left child
	bool getLeftChild()
	{
		return leftChild;
	}

	//return all non hist data on the node
	std::string getAllData()
	{
		std::string hold = Id + " " + RawEvent + " " + ParentId + " " + LHash + " " + RHash;
		return hold;
	}

	//return the history of the node
	std::string getAllLHist()
	{
		std::string hold;
		std::list <std::string> :: iterator it;
		for (it = LHist.begin(); it != LHist.end(); ++it)
		{
			hold = hold + *it + " ";
		}
		return hold;
	}

	//return the history of the node
	std::string getAllRHist()
	{
		std::string hold;
		std::list <std::string> ::iterator it;
		for (it = RHist.begin(); it != RHist.end(); ++it)
		{
			hold = hold + *it + " ";
		}
		return hold;
	}

	//change the Node's Raw data
	void changeRaw(std::string newRaw)
	{
		RawEvent = newRaw;
	}

	//custom hash
	std::string Hash(std::string toHash)
	{
		int sum = 11111111;
		for (size_t i = 0; i < toHash.length(); i++)
		{
			sum += (int(toHash[i]) * 10 ^ (i % 8));
		}
		std::string returnVal = std::to_string(sum);
		return returnVal.substr(8);
	}

private:

	std::string RawEvent;
	std::string Id;
	std::string ParentId;
	int ParIndex;
	std::string LHash;
	std::string RHash;
	bool leftChild;
	std::list<std::string> LHist;
	std::list<std::string> RHist;

};



//tree uses subclass Node
class Tree
{
public:
	std::vector<Node> AllNodes;
	int currentIndex = 0;

	std::string changeNode(std::string checkId,std::string Raw)
	{
		size_t i = 0;
		while (AllNodes[i].getId() != checkId && i >= AllNodes.size())
		{
			i++;
		}
		if (i >= AllNodes.size())
		{
			return "The Id does not exist";
		}
		else
		{
			AllNodes[i].changeRaw(Raw);
			HashUp(i);
			return "Success";
		}
	}


	//store all node's data in an accessable vector
	void getData(std::vector <std::string> &DataArray)
	{
		int workIndex = 0;
		do
		{
			DataArray.push_back(AllNodes[workIndex].getAllData());
		} while (workIndex != AllNodes.size());
	}

	//print the data of a node in a string
	std::string getData(std::string anId)
	{
		int anIndex = 0;
		while (AllNodes[anIndex].getId() != anId && anIndex != AllNodes.size())
		{
			anIndex++;
		}
		if (anIndex != AllNodes.size())
		{
			return AllNodes[anIndex].getAllData();
		}
		else
		{
			return "Could not find the indicated ID";
		}
	}
	//system of adding a node to the vector
	void addNode(std::string RawData)
	{
		//add a node to 
		if (AllNodes.size() == 0)
		{
			Node tempNode("rootnode", RawData, currentIndex, false);
			AllNodes.push_back(tempNode);
		}
		else if (AllNodes[currentIndex].getLHash().empty())
		{
			Node tempNode(AllNodes[currentIndex].getId(), RawData, currentIndex, true);
			AllNodes[currentIndex].setLHash(tempNode.getDataNoHist());
			AllNodes.push_back(tempNode);
			HashUp();
		}
		else if (AllNodes[currentIndex].getRHash().empty())
		{
			Node tempNode(AllNodes[currentIndex].getId(), RawData, currentIndex, false);
			AllNodes[currentIndex].setRHash(tempNode.getDataNoHist());
			AllNodes.push_back(tempNode);
			HashUp();
		}
		else
		{
			currentIndex++;
			addNode(RawData);
		}

	}

	//return all histories of all nodes for printing
	void getHistories(std::vector<std::string> &superList)
	{
		for (size_t i = 0; i < AllNodes.size(); i++)
		{
			superList.push_back("Index: " + i);
			superList.push_back("Lhist: " + AllNodes[i].getAllLHist());
			superList.push_back("Rhist: " + AllNodes[i].getAllRHist());
		}
	}

private:
	//update tree 
	void HashUp()
	{
		int workIndex = currentIndex;
		do
		{
			if (AllNodes[workIndex].getLeftChild())
			{
				AllNodes[AllNodes[workIndex].getParIndex()].setLHash(AllNodes[workIndex].getDataNoHist());
				workIndex = AllNodes[workIndex].getParIndex();
			}
			else
			{
				AllNodes[AllNodes[workIndex].getParIndex()].setRHash(AllNodes[workIndex].getDataNoHist());
				workIndex = AllNodes[workIndex].getParIndex();
			}
		} while (workIndex != 0);
	}
	//update tree by index
	void HashUp(int index)
	{
		int workIndex = index;
		do
		{
			if (AllNodes[workIndex].getLeftChild())
			{
				AllNodes[AllNodes[workIndex].getParIndex()].setLHash(AllNodes[workIndex].getDataNoHist());
				workIndex = AllNodes[workIndex].getParIndex();
			}
			else
			{
				AllNodes[AllNodes[workIndex].getParIndex()].setRHash(AllNodes[workIndex].getDataNoHist());
				workIndex = AllNodes[workIndex].getParIndex();
			}
		} while (workIndex != 0);
	}


};