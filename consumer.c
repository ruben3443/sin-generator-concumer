#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    FILE *shmid_file;
    shmid_file = fopen("./shmid.txt", "r");
    int shmid;
    fscanf (shmid_file, "%d", &shmid);  
    fclose(shmid_file);

    // The original sin() signal has 360 samples per period, but the consumer is not fully synchronized
    //     with the generator, so it doesn't get all the samples from a single period. That's why we get
    //     and approximate result each time we execute the consumer.
    //     The more samples the consumer gets, the more accurate the result is. That's why we are
    //     getting 50 times 360.
    int samples = 360*50;

    float rms = 0; // RMS = sqrt of the squared samples sum divided by the number of samples
    float squared_sum=0;
    float mean_square=0;

    for(size_t i=0; i<samples; i++)
    {
        float* shmptr = (float *)shmat(shmid, NULL, 0);
        float shared_value = *shmptr;
        squared_sum += pow(shared_value,2);
        shmdt(shmptr);
    }

    mean_square=squared_sum/samples;
    rms = sqrt(mean_square);

    printf("RMS --> %.2f\n", rms);

    return 0;
}