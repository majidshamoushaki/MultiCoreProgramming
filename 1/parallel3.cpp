// Example Program
// Optimizes code for maximum speed
#pragma optimize( "2", on )
#include <stdio.h>
#include <math.h>
#include <omp.h>
// Adds an additional library so that timeGetTime() can be used
#pragma comment(lib, "winmm.lib")
const long int VERYBIG = 100000;
#define num_thread 4
// ***********************************************************************
int main(void)
{
    int i;
    long int sum;
    double total;
    double starttime, elapsedtime;
    // -----------------------------------------------------------------------
    // Output a start message
    printf("None Parallel Timings for %ld iterations\n\n", VERYBIG);
    // repeat experiment several times
    for (i = 0; i<6; i++)
    {
        // get starting time56 x CHAPTER 3 PARALLEL STUDIO XE FOR THE IMPATIENT
        starttime = omp_get_wtime();
        // reset check sum & running total
        sum = 0;
        total = 0.0;
        // Work Loop, do some work by looping VERYBIG times
        omp_set_num_threads(num_thread);
#pragma omp parallel
        {
            long int j, k;
            double sumx, sumy;
#pragma omp for
            for (j = 0; j<VERYBIG; j++)
            {
                // increment check sum
#pragma omp critical
                sum += 1;
                // Calculate first arithmetic series
                sumx = 0.0;
                for (k = 0; k<j; k++)
                    sumx = sumx + (double)k;
                // Calculate second arithmetic series
                sumy = 0.0;
                for (k = j; k>0; k--)
                    sumy = sumy + (double)k;
//#pragma omp critical
                {
                if (sumx > 0.0)
#pragma omp critical
                    total = total + 1.0 / sqrt(sumx);
                if (sumy > 0.0)
#pragma omp critical
                    total = total + 1.0 / sqrt(sumy);
                }
            }
        }
        // get ending time and use it to determine elapsed time
        elapsedtime = omp_get_wtime() - starttime;
        // report elapsed time
        printf("Time Elapsed %f mSecs Total = %lf Check Sum = %ld \n",
               elapsedtime, total, sum);
    }
    // return integer as required by function header
    return 0;
}
// **********************************************************************