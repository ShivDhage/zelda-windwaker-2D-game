#include "ofApp.h"
#include <map>

void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);

	//required call
	gui.setup();

	ImGui::GetIO().MouseDrawCursor = false;
	//backgroundColor is stored as an ImVec4 type but can handle ofColor
	//backgroundColor = ofColor(114, 144, 154);
	player = new Player(gameEngine.getLayout());


	
}

//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(255, 255, 255);
	
}
void ofApp::resolveIslands(vector<Direction> directions, map<int, string>& islandMap)
{
	map<string, int> islandDirectionMap = {

			{"north",2},
			{"south",22},
			{"east",14},
			{"west",10},
			{"northwest",0},
			{"northeast",4},
			{"southwest",20},
			{"southeast",24},
			{"up",2},
			{"down",22}
	};

	for (int i = 0; i < directions.size(); i++)
	{
		string direction = directions[i].getDirectionName();
		string islandName = directions[i].getIslandName();
		transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
		
		
		if ( islandDirectionMap.find(direction) != islandDirectionMap.end())
		{
			int position = islandDirectionMap[direction];
			islandMap[position] = islandName;
		}

	}
}
void ofApp::draw() {


	map<int, string>  islandMap;

	resolveIslands((player)->getCurrentIsland().getDirections(), islandMap);
	
	//ofSetBackgroundColor(backgroundColor);

	//required to call this at beginning
	gui.begin();
	ImGui::SetWindowPos(ImVec2(25,25));
	ImGui::SetWindowSize(ImVec2(900.0f, 700.0f), NULL);

	ImGui::Columns(5, NULL);
	ImGui::Separator();
	char name[25];

	for (int i = 0; i < 25; i++)
	{
		if (i > 0 && i % 5 == 0) ImGui::Separator();
		//sprintf(name, "%d", i);

		string buttonName = "";

		if (i == 12)
			buttonName = player->getCurrentIsland().getName().c_str();
		else
		{
			if (islandMap.find(i) != islandMap.end())
			{
				buttonName = islandMap[i];
			}

		}
		ImGui::Button(buttonName.c_str(), ImVec2(175.0f, 125.0f));
		ImGui::NextColumn();
	}

	ImGui::Begin("Game Window", NULL);
	ImGui::SetWindowSize(ImVec2(475.0f, 425.0f));
	ImGui::SetWindowPos(ImVec2(25.0f, 750.0f));
	if (gameEngine.isGameOver())
	{
		gameResponse = gameResult.gameMessage + "\n" + "----------------------------------\n" + "Game is over! Either enter quit or exit or close the game windows!";
	}
	else
	{
		gameResponse = gameResult.gameMessage + "\n" + "----------------------------------\n" + gameEngine.getGameEngineResponse(*player);
	}

	ImGui::Text("Game Status");
	ImGui::BeginChild("GameStatus");
	ImGui::TextWrapped(gameResponse.c_str());
	ImGui::EndChild();

	ImGui::End();

	ImGui::Begin("Player Window", NULL);
	ImGui::SetWindowSize(ImVec2(500.0f, 150.0f));
	ImGui::SetWindowPos(ImVec2(525.0f, 750.0f));
	string playerResponse = "Player response";
	static int lines = 0;
	ImGui::Text("Player response");
	string enterMsg = " processing  enter key";

	if (ImGui::InputText("", this->playerInput, 256, ImGuiInputTextFlags_EnterReturnsTrue, NULL, this->playerInput))
	{
		if (this->playerInput[0])
		{

			gameResult = gameEngine.processPlayerInput(*player, string(playerInput));
			strcpy(this->playerInput, "");
			if (gameResult.gameStatus == GameResult::GAME_EXIT)
			{
				ofExit(1);
			}
		}
		 
	}
	ImGui::BeginChild("Player Response");
	ImGui::EndChild();
	ImGui::End();
	gui.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
