#include <iostream>
#include <vector>

class Adaline
{

private:
    double eta;
    int epochs;
    std::vector<double> error;
    std::vector<std::vector<double>> weights;
public:
    Adaline(double et, int ep);
    void fit(std::vector<std::vector<double>> X, std::vector<std::vector<double>> y);
    std::vector<std::vector<double>> decide(std::vector<std::vector<double>>);
    std::vector<std::vector<double>> predict(std::vector<std::vector<double>> X);
    void addBias(std::vector<std::vector<double>> &X);
    void plot();

};

Adaline::Adaline(double et, int ep)
{
    eta = et;
    epochs = ep;
    error;
    std::srand(std::time(NULL));
}

void Adaline::fit(std::vector<std::vector<double>> X, std::vector<std::vector<double>> y)
{
    addBias(X);
    for ( int i = 0; i < X[0].size(); i++ )
    {
        std::vector<double> temp(1);
        temp[0] = (double)(std::rand()) / RAND_MAX;
        weights.push_back(temp);
    }

    for( int i = 0; i < epochs; i++ ) 
    {
        std::vector<std::vector<double>> out = matMult(X, weights);
        std::vector<std::vector<double>> errors = matMin(y, out);
        out = matMult(matTrans(X), errors);
        out = matMult(out, eta);
        weights = matAdd(weights, out);
        error.push_back(sumVec(matSq(errors)));

    }


}

void Adaline::addBias(std::vector<std::vector<double>> &X)
{
    for( int i = 0; i < X.size(); i++ )
    {
        X[i].push_back(1);
    }
}

std::vector<std::vector<double>> Adaline::predict(std::vector<std::vector<double>> X)
{
    for( int i = 0; i < X.size(); i++ )
    {
        for( int j = 0; j < X[0].size(); j++ )
        {
            if(X[i][j] >= 0)
                X[i][j] = 1;
            else
                X[i][j] = -1;
        }
    }
    return X;
}

std::vector<std::vector<double>> Adaline::decide(std::vector<std::vector<double>> X)
{
    addBias(X);
    std::vector<std::vector<double>> temp = matMult(X, weights);
    return predict(temp);
}


void Adaline::plot()
{
	try
	{
		int end;
		Gnuplot gp("lines");
		gp.set_style("impulses").plot_x(error, "error-plot");
		std::cout << "plotting, please write anything and press enter" << std::endl;
		std::cin >> end;
	}
	catch(GnuplotException ge)
	{
		std::cout << ge.what() << std::endl;
	}
}


void load_file(std::string name, std::vector<std::vector<double>> &data, std::vector<std::string> &labels, std::string rejected = "Iris-virginica")
{
    std::ifstream myfile(name);
    std::string line;
    std::string delimiter = ",";
    if(myfile.is_open())
    {
        while(getline (myfile, line))
        {
            size_t pos = 0;
            std::string token;
            std::vector<double> temp;
            while ((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                temp.push_back(std::stod(token));
                line.erase(0, pos + delimiter.length());
            }
            if (line != rejected)
            {
                data.push_back(temp);
                labels.push_back(line);
            }
        }
    }
    else
    {
	    std::cout << "no file" << std::endl;
	    throw(1);
    }
    myfile.close();
}

void shuffle_data(std::vector<std::vector<double>> &data, std::vector<std::vector<double>> &labels)
{
    auto seed = unsigned(std::time(NULL));
    std::srand(seed);
    std::random_shuffle(data.begin(), data.end());
    std::srand(seed);
    std::random_shuffle(labels.begin(), labels.end());
}


void train_test_split(std::vector<std::vector<double>> data, std::vector<std::vector<double>> labels, double size_ratio, std::vector<std::vector<double>> &train_x, std::vector<std::vector<double>> &train_y, std::vector<std::vector<double>> &test_x, std::vector<std::vector<double>> &test_y)
{
    shuffle_data(data, labels);
    if(size_ratio < 0 || size_ratio > 1)
        throw 1;
    int border = size_ratio * data.size();
    for(int i = 0; i < border; i++)
    {
        train_x.push_back(data[i]);
        train_y.push_back(labels[i]);
    }

    for(int i = border; i < data.size(); i++)
    {
        test_x.push_back(data[i]);
        test_y.push_back(labels[i]);
    }
}


