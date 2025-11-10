-module(arp_parser).
-export([parse/1]).

-record(arp_packet, {
    htype,
    ptype,
    hsize,
    psize,
    op,
    sha,
    spa,
    tha,
    tpa
}).



parse(Binary) ->
    TestPacket = <<
    16#00, 16#01, 16#08, 16#00, 16#06, 16#04, 16#00, 16#01,
    16#08, 16#00, 16#27, 16#12, 16#34, 16#56, 16#C0, 16#A8,
    16#01, 16#01, 16#00, 16#00, 16#00, 16#00, 16#00, 16#00,
    16#C0, 16#A8, 16#01, 16#02
    >>,
    % Ваша реализация здесь
    ok.

print_arp(#arp_packet{
    htype = HType,
    ptype = PType,
    hsize = HSize,
    psize = PSize,
    op = Op,
    sha = SHa,
    spa = SPa,
    tha = THa,
    tpa = TPa
}) ->
    % Функция вывода record
    io:format("ARP Packet:~n").