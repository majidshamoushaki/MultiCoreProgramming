// Example Program
// Optimizes code for maximum speed
#pragma optimize( "2", on )
#include <stdio.h>
#include <math.h>
#include <omp.h>
// Adds an additional library so that timeGetTime() can be used
#pragma comment(lib, "winmm.lib")
const long int VERYBIG = 100000;
// ***********************************************************************
#define num_thread 4
int main(void)
{
    int i;
    long int sum[num_thread], all_sum;
    double total[num_thread], total_sum;
    double starttime, elapsedtime;
    // -----------------------------------------------------------------------
    // Output a start message
    printf("None Parallel Timings for %d iterations\n\n", VERYBIG);
    // repeat experiment several times
    for (i = 0; i<6; i++)
    {
        // get starting time56 x CHAPTER 3 PARALLEL STUDIO XE FOR THE IMPATIENT
        starttime = omp_get_wtime();
        // reset check sum & running total
        all_sum = 0;
        // Work Loop, do some work by looping VERYBIG times
        total_sum = 0;
        omp_set_num_threads(num_thread);
        
#pragma omp parallel
        {
            int id = omp_get_thread_num();
            double sumx, sumy;
            long int j, k;
            for (j = id, total[id] = 0.0, sum[id] = 0; j<VERYBIG; j += num_thread)
            {
                // increment check sum
                sum[id] += 1;
                // Calculate first arithmetic series
                sumx = 0.0;
                for (k = 0; k<j; k++)
                    sumx = sumx + (double)k;
                // Calculate second arithmetic series
                sumy = 0.0;
                for (k = j; k>0; k--)
                    sumy = sumy + (double)k;
                if (sumx > 0.0)total[id] = total[id] + 1.0 / sqrt(sumx);
                if (sumy > 0.0)total[id] = total[id] + 1.0 / sqrt(sumy);
            }
        }
        
        for (int j = 0; j < num_thread; j++) {
            total_sum += total[j];
            all_sum += sum[j];
        }
        // get ending time and use it to determine elapsed time
        elapsedtime = omp_get_wtime() - starttime;
        // report elapsed time
        printf("Time Elapsed %f mSecs Total = %lf Check Sum = %ld \n",
               elapsedtime, total_sum, all_sum);
    }
    
    // return integer as required by function header
    return 0;
}
// **********************************************************************