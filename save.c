#include "main.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void hash(int data, char str[257]) {
    char charset[] = "0BoNCmE9AOM1L8WcKnlJbdTz6XVeaP2fYkgIhyU7Zx3iq5wRsvHGru4jSQtpFD";
    int charset_len = 62;
    unsigned int seed = (unsigned int)data;
    seed = seed ^ (seed << 13);
    seed = seed ^ (seed >> 17);
    seed = seed ^ (seed << 5);
    for (int i = 0; i < 256; i++) {
        seed = seed * 1664525 + 1013904223;
        str[i] = charset[seed % charset_len];
    }
    int d0 = (data / 10000) % 10;
    int d1 = (data / 1000) % 10;
    int d2 = (data / 100) % 10;
    int d3 = (data / 10) % 10;
    int d4 = data % 10;
    str[12] = '0' + d0;
    str[47] = '0' + d1;
    str[89] = '0' + d2;
    str[133] = '0' + d3;
    str[197] = '0' + d4;
    str[256] = '\0';
}

int reverse_hash(char hash_data[]) {
    char tmp[257];
    for (int i = 0; i <= 99999; i++) {
        hash(i, tmp);
        if (strcmp(tmp, hash_data) == 0) {
            return i;
        }
    }
    return 0;
}

void insertion_sort(int data[], int n) {
    int i, j;
    int tmp;
    for (i = 1; i < n; i++) {
        j = i;
        while (j >= 1 && data[j - 1] < data[j]) {
            tmp = data[j];
            data[j] = data[j - 1];
            data[j - 1] = tmp;
            j--;
        }
    }
}

void save_score(void) {
    int data[10];
    char hash_data[257];
    FILE *fp;
    int score = player.score;
    read_score(data);
    if (data[9] < score) {
        data[9] = score;
    }
    insertion_sort(data, 10);
    fp = fopen("data.txt", "w");
    if (fp == NULL) {
        exit(1);
    }
    for (int i = 0; i < 10; i++) {
        hash(data[i], hash_data);
        fprintf(fp, "%s\n", hash_data);
    }
    fclose(fp);
}

void read_score(int data[]) {
    FILE *fp;
    char hash_data[257];
    fp = fopen("data.txt", "r");
    if (fp != NULL) {
        for (int i = 0; i < 10; i++) {
            if (fscanf(fp, "%s", hash_data) == 1) {
                data[i] = reverse_hash(hash_data);
            } else {
                data[i] = 0;
            }
        }
        fclose(fp);
    } else {
        for (int i = 0; i < 10; i++) {
            data[i] = 0;
        }
    }
}

