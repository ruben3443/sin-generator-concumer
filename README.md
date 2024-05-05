# sin-generator-consumer

The idea is to generate a sinusoidal signal (f=50Hz, RMS=240V, samples=360 per period) until the process is killed by ctrl+c. Then, the consumer will calculate the RMS of the signal. Both generator and consumer will be related by shared memory.

## Generator
 - It executes continuously, printing the calculated sin() value for each sample, until it is manually stopped with ctrl+c.
 - It generates a "shmid.txt" file where it stores the ID of the shared memory segment that the consumer will read.
 - It calculates continuously the sin() value for each sample and, besides printing it in the console, it stores the value in the shared memory.
 - This value (float) is been overwritten continuously, so there is just the value of one sample at a time.

## Consumer
 - It opens the "shmid.txt" file, previously created by the generator, to extract the ID of the shared memory segment to read.
 - Although the generated signal only has 360 samples per period, the consumer will read 50 times 360 samples (18000 samples in total). This is because the generator and the consumer are not synchronized, so although the generator processes the 360 samples for each period, it is possible that the consumer doesn't read them all. The more samples the consumer reads, the more accurate the result will be.
 - When it finishes reading all the samples and processing the result, the consumer prints it in the console.

## Makefile
 - "all" option to generate both generator and consumer executables.
 - "generator" and ""consumer" options to generate each executable individually.
 - "clean" option to delete the generated files.
