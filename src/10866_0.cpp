#include <stdio.h>
#include <string.h>

int deck[2000000];
int num, start = 1000000, end = 1000000;

void push_front(int k){
  start--;
  deck[start] = k;
}

void push_back(int k){
  deck[end] = k;
  end++;
}

void pop_front(){
  
  if(start == end && deck[start] == 0)
    printf("-1\n");
    
  else{
    printf("%d\n", deck[start]);
    deck[start] = 0;
    start++;
  } 
}

void pop_back(){
  
  if(start == end && deck[start] == 0)
    printf("-1\n");
    
  else{
    end--;
    printf("%d\n", deck[end]);
    deck[end] = 0;
  } 
}

void size(){
  
  if(start == end && deck[start] == 0)
    printf("0\n");
    
  else if(start == end)
    printf("1\n");
    
  else
    printf("%d\n", end - start);
}

void empty(){
  
  if(start == end && deck[start] == 0)
    printf("1\n");
    
  else
    printf("0\n");
}

void front(){
  
  if(start == end && deck[start] == 0)
    printf("-1\n");

  else
    printf("%d\n", deck[start]);
}

void back(){
  if(start == end && deck[start] == 0)
    printf("-1\n");

  else if(start == end)
    printf("%d\n", deck[end]);

  else
    printf("%d\n", deck[end-1]);
}


int main(void) {
  
  int i, n;

  char command[15];
  
  scanf("%d",&n);
  
  for(i=0;i<n;i++){
    scanf("%s",command);
    
    if (strcmp(command, "push_front") == 0){  
      scanf("%d", &num);
      push_front(num);
    }
    
    if (strcmp(command, "push_back") == 0){  
      scanf("%d", &num);
      push_back(num);
    }

    if (strcmp(command, "pop_front") == 0)
      pop_front();

    if (strcmp(command, "pop_back") == 0)
      pop_back();

    if (strcmp(command, "size") == 0)
      size();
    
    if (strcmp(command, "empty") == 0)
      empty();

    if (strcmp(command, "front") == 0)
      front();

    if (strcmp(command, "back") == 0)
      back();
  }
} 