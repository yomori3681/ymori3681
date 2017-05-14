// getCSV.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ��istringstream���g�����߂ɕK�v

#include "GetContents.h"

// ���O���
using namespace std;

int main(int argc, char **argv)
{
	// �ϐ����`����
	bool status = false;    // ���\�b�h�̃X�e�[�^�X
	string filename = "sample.csv";		// �t�@�C����
	vector<vector<string>> table;		// �ǂݍ���CSV�t�@�C���̓��e
	vector<vector<string>> table2;		// �ǂݍ���CSV�t�@�C���̓��e ���̂Q
	fpos_t ft;							// �t�@�C���|�C���^
	string csvData;						// CSV�t�@�C���̓��e 1�t�@�C����
	vector<string>	oneLineDiv;			// �ǂݍ���CSV�t�@�C���̓��e 1�s����
	vector<string>::iterator itr;		// �ǂݍ���CSV�t�@�C���̓��e 1�s�����i�C�e���[�^)


	// CSV�擾�N���X
	GetContents clsGetCSV;

	filename = argv[1];

	// ------------------------------------------
	//  --- STEP1 CSV�t�@�C�����o�� ---
	// ------------------------------------------
	// CSV�t�@�C���̃T�C�Y���擾����
	clsGetCSV.GetCSVFileSize(filename, &ft);
	// CSV�t�@�C���̓��e���擾����
	clsGetCSV.ReadFileToString(filename, csvData);
	//�@CSV�t�@�C���̏����o��
	cout << " --- STEP1 CSV�t�@�C�����o�� ---" << endl;
	cout << "File Name :" << filename <<  endl << "�t�@�C���T�C�Y" << ft << endl <<csvData  << endl;


	// ------------------------------------------
	//  --- STEP2 GetCSVString ---
	// ------------------------------------------
	//�@CSV�t�@�C���̏����o��
	clsGetCSV.GetCSVString(csvData, oneLineDiv);
	cout << " --- STEP2 GetCSVString ���ʏo�� ---" << endl;
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
		// �擾�Ɏ��s�����ꍇ�̓G���[�I������
		return -1;
	}

	// �m�F�̂��߂ɃR���\�[���ɓ��e���o�͂���(���J�����̂݁j
	cout << " --- STEP3 GetCSVString2 ���ʏo�� ---" << endl;
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
		// �擾�Ɏ��s�����ꍇ�̓G���[�I������
		return -1;
	}

	// �m�F�̂��߂ɃR���\�[���ɓ��e���o�͂���
	cout << " --- STEP4 GetCSVFile2 ���ʏo�� ---" << endl;
	for (int row = 0; row < table2.size(); row++)
	{
		vector<string> record;  // �P�s���̓��e
		record = table2[row];    // �P�s���ǂݍ���
								// �P�Z�����ǂݍ���ŃR���\�[���ɏo�͂���
		for (int column = 0; column < record.size(); column++)
		{
			cout << record[column];
			// �����̗�łȂ��ꍇ�̓J���}���o�͂���
			if (column < record.size() - 1)
			{
				cout << ",";
			}
		}
		cout << endl;
	}

	// ------------------------------------------
	//  --- STEP5 �񕪒T�� ---
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

