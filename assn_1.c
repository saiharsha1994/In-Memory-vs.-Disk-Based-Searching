#include<stdio.h>
#include<sys/time.h>

struct timeval tm1, tm2;

void memoryLinearSearch(char keys[],char seeks[]){
	FILE *inp,*opt;
	int i=0, j=0;
	inp = fopen( keys, "rb");
	opt = fopen( seeks, "rb");
	fseek(opt, 0L, SEEK_END);
        int sizeSeek = ftell(opt)/sizeof(int);
        fseek(opt, 0L, SEEK_SET);
	gettimeofday( &tm1, NULL );
        fseek(inp, 0L, SEEK_END);
        int sizeKey = ftell(inp)/sizeof(int);
        fseek(inp, 0L, SEEK_SET);
        int key[sizeKey];
        fread(&key, sizeof( int ), sizeKey,  inp);
	int seek[sizeSeek];
        fread(&seek, sizeof( int ), sizeSeek,  opt);
	int hit[sizeSeek];
	for(i=0; i<sizeSeek; i++){
		for(j=0; j<sizeKey; j++){
			if(seek[i]==key[j]){
				hit[i]=1;
				break;
			}
			else hit[i]=0;
		}
	}
	gettimeofday( &tm2, NULL );
	for(i=0; i<sizeSeek; i++){
		if(hit[i]==0)	printf( "%12d: No\n", seek[i] );
		else	printf( "%12d: Yes\n", seek[i] );
	}
	if(tm2.tv_usec<tm1.tv_usec )	 printf( "Time: %ld.%06ld\n",(tm2.tv_sec-tm1.tv_sec-1),(tm2.tv_usec+1000000-tm1.tv_usec));
	else	printf( "Time: %ld.%06ld\n",tm2.tv_sec-tm1.tv_sec,tm2.tv_usec-tm1.tv_usec );
fclose(inp);
fclose(opt);
}

void memoryBinarySearch(char keys[],char seeks[]){
	FILE *inp,*opt;
        int i=0, j=0;
        inp = fopen( keys, "rb");
        opt = fopen( seeks, "rb");
	fseek(opt, 0L, SEEK_END);
        int sizeSeek = ftell(opt)/sizeof(int);
        fseek(opt, 0L, SEEK_SET);
	gettimeofday( &tm1, NULL );	
        fseek(inp, 0L, SEEK_END);
        int sizeKey = ftell(inp)/sizeof(int);
        fseek(inp, 0L, SEEK_SET);
        int key[sizeKey];
        fread(&key, sizeof( int ), sizeKey,  inp);
        int seek[sizeSeek];
        fread(&seek, sizeof( int ), sizeSeek,  opt);
        int hit[sizeSeek];
        for(i=0; i<sizeSeek; i++){
		int left = 0, right = sizeKey-1;
                while(left<=right){
			int mid = left+(right-left)/2;
                        if(seek[i] == key[mid]){
                                hit[i]=1;
                                break;
                        }
                        else if(seek[i] < key[mid]){
			 	hit[i] = 0;
				right = mid - 1;
			}
			else if(seek[i] > key[mid]){
				hit[i] = 0;
				left = mid + 1;
			}
                }
        }
	gettimeofday( &tm2, NULL );
        for(i=0; i<sizeSeek; i++){
                if(hit[i]==0)   printf( "%12d: No\n", seek[i] );
                else    printf( "%12d: Yes\n", seek[i] );
        }
	if(tm2.tv_usec<tm1.tv_usec )     printf( "Time: %ld.%06ld\n",(tm2.tv_sec-tm1.tv_sec-1),(tm2.tv_usec+1000000-tm1.tv_usec));
        else    printf( "Time: %ld.%06ld\n",tm2.tv_sec-tm1.tv_sec,tm2.tv_usec-tm1.tv_usec );
fclose(inp);
fclose(opt);
}

