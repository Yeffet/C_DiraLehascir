#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 7
#define LEN 7

// Typedef declaration
typedef char string[256];

//-----------------------------------------------------------------------------
// Check Neighbor Compatibility
// -----------------------------
//
// General : Checks if the current animal is compatible with its neighboring animal.
//
// Parameters :  
// nAnimal - Current animal (In).
// nNeighborAnimal - Animal in the neighbor's position (In).
//
// Return Value : 1 if compatible, 0 otherwise.
//-----------------------------------------------------------------------------
int CheckNeighborCapability(int nAnimal, int nNeighborAnimal) {
    if ((nAnimal == 1 && nNeighborAnimal == 2) ||
        (nAnimal == 2 && nNeighborAnimal == 1) ||
        (nAnimal == 4 && nNeighborAnimal == 3) ||
        (nAnimal == 3 && nNeighborAnimal == 4)) {
        return 0;
    }
    return 1;
}

//-----------------------------------------------------------------------------
// Check If Position is Valid
// ---------------------------
//
// General : Checks if a certain position in the matrix is valid for placing an animal.
//
// Parameters :  
// nAnimal - Animal to be placed (In).
// nMaxNeighbors - Maximum allowed neighbors (In).
// arrnHelpMat - Helper matrix to check neighboring animals (In).
// nRow, nCol - Position of the current cell (In).
//
// Return Value : 1 if valid, 0 if invalid.
//-----------------------------------------------------------------------------
int Check(int nAnimal, int nMaxNeighbors, int arrnHelpMat[12][9], int nRow, int nCol) {
    int nCount = 0;
    for (int nRowOffset = nRow - 1; nRowOffset <= nRow + 1; nRowOffset++) {
        for (int nColOffset = nCol - 1; nColOffset <= nCol + 1; nColOffset++) {
            if (arrnHelpMat[nRowOffset][nColOffset] != 0) {
                nCount++;
            }
            if (!CheckNeighborCapability(nAnimal, arrnHelpMat[nRowOffset][nColOffset])) {
                return 0;
            }
        }
    }
    return nCount <= nMaxNeighbors ? 1 : 0;
}

//-----------------------------------------------------------------------------
// Write Matrix to File
// --------------------
//
// General : Writes the current state of the matrix to a file.
//
// Parameters :  
// arrnMat - Matrix to write (In).
// pszFilename - Output file name (In).
//
// Return Value : None.
//-----------------------------------------------------------------------------
void WriteMatrixToFile(int arrnMat[12][9], const char* pszFilename) {
    FILE* fp = fopen(pszFilename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int nRow = 1; nRow < 10; nRow++) {
        for (int nCol = 1; nCol < 8; nCol++) {
            fprintf(fp, "%d ", arrnMat[nRow][nCol]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("Matrix written to %s successfully.\n", pszFilename);
}

//-----------------------------------------------------------------------------
// Enter Animals into Matrix
// --------------------------
//
// General : Reads animal data from the input file, attempts to place each animal
//           into a matrix, and writes the final matrix to the output file.
//
// Parameters :  
// pszInputFileName - Input file name (In).
//
// Return Value : None.
//-----------------------------------------------------------------------------
void Enter(const char* pszInputFileName) {
    FILE* fp = fopen(pszInputFileName, "r");
    if (fp == NULL) {
        printf("Error opening input file!\n");
        return;
    }

    int arrnMat[12][9] = { 0 }; // Initialize matrix with 0
    char szOutputFile[256];
    fgets(szOutputFile, sizeof(szOutputFile), fp);  // Read output file name
    szOutputFile[strcspn(szOutputFile, "\n")] = '\0';  // Remove newline

    int nAnimal, nMaxNeighbors;
    while (fscanf(fp, "%d %d", &nAnimal, &nMaxNeighbors) != EOF) {
        int bPlaced = 0;
        for (int nRow = 1; nRow < 11; nRow++) {
            for (int nCol = 1; nCol < 9; nCol++) {
                if (arrnMat[nRow][nCol] == 0 && Check(nAnimal, nMaxNeighbors, arrnMat, nRow, nCol)) {
                    arrnMat[nRow][nCol] = nAnimal;
                    bPlaced = 1;
                    break;
                }
            }
            if (bPlaced) {
                break;
            }
        }
        if (!bPlaced) {
            printf("Sorry, no space available for animal %d\n", nAnimal);
        }
    }
    fclose(fp);

    // Write the final matrix to the output file
    WriteMatrixToFile(arrnMat, szOutputFile);
}

//-----------------------------------------------------------------------------
// Main Function
// -------------
//
// General : Generates an input file with animal data, calls the Enter function,
//           and writes the matrix to an output file.
//
// Return Value : 0 on success.
//-----------------------------------------------------------------------------
void main() {
    // Create input file
    FILE* inputFile = fopen("Apartment1.txt", "w");
    if (inputFile == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(inputFile, "check.txt\n"); // Output file name
    fprintf(inputFile, "1 3\n");  // Chicken, 3 neighbors
    fprintf(inputFile, "2 4\n");  // Ant, 4 neighbors
    fprintf(inputFile, "5 2\n");  // Dove, 2 neighbors
    fprintf(inputFile, "2 1\n");  // Cat, 1 neighbor
    fprintf(inputFile, "4 3\n");  // Pig, 3 neighbors

    fclose(inputFile);
    // Process input file and write output
    Enter("Apartment1.txt");

}
