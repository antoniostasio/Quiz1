#pragma once

#include "Question.h"
#include "QuestionBoolean.h"
#include "QuestionManager.h"
#include "QuestionMultipleChoice.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

inline void ClearTerminal() { cout << "\x1B[2J\x1B[H"; }

void StartQuizWith(const vector<Question *> &questions) {
    
    cout << "\n- - - - - - - - - - - - -\n\n";
    int score = 0;
    for(int n = 0; n < questions.size(); ++n) {
        Question *qs = questions.at(n);
        
        cout << "Question " << (n+1) << '\n' ;
        cout << qs->GetQuestionText() << '\n' << endl;
        
        vector<string> &answers = qs->GetAnswers();
        std::random_device rng("default");
        std::shuffle(std::begin(answers), std::end(answers), rng);
        
        int i = 1;
        for(auto ans : answers) {
            cout << '\t' << i++ << ". " << ans << endl;
        }
        
        // Check selected answer
        int selection = 0;
        std::cin >> selection;
        
        bool correct = false;
        if(selection > 0 && selection <= answers.size()) {
            const string& selected_answer = answers.at(selection-1);
            const string& solution = qs->GetSolution();
            if(solution.compare(selected_answer) == 0) {
                correct = true;
                ++score;
            }
        }
        if(correct)
            cout << "correct!\n" << endl;
        else
            cout <<  "wrong!\n"  << endl;
    }
    cout << "\n- - - - - - - - - - - - -"
         << "\nCorrect answers: " << score << "/" << questions.size() << endl;
}

int main() {
    // QuestionManager questionManager("domande.txt");
    QuestionManager questionManager("domande2.txt");
    vector<Question *> questions = questionManager.GetQuestionSet();
    
    // Quiz taking
    ClearTerminal();
    StartQuizWith(questions);
    
    return 0;
}