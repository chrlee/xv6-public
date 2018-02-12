// CS3224
// by: Christian lee
// net-id: CJL573

#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
sed(int fd, char *removed, char *inserted, char *name)
{
  int i, j, n, fdw;
  int wc;
  int valid;
  if(fd == 0) fdw = 1;
  else fdw = open(name, 2);
  wc = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i < n-strlen(removed); ++i){
    	valid = 0;
	for(j = 1; j < strlen(removed); ++j){
           if(buf[i+j-1] != removed[j]) valid = 1;
	}
	if(valid == 0){
          for(j = 1; j < strlen(removed); ++j){
            buf[i+j-1] = inserted[j];
	  }
	  i+=j-1;
          wc++;
	}
    }
    if(write(fdw, buf, n) != n){
        printf(1, "sed: %s write error\n", name);
	exit();
    }
  }

  if(n < 0){
    printf(1, "\nsed: %s read error\n", name);
    exit();
  }
  printf(1, "\nFound and Replaced %d occurences\n", wc);
}

int
main(int argc, char *argv[])
{
  int fd;

  if(argc <= 1){
    sed(0, "-the", "-xyz",  "");
  }
  else if(argc == 2){
    if((fd = open(argv[1], 2)) < 0){
      printf(1, "sed: cannot open %s\n", argv[1]);
    }
    else{
      sed(fd, "-the", "-xyz", argv[1]);
      close(fd);
    }
  }
  else if(argc == 3){
    sed(0, argv[1], argv[2], "");
  }
  else if(argc == 4){
    if(argv[1][0] != '-' || argv[2][0] != '-'){
      printf(1, "sed: input error\n");
    }
    else if((fd = open(argv[3], 2)) < 0){
      printf(1, "sed: cannot open %s\n", argv[3]);
    }
    else{
      sed(fd, argv[1], argv[2], argv[3]);
      close(fd);
    }
  }
  exit();
}
