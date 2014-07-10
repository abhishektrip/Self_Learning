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
	unsigned long temp = inputArray.at(j);
	inputArray.at(j) = inputArray.at(i);
	inputArray.at(i) = temp;
}
unsigned long choosePivotQuestion1(vector<unsigned long>& inputArray, unsigned long arraySize)
{
	return 0;
}
unsigned long choosePivotQuestion2(vector<unsigned long>& inputArray, unsigned long arraySize)
{
	return arraySize -1; 
}
unsigned long choosePivotQuestion3(vector<unsigned long>& inputArray, unsigned long arraySize)
{
	unsigned long first, middle, last ,median; 
	median = 0; 
	first = 0 ; last = arraySize - 1;  middle = (arraySize-1)/2;
	if( (first < middle && middle < last) || (last < middle && middle < first)) //f< m< l  OR l< m <f
		median = middle;
	else if ((middle <first && first < last) || (last < first && first < middle)) //m<f<l OR  l< f < m
		median = first;
	else if ((first<last && last <middle)||(middle <last && last < first))// f<l<m OR m<l<f
		median = last; 

	return median; 

}
unsigned long partitionArrayAroundPivot(vector<unsigned long>& inputArray,unsigned long arraySize)
{
	unsigned long pivot = inputArray[0];
	unsigned long i = 1;
	for (unsigned long j = 1; j < arraySize ; j++)
	{
		if(inputArray[j] < pivot )
		{
			swapElements(inputArray, i, j);

			i++;
		}
	}
	//swap elements
	swapElements(inputArray, 0, i-1);
	cout << "Partitioned Array" <<endl;
				for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
			cout << *it << "  ";
	cout<<endl;
	return i-1; 

}
unsigned long choosePivot(vector<unsigned long>& inputArray, unsigned long arraySize)
{
	switch(questionNumber)
	{
	case 1 :
		return choosePivotQuestion1(inputArray, arraySize);
	case 2:
		return choosePivotQuestion2(inputArray, arraySize);
	case 3 :
		return choosePivotQuestion3(inputArray, arraySize);
	}

}
void myQuickSort( vector<unsigned long>& inputArray , unsigned long arraySize)
{
	
	
	if ( arraySize == 1 || arraySize == 0 )
		return ; 
	else
	{
		numberOfComparisons+= arraySize -1;
		unsigned long pivot = choosePivot(inputArray, arraySize);
		swapElements(inputArray,0,pivot);
		unsigned long i = partitionArrayAroundPivot(inputArray,arraySize);
		vector<unsigned long> leftHalf(inputArray.begin(),inputArray.begin() + i);
		vector<unsigned long> rightHalf(inputArray.begin()+ i+1 ,inputArray.end());
		cout << "Left Half "<< endl;
		for(vector<unsigned long>::iterator it1 = leftHalf.begin(); it1 != leftHalf.end(); it1++)
			cout << *it1 << "  ";
		cout<< endl;
	/*	cout << "Right Half "<< endl;
				for(vector<unsigned long>::iterator it2 = rightHalf.begin(); it2 != rightHalf.end(); it2++)
			cout << *it2 << "  ";
		cout<< endl;*/
		myQuickSort(vector<unsigned long>(inputArray.begin(),inputArray.begin() + i) , leftHalf.size());
				cout << "Sorted Array" <<endl;
				for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
			cout << *it << "  ";
		cout<< endl;
		myQuickSort(vector<unsigned long> (inputArray.begin()+ i +1,inputArray.end()), rightHalf.size());
		cout << "Sorted Array" <<endl;
				for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
			cout << *it << "  ";
		cout<< endl;
	}
}

int main()
{
	vector<unsigned long> inputArray = openInputFile("C:\\TrainingCode\\AlgoAssignment02\\10.txt");
	vector<unsigned long> copyArray = inputArray;
	//for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
	//cout << *it << endl;
	for (int i = 0 ; i < 3; i ++ )
	{
		questionNumber = i +1; 
		numberOfComparisons = 0 ;
		cout << " QuickSort - Question # " <<questionNumber<< endl;

		myQuickSort(inputArray , inputArray.size());

		cout << "Number of Comparisons= " << numberOfComparisons <<endl; 
		for(vector<unsigned long>::iterator it = inputArray.begin(); it != inputArray.end(); it++)
			cout << *it << "  ";
		cout<< endl;
		inputArray = copyArray;
	}
	int x;
	cin>>x;
}
