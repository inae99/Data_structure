//<배열 관리 프로그램>
//  Array ADT
//
//  Created by 2020315756 곽인애.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

int size = 0;
int position = -1;
char array[30];

void create(int len) { //배열 생성 ADT
  for (int i = 0; i < len; i++) {
    array[i] = ' ';
  }
}
void insert(char array[], char data) { //삽입 ADT
  size++;
  position++;
  if (size > 30) {
    printf("Error: 배열이 가득 찼습니다.\n");
    return;
  }
  for (int i = size; i > position; i--) {
    array[i] = array[i - 1];
  }
  array[position] = data;
}
void insert_at(char array[], int index,
               char data) { //위치 지정 삽입 ADT- 나만의 기능1
  size++;
  position = index;
  if (size > 30) {
    printf("Error: 배열이 가득 찼습니다.\n");
    return;
  }
  if (index < 0 || index > size) {
    printf("Error: 잘못된 위치입니다.\n");
    return;
  }
  for (int i = size; i > index; i--) {
    array[i] = array[i - 1];
  }
  array[index] = data;
}

void traverse_front(char array[], int count) { //제일 앞에서부터 시작 ADT
  position = count;
}
void traverse_rear(char array[], int count) { //제일 뒤부터 시작 ADT
  position = size - 1 - count;
}
void delete (char array[]) { //삭제 ADT
  if (size == 0) {
    printf("Error: 배열이 비어있습니다.\n");
    return;
  }
  for (int i = position; i < size - 1; i++) {
    array[i] = array[i + 1];
  }
  array[size - 1] = ' ';
  size--;
  if (position == size) {
    position = 0;
  }
}
char get_data(char array[]) { //데이터 반환 ADT

  return (array[position]);
}
void replace(char array[], char new_data) { //입력값으로 대체 ADT
  array[position] = new_data;
}
void empty(char array[]) {              //배열 비우기 ADT
  for (int i = 0; i < size; i++) {
    array[i] = ' ';
  }
  size = 0;
  position = -1;
}
void move(char array[], int new_position) {     //이동 ADT
  char element;
  printf("Movement started\n");
  printf("Position: %d to New Position:%d\n", position, new_position);
  if (new_position >= size || new_position <= (-size)) {
    printf("Error: 범위를 벗어난 이동입니다.\n");
    return;
  }
  element = array[position];
  printf("move %c to index %d\n", element, new_position);
  if (position == new_position)
    printf("위치가 그대로 입니다.");
  else if (position < new_position) {
    for (int i = position; i < new_position; i++) {
      array[i] = array[i + 1];
    }
    array[new_position] = element;
  } else if (position > new_position) {
    for (int i = position; i > new_position; i--) {
      array[i] = array[i - 1];
    }
    array[new_position] = element;
  }

  position = new_position;
}

int data_count(char array[]) {  //데이터 개수 세는 ADT
  int count_d=0;
  for (int i = 0; i < strlen(array); i++) {
    if (array[i] != ' ')count_d++;
  }
  return count_d;
}
void search(char array[], char find){// 검색 ADT - 나만의 기능2
  int i=0;
  printf("Searching Start!\n");
  printf("Searching '%c'\n",find);
  for(i=0;i<size;i++)
    {
     if(array[i]==find){
       printf("%c is in index %d\n",find,i);
      break;
     }
    }
  position=i;
}
void print(char array[]) {              //출력 ADT
  printf("%s\n", array);
}
void print_at(char array[],int index){  //특정 위치 값 출력 ADT - 나만의 기능3
  printf("in %d, there is %c\n",index,array[index]);
}

int main() {

  int current_position = 0;
  int countN = 0;
  int countP = 0;

  char array[30];
  create(30); // 베열 생성

  while (1) {
    char cmd[60];
    printf("=====Array ADT=====\n");
    printf("1.'+' to insert (ex)+a+b+c+d), if you want to input index where to "
           "input, enter like this: ex) +a2\n");
    printf("2.'<' means front and 'N'means one move from the front\n");
    printf("3.'>'means rear and 'P'means one move from rear\n");
    printf("4.'-' means delete\n");
    printf("5.'>-'means delete the last\n");
    printf("6.'@'means returning the data from the position now\n");
    printf("7.'='means replace (ex)=h is replacing the element to h\n");
    printf("8.'E'means empty array\n");
    printf("9.'M'means move (ex) M0 means move to 0 positon, MP means move "
           "backward one, MN means move forward one\n");
    printf("10. S means search   ex) Sa found 'a' and return where it is. \n");
    printf("11.'L'means print and if you want to print a char in a distict index, input index number  ex)L2 \n\n");
    printf("12. Q to quit\n\n");
    printf("Enter your command:");

    scanf("%s", cmd);
    int length;
    length = strlen(cmd);
    printf("%s\n", cmd);

    for (int i = 0; i < length; i++) {
      if (cmd[i] == '+') {
        if ((int)cmd[i + 2] - 48 > 0 && (int)cmd[i + 2] - 48 < size) {
          insert_at(array, (int)cmd[i + 2] - 48, cmd[i + 1]);
        }
        else{
          insert(array, cmd[i + 1]);
        }
        
      } else if (cmd[i] == '<') {
        position = 0;
        if (cmd[i + 1] == 'N') {

          for (int j = i + 1; j < length; j++) {
            if (cmd[j] == 'N')
              countN++;
          }
          traverse_front(array, countN);
        }

      } else if (cmd[i] == '>') {

        position = size - 1;
        if (cmd[i + 1] == 'P') {

          for (int j = i + 1; j < length; j++) {
            if (cmd[j] == 'P')
              countP++;
          }
          traverse_rear(array, countP);
        }
      } else if (cmd[i] == '-') {
        delete (array);
      }

      else if (cmd[i] == '@') {
        printf("Return: %c\n", get_data(array));
      } else if (cmd[i] == '=') {
        replace(array, cmd[i + 1]);
      } else if (cmd[i] == 'E') {
        empty(array);
      } else if (cmd[i] == 'M') {
        if ((int)(cmd[i + 1]) - 48 >= 0 &&
            (int)(cmd[i + 1]) - 48 < (data_count(array))) {
          move(array, (int)cmd[i + 1] - 48);
        } else if (cmd[i + 1] == 'n') {
          move(array, size-1);
        } else if (cmd[i + 1] == 'N') {

          for (int j = i + 1; j < length; j++) {
            if (cmd[j] == 'N')
              countN++;
          }
          move(array, position + countN);
        } else if (cmd[i + 1] == 'P') {
          for (int j = i + 1; j < length; j++) {
            if (cmd[j] == 'P')
              countP++;
          }
          move(array, position-countP);
        }
      }
      else if(cmd[i]=='S'){
          search(array,cmd[i+1]);
        }
       else if (cmd[i] == 'L') {
        if((int)cmd[i+1]-48>=0&&(int)cmd[i+1]-48<size)
        {
          print_at(array,(int)cmd[i+1]-48);
        }
        else print(array);
      }
    }
    printf("Array:%s\n", array);
    printf("Size of Array:%d\n", size);
    printf("Position:%d\n", position);
  }

  return 0;
}
