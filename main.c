/**
 * @file main.c
 * @brief Solution for the "Mobile Network Antenna Placement" problem.
 * * Problem Statement:
 * Given a set of n cities arranged linearly, each with a specific population,
 * determine the maximum population that can be covered by placing antennas.
 * Constraint: Antennas cannot be placed in adjacent cities.
 * * Approach: Bottom-Up Dynamic Programming.
 * The problem is equivalent to the "Maximum Weight Independent Set on a Path Graph".
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Reconstructs and prints the optimal antenna placement.
 * * @param dp The dynamic programming array containing optimal values.
 * @param population The array containing the population of each city.
 * @param n The total number of cities.
 */
void display_solution(int *dp, int *population, int n) {
    // Array to store the final decision for each city (1 = antenna placed, 0 = no antenna)
    int *is_selected = calloc((n + 1), sizeof(int));
    if (!is_selected) {
        perror("Memory allocation error");
        exit(1);
    }

    // Heuristic initialization from the lab notes: 
    // We optimistically assume city 1 is selected unless proven otherwise later.
    is_selected[1] = 1; 

    int i = n;
    while (i >= 2) {
        if (dp[i] == dp[i - 1]) {
            // Case 1: The optimal value is the same as the previous city.
            // This means we did NOT place an antenna at 'i'.
            is_selected[i] = 0;
            i--; // Move to the previous city
        } 
        else if (dp[i] == dp[i - 2] + population[i]) {
            // Case 2: The optimal value includes the population of city 'i'.
            // This means we placed an antenna at 'i'.
            is_selected[i] = 1;
            is_selected[i - 1] = 0; // Constraint: cannot have an antenna at i-1
            i -= 2; // Move back two steps
        }
    }

    printf("Selected cities for antenna placement:\n");
    for (int j = 1; j <= n; j++) {
        if (is_selected[j]) {
            printf("%d ", j);
        }
    }
    printf("\n");

    free(is_selected);
}

/**
 * @brief Solves the problem using Bottom-Up Dynamic Programming.
 * * Recurrence relation:
 * dp[i] = max(dp[i-1], population[i] + dp[i-2])
 * * @param population Array of populations (1-based index).
 * @param n Number of cities.
 */
void solve_dp(int *population, int n) {
    int *dp = calloc((n + 1), sizeof(int));
    if (!dp) {
        perror("Memory allocation error");
        exit(1);
    }

    // Base case: For the first city, the max population is just its own population.
    dp[1] = population[1];

    // Fill the DP table
    for (int i = 2; i <= n; i++) {
        int exclude_current = dp[i - 1];
        int include_current = population[i] + dp[i - 2];

        if (include_current > exclude_current) {
            dp[i] = include_current;
        } else {
            dp[i] = exclude_current;
        }
    }

    printf("=== DP Solution ===\n");
    printf("Maximum population covered: %d\n", dp[n]);
    
    display_solution(dp, population, n);
    
    free(dp);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    int n; // Number of cities
    if (fscanf(fp, "%d", &n) != 1) {
        fprintf(stderr, "Error reading number of cities.\n");
        fclose(fp);
        return 1;
    }

    // Allocate memory for n+1 integers (using 1-based indexing for convenience)
    int *population = malloc(sizeof(int) * (n + 1));
    if (!population) {
        perror("Memory allocation error");
        fclose(fp);
        return 1;
    }

    population[0] = 0; // Dummy value for index 0
    for (int i = 1; i <= n; i++) {
        if (fscanf(fp, "%d", &population[i]) != 1) {
            fprintf(stderr, "Error reading population for city %d.\n", i);
            free(population);
            fclose(fp);
            return 1;
        }
    }

    solve_dp(population, n);

    fclose(fp);
    free(population);
    return 0;
}
