
#include <stdio.h>
#include <string.h>


#define DICOSIZE  256
static char *dico[DICOSIZE][3];
static int lang = 1;
static char ret[1024];

const char *gettext(const char *ptMess)
{
  int index = 0; 
  *ret = '\0';
  while (dico[index][0] != NULL)
  {
    if(!strcmp(dico[index][0], ptMess))
    {
      strcpy(ret, dico[index][lang]);
      return ret;
    }
    index++;
  }
  return ret;
}

#define  _(STRING)  gettext(STRING)

#define BUFFSIZE 1024

int resetDico()
{
  for(int i=0;i< (DICOSIZE-1); i++)
  {
    dico[i][0]=NULL;
    dico[i][1]=NULL;
    dico[i][2]=NULL;
  }
}

int initDictionary(char *name)
{
  FILE *file;
  char buffer[BUFFSIZE];

  file = fopen(name, "r");
  if(!file)
    return 0;

  int index = 0;

  resetDico();
  while(fgets(buffer, BUFFSIZE, file)) {
   if (index>=DICOSIZE)
      return 0;

   char *t = strtok(buffer,"\t");
   dico[index][0] = strdup(t);
   t = strtok(NULL,"\t");
   dico[index][1] = strdup(t);
   t = strtok(NULL,"\t");
   dico[index][2] = strdup(t);

   index++;
 }

  fclose(file);
  return 1;
}

int main()
{
  initDictionary("exemple.dic");
  printf(_("Bonjour %s!"),"Toto");
  printf("\n");
}



