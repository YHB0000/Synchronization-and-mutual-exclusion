#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "RunableThread.h"
#include "Buffer.h"
#ifndef Consumer_h
#define COnsumer_h
class Consumer :public RunableThread
{
	private:
		Buffer* bf;
		FILE* fp;
	protected:
		unsigned Execue()
		{
			std::cout << "Consumer Execue()" << std::endl;
			char buffer[20];
			while (1)
			{
				bf->Read(buffer, 20);
				printf("%s\n", buffer);
				if (0 == strcmp(buffer, "exit"))
				{
					fprintf(fp, "Consumer Received: %s\n", buffer);
					break;		// µÈ´ý¿ØÖÆ×Ö·û½áÊø
				}
				fprintf(fp, "Consumer Received: %s\n", buffer);
			}
			return 0;
		}
	public:
		Consumer()
		{
			this->bf = NULL; 
			fp = NULL;
		}
		Buffer* Init(Buffer* bf, FILE* fp)
		{
			Buffer* hold = this->bf = bf;
			this->bf = bf;
			this->fp = fp;
			return hold;
		}
};
#endif