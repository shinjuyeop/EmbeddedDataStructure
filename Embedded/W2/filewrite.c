#include <stdio.h>

void main() {
    FILE* fp;
    int score;

    // 파일 쓰기 모드로 열기
    fp = fopen("C:\\Users\\shinj\\Desktop\\3-1\\EmbeddedDataStructure\\score.txt", "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return;
    }

    // 점수 입력 및 파일에 저장
    while (1) {
        printf("Input score: ");
        scanf("%d", &score);
        if (score < 0) break;
        fprintf(fp, "%d\n", score);
    }
    fclose(fp);
}
