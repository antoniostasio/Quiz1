#pragma once

#include <fstream>
#include <vector>
#include <array>
#include <unordered_set>
#include <string>
#include <random>
#include "Question.h"
#include "QuestionBoolean.h"
#include "QuestionMultipleChoice.h"

#define BOOLEAN_TYPE "b"
#define MULTIPLE_CHOICE "m"

using std::string;


class QuestionManager {
    
    std::vector<Question *> _questions;
    
    const std::array<string, 2> QuestionTypes = {BOOLEAN_TYPE, MULTIPLE_CHOICE};
    
    // enum QuestionType : char {MULTIPLE = 'm', BOOLEAN = 'b'};
    
    
    Question* _questionOfType(const string& questionType, const std::vector<string>& questionData) {
        if(questionData.size() > 1) {
            string whatIsAsked = questionData.front();
            string solutionText = questionData[1];
            
            // build boolean question
            if(questionType.compare(BOOLEAN_TYPE) == 0) {
                bool solution = false;
                if(solutionText.compare("true") == 0) {
                    solution = true;
                }
                QuestionBoolean *qb = new QuestionBoolean(whatIsAsked, solution);
                return qb;
            }
            
            // build multiple choice question
            else if(questionType.compare(MULTIPLE_CHOICE) == 0) {
                QuestionMultipleChoice *qm = new QuestionMultipleChoice(whatIsAsked);
                qm->SetCorrectAnswer(solutionText);
                
                for(int i = 2; i< questionData.size(); ++i) {
                    qm->AddWrongAnswer(questionData[i]);
                }
                return qm;
            }
        }
        return nullptr;
    }
    
    
    void LoadDataFromFile(const string& textfileName) {
        std::ifstream txtfile;
        txtfile.open(textfileName);
        
        string line;
        while(std::getline(txtfile, line)) {
            string questionType = line;
            std::vector<string> linesBuffer;
            while(std::getline(txtfile, line)) {
                bool endOfQuestion = line.compare("") == 0;
                if(endOfQuestion) {
                    Question *newQuestion = _questionOfType(questionType, linesBuffer);
                    if(newQuestion != nullptr)
                        _questions.push_back(newQuestion);
                    break;
                }
                linesBuffer.push_back(line);
            }
        }
        txtfile.close();
    }
    
    
public:
    QuestionManager(const string& textfile_name) {
        LoadDataFromFile(textfile_name);
    }
    
    QuestionManager(const QuestionManager& qm) = delete;
    
    ~QuestionManager() {
        for(auto q : _questions) {
            delete q;
        }
    }
    
    
    std::vector<Question *> GetQuestionSet(int desiredSize = 5) {
        std::vector<Question *> selection;
        
        int questionsCount = _questions.size();
        
        std::random_device rng("default");
               
        std::unordered_set<int> selectedIndexes;
        if(questionsCount < desiredSize)
            desiredSize = questionsCount;
            
        while(selectedIndexes.size() < desiredSize) {
            selectedIndexes.insert(rng() % questionsCount);
        }
        for(auto index : selectedIndexes) {
            selection.push_back(_questions.at(index));
        }
        // std::shuffle(std::begin(selection), std::end(selection), rng); 
        return selection;
    }
};