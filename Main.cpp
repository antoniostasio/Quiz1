// #include "SDL2/include/SDL.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Question.h"
#include "QuestionBoolean.h"
#include "QuestionMultipleChoice.h"

int main() {
    std::ifstream txtfile;
    txtfile.open("domande.txt");
    
    std::vector<Question *> questions;
    
    std::string line;
    while(std::getline(txtfile, line)) {
        if(line.compare("b") == 0) {
            std::getline(txtfile, line);
            QuestionBoolean *qb = new QuestionBoolean(line);
            std::getline(txtfile, line);
            if(line.compare("true") == 0){
                qb->addSolution(true);
            }
            questions.push_back(qb);
        }
        else if(line.compare("m") == 0) {
            std::getline(txtfile, line);
            QuestionMultipleChoice *qm = new QuestionMultipleChoice(line);
            questions.push_back(qm);
        }
    
    }
    
    for(auto qs : questions) {
        std::cout << "Question: " << qs->getQuestionText() << std::endl;
        int i = 1;
        for(auto ans : qs->getAnswers()) {
            std::cout << i++ << ". " << ans << std::endl;
        }
    }
    // std::getline(txtfile, line);
    // std::getline(txtfile, line);
    // QuestionBoolean qb(line);
    // std::getline(txtfile, line);
    // if(line.compare("true") == 0){
        // qb.addSolution(true);
    // }
    // 
    // std::cout << qb.getQuestionText() << std::endl;
    // int i = 1;
    // for(auto ans : qb.getAnswers()) {
        // std::cout << i++ << ". " << ans << std::endl;
    // }
    
    return 0;
}