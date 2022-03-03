#pragma once

#include <string>
#include <array>
#include <vector>


class Question {
public:
    Question(std::string content): text(content) {};
    void setQuestionText(std::string txt) {
        text = txt;
    }
    
    std::string getQuestionText() {
        return text;
    }
    
    virtual std::vector<std::string> getAnswers() = 0;
    
    virtual std::string getSolution() = 0;
private:
    std::string text;
};
