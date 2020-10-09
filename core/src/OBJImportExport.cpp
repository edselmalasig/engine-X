#include "OBJImportExport.h"

int main() {

   fp = fopen("experiments/elements_rnd/models/cube.obj", "r");
   fscanf(fp, "%s", buff);
   printf("1 : %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("2: %s\n", buff );

   fgets(buff, 255, (FILE*)fp);
   printf("3: %s\n", buff );

   fscanf(fp, "%s", buff);
   printf("4 : %s\n", buff );

   fscanf(fp, "%s", buff);
   printf("5 : %s\n", buff );

   fclose(fp);

}
