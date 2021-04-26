#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
// init_command to .data
char cmd[4096] = "\x00";

// init_args to .data
char arch[255] = "\x00";
char support[255] = "\x00";
char image[255] = "\x00";
char kernel[255] = "\x00";
char initrd[255] = "\x00";
char memory[255] = "\x00";
char append[255] = "\x00";
char device[255] = "\x00";
char net_mode[255] = "\x00";
char net_port[255] = "\x00";

void system_Cmd(char *cmd){
    char buf[1024];
    FILE *fp;
    fp = popen(cmd,"r");
    while(fgets(buf,sizeof(buf),fp) != NULL){
        printf("%s",buf);
    }
    puts("<br>");
}


int split(char dst[][80], char* str, const char* spl)
{
    int n = 0;
    char *result = NULL;
    result = strtok(str, spl);
    while( result != NULL )
    {
        strcpy(dst[n++], result);
        result = strtok(NULL, spl);
    }
    return n;
}


void setCmd(char *arch, char *support, char *image, char *kernel, char *initrd, char *append, char *memory, char *device, char *net_mode, char *net_port){
    snprintf(cmd,13,"%s","qemu-system-");
    snprintf(cmd+strlen(cmd),strlen(arch)+1,"%s",arch);
    snprintf(cmd+strlen(cmd),4+1,"%s"," -M ");
    snprintf(cmd+strlen(cmd),strlen(support)+1,"%s",support);
    snprintf(cmd+strlen(cmd),6+1,"%s"," -hda ");
    snprintf(cmd+strlen(cmd),strlen(image)+1,"%s",image);
    snprintf(cmd+strlen(cmd),9+1,"%s"," -kernel ");
    snprintf(cmd+strlen(cmd),strlen(kernel)+1,"%s",kernel);
    snprintf(cmd+strlen(cmd),4+1,"%s"," -m ");
    snprintf(cmd+strlen(cmd),strlen(memory)+1,"%s",memory);
    snprintf(cmd+strlen(cmd),10+1,"%s"," -append '");
    snprintf(cmd+strlen(cmd),strlen(append)+1,"%s",append);
    snprintf(cmd+strlen(cmd),4+1,"%s","' ");
    snprintf(cmd+strlen(cmd),11+1,"%s","-nographic ");
    snprintf(cmd+strlen(cmd),8+1,"%s","-device ");
    snprintf(cmd+strlen(cmd),strlen(device)+1,"%s",device);
    snprintf(cmd+strlen(cmd),17+1,"%s"," -netdev user,id=");
    snprintf(cmd+strlen(cmd),5+1,"%s","net0,");

    
    char port[10][80];
    int port_cnt = split(port, net_port, ",");
    for (int i = 0; i < port_cnt; i++){
        char safe_port[5] = "\x00";
        snprintf(safe_port,5,"%d",atoi(port[i])); //Defense command injection
        if(i == port_cnt-1){
            snprintf(cmd+strlen(cmd),20+sizeof(port)*2+1,"hostfwd=tcp::%s-:%s",safe_port,safe_port);
        }else{
            snprintf(cmd+strlen(cmd),20+sizeof(port)*2+1,"hostfwd=tcp::%s-:%s,",safe_port,safe_port);
        }
    }

}


