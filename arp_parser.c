#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h> 

struct arp_packet {
    uint16_t htype;
    uint16_t ptype;
    uint8_t hsize;
    uint8_t psize;
    uint16_t op;
    uint8_t sha[6];
    uint8_t spa[4];
    uint8_t tha[6];
    uint8_t tpa[4];
};

uint8_t test_arp_packet[] = {
    0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01,
    0x08, 0x00, 0x27, 0x12, 0x34, 0x56, 0xC0, 0xA8,
    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xC0, 0xA8, 0x01, 0x02
};

//обработки ошибок решил сделать через числовые обозначения чтобы не плодить дополнительные структурыХ
int parse_arp(const uint8_t *data, size_t len, struct arp_packet *packet) {
    // Ваша реализация здесь
    if (!data || !packet) return -1; //проверка на указатели 
    if (len < 28) return -2; //проверка на длину
    uint16_t tmp16;
    packet->htype = (uint16_t)((data[0] << 8) | data[1]);
    packet->ptype = (uint16_t)((data[2] << 8) | data[3]);
    packet->hsize = data[4];
    packet->psize = data[5];
    packet->op    = (uint16_t)((data[6] << 8) | data[7]);

    if (packet->hsize != 6 || packet->psize != 4) return -3; //на случай если нам прислали другую структуру пакета
    memcpy(packet->sha, data + 8, 6);
    memcpy(packet->spa, data + 14, 4);
    memcpy(packet->sha, data + 18, 6);
    memcpy(packet->spa, data + 24, 4);

    return 0;
}

void print_arp(const struct arp_packet *packet) {
    if (!packet) return; //проверка Null
    printf("ARP Packet:\n");
    printf("  htype=%u ptype=0x%04x hsize=%u psize=%u op=%u\n",
           packet->htype, packet->ptype, packet->hsize, packet->psize, packet->op);
    printf("  sha=");
    for (int i = 0; i < 6; ++i) {
        printf("%02x", packet->sha[i]);
        if (i < 5) printf(":");
    }
    printf("  spa=");
    for (int i = 0; i < 4; ++i) {
        printf("%u", packet->spa[i]);
        if (i < 3) printf(".");
    }
    putchar('\n');

    printf("  tha=");
    for (int i = 0; i < 6; ++i) {
        printf("%02x", packet->tha[i]);
        if (i < 5) printf(":");
    }
    printf("  tpa=");
    for (int i = 0; i < 4; ++i) {
        printf("%u", packet->tpa[i]);
        if (i < 3) printf(".");
    }
    printf("\n");
    // Функция вывода структуры
}
int main(void)
{   
    struct arp_packet packet;
    int rc = parse_arp(test_arp_packet, sizeof(test_arp_packet), &packet);
    if (rc != 0)
    {
       printf("parse_arp failed: %d\n", rc);
       return 1; 
    }
    
    print_arp(&packet);
    return 0;
}