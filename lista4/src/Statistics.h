#ifndef STATISTICS_H
#define STATISTICS_H


#include <ctime>

class Statistics {
public:
    static int insertAmount;
    static int loadAmount;
    static int deleteAmount;
    static int findAmount;
    static int minAmount;
    static int maxAmount;
    static int successorAmount;
    static int inorderAmount;

    static clock_t startTimer;
    static clock_t stopTimer;

    static int compareAmount;
};

#endif //STATISTICS_H
