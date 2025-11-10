# ARP parser (C + Erlang) — Linux/macOS

CC       ?= gcc
CFLAGS   ?= -Wall -Wextra -O2 -std=c11
BUILD_DIR := build

ERLC     ?= erlc
ERL      ?= erl
ERL_FLAGS := -pa $(BUILD_DIR) -noshell

C_SRC    := arp_parser.c
C_BIN    := $(BUILD_DIR)/arp_parser
ERL_SRC  := arp_parser.erl
ERL_BEAM := $(BUILD_DIR)/arp_parser.beam

.PHONY: all c erlang run run-c run-erlang clean

all: c erlang

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# --- C ---
c: $(C_BIN)

$(C_BIN): $(C_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

run-c: $(C_BIN)
	$(C_BIN)

# --- Erlang ---
erlang: $(ERL_BEAM)

$(ERL_BEAM): $(ERL_SRC) | $(BUILD_DIR)
	$(ERLC) -o $(BUILD_DIR) $<

run-erlang: $(ERL_BEAM)
	$(ERL) $(ERL_FLAGS) -eval "Packet = <<16#00,16#01,16#08,16#00,16#06,16#04,16#00,16#01,16#08,16#00,16#27,16#12,16#34,16#56,16#C0,16#A8,16#01,16#01,16#00,16#00,16#00,16#00,16#00,16#00,16#C0,16#A8,16#01,16#02>>, case arp_parser:parse(Packet) of {ok, Rec} -> arp_parser:print_arp(Rec); Err -> io:format(\"~p~n\", [Err]) end, halt()."

# --- Both ---
run: run-c run-erlang

clean:
	rm -rf $(BUILD_DIR)

