#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to calculate letter frequency in the ciphertext
void calculateFrequency(char *ciphertext, int frequency[26]) {
    int i;
    for(i = 0; i < strlen(ciphertext); i++) {
        if(isalpha(ciphertext[i])) {
            frequency[tolower(ciphertext[i]) - 'a']++;
        }
    }
}

// Function to print the top 'count' possible plaintexts
void printPossiblePlaintexts(char *ciphertext, int frequency[26], int count) {
    char mapping[26];
    int i, j, max_index;
    int max_frequency;
    for(i = 0; i < 26; i++) {
        max_frequency = 0;
        for(j = 0; j < 26; j++) {
            if(frequency[j] > max_frequency) {
                max_frequency = frequency[j];
                max_index = j;
            }
        }
        frequency[max_index] = -1; // Mark the frequency as processed
        mapping[max_index] = 'a' + i; // Map the letter to the alphabet
    }

    printf("Top %d possible plaintexts:\n", count);
    for(i = 0; i < count; i++) {
        for(j = 0; j < strlen(ciphertext); j++) {
            if(isalpha(ciphertext[j])) {
                if(isupper(ciphertext[j])) {
                    printf("%c", toupper(mapping[ciphertext[j] - 'A']));
                } else {
                    printf("%c", mapping[ciphertext[j] - 'a']);
                }
            } else {
                printf("%c", ciphertext[j]); // Non-alphabetic characters remain unchanged
            }
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[1000];
    int frequency[26] = {0}; // Frequency array to store occurrences of each letter

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove trailing newline if present

    calculateFrequency(ciphertext, frequency);
    printPossiblePlaintexts(ciphertext, frequency, 10); // Print top 10 possible plaintexts

    return 0;
}
