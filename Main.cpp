#include "Encrypter.h"
#include <fstream>
using namespace std;

int main()
{
	Encrypter c;
	while ( true )
	{
		printf( "Directory: " );
		string directory;
		cin >> directory;
		struct stat __stat;
		if ( stat( directory.c_str(), &__stat ) == -1 ) continue;
		c.SetDirectory( directory );
		c.FindFiles();

		while ( true )
		{
			printf( "1. Encrypte\n" );
			printf( "2. Decrypte\n" );
			printf( ">> " );
			int command;
			cin >> command;
			if ( cin.fail() )
			{
				cin.clear();
				cin.ignore( 1024, '\n' );
				continue;
			}
			switch ( command )
			{
				case 1: c.Encrypte(); break;
				case 2: c.Decrypte(); break;
			}
			break;
		}
	}
}