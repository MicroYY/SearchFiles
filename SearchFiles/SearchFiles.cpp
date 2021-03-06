#include <iostream>
#include <cstring>
#include <io.h>
#include <direct.h>
#include <string>
#include <fstream>

using namespace std;

void listFiles(const char * dir);

int main()
{
	cout << "输入目录以  \'\\\' 结尾,回车为默认目录" << endl;
	char dir[1000];
	cin.getline(dir, 1000);
	if (!dir[0])
	{
		_getcwd(dir, 1000);
		strcat(dir, "\\");
	}

	cout << "输入查找的文件,回车搜索所有文件" << endl;
	char type[100];
	cin.getline(type, 100);
	if (!type[0])
		strcat(dir, "*.*");
	else
	{	
		string s(dir);
		string t(type);
		s += t;
		strcpy(dir, s.c_str());
	}
    
	listFiles(dir);

	system("pause");
	return 0;
}

void listFiles(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
	if (handle == -1)
	{
		cout << "Failed to find first file!\n";
		return;
	}

	ofstream output;
	output.open("files.txt");

	do
	{
		if (findData.attrib & _A_SUBDIR
			&& strcmp(findData.name, ".") == 0
			&& strcmp(findData.name, "..") == 0
			)    // 是否是子目录并且不为"."或".."
			cout << findData.name << "\t<dir>\n";
		else
		{
			cout << findData.name << "\t" << findData.size << endl;
			output << findData.name << endl;
		}
	} while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件

	output.close();
	cout << "Done!\n";
	_findclose(handle);    // 关闭搜索句柄
}