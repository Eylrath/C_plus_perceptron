#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>
#include"gnuplot_i.hpp"
#include"Matrix.h"
#include"Adaline.h"

std::vector<std::vector<std::vector<double>>> split_test_train(std::vector<std::vector<double>> data, std::vector<std::string> labels, double ratio);

int main()
{

    std::vector<std::vector<double>> data, x_train, x_test, y_test, y_train;
    std::vector<std::string> labels;
    load_file("iris.data", data, labels);
    std::vector<std::vector<double>> y = convert(labels);
    double rat = 0.5, score = 0;
    train_test_split(data, y, rat, x_train, y_train, x_test, y_test);

    std::cout << "train data: " << std::endl;
    for(int i = 0; i < x_train.size(); i ++)
    {
        std::cout << y_train[i][0] << ": ";
        for(int j = 0; j < x_train[0].size(); j++)
            std::cout << std::setw(10) << x_train[i][j];
        std::cout << std::endl;
    }
    Adaline Ad(0.0001, 1000);


    Ad.fit(x_train, y_train);
    std::vector<std::vector<double>> out = Ad.decide(x_test);

    std::cout << "predicted labels " << std::endl; 

    int good_ans = 0;
    for(int i = 0; i < out.size(); i ++)
    {
        std::cout << i << ": predicted: " <<(int) out[i][0] << ", desired: " << y_test[i][0] << std::endl;
        if(out[i][0] == y_test[i][0])
            good_ans ++;

    }
    score = (good_ans * 1.0) / out.size();
    std::cout << "score=" << score << std::endl;
    Ad.plot();

    return 0;
}

