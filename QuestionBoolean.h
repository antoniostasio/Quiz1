#pragma once

#include "Question.h"

class QuestionBoolean: public Question {
public:
    QuestionBoolean(std::string content): Question(content) {};
    QuestionBoolean(QuestionBoolean& qb): Question(qb.getQuestionText()) {
        setQuestionText(qb.getQuestionText() );
    };
    
    
    std::vector<std::string> getAnswers() override {
        std::vector<std::string> answers;
        answers.push_back("true");
        answers.push_back("false");
        
        return answers;
    }
    
    
    void addSolution(bool sol) {
        solution = sol;
    }
    
    
    std::string getSolution() override {
        if(solution)
            return "true";
        else
            return "false";
    }
private:
    bool solution;
};