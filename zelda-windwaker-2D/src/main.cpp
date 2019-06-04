#pragma once
#include "ofMain.h"
#include "ofApp.h"





/*========================================================================
	Main function which runs when application is built in Release mode
*/
int main( ){

	ofSetupOpenGL(1200, 1200, OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowPosition(10, 10);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	
	//GameEngine gm("WindWaker.json");
	//gm.play();
	return 0;
}

