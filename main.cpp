#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	ifstream dataSet ("");
	if (dataSet.is_open())
		{
			JobShop jobShop = readFirstLine(getLine(dataSet));
			id=1;
			while(getLine(dataSet, line)) {
				new Job(line[1], id);
				generateJob(line, id);
				i++;			
			}
		}
}

*JobShop readFirstLine() {
	
}

void generateJob(string line) {
	
	for(int i=0; i<; i++) 
	{
		
	}
}
