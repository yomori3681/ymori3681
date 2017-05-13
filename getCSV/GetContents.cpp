#include "stdafx.h"
#include "GetContents.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ��istringstream���g�����߂ɕK�v
// ���O���
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

	// �t�@�C�����J��
	fstream filestream(filename);
	if (!filestream.is_open())
	{
		// �t�@�C�����J���Ȃ������ꍇ�͏I������
		bRet = false;
		return bRet;
	}

	// �t�@�C����ǂݍ���
	while (!filestream.eof())
	{
		// �P�s�ǂݍ���
		string buffer;
		filestream >> buffer;

		// �t�@�C������ǂݍ��񂾂P�s�̕��������؂蕶���ŕ����ă��X�g�ɒǉ�����
		vector<string> record;              // �P�s���̕�����̃��X�g
		istringstream streambuffer(buffer); // ������X�g���[��
		string token;                       // �P�Z�����̕�����
		while (getline(streambuffer, token, delimiter))
		{
			// �P�Z�����̕���������X�g�ɒǉ�����
			record.push_back(token);
		}

		// �P�s���̕�������o�͈����̃��X�g�ɒǉ�����
		table.push_back(record);
	}

	return bRet;
}

bool GetContents::GetCSVString(const string & csvdata, vector<string>& table)
{
	const char delimiter = '\n';
	string token;						 // �P�s���̕�����
	istringstream streambuffer(csvdata); // ������X�g���[��

	while (getline(streambuffer, token, delimiter))
	{
		// �P�s���̕���������X�g�ɒǉ�����
		table.push_back(token);
	}

	return true;
}

bool GetContents::GetCSVString2(const string & csvdata, vector<vector<string>>& table, const char delimiter)
{
	bool bRet = true;

	const char newLine = '\n';
	string oneLine;								 // �P�s���̕�����
	istringstream streamOneLineBuffer(csvdata);	// ������X�g���[��

	// �t�@�C����ǂݍ���
	while (getline(streamOneLineBuffer, oneLine, newLine))
	{
		// �P�s�̕��������؂蕶���ŕ����ă��X�g�ɒǉ�����
		vector<string> record;						// �P�s���̕�����̃��X�g
		istringstream streambuffer(oneLine);		// ������X�g���[��
		string token;								// �P�Z�����̕�����
		while (getline(streambuffer, token, delimiter))
		{
			// �P�Z�����̕���������X�g�ɒǉ�����
			record.push_back(token);
		}

		// �P�s���̕�������o�͈����̃��X�g�ɒǉ�����
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
	// �t�@�C���|�C���^�𖖔��܂ňړ�
	fseek(fp, 0, SEEK_END);
	// �t�@�C���|�C���^�̈ʒu���擾
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

	// string�^��filename�Ŏw�肵���t�@�C����S���Ǎ���
	std::istreambuf_iterator<char> it(ifs);
	std::istreambuf_iterator<char> last;
	std::string str(it, last);
	// �ǂݍ��񂾃f�[�^���p�����[�^�ɐݒ�
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


