#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define SUCCESS 0
#define FAILURE 1


typedef struct subnode
{
    char filename[25];
    int wordcount;
    struct subnode*link;
}subnode;

typedef struct mainnode
{
    char word[25];
    int filecount;
    subnode*sublink;
    struct mainnode*link;
}mainnode_t;

typedef struct file_node
{
    char filename[25];
    struct file_node *link;

} file_node;

int validate(int argc,char*argv[],file_node**);
int insert_at_last(file_node**,int ,char**);
int creat_database(file_node*,mainnode_t*[]);

int insert_in_database(char*,char*,mainnode_t*[]);
int insert_subnode(mainnode_t *mainnode, char *filename);

int display_database(mainnode_t*hash[]);
int save_database(mainnode_t *hash[],char*);

int search_database(mainnode_t *hash[]);