#include "Question.h"

class QuestionMultipleChoice: public Question {
public:
    QuestionMultipleChoice(std::string content): Question(content) {};
    QuestionMultipleChoice(QuestionMultipleChoice& qm): Question(qm.getQuestionText()) {};
    void addWrongAnswer(std::string answer) {
        wrong_answers.push_back(answer);
    }
    
    void setCorrectAnswer(std::string answer) {
        correct_answer = answer;
    }
    
    std::vector<std::string> getAnswers() override {
        std::vector<std::string> answers;
        answers.push_back(correct_answer);
        answers.insert(std::end(answers), std::begin(wrong_answers), std::end(wrong_answers));
        // for(auto ans : wrong_answers) {
            // answers.push_back(ans);
        // }
        
        return answers;
    }
private:
    std::vector<std::string> wrong_answers;
    std::string correct_answer;
};