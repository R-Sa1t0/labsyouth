#include <stdio.h>
#include <string.h>

int main(){
    {
        puts(
            "(1) Edit\n"
            "(2) Compile\n"
            "(3) Run"
        );
    }
    {
        printf("%p\n", "Hello");
        printf("%d\n", "Hello"[0]);
        printf("%d\n", "Hello"[1]);
        printf("%d\n", "Hello"[2]);
        printf("%d\n", "Hello"[3]);
        printf("%d\n", "Hello"[4]);
        printf("%d\n", "Hello"[5]);
    }
    {
        char s[]={"Hello"};
        for (int i=0; s[i]; i++) printf("%c %d\n", s[i], s[i]);
    }
    {
        //char s[100];
        //scanf("%s", &s);
        //printf("%s\n", &s);
    }
    {
        //char s[100];
        //fgets(s, sizeof s, stdin);
        //puts(s);
    }
    {
        char s[]={"String Length"};
        printf("%lu\n", strlen(s));
        
        int i;
        for (i=0; s[i]; i++);
        printf("%d\n", i);
    }
    {
        char s[]={"Srting Copy"};
        
        char t[100];
        strcpy(t, s);
        puts(t);

        char u[100];
        int i;
        for (i=0; s[i]; i++) u[i]=s[i];
        u[i]='\0';
        puts(u);
    }
    {
        char s[100], u[100];
        fgets(s, sizeof s, stdin);
        fgets(u, sizeof u, stdin);
        
        int j;
        puts(j<0 ? "<" : j>0 ? ">" : "==");

        int i;
        for (i=0; s[i] && s[i]==u[i]; i++);
        puts(s[i]<u[i] ? "<" : s[i]>u[i] ? ">" : "=="); 
    }
}