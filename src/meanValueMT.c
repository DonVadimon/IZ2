#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/mman.h>

struct FileMapping
{
    int fd;
    size_t fsize;
    unsigned char *dataPtr;
};

struct ThreadArgs
{
    unsigned char *left;
    unsigned char *right;
    unsigned char *last_ch;
    int COORDINATES;
};

struct meanValues
{
    pthread_mutex_t mutex;
    double *vals;
};

struct meanValues meanVals = {PTHREAD_MUTEX_INITIALIZER, NULL};

void *thread_routine(void *arg);

double power(double x, double n);

int ReverseNum(int x);

int meanValueMT(const char *path, double **dest, const int _COORDINATES)
{
    //memory common data for answers
    meanVals.vals = (double *)malloc(sizeof(double) * _COORDINATES);
    for (int i = 0; i < _COORDINATES; i++)
    {
        meanVals.vals[i] = 0;
    }

    //mmap
    int fd = open(path, O_RDONLY, 0);

    assert(fd >= 0 && "FILE NE OTKRILSYA");

    struct stat st;

    assert(fstat(fd, &st) >= 0 && "NE POLUCHIL STATISTIKU");

    size_t fsize = (size_t)st.st_size;

    unsigned char *dataPtr = (unsigned char *)mmap(NULL, fsize,
                                                   PROT_READ,
                                                   MAP_PRIVATE,
                                                   fd, 0);
    assert(dataPtr != MAP_FAILED && "MAP FAILED");

    struct FileMapping *mapping = (struct FileMapping *)malloc(sizeof(struct FileMapping));
    if (mapping == NULL)
    {
        printf("\nfileMappingCreate - malloc failed, file name = %s\n", path);
        munmap(dataPtr, fsize);
        close(fd);
        abort();
    }

    int shift = 1;
    int vec_count = 0;
    int p = 0;
    for (int i = 0; dataPtr[i] != ' ' && dataPtr[i] != '\n'; i++)
    {
        int rank = power(10.0, (double)p);
        int symb = (int)((dataPtr[i]) - '0');
        vec_count += symb * rank;
        p++;
        shift++;
    }

    vec_count = ReverseNum(vec_count);

    mapping->fd = fd;
    mapping->fsize = fsize - shift * sizeof(unsigned char);
    mapping->dataPtr = dataPtr + shift;
    //threads
    const int N = 5;
    pthread_t threadIds[N];

    //inicialize data for borders

    struct ThreadArgs **threadArgs = (struct ThreadArgs **)malloc(sizeof(struct ThreadArgs *) * N);
    printf("\n========= TEST TEST TEST TEST TEST =========\n");
    for (int i = 0; i < N; i++)
    {
        threadArgs[i] = malloc(sizeof(struct ThreadArgs));
        threadArgs[i]->left = malloc(sizeof(unsigned char));
        threadArgs[i]->right = malloc(sizeof(unsigned char));
        threadArgs[i]->last_ch = malloc(sizeof(unsigned char));
        threadArgs[i]->COORDINATES = _COORDINATES;
    }

    //set borders
    for (int i = 0; i < N; i++)
    {
        threadArgs[i]->left = (mapping->dataPtr + i * (mapping->fsize / N));
        threadArgs[i]->right = mapping->dataPtr + (i == N - 1 ? (mapping->fsize + 1) : ((i + 1) * (mapping->fsize / N)));
        threadArgs[i]->last_ch = (mapping->dataPtr + mapping->fsize);
    }

    //start threads
    for (int i = 0; i < N; i++)
    {
        int errflag = pthread_create(&threadIds[i], NULL, thread_routine, (void *)(threadArgs[i]));
        if (errflag != 0)
        {
            printf("\nTHREAD CREATION ERROR\n");
            abort();
        }
    }
    for (int i = 0; i < N; i++)
    {
        int errflag = pthread_join(threadIds[i], NULL);
        if (errflag != 0)
        {
            printf("\nTHREAD JOIN ERROR\n");
            abort();
        }
    }

    //divideing for vector count
    printf("\n");
    for (int i = 0; i < _COORDINATES; i++)
    {
        meanVals.vals[i] /= vec_count;
    }

    printf("\n");
    for (int i = 0; i < _COORDINATES; i++)
    {
        (*dest)[i] = meanVals.vals[i];
    }

    return 1;
}

void *thread_routine(void *args)
{
    pthread_mutex_t *mutex = &meanVals.mutex;
    struct ThreadArgs copy = *(struct ThreadArgs *)args;

    int errflag = 0;
    int j = 0;

    int num = 0;
    int p = 0;
    int rank = 0;
    int symb = 0;
    for (unsigned char *symb_p = copy.left; symb_p < copy.right; symb_p++)
    {
        //printf("%c", *symb_p);
        if (*symb_p != ' ' && *symb_p != '\n' && symb_p != copy.last_ch)
        {
            rank = power(10.0, (double)p);
            //printf("%d\n", rank);
            symb = ((int)(*symb_p) - '0');
            num += symb * rank;
            p++;
            continue;
        }
        p = 0;
        num = ReverseNum(num);

        printf("\nNUM = %d\n", num);

        // lock mutex before value change
        errflag = pthread_mutex_lock(mutex);
        // check if pthread_mutex_lock call was successful
        if (errflag != 0)
        {
            printf("\nError in thread_routin\n");
            return NULL;
        }

        

        meanVals.vals[j % copy.COORDINATES] += num;

        // unlock mutex after value change
        errflag = pthread_mutex_unlock(mutex);
        // check if pthread_mutex_unlock call was successful
        if (errflag != 0)
        {
            printf("\nERROR AFTER MUTEX UNLOCK\n");
        }
        num = 0;
        j++;
    }

    return NULL;
}

double power(double x, double n)
{
    if (n == 0)
        return 1;
    if (n < 0)
        return power(1.0 / x, -n);
    return x * power(x, n - 1);
}

int ReverseNum(int x)
{
    int y = 0;
    while (x)
    {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}