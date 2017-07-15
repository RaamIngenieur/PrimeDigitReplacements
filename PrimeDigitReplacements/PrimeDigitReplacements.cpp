// PrimeDigitReplacements.cpp : Defines the entry point for the console application.
//

/*
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
*/

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void printPrimeFamily(int N);
bool detectPrimeValueFamily(int N, int prime[], int length);
bool checkForFamily(int diff[], int members[], int length,int N);

int main()
{
	int N = 8;

	printPrimeFamily(N);

    return 0;
}

void printPrimeFamily(int N)
{
	int prime[100000], numPrime, digits, digitCheck, digitLowIndex,digitHighIndex;
	bool isPrime,familyFound;

	prime[0] = 2;
	numPrime = 1;
	digitLowIndex = 0;
	digitHighIndex = 0;
	digitCheck = 10;

	for (int t = 3; t < 1000000; t++)
	{
		for (int j = 0; j < numPrime; j++)
		{
			isPrime = true;

			if (t%prime[j] == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime)
		{
			prime[numPrime] = t;
			numPrime++;

			if (t / digitCheck > 0)
			{
				digitHighIndex = numPrime - 2;
				digitCheck *= 10;

				familyFound = detectPrimeValueFamily(N, &prime[digitLowIndex], digitHighIndex - digitLowIndex);

				if (familyFound)
					break;

				digitLowIndex = numPrime - 1;
			}
		}
	}
}

bool detectPrimeValueFamily(int N, int prime[], int length)
{
	int numMem,*diff,*members;

	diff = new int[length - 1];
	members = new int[N];

	for (int i = 0; i < length -N; i++)
	{
		numMem = 1;
		members[0] = i;
		for (int j = i +1; j < length; j++)
		{
			diff[j-i-1] = prime[j] - prime[i];
		}
		
		if (checkForFamily(diff, members, length - i -1, N))
		{
			cout << "The smallest member of the family is " << prime[members[0]]<<endl;
			cout << "The members are: " << endl;
			for (int k = 0; k < N; k++)
			{
				cout << prime[members[k]]<< endl;
			}
			cin.get();
			return true;

		}
	}
	return false;
}

bool checkForFamily(int diff[], int members[], int length,int N)
{
	char digit[10] = { '0','1', '2', '3', '4', '5', '6', '7', '8', '9' };
	string diffString;
	bool patternfound;
	int numOfUniqDgts,num, ptrnNum,numMem;
	
	for (int i = 0; i < length - N; i++)
	{
		diffString = to_string(diff[i]);
		//Check for trend
		//Check if 0 is present
		if (count(diffString.begin(), diffString.end(), '0') > 0)
		{
			numOfUniqDgts = 0;
			//Verify that only one more character is there
			for (int j = 1; j < 10; j++)
			{
				if (count(diffString.begin(), diffString.end(), digit[j]) > 0)
				{
					numOfUniqDgts++;
					num = j;
				}
			}

			//if found normalize
			if (numOfUniqDgts == 1)
			{
				//divide the number by the other character
				ptrnNum = diff[i] / num;
				members[0] = i;
				numMem = 1;

				//Check if other differences match the trend
				for (int k = i + 1; k < length; k++)
				{
					//Divide each of remaining difference by normalized value and check for remainder
					if ((diff[k] % ptrnNum == 0) &&(diff[k]/ ptrnNum < 10))
					{
						members[numMem] = k;
						numMem++;
					}
				}

				if (numMem == N)
				{
					cout << "The pattern of the family is " << ptrnNum << endl;
					return true;
				}
			}
		}
	}

	return false;
}
