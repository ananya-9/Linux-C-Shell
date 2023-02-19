#include"headers.h"

void overkill()
{
    for (int i = 1; i <= backgroundJob_count; i++)
    {
        kill(bjob[i].pid, 9);
    }
}