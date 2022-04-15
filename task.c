#include <stdio.h>
#include <stdbool.h> // for boolean
#include <string.h>
#include <stdlib.h>
const int Size= 10;
int totalElements = 0;
struct Employee{
char* Username;
char* Email;
char* Password;
char* ID;
char* firstName; 
char* lastName;
double Salary; 
char* Department; 
bool isEmployed ;
};
void empty(struct Employee emp[]);
void displayEmployee(struct Employee emp[]);
void readFromFile(struct Employee emp[]);
void writeToFile(struct Employee emp[]);
void deleteData(struct Employee emp[]);
void modify(struct Employee emp[]);
void mergeBothFiles(struct Employee emp[]);
int main(){
	//task to build an console based
	//program to interact with DB(files)
	// to modify, add, delete employee data
	//program
	//part 3 
	//declaring array
	struct Employee emp[Size];
	// initializing it too empty
	empty(emp);
	//reading into the array
	readFromFile(emp);
	//displaying data
	displayEmployee(emp);
	//part 4 making a console
	bool consolePromt = true;
	int input = 0;
	while(consolePromt){
	printf("Please chose an option?\n");	
	printf("1 Add employee\n");
	printf("2 Delete an employee\n");
	printf("3 update an employee\n");
	printf("4 Exit\n");
	 scanf("%d", &input);
	 if(input == 1){
	 	// add
	 	writeToFile(emp);
	 	displayEmployee(emp);
	 	FILE *fPtr;
		fPtr = fopen("./Resource Files/Log.txt", "a");
		char arr[100];
		strcat(arr,"employee added ");
		printf("%s\n",arr);
		strcat (arr, emp[totalElements-1].ID);
		printf("%s\n",arr);
		strcat(arr," at position ");
		printf("%s\n",arr);
		char has[100];
		strcat(arr,itoa((totalElements-1),has,10));
		printf("%s\n",arr);
		strcat(arr,"\n");
		fputs(arr,fPtr);
		fclose(fPtr);
	 }
	 else if(input == 2){
	 	//delete
	 	deleteData(emp);
	 	displayEmployee(emp);
	 }
	 else if(input == 3){
	 	//modify
	 	modify(emp);
	 }
	 else if(input == 4){
	 	consolePromt = false;
	 	mergeBothFiles(emp); // this will merge both files
	 }
	 else {
	 	printf("Wrong input enter again");
	 }
	}
	return 0;
}
void empty(struct Employee emp[]){
	int i =0;
	for(i=0;i<totalElements;i++){
		//empty code
		emp[i].Username = NULL;
		emp[i].Email = NULL;
		emp[i].Password = NULL;
		emp[i].ID = NULL;
		emp[i].firstName = NULL;
		emp[i].lastName = NULL;
		emp[i].Salary = 0;
		emp[i].Department = NULL;
		emp[i].isEmployed = false;
	}
}

void displayEmployee(struct Employee emp[]){
	int i =0;
	for(i=0;i<totalElements;i++){
		printf("ID = %s \n", emp[i].ID);	
		printf("UserName = %s \n", emp[i].Username);
		printf("First Name = %s \n", emp[i].firstName);
		printf("Last Name = %s \n", emp[i].lastName);
		printf("Email = %s \n", emp[i].Email);
		printf("Password = %s \n", emp[i].Password);
		printf("Department = %s \n", emp[i].Department);
		printf("Salary =  %f \n", emp[i].Salary);
		printf("%s\n", emp[i].isEmployed ? "true" : "false");	
	}
}

