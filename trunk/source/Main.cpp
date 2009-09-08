/*	NxOgre Tutorial 1: Simple Sample by radsun	*/

#include "GameBalyoz.h"
#include <iostream>
#include <Windows.h>
using namespace std;



//	startup
INT WINAPI WinMain(HINSTANCE , HINSTANCE, LPSTR, INT)
{
	Balyoz::GameBalyoz app;

	//	aplication setup and loop
	try {
        app.go();
    } catch( Ogre::Exception& e ) {
        MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}

	return 0;
}