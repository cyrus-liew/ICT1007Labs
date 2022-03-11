#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>  
 
int main(){
    int CIPHER_KEY;
    FILE *orig, *decrypt, *final;

    char name[30] = "encrypted.txt", ch;
    char txt[100] = "MPYZA DPAO UPUL HUK AOLU DPAO TPUBZ ADV PZ ZHTL HZ ZLCLU";

    //orig = fopen(name, "r+");
    //decrypt = fopen("decrypted.txt", "w");
    
    /*
    for(CIPHER_KEY = 1; CIPHER_KEY < 26; CIPHER_KEY++){
        while(1) { 
            ch = fgetc(orig); 
            if(ch == EOF) { 
                break; 
            } 
            else { 
                if (ch != ' ') 
                { 
                    ch = ch + 3 - CIPHER_KEY;
                    if(ch < 65){
                        ch = ch + 26;
                    }
                    else if(ch > 90){
                        ch = ch % 90 + 64;
                    }
                } 
                fputc(ch, decrypt); 
            } 
        }
        fseek(orig, 0 ,SEEK_SET);
        fputc(10, decrypt);
    }
    */
    
    CIPHER_KEY = 10;

    //fseek(orig, 0 ,SEEK_SET);

    final = fopen("Lab_SetD1_Q3.txt", "w");
    fprintf(final, "%d -%d\n", CIPHER_KEY, 3);
    int len = strlen(txt);
    for(int i = 0; i < len; i++){
        ch = txt[i];

        if (ch != ' ') 
        { 
            ch = ch + 3 - CIPHER_KEY;
            if(ch < 65){
                ch = ch + 26;
            }
            else if(ch > 90){
                ch = ch % 90 + 64;
            }
        } 
        fputc(ch, final); 
    }

    /*
    while(1) { 
            ch = fgetc(orig);
            if(ch == EOF) { 
                break; 
            } 
            else { 
                if (ch != ' ') 
                { 
                    ch = ch + 3 - CIPHER_KEY;
                    if(ch < 65){
                        ch = ch + 26;
                    }
                    else if(ch > 90){
                        ch = ch % 90 + 64;
                    }
                } 
                fputc(ch, final); 
            } 
        }
    */

    //fclose(orig);
    //fclose(decrypt);
    fclose(final);
    return 0;
}