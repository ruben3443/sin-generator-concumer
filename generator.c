#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <sys/ipc.h>
#include <sys/shm.h>

float get_sin(float amplitude, int frequency, float time, float phase_shift, float vertical_shift)
{
    // y = A * sin (2*pi*f*x - C) + D
        // A --> amplitude
        // f --> frequency in Hz
        // C --> phase shift in rad
        // D --> vertical shift in rad
    return amplitude * sin(2*M_PI*frequency*time - phase_shift) + vertical_shift;
}

int main()
{
    float y = 0;

    int shmid=shmget(IPC_PRIVATE, sizeof(float), IPC_CREAT | 0666);
    FILE *shmid_file;
    shmid_file = fopen("./shmid.txt", "w+");
    fprintf(shmid_file, "%d", shmid);
    fclose(shmid_file);

    int samples = 360;
    float amplitude = 240 * sqrt(2); // A = RMS * sqrt(2)
    int frequency = 50;
    float phase_shift = 0;
    float vertical_shift = 0;
    float time_between_samples = (1.0/frequency)/samples;
    float time = 0;

    while(true)
    {
        y = get_sin(amplitude, frequency, time, phase_shift, vertical_shift);
        printf("Current sin() value --> %.2f rad\n", y);

        float* shmptr = (float*)shmat(shmid, NULL, 0);
        *shmptr=y;
        shmdt(shmptr);
        
        time+=time_between_samples;
    }

    return 0;
}