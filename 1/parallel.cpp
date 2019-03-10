// Example Program
// Optimizes code for maximum speed
#pragma optimize("2", on)
#include <stdio.h>
#include <omp.h>
#include <math.h>
// Adds an additional library so that timeGetTime() can be used
#pragma comment(lib, "winmm.lib")
const long int VERYBIG = 100000;
// ***********************************************************************
int main(void)
{
    // -----------------------------------------------------------------------
    // Output a start message
    printf("None Parallel Timings for %d iterations\n\n", VERYBIG);
    // repeat experiment several times
    omp_set_num_threads(6);
#pragma omp parallel
    {
        long int j, k, sum;
        double sumx, sumy, total;
        double starttime, elapsedtime;
        int id = omp_get_thread_num();
        // get starting time56 x CHAPTER 3 PARALLEL STUDIO XE FOR THE IMPATIENT
        starttime = omp_get_wtime();
        // reset check sum & running total
        sum = 0;
        total = 0.0;
        // Work Loop, do some work by looping VERYBIG times
        for (j = 0; j < VERYBIG; j++)
        {
            // increment check sum
            sum += 1;
            // Calculate first arithmetic series
            sumx = 0.0;
            for (k = 0; k < j; k++)
                sumx = sumx + (double)k;
            // Calculate second arithmetic series
            sumy = 0.0;
            for (k = j; k > 0; k--)
                sumy = sumy + (double)k;
            if (sumx > 0.0)
                total = total + 1.0 / sqrt(sumx);
            if (sumy > 0.0)
                total = total + 1.0 / sqrt(sumy);
        }
        // get ending time and use it to determine elapsed time
        elapsedtime = omp_get_wtime() - starttime;
        // report elapsed time
        printf("Time Elapsed %f mSecs Total = %lf Check Sum = %ld id=%d \n",
               elapsedtime, total, sum, id);
    }
    // return integer as required by function header

    return 0;
}
// **********************************************************************