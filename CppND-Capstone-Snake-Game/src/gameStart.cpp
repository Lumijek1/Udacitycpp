#include "gameStart.h"
#include <sstream>
#include <algorithm>


bool gameStarter::sortByValue(const std::pair<std::string, int> &a,const std::pair<std::string, int> &b) { 
    return (a.second > b.second); 
} 


int gameStarter::start(Game &game){
  std::cout << "Welcome to the Snake Game" << std::endl;
  std::cout << "Do you want to: \n" << std::endl;
  std::cout << "1. Play" << std::endl;
  std::cout << "2. Read the rules" << std::endl;
  std::cout << "3. View the Leaderboard" << std::endl;
  std::cout << "4. Quit" << std::endl;
  int input;  
  while(!(std::cin >> input) || input > 4 || input < 1) {
    std::cin.clear(); 
   	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter a valid integer ranging from 1 - 4. " << std::endl;
  }
  if(input == 1){
    std::cout << "Select Difficulty: " << std::endl;
    std::cout << "1. Easy " << std::endl;
    std::cout << "2. Medium " << std::endl;
    std::cout << "3. Hard " << std::endl;
    int difficultyInput;  
  	while(!(std::cin >> difficultyInput) || difficultyInput > 3 || difficultyInput < 1){
    	std::cin.clear(); 
   		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    	std::cout << "Please enter a valid integer ranging from 1 - 3. " << std::endl;
  	}
    setDifficulty(difficultyInput, game);
    
    std::cout << "Starting Game!" << std::endl;
    return 1;
  }
  else if (input == 2){
    std::cout << "The goal if the game is to get as big as possible! " << std::endl;
    std::cout << "Use your arrow keys to move. Type q to quit the game at any time and p to pause the game" << std::endl;
    std::cout << "If you are playing with obstacles be sure to avoid them so that you don't die! " << std::endl;
    return 2;     	    
  }
  else if (input == 3){
    std::cout << "\n\n" << std::endl;
    printLeaderBoards();
    return 3;
  }
  else if (input == 4){
    quit();
  }
  
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
  std::fstream highScores("../src/highScore.txt");
  std::string line, name, score;
  if (highScores.is_open()){
  	while(std::getline(highScores, line)){
  		std::istringstream linestream(line);
  		while (linestream >> name >> score) {
  			leaderBoard[name] = std::stoi(score);
  		}
  	}
  }
  else std::cout << "Open failed" << std::endl;
  std::vector<std::pair<std::string, int>> lb;
  std::map<std::string, int> :: iterator it;
  for (it = leaderBoard.begin(); it != leaderBoard.end(); it++) {
    lb.push_back(make_pair(it->first, it->second));
  }
  std::sort(lb.begin(), lb.end(), sortByValue); 
  std::cout << "Leaderboard! " << std::endl;
  for (int i = 0; i < 10; i++) {
		std::cout << i + 1 << ". " << lb[i].first << ": " << lb[i].second << std::endl;
  }
}
void gameStarter::setDifficulty(int difficulty, Game& game){
  if(difficulty == 1){
     game.setSpeedIncrease(0.02); 
  }
  if(difficulty == 2){
     game.setSpeedIncrease(0.03);
     game.setObstacles(true, 10);
  }
  if(difficulty == 3){
     game.setSpeedIncrease(0.04);
     game.setObstacles(true, 20);
  }
}
bool gameStarter::playAgain(){
  
}
void gameStarter::quit(){
  exit(0);
}


