#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigen>
#include <iostream>
#include <matplotlibcpp.h>
#include <random>

#define STD_VEC_EIGEN(mat) std::vector<double>(mat.data(), mat.data() + mat.rows() * mat.cols())
Eigen::VectorXd polyfit(const Eigen::VectorXd &xVec, const Eigen::VectorXd &yVec, int poly_order)
{
    assert(poly_order > 0);
    assert(xVec.size() > poly_order);
    assert(xVec.size() == yVec.size());

    Eigen::MatrixXd A(xVec.size(), poly_order + 1);
    Eigen::VectorXd B(xVec.size());

    for (int i = 0; i < xVec.size(); ++i)
    {
        const double x = xVec(i);
        const double y = yVec(i);

        double x_pow_k = 1.0;

        for (int k = 0; k <= poly_order; ++k)
        {
            A(i, k) = x_pow_k;
            x_pow_k *= x;
        }

        B(i) = y;
    }

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::VectorXd x = svd.solve(B);

    return x;
}

double evaluatePolynomial(const Eigen::VectorXd &coef, double x, double noise = 0.000)
{
    int degree = coef.size() - 1;
    double result = 0.0;

    for (int i = degree; i >= 0; i--)
    {
        result = result * x + coef(i);
    }
    if (abs(noise) > 0.0001)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());

        // 创建一个正态分布对象
        double mean = 0.0;   // 均值
        double stddev = 5.0; // 标准差
        std::normal_distribution<double> distribution(mean, stddev);
        result += distribution(gen);
    }

    return result;
}

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));
    Eigen::VectorXd coef_gt(7);
    coef_gt << 0.0, 1.0, 2.0, 3.0, 4.4, 5.0, 6.89324234;
    Eigen::VectorXd x;
    x.setLinSpaced(1000, 0., 10.);
    std::vector<double> y, y_gt;
    for (int i = 0; i < x.size(); i++)
    {
        y.push_back(evaluatePolynomial(coef_gt, x(i), 0.1));
        y_gt.push_back(evaluatePolynomial(coef_gt, x(i)));
    }

    Eigen::Map<Eigen::VectorXd> y_eigen(y.data(), y.size());

    auto coef = polyfit(x, y_eigen, 6);
    std::cout << coef << std::endl;

    std::vector<double> y_est;
    std::vector<double> err;
    for (int i = 0; i < x.size(); i++)
    {
        y_est.push_back(evaluatePolynomial(coef, x(i)));
        err.push_back((y_est[i] - y_gt[i]));
    }
    matplotlibcpp::subplot(1, 2, 1);
    matplotlibcpp::scatter(STD_VEC_EIGEN(x), y, 2);
    matplotlibcpp::plot(STD_VEC_EIGEN(x), y_est, "r");
    matplotlibcpp::subplot(1, 2, 2);
    matplotlibcpp::plot(STD_VEC_EIGEN(x), err, "g");
    matplotlibcpp::show();
    return 0;
}
