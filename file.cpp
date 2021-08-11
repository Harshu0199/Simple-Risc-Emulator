#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include<cstring>
std::string binary(int,int);
int hextodec(std::string);
using namespace std;
int main()
{
	string what,inst,s1,s2,s3,s4,s5,s;
	int r[13],sp,ra,k,n1,n2,n3,i=0,GT=0,E=0,memory[100000],v=0,call[100],z, ii=-1,in=hextodec("2000");
	ofstream ofile("output.txt");
	ifstream ifile("input.txt");
	if(ifile.is_open())
	{
		for(int u=0;u<2;u++)
		{
			i=0;
			if(u==1)
			for(int j=0;j<v;j++)
			{
				getline(ifile,s);
				i++;
			}
		again:
		while(getline(ifile,s))
		{
			i++;
			stringstream iss(s);
			iss>>what;
			if(what==".encode")
			{
				iss>>inst;
//_____________________mov instruction___________________________________________
				if(inst=="mov")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": mov is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": mov is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s2)>>k;
						if(s2[0]=='#')
						{
							int l=s2.length()-1,ad;
							s2=s2.substr(1,l);
							if(l!=4)
							{
								ofile<<"Error in Line-"<<i<<": 16 bit address required!\n";
								goto exit;
							}
							if(u==0)
							{
								ad= hextodec(s2);
								ofile<<"01001 1 "<<binary(4,n1)<<" .... ##"<<binary(16,ad)<<"\n";
							}
							if(u==1)
							{
								k=memory[ad];
								if(k==0)k=-1;
							}
						}
						if(s2=="0")
						{
							if(u==1)
							r[n1]=0;
							if(u==0)
							ofile<<"01001 1 "<<binary(4,n1)<<" .... "<<binary(18,0)<<"\n";
						}
						else if(k!=0)
						{
							if(k==-1)k=0;
							if(u==1)
							r[n1]=k;
							if(u==0)
							ofile<<"01001 1 "<<binary(4,n1)<<" .... "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2];
							if(u==0)
							ofile<<"01001 0 "<<binary(4,n1)<<" .... "<<binary(4,n2);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": mov is Two address instrucion ";
						ofile<<"need two registers!\n";
						goto exit;
					}
				}
//_____________________add instruction___________________________________________
				else if(inst=="add")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": add is Three address instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": add is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": add is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]+k;
							if(u==0)
							ofile<<"00000 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
					 }
						else
						{
							if(u==1)
							r[n1]=r[n2]+r[n3];
							if(u==0)
							ofile<<"00000 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": add is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}
//_____________________sub instruction___________________________________________
				else if(inst=="sub")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": sub is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": sub is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": sub is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]-k;
							if(u==0)
							ofile<<"00001 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
					 }
						else
						{
							if(u==1)
							r[n1]=r[n2]-r[n3];
							if(u==0)
							ofile<<"00001 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": sub is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}
//_____________________mul instruction___________________________________________
				else if(inst=="mul")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": mul is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": mul is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": mul is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]*k;
							if(u==0)
							ofile<<"00010 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]*r[n3];
							if(u==0)
							ofile<<"00010 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": mul is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}				
//_____________________div instruction___________________________________________
				else if(inst=="div")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": div is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": div is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": div is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]/k;
							if(u==0)
							ofile<<"00011 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]/r[n3];
							if(u==0)
							ofile<<"00011 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": div is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}				
//_____________________mod instruction___________________________________________
				else if(inst=="mod")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": mod is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": mod is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": mod is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]%k;
							if(u==0)
							ofile<<"00100 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]%r[n3];
							if(u==0)
							ofile<<"00100 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": mod is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}				
//_____________________and instruction___________________________________________
				else if(inst=="and")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": and is Three address instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": and is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": and is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]&k;
							if(u==0)
							ofile<<"00110 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]&r[n3];
							if(u==0)
							ofile<<"00110 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": and is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}				
//_____________________or instruction___________________________________________
				else if(inst=="or")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": or is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": or is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": or is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]|k;
							if(u==0)
							ofile<<"00111 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]|r[n3];
							if(u==0)
							ofile<<"00111 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": or is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}				
