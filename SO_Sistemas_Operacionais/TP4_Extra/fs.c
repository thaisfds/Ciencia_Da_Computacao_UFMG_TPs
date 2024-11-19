#include "fs.h"

#include <errno.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>   

//============================ INFO TESTS ============================//
/*
test1.c -> test fs_format and fs_close
test2.c -> test fs_format and fs_close
test3.c -> components of sb after fs_format
test4.c -> test fs_open, fs_get_block and fs_put_block
test5.c -> test fs_write_file, fs_list_dir, fs_unlink, fs_rmdir
*/

//============================ DEFINES ============================//
#define MAGICNUMBER 0xdcc605f5

//============================ REFERENCE ============================//
// erros: https://man7.org/linux/man-pages/man3/errno.3.html
//Chapter 12 - File-System Implementation - Silberschatz
// erros: https://www.bing.com/chat

//============================ AUX FUNCTIONS ============================//    

int fsOpen; 

//============================ FUNCTIONS FS_ ============================//


/*
Constrói um novo sistema de arquivos no arquivo fname. O arquivo fname deve 
existir no sistema de arquivos do sistema operacional. O sistema de arquivos 
DCC605FS criado em fname deve usar blocos de tamanho blocksize; o número de 
blocos no sistema de arquivos deve ser calculado automaticamente baseado no 
tamanho do arquivo fname. O sistema de arquivos deve ser inicializado com um 
diretório raiz vazio; o nome do diretório raiz deve ser "/" como em sistemas UNIX.

Esta função retorna NULL em caso de erro e guarda em errno o código de erro 
apropriado. Se o tamanho do bloco for menor que MIN_BLOCK_SIZE, a função falha 
e atribui EINVAL a errno. Se existir espaço em fname insuficiente para armazenar 
MIN_BLOCK_COUNT blocos, a função falha e atribui ENOSPC a errno. Execute man errno 
no Linux para estudar sobre erros do sistema. */

struct superblock * fs_format(const char *fname, uint64_t blocksize){
    //verify if the blocksize is valid
    if(blocksize < MIN_BLOCK_SIZE){
        errno = EINVAL; //invalid argument
        return NULL;
    }

    //open the file
    FILE *file = fopen(fname, "r");
    if(file == NULL){
        errno = ENOENT; // no such file or directory
        return NULL;
    }

    //calculate the file size and close the file
    fseek(file, 0, SEEK_END);
    uint64_t fileSize = ftell(file);
    fclose(file);

    //calculate the number of blocks and check if there is enough space
    uint64_t numBlocks = fileSize / blocksize;
    if(numBlocks < MIN_BLOCK_COUNT){
        errno = ENOSPC; //no space left on device
        return NULL;
    }

    fsOpen = 0;

    //------------- superblock initialization -------------//

    struct superblock *sb = (struct  superblock *)malloc(blocksize);
    if(sb == NULL){
        errno = ENOMEM; //cannot allocate memory
        return NULL;
    }

    //let the important data at the beginning of the block
    sb->magic = MAGICNUMBER; //magic number
    sb->blks = numBlocks; //number of blocks
    sb->blksz = blocksize; //block size
    sb->freeblks = numBlocks - 3; //number of free blocks
    sb->freelist = 3; //first free block
    sb->root = 2; //root directory (inode)
    sb->fd = open(fname, O_RDWR, 0777); //file descriptor

    //verify if the file descriptor was opened successfully
    if(sb->fd == -1){
        free(sb);
        errno = EBADF; //bad file descriptor
        return NULL;
    }

    //write the superblock to the file
    if(write(sb->fd, sb, blocksize) == -1){
        close(sb->fd);
        free(sb);
        errno = EPERM; //operation not permitted
        return NULL;
    }

    //------------- root nodeinfo initialization -------------//

    struct nodeinfo *rootNodeInfo = (struct nodeinfo *)malloc(blocksize);
    if(rootNodeInfo == NULL){
        errno = ENOMEM; //cannot allocate memory
        return NULL;
    }

    rootNodeInfo->size = 0; //root directory is empty

    //copy the root nodeinfo to the file
    strcpy(rootNodeInfo->name, "/\0"); //root directory name
    if(write(sb->fd, rootNodeInfo, blocksize) == -1){
        free(rootNodeInfo);
        errno = EPERM; //operation not permitted
        return NULL;
    }

    free(rootNodeInfo); //free memory after writing to the file

    //------------- root inode initialization -------------//

    struct inode *rootInode = (struct inode *)malloc(blocksize);
    if(rootInode == NULL){
        errno = ENOMEM; //cannot allocate memory
        return NULL;
    }

    rootInode->mode = IMDIR; //directory inode
    rootInode->parent = 2; //root directory
    rootInode->meta = 1; //root directory
    rootInode->next = 0; //no next inode
    memset(rootInode->links, 0, sizeof(uint64_t)); //no links
    
    if(write(sb->fd, rootInode, blocksize) == -1){
        free(rootInode);
        errno = EPERM; //operation not permitted
        return NULL;
    }


    free(rootInode); //free memory after writing to the file

    //------------- freepage initialization -------------//

    struct freepage* freePage;
    for (int i = 3; i < numBlocks; i++){
        //if is the last block
        if(i == numBlocks - 1){
            freePage->next = 0;
        }else{
            freePage->next = i + 1;
        }

        //write and pass to the next block
        if(write(sb->fd, freePage, blocksize) == -1){
            free(freePage);
            errno = EPERM; //operation not permitted
            return NULL;
        }
    }

    return sb;    

}

