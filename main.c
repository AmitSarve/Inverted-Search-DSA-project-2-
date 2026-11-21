#include<stdio.h>
#include"header.h"

int main(int argc, char *argv[])
{
	char backup_file[100];
	mainnode_t *arr[27]={NULL};
	file_node*file_n=NULL;
	int create_flag = 0;
	int update_flag = 0;

	
	if(validate(argc,argv,&file_n)==FAILURE)
	{
		return FAILURE;
	}
	
	while(1)
	{

	int sr;
	printf("1.Create Database\n2.Display Database\n3.Search Database\n4.Update Database\n5.Save\n6.Exit\n");
	printf("Enter the choice : ");
	scanf("%d",&sr);
	switch(sr)
	{
		case 1:
		if(create_flag == 0 && update_flag == 0)
    	{
        if(creat_database(file_n, arr) == SUCCESS)
        {
            create_flag = 1;
			printf("\n-------------------------------------\n");
            printf("Database created successfully\n");
			printf("\n-------------------------------------\n");
        }
        else
        {
			printf("\n-------------------------------------\n");
            printf("Database creation failed\n");
			printf("\n-------------------------------------\n");
        }
    	}
    	else
    	{
			printf("\n-------------------------------------\n");
        printf("Database already created or updated\n");
		printf("\n-------------------------------------\n");
    	}
		break;
		case 2:
		if(create_flag==1 || update_flag==1)
		{
			if(display_database(arr)==FAILURE)
			{
				return FAILURE;
			}
		}
		else
		{
			printf("\n-------------------------------------\n");
			printf("create database first\n");
			printf("\n-------------------------------------\n");
		}
		break;
		case 3:
		if(create_flag==1 || update_flag==1)
		{
			if(search_database(arr)==FAILURE)
			{

				return FAILURE; 
			}
		}
			else{
				printf("\n-------------------------------------\n");
				printf("create database first\n");
				printf("\n-------------------------------------\n");

			    }
		break;
		case 4:
		if(create_flag == 0 && update_flag == 0)
    	{
        if(update_database(arr, &file_n) == SUCCESS)
        {
            update_flag = 1;
			printf("\n-------------------------------------\n");
            printf("Update successful\n");
			printf("\n-------------------------------------\n");
        }
        else
        {
			printf("\n-------------------------------------\n");
            printf("Update failed\n");
			printf("\n-------------------------------------\n");
        }
    	}
    	else
    	{
			printf("\n-------------------------------------\n");
        printf("Database already created or updated\n");
		printf("\n-------------------------------------\n");
    	}
		break;
		case 5:
		if(create_flag==1 || update_flag==1)
		{
			printf("Enter backup file name: ");
			scanf("%s", backup_file);
			if (save_database(arr, backup_file) == SUCCESS)
			{
				printf("\n-------------------------------------\n");
    			printf("Save operation completed\n");
				printf("\n-------------------------------------\n");
			}
		}
		else
        {
			printf("\n-------------------------------------\n");
            printf("Create or update database first\n");
			printf("\n-------------------------------------\n");
        }
		break;
		case 6:
		printf("--------------------------\n");
			printf("Exiting Successfully\n");
			return SUCCESS;
		break;
		default:
		printf("Invalid choice\n");


	}
}
return 0;
}

