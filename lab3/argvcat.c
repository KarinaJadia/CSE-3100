//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // TODO 

    char* store= (char*) malloc(sizeof(char)*((2*(strlen(s1)+strlen(s2)))+1));
    strcpy(store,s1);
    strcat(store,s2);

    
    return store;
}

int main(int argc, char *argv[])
{
    char    *s;
    char    *o;
    

    s = my_strcat("", argv[0]);
    //store= (char*) malloc(sizeof(char)*(2*(strlen(s1)+strlen(s2))));
    for (int i = 1; i < argc; i ++) {
        o=s;
        s = my_strcat(s, argv[i]);
        free(o);
        
    }


    printf("%s\n", s);
    free(s);
    
    return 0;
}