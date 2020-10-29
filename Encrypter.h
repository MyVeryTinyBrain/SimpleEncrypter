#pragma once
#include <iostream>
#include <fstream>
#include <io.h>
#include <string>
#include <vector>
using namespace std;

class Encrypter
{
	string m_Directory;
	vector<string> m_TargetPathes;
public:
	Encrypter();
	~Encrypter();
	void SetDirectory( string directory );
	string GetDirectory();
	int FindFiles( string filter = "*.*" );
	void Encrypte();
	void Decrypte();
	void EncrypteOnce( string path );
	void DecrypteOnce( string path );
};