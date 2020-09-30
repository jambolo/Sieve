#include <stdio.h>
#include <vector>

static void printSyntaxAndExit(int e);
static void removeComposites(std::vector<bool>& sieve);
static void printResults(std::vector<bool> const& sieve);

static int verbosity = 0;

int main(int argc, char** argv)
{
    size_t limit = 0;

    if (argc > 3)
        printSyntaxAndExit(1);

    while (--argc > 0)
    {
        ++argv;
        if (strcmp(argv[0], "-v") == 0)
            verbosity = 1;
        else if (strcmp(argv[0], "-vv") == 0)
            verbosity = 2;
        else
        {
            if (sscanf(argv[0], "%llu", &limit) < 1)
                printSyntaxAndExit(1);
        }
    }

    if (limit == 0)
        limit = 4294967296ULL; // 2^32

    if (verbosity > 0)
        fprintf(stderr, "Finding all primes less than %llu.\n", limit);

    std::vector<bool> sieve(limit, true);    // Set all initially to prime

    // Find the prime numbers between 2 and limit-1 (inclusive) using a Sieve of Eratosthenes
    removeComposites(sieve);

    // Print the results as json

    printResults(sieve);
}

static void printSyntaxAndExit(int e)
{
    fprintf(stderr, "Syntax: Sieve [-v|-vv] <limit>\n");
    exit(e);
}

static void removeComposites(std::vector<bool>& sieve)
{
    size_t limit = sieve.size();

    // 0 and 1 are not prime
    sieve[0] = false;
    sieve[1] = false;

    // Optimization: no need to remove multiples of primes greater than sqrt(limit) because they have already been removed
    // by smaller primes.
    size_t maxFactor = size_t(sqrt(double(limit)));

    for (size_t p = 2; p <= maxFactor; ++p)
    {
        // Skip to the next prime
        while (!sieve[p])
            ++p;

        // Set all multiples of p to composite
        // Optimization: start at p*p because smaller composites have already been removed by smaller primes.
        for (size_t i = p * p; i < limit; i += p)
        {
            sieve[i] = false;
        }
    }
}

static void printResults(std::vector<bool> const& sieve)
{
    size_t limit = sieve.size();

    printf("[\n");
    printf("           2");
    int count = 1;
    for (size_t i = 3; i < limit; ++i)
    {
        if (sieve[i])
        {
            if (++count % 8 != 1)
                printf(", %10llu", (uint64_t)i);
            else
                printf(",\n  %10llu", (uint64_t)i);

            if (verbosity > 1)
            {
                if (count % 1000 == 0)
                    fprintf(stderr, "%d primes at %llu.\n", count, i);
            }
        }
    }

    printf("\n]\n");
    if (verbosity > 0)
        fprintf(stderr, "%d primes less than %llu.\n", count, limit);
}