void readFromFile(struct Employee emp[]){
	int num;
   	FILE *fptr;
	if ((fptr = fopen("./Resource Files/EmployeeList.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
	int tempForBooleanInput;
	char x[1024];
	char* temp;
	int i=0;
	while((fscanf(fptr, "%s", x) != EOF)){
		fscanf(fptr, "%s", x); //skipping values
		fscanf(fptr, "%s", x); //taking id
		emp[i].ID = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].ID,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//taking username
		emp[i].Username = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].Username,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//taking email
		emp[i].Email = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].Email,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//taking pass
		emp[i].Password = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].Password,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);////taking firstname
		emp[i].firstName = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].firstName,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);////taking firstname
		emp[i].lastName = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].lastName,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//taking dept
		emp[i].Department = (char *)malloc(strlen(x)+1);
		strcpy(emp[i].Department,x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values	
		emp[i].Salary = atoi(x);
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//skipping values
		fscanf(fptr,"%s",x);//taking employment bool
		if(x[0]=='f')
			emp[i].isEmployed = false;
		else 
			emp[i].isEmployed = true;
			
		i++;
		totalElements++;
	}
   fclose(fptr); 
}

void writeToFile(struct Employee emp[]){
	FILE *fPtr;
	fPtr = fopen("./Resource Files/StagedChanges.txt", "a");
	if (fPtr == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open  file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
    char temp[100];
    char temp2[100];
    double d;
    char isEmployed;
    printf("Enter ID ");
    scanf("%s",&temp);
    emp[totalElements].ID = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].ID,temp);
    strcpy(temp2,"ID = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter username ");
    scanf("%s",&temp);
    emp[totalElements].Username = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].Username,temp);
    strcpy(temp2,"Username = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter email ");
    scanf("%s",&temp);
    emp[totalElements].Email = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].Email,temp);
    strcpy(temp2,"Email = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter password " );
    scanf("%s",&temp);
    emp[totalElements].Password = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].Password,temp);
    strcpy(temp2,"Password = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter first name ");
    scanf("%s",&temp);
    emp[totalElements].firstName = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].firstName,temp);
    strcpy(temp2,"First Name = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter last name ");
    scanf("%s",&temp);
    emp[totalElements].lastName = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].lastName,temp);
    strcpy(temp2,"Last Name = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter department ");
    scanf("%s",&temp);
    emp[totalElements].Department = (char *)malloc(strlen(temp)+1);
	strcpy(emp[totalElements].Department,temp);
    strcpy(temp2,"Department = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Enter salary ");
    scanf("%s",&temp);
    emp[totalElements].Salary= (double) atoi(temp);
    strcpy(temp2,"Salary = ");
    strcat(temp2, temp);
    fputs(temp2, fPtr);
    fputs("\n",fPtr);
    printf("Is person employed y/n? ");
    scanf("%s", temp);
    if(temp[0]=='y')
    {
    	fputs("Employed = true", fPtr);
    	emp[totalElements].isEmployed= true;
	}
    else
    {
    	emp[totalElements].isEmployed= false;
	}
    fputs("\n",fPtr);
    fclose(fPtr);
    totalElements++;
}

void deleteData(struct Employee emp[]){
	char id[100];
	printf("Enter ID you want to delete\n");
	scanf("%s",&id);
	int indexOfDeletion = -1;
	int i=0;
	for(i = 0;i<totalElements;i++){
		if(strcmp(emp[i].ID,id))
		{
			indexOfDeletion =i;
			break;
		}
	}
	if(indexOfDeletion== -1){
		printf("ID doesn't exists\n");
	}
	else{
		strcpy(emp[indexOfDeletion].ID , emp[totalElements-1].ID);
		strcpy(emp[indexOfDeletion].Username , emp[totalElements-1].Username);
		strcpy(emp[indexOfDeletion].Password , emp[totalElements-1].Password);
		strcpy(emp[indexOfDeletion].Email , emp[totalElements-1].Email);
		strcpy(emp[indexOfDeletion].firstName , emp[totalElements-1].firstName);
		strcpy(emp[indexOfDeletion].lastName , emp[totalElements-1].lastName);
		strcpy(emp[indexOfDeletion].Department , emp[totalElements-1].Department);
		emp[indexOfDeletion].Salary = emp[totalElements-1].Salary;
		emp[indexOfDeletion].isEmployed = emp[totalElements-1].isEmployed;
		totalElements--;
		// updating in log
		FILE *fPtr;
		fPtr = fopen("./Resource Files/Log.txt", "a");
		char arr[100]= {};
		strcat(arr,"employee removed ");
		strcat(arr,id);
		printf("%s\n",id);
		printf("%s\n",arr);
		strcat(arr,"\n");
		fputs(arr,fPtr);
		fclose(fPtr);
	}
	
}

