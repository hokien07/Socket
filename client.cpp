//
// Created by HOKIEN on 5/18/2017.
//

void UploadFile(SOCKET Socket){
    if(Socket == NULL){
        return;
    }
    while(1){
        char filename[1024];
        recv(Socket, filename, sizeof(filename), 0);
        if(filename[0] == '.'){
            break;
        }
        FILE* fp = fopen(filename, "r");
        fseek(fp, 0, SEEK_END);
        long FileSize = ftell(fp);
        char GotFileSize[1024];
        _itoa_s(FileSize, GotFileSize, 10);
        send(Socket, GotFileSize, 1024, 0);
        rewind(fp);
        long SizeCheck = 0;
        char* mfcc;
        if(FileSize > 1499){
            mfcc = (char*)malloc(1500);
            while(SizeCheck < FileSize){
                int Read = fread_s(mfcc, 1500, sizeof(char), 1500, fp);
                int Sent = send(Socket, mfcc, Read, 0);
                SizeCheck += Sent;
            }
        }
        else{
            mfcc = (char*)malloc(FileSize + 1);
            fread_s(mfcc, FileSize, sizeof(char), FileSize, fp);
            send(Socket, mfcc, FileSize, 0);
        }
        fclose(fp);
        Sleep(500);
        free(mfcc);
    }
    return;
}