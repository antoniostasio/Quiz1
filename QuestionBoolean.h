#pragma once

#include "Question.h"

class QuestionBoolean: public Question {
public:
    QuestionBoolean(std::string content): Question(content) {};
    QuestionBoolean(QuestionBoolean& qb): Question(qb.GetQuestionText()) {
        SetQuestionText(qb.GetQuestionText() );
    };
    QuestionBoolean(const std::string& content, bool solution) 
        : Question(content), _solution(solution) {};
    
    std::vector<std::string> GetAnswers() override {
        std::vector<std::string> answers;
        answers.push_back("true");
        answers.push_back("false");
        
        return answers;
    }
    
    // TODO add constructor with solution
    void setSolution(bool sol) {
        _solution = sol;
    }
    
    
    std::string GetSolution() override {
        if(_solution)
            return "true";
        else
            return "false";
    }
private:
    bool _solution;
};