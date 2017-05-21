#include <iostream>

using namespace std;
void DownloadFile(SOCKET Socket){
    if(Socket == NULL){
        return;
    }
    while(1){
        printf("Input local filename: ");
        char localfile[1024];
        gets_s(localfile, 1024);
        if(localfile[0] == '.'){
            send(Socket, localfile, sizeof(localfile), 0);
            break;
        }
        printf("Input remote filename: ");
        char filename[1024];
        gets_s(filename, 1024);
        if(filename[0] == '.'){
            send(Socket, filename, sizeof(filename), 0);
            break;
        }
        send(Socket, filename, sizeof(filename), 0);
        char GotFileSize[1024];
        recv(Socket, GotFileSize, 1024, 0);
        long FileSize = atoi(GotFileSize);
        long SizeCheck = 0;
        FILE *fp = fopen(localfile, "w");
        char* mfcc;
        if(FileSize > 1499){
            mfcc = (char*)malloc(1500);
            while(SizeCheck < FileSize){
                int Received = recv(Socket, mfcc, 1500, 0);
                SizeCheck += Received;
                fwrite(mfcc, 1, Received, fp);
                fflush(fp);
                printf("Filesize: %d\nSizecheck: %d\nReceived: %d\n\n", FileSize, SizeCheck, Received);
            }
        }
        else{
            mfcc = (char*)malloc(FileSize + 1);
            int Received = recv(Socket, mfcc, FileSize, 0);
            fwrite(mfcc, 1, Received, fp);
            fflush(fp);
        }
        fclose(fp);
        Sleep(500);
        free(mfcc);
    }
}