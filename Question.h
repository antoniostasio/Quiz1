#pragma once

#include <string>
#include <array>
#include <vector>


class Question {
public:
    Question(std::string content): _text(content) {};
    
    void SetQuestionText(const std::string& text) {
        _text = text;
    }
    
    std::string GetQuestionText() {
        return _text;
    }
    
    virtual std::vector<std::string> GetAnswers() = 0;
    
    virtual std::string GetSolution() = 0;
private:
    std::string _text;
};
