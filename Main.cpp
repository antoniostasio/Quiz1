#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include "Question.h"
#include "QuestionBoolean.h"
#include "QuestionMultipleChoice.h"
#include "QuestionManager.h"


using std::ifstream;
using std::cout;
using std::string;
using std::endl;
using std::vector;


int main() {    
    QuestionManager questionManager("domande.txt");
    vector<Question *> questions = questionManager.GetQuestionSet();

    
    std::random_device rng("default");
    std::shuffle(std::begin(questions), std::end(questions), rng);
    
    cout << "\x1B[2J\x1B[H"
         << "\n- - - - - - - - - - - - -\n\n";
    int score = 0;
    for(int n=0; n< questions.size(); ++n) {
        Question *qs = questions.at(n);
        // cout << "\x1B[2J\x1B[H"; //clear console
        cout << "\tQuestion " << (n+1) << '\n' << qs->getQuestionText() << endl;
        
        vector<string> &answers = qs->getAnswers();
        std::shuffle(std::begin(answers), std::end(answers), rng);
        int i = 1;
        for(auto ans : answers) {
            cout << i++ << ". " << ans << endl;
        }
        
        int selection = 0;
        std::cin >> selection;
        
        bool correct = false;
        if(selection > 0 && selection <= answers.size()) {
            const string& selected_answer = answers.at(selection-1);
            const string& solution = qs->getSolution();
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
    
    return 0;
}