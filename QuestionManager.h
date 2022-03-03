#pragma once

#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <cstdlib>
#include "Question.h"
#include "QuestionBoolean.h"
#include "QuestionMultipleChoice.h"

class QuestionManager {
    std::vector<Question *> questions;
    
    void LoadDataFromFile(std::string textfileName) {
        std::ifstream txtfile;
        txtfile.open(textfileName);
        
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
                
                std::getline(txtfile, line);
                qm->setCorrectAnswer(line);
                
                std::streampos oldpos = txtfile.tellg();
                while(std::getline(txtfile, line)) {
                    if((line.compare("m") * line.compare("b")) == 0) {
                        txtfile.seekg(oldpos);
                        break;
                    }
                    qm->addWrongAnswer(line);
                    oldpos = txtfile.tellg();
                }
                
                questions.push_back(qm);
            }
        }
    }
    
public:
    QuestionManager(std::string textfile_name) {
        LoadDataFromFile(textfile_name);
    }
    
    std::vector<Question *> GetQuestionSet() {
        std::vector<Question *> selection;
        
        int questionsCount = questions.size();
        
        std::set<int> selectedIndexes;
        while(selectedIndexes.size() < 5) {
            selectedIndexes.insert(rand() % questionsCount);
        }
        for(auto index : selectedIndexes) {
            selection.push_back(questions.at(index));
        }
        
        return selection;
    }
};