int cgiMain() {
    //set HTTP header.
    cgiHeaderContentType("text/html");
    fprintf(cgiOut, "<HTML><HEAD>\n");
    fprintf(cgiOut, "<TITLE>My Qemu</TITLE><meta charset='utf-8'></HEAD>\n");
    fprintf(cgiOut, "<BODY>");
    cgiFormString("arch", arch, 240);
    cgiFormString("support", support, 240);
    cgiFormString("image", image, 240);
    cgiFormString("kernel", kernel, 240);
    cgiFormString("initrd", initrd, 240);
    cgiFormString("append", append, 240);
    cgiFormString("memory", memory, 240);
    cgiFormString("device", device, 240);
    cgiFormString("net_mode", net_mode, 240);
    cgiFormString("net_port", net_port, 240);

    /*
    switch("arch"){
        strstr(mips):
            switch("netmode"){
                case "netadv":
                    xxx;
                    break;
                case "tap":
                    xxx;
                    break;
            }
        strstr(arm):
            switch("netmode"){
                case "netadv":
                    xxx;
                    break;
                case "tap":
                    xxx;
                    break;
            }
        setcmd()
    }else{

    }
    */

//arch_config
    char arch_str[255][80];
    split(arch_str, arch, "_");
    char arch_cnt = atoi(arch_str[1]);
    switch(arch_cnt){
        case 1:
            strncpy(arch,"mipsel",6);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// support_config
    char support_str[255][80];
    split(support_str, support, "_");
    char support_cnt = atoi(support_str[1]);
    switch(support_cnt){
        case 1:
            strncpy(support,"malta\x00",6);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// image_config
    char image_str[255][80];
    split(image_str, image, "_");
    char image_cnt = atoi(image_str[1]);
    switch(image_cnt){
        case 1:
            strncpy(image,"debian_squeeze_mipsel_standard.qcow2\x00",37);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// kernel_config
    char kernel_str[255][80];
    split(kernel_str, kernel, "_");
    char kernel_cnt = atoi(kernel_str[1]);
    switch(kernel_cnt){
        case 1:
            strncpy(kernel,"vmlinux-2.6.32-5-4kc-malta\x00",27);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// initrd_config
    char initrd_str[255][80];
    split(initrd_str, initrd, "_");
    char initrd_cnt = atoi(initrd_str[1]);
    switch(initrd_cnt){
        case 1:
            strncpy(initrd,"NULL\x00",5);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// append_config
    char append_str[255][80];
    split(append_str, append, "_");
    char append_cnt = atoi(append_str[1]);
    switch(append_cnt){
        case 1:
            strncpy(append,"root=/dev/sda1 console=tty0\x00",28);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// memory_config
    char memory_str[255][80];
    split(memory_str, memory, "_");
    char memory_cnt = atoi(memory_str[1]);
    switch(memory_cnt){
        case 1:
            strncpy(memory,"512\x00",4);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }

// device_config
    char device_str[255][80];
    split(device_str, device, "_");
    char device_cnt = atoi(device_str[1]);
    switch(device_cnt){
        case 1:
            strncpy(device,"e1000,netdev=net0\x00",18);
            break;
        case 2:
            fprintf(cgiOut, "<H4>sorry, no support!</H4>");
            break;
        default:
            break;
    }




    // printf("<H2>[Debug]</H2>");
    // fprintf(cgiOut, "<H4>Arch: %s</H4>",arch);
    // fprintf(cgiOut, "<H4>Support: %s</H4>",support);
    // fprintf(cgiOut, "<H4>Image: %s</H4>",image);
    // fprintf(cgiOut, "<H4>Kernel: %s</H4>",kernel);
    // fprintf(cgiOut, "<H4>Initrd: %s</H4>",initrd);
    // fprintf(cgiOut, "<H4>Append: %s</H4>",append);
    // fprintf(cgiOut, "<H4>Memory: %s</H4>",memory);
    // fprintf(cgiOut, "<H4>Device: %s</H4>",device);
    // fprintf(cgiOut, "<H4>Net_mode: %s</H4>",net_mode);
    // fprintf(cgiOut, "<H4>Net_port: %s</H4>",net_port);




    //set qemu-system args.
    setCmd(arch, support, image, kernel, initrd, append, memory, device, net_mode, net_port);
    // fprintf(cgiOut, "<H4>cmd: %s</H4>",cmd);
    system_Cmd("date");
    fprintf(cgiOut, "<H2>启动中,预计等待20秒左右...</H2>\n");
    system_Cmd(cmd);
    // system_Cmd("id");
    fprintf(cgiOut, "</BODY>\n");
    fprintf(cgiOut, "</HTML>\n");
    return 0;
}