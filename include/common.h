//
// Created by john on 08.04.23.
//

#pragma once


#define OF_ELF64
#define OF_ELFX32
#define OF_ELF32


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum out_type {
    OUT_RAWDATA,    /* Plain bytes */
    OUT_RESERVE,    /* Reserved bytes (RESB et al) */
    OUT_ZERODATA,   /* Initialized data, but all zero */
    OUT_ADDRESS,    /* An address (symbol value) */
    OUT_RELADDR,    /* A relative address */
    OUT_SEGMENT,    /* A segment number */
    OUT_REL1ADR,
    OUT_REL2ADR,
    OUT_REL4ADR,
    OUT_REL8ADR
};

typedef enum {
    DIRR_OK,
    D_OSABI = 1,
    DIRR_ERROR,
    DIRR_UNKNOWN
} directive, directive_result;

enum out_flags {
    OUT_WRAP     = 0,           /* Undefined signedness (wraps) */
    OUT_SIGNED   = 1,           /* Value is signed */
    OUT_UNSIGNED = 2,           /* Value is unsigned */
    OUT_SIGNMASK = 3            /* Mask for signedness bits */
};

struct src_location {
    const char *filename;
    int32_t lineno;
};

struct out_data {
    int64_t offset;             /* Offset within segment */
    int32_t segment;            /* Segment written to */
    enum out_type type;         /* See above */
    enum out_flags flags;       /* See above */
    int inslen;                 /* Length of instruction */
    int insoffs;                /* Offset inside instruction */
    int bits;                   /* Bits mode of compilation */
    uint64_t size;              /* Size of output */
    const struct itemplate *itemp; /* Instruction template */
    const void *data;           /* Data for OUT_RAWDATA */
    uint64_t toffset;           /* Target address offset for relocation */
    int32_t tsegment;           /* Target segment for relocation */
    int32_t twrt;               /* Relocation with respect to */
    int64_t relbase;            /* Relative base for OUT_RELADDR */
    struct src_location where;  /* Source file and line */
};

struct pragma;
typedef enum directive_result (*pragma_handler)(const struct pragma *);

union intorptr {
    int64_t i;
    uint64_t u;
    size_t s;
    void *p;
    const void *cp;
    uintptr_t up;
};
typedef union intorptr intorptr;

#define list_for_each_safe(pos, _n, head)                \
    for (pos = head, _n = (pos ? pos->next : NULL); pos; \
        pos = _n, _n = (_n ? _n->next : NULL))

#define SEG_ABS 0x40000000L
#define NO_SEG  INT32_C(-1)


#define cpu_to_le16(v) ((uint16_t)(v))
#define cpu_to_le32(v) ((uint32_t)(v))
#define cpu_to_le64(v) ((uint64_t)(v))

typedef const unsigned char macros_t;
enum label_type;
enum directive;

struct debug_macro_info;
#pragma GCC diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
struct dfmt {
    const char *fullname;
    const char *shortname;
    void (*init)(void);
    void (*linenum)(const char *filename, int32_t linenumber, int32_t segto);
    void (*debug_deflabel)(char *name, int32_t segment, int64_t offset,
                           int is_global, char *special);
    void (*debug_smacros)(bool define, const char *def);
    void (*debug_include)(bool start, struct src_location outer,
                          struct src_location inner);
    void (*debug_mmacros)(const struct debug_macro_info *);
    void (*debug_directive)(const char *directive, const char *params);
    void (*debug_typevalue)(int32_t type);
    void (*debug_output)(int type, void *param);
    void (*cleanup)(void);
    const struct pragma_facility *pragmas;
};
#pragma GCC diagnostic pop

extern struct dfmt *dfmt;
struct ofmt;

#pragma GCC diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
struct ofmt {
    const char *fullname;
    const char *shortname;
    const char *extension;
    unsigned int flags;
    int maxbits;
    const struct dfmt *const *debug_formats;
    const struct dfmt *default_dfmt;
    macros_t *stdmac;
    void (*init) (void);
    void (*reset) (void);
    void (*output) (const struct out_data *data);
    void (*legacy_output) (int32_t segto, const void *data,
                           enum out_type type, uint64_t size,
                           int32_t segment, int32_t wrt);
    void (*symdef) (char *name, int32_t segment, int64_t offset,
                    int is_global, char *special);
    int32_t (*section) (char *name, int *bits);
    int32_t (*herelabel) (const char *name, enum label_type type,
                          int32_t seg, int32_t *subsection,
                          bool *copyoffset);
    void (*sectalign) (int32_t seg, unsigned int value);
    int32_t (*segbase) (int32_t segment);
    enum directive_result (*directive) (enum directive directive, char *value);
    void (*cleanup) (void);
    const struct pragma_facility *pragmas;
};
#pragma GCC diagnostic pop

struct ofmt_alias {
    const char  *shortname;
    const struct ofmt *ofmt;
};

extern const struct ofmt *ofmt;
extern FILE *ofile;

#define is_power2(v) ((v) && ((v) & ((v) - 1)) == 0)

typedef struct {
    int32_t type;                  /* a register, or EXPR_xxx */
    int64_t value;                 /* must be >= 32 bits */
} expr;

#define EXPR_REG_END 248

#define EXPR_UNKNOWN    (EXPR_REG_END+1) /* forward references */
#define EXPR_SIMPLE     (EXPR_REG_END+2)
#define EXPR_WRT        (EXPR_REG_END+3)
#define EXPR_RDSAE      (EXPR_REG_END+4)
#define EXPR_SEGBASE    (EXPR_REG_END+5)

struct location {
    int64_t offset;
    int32_t segment;
    int     known;
};
extern struct location location;

bool is_self_relative(const expr *);
int32_t reloc_wrt(const expr *);
int32_t reloc_seg(const expr *);
int64_t reloc_value(const expr *);
bool is_just_unknown(const expr *);
bool is_unknown(const expr *);
bool is_reloc(const expr *);
bool is_really_simple(const expr *);
bool is_simple(const expr *);

int32_t seg_alloc(void);
#define ZERO_BUF_SIZE 65536
extern const uint8_t zero_buffer[ZERO_BUF_SIZE];

