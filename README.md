# ARP parser (C + Erlang)

Мини-проект: парсер ARP-пакета для классического случая **Ethernet/IPv4 (28 байт)** — две реализации:

- **C:** `parse_arp(const uint8_t *data, size_t len, struct arp_packet *out)` и `print_arp(const struct arp_packet *p)`  
  (демо-`main()`)
- **Erlang:** `parse/1` и `print_arp/1`

## Важно знать
Erlang я не знаю вообще, поэтому воспользовался реализацией ChatGPT
Поддерживается только Ethernet/IPv4: ровно 28 байт, hsize=6, psize=4.
При несовпадении длины/размеров — возвращается ошибка:
    C: отрицательный код (в коде есть комментарии)
    Erlang: {error, invalid_length | unsupported_sizes | invalid_layout}

## Файлы

arp_parser.c # реализация на C 
arp_parser.erl # реализация на Erlang 
Makefile # сборка и запуск демо
build/ # артефакты сборки (создается автоматически)

## Требования

- GCC/Clang (C11)
- Erlang/OTP (`erlc`, `erl`)
- Linux/macOS (или любой *nix с make)

## Быстрый старт

Собрать всё и запустить обе демки:
```bash
make          # соберёт C и Erlang
make run      # запустит C-демо и Erlang-демо
```
Отдельно:
```bash
make c        # только C
make run-c
make erlang   # только Erlang
make run-erlang
```
Очистить:
```bash
make clean
```
Ожидаемый вывод (для тестовых данных):
ARP Packet:
  htype=1 ptype=0x0800 hsize=6 psize=4 op=1
  sha=08:00:27:12:34:56  spa=192.168.1.1
  tha=00:00:00:00:00:00  tpa=192.168.1.2
