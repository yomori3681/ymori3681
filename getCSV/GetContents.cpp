#include "stdafx.h"
#include "GetContents.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要
// 名前空間
using namespace std;

// コンストラクタ
GetContents::GetContents()
{
}

// ディスコンストラクタ
GetContents::~GetContents()
{
}

//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	GetCSVFile2
//	機能	：	CSVファイル読み込み [CSVファイル読み込み高速化バージョン]
//	引数	：	const string& filename		（I)	CSVファイル名
//				vector<vector<string>>& table(O)	読み込み結果
//													(行・カラム単位)
//				const char delimiter		（I)	CSVファイルの区切り文字
// ---------------------------------------------------------------------------
bool GetContents::GetCSVFile2(const string& filename
								, vector<vector<string>>& table
								, const char delimiter)
{
	bool bRet = false;
	std::string strData;

	// CSVファイル一括読み込み
	if (ReadFileToString(filename, strData) == -1)
		return bRet;

	// CSVデータをvectorに格納
	return(GetCSVString2(strData, table, delimiter));
}

//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	GetCSVFile
//	機能	：	CSVファイル読み込み
//	引数	：	const string& filename		（I)	CSVファイル名
//				vector<vector<string>>& table(O)	読み込み結果
//													(行・カラム単位)
//				const char delimiter		（I)	CSVファイルの区切り文字
// --------------------------------------------------------------------------

bool GetContents::GetCSVFile(const string& filename
					, vector<vector<string>>& table
					, const char delimiter)
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


//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	GetCSVString
//	機能	：	CSVデータをvector型データに格納する
//	引数	：	const string & csvdata		(I)	CSVデータ
//				vector<string>& table		(O)	読み込み結果(行単位)
// ---------------------------------------------------------------------------

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

//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	GetCSVString2
//	機能	：	CSVデータをvector型データに格納する
//	引数	：	const string & csvdata		（I)	CSVデータ
//				vector<vector<string>>& table(O)	読み込み結果
//													(行・カラム単位)
//				const char delimiter		（I)	CSVファイルの区切り文字
// -------------------------------------------------------------------------

bool GetContents::GetCSVString2(const string & csvdata
								, vector<vector<string>>& table
								, const char delimiter)
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

//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	GetCSVFileSize
//	機能	：	CSVファイルのファイルサイズを取得する
//	引数	：	const string& filename		(I)	CSVファイル名
//				fpos_t* ft					(O)	ファイルサイズ
// ---------------------------------------------------------------------------

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

//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	ReadFileToString
//	機能	：	CSVファイル読み込みstring型データに保存する
//	引数	：	const string& filename		(I)	CSVファイル名
//				string& strData				(O)	読み込み結果
//												(１ファイル一括読み込み)
// ---------------------------------------------------------------------------

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

//       1         2         3         4         5         6         7 
//3456789012345678901234567890123456789012345678901234567890123456789012345678
// ---------------------------------------------------------------------------
//メソッド名：	BsearchCSV
//	機能	：	２分探索をする
//	引数	：	string  key					（I)	探索キー(固定長)
//				vector<vector<string>>& table(I)	読み込み結果
//													(行・カラム単位)
//				vector<string> &resultStr	 (O)	検索成功の場合、
//													1行分のdデータ
//  戻り値	：	1: 検索成功　0：検索成功
// ---------------------------------------------------------------------------

int GetContents::BsearchCSV(string  key
						, vector<vector<string>>& table 
						, vector<string> &resultStr)
{
	int iRet = 0;
	int left = 0;					/* start key of index */
	int right = table.size() -1;	/* end   key of index ( SIZE -1 !!!) */
	int mid = 0;					/* middle key of index */

	while (left <= right) {
		mid = (left + right) / 2  ; /* calc of middle key */
#if 1
		char buff[256];
		sprintf(buff, "left:%3d mid:%3d right:%3d  table[mid][%s] key[%s]"
			, left,mid, right, table[mid][0].c_str(),key.c_str());
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