void modify(struct Employee emp[]){
	char id[100];
	printf("Enter ID you want to modify\n");
	scanf("%s",&id);
	int indexOfDeletion = -1;
	int i=0;
	for(i = 0;i<totalElements;i++){
		if(strcmp(emp[i].ID,id))
		{
			indexOfDeletion =i;
			break;
		}
	}
	if(indexOfDeletion== -1){
		printf("ID doesn't exists\n");
	}
	else{
		printf("Enter new ID\n");
		char ID[100];
		scanf("%s", ID);
		emp[indexOfDeletion].ID = ID;
		printf("Enter new Username\n");
		char un[100];
		scanf("%s",un);
		emp[indexOfDeletion].Username = un;
		printf("Enter new Email\n");
		char em[100];
		scanf("%s",em);
		emp[indexOfDeletion].Email = em;
		printf("Enter new pass\n");
		char pass[100];
		scanf("%s",pass);
		emp[indexOfDeletion].Password = pass;
		printf("Enter new firstName\n");
		char fn[100];
		scanf("%s",fn);
		emp[indexOfDeletion].firstName = fn;
		printf("Enter new Lastname\n");
		char ln[100];
		scanf("%s",ln);
		emp[indexOfDeletion].lastName = ln;
		printf("Enter new Salary\n");
		double sal;
		scanf("%f",sal);
		emp[indexOfDeletion].Salary = sal;
		
		printf("Enter new Depart\n");
		char dep[100];
		scanf("%s",dep);
		emp[indexOfDeletion].Department = dep;
		printf("Is user employed? 1/0 \n");
		int chk;
		scanf("%d",chk);
		if(chk == 1)
		emp[indexOfDeletion].isEmployed = true;
		else
			emp[indexOfDeletion].isEmployed = false;
		// updating in log
		FILE *fPtr;
		fPtr = fopen("./Resource Files/Log.txt", "a");
		char arr[100];
		strcat(arr,"employee changed ");
		printf("%s\n",id);
		printf("%s\n",arr);
		strcat(arr,"\n");
		fputs(arr,fPtr);
		fclose(fPtr);
	}
}

void mergeBothFiles(struct Employee emp[]){
	FILE *fPtr;
	fPtr = fopen("./Resource Files/EmployeeList.txt", "w");
	if (fPtr == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open  file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
    int i=0;
    char temp[100];
    for(i=0;i<totalElements;i++){
    	memset(temp, 0, 100);
    	strcat(temp,"ID = ");
    	strcat(temp, emp[i].ID);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Username = ");
    	strcat(temp, emp[i].Username);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Email = ");
    	strcat(temp, emp[i].Email);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Password = ");
    	strcat(temp, emp[i].Password);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"First Name = ");
    	strcat(temp, emp[i].firstName);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Last Name = ");
    	strcat(temp, emp[i].lastName);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Department = ");
    	strcat(temp, emp[i].Department);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Salary = ");
    	char chka[100];
    	snprintf(chka, 50, "%f", emp[i].Salary);
    	strcat(temp, chka);
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
    	memset(temp, 0, 100);
    	strcat(temp,"Employed = ");
    	strcat(temp, "true");
    	strcat(temp,"\n");
    	fputs(temp, fPtr);
	}
    fclose(fPtr);
    totalElements++;
}
