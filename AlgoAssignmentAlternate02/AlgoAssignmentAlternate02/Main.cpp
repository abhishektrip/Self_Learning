#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int questionNumber; 
unsigned long numberOfComparisons = 0; 
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
void swapElements(vector<unsigned long>& inputArray,unsigned long i , unsigned long j)
{
	//swap elements
	if (i != j)
	{
		unsigned long temp = inputArray[j];
		inputArray[j] = inputArray[i];
		inputArray[i] = temp;
	}
}
unsigned long choosePivotQuestion1(vector<unsigned long>& inputArray, unsigned long start, unsigned long end)
{
	return start;
}
unsigned long choosePivotQuestion2(vector<unsigned long>& inputArray, unsigned long start, unsigned long end)
{
	return end; 
}
unsigned long choosePivotQuestion3(vector<unsigned long>& inputArray, unsigned long start, unsigned long end)
{
	unsigned long first, middle, last ,median; 
	median = 0; 
	unsigned long arraySize = end- start+1; 
	if (arraySize < 3)
		median = start; 
	else
	{
	first = inputArray[start] ; last = inputArray[end];  middle = inputArray[start+ (arraySize-1)/2];
	if(first > middle ) 
	{
		if(middle > last )
		{
			median = start + (arraySize-1)/2;
		}
		else if(first> last)
		{
			median = end;
		}
		else
		{
			median = start;
		}
	}
	else
	{
		if(first > last)
		{
			median = start;
		}
		else if(middle > last)
		{
			median = end;
		}
		else
		{
			median = start + (arraySize-1)/2;
		}
	}

	}

	//if( (first < middle && middle < last) || (last < middle && middle < first)) //f< m< l  OR l< m <f
	//	median = (arraySize-1)/2;
	//else if ((middle <first && first < last) || (last < first && first < middle)) //m<f<l OR  l< f < m
	//	median = start;
	//else if ((first<last && last <middle) || (middle <last && last < first))// f<l<m OR m<l<f
	//	median = end; 

	return median; 

}
unsigned long partitionArrayAroundPivot(vector<unsigned long>& inputArray,unsigned long start , unsigned long end)
{
	unsigned long pivot = inputArray[start];
	unsigned long i = start + 1;
	for (unsigned long j = start; j <end+1 ; j++)
	{
		if(inputArray[j] < pivot )
		{
			swapElements(inputArray, i, j);

			i++;
		}
	}
	//swap elements
	swapElements(inputArray, start, i-1);
	//cout << "Partitioned Array" <<endl;
	//			for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
	//		cout << *it << "  ";
	//cout<<endl;
	return i-1; 

}
unsigned long choosePivot(vector<unsigned long>& inputArray, unsigned long start, unsigned long end)
{
	switch(questionNumber)
	{
	case 1 :
		return choosePivotQuestion1(inputArray, start, end);
	case 2:
		return choosePivotQuestion2(inputArray, start, end);
	case 3 :
		return choosePivotQuestion3(inputArray, start, end);
	}

}
void myQuickSort( vector<unsigned long>& inputArray , unsigned long start, unsigned long end)
{
	unsigned long arraySize = end - start + 1; 

	if ( arraySize == 1 || arraySize == 0 )
		return ; 
	else
	{
		numberOfComparisons+= arraySize -1;
		unsigned long pivot = choosePivot(inputArray, start,end);
		swapElements(inputArray, start, pivot);
		unsigned long i = partitionArrayAroundPivot(inputArray, start, end);

		myQuickSort(inputArray, start, i-1 );

		myQuickSort(inputArray, i+1, end);
		/*cout << "Sorted Array" <<endl;
		for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
			cout << *it << "  ";
		cout<< endl;*/
	}
}

int main()
{
	vector<unsigned long> inputArray = openInputFile("C:\\TrainingCode\\AlgoAssignmentAlternate02\\QuickSort.txt");
	vector<unsigned long> copyArray = inputArray;
	//for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
	//cout << *it << endl;
	for (int i = 0 ; i < 3; i ++ )
	{
		questionNumber = i +1; 
		numberOfComparisons = 0 ;
		cout << " QuickSort - Question # " <<questionNumber<< endl;

		myQuickSort(inputArray , 0, inputArray.size()-1);

		cout << "Number of Comparisons= " << numberOfComparisons <<endl; 
		//for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
		//	cout << *it << "  ";
		//cout<< endl;
		inputArray = copyArray;
	}
	int x;
	cin>>x;
}
