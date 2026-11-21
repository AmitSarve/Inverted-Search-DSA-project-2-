#include"header.h"

int validate(int argc,char*argv[],file_node**head)
{
    if(argc < 2)
    {
        return FAILURE;
    }

    int i=1;
    while(i!=argc)
    {
        char*ch=strrchr(argv[i],'.');

        if(ch == NULL || strcmp(ch,".txt") != 0 )
        {
            printf("%s is not a txt file\n",argv[i]);
            i++;
            continue;
        }
        FILE*fp=fopen(argv[i],"r");
        if(fp==NULL)
        {
            printf("file not opened succesfully");
            i++;
            continue;
        }
        char c=fgetc(fp);
        
        if(c==EOF)
        {
            printf("%s is empty \n",argv[i]);
            fclose(fp);
            i++;
            continue;
            
        }
        fclose(fp);

        file_node*temp=*head;
        int found=0;
        while(temp!=NULL)
        {
            if(strcmp(temp->filename,argv[i])==0)
            {
                found=1;
                break;
            }
            temp=temp->link;
        }
        if(found==1)
        {
            printf("%s is duplicate \n",argv[i]);
            i++;
            continue;
        }

        //insert at last 
        if( insert_at_last(head,i,argv) == FAILURE)
        {
            return FAILURE;
        }

        i++;
    }
    return SUCCESS;
}
int insert_at_last(file_node**head,int i,char*argv[])
{
    file_node*newnode=malloc(sizeof(file_node));
        if(newnode==NULL)
        {
            return FAILURE;
        }
        //initilize struct member 
        strcpy(newnode->filename,argv[i]);
        newnode->link=NULL;
    if(*head==NULL)
    {
        *head=newnode;
        return SUCCESS;

    }
    else{
        file_node*temp=*head;
        while(temp->link!=NULL)
        {

            temp=temp->link;
        }
        temp->link=newnode;
    }
    return SUCCESS;
}
int creat_database(file_node*file_head,mainnode_t*hash_table[])
{
    file_node*temp=file_head;
    while(temp != NULL)
    {
        FILE*fp=fopen(temp->filename,"r");
        if(fp==NULL)
        {
            printf("File not open successfully \n");
            temp=temp->link;
            continue;
        }
        char word[25];
        while(fscanf(fp,"%s",word) == 1)
        {
           if( insert_in_database(word,temp->filename,hash_table)==FAILURE)
           {
            fclose(fp);
            return FAILURE;
           }

        }
        fclose(fp);
        temp=temp->link;

    }
    return SUCCESS;

}

int insert_in_database(char *word ,char* filename ,mainnode_t*hash[])
{
    int index;
    if(isalpha(word[0]))
    {
        index=tolower(word[0])-'a';
    }
    else
    {
        index=26;
    }

    mainnode_t*temp=hash[index];
    //search word in mainnode
    while(temp!=NULL)
    {
        if(strcmp(temp->word,word)==0)
        {
            //call subnode;
            return insert_subnode(temp,filename);
        }
        temp=temp->link;
    }

    //word not exits
    mainnode_t*newnode=malloc(sizeof(mainnode_t));
    if(newnode==NULL)
    {
        return FAILURE;
    }
    strcpy(newnode->word,word);
    newnode->filecount=0;
    newnode->sublink=NULL;
    newnode->link=NULL;
    // Create subnode for new word
    if (insert_subnode(newnode, filename) == FAILURE)
    {
        free(newnode);
        return FAILURE;
    }
//insert in mainnode
    newnode->link=hash[index];
    hash[index]=newnode;
return SUCCESS;

}
int insert_subnode(mainnode_t *mainnode, char *filename)
{
    subnode *temp = mainnode->sublink;

    // Check filename already exists
    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            temp->wordcount++;
            return SUCCESS;
        }

        temp = temp->link;
    }

    // Create new subnode
    subnode *newnode = malloc(sizeof(subnode));

    if (newnode == NULL)
    {
        return FAILURE;
    }

    strcpy(newnode->filename, filename);
    newnode->wordcount = 1;
    newnode->link = mainnode->sublink;

    mainnode->sublink = newnode;

    mainnode->filecount++;

    return SUCCESS;
}

