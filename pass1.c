#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

struct op_table
{
        char opc[16];             //mnemonic name
        char opr1[16];            //operand 1
        char opr2[16];            //operand 2
        char opr3[16];            //operand 3
        char bin[16];            //hexadecimal code of mnemonic
        int len;                 //no. of cycles
        int ins_class;           //instruction class
};

int main()
{
	FILE *f1, *f2,*fh,*f3,*f4;
	char file1[20],file2[20];
	printf("Enter source file name:");
	scanf("%s",file1);
	printf("Enter destination file name:");
	scanf("%s",file2);
	f1 = fopen(file1, "r");		//file containing assembly language codes using new ISA opened in read mode
	
	f2 = fopen(file2,"w");		//pass one file opened in write mode
	
	f3 = fopen("opcodeTable.txt","r");
	f4 = fopen("register.txt","r");
	
	char reg[10],regis[10],regop[10];
			
	struct op_table s[100];
	int q,x,f;
	char opcode[16];
	int opcod;
	fscanf(f3,"%s",opcode);
	
	while(!feof(f3))
	{
		for(q=0;q<100;q++)
		{
			for(x=0;x<16;x++)
			{
				s[q].opc[x]=opcode[x];
			}
			fscanf(f3,"%s",opcode);
				for(x=0;x<16;x++)
			{
				s[q].opr1[x]=opcode[x];
			}
			
			fscanf(f3,"%s",opcode);
				for(x=0;x<16;x++)
			{
				s[q].opr2[x]=opcode[x];
			}
			
			fscanf(f3,"%s",opcode);
				for(x=0;x<16;x++)
			{
				s[q].opr3[x]=opcode[x];
			}
			
			fscanf(f3,"%s",opcode);
				for(x=0;x<16;x++)
			{
				s[q].bin[x]=opcode[x];
			}
			
			fscanf(f3,"%d",opcode);
			
				s[q].len=opcode[0];
						
			fscanf(f3,"%d",opcode);
			
				s[q].ins_class=opcode[0];
			
			
			fscanf(f3,"%s",opcode);
			
			
		}
	}
	
	fclose(f3);
	char str[10],colon[10],garbage[10];
	int z,i,j,k,ilc=-1, flag = 0, flag3 = 0; //ilc is initialized to -1 sice we are incrementing it later as ilc of program starts from 0
	
    char c ,ch, sh,opcd[5],d,re[20];
	
	fprintf(f2,"SYMBOL TABLE\n");		
	fprintf(f2,"LABEL NAME\tILC\n");
	
	while((c = fgetc(f1)) != EOF)    
	{
		if(c == '\n')
		{
			fscanf(f1,"%s",str);
            for(i=0;i<100;i++)                       //calculating ilc
			{
                strcpy(opcd,s[i].opc);
				flag =0;
				if((strcmp( str,opcd)) == 0)
				{
					
					ilc+=s[i].len; 
                    flag = 1;
					/*fscanf(f1,"%s",reg);
					fscanf(f4,"%s",regis);
					while(fgetc(f4)!=EOF)			
					{
							if(strcmp(reg,regis)==0)
							{
								printf("%s\t%s",reg,regis);
								f=1;
								
								
							}
							
						fscanf(f4,"%s",regis);
					}
					if(f==0)
					{
						printf("error");
					}*/
	fclose(f4);
					/*char reg[10],regis[10];
					if(flag==1)
						
			{
				fscanf(f1,"%s",reg);
				printf("%s\n",reg);
				while(! feof(f4))    
				{
					
					
						
						fscanf(f4,"%s",regis);
						printf("%s",regis);
						
					
				}
			}*/
					break;
					
				}
				
			}
			
			
			
	        if(flag == 0)                           //printing label name and ilc (Symbol Table)
	        {
	        	
	        	fscanf(f1,"%s",colon);
	        if (strcmp(colon,":") == 0)
	        	{
	        		fprintf(f2,"%s\t",str);
					fprintf(f2,"\t%d\n",++ilc);
				}
				else                   //if illegal opcode is encountered program is terminated
				{
					flag3 = 1;
					printf ("ILLEGAL OPCODE\nCANNOT PROCEED FURTHER\tINSTRUCTION NO:%d\n",ilc+1);
					printf("Press 1 and enter for help\n");
					scanf("%d",&z);
						if(z==1)
						{			
						
							fh=fopen("help.txt", "r");
							while(1)
							{
								ch = fgetc(fh);
								if( feof(fh) )
								{
									break ;
								}
								printf("%c", ch);
							}
							fclose(fh);
							break;
							break;
						}
					return;
				}
            }
		}
	}
	rewind(f1);
	fprintf(f2,"\n\n\t\t   \t\t\tOPCODE TABLE\n\n");
	fprintf(f2,"MNEMONIC \tOPR1 \t\tOPR2 \t\tOPR3 \t\tHEX. CODE \tINSTR LENGTH \tINSTR CLASS\n");
	for(i=0; i<100; i++)       //printing opcode table
	{
		rewind(f1);
		while((c = fgetc(f1)) != EOF)
	    {
		     if(c == '\n')
		     {
		        	fscanf(f1,"%s",str);
		        	strcpy(opcd,s[i].opc);
		        	if((strcmp( str,opcd)) == 0)
				    {
	                     fprintf(f2,"%s \t\t%s \t\t%s \t\t%s \t\t%s \t\t    %d \t\t   %d\n",s[i].opc,s[i].opr1,s[i].opr2,s[i].opr3,s[i].bin,s[i].len,s[i].ins_class);
	                     break;
                    }
			}
		}
	}	

	
	fclose(f1);
	fclose(f2);
	
	return 0;
}
