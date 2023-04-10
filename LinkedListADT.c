//<연결리스트 관리 프로그램>
//  LinkedList ADT
//
//  Created by 2020315756 곽인애.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 10

typedef struct node {
  char data;
  struct node *prev;
  struct node *next;
} Node;

Node *head = NULL;
Node *current = NULL;


void add(char data) {//추가 함수
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = head;

  if (head == NULL) {
    head = new_node;
    current = new_node;
  } else {
    head = new_node;
  }
}

void addTail(char data) {// 끝에 순서대로 추가
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->data = data;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
    current = new_node;
  } else {
    new_node->next = current->next;
    current->next = new_node;

    if (current != head && current->next == NULL) {
      current = head;
    } else {
      current = current->next;
    }
  }
}

void delete () {//현위치 값 삭제
  if (head == NULL) {
    printf("List is empty\n");
    return;
  }

  if (current == head) {
    head = head->next;
    free(current);
    current = head;
  } else {
    Node *temp = head;

    while (temp->next != current) {
      temp = temp->next;
    }

    temp->next = current->next;
    free(current);
    current = temp->next;
  }
}

void get_data() {//현위치의 data 출력
  if (head == NULL) {
    return;
  }

  printf("%c\n", current->data);
}

void replace(char ins) {//대체값으로 바꿈
  if (head == NULL) {

    return;
  }

  current->data = ins;
}

void traverse_front(int n) {//앞에서부터 이동
  if (head == NULL) {

    return;
  }

  if (n == 0) {
    current = head;
    return;
  }

  Node *temp = head;
  int i;

  for (i = 0; i < n - 1 && temp != NULL; i++) {
    temp = temp->next;
  }

  if (temp == NULL) {
    printf("Invalid index\n");
  } else {
    current = temp;
  }
}

void traverse_rear(int n) {//뒤에서부터 이동
  if (head == NULL) {

    return;
  }

  if (n == 0) {
    while (current->next != NULL) {
      current = current->next;
    }
    return;
  }

  Node *temp = head;
  int count = 0;

  while (temp != NULL) {
    temp = temp->next;
    count++;
  }

  if (n >= count) {
    current = temp;
  } else {
    temp = head;
    int i;

    for (i = 0; i < count - n - 1 && temp != NULL; i++) {
      temp = temp->next;
    }

    if (temp == NULL) {
      printf("Invalid index\n");
    } else {
      current = temp;
    }
  }
}

void clear() {//list 모든 값 삭제
  Node *temp;

  while (head != NULL) {
    temp = head;
    head = head->next;
    free(temp);
  }

  current = NULL;
}

void print() {//list 츨력
  Node *temp = head;

  while (temp != NULL) {
    printf("%c ", temp->data);
    temp = temp->next;
  }

  printf("\n");
}

void data_count() {//data 총 개수 출력
  Node *temp = head;
  int count = 0;

  while (temp != NULL) {
    count++;
    temp = temp->next;
  }

  printf("Number of nodes: %d\n", count);
}
int is_empty() {//비어있는지 아닌지 값 반환
  if (head == NULL) {
    return 1; // list is empty
  } else {
    return 0; // list is not empty
  }
}
void is_member(char data) {//특정 데이터 위치 출력
  if (head == NULL) {
    printf("List is empty\n");
    return;
  }

  Node *temp = head;
  int pos = 0;

  while (temp != NULL) {
    if (temp->data == data) {
      printf("%c is at position %d\n", data, pos + 1);
      return;
    }
    temp = temp->next;
    pos++;
  }

  printf("%c is not found in the list\n", data);
}
int get_current_position() {//나만의 기능 1- 현재 위치 반환
  if (head == NULL) {

    return -1;
  }

  int index = 0;
  Node *temp = head;

  while (temp != NULL) {
    if (temp == current) {
      return index;
    }
    temp = temp->next;
    index++;
  }

  return -1;
}
void reverse_list() {// 나만의 기능 2-역순으로 배열
  Node *prev_node = NULL;
  Node *next_node = NULL;
  current = head;
  while (current != NULL) {
    next_node = current->next;
    current->next = prev_node;
    prev_node = current;
    current = next_node;
  }
  head = prev_node;
}
void remove_duplicates() {//나만의 기능 3- 중복되는 값 제거
    if (head == NULL) return;

    Node* curr = head;
    while (curr != NULL) {
        Node* temp = curr;
        while (temp->next != NULL) {
            if (curr->data == temp->next->data) {
                Node* duplicate = temp->next;
                temp->next = temp->next->next;
                free(duplicate);
            } else {
                temp = temp->next;
            }
        }
        curr = curr->next;
    }
}

int main() {
  char command[MAX_COMMAND_LENGTH];
  int n;
  char c;

  while (1) {
    printf("Enter your command:");
    scanf("%s", command);
    for (int i = 0; i < strlen(command); i++) {
      if (command[i] == '<' && command[i + 1] == '+') {
        add(command[i + 2]);
        i += 2;
        traverse_front(0);
      }
      if (command[i] == '+') {
        addTail(command[i + 1]);
      } else if (command[i] == '-') {
        delete ();
      } else if (command[i] == 'G') {
        get_data();
      } else if (command[i] == '=') {
        replace(command[i + 1]);
      } else if (command[i] == '<') {
        int countN = 0;
        traverse_front(0);
        if (command[i + 1] == 'N') {

          for (int j = i + 1; j < strlen(command); j++) {
            countN++;
          }

          traverse_front(countN + 1);
        }
      } else if (command[i] == '>') {
        int countP = 0;
        traverse_rear(0);
        if (command[i + 1] == 'P') {

          for (int j = i + 1; j < strlen(command); j++) {
            countP++;
          }

          traverse_rear(countP);
        }
      } else if (command[0] == 'C') {
        clear();
      } else if (command[0] == 'L') {
        print();
      } else if (command[0] >= '0' && command[0] <= '9') {
        n = atoi(&command[0]);
        traverse_front(n);
        get_data();
      } else if (command[1] == '=') {
        n = atoi(&command[0]);
        c = command[2];
        traverse_front(n - 1);
        replace(c);
      } else if (command[0] == '#') {
        data_count();
      } else if (command[0] == 'E') {
        if (is_empty() == 1)
          printf("Empty\n");
        else
          printf("Not Empty");
      } else if (command[i] == '?') {
        is_member(command[i + 1]);
      }
        else if(command[i]=='^'){//나만의 기능 1- 현재 위치 반환
          printf("current position is %d\n",get_current_position()+1);
        }
        else if(command[i]=='$'){//나만의 기능 2-역순으로 배열
          reverse_list();
        }
        else if(command[i]=='%'){//나만의 기능 3- 중복되는 값 제거
          remove_duplicates();
        }
    }
    printf("Linked List:");
    print();
  }

  return 0;
}
