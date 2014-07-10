#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<unsigned long> openInputFile(std::string iFilename)
{
	std::string line;
	ifstream myfile (iFilename);
	vector<unsigned long> inputNumbers;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			inputNumbers.push_back(atol(line.c_str()));
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 

	return inputNumbers;
}

unsigned long MergeAndCountSplitInv(vector<unsigned long>& leftHalf, vector<unsigned long>& rightHalf, vector<unsigned long>& inputArray,unsigned long sizeOfArray )
{
	unsigned long lCount = 0 , rCount = 0 ;
	unsigned long splitCount = 0; 
	for (unsigned long k= 0 ; k < sizeOfArray ; k ++)
	{
		if(lCount < leftHalf.size() && rCount < rightHalf.size() )
		{
			if( leftHalf[lCount] < rightHalf[rCount])
			{
				inputArray[k] = leftHalf[lCount];
				lCount++;
			}
			else 
			{
				inputArray[k] = rightHalf[rCount];
				rCount++;
				splitCount += (leftHalf.size() - (lCount)); 				
			}
		}
		else
		{
			if (lCount < leftHalf.size())
			{
				inputArray[k] = leftHalf[lCount];
				lCount++;
			}
			if (rCount < rightHalf.size() )
			{
				inputArray[k] = rightHalf[rCount];
				rCount++;
			}
		}
	}
	return splitCount;
}
unsigned long SortAndCount( vector<unsigned long>& inputArray, unsigned long sizeOfArray)
{
	if (sizeOfArray == 1)
		return 0;
	else
	{
		std::vector<unsigned long> leftHalf(inputArray.begin(), inputArray.begin() + inputArray.size()/2);
		std::vector<unsigned long> rightHalf(inputArray.begin() + inputArray.size()/2, inputArray.end());
		unsigned long x = SortAndCount(leftHalf , leftHalf.size());
		unsigned long y = SortAndCount(rightHalf , rightHalf.size());
		unsigned long z = MergeAndCountSplitInv(leftHalf, rightHalf , inputArray, sizeOfArray);
		return x + y + z ;
	}
}


int main()
{
	vector<unsigned long> inputArray = openInputFile("C:\\TrainingCode\\AlgoProgrammingAssignment01\\IntegerArray.txt");
	//for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
		//cout << *it << endl;
	cout << " Sorting & Merging Begin " << endl;
	unsigned long answer = SortAndCount(inputArray , inputArray.size());
	cout << "Number of Inversions = " << answer <<endl; 

	int x;
	cin>>x;
}