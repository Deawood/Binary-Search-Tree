#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <utility>
#include <cstring>
#include <algorithm>


using namespace std;

typedef long long ull;


class BST {

private:
	pair<string, ull> FandW;
	vector<pair<string, ull> > wAndf;
	vector<vector<ull> > tableRtCt;
	vector<ull> Sum;
	vector<ull> addLoc;
	char word[40];
	ull wFreq;
	ull tRoot;
public:
	
	bool pairCompare(const pair<string, int>& firstElem, 
		const pair<string, int>& secondElem) 
	{
		 return firstElem.first < secondElem.first;	
	}

	BST()
	{ 
		Sum.push_back(0);
		for(ull count = 0; scanf("%40s", word) != EOF; ++count) 
		{
			
			scanf("%llu", &wFreq);
			FandW.first = word;
			FandW.second = wFreq;
			wAndf.push_back(FandW);
			Sum.push_back(wFreq+Sum[count]);
			// Add to the row length
			addLoc.push_back(0);
			sort(wAndf.begin(), wAndf.end());
		}
		// cout << wAndf[7].first << '\n'; //" " << FandW.second << " " << Sum[count+1] << "\n";			
		sort(wAndf.begin(), wAndf.end());
		// Create vertical part of table 
		ull CT;
		while (CT <= wAndf.size())
		{
			tableRtCt.push_back(addLoc);
			++CT;
		}

		tRoot = CalulateTable();
		// tablePrint();
		cout << wAndf[tRoot].first << " " << tableRtCt[0][wAndf.size()-1] << "\n";

	}
	ull CalulateTable()
	{
		ull root;
		ull curConst;
		ull const maxSize = wAndf.size();
		for (ull x = maxSize-1; x >= 0 ;  --x)
		{	
			for (ull y = x; y < maxSize; ++y)
			{
				// Calculation for main diagonal
				if (x == y)
				{
					tableRtCt[x][y] = wAndf[x].second;
					//cout << "This is the diagonal: " << tableRtCt[x][y] << "\n";
				}
				else
				{
					// Calculate Constant
					curConst = Sum[y+1] - Sum[x];
					ull rootOff = 0;
					ull offX = 1;	
					ull offY = 1;
					root = y;
					long long int min = -1;

					// Calculate Minimum
					while (y+offX != x)
					{

						ull leftV = 0;
						ull downV = 0;
						if (y+offX < maxSize) 
						{ 
							downV = tableRtCt[y+offX][y];
						}
						if (y-offY >= 0)
						{
							leftV = tableRtCt[x][y-offY];
						}
						--offX;
						++offY;

						if (min == -1)
						{
							min = downV + leftV;
						}
						// min = (min > downV + leftV) ? downV + leftV : min;
						if (min > (downV + leftV))
						{
							min = downV + leftV;
							root = y-rootOff;
						} 
						else
						{
							min = min;
						}
						++rootOff;

					}

					tableRtCt[x][y] = curConst + min;
				}

			}
		}
		
		return root;
	}

	void tablePrint() 
	{
		for (int k = 0; k < tableRtCt.size()-1; k++) {
	 			for (int j = 0; j < tableRtCt.size()-1; j++) {
					cout << tableRtCt[k][j] << "\t";
				}
				cout << "\n";
			}
			cout << "\n";
	}



};



int main()
{
	BST myBST = BST();
	return 0;
}