/* Abre o sistema de arquivos em fname e retorna seu superbloco. 
Retorna NULL em caso de erro e carrega o código de erro em errno. 
Caso o superbloco em fname não contenha o marcador de sistemas de 
arquivo DCC605FS (0xdcc605f5), a função falha e atribui EBADF a errno.

Note que suas funções fs_format e fs_open não devem permitir que o 
mesmo sistema de arquivo seja aberto duas vezes, para evitar corrupção 
dos arquivos. No caso do sistema de arquivos já estar aberto, ambas 
funções devem falhar e atribuir EBUSY a errno.*/

struct superblock * fs_open(const char *fname){

    if(fsOpen == 1){
        errno = EBUSY; //device or resource busy
        return NULL;
    }

    //cache the file descriptor
    int fd = open(fname, O_RDWR); 

    if(fd == -1){
        errno = ENOENT; //no such file or directory
        return NULL;
    }


    //read the superblock
    struct superblock *sb = malloc(sizeof(struct superblock));

    if(sb == NULL){
        close(fd);
        errno = ENOMEM; //cannot allocate memory
        return NULL;
    }


    lseek(fd, 0, SEEK_SET); //set the file pointer to the beginning
    if(read(fd, sb, sizeof(struct superblock)) == -1){
        close(fd);
        free(sb);
        errno = EPERM; //operation not permitted
        return NULL;
    }

    //check if sb isn't from 0xdcc605f5
    if(sb->magic != MAGICNUMBER){
        close(fd);
        free(sb);
        errno = EBADF; //bad file descriptor
        return NULL;
    }

    fsOpen = 1; //set the fsOpen to 1

    return sb;
}

/* Fecha o sistema de arquivos apontado por sb. Libera toda a memória 
e recursos alocados à estrutura sb. Retorna zero se não houver erro. 
Em caso de erro, um valor negativo é retornado e errno indica o erro. 
Se sb não tiver o marcador 0xdcc605f5, atribui EBADF a errno. */
int fs_close(struct superblock *sb){
    //check if sb exists
    if(sb == NULL){
        errno = EINVAL; //invalid argument
        return -1;
    }

    //check if sb isn't from 0xdcc605f5
    if(sb->magic != MAGICNUMBER){
        errno = EBADF; //bad file descriptor
        return -1;
    }

    //close the file descriptor
    if(close(sb->fd) == -1){
        errno = EBADF; //bad file descriptor
        return -1;
    }

    fsOpen = 0; //set the fsOpen to 0

    free(sb); //free the superblock memory

    return 0;

}

/* Pega um ponteiro para um bloco livre no sistema de arquivos sb. 
O bloco retornado é retirado da lista de blocos livres do sistema de arquivos. 
Retorna zero caso não existam mais blocos livres; retorna (uint64_t)-1 
e atribui errno caso um erro ocorra. */
uint64_t fs_get_block(struct superblock *sb){

    //chack if the sb exists
    if(sb == NULL){
        errno = EINVAL; //invalid argument
        return (uint64_t) -1;
    }

    //check if sb isn't from 0xdcc605f5
    if(sb->magic != MAGICNUMBER){
        errno = EBADF; //bad file descriptor
        return (uint64_t) -1;
    }

    //check if there are free blocks
    if(sb->freeblks == 0){
        errno = ENOSPC; //no space left on device
        return (uint64_t) 0;
    }

    //return the first free block
    lseek(sb->fd,sb->freelist * sb->blksz, SEEK_SET);
    struct freepage *fp = (struct freepage *)malloc(sb->blksz);

    if(fp == NULL){
        errno = ENOMEM; //cannot allocate memory
        return (uint64_t) -1;
    }

    //read the first free block
    if(read(sb->fd, fp, sb->blksz) == -1){
        free(fp);
        errno = EPERM; //operation not permitted
        return (uint64_t) -1;
    }

    //get the first free block
    uint64_t freeBlock = sb->freelist; //get the first free block
    sb->freelist = fp->next; //point to the next free block
    sb->freeblks--; //decrement the number of free blocks

    //write the superblock to the file
    lseek(sb->fd, 0, SEEK_SET);

    if(write(sb->fd, sb, sb->blksz) == -1){
        errno = EPERM; //operation not permitted
        return (uint64_t) -1;
    }
    
    free(fp);

    //return 0;
    return freeBlock;  
      
}

/* Retorna o bloco de número block para a lista de blocos livres do 
sistema de arquivo sb. Retorna zero em caso de sucesso e um valor 
negativo em caso de erro. Código de erro, se ocorrer, é salvo em errno. */
int fs_put_block(struct superblock *sb, uint64_t block){
    
    //chack if the sb exists
    if(sb == NULL){
        errno = EINVAL; //invalid argument
        return -1;
    }

    //check if sb isn't from 0xdcc605f5
    if(sb->magic != MAGICNUMBER){
        errno = EBADF; //bad file descriptor
        return -1;
    }

    //check if the block is valid
    if(block <= 0){
        errno = EINVAL; //invalid argument
        return -1;
    }

    //back the block to the free blocks
    struct freepage *fp = (struct freepage *)malloc(sb->blksz);
    if(fp == NULL){
        errno = ENOMEM; //cannot allocate memory
        return -1;
    }

    fp->next = sb->freelist; //point to the next free block
    lseek(sb->fd, block * sb->blksz, SEEK_SET);
    if(write(sb->fd, fp, sb->blksz) == -1){
        free(fp);
        errno = EPERM; //operation not permitted
        return -1;
    }

    sb->freelist = block; //set the block as the first free block
    sb->freeblks++; //increment the number of free blocks

    //write the superblock to the file
    lseek(sb->fd, 0, SEEK_SET);
    if(write(sb->fd, sb, sb->blksz) == -1){
        free(fp);
        errno = EPERM; //operation not permitted
        return -1;
    }    

    return 0;
}