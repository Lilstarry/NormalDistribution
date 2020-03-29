#include <iostream>
#include <random>
#include <cmath>

class Gen {
public:
    Gen(double mean, double deviation, std::default_random_engine& generator)
        : m_distribution(std::normal_distribution<double>(mean, deviation))
        , m_generator(generator)
        {}

    double getNumber() { return m_distribution(m_generator); }

private:
    std::normal_distribution<double> m_distribution;
    std::default_random_engine m_generator;
};

int main()
{
    const double width = 150;
    const double height = 60;
    const double m = 0;
    const double xDeviation = 60;
    const double yDeviation = 30;
    const int bombsPerAttempt = 6;

    const double xMetersFromCenter = width / 2;
    const double yMetersFromCenter = height / 2;
    std::default_random_engine generator;

    auto xGen = Gen(m, xDeviation, generator);
    auto yGen = Gen(m, yDeviation, generator);

    std::cout << "Press Ctrl+C to close the program...\n";
    while(true) {
        int rollsNumber;
        std::cout << "Enter rolls number:\n";
        std::cin >> rollsNumber;
        if(!std::cin.good()) {
            std::cout << "Input data is incorrect.\n";
            return 0;
        }

        int totalHits = 0;

        for(int i = 0; i < rollsNumber; ++i) {
            for(int j = 0; j < bombsPerAttempt; ++j) {
                if(fabs(xGen.getNumber()) > xMetersFromCenter)
                    continue;

                if(fabs(yGen.getNumber()) > yMetersFromCenter)
                    continue;

                totalHits++;
            }
        }
        std::cout << "Average hits: "
                  << static_cast<double>(totalHits) / rollsNumber
                  << std::endl << std::endl;
    }
}
