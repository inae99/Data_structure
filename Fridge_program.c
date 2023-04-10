#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 냉장고에 보관할 음식 정보를 담는 구조체
struct food {
  char name[20];
  char expiration_date[20];
  char brand[20];
};

// 냉장고 구조체 정의
struct fridge {
  int capacity;
  int num_foods;
  struct food *foods;
};

// 냉장고 생성 함수
struct fridge *create_fridge(int capacity) {
  struct fridge *fr = (struct fridge *)malloc(sizeof(struct fridge));
  fr->capacity = capacity;
  fr->num_foods = 0;
  fr->foods = (struct food *)malloc(capacity * sizeof(struct food));
  return fr;
}

// 음식 추가 함수
int food_insert(struct fridge *fr) {
  if (fr->num_foods >= fr->capacity) {
    printf("냉장고가 가득 찼습니다.\n");
    return 0;
  }

  printf("음식의 정보를 입력해주세요.\n");
  printf("이름: ");
  char name[20];
  scanf("%s", name);
  printf("유통기한 ex)2023-04-07 :");
  char expiration_date[20];
  scanf("%s", expiration_date);
  printf("브랜드: ");
  char brand[20];
  scanf("%s", brand);

  struct food new_food;
  strcpy(new_food.name, name);
  strcpy(new_food.expiration_date, expiration_date);
  strcpy(new_food.brand, brand);
  fr->foods[fr->num_foods] = new_food;
  fr->num_foods++;

  // 유통기한을 기준으로 정렬
  for (int i = 0; i < fr->num_foods; i++) {
    for (int j = i + 1; j < fr->num_foods; j++) {
      if (strcmp(fr->foods[i].expiration_date, fr->foods[j].expiration_date) >
          0) {
        struct food temp = fr->foods[i];
        fr->foods[i] = fr->foods[j];
        fr->foods[j] = temp;
      }
    }
  }
  return 1;
}

// 냉장고 정보 출력 함수
void print_fridge(struct fridge *fr) {
  printf("냉장고 용량: %d\n", fr->capacity);
  printf("현재 음식 개수: %d\n", fr->num_foods);
  printf("음식 정보:\n");
  for (int i = 0; i < fr->num_foods; i++) {
    printf("이름: %s / 유통기한: %s / 브랜드: %s\n", fr->foods[i].name,
           fr->foods[i].expiration_date, fr->foods[i].brand);
  }
}
void clear_fridge(struct fridge *fr) {
  free(fr->foods);
  fr->foods = (struct food *)malloc(fr->capacity * sizeof(struct food));
  fr->num_foods = 0;
  printf("냉장고를 비웠습니다.\n");
}
void search_fridge(struct fridge *fr) {
  char name[20];
  char brand[20];
  printf("찾을 음식 이름을 입력하시오:");
  scanf("%s", name);
  printf("찾을 음식의 브랜드 이름을 입력하시오:");
  scanf("%s", brand);

  for (int i = 0; i < fr->num_foods; i++) {
    if (strcmp(fr->foods[i].brand, brand) && strcmp(fr->foods[i].name, name)) {
      printf("%s 의 %s 제품은 유통기한이 %s 입니다.\n 냉장고 안에 %d칸에 "
             "존재합니다.\n",
             brand, name, fr->foods[i].expiration_date, i + 1);
      return;
    }
  }
  printf("해당 제품은 없습니다. 다시 검색해주세요.\n");
}
void refresh(struct fridge *fr) {
  time_t current_time = time(NULL); // 현재 날짜.
  struct tm *tm_current_time = localtime(&current_time);
  for (int i = 0; i < fr->num_foods; i++) {
    struct food curr_food = fr->foods[i];
    struct tm exp_time = {0};
    int year, month, day;
    sscanf(curr_food.expiration_date, "%d-%d-%d", &year, &month,
           &day); // 유통기한을 year, month, day 변수로 파싱
    exp_time.tm_year =
        year - 1900; // struct tm의 year 필드는 1900년부터 시작하므로,
                     // 유통기한에서 1900을 빼준 값을 대입
    exp_time.tm_mon = month - 1; // struct tm의 month 필드는 0부터 시작하므로,
                                 // 유통기한에서 1을 빼준 값을 대입
    exp_time.tm_mday = day; // struct tm의 day 필드에 유통기한의 day 값을 대입
    if (difftime(mktime(&exp_time), mktime(tm_current_time)) < 0) {
      // 유통기한이 지난 경우, 해당 음식을 리스트에서 삭제
      for (int j = i; j < fr->num_foods - 1; j++) {
        fr->foods[j] = fr->foods[j + 1];
      }
      fr->num_foods--;
      i--; // 삭제 후 인덱스를 하나 줄인다.
    }
  }
}
// 원하는 음식 삭제 기능
void delete_food(struct fridge *fr) {
    char name[20];
    printf("삭제할 음식의 이름을 입력하세요: ");
    scanf("%s", name);

    // 해당 이름의 음식 찾기
    int index = -1;
    for (int i = 0; i < fr->num_foods; i++) {
        if (strcmp(fr->foods[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    // 해당 이름의 음식이 존재하지 않는 경우
    if (index == -1) {
        printf("입력한 이름과 일치하는 음식이 냉장고에 없습니다.\n");
        return;
    }

    // 해당 인덱스에 있는 음식 삭제
    for (int i = index; i < fr->num_foods - 1; i++) {
        fr->foods[i] = fr->foods[i + 1];
    }
    fr->num_foods--;

    printf("음식 \"%s\" 삭제 완료.\n", name);
}


void check(struct fridge *fr) {
  char food_name[20];
  printf("유통기한을 알아볼 음식의 이름을 입력하세요. : ");
  scanf("%s", food_name);
  for (int i = 0; i < fr->num_foods; i++) {
    if (strcmp(fr->foods[i].name, food_name) == 0) {
      printf("유통기한 : %s\n", fr->foods[i].expiration_date);
      return;
    }
  }
}

int main() {
  int insert_n;
  // 냉장고 생성
  struct fridge *fr = create_fridge(5);
  while (1) {
    int cmd;
    printf("=====냉장고 프로그램=====\n\n 1: 음식 추가\n 2: 음식삭제\n 3: "
           "냉장고에 저장된 음식들 출력\n 4: 유통기한 체크\n 5: 유통기한 지난 "
           "음식 삭제\n 6: 특정음식 찾기\n 7: 냉장고 비우기\n 8: 냉장고 "
           "프로그램 종료\n\n 실행할 명령의 번호를 입력하시오:");
    scanf("%d", &cmd);
    if (cmd == 1) {
      printf("냉장고에 넣고 싶은 음식의 개수를 입력해주세요:");
      scanf("%d", &insert_n);
      // 음식 추가
      for (int i = 0; i < insert_n; i++) {
        food_insert(fr);
      }
    } else if (cmd == 2) {
      // 음식 삭제
      delete_food(fr);
    } else if (cmd == 3) {
      // 냉장고 정보 출력
      print_fridge(fr);
    } else if (cmd == 4) {

      //유통기한 check
      check(fr);
    } else if (cmd == 5) {
      // 날짜는 오늘을 기준으로 유통기한 지난 음식 삭제
      refresh(fr);
    } else if (cmd == 6) {
      search_fridge(fr);
    } else if (cmd == 7) {
      clear_fridge(fr);
    }

    else if (cmd == 8) {
      return 0;
    } else {
      printf("번호를 잘못 눌렀습니다.\n");
    }
  }
  // 냉장고 메모리 해제
  free(fr->foods);
  free(fr);

  return 0;
}
