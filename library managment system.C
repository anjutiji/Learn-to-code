#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#define RETURNTIME 15
void issue();
void edit();
void deletee();
void view();
void menu();
int checkmem(int);
int checkbook(int);
void checkissue(int);
void bookdetails(int);
void editrec(int);
int countcode();
void bookcopy(int);
void bookcopyinc(int);
struct library
{
	int i_code;
	int m_id;
	int b_id;
	char i_date[10];
	char i_rdate[10];
	int i_fine;
}lib,updis,check;
struct member
{
	int m_id;
	char m_name[20];
	char m_addr[40];
}m,cm;
struct book
{
	int b_id;
	char b_name[20];
	char b_auth[20];
	int b_copy;
}b,cb,upd;
struct dates
{
	int mm,dd,yy;
}issued,duedate;
struct Count
{
	int c_code;
}cnt,co;
void main()
{
	menu();
	getch();
}
void menu()
{
	int n;
	char c;
	label:
	clrscr();
	printf("\n########################### LIBRARY MANAGEMENT SYSTEM #########################\n\n");
	printf("\n\t##################################################################");
	printf("\n\t####################### ISSUE BOOK CONSOLE #######################");
	printf("\n\t##################################################################");
	printf("\n\n\t\t\t ****** 1. ISSUE BOOK *********");
	printf("\n\n\t\t\t ****** 2. EDIT      **********");
	printf("\n\n\t\t\t ****** 3. DELETE    **********");
	printf("\n\n\t\t\t ****** 4. VIEW      **********");
	printf("\n\n\t\t\t ****** 5. EXIT      **********");
	printf("\n\n\nENTER YOUR CHOICE: ");
	scanf("%d",&n);
	switch(n)
	{
		case 1: issue();
			break;
		case 2: edit();
			break;
		case 3: deletee();
			break;
		case 4: view();
			break;
		case 5: exit(0);
			break;
		default: printf("\nWrong Entry !!  Please Enter correct option.");
			 printf("\nDo you want to continue? (Y/N) : ");
			scanf("%s",&c);
			if((c=='y')||(c=='Y'))
			{
				goto label;
			}
			else
			{
				exit(0);
			}
			 break;
	}
}
void issue()
{
	FILE *fi;
	int mid,rm,bid,rb;
	int day,month,year,rday,rmonth,ryear;
	char rdate[10],idate[10];
	char ch,c;
	char *p1=lib.i_date;
	char *p=lib.i_rdate;
	issue_more:
	clrscr();
	printf("\n\t\t#################################################");
	printf("\n\t\t############### ISSUE BOOK SECTION ##############");
	printf("\n\t\t#################################################");
	printf("\n\nEnter the member id: ");
	scanf("%d",&cm.m_id);
	mid=cm.m_id;
	rm=checkmem(mid);
	if(rm==0)
	{
		printf("\n\nEnter the book id:");
		scanf("%d",&cb.b_id);
		bid=cb.b_id;
		rb=checkbook(bid);
		if(rb==0)
		{
		   bookdetails(bid);
		   printf("\n\nDo you want to issue book? (Y/N) : ");
		   scanf("%s",&ch);
		   if((ch=='Y')||(ch=='y'))
		   {
			struct dosdate_t d;
			_dos_getdate(&d);
			issued.dd=d.day;
			issued.mm=d.month;
			issued.yy=d.year;
			day=issued.dd;
			month=issued.mm;
			year=issued.yy;
			sprintf(idate,"%d/%d/%d",day,month,year);
			strcpy(p1,idate);
			printf("\nIssued date: %s",idate);
			duedate.dd=issued.dd+RETURNTIME;
			duedate.mm=issued.mm;
			duedate.yy=issued.yy;
			if(duedate.dd>30)
			{
				duedate.mm+=duedate.dd/30;
				duedate.dd-=30;
			}
			if(duedate.mm>12)
			{
				duedate.yy+=duedate.mm/12;
				duedate.mm-=12;
			}
			rday=duedate.dd;
			rmonth=duedate.mm;
			ryear=duedate.yy;
			sprintf(rdate,"%d/%d/%d",rday,rmonth,ryear);
			printf("\nTo be Returned : %s",rdate);
			strcpy(p,rdate);
			cnt.c_code=countcode();
			bookcopy(bid);
			fi=fopen("issue.txt","a+");
			fprintf(fi,"%d\t%d\t%d\t%s\t%s\t%d\n",cnt.c_code,cm.m_id,cb.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
			fclose(fi);
			printf("\n\tBOOK ISSUED SUCESSFULLY");
		   }
		   else
		   {
			goto issue_more;
		   }
		}
	}
	printf("\nDo you want to issue more? (Y/N) : ");
	scanf("%s",&c);
	if((c=='y')||(c=='Y'))
	{
		goto issue_more;
	}
	else
	{
		menu();
	}
}
void edit()
{
	int ch;
	char c;
	edit_more:
	clrscr();
	ch=1;
	printf("\n\t\t###################################################");
	printf("\n\t\t################ EDIT ISSUED BOOK #################");
	printf("\n\t\t###################################################\n\n");
	checkissue(ch);
	remove("issue.txt");
	rename("temp.txt","issue.txt");
	printf("\nDo you want to edit more? (Y/N) : ");
	scanf("%s",&c);
	if((c=='y')||(c=='Y'))
	{
		goto edit_more;
	}
	else
	{
		menu();
	}
}
void deletee()
{
	char c;
	int ch;
	del:
	clrscr();
	ch=0;
	printf("\n\t\t#####################################################");
	printf("\n\t\t################ DELETE ISSUED BOOK #################");
	printf("\n\t\t#####################################################\n\n");
	checkissue(ch);
	remove("issue.txt");
	rename("temp.txt","issue.txt");
	printf("\nDo you want to delete more? (Y/N) : ");
	scanf("%s",&c);
	if((c=='y')||(c=='Y'))
	{
		goto del;
	}
	else
	{
		menu();
	}
}
void view()
{
	int ch,flag=0,bid,mid;
	char c;
	FILE *fi;
	view_more:
	clrscr();
	printf("\t\t####################################################\n");
	printf("\t\t#################### VIEW DETAILS ##################\n");
	printf("\t\t####################################################\n");
	printf("\n\n\t1. Issue Details\n\n\t2. Search Book ID\n\n\t3. Search Member ID\n");
	printf("\nEnter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: printf("\nISSUE CODE   MEMBER ID   BOOK ID    ISSUE DATE\tRETURN DATE\tFINE\n");
			printf("********************************************************************");
			fi=fopen("issue.txt","r");
			while(fscanf(fi,"%d%d%d%s%s%d",&lib.i_code,&lib.m_id,&lib.b_id,lib.i_date,lib.i_rdate,&lib.i_fine)!=EOF)
			{
				printf("\n    %d\t%d\t%d\t  %s  \t%s \t  %d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
				flag++;
			}
			if(flag==0)
			{
				printf("\nNo Record Found!\n");
			}
			fclose(fi);
			break;
		case 2: printf("Enter the Book Id: ");
			scanf("%d",&bid);
			printf("\nISSUE CODE   MEMBER ID   BOOK ID    ISSUE DATE\tRETURN DATE\tFINE\n");
			printf("********************************************************************");
			fi=fopen("issue.txt","r");
			while(fscanf(fi,"%d%d%d%s%s%d",&lib.i_code,&lib.m_id,&lib.b_id,lib.i_date,lib.i_rdate,&lib.i_fine)!=EOF)
			{
				if(bid==lib.b_id)
				{
					printf("\n    %d\t%d\t%d\t  %s  \t%s\t  %d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
					flag++;

				}
			}
			if(flag==0)
			{
				printf("\nBook not Found\n");
			}
			fclose(fi);
			break;
		case 3: printf("Enter the Member Id: ");
			scanf("%d",&mid);
			printf("\nISSUE CODE   MEMBER ID   BOOK ID    ISSUE DATE\tRETURN DATE\tFINE\n");
			printf("********************************************************************");
			fi=fopen("issue.txt","r");
			while(fscanf(fi,"%d%d%d%s%s%d",&lib.i_code,&lib.m_id,&lib.b_id,lib.i_date,lib.i_rdate,&lib.i_fine)!=EOF)
			{
				if(mid==lib.m_id)
				{
					printf("\n    %d\t%d\t%d\t  %s  \t%s\t  %d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
					flag++;
				}
			}
			if(flag==0)
			{
				printf("\nMember not Found\n");
			}
			fclose(fi);
			break;
		default: printf("Wrong Entry");
			 break;

	}
	printf("\nDo you want to view more? (Y/N) : ");
	scanf("%s",&c);
	if((c=='y')||(c=='Y'))
	{
		goto view_more;
	}
	else
	{
		menu();
	}
}
void editrec(int isid)
{
	int s,bid;
	FILE *fe;
	printf("\nWhich information do you want to change?");
	printf("\n\t1. BOOK ID");
	printf("\n\t2. ISSUE DATE");
	printf("\n\t3. RETURN DATE");
	printf("\n\t4. FINE");
	printf("\n\t5. CANCEL");
	printf("\n\t6. EXIT");
	printf("\nEnter your choice: ");
	scanf("%d",&s);
	switch(s)
	{
		case 1: printf("\nEnter the New Book Id: ");
			scanf("%d",&updis.b_id);
			bid=updis.b_id;
			bookcopy(bid);
			bookcopyinc(isid);
			fe=fopen("temp.txt","a");
			fprintf(fe,"%d\t%d\t%d\t%s\t%s\t%d\n",isid,lib.m_id,updis.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
			printf("\nChanges Saved Successfully!");
			fclose(fe);
			break;
		case 2: printf("\nEnter the New Issue Date: ");
			scanf("%s",&updis.i_date);
			fe=fopen("temp.txt","a");
			fprintf(fe,"%d\t%d\t%d\t%s\t%s\t%d\n",lib.i_code,lib.m_id,lib.b_id,updis.i_date,lib.i_rdate,lib.i_fine);
			printf("\nChanges Saved Successfully!");
			fclose(fe);
			break;
		case 3: printf("\nEnter the New Return Date: ");
			scanf("%s",&updis.i_rdate);
			fe=fopen("temp.txt","a");
			fprintf(fe,"%d\t%d\t%d\t%s\t%d\t%d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,updis.i_rdate,lib.i_fine);
			printf("\nChanges Saved Successfully!");
			fclose(fe);
			break;
		case 4: printf("\nEnter the New Fine: ");
			scanf("%d",&updis.i_fine);
			fe=fopen("temp.txt","a");
			fprintf(fe,"%d\t%d\t%d\t%s\t%s\t%d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,updis.i_fine);
			printf("\nChanges Saved Successfully!");
			fclose(fe);
			break;
		case 5: remove("temp.txt");
			edit();
			break;
		case 6: remove("temp.txt");
			menu();
			break;
		default:printf("wrong choice");
			break;
	}
}
int checkmem(int mid)
{
	int flag=0,f=0;
	FILE *fm;
	fm=fopen("member.txt","r");
	while(fscanf(fm,"%d\t%s\t%s\n",&m.m_id,m.m_name,m.m_addr)!=EOF)
	{
		if(mid==m.m_id)
		{
			flag++;
			f++;
		}
	}
	if(flag==0)
	{
		printf("\n%d is not a member\n",cm.m_id);
	}
	fclose(fm);
	if(f!=0)
	{
		return 0;
	}
	else
	{
		return 1;
	}

}
int checkbook(int bid)
{
	int flag=0,f=0;
	FILE *fb;
	fb=fopen("book.txt","r");
	while(fscanf(fb,"%d\t%s\t%s\t%d\n",&b.b_id,b.b_name,b.b_auth,&b.b_copy)!=EOF)
	{
		if(bid==b.b_id)
		{
			flag++;
			f++;
		}
	}
	if(flag==0)
	{
		printf("\nbook is not available\n");
	}
	fclose(fb);
	if(f!=0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void checkissue(int ch)
{
	int flag=0,isid;
	char c;
	FILE *fi,*ftemp;
	fi=fopen("issue.txt","r");
	printf("\n\nEnter the issue code : ");
	scanf("%d",&isid);
	while(fscanf(fi,"%d\t%d\t%d\t%s\t%s\t%d",&lib.i_code,&lib.m_id,&lib.b_id,lib.i_date,lib.i_rdate,&lib.i_fine)!=EOF)
	{
		if(isid==lib.i_code)
		{
			printf("\nISSUE CODE   MEMBER ID   BOOK ID    ISSUE DATE\tRETURN DATE\tFINE\n");
			printf("*****************************************************************");
			printf("\n    %d\t%d\t%d\t  %s  \t%s\t  %d\n\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
			flag++;
			if(ch==1)
			{
				editrec(isid);
			}
			else
			{
				printf("\nDo you want to delete the record (Y/N): ");
				scanf("%s",&c);
				if((c=='y')||(c=='Y'))
				{
					printf("\nRecord deleted successfully\n");
				}
				else
				{
					ftemp=fopen("temp.txt","a");
					fprintf(ftemp,"%d\t%d\t%d\t%s\t%s\t%d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
					fclose(ftemp);
				}
			}
		}
		else
		{
			ftemp=fopen("temp.txt","a");
			fprintf(ftemp,"%d\t%d\t%d\t%s\t%s\t%d\n",lib.i_code,lib.m_id,lib.b_id,lib.i_date,lib.i_rdate,lib.i_fine);
			fclose(ftemp);
		}
	}
	fclose(fi);
	if(flag==0)
	{
		remove("temp.txt");
		printf("\nNo records available\n");
	}
}

void bookdetails(int bid)
{
	FILE *fb;
	fb=fopen("book.txt","r");
	while(fscanf(fb,"%d\t%s\t%s\t%d\n",&b.b_id,b.b_name,b.b_auth,&b.b_copy)!=EOF)
	{
		if(bid==b.b_id)
		{
			printf("\n\n\t   BOOK DETAILS");
			printf("\n\t__________________\n");
			printf("\n\tBook Name: %s",b.b_name);
			printf("\n\tBook Author: %s",b.b_auth);
			printf("\n\tNo: of copies available: %d",b.b_copy);
		}
	}
	fclose(fb);
}
int countcode()
{
	FILE *fc,*fcd;
	fc=fopen("count.txt","r");
	fscanf(fc,"%d",&cnt.c_code);
	co.c_code=cnt.c_code+1;
	fclose(fc);
	fcd=fopen("count.txt","w");
	fprintf(fcd,"%d",co.c_code);
	fclose(fcd);
	return co.c_code;
}
void bookcopy(int bid)
{
	int flag=0;
	FILE *fb,*ft;
	fb=fopen("book.txt","r");
	ft=fopen("tempbook.txt","a");
	while(fscanf(fb,"%d\t%s\t%s\t%d\n",&b.b_id,b.b_name,b.b_auth,&b.b_copy)!=EOF)
	{
		if(bid==b.b_id)
		{
			upd.b_copy=b.b_copy-1;
			fprintf(ft,"%d\t%s\t%s\t%d\n",b.b_id,b.b_name,b.b_auth,upd.b_copy);
			flag++;
		}
		else
		{
			fprintf(ft,"%d\t%s\t%s\t%d\n",b.b_id,b.b_name,b.b_auth,b.b_copy);
		}

	}
	fclose(fb);
	if(flag!=0)
	{
		fclose(ft);
		remove("book.txt");
		rename("tempbook.txt","book.txt");
	}
}
void bookcopyinc(int isid)
{
	int flag=0,bid;
	FILE *fb,*ft,*fi;
	fi=fopen("issue.txt","r");
	while(fscanf(fi,"%d\t%d\t%d\t%s\t%s\t%d",&lib.i_code,&lib.m_id,&lib.b_id,lib.i_date,lib.i_rdate,&lib.i_fine)!=EOF)
	{
		if(isid==lib.i_code)
		{
			bid=lib.b_id;
			fb=fopen("book.txt","r");
			ft=fopen("tempbook.txt","a");
			while(fscanf(fb,"%d\t%s\t%s\t%d\n",&b.b_id,b.b_name,b.b_auth,&b.b_copy)!=EOF)
			{
				if(bid==b.b_id)
				{
					upd.b_copy=b.b_copy+1;
					fprintf(ft,"%d\t%s\t%s\t%d\n",b.b_id,b.b_name,b.b_auth,upd.b_copy);
					flag++;
				}
				else
				{
					fprintf(ft,"%d\t%s\t%s\t%d\n",b.b_id,b.b_name,b.b_auth,b.b_copy);
				}
			}
			fclose(fb);
		 }
	}
	fclose(fi);
	if(flag!=0)
	{
		fclose(ft);
		remove("book.txt");
		rename("tempbook.txt","book.txt");
	}
}