//_____________________lsl instruction___________________________________________
				else if(inst=="lsl")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": lsl is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": lsl is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": lsl is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]<<k;
							if(u==0)
							ofile<<"01010 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]<<r[n3];
							if(u==0)
							ofile<<"01010 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": lsl is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}								
//_____________________lsr instruction___________________________________________
				else if(inst=="lsr")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": lsr is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": lsr is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": lsr is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]>>k;
							if(u==0)
							ofile<<"01011 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]>>r[n3];
							if(u==0)
							ofile<<"01011 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": lsr is Three address instrucion ";
						ofile<<"need three registers!\n";
					}
				}				
//_____________________asr instruction___________________________________________
				else if(inst=="asr")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": asr is Three subress instrucion,";
						ofile<<"need Three registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": asr is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						ofile<<"Error in Line-"<<i<<": sub is Three address instrucion,";
						ofile<<"need three registers!\n";
						goto exit;	
					}
					if(!(iss>>s4))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s3.substr(1,s3.length()-1))>>n3;
						istringstream(s3)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=r[n2]>>k;
							if(u==0)
							ofile<<"01100 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=r[n2]>>r[n3];
							if(u==0)
							ofile<<"01100 0 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(4,n3);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": asr is Three address instrucion ";
						ofile<<"need three registers!\n";
						goto exit;
					}
				}
//_____________________not instruction___________________________________________
				else if(inst=="not")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": not is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": not is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s2)>>k;
						if(k!=0)
						{
							if(u==1)
							r[n1]=~k;
							if(u==0)
							ofile<<"01000 1 "<<binary(4,n1)<<" .... "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							r[n1]=~r[n2];
							if(u==0)
							ofile<<"01000 0 "<<binary(4,n1)<<" .... "<<binary(4,n2);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": not is Two address instrucion ";
						ofile<<"need two registers!\n";
						goto exit;
					}
				}
//_____________________cmp instruction___________________________________________
				else if(inst=="cmp")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": cmp is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": cmp is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(1,s2.length()-1))>>n2;
						istringstream(s2)>>k;
						if(s2=="0")
						{
							if(u==1)
							{
							if(r[n1]>0)
							{
								GT=1;E=0;
							}
							else if(r[n1]==0)
							{
								GT=0;E=1;
							}
						}
							if(u==0)
							ofile<<"00101 1 "<<".... "<<binary(4,n1)<<" "<<binary(18,0)<<"\n";
						}
						else if(k!=0)
						{
							if(u==1)
							{
							if(r[n1]>k)
							{
								GT=1;E=0;
							}
							else if(r[n1]==k)
							{
								GT=0;E=1;
							}
						}
							if(u==0)
							ofile<<"00101 1 "<<".... "<<binary(4,n1)<<" "<<binary(18,k)<<"\n";
						}
						else
						{
							if(u==1)
							{
							if(r[n1]>r[n2])
							{
								GT=1;E=0;
							}
							else if(r[n1]==r[n2])
							{
								GT=0;E=1;
							}
						}
							if(u==0)
							ofile<<"00101 0 "<<binary(4,n1)<<" .... "<<binary(4,n2);
							if(u==0)
							ofile<<" .............\n";
						}
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": cmp is Two address instrucion ";
						ofile<<"need two registers!\n";
						goto exit;
					}
				}
//__________________________________ld instruction_____________________________________
				else if(inst=="ld")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": ld is Two address instrucion,";
						ofile<<"need two registers!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": ld is Two address instrucion,";
						ofile<<"need two registers and an immidiate value!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						k=0;
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(0,s2.find('[')))>>k;
						istringstream(s2.substr(s2.find('[')+2,s2.length()-s2.find('[')-3))>>n2;
						if(u==1)
						r[n1]=memory[in+n2+k];
						if(u==0)
						ofile<<"01110 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": ld is Two address instrucion ";
						ofile<<"need two registers and an immidiate value!\n";
						goto exit;
					}		
				}
