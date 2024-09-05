#include "include.h"

void traitement()
{
    int n = -1;
    char class;
    char *ip = affichage();
    char *adress_net;
    char *adress_broad;
    char *IP_mask;
    int mask;

    affichage_classe(&ip, &mask, &class);

    adress_net = (char *)malloc(sizeof(char) * 16);
    adress_broad = (char *)malloc(sizeof(char) * 16);
    IP_mask = (char *)malloc(sizeof(char) * 16);

    masque_reseau(mask, &IP_mask);
    affichage_subnet(IP_mask, ip, &adress_net);
    affichage_broadcast(adress_net, mask, &adress_broad, IP_mask);

    printf("\nNumber of possibility users: \t\t\t%d\n\n", (int)pow(2, 32 - mask) -  2);
    printf("\n###############################################################################################\n\n");

    while(n < 0 || n > (32 - mask - 2))
    {
        number_div(&n);
    }
    decoupage_reseau(mask, IP_mask, ip, n, adress_net, adress_broad, class);
    printf("\nNumber of each subnet: \t\t%d\n\n", (int)pow(2, 32 - (mask + n)) - 2);
}

char *affichage()
{
    char *ipMask = (char*)malloc(sizeof(char) * 35);
    printf("Enter the IP Adress and the netmask #IP Adress/netmask# : ");
    scanf("%s", ipMask);
    return ipMask;
}

void affichage_classe(char **ip, int *mask, char *class)
{
    int decimal[4];
    int count = 0;
    int open;

    open = sscanf(*ip, "%d.%d.%d.%d/%d", &decimal[0], &decimal[1], &decimal[2], &decimal[3], mask);

    try:
    if(*mask > 32 || *mask < 0 || open != 5)
    {
        *ip = affichage();
        open = sscanf(*ip, "%d.%d.%d.%d/%d", &decimal[0], &decimal[1], &decimal[2], &decimal[3], mask);
        goto try;
    }

    printf("\n###############################################################################################\n\n");
    if ((decimal[0]>= 0 && decimal[0]<= 127) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        *class = 'A';
        printf("Adresse Classe             :\t\t\tA\n");
    }
    else if ((decimal[0]>= 128 && decimal[0]<= 191) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        printf("Adresse Classe             :\t\t\tB\n");
        *class = 'B';
    }
    else if ((decimal[0]>= 192 && decimal[0]<= 223) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        printf("Adresse Classe             :\t\t\tC\n");
        *class = 'C';
    }
}

void masque_reseau(int mask, char **IP_Mask)
{
    char bytes[4][9];
    int byte[4];
    char binary_ip[32] = {0};
    int i;

    for (i = 0; i < mask; i++)
    {
        binary_ip[i] = '1';
    }
    for (; i < 32; i++)
    {
        binary_ip[i] = '0';
    }

    strncpy(bytes[0], binary_ip, 8);
    strncpy(bytes[1], binary_ip + 8, 8);
    strncpy(bytes[2], binary_ip + 16, 8);
    strncpy(bytes[3], binary_ip + 24, 8);

    byte[0] = (int)strtol(bytes[0], NULL, 2);
    byte[1] = (int)strtol(bytes[1], NULL, 2);
    byte[2] = (int)strtol(bytes[2], NULL, 2);
    byte[3] = (int)strtol(bytes[3], NULL, 2);

    snprintf(*IP_Mask, 16, "%d.%d.%d.%d", byte[0], byte[1], byte[2], byte[3]);
    printf("\nAdresse Masque             : \t\t\t%s\n", *IP_Mask);
}