void diskLinearSearch(char keys[],char seeks[]){
	FILE *inp,*opt;
        int i=0, j=0;
        inp = fopen( keys, "rb");
        opt = fopen( seeks, "rb");
        fseek(inp, 0L, SEEK_END);
        int sizeKey = ftell(inp)/sizeof(int);
        fseek(inp, 0L, SEEK_SET);
        fseek(opt, 0L, SEEK_END);
        int sizeSeek = ftell(opt)/sizeof(int);
        fseek(opt, 0L, SEEK_SET);
        int seek[sizeSeek];
        fread(&seek, sizeof( int ), sizeSeek,  opt);
        int hit[sizeSeek];
	gettimeofday( &tm1, NULL );
	for(i=0; i<sizeSeek; i++){
		int element = 0;
		fseek(inp, 0L, SEEK_SET);
                while(!feof(inp)){
			fread(&element, sizeof( int ), 1, inp);
                        if(seek[i]==element){
                                hit[i]=1;
                                break;
                        }
                        else hit[i]=0;
                }
        }
	gettimeofday( &tm2, NULL );
        for(i=0; i<sizeSeek; i++){
                if(hit[i]==0)   printf( "%12d: No\n", seek[i] );
                else    printf( "%12d: Yes\n", seek[i] );
        }
	if(tm2.tv_usec<tm1.tv_usec )     printf( "Time: %ld.%06ld\n",(tm2.tv_sec-tm1.tv_sec-1),(tm2.tv_usec+1000000-tm1.tv_usec));
        else    printf( "Time: %ld.%06ld\n",tm2.tv_sec-tm1.tv_sec,tm2.tv_usec-tm1.tv_usec );
fclose(inp);
fclose(opt);
}

void diskBinarySearch(char keys[],char seeks[]){
	FILE *inp,*opt;
        int i=0, j=0;
        inp = fopen( keys, "rb");
        opt = fopen( seeks, "rb");
        fseek(inp, 0L, SEEK_END);
        int sizeKey = ftell(inp)/sizeof(int);
        fseek(inp, 0L, SEEK_SET);
        fseek(opt, 0L, SEEK_END);
        int sizeSeek = ftell(opt)/sizeof(int);
        fseek(opt, 0L, SEEK_SET);
        int key[sizeKey];
        fread(&key, sizeof( int ), sizeKey,  inp);
        int seek[sizeSeek];
        fread(&seek, sizeof( int ), sizeSeek,  opt);
        int hit[sizeSeek];
	gettimeofday( &tm1, NULL );
        for(i=0; i<sizeSeek; i++){
                int left = 0, right = sizeKey-1, element = 0;
                while(left<=right){
			fseek(inp, 0L, SEEK_SET);
                        int mid = left+(right-left)/2;
			fseek(inp, sizeof( int )*mid , SEEK_SET);
			fread(&element, sizeof( int ), 1, inp);
                        if(seek[i] == element){
                                hit[i]=1;
                                break;
                        }
                        else if(seek[i] < element){
                                hit[i] = 0;
                                right = mid - 1;
                        }
                        else if(seek[i] > element){
                                hit[i] = 0;
                                left = mid + 1;
                        }
                }
        }
	gettimeofday( &tm2, NULL );
        for(i=0; i<sizeSeek; i++){
                if(hit[i]==0)   printf( "%12d: No\n", seek[i] );
                else    printf( "%12d: Yes\n", seek[i] );
        }
	if(tm2.tv_usec<tm1.tv_usec )     printf( "Time: %ld.%06ld\n",(tm2.tv_sec-tm1.tv_sec-1),(tm2.tv_usec+1000000-tm1.tv_usec));
        else    printf( "Time: %ld.%06ld\n",tm2.tv_sec-tm1.tv_sec,tm2.tv_usec-tm1.tv_usec );
fclose(inp);
fclose(opt);
}

int main(int argc, char *argv[]){
	if(strcmp( argv[1], "--mem-lin") == 0 )
		memoryLinearSearch(argv[2],argv[3]);
	else if(strcmp( argv[1], "--mem-bin") == 0 )
		memoryBinarySearch(argv[2],argv[3]);
	else if(strcmp( argv[1], "--disk-lin") == 0 )
		diskLinearSearch(argv[2],argv[3]);
	else if(strcmp( argv[1],  "--disk-bin") == 0 )
		diskBinarySearch(argv[2],argv[3]);
	else	printf("Enter the parameters correctly\n");
	return 0;
}

