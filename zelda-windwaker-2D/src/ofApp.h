#pragma once

#include "ofMain.h"
#include <string.h>
#include "ofxImGui.h"
#include "domain/GameEngine.h";
#include "domain/Player.h";

using namespace adventure::domain;

/* Header file of open framework App which defines interface for various interactive actions*/
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void resolveIslands(vector<Direction> directions, map<int, string>& islandMap);
		ofxImGui::Gui gui;
		string gameStatusText="Game Status : ";
		string playerResponseText = "Your input : ";
		char  playerInput[1000] = "";
		string gameResponse = "";
		ImGuiIO& io = ImGui::GetIO();
		GameResult gameResult;
		GameEngine gameEngine;
		Player* player;
			


};
