#include <iostream>
#include <string>
#include <stdexcept>
#include "Application.h"


void WriteErrorToConsole( const std::string &message )
{
    std::cerr << "Error: " << message << std::endl;
}


int main()
{
#if defined _DEBUG | defined DEBUG
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    try
    {
        Application app;
        app.Initialize();
        app.MainLoop();
    }
    catch( const std::exception &e )
    {
        WriteErrorToConsole( e.what() );
    }
    catch( ... )
    {
        WriteErrorToConsole( "unknown exception" );
    }

    return 0;
}

