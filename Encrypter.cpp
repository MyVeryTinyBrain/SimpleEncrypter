#include "Encrypter.h"

Encrypter::Encrypter()
{
}

Encrypter::~Encrypter()
{
}

void Encrypter::SetDirectory( string directory )
{
    m_Directory = directory;
}

string Encrypter::GetDirectory()
{
    return m_Directory;
}

int Encrypter::FindFiles( string filter )
{
    m_TargetPathes.clear();

    string findKeyword = m_Directory + '/' + filter;
    _finddata_t fd;
    int handle = _findfirst( findKeyword.c_str(), &fd );
    if ( handle == -1 ) return 0;

    int fileCount = 0;
    do
    {
        m_TargetPathes.push_back( m_Directory + '/' + fd.name );
        ++fileCount;
    } while ( _findnext( handle, &fd ) == 0 );

    _findclose( handle );
}

void Encrypter::Encrypte()
{
    for ( auto i : m_TargetPathes )
    {
        EncrypteOnce( i );
    }
}

void Encrypter::Decrypte()
{
    for ( auto i : m_TargetPathes )
    {
        DecrypteOnce( i );
    }
}

void Encrypter::EncrypteOnce( string path )
{
    int pos = path.find( ".encrypted" );
    if ( pos != string::npos ) return;

    ifstream in( path.c_str(), ifstream::binary );
    in.seekg( 0, ifstream::end );
    int size = in.tellg();
    if ( !in.is_open() || size < 0 ) return;
    char* buf = new char[size];
    in.seekg( 0, ifstream::beg );
    in.read( buf, size );
    in.close();

    ofstream out( path.c_str(), ofstream::binary );
    out.seekp( 0, ofstream::beg );
    reverse( buf, &buf[size - 1] );
    out.write( buf, size );
    //for ( int i = 0; i < size; i++ )
    //{
    //    char byte = ~buf[i];
    //    out.write( &byte, 1 );
    //}
    out.close();
    printf( "%s is Encrypted\n", path.c_str() );
    rename( path.c_str(), ( path + ".encrypted" ).c_str() );
}

void Encrypter::DecrypteOnce( string path )
{
    int pos = path.find( ".encrypted" );
    if ( pos == string::npos ) return;

    ifstream in( path.c_str(), ifstream::binary );
    in.seekg( 0, ifstream::end );
    int size = in.tellg();
    if ( !in.is_open() || size < 0 ) return;
    char* buf = new char[size];
    in.seekg( 0, ifstream::beg );
    in.read( buf, size );
    in.close();

    ofstream out( path.c_str(), ofstream::binary );
    out.seekp( 0, ofstream::beg );
    reverse( buf, &buf[size - 1] );
    out.write( buf, size );
    //for ( int i = 0; i < size; i++ )
    //{
    //    char byte = ~buf[i];
    //    out.write( &byte, 1 );
    //}
    out.close();
    printf( "%s is Decrypted\n", path.c_str() );
    rename( path.c_str(), ( path.substr( 0, pos ) ).c_str() );
}
