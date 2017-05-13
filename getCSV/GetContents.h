#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ��istringstream���g�����߂ɕK�v
// ���O���
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

	// 2���T��
	int  BsearchCSV(string key, vector<vector<string>>& table, vector<string> &resultStr);
};

