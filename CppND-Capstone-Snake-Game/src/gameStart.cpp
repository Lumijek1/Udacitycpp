#include "gameStart.h"
#include "game.h"
#include <sstream>
#include <algorithm>

std::string gameStarter::lower(std::string data){
  std::for_each(data.begin(), data.end(), [](char & c) {
    c = ::tolower(c);
  });
  return data;
}
bool gameStarter::sortByValue(const std::pair<std::string, int> &a,const std::pair<std::string, int> &b) { 
    return (a.second > b.second); 
} 

void gameStarter::highScore(std::string name, int score){
  std::fstream highscore("highScore.txt", std::ios::app);
  if (highscore.is_open())
  {
    highscore << name << " " << score << std::endl;
  }
  highscore.close();
}
void gameStarter::printLeaderBoards(){
  std::map<std::string, int> leaderBoard;
  std::fstream highScores("highScore.txt");
  std::string line, name, score;
  if (highScores.is_open()){
  	while(std::getline(highScores, line)){
  		std::istringstream linestream(line);
  		while (linestream >> name >> score) {
  			leaderBoard[name] = std::stoi(score);
  		}
  	}
  }
  std::vector<std::pair<std::string, int>> lb;
  std::map<std::string, int> :: iterator it;
  for (it = leaderBoard.begin(); it != leaderBoard.end(); it++) {
    lb.push_back(make_pair(it->first, it->second));
  }
  std::sort(lb.begin(), lb.end(), sortByValue); 
  for (int i = 0; i < lb.size(); i++) {
		std::cout << lb[i].first << ": " << lb[i].second << std::endl;
  }
}
void gameStarter::setDifficulty(std::string difficulty){
  if(lower(difficulty) == "easy" || 
     difficulty == "1"){
    Game.setSpeedIncrease(0.02);
  }
  if(lower(difficulty) == "medium" || 
     difficulty == "1"){
    
  }
  if(lower(difficulty) == "hard" || 
     difficulty == "1"){
    
  }
}
bool gameStarter::playAgain(){}
void gameStarter::quit(){
  exit(0);
}


