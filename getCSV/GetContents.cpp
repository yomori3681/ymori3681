#include "stdafx.h"
#include "GetContents.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要
// 名前空間
using namespace std;

GetContents::GetContents()
{
}


GetContents::~GetContents()
{
}

bool GetContents::GetCSVFile(const string& filename, vector<vector<string>>& table, const char delimiter)
{
	bool bRet = true;

	// ファイルを開く
	fstream filestream(filename);
	if (!filestream.is_open())
	{
		// ファイルが開けなかった場合は終了する
		bRet = false;
		return bRet;
	}

	// ファイルを読み込む
	while (!filestream.eof())
	{
		// １行読み込む
		string buffer;
		filestream >> buffer;

		// ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
		vector<string> record;              // １行分の文字列のリスト
		istringstream streambuffer(buffer); // 文字列ストリーム
		string token;                       // １セル分の文字列
		while (getline(streambuffer, token, delimiter))
		{
			// １セル分の文字列をリストに追加する
			record.push_back(token);
		}

		// １行分の文字列を出力引数のリストに追加する
		table.push_back(record);
	}

	return bRet;
}

bool GetContents::GetCSVString(const string & csvdata, vector<string>& table)
{
	const char delimiter = '\n';
	string token;						 // １行分の文字列
	istringstream streambuffer(csvdata); // 文字列ストリーム

	while (getline(streambuffer, token, delimiter))
	{
		// １行分の文字列をリストに追加する
		table.push_back(token);
	}

	return true;
}

bool GetContents::GetCSVString2(const string & csvdata, vector<vector<string>>& table, const char delimiter)
{
	bool bRet = true;

	const char newLine = '\n';
	string oneLine;								 // １行分の文字列
	istringstream streamOneLineBuffer(csvdata);	// 文字列ストリーム

	// ファイルを読み込む
	while (getline(streamOneLineBuffer, oneLine, newLine))
	{
		// １行の文字列を区切り文字で分けてリストに追加する
		vector<string> record;						// １行分の文字列のリスト
		istringstream streambuffer(oneLine);		// 文字列ストリーム
		string token;								// １セル分の文字列
		while (getline(streambuffer, token, delimiter))
		{
			// １セル分の文字列をリストに追加する
			record.push_back(token);
		}

		// １行分の文字列を出力引数のリストに追加する
		table.push_back(record);
	}

	return bRet;
}

int GetContents::GetCSVFileSize(const string & filename, fpos_t* ft)
{
	FILE *fp;

	fp = fopen(filename.c_str(), "rb");
	if (fp == NULL) {
		return -1;
	}
	// ファイルポインタを末尾まで移動
	fseek(fp, 0, SEEK_END);
	// ファイルポインタの位置を取得
	fgetpos(fp, ft);

	fclose(fp);
	return 0;
}

int GetContents::ReadFileToString(const string & filename, string & strData)
{
	std::ifstream ifs(filename);
	if (ifs.fail())
	{
		return -1;
	}

	// string型にfilenameで指定したファイルを全部読込む
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);
	// 読み込んだデータをパラメータに設定
	strData = str;

	return 0;
}

int GetContents::BsearchCSV(string  key, vector<vector<string>>& table , vector<string> &resultStr)
{
	int iRet = 0;
	int left = 0;					/* start key of index */
	int right = table.size() -1;	/* end   key of index ( SIZE -1 !!!) */
	int mid = 0;					/* middle key of index */

	while (left <= right) {
		mid = (left + right) / 2  ; /* calc of middle key */
#if 0
		char buff[256];
		sprintf(buff, "left:3%d mid:%3d right:%3d  %s\ %s", left,mid, right, table[mid][0].c_str(),key.c_str());
		puts(buff);
#endif
		if (table[mid][0] == key) {
			resultStr = table[mid];
			iRet = 1;
			return iRet;
		}
		else if (table[mid][0] < key) {
			left = mid + 1; /* adjustment of left(start) key */
		}
		else {
			right = mid - 1; /* adjustment of right(end) key */
		}
	}
	return iRet;
}