//________________________________st instrruction____________________________________
				else if(inst=="st")	
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": st is Two address instrucion,";
						ofile<<"need two registers and an immidiate value!\n";
						goto exit;	
					}
					if(!(iss>>s2))
					{
						ofile<<"Error in Line-"<<i<<": st is Two address instrucion,";
						ofile<<"need two registers and an immidiate value!\n";
						goto exit;	
					}
					if(!(iss>>s3))
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						istringstream(s2.substr(0,s2.find('[')))>>k;
						istringstream(s2.substr(s2.find('[')+2,s2.length()-s2.find('[')-3))>>n2;
						if(u==1)
						{
						memory[in+n2+k]=r[n1];
						int t=in+n2+k;
						if(t>in-1&&t<in+14)
						r[t-in]=memory[t];
					}
						if(u==0)
						ofile<<"01111 1 "<<binary(4,n1)<<" "<<binary(4,n2)<<" "<<binary(18,k)<<"\n";
					}
					else
					{
						ofile<<"Error in Line-"<<i<<": st is Two address instrucion,";
						ofile<<"need two registers and an immidiate value!\n";
						goto exit;
					}		
				}
				else if(inst=="nop")
				{
					if(!(iss>>s1))
					if(u==0)
					ofile<<"01101 "<<"..............................\n";
					else
					{ 
						ofile<<"Error in Line-"<<i<<": nop is 0 address instruction,";
						ofile<<"No register required\n";
						goto exit;
					}
				}
				else if(inst=="b")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": b requires 1 address level!";
						goto exit;
					}
					if(!(iss>>s2))
					{
						if(u==0)
						ofile<<"10010 "<<s1<<"\n";
						if(u==1)
						{
							ifile.seekg(0,ios::beg);
							z=i;
							i=0;
							while(getline(ifile,s))
							{
								i++;
								stringstream iss(s);
								iss>>s3;iss>>s4;
								s4=s4.substr(0,s4.length()-1);
								if(s3==".encode"&&s4==s1)
								goto again;
							}
							if(s4!=s1)
							{
								ofile<<"Error in Line-"<<z<<": "<<s1<<" -No such level found!";
								goto exit;
							}
						}	
					}
					else 
					{
						ofile<<"Error in Line-"<<i<<": b requires only 1 address level!";
						goto exit;	
					}
				}
//___________________________________bgt instruction____________________________
				else if(inst=="bgt")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": bgt requires 1 address level!";
						goto exit;
					}
					if(!(iss>>s2))
					{
						if(u==0)
						ofile<<"10001 "<<s1<<"\n";
						if(u==1)
						{
						if(GT==1)
						{
							ifile.seekg(0,ios::beg);
							z=i;
							i=0;
							while(getline(ifile,s))
							{
								i++;
								stringstream iss(s);
								iss>>s3;iss>>s4;
								s4=s4.substr(0,s4.length()-1);
								if(s3==".encode"&&s4==s1)
								goto again;
							}
							if(s4!=s1)
							{
								ofile<<"Error in Line-"<<z<<": "<<s1<<" -No such level found!";
								goto exit;
							}
						}
					}
					}
					else 
					{
						ofile<<"Error in Line-"<<i<<": bgt requires only 1 address level!";
						goto exit;	
					}	
				}
