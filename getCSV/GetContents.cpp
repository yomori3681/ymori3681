#include "stdafx.h"
#include "GetContents.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>  // ��istringstream���g�����߂ɕK�v
// ���O���
using namespace std;

// �R���X�g���N�^
GetContents::GetContents()
{
}

// �f�B�X�R���X�g���N�^
GetContents::~GetContents()
{
}
// ----------------------------------------------------------------------------
//���\�b�h��	�F	GetCSVFile2
//	�@�\		�F	CSV�t�@�C���ǂݍ��� [CSV�t�@�C���ǂݍ��ݍ������o�[�W����]
//	����		�F	const string& filename		�iI)	CSV�t�@�C����
//					vector<vector<string>>& table(O)	�ǂݍ��݌���(�s�E�J�����P��)
//					onst char delimiter			�iI)	CSV�t�@�C���̋�؂蕶��				
// -----------------------------------------------------------------------------
bool GetContents::GetCSVFile2(const string& filename, vector<vector<string>>& table, const char delimiter)
{
	bool bRet = false;
	std::string strData;

	// CSV�t�@�C���ꊇ�ǂݍ���
	if (ReadFileToString(filename, strData) == -1)
		return bRet;

	// CSV�f�[�^��vector�Ɋi�[
	return(GetCSVString2(strData, table, delimiter));
}

// ----------------------------------------------------------------------------
//���\�b�h��	�F	GetCSVFile
//	�@�\		�F	CSV�t�@�C���ǂݍ���
//	����		�F	const string& filename		�iI)	CSV�t�@�C����
//					vector<vector<string>>& table(O)	�ǂݍ��݌���(�s�E�J�����P��)
//					onst char delimiter			�iI)	CSV�t�@�C���̋�؂蕶��				
// -----------------------------------------------------------------------------

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


// ----------------------------------------------------------------------------
//���\�b�h��	�F	GetCSVString
//	�@�\		�F	CSV�f�[�^��vector�^�f�[�^�Ɋi�[����
//	����		�F	const string & csvdata		(I)	CSV�f�[�^
//					vector<string>& table		(O)	�ǂݍ��݌���(�s�P��)
//					onst char delimiter			(I)	CSV�t�@�C���̋�؂蕶��				
// -----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
//���\�b�h��	�F	GetCSVString2
//	�@�\		�F	CSV�f�[�^��vector�^�f�[�^�Ɋi�[����
//	����		�F	const string & csvdata		�iI)	CSV�f�[�^
//					vector<vector<string>>& table(O)	�ǂݍ��݌���(�s�E�J�����P��)
//					onst char delimiter			�iI)	CSV�t�@�C���̋�؂蕶��				
// -----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
//���\�b�h��	�F	GetCSVFileSize
//	�@�\		�F	CSV�t�@�C���̃t�@�C���T�C�Y���擾����
//	����		�F	const string& filename		(I)	CSV�t�@�C����
//					fpos_t* ft					(O)	�t�@�C���T�C�Y
// -----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
//���\�b�h��	�F	ReadFileToString
//	�@�\		�F	CSV�t�@�C���ǂݍ���string�^�f�[�^�ɕۑ�����
//	����		�F	const string& filename		(I)	CSV�t�@�C����
//					string& strData				(O)	�ǂݍ��݌���(�P�t�@�C���ꊇ�ǂݍ���)
// -----------------------------------------------------------------------------

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


