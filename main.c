#include<stdio.h>
#include"header.h"

int main(int argc, char *argv[])
{
	char backup_file[100];
	mainnode_t *arr[27]={NULL};
	file_node*file_n=NULL;

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
			if(creat_database(file_n,arr)==FAILURE)
			{
				printf("Failed ...database not created \n");
				return FAILURE;
			}
			else
			{
				printf("-------------------------------\n");
				printf("DATABASE created successfully\n");
				printf("-------------------------------\n");
				
			}
		break;
		case 2:
			if(display_database(arr)==FAILURE)
			{
				return FAILURE;
			}
		break;
		case 3:
			if(search_database(arr)==FAILURE)
			{

				return FAILURE; 
			}
			else{
				printf("---------------------------------\n");

			    }
		break;
		case 4:
			printf("update");
		break;
		case 5:
			printf("Enter backup file name: ");
			scanf("%s", backup_file);
			if (save_database(arr, backup_file) == SUCCESS)
			{
    			printf("Save operation completed\n");
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

