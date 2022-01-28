#include<map>
#include<vector>
std::vector<std::vector<double>> matMult(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
    if( B.size() != A[0].size() )
        throw 1;

    std::vector<std::vector<double>> C(A.size());
    for( int m = 0; m < A.size(); m++ )
    {
        std::vector<double> temp(B[0].size());
        for( int n = 0; n <B[0].size(); n++ )
        {
            double sum = 0;
            for( int i = 0; i < A[0].size(); i++ )
            {
                sum +=  A[m][i] * B[i][n];
            }
            temp[n] = sum;
        }
        C[m] = temp;

    }
    return C;

}
std::vector<std::vector<double>> matTrans(std::vector<std::vector<double>> A)
{
    std::vector<std::vector<double>> B;
    for ( int i = 0; i < A[0].size(); i++ )
    {
        std::vector<double> temp;
        for( int j = 0; j < A.size(); j++ )
        {
            temp.push_back(A[j][i]);
        }
        B.push_back(temp);
    }
    return B;
}

std::vector<std::vector<double>> matMin(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
    if( A.size() != B.size() || A[0].size() != B[0].size() )
        throw 1;
    for( int i = 0; i < A.size(); i ++ )
    {
        for( int j = 0 ; j < A[0].size(); j++ )
        {
            A[i][j] = A[i][j] - B[i][j];
        }
    }
    return A;
}

std::vector<std::vector<double>> matAdd(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B)
{
    if( A.size() != B.size() || A[0].size() != B[0].size() )
        throw 1;
    for( int i = 0; i < A.size(); i ++ )
    {
        for( int j = 0 ; j < A[0].size(); j++ )
        {
            A[i][j] = A[i][j] + B[i][j];
        }
    }
    return A;
}

void print_mat(std::vector<std::vector<double>> C)
{
    std::cout << std::endl;
    for( int i = 0; i < C.size(); i++ )
    {
        for( int j = 0; j < C[0].size(); j++ )
            std::cout << std::setw(10) << C[i][j];
        std::cout << std::endl;
    }
}

void print_mat(std::vector<double> C)
{
    std::cout << std::endl;
    for( int i = 0; i < C.size(); i++ )
    {
        std::cout <<  C[i] << std::endl;
    }
}

std::vector<std::vector<double>> matMult(std::vector<std::vector<double>> A, double b)
{
    for( int i = 0; i < A.size(); i++ )
        for( int j = 0; j < A[0].size(); j++ )
            A[i][j] = A[i][j] * b;
    return A;
}


std::vector<std::vector<double>> convert(std::vector<std::string> labels, std::string rejected = "virginica")
{
    std::map<std::string, int> unique_val;
    int lab_i = -1;
    for(std::string s : labels)
    {
        if( s == rejected ) continue;
        if( unique_val.find(s) == unique_val.end() )
        {
            unique_val[s] = lab_i;
            lab_i  = 1;
        }

    }
    std::vector<std::vector<double>> result(labels.size());
    for( int i = 0; i < labels.size(); i++ )
    {
       if( labels[i] == rejected ) continue;
       result[i].push_back(unique_val[labels[i]]);
    }
    return result;

}

std::vector<std::vector<double>> matSq(std::vector<std::vector<double>> A)
{
    for( int i = 0; i < A.size(); i++ )
    {
        A[i][0] *= A[i][0];
    }
    return A;
}

double sumVec(std::vector<std::vector<double>> A)
{
    double sum = 0;
    for( int i = 0; i < A.size(); i++ )
    {
        sum += A[i][0];
    }
    return sum;
}
