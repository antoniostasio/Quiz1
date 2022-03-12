#pragma once

#include "Question.h"

class QuestionMultipleChoice: public Question {
public:
    QuestionMultipleChoice(std::string text): Question(text) {};
    QuestionMultipleChoice(QuestionMultipleChoice& qm): Question(qm.GetQuestionText()) {};
    // QuestionMultipleChoice(std::vector<std::string> content) {};
    
    
    void AddWrongAnswer(std::string answer) {
        _wrongAnswers.push_back(answer);
    }
    
    // First element must be correct answer
    void AddAnswers(const std::vector<std::string>& answers) {
        int i = 0;
        _correctAnswer = answers[i];
        for(i = 1; i < answers.size(); ++i) {
            _wrongAnswers.push_back(answers[i]);
        }
    }
    
    void SetCorrectAnswer(std::string answer) {
        _correctAnswer = answer;
    }
    
    std::vector<std::string> GetAnswers() override {
        std::vector<std::string> answers {_wrongAnswers};
        answers.push_back(_correctAnswer);
        // answers.insert(std::end(answers), std::begin(_wrongAnswers), std::end(_wrongAnswers));
        // for(auto ans : _wrongAnswers) {
            // answers.push_back(ans);
        // }
        
        return answers;
    }
    
    std::string GetSolution() override {
        return _correctAnswer;
    }
private:
    std::vector<std::string> _wrongAnswers;
    std::string _correctAnswer;
};