void affichage_subnet(char *mask_adress, char *ip, char **adress_net)
{
    int bytemask[4];
    int byteip[4];
    int add[4];

    sscanf(mask_adress, "%d.%d.%d.%d", &bytemask[0], &bytemask[1], &bytemask[2], &bytemask[3]);
    sscanf(ip, "%d.%d.%d.%d", &byteip[0], &byteip[1], &byteip[2], &byteip[3]);

    add[0] = byteip[0] & bytemask[0];
    add[1] = byteip[1] & bytemask[1];
    add[2] = byteip[2] & bytemask[2];
    add[3] = byteip[3] & bytemask[3];

    sprintf(*adress_net, "%d.%d.%d.%d", add[0], add[1], add[2], add[3]);
    printf("\nAdresse du Reseau          : \t\t\t%s\n", *adress_net);
}

void affichage_broadcast(char *adress_network, int mask, char **add_broad, char *ip_mask)
{
    int bytes[4];
    int bytesMask[4];
    int bytesBrad[4];

    sscanf(adress_network, "%d.%d.%d.%d", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
    sscanf(ip_mask, "%d.%d.%d.%d", &bytesMask[0], &bytesMask[1], &bytesMask[2], &bytesMask[3]);

    bytesMask[0] = 255 - bytesMask[0];
    bytesMask[1] = 255 - bytesMask[1];
    bytesMask[2] = 255 - bytesMask[2];
    bytesMask[3] = 255 - bytesMask[3];

    bytesBrad[0] = bytes[0] | bytesMask[0];
    bytesBrad[1] = bytes[1] | bytesMask[1];
    bytesBrad[2] = bytes[2] | bytesMask[2];
    bytesBrad[3] = bytes[3] | bytesMask[3];

    sprintf(*add_broad, "%d.%d.%d.%d", bytesBrad[0], bytesBrad[1], bytesBrad[2], bytesBrad[3]);
    printf("\nAdresse Broadcast          : \t\t\t%s\n", *add_broad);
}

void number_div(int *n)
{
    printf("Give the division : ");
    scanf("%d", n);
}
void decoupage_reseau(int netMask, char *IP_Mask, char *ip, int bit, char *adress_net, char *adress_broad, char class)
{
    int bytes[4];
    int temp_bytes[4];
    int broadcast_bytes[4];
    int new_netMask = netMask + bit;
    int subnet_size = pow(2, (32 - new_netMask));
    int num_subnets = pow(2, bit);

    sscanf(adress_net, "%d.%d.%d.%d", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
    printf("\n-----------------------------------------------------------------------------------------------\n");
    printf("\n    Sous reseau         |               \tbroadcast \n");

    for (int i = 0; i < num_subnets; i++)
    {
        temp_bytes[0] = bytes[0];
        temp_bytes[1] = bytes[1];
        temp_bytes[2] = bytes[2];
        temp_bytes[3] = bytes[3] + i * subnet_size;

        temp_bytes[2] += temp_bytes[3] / 256;
        temp_bytes[3] %= 256;
        temp_bytes[1] += temp_bytes[2] / 256;
        temp_bytes[2] %= 256;
        temp_bytes[0] += temp_bytes[1] / 256;
        temp_bytes[1] %= 256;

        broadcast_bytes[3] = temp_bytes[3] + subnet_size - 1;
        broadcast_bytes[2] = temp_bytes[2];
        broadcast_bytes[1] = temp_bytes[1];
        broadcast_bytes[0] = temp_bytes[0];
        broadcast_bytes[2] += broadcast_bytes[3] / 256;
        broadcast_bytes[3] %= 256;
        broadcast_bytes[1] += broadcast_bytes[2] / 256;
        broadcast_bytes[2] %= 256;
        broadcast_bytes[0] += broadcast_bytes[1] / 256;
        broadcast_bytes[1] %= 256;

        printf("\n-----------------------------------------------------------------------------------------------\n");
        printf("|Sous reseau: %d:%35d.%d.%d.%d\n", i + 1, temp_bytes[0], temp_bytes[1], temp_bytes[2], temp_bytes[3]);
        printf("|Sous Adresse Broadcast : %d:%23d.%d.%d.%d\n", i + 1, broadcast_bytes[0], broadcast_bytes[1], broadcast_bytes[2], broadcast_bytes[3]);
        printf("-----------------------------------------------------------------------------------------------\n");
    }
}

