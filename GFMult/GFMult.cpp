/********************************************************************************************
*										GFMult.cpp 											*
*																							*
*	DESCRIPTION: Computes multiplation tables in Galois Field 2^8. 							*
*																							*
*																							*
*	AUTHOR: Aaron Millikin											START DATE: 2/18/2017	*
*********************************************************************************************/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Determines most significant bit in a binary number. -ARM
int getMSB(unsigned int numToCheck) {
	int msb = 0;
	while (numToCheck >>= 1) {
		msb++;
	}
	return msb;
}

unsigned int GFMult(unsigned int a, unsigned int b, unsigned int c) {
	unsigned int result;
	unsigned int terms[8] = { 0 };
	int msb, termCnt = 0;

	//Determins most significant bit of a term, only loops until that bit is reached
	msb = getMSB(a);
	result = b;

	if (a & 0x1) {
		terms[termCnt] = result;
		termCnt++;
	}
	
	for (int i = 1; i <= msb; i++) {
		//Check if MSB of pervious result < 7
		//If so, just shift left 1 bit (multiply by x)
		//Else, shift left 1 bit and XOR with modulus
		if (getMSB(result) < 7) {
			result <<= 1;
		}
		else {
			result <<= 1;
			result ^= c;
		}
		//Checks if term is needed to compute final result
		if ((a >> i) & 0x1) {
			terms[termCnt] = result;
			termCnt++;
		}
	}

	//If multiple terms needed, XORs each together
	for (int i = 1; i < termCnt; i++) {
		terms[0] ^= terms[i];
	}

	//Final result will be the value in terms[0]
	return result = terms[0];
}

int main()
{
	int cnt = 0;

	for (int i = 0; i < 16; i++) {
		cout << "Table " << i << endl;
		for (int j = 0; j < 256; j++) {
			cnt++;
			if (cnt == 32) {
				cout << "0x" << setfill('0') << setw(2) << hex << GFMult(i, j, 0x11b) << endl;
				cnt = 0;
			}
			else {
				cout << "0x" << setfill('0') << setw(2) << hex << GFMult(i, j, 0x11b) << ", ";
			}
		}
		cout << endl;
	}

	
    return 0;
}

