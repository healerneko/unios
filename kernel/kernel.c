typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define MB2_BOOT_MAGIC 0x36d76289u
#define MB2_TAG_END 0
#define MB2_TAG_FRAMEBUFFER 8

typedef struct { u32 type, size; } mb2_tag;
typedef struct { u32 total_size, reserved; mb2_tag first; } mb2_info;
typedef struct {
    u32 type, size;
    u64 address;
    u32 pitch, width, height;
    u8 bpp, framebuffer_type;
    u16 reserved;
} mb2_framebuffer;

typedef struct { u32 width, height, pitch; u8 bpp; volatile u8 *base; } framebuffer;

static framebuffer screen;

static void pixel(u32 x, u32 y, u32 color) {
    if (x >= screen.width || y >= screen.height || !screen.base) return;
    volatile u32 *row = (volatile u32 *)(screen.base + (u64)y * screen.pitch);
    row[x] = color;
}

static void fill(u32 x, u32 y, u32 w, u32 h, u32 color) {
    for (u32 j = 0; j < h; j++)
        for (u32 i = 0; i < w; i++) pixel(x + i, y + j, color);
}

static void moon(u32 cx, u32 cy, u32 r, u32 color, u32 background) {
    u64 rr = (u64)r * r;
    for (u32 y = 0; y <= 2 * r; y++) {
        for (u32 x = 0; x <= 2 * r; x++) {
            long long dx = (long long)x - r;
            long long dy = (long long)y - r;
            if ((u64)(dx * dx + dy * dy) <= rr) {
                long long sx = dx + r / 2;
                if ((u64)(sx * sx + dy * dy) > rr * 3 / 4)
                    pixel(cx + x, cy + y, background);
                else
                    pixel(cx + x, cy + y, color);
            }
        }
    }
}

static const u8 *glyph(char c) {
    static const u8 blank[7] = {0};
    static const u8 font[128][7] = {
        ['A']={14,17,17,31,17,17,17}, ['B']={30,17,17,30,17,17,30},
        ['C']={14,17,16,16,16,17,14}, ['D']={30,17,17,17,17,17,30},
        ['E']={31,16,16,30,16,16,31}, ['F']={31,16,16,30,16,16,16},
        ['G']={14,17,16,23,17,17,15}, ['H']={17,17,17,31,17,17,17},
        ['I']={31,4,4,4,4,4,31}, ['K']={17,18,20,24,20,18,17},
        ['L']={16,16,16,16,16,16,31}, ['M']={17,27,21,21,17,17,17},
        ['N']={17,25,25,21,19,19,17}, ['O']={14,17,17,17,17,17,14},
        ['P']={30,17,17,30,16,16,16}, ['R']={30,17,17,30,20,18,17},
        ['S']={15,16,16,14,1,1,30}, ['T']={31,4,4,4,4,4,4},
        ['U']={17,17,17,17,17,17,14}, ['V']={17,17,17,17,17,10,4},
        ['W']={17,17,17,21,21,21,10}, ['0']={14,17,19,21,25,17,14},
        ['X']={17,17,10,4,10,17,17},
        ['2']={14,17,1,2,4,8,31}, ['3']={30,1,1,14,1,1,30},
        ['-']={0,0,0,31,0,0,0}, [':']={0,4,4,0,4,4,0},
        ['.']={0,0,0,0,0,12,12}, ['/']={1,2,2,4,8,8,16}
    };
    if (c < 0 || c > 127 || c == ' ') return blank;
    return font[(u8)c];
}

static void text(u32 x, u32 y, const char *s, u32 scale, u32 color) {
    while (*s) {
        const u8 *rows = glyph(*s++);
        for (u32 row = 0; row < 7; row++)
            for (u32 col = 0; col < 5; col++)
                if (rows[row] & (1u << (4 - col)))
                    fill(x + col * scale, y + row * scale, scale, scale, color);
        x += 6 * scale;
    }
}

static int framebuffer_from_info(u64 address) {
    if (!address) return 0;
    const mb2_info *info = (const mb2_info *)address;
    if (info->total_size < 16 || info->total_size > 1024 * 1024) return 0;
    const u8 *cursor = (const u8 *)&info->first;
    const u8 *end = (const u8 *)info + info->total_size;
    while (cursor + 8 <= end) {
        const mb2_tag *tag = (const mb2_tag *)cursor;
        if (tag->size < 8 || cursor + tag->size > end) return 0;
        if (tag->type == MB2_TAG_FRAMEBUFFER && tag->size >= sizeof(mb2_framebuffer)) {
            const mb2_framebuffer *fb = (const mb2_framebuffer *)tag;
            if (fb->framebuffer_type != 1 || fb->bpp != 32 || !fb->address || !fb->width || !fb->height) return 0;
            screen.width = fb->width; screen.height = fb->height;
            screen.pitch = fb->pitch; screen.bpp = fb->bpp;
            screen.base = (volatile u8 *)(u64)fb->address;
            return 1;
        }
        if (tag->type == MB2_TAG_END) break;
        cursor += (tag->size + 7) & ~7u;
    }
    return 0;
}

void kernel_main(u64 magic, u64 info_address) {
    if (magic != MB2_BOOT_MAGIC || !framebuffer_from_info(info_address)) {
        for (;;) __asm__ volatile("hlt");
    }
    fill(0, 0, screen.width, screen.height, 0x100b20);
    fill(0, screen.height - 12, screen.width, 12, 0x6d3b9c);
    for (u32 i = 0; i < 5; i++) {
        u32 x = (screen.width * (i + 1)) / 6;
        u32 y = 55 + (i * 37) % 120;
        fill(x, y, 4, 4, i & 1 ? 0xdfb7ff : 0xffffff);
    }
    moon(screen.width * 3 / 4, screen.height / 5, screen.height / 9, 0xe5dcff, 0x100b20);
    text(screen.width / 10, screen.height / 3, "UNIOS KERNEL", 7, 0xf4edff);
    text(screen.width / 10, screen.height / 3 + 75, "STAGE 3 - BOOT CORE", 3, 0xcba7ff);
    text(screen.width / 10, screen.height / 3 + 125, "UEFI MULTIBOOT2", 3, 0x65e6c1);
    text(screen.width / 10, screen.height - 65, "KERNEL ONLINE / NETWORK NEXT", 2, 0xd9d1e7);
    for (;;) __asm__ volatile("hlt");
}
