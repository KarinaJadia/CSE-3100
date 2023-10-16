#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240
#define MAX_WORD_COUNT 60000                //we have less than 60000 words
#define MAX_WORD_LENGTH 80                //each word is less than 80 letters

//Using these two global variables can be justified :)
char words[MAX_WORD_COUNT][MAX_WORD_LENGTH];        //2-d array to hold all the words
int word_count = 0;                    //number of words, initilized to 0

//Note the words in the dictionary file are sorted
//This fact could be useful
void read_file_to_array(char *filename)
{
    FILE *fp;

    //open the file for reading
    fp = fopen(filename, "r");
    if(fp==NULL)
    {
        printf("Cannot open file %s.\n", filename);
        exit(-1);
    }
    //make sure when each word is saved in the array words,
    //it does not ends with a '\n'
    //see how this is done using fscanf 
    while(!feof(fp))
        fscanf(fp, "%s\n", words[word_count++]);
    fclose(fp);
}

//TODO
//Test wether a string word is in the dictionary
//Return 1 if word is in the dictionary
//Return 0 otherwise
//Be efficient in implementing this function
//Efficiency is needed to pass test cases in limited time
int in_dict(const char *word) {
    int l = 0;
    int r = word_count - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        int place = strcmp(word, words[m]);
        
        if (place == 0) return 1;
        else if (place < 0) r = m - 1;
        else l = m + 1;
    }
    return 0;
}

//TODO
//Use key and shift to decrypt the encrypted message
//len is the length of the encrypted message
//Note the encrypted message is stored as an array of integers (not chars)
//The result is in decrypted
void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted) {
    int dec_index = 0;
    for (int i = 0; i < len; i++){ // loops through message
        int dc = (encrypted[i] ^ key) >> shift; // xors the key with the encrypted character and then shifts it by shift
        if (dc < 32 || dc > 126) { // if it's not printable
            dc = ' ';
        }
        decrypted[dec_index++] = (char)dc;
    }
    decrypted[len] = '\0';
    //printf("PRONT decy message: %s\n", decrypted);
} 

//TODO
//calculate a score for a message msg
//the score is used to determine whether msg is the original message
int message_score(const char *msg) {
    int score = 0;
    int i = 0;
    while (msg[i] != '\0') {
        int wordStart = i;
        while (msg[i] != ' ' && msg[i] != '\0') {
            i++;
        }
        int wordEnd = i;
        char word[MAX_WORD_LENGTH]; // stores current word
        if (wordEnd > wordStart) {
            strncpy(word, msg + wordStart, wordEnd - wordStart); // extract word
            word[wordEnd - wordStart] = '\0';

            if (in_dict(word)) score++; // check if in dictionary
        }
        if (msg[i] == ' ') i++; // move to next word
    }
    //printf("PRONT score: %d\n", score);
    return score;
}

//search using all the (key, shift) combinations
//to find the original message
//result is saved in message
void search(const int *encrypted, int len, char *message)
{
	char decrypted[MAX];

    int max_score = 0;
    strcpy(message, "");
    for(unsigned char k = 0; k < 255; k++)
    {
        for(unsigned char shift = 0; shift <= 24; shift++)
        {
            decryption(k, shift, encrypted, len, decrypted);
			int score = message_score(decrypted);
            //printf("Key: %d, Encrypted Message: %d, Decrypted Message: %s\n", k, encrypted, decrypted);
			if(score > max_score)
			{	
				max_score = score;
				strcpy(message, decrypted);
			}
        }
    }
}

//TODO
//read the encrypted message from the file to encrypted
//return number of bytes read
int read_encrypted(char *filename, int *encrypted) {
    int fil = open(filename, O_RDONLY);
    if (fil < 0) exit(-1); // can't read file so leave

    int l = read(fil, encrypted, MAX * sizeof(int));
    close(fil);
    return l / sizeof(int);
}

//Do not change the main() function
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s encrypted-message\n", argv[0]);
		return 0;
	}

	read_file_to_array("dict.txt");

	int encrypted[MAX];
	int len = read_encrypted(argv[1], encrypted);
	
	char message[MAX];
	strcpy(message, "");
	search(encrypted, len, message);
	//printf("%s\n", message);
    for (int i = 0; message[i] != '\0'; i++) {
        if (i < len-5 && message[i+5] == ' ' && message[i+4] == ' ' && message[i+3] == ' ' && message[i+2] == ' ' && message[i+1] == ' ' && message[i] == ' ') {
            printf("—");
            i += 6;
        }
        if (i < len-2 && message[i+2] == ' ' && message[i+1] == ' ' && message[i] == ' ') {
            printf("’");
            i += 3;
        }
        printf("%c", message[i]);
    }
    printf("\n");
	return 0;
}