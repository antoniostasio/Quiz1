#include <string>
#include <array>
#include <vector>

#ifndef QUESTION_H
#define QUESTION_H

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
private:
    std::string text;
};

#endif