int display_database(mainnode_t*hash[])
{
    for(int i=0;i<=26;i++)
    {
       mainnode_t*temp=hash[i];
       if(temp==NULL)
       {
        continue;
       }

       while(temp!=NULL)
       {
            printf("%s \t %d \t ",temp->word,temp->filecount);
        
            subnode*temp_sub=temp->sublink;
            while(temp_sub !=NULL)
            {
                printf("%s \t %d \n",temp_sub->filename,temp_sub->wordcount);
                temp_sub=temp_sub->link;
            }
            temp=temp->link;
        }
    }
    return SUCCESS;
}
int save_database(mainnode_t *hash[],char*backup_file)
{
    FILE *fp = fopen(backup_file, "w");

    if (fp == NULL)
    {
        printf("File not opened successfully\n");
        return FAILURE;
    }

    // Traverse hash table
    for (int i = 0; i < 27; i++)
    {
        mainnode_t *temp = hash[i];

        while (temp != NULL)
        {
            // Write main node details
            fprintf(fp, "#%d;", i);
            fprintf(fp, "%s;", temp->word);
            fprintf(fp, "%d;", temp->filecount);

            // Traverse subnode list
            subnode *sub = temp->sublink;

            while (sub != NULL)
            {
                fprintf(fp, "%s;", sub->filename);
                fprintf(fp, "%d;", sub->wordcount);

                sub = sub->link;
            }

            fprintf(fp, "#\n");

            temp = temp->link;
        }
    }

    fclose(fp);
    return SUCCESS;
}

int search_database(mainnode_t *hash[])
{
    char word[25];

    printf("Enter the word to search: ");
    scanf("%s", word);

   
    int index;

    char ch = word[0];

    if (isalpha(ch))
    {
        index = tolower(ch) - 'a';
    }
    else
    {
        index = 26;
    }

    // Search main node
    mainnode_t *temp = hash[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            printf("\nWord found: %s\n", temp->word);
            printf("File count: %d\n", temp->filecount);

            // Traverse subnode
            subnode *sub = temp->sublink;
            while (sub != NULL)
            {
                printf("Filename: %s\t", sub->filename);
                printf("Word count: %d\n", sub->wordcount);

                sub = sub->link;
            }
           return SUCCESS;
        }
        temp = temp->link;
    }

    printf("Word not found\n");

    return FAILURE;
}
int insert_backup_word(mainnode_t *hash[], char *word,char *filename, int wordcount, int index)
{
    mainnode_t *main_temp = hash[index];
    mainnode_t *new_main;
    subnode *sub_temp;
    subnode *new_sub;

    // Check whether word already exists
    while (main_temp != NULL)
    {
        if (strcmp(main_temp->word, word) == 0)
        {
            // Check filename in subnode list
            sub_temp = main_temp->sublink;

            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->filename, filename) == 0)
                {
                    sub_temp->wordcount += wordcount;
                    return SUCCESS;
                }

                sub_temp = sub_temp->link;
            }

            // Filename not found, create new subnode
            new_sub = malloc(sizeof(subnode));

            if (new_sub == NULL)
                return FAILURE;

            strcpy(new_sub->filename, filename);
            new_sub->wordcount = wordcount;

            new_sub->link = main_temp->sublink;
            main_temp->sublink = new_sub;

            main_temp->filecount++;

            return SUCCESS;
        }

        main_temp = main_temp->link;
    }

    // Word does not exist, create mainnode
    new_main = malloc(sizeof(mainnode_t));

    if (new_main == NULL)
        return FAILURE;

    strcpy(new_main->word, word);
    new_main->filecount = 1;
    new_main->sublink = NULL;

    // Create subnode
    new_sub = malloc(sizeof(subnode));

    if (new_sub == NULL)
    {
        free(new_main);
        return FAILURE;
    }

    strcpy(new_sub->filename, filename);
    new_sub->wordcount = wordcount;
    new_sub->link = NULL;

    new_main->sublink = new_sub;

    // Insert mainnode into hash table
    new_main->link = hash[index];
    hash[index] = new_main;
}
int is_file_indexed(mainnode_t *hash[], char *filename)
{
    mainnode_t *main_temp;
    subnode *sub_temp;

    for (int i = 0; i < 27; i++)
    {
        main_temp = hash[i];

        while (main_temp != NULL)
        {
            sub_temp = main_temp->sublink;

            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->filename, filename) == 0)
                {
                    return SUCCESS;
                }

                sub_temp = sub_temp->link;
            }

            main_temp = main_temp->link;
        }
    }

    return FAILURE;
}
int is_file_present(file_node *head, char *filename)
{
    while (head != NULL)
    {
        if (strcmp(head->filename, filename) == 0)
        {
            return SUCCESS;
        }

        head = head->link;
    }

    return FAILURE;
}
int validate_backup(char *backup_file)
{
    FILE *fp;

    // Check extension
    char *ptr = strrchr(backup_file, '.');

    if (ptr == NULL || strcmp(ptr, ".txt") != 0)
    {
        printf("Invalid backup file extension\n");
        return FAILURE;
    }

    // Check file exists
    fp = fopen(backup_file, "r");

    if (fp == NULL)
    {
        printf("Backup file does not exist\n");
        return FAILURE;
    }

    // Check empty file
    if (fgetc(fp) == EOF)
    {
        printf("Backup file is empty\n");
        fclose(fp);
        return FAILURE;
    }

    fclose(fp);

    return SUCCESS;
}

