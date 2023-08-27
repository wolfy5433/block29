#include "FineGrainedQueue.h"

int main()
{
    FineGrainedQueue fgq;
    fgq.addValue(43);
    fgq.addValue(77);
    fgq.addValue(18);
    fgq.addValue(66);
    fgq.addValue(96);
    fgq.addValue(51);
    fgq.addValue(3);
    fgq.show();
    fgq.insertIntoMiddle(158, 5);
    fgq.show();
    fgq.insertIntoMiddle(158, 10);
    fgq.show();
    fgq.remove(23);
    fgq.show();
}