//___________________________________beq instruction____________________________
				else if(inst=="beq")
				{
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": beq requires 1 address level!";
						goto exit;
					}
					if(!(iss>>s2))
					{
						if(u==0)
						ofile<<"10000 "<<s1<<"\n";
						if(u==1)
						{
						if(E==1)
						{
							ifile.seekg(0,ios::beg);
							z=i;i=0;
							while(getline(ifile,s))
							{
								i++;
								stringstream iss(s);
								iss>>s3;iss>>s4;
								s4=s4.substr(0,s4.length()-1);
								if(s3==".encode"&&s4==s1)
								goto again;
							}
							if(s4!=s1)
							{
								ofile<<"Error in Line-"<<z<<": "<<s1<<" -No such level found!";
								goto exit;
							}
						}
						}
					}
					else 
					{
						ofile<<"Error in Line-"<<i<<": beq requires only 1 address level!";
						goto exit;	
					}	
				}
				else if(inst==".main:")
				{
					if(u==0)
					{
						ofile<<inst<<"\n";
						v=i;
					}
				}
			 	else if(inst[0]=='.'&&inst[inst.length()-1]==':')
				{
					if(u==0)
					ofile<<inst<<"\n";
				}
				else if(inst=="call")       //call
				{
					if(u==1)
					call[++ii]=i;
					if(!(iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": call requires 1 address level!";
						goto exit;
					}
					if(!(iss>>s2))
					{
						if(u==0)
						ofile<<"10011 "<<s1<<"\n";
						if(u==1)
						{
							ifile.clear();
							ifile.seekg(0,ios::beg);
							z=i;i=0;
							while(getline(ifile,s))
							{
								i++;
								stringstream iss(s);
								iss>>s3;iss>>s4;
								s4=s4.substr(0,s4.length()-1);
								if(s3==".encode"&&s4==s1)
								goto again;
							}
							if(s4!=s1)
							{
								ofile<<"Error in Line-"<<z<<": "<<s1<<" -No such Function found!";
								goto exit;
							}
						}	
					}
					else 
					{
						ofile<<"Error in Line-"<<i<<": call requires only 1 address level!";
						goto exit;	
					}
				}
				else if(inst=="ret")        //ret  
				{
					if((iss>>s1))
					{
						ofile<<"Error in Line-"<<i<<": ret requires no any address level!";
						goto exit;	
					}
					if(u==0)
					ofile<<"10100 "<<"..............................\n";
					if(u==1)
					{
						ifile.clear();
						ifile.seekg(0,ios::beg);
						i=0;
						for(int j=0;j<call[ii];j++)
						{
							getline(ifile,s);
							i++;
						}
						ii--;
					}	
				}
				for(int j=0;j<14;j++)
				memory[in+j]=r[j];
			}
			else if(what==".print")
			{
				if(!(iss>>s1))
				{
					ofile<<"Error in Line-" <<i<<": One argument required!\n";
					continue;
				}
				if(!(iss>>s2))
				{
					if(s1=="r0"||s1=="ra"||s1=="pc"||s1=="r14"||s1=="r1"||s1=="r2"||s1=="r3"||s1=="r4"||s1=="r5"||s1=="r6"||s1=="r7"||s1=="r8"||s1=="r9"||s1=="r10"||s1=="r11"||s1=="r12"||s1=="r13")
					{
						istringstream(s1.substr(1,s1.length()-1))>>n1;
						if(u==1)
						ofile<<"r"<<n1<<" = "<<r[n1]<<"\n";
					}
					else
					{
						ofile<<"Error in Line-" <<i<<": "<<s1<<" -Invalid register used!\n";
						continue;
					}
				}
				else ofile<<"Error in Line-" <<i<<": Only One argument required!\n";
			}
		}
		ifile.clear();
		ifile.seekg(0,ios::beg);
	}
	}
	cout<<"your code executed Successfully! please check output.txt file!\n\n\n";
	exit:;
}
std::string binary(int n,int x)
{
	string s="";char c;int b,i=0;
	while(x!=0)
	{
		b=x%2;
		x=x/2;
		c=b+'0';
		s=c+s;
		i++;
	}
	for(int j=i;j<n;j++)
	s="0"+s;
	return s;
}
int hextodec(string s)
{
	int k[4];
	for(int i=0;i<4;i++)
	{
		if(s[i]=='A')
		k[i]=10;
		else if(s[i]=='B')
		k[i]=11;
		else if(s[i]=='C')
		k[i]=12;
		else if(s[i]=='D')
		k[i]=13;
		else if(s[i]=='E')
		k[i]=14;
		else if(s[i]=='F')
		k[i]=15;
		else
		k[i]=s[i]-'0';
	}
	return 16*16*16*k[0]+16*16*k[1]+16*k[2]+k[3];
}
