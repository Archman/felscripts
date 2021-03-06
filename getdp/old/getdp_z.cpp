/*********************************************************************\
 * Program: getdp_z                                                  *
 * Purpose: extract z-order data info from the GENESIS output result *  
 * Copyright (C) 2012 Tong Zhang                                     *
 *                                                                   *
 * This program is free software: you can distribute it and/or modify*
 * it under the terms of GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License or  *
 * (at your option) any later version.                               *
 *                                                                   *
 * This program is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      *
 * GNU General Public License for more details.                      *
 *                                                                   *
 * You should have received a copy of the GNU General Public License *
 * along with this program. If not see <http://www.gnu.org/licenses/>.*
\*********************************************************************/

/******************************************************************************\
This program is written for parsing output file (TDP)
***get all slice value at given z-record
Usage: getdp file1 file2 z_order
	file1: output file (TDP)
	file2: write into the extrated data
	z_order: z-record order
Author: Tong ZHANG
e-mail: tzhang@sinap.ac.cn
Created Time: 14:58, Dec. 9th, 2011
\*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 30;
const char* DELIMITER = " \t";

using namespace std;

int main(int argc, char **argv)
{

	if(argc != 4) // if the number of parameters is not enough, then give errors, exit
	{
		if(argc >=2)cout << "Not enough parameters!\n\n";
		cout << "Usage: " << argv[0] << " file1 file2 z-order\n";
		cout << "\t" << "file1: " << "\t\t" << "TDP output filename, open to read\n";
		cout << "\t" << "file2: " << "\t\t" << "data filename, open to write\n";
		cout << "\t" << "z-order:"<< "\t"   << "z-axis order number\n\n";
		exit(1);
	}

	ifstream file1(argv[1]); 		// tdp filename to read
	ofstream file2(argv[2]); 		// filename for writting data
	int z_order = atoi(argv[3]); 	// z-record order

	if (!file1 || !file2) 			// if any one of files cannot open, return error, exit
	{
		cout << "Open file error!\n\n";
		exit(1);
	}
	

	int count = 0; // read line by line, increase count value when encounter line starts with "*", means find one slice record
	while(!file1.eof()) // do not stop reading untile the end of file1 
	{
		// locate the beginning of every slice [s-order]
		while(1)
		{
			char buf[MAX_CHARS_PER_LINE];
			file1.getline(buf, MAX_CHARS_PER_LINE);
			char* token[MAX_TOKENS_PER_LINE] = {0};
			token[0] = strtok(buf, DELIMITER);
			if(token[0] && token[0][0]=='*')
			{
				count++;
				break;
			}
		}

		//pass next 5 useless lines
		string line;
		for(int i =1;i<=5;i++)
		{
			getline(file1, line);
			//file2 << line << "\n";
		}
		
		//extract the [slice_order]th z-record, given that line_count = z_order
		int line_count = 0;
		getline(file1, line);
		while(!line.empty())
		{
			line_count++;
			if(line_count==z_order)file2 << line << "\n";
			getline(file1, line);
		}
	}

	//close opened files
	file1.close();
	file2.close();

	return 0;
}
