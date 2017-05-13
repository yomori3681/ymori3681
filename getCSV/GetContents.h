#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要
// 名前空間
using namespace std;

class GetContents
{
public:
	GetContents();
	~GetContents();

	bool GetCSVFile(const string& filename, vector<vector<string>>& table, const char delimiter = ',');
	bool GetCSVString(const string & csvdata, vector<string> & table);
	bool GetCSVString2(const string & csvdata, vector<vector<string>>& table, const char delimiter = ',');

	int  GetCSVFileSize(const string& filename, fpos_t *ft);
	int	 ReadFileToString(const string& filename, string& strData);

	// 2分探索
	int  BsearchCSV(string key, vector<vector<string>>& table, vector<string> &resultStr);
};

