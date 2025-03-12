#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** fullJustify(char ** words, int wordsSize, int maxWidth, int* returnSize) {
    char **result = (char **)malloc(sizeof(char *) * wordsSize);
    *returnSize = 0;
    
    int start = 0;  // Index of the first word in the current line.
    
    while (start < wordsSize) {
        int end = start;  // Index of the last word in the current line.
        int lineLength = 0;  // Length of the words and spaces in the current line.
        
        // Calculate the number of words and total length that can fit in the current line.
        while (end < wordsSize && lineLength + strlen(words[end]) + end - start <= maxWidth) {
            lineLength += strlen(words[end]);
            end++;
        }
        
        // Calculate the total number of spaces needed in the line.
        int totalSpaces = maxWidth - lineLength;
        
        // If it's the last line or only one word in the line, left-justify.
        if (end == wordsSize || end - start == 1) {
            result[*returnSize] = (char *)malloc(sizeof(char) * (maxWidth + 1));
            int idx = 0;
            for (int i = start; i < end; i++) {
                strcpy(result[*returnSize] + idx, words[i]);
                idx += strlen(words[i]);
                if (i != end - 1) {
                    result[*returnSize][idx++] = ' ';
                }
            }
            while (idx < maxWidth) {
                result[*returnSize][idx++] = ' ';
            }
            result[*returnSize][maxWidth] = '\0';
        } else {
            int spaceBetweenWords = totalSpaces / (end - start - 1);
            int extraSpaces = totalSpaces % (end - start - 1);
            
            result[*returnSize] = (char *)malloc(sizeof(char) * (maxWidth + 1));
            int idx = 0;
            for (int i = start; i < end; i++) {
                strcpy(result[*returnSize] + idx, words[i]);
                idx += strlen(words[i]);
                if (i != end - 1) {
                    int spaces = spaceBetweenWords + (extraSpaces > 0 ? 1 : 0);
                    extraSpaces--;
                    for (int j = 0; j < spaces; j++) {
                        result[*returnSize][idx++] = ' ';
                    }
                }
            }
            result[*returnSize][maxWidth] = '\0';
        }
        
        (*returnSize)++;
        start = end;
    }
    
    return result;
}

// Helper function to print the result
void printResult(char **result, int returnSize) {
    printf("[\n");
    for (int i = 0; i < returnSize; i++) {
        printf("   \"%s\",\n", result[i]);
    }
    printf("]\n");
}

int main() {
    // Example 1
    char *words1[] = {"This", "is", "an", "example", "of", "text", "justification."};
    int wordsSize1 = sizeof(words1) / sizeof(words1[0]);
    int maxWidth1 = 16;
    int returnSize1;
    char **result1 = fullJustify(words1, wordsSize1, maxWidth1, &returnSize1);
    printf("Input: words = [\"This\", \"is\", \"an\", \"example\", \"of\", \"text\", \"justification.\"], maxWidth = 16\n");
    printf("Output:\n");
    printResult(result1, returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        free(result1[i]);
    }
    free(result1);

    // Example 2
    char *words2[] = {"What","must","be","acknowledgment","shall","be"};
    int wordsSize2 = sizeof(words2) / sizeof(words2[0]);
    int maxWidth2 = 16;
    int returnSize2;
    char **result2 = fullJustify(words2, wordsSize2, maxWidth2, &returnSize2);
    printf("Input: words = [\"What\",\"must\",\"be\",\"acknowledgment\",\"shall\",\"be\"], maxWidth = 16\n");
    printf("Output:\n");
    printResult(result2, returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        free(result2[i]);
    }
    free(result2);

    // Example 3
    char *words3[] = {"Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"};
    int wordsSize3 = sizeof(words3) / sizeof(words3[0]);
    int maxWidth3 = 20;
    int returnSize3;
    char **result3 = fullJustify(words3, wordsSize3, maxWidth3, &returnSize3);
    printf("Input: words = [\"Science\",\"is\",\"what\",\"we\",\"understand\",\"well\",\"enough\",\"to\",\"explain\",\"to\",\"a\",\"computer.\",\"Art\",\"is\",\"everything\",\"else\",\"we\",\"do\"], maxWidth = 20\n");
    printf("Output:\n");
    printResult(result3, returnSize3);
    for (int i = 0; i < returnSize3; i++) {
        free(result3[i]);
    }
    free(result3);

    return 0;
}
