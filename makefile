CC = g++
OUT_PATH = out
OUT_TRIAL = $(OUT_PATH)/trial

.PHONY: all clean

$(OUT_TRIAL): src/main.cpp
	$(CC) $^ -o $@

$(OUT_PATH):
	mkdir -p $(OUT_PATH)

all: $(OUT_PATH) $(OUT_TRIAL)

clean:
	rm -rf $(OUT_PATH)
