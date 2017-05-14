// getCSV.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ※istringstreamを使うために必要

#include "GetContents.h"

// 名前空間
using namespace std;

int main(int argc, char **argv)
{
	// 変数を定義する
	bool status = false;    // メソッドのステータス
	string filename = "sample.csv";		// ファイル名
	vector<vector<string>> table;		// 読み込んだCSVファイルの内容
	vector<vector<string>> table2;		// 読み込んだCSVファイルの内容 その２
	fpos_t ft;							// ファイルポインタ
	string csvData;						// CSVファイルの内容 1ファイル分
	vector<string>	oneLineDiv;			// 読み込んだCSVファイルの内容 1行分割
	vector<string>::iterator itr;		// 読み込んだCSVファイルの内容 1行分割（イテレータ)


	// CSV取得クラス
	GetContents clsGetCSV;

	filename = argv[1];

	// ------------------------------------------
	//  --- STEP1 CSVファイル情報出力 ---
	// ------------------------------------------
	// CSVファイルのサイズを取得する
	clsGetCSV.GetCSVFileSize(filename, &ft);
	// CSVファイルの内容を取得する
	clsGetCSV.ReadFileToString(filename, csvData);
	//　CSVファイルの情報を出力
	cout << " --- STEP1 CSVファイル情報出力 ---" << endl;
	cout << "File Name :" << filename <<  endl << "ファイルサイズ" << ft << endl <<csvData  << endl;


	// ------------------------------------------
	//  --- STEP2 GetCSVString ---
	// ------------------------------------------
	//　CSVファイルの情報を出力
	clsGetCSV.GetCSVString(csvData, oneLineDiv);
	cout << " --- STEP2 GetCSVString 結果出力 ---" << endl;
	for (auto itr = oneLineDiv.begin(); itr != oneLineDiv.end(); ++itr) {
		cout << (*itr) << endl;
	}
	cout << endl;

	// ------------------------------------------
	//  --- STEP3 GetCSVString2 ---
	// ------------------------------------------
	status = clsGetCSV.GetCSVString2(csvData, table);
	if (!status)
	{
		// 取得に失敗した場合はエラー終了する
		return -1;
	}

	// 確認のためにコンソールに内容を出力する(第一カラムのみ）
	cout << " --- STEP3 GetCSVString2 結果出力 ---" << endl;
	for (int row = 0; row < table2.size(); row++)
	{
		std::string str = table2[row][0];
		cout << str << endl;
	}
	cout << endl;

	// ------------------------------------------
	//  --- STEP4 GetCSVFile ---
	// ------------------------------------------
	status = clsGetCSV.GetCSVFile2(filename, table2);
	if (!status)
	{
		// 取得に失敗した場合はエラー終了する
		return -1;
	}

	// 確認のためにコンソールに内容を出力する
	cout << " --- STEP4 GetCSVFile2 結果出力 ---" << endl;
	for (int row = 0; row < table2.size(); row++)
	{
		vector<string> record;  // １行分の内容
		record = table2[row];    // １行分読み込む
								// １セルずつ読み込んでコンソールに出力する
		for (int column = 0; column < record.size(); column++)
		{
			cout << record[column];
			// 末尾の列でない場合はカンマを出力する
			if (column < record.size() - 1)
			{
				cout << ",";
			}
		}
		cout << endl;
	}

	// ------------------------------------------
	//  --- STEP5 二分探索 ---
	// ------------------------------------------
	vector<string> strResult;
	int	   iRet;
	std::string key = argv[2];
	iRet = clsGetCSV.BsearchCSV(key, table2, strResult);
	cout << "Ret[" << std::to_string(iRet) << "]" << endl;
	for (vector<string>::iterator itr = strResult.begin(); itr != strResult.end(); ++itr) {
		cout << "[" <<(*itr) << "]" << endl;
	}
	cout << endl;


    return 0;
}

