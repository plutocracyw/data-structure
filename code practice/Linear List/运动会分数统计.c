#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_NAME 20
#define MAX_ATHLETES 1000
#define MAX_SCHOOLS 20

typedef struct {
    char name[MAX_NAME];
    int schoolid;
    int itemid;
    int score;
    int rank;
} Athlete;

typedef struct {
    char name[MAX_NAME];
    int male_count;
    int female_count;
    int total_score;
    int rank;
} SchoolScore;

Athlete athletes[MAX_ATHLETES];
SchoolScore schools[MAX_SCHOOLS + 1];

int main(){
    SetConsoleOutputCP(65001);

    int n, m, w;
    printf("请输入学校数n、男子项目数m、女子项目数w： ");
    scanf("%d %d %d", &n, &m, &w);

    int athelete_count = 0;

    for (int i = 1; i <= n;i++){
        schools[i].male_count = 0;
        schools[i].female_count = 0;
        schools[i].total_score = 0;
        schools[i].rank = 0;
    }

    for (int itemid = 1; itemid <= 3; itemid++){
        int isTop5;
        if(itemid % 2 == 1){
            isTop5 = 1;
            printf("\n项目%d(取前五名)\n", itemid);
        } else {
            isTop5 = 0;
            printf("\n项目%d(取前三名)\n", itemid);
        }

        int rankNum = isTop5 ? 5 : 3;
        int isFemaleItem = (itemid > m);

        for (int rank = 1; rank <= rankNum; rank++){
            Athlete ath;
            ath.itemid = itemid;
            ath.rank = rank;
            printf("请输入第%d名的姓名、学校编号、成绩：", rank);
            scanf("%s %d ", ath.name, &ath.schoolid);

            if(isTop5){
                int scores[6] = {0,7,5,3,2,1};
                ath.score = scores[rank];
            } else {
                ath.score=(rank==1)?5:((rank==2)?3:1);
            }

            athletes[athelete_count++] = ath;

            if(isFemaleItem){
                schools[ath.schoolid].female_count += ath.score;
            } else {
                schools[ath.schoolid].male_count+= ath.score;
            }
        }
    }

    for(int i = 1; i <= n; i++){
        schools[i].total_score = schools[i].male_count + schools[i].female_count;
    }

    printf("\n========学校总分排名========\n");
    printf("学校编号\t学校名称\t男子分数\t女子分数\t总分\n");
    for(int i = 1; i <= n; i++){
        printf("%d\t%s\t%d\t%d\t%d\n", i, schools[i].name, schools[i].male_count, schools[i].   female_count, schools[i].total_score);
    }

    printf("\n========各学校成绩单========\n");
    for(int i = 1; i <= n; i++){
        printf("\n学校编号：%d 学校名称：%s\n", i, schools[i].name);
        printf("项目编号\t名次\t姓名\t成绩\n");
        for(int j = 0; j < athelete_count; j++){
            if(athletes[j].schoolid == i){
                printf("%d\t%d\t%s\t%d\n", athletes[j].itemid, athletes[j].rank, athletes[j].name, athletes[j].score);
            }
        }
    }

    return 0;
}