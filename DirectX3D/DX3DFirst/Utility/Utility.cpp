#include "Framework.h"
#include "Utility.h"

wstring Utility::GetExtension(wstring path)
{
	UINT index = path.find_last_of('.');



	return path.substr(index + 1, path.length());
}

string Utility::ToString(wstring str)
{
	string tmp;

	tmp.assign(str.begin(), str.end());

	return tmp;
}

wstring Utility::ToWString(string str)
{
	wstring tmp;

	tmp.assign(str.begin(), str.end());

	return tmp;
}

wstring Utility::GetProjectDir()
{

	WCHAR curPath[128];
	GetCurrentDirectory(128, curPath);

	wstring dir = curPath;

	return dir + L"/";
}

wstring Utility::GetTextureDir()
{
	return GetProjectDir() + L"_Texture/";
}
