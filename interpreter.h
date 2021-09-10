#include <math.h>
#include <string>


void function(float split, float zoom, float Width, float Height, int partitionsize, std::string function, float* points);
std::string interpreter(float x, std::string function);
std::string hierarchyO(float x, std::string function);
std::string hierarchyF(float x, std::string function);



void function(float split, float zoom, float Width, float Height, int partitionsize, std::string function, float* points)
{
	float t;
	for(int iteration = 0; iteration<partitionsize; iteration+=2)
	{
		t = (2*(float)iteration/(partitionsize-2)-1)*Width+split;
		points[iteration] = t;
		points[iteration+1] = -std::stof(interpreter(t,function));
	}
	
	
}


std::string interpreter(float x, std::string function)
{
	
	return hierarchyF(x,function);
}



std::string hierarchyO(float x, std::string function)
{
	std::string ohierarchy[6] = {"-","+","/","*","^","&"}; //hierarchy of binary operators	
	int findcap;
	
	for(int i = 0; i<6; i++)
	{
		 findcap = function.rfind(ohierarchy[i]);
		 
		 
		if((unsigned int)findcap != std::string::npos)
		{
			
			
			
			switch(i)
			{
				case 0:

					for(int j = 48; j<58; j++)
					{
						if(function[findcap-1] == j || function[findcap-1] == 120)
						{
							return std::to_string(std::stof(interpreter(x,function.substr(0,findcap)))-std::stof(interpreter(x,function.substr(findcap+1,function.size()-findcap-1))));
						}
							
						
					}
					return interpreter(x,function.substr(0,findcap)+"&"+function.substr(findcap+1,function.size()-findcap-1));
					 
					break;
				
				case 1: 
					return std::to_string(std::stof(interpreter(x,function.substr(0,findcap)))+std::stof(interpreter(x,function.substr(findcap+1,function.size()-findcap-1))));
					break;
				
				case 2: 
					return std::to_string(std::stof(interpreter(x,function.substr(0,findcap)))/std::stof(interpreter(x,function.substr(findcap+1,function.size()-findcap-1))));
					break;
				
				case 3: 
					return std::to_string(std::stof(interpreter(x,function.substr(0,findcap)))*std::stof(interpreter(x,function.substr(findcap+1,function.size()-findcap-1))));
					break;
					
				case 4: 
					return std::to_string(pow(std::stof(interpreter(x,function.substr(0,findcap))),std::stof(interpreter(x,function.substr(findcap+1,function.size()-findcap-1)))));
					break;
					
				case 5:
					return std::to_string(-std::stof(interpreter(x,function.substr(1,function.size()-1))));
					break;

				
				
				
			}
			
		}
		
		

		
	}	
	
	
	if(function == "x")
	{
		return std::to_string(x);
	}
	
	if(function == "-x" || function == "&x")
	{
		return std::to_string(-x);
	}
	
	return function;
	
}


std::string hierarchyF(float x, std::string function)
{
	std::string fhierarchy[6] = {"sin","cos","tan","abs","sqrt","("}; //hierarchy of functions (R to R)
	int findcap,findtail,extrafind,space;
	std::string newfunction;
	for(int i = 0; i < 6; i++)
	{
	
		findcap = function.find(fhierarchy[i]);
		
		if((unsigned int)findcap != std::string::npos)
		{
			
			
			newfunction = function.substr(0,findcap); //first section of the  (cap)
			extrafind = findcap+fhierarchy[i].size();
			findtail = function.find(")",findcap);

			while((int)function.find("(",extrafind+1)<findtail&&function.find(")",findtail+1)!= std::string::npos)
			{
				findtail = function.find(")",findtail+1);
				extrafind = function.find("(",findcap+1);
			}

			space = fhierarchy[i].size()+1;
			switch(i)
			{	
				case 0:
					newfunction += std::to_string(sin(std::stof(interpreter(x,function.substr(findcap+space,findtail-findcap-space))))); //middle in each case
					break;
					
				case 1:
					newfunction += std::to_string(cos(std::stof(interpreter(x,function.substr(findcap+space,findtail-findcap-space))))); 
					break;	

				case 2:
					newfunction += std::to_string(tan(std::stof(interpreter(x,function.substr(findcap+space,findtail-findcap-space))))); 
					break;		
					
				case 3:
					newfunction += std::to_string(fabs(std::stof(interpreter(x,function.substr(findcap+space,findtail-findcap-space))))); 
					break;		
					
				case 4:
					newfunction += std::to_string(sqrt(std::stof(interpreter(x,function.substr(findcap+space,findtail-findcap-space))))); 
					break;	
				
				case 5:
					newfunction += interpreter(x,function.substr(findcap+1,findtail-findcap-1));
					break;
				
			}
			
			
			newfunction +=function.substr(findtail+1,function.size()); //last section of the string (tail)
			return interpreter(x,newfunction);
			
		}	
		
		
		
		
	}
	
	
	
	return hierarchyO(x,function);
	
}






