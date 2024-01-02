//
// Created by tibov on 30/12/23.
//

#include "HighScore.h"

namespace Logic {
    std::shared_ptr<HighScore> HighScore::getInstance() {
        if (!_instance){
            _instance = std::shared_ptr<HighScore>(new HighScore{});
        }
        return _instance;
    }

    HighScore::HighScore() {
        std::string file_path = "scoreboard";

        //in case file is not found
        try{
            readFile(file_path);
        }catch (std::exception& e){
            scores.push_back(0);
        }


    }

    void HighScore::add(unsigned int score) {
        scores.push_back(score);
        //sort from high to low
        std::sort(scores.begin(), scores.end(), std::greater<>());

    }

    HighScore::~HighScore() {
        //save scores in file
        std::fstream score_file{"scoreboard"};
        for (int i=0; i<5; i++){
            if (scores.size() <= i){
                break;
            }
            score_file << scores[i];
            score_file << '\n';
        }
        score_file.close();

    }

    std::vector<unsigned int> HighScore::getScores() const {
        std::vector<unsigned int> out;

        for (int i=0; i<5; i++){

            if (scores.size() <= i){
                break;
            }

            out.push_back(scores[i]);
        }

        return out;
    }

    void HighScore::readFile(const std::string &file_path) {
        std::fstream score_file{file_path};

        if (!score_file.good()){
            throw std::invalid_argument{file_path};
        }

        std::string buffer;
        while (!score_file.eof()){
            char c = (char) score_file.get();

            if (c == '\n'){
                if (!buffer.empty()){
                    scores.push_back(std::stoi(buffer));
                    buffer = "";
                }

            }else{
                buffer += c;
            }


        }
        score_file.close();
        if (!buffer.empty() && buffer != "\377"){
            scores.push_back(std::stoi(buffer));
        }

    }

} // Logic