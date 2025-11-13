#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "lotto.txt"
#define MAX_LINE_LENGTH 1024

int is_number_in_lotto(int lotto_nums[], int num) {
    for (int i = 0; i < 7; i++) {
        if (lotto_nums[i] == num) {
            return 1;
        }
    }
    return 0;
}

void check_lotto_file(int user_nums[], int num_count) {
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    int winning_count = 0;
    
    printf("您的中獎號碼為: %02d %02d %02d\n", user_nums[0], user_nums[1], user_nums[2]);
    printf("以下為中獎彩卷:\n");
    
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        if (strstr(line, "March") != NULL || strstr(line, "September") != NULL || strstr(line, "April") != NULL) {
            char date_info[MAX_LINE_LENGTH];
            strcpy(date_info, line);
            if (fgets(line, MAX_LINE_LENGTH, fp) == NULL) break;
            if (line[0] == '[' && line[2] == ']') {
                int list_id;
                int lotto_nums[7];
                char *token = strtok(line, "[]:");
                if (token) {
                    list_id = atoi(token);
                    for (int i = 0; i < 7; i++) {
                        token = strtok(NULL, " \n");
                        if (token) {
                            lotto_nums[i] = atoi(token);
                        } else {
                            break;
                        }
                    }
                    int match_count = 0;
                    for (int i = 0; i < num_count; i++) {
                        if (is_number_in_lotto(lotto_nums, user_nums[i])) {
                            match_count++;
                        }
                    }
                    if (match_count == num_count) {
                        winning_count++;
                        printf("售出時間: %s [", date_info);
                        date_info[strcspn(date_info, "\n")] = 0; 
                        printf("%d]:", list_id);
                        for (int i = 0; i < 7; i++) {
                             printf(" %02d", lotto_nums[i]);
                        }
                        printf("\n");
                    }
                }
            }
        }
    }

    if (winning_count == 0) {
        printf("-> 遺憾! 您輸入的號碼在檔案中沒有完全匹配的彩券。\n");
    }
    fclose(fp);
}

int main() {
    int user_nums[3];
    int num_count = 3;
    printf("請輸入中獎號碼三個 (用空格分隔): ");
    if (scanf("%d %d %d", &user_nums[0], &user_nums[1], &user_nums[2]) != 3) {
        printf("🚨 輸入錯誤。請輸入三個整數。\n");
        return 1;
    }
    printf("輸入中獎號碼為: %02d %02d %02d\n", user_nums[0], user_nums[1], user_nums[2]);
    check_lotto_file(user_nums, num_count);
    return 0;
}