int update_database(mainnode_t *hash[], file_node **head)
{
    char backup_file[25];
    char word[100];
    char filename[25];

    int index;
    int filecount;
    int wordcount;

    FILE *fp;

    file_node *temp;
    file_node *new_node;
    file_node *new_files = NULL;
    file_node *tail = NULL;

    printf("Enter backup file name: ");
    scanf("%99s", backup_file);

    // Validate backup file
    if (validate_backup(backup_file) == FAILURE)
    {
        return FAILURE;
    }

    fp = fopen(backup_file, "r");

    if (fp == NULL)
    {
        return FAILURE;
    }

    // Read backup records
    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &filecount) == 3)
    {
        if (index < 0 || index > 26 || filecount < 0)
        {
            printf("Invalid backup format\n");
            fclose(fp);
            return FAILURE;
        }

        // Read subnodes
        for (int i = 0; i < filecount; i++)
        {
            if (fscanf(fp, "%[^;];%d;", filename, &wordcount) != 2)
            {
                printf("Invalid backup format\n");
                fclose(fp);
                return FAILURE;
            }

            if (wordcount < 0)
            {
                printf("Invalid wordcount\n");
                fclose(fp);
                return FAILURE;
            }

            if(insert_backup_word(hash, word, filename, wordcount, index)==FAILURE)
            {
                return FAILURE;
            }

            // Add backup source filename to file list if absent
            if (is_file_present(*head, filename) == FAILURE)
            {
                new_node = malloc(sizeof(file_node));

                if (new_node == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_node->filename, filename);
                new_node->link = NULL;

                if (*head == NULL)
                {
                    *head = new_node;
                }
                else
                {
                    temp = *head;

                    while (temp->link != NULL)
                        temp = temp->link;

                    temp->link = new_node;
                }
            }
        }

        // Consume record ending '#'
        if (fgetc(fp) != '#')
        {
            printf("Invalid backup record ending\n");
            fclose(fp);
            return FAILURE;
        }

        // Consume newline if present
        int ch = fgetc(fp);

        if (ch != '\n' && ch != EOF)
            ungetc(ch, fp);
    }

    fclose(fp);

    // Select only files that are not already indexed
    temp = *head;

    while (temp != NULL)
    {
        if (is_file_indexed(hash, temp->filename) == FAILURE)
        {
            new_node = malloc(sizeof(file_node));

            if (new_node == NULL)
                return FAILURE;

            strcpy(new_node->filename, temp->filename);
            new_node->link = NULL;

            if (new_files == NULL)
            {
                new_files = new_node;
                tail = new_node;
            }
            else
            {
                tail->link = new_node;
                tail = new_node;
            }
        }

        temp = temp->link;
    }

    // Add new files to database
    if (new_files != NULL)
    {
        creat_database(new_files, hash);
    }
    printf("Database updated successfully\n");

    return SUCCESS;
}
