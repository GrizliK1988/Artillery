#include "Application.h"
#include <iostream>
#include <string>


void WriteError( const std::string &message )
{
    std::clog << "Error: " << message << std::endl;
}


int main()
{
#ifdef _DEBUG
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    try
    {
        Application app;
        app.Init();
        app.MainLoop();
    }
    catch( std::exception &e )
    {
        WriteError( e.what() );
    }
    catch( ... )
    {
        WriteError( "unknown exception" );
    }

    return 0;
}

