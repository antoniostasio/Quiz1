#pragma once

#include <fstream>
#include <vector>
#include <array>
#include <set>
#include <string>
#include <cstdlib>
#include <random>
#include "Question.h"
#include "QuestionBoolean.h"
#include "QuestionMultipleChoice.h"

class QuestionManager {
    std::vector<Question *> questions;
    
    const std::array<std::string, 2> QuestionTypes = {"m", "b"};
    
    Question* questionOfType(const std::string& questionToken, std::ifstream& txtfile) {
        std::string line;
        // build boolean question
        if(questionToken.compare("b") == 0) {
            std::getline(txtfile, line);
            QuestionBoolean *qb = new QuestionBoolean(line);
            std::getline(txtfile, line);
            bool solution = false;
            if(line.compare("true") == 0){
                solution = true;
            }
            qb->addSolution(solution);
            return qb;
        }
        
        // build multiple choice question
        else if(questionToken.compare("m") == 0) {
            std::getline(txtfile, line);
            QuestionMultipleChoice *qm = new QuestionMultipleChoice(line);
            
            std::getline(txtfile, line);
            qm->setCorrectAnswer(line);
            
            std::streampos savedPos = txtfile.tellg();
            while(std::getline(txtfile, line)) {
                // check if no more answers
                bool foundNextObject = false;
                for(const auto& qtype : QuestionTypes) {
                    int comparisonResult = line.compare(qtype);
                    if(comparisonResult == 0) {
                        foundNextObject = true;
                        break; // found: no need to keep checking
                    }
                }
                if(foundNextObject) {
                    txtfile.seekg(savedPos);
                    break;
                }
                qm->addWrongAnswer(line);
                savedPos = txtfile.tellg();
            }
            return qm;
        }
        return nullptr;
    }
    
    
    void LoadDataFromFile(std::string textfileName) {
        std::ifstream txtfile;
        txtfile.open(textfileName);

        std::string line;
        while(std::getline(txtfile, line)) {
            for(const auto& qtype : QuestionTypes) {
                bool foundNewQuestion = line.compare(qtype) == 0;
                if(foundNewQuestion) {
                    Question *newQuestion = questionOfType(qtype, txtfile);
                    if(newQuestion != nullptr)
                        questions.push_back(newQuestion);
                    break;
                }
            }
        }
        txtfile.close();
    }
    
public:
    QuestionManager(std::string textfile_name) {
        LoadDataFromFile(textfile_name);
    }
    
    ~QuestionManager() {
        for(auto q : questions) {
            delete q;
        }
    }
    
    
    std::vector<Question *> GetQuestionSet(int desiredSize = 5) {
        std::vector<Question *> selection;
        
        int questionsCount = questions.size();
        
        std::random_device rng("default");
               
        std::set<int> selectedIndexes;
        if(questionsCount < desiredSize)
            desiredSize = questionsCount;
            
        while(selectedIndexes.size() < desiredSize) {
            selectedIndexes.insert(rng() % questionsCount);
        }
        for(auto index : selectedIndexes) {
            selection.push_back(questions.at(index));
        }
        // std::shuffle(std::begin(selection), std::end(selection), rng); 
        return selection;
    }
};