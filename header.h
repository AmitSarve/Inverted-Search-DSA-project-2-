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
    char word[100];
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
int update_database(mainnode_t *hash[], file_node **head);

int insert_backup_word(mainnode_t *hash[],char *word,char *filename,int wordcount,int index);
int add_file_to_list(file_node **head, char *filename);
int is_file_present(file_node *head, char *filename);
int is_file_indexed(mainnode_t *hash[], char *filename);

int validate_backup(char *backup_file);