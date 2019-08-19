#ifndef PACKAGE
#define PACKAGE "jbig2dec"
#endif

#include <rtthread.h>
#include <stdlib.h>

#if defined(RT_USING_OLPC_DEMO)
#include <stdio.h>
#include <math.h>

#include "color_palette.h"
#include "drv_display.h"
#include "drv_heap.h"
#include "image_info.h"
#include "olpc_display.h"
#include "jbig2dec.h"
#include "hal_base.h"

#if !defined (UINT32_MAX)
#define UINT32_MAX 0xffffffff
#endif

#define get_uint16(bptr)\
    (((bptr)[0] << 8) | (bptr)[1])
#define get_int16(bptr)\
    (((int)get_uint16(bptr) ^ 0x8000) - 0x8000)

#define  OPTI   1

#define CONTEXT_13 0

#if CONTEXT_13
#define  CONTEXT_VALUE0 0x0efb
#define  CONTEXT_VALUE1 0x0008
#define  CONTEXT_VALUE2 0x0200
#define  CONTEXT_VALUE3 1
#else //else CONTEXT = 16
#define  CONTEXT_VALUE0 0x7bf7
#define  CONTEXT_VALUE1 0x10
#define  CONTEXT_VALUE2 0x800
#define  CONTEXT_VALUE3 0
#endif


void
jbig2_free(Jbig2Allocator *allocator, void *p)
{
    allocator->free(allocator, p);
}

int16_t
jbig2_get_int16(const unsigned char *bptr)
{
    return get_int16(bptr);
}

int32_t
jbig2_get_int32(const unsigned char *bptr)
{
    return ((int32_t)get_int16(bptr) << 16) | get_uint16(bptr + 2);
}

uint32_t
jbig2_get_uint32(const unsigned char *bptr)
{
    return ((uint32_t)get_uint16(bptr) << 16) | get_uint16(bptr + 2);
}

/* could put bit fields in to minimize memory usage */
typedef struct
{
    unsigned short Qe;
    unsigned char mps_xor;               /* mps_xor = index ^ NMPS */
    unsigned char lps_xor;               /* lps_xor = index ^ NLPS ^ (SWITCH << 7) */
} Jbig2ArithQe;

const Jbig2ArithQe jbig2_arith_Qe[47] =
{
    { 0x5601, 1 ^ 0, 1 ^ 0 ^ 0x80 },
    { 0x3401, 2 ^ 1, 6 ^ 1 },
    { 0x1801, 3 ^ 2, 9 ^ 2 },
    { 0x0AC1, 4 ^ 3, 12 ^ 3 },
    { 0x0521, 5 ^ 4, 29 ^ 4 },
    { 0x0221, 38 ^ 5, 33 ^ 5 },
    { 0x5601, 7 ^ 6, 6 ^ 6 ^ 0x80 },
    { 0x5401, 8 ^ 7, 14 ^ 7 },
    { 0x4801, 9 ^ 8, 14 ^ 8 },
    { 0x3801, 10 ^ 9, 14 ^ 9 },
    { 0x3001, 11 ^ 10, 17 ^ 10 },
    { 0x2401, 12 ^ 11, 18 ^ 11 },
    { 0x1C01, 13 ^ 12, 20 ^ 12 },
    { 0x1601, 29 ^ 13, 21 ^ 13 },
    { 0x5601, 15 ^ 14, 14 ^ 14 ^ 0x80 },
    { 0x5401, 16 ^ 15, 14 ^ 15 },
    { 0x5101, 17 ^ 16, 15 ^ 16 },
    { 0x4801, 18 ^ 17, 16 ^ 17 },
    { 0x3801, 19 ^ 18, 17 ^ 18 },
    { 0x3401, 20 ^ 19, 18 ^ 19 },
    { 0x3001, 21 ^ 20, 19 ^ 20 },
    { 0x2801, 22 ^ 21, 19 ^ 21 },
    { 0x2401, 23 ^ 22, 20 ^ 22 },
    { 0x2201, 24 ^ 23, 21 ^ 23 },
    { 0x1C01, 25 ^ 24, 22 ^ 24 },
    { 0x1801, 26 ^ 25, 23 ^ 25 },
    { 0x1601, 27 ^ 26, 24 ^ 26 },
    { 0x1401, 28 ^ 27, 25 ^ 27 },
    { 0x1201, 29 ^ 28, 26 ^ 28 },
    { 0x1101, 30 ^ 29, 27 ^ 29 },
    { 0x0AC1, 31 ^ 30, 28 ^ 30 },
    { 0x09C1, 32 ^ 31, 29 ^ 31 },
    { 0x08A1, 33 ^ 32, 30 ^ 32 },
    { 0x0521, 34 ^ 33, 31 ^ 33 },
    { 0x0441, 35 ^ 34, 32 ^ 34 },
    { 0x02A1, 36 ^ 35, 33 ^ 35 },
    { 0x0221, 37 ^ 36, 34 ^ 36 },
    { 0x0141, 38 ^ 37, 35 ^ 37 },
    { 0x0111, 39 ^ 38, 36 ^ 38 },
    { 0x0085, 40 ^ 39, 37 ^ 39 },
    { 0x0049, 41 ^ 40, 38 ^ 40 },
    { 0x0025, 42 ^ 41, 39 ^ 41 },
    { 0x0015, 43 ^ 42, 40 ^ 42 },
    { 0x0009, 44 ^ 43, 41 ^ 43 },
    { 0x0005, 45 ^ 44, 42 ^ 44 },
    { 0x0001, 45 ^ 45, 43 ^ 45 },
    { 0x5601, 46 ^ 46, 46 ^ 46 }
};

typedef enum
{
    usage, dump, render
} jbig2dec_mode;

typedef enum
{
    jbig2dec_format_none,
    jbig2dec_format_jbig2,
    jbig2dec_format_pbm,
} jbig2dec_format;

typedef struct
{
    jbig2dec_mode mode;
    int verbose, embedded;
    char *output_filename;
    jbig2dec_format output_format;
    char *last_message;
    Jbig2Severity severity;
    char *type;
    long repeats;
} jbig2dec_params_t;

static void *
jbig2_default_alloc(Jbig2Allocator *allocator, size_t size)
{
    return malloc(size);
}

static void
jbig2_default_free(Jbig2Allocator *allocator, void *p)
{
    free(p);
}

static void *
jbig2_default_realloc(Jbig2Allocator *allocator, void *p, size_t size)
{
    return realloc(p, size);
}

static Jbig2Allocator jbig2_default_allocator =
{
    jbig2_default_alloc,
    jbig2_default_free,
    jbig2_default_realloc
};

void *
jbig2_alloc(Jbig2Allocator *allocator, size_t size, size_t num)
{
    //rt_kprintf("size is %d and num is %d\n", size, num);
    if (num > 0 && size > SIZE_MAX / num)
    {
        //rt_kprintf("1-----------------------------------------------\n");
        return NULL;
    }

    return allocator->alloc(allocator, size * num);
}

void *
jbig2_realloc(Jbig2Allocator *allocator, void *p, size_t size, size_t num)
{
    /* check for integer multiplication overflow */
    if (num > 0 && size >= SIZE_MAX / num)
    {
        //rt_kprintf("2-----------------------------------------------\n");
        return NULL;
    }
    return allocator->realloc(allocator, p, size * num);
}

Jbig2Segment *//
jbig2_parse_segment_header(Jbig2Ctx *ctx, uint8_t *buf, size_t buf_size, size_t *p_header_size)
{
    Jbig2Segment *result;
    uint8_t rtscarf;
    uint32_t rtscarf_long;
    uint32_t *referred_to_segments;
    uint32_t referred_to_segment_count;
    uint32_t referred_to_segment_size;
    uint32_t pa_size;
    uint32_t offset;

    /* minimum possible size of a jbig2 segment header */
    if (buf_size < 11)
    {
        //rt_kprintf("3-----------------------------------------------\n");
        return NULL;
    }
    //result = jbig2_new(ctx, Jbig2Segment, 1);
    result = (Jbig2Segment *)malloc(sizeof(Jbig2Segment) * 1);
    if (result == NULL)
    {
        rt_kprintf("malloc failed : fail to malloc result\n");
        return NULL;
    }

    /* 7.2.2 */
    result->number = jbig2_get_uint32(buf);

    /* 7.2.3 */
    result->flags = buf[4];

    /* 7.2.4 referred-to segments */
    rtscarf = buf[5];
    if ((rtscarf & 0xe0) == 0xe0)
    {
        rtscarf_long = jbig2_get_uint32(buf + 5);
        referred_to_segment_count = rtscarf_long & 0x1fffffff;
        offset = 5 + 4 + (referred_to_segment_count + 1) / 8;
    }
    else
    {
        referred_to_segment_count = (rtscarf >> 5);
        offset = 5 + 1;
    }
    result->referred_to_segment_count = referred_to_segment_count;

    /* we now have enough information to compute the full header length */
    referred_to_segment_size = result->number <= 256 ? 1 : result->number <= 65536 ? 2 : 4;     /* 7.2.5 */
    pa_size = result->flags & 0x40 ? 4 : 1;     /* 7.2.6 */
    if (offset + referred_to_segment_count * referred_to_segment_size + pa_size + 4 > buf_size)
    {
        jbig2_free(ctx->allocator, result);
        //rt_kprintf("5-----------------------------------------------\n");
        return NULL;
    }

    /* 7.2.5 */
    if (referred_to_segment_count)
    {
        uint32_t i;

        referred_to_segments = jbig2_new(ctx, uint32_t, referred_to_segment_count * referred_to_segment_size);
        //referred_to_segments = (uint32_t*)malloc(sizeof(uint32_t) * referred_to_segment_count * referred_to_segment_size);
        if (referred_to_segments == NULL)
        {
            //rt_kprintf("6-----------------------------------------------\n");
            return NULL;
        }

        for (i = 0; i < referred_to_segment_count; i++)
        {
            referred_to_segments[i] =
                (referred_to_segment_size == 1) ? buf[offset] :
                (referred_to_segment_size == 2) ? get_uint16(buf + offset) : jbig2_get_uint32(buf + offset);
            offset += referred_to_segment_size;
        }
        result->referred_to_segments = referred_to_segments;
    }
    else                      /* no referred-to segments */
    {

        result->referred_to_segments = NULL;
    }

    /* 7.2.6 */
    if (pa_size == 4)
    {
        result->page_association = jbig2_get_uint32(buf + offset);
        offset += 4;
    }
    else
    {
        result->page_association = buf[offset++];
    }

    /* 7.2.7 */
    result->rows = UINT32_MAX;
    result->data_length = jbig2_get_uint32(buf + offset);
    *p_header_size = offset + 4;

    /* no body parsing results yet */
    result->result = NULL;

    return result;
}

Jbig2Ctx *
jbig2_ctx_new(Jbig2Allocator *allocator)
{
    Jbig2Ctx *result;

    if (allocator == NULL)
        allocator = &jbig2_default_allocator;

    result = (Jbig2Ctx *)jbig2_alloc(allocator, sizeof(Jbig2Ctx), 1);

    result->allocator = allocator;
    result->state = JBIG2_FILE_HEADER;
    result->buf = NULL;
    result->n_segments = 0;
    result->segments = jbig2_new(result, Jbig2Segment *, 8);
    result->segment_index = 0;

    result->current_page = 0;
    result->max_page_index = 4;
    result->pages = jbig2_new(result, Jbig2Page, result->max_page_index);

    {
        int index;

        for (index = 0; index < result->max_page_index; index++)
        {
            result->pages[index].state = JBIG2_PAGE_FREE;
            result->pages[index].number = 0;
            result->pages[index].width = 0;
            result->pages[index].height = 0xffffffff;
            result->pages[index].x_resolution = 0;
            result->pages[index].y_resolution = 0;
            result->pages[index].flags = 0;
            result->pages[index].image = NULL;
        }
    }

    return result;
}

//static void
//error_callback(void *error_callback_data, const char *buf, Jbig2Severity severity, int32_t seg_idx)
//{
//  jbig2dec_params_t *params = (jbig2dec_params_t *)error_callback_data;
//  char *type;
//  char segment[22];
//  int len;
//  char *message;
//
//  switch (severity) {
//  case JBIG2_SEVERITY_DEBUG:
//      if (params->verbose < 3)
//          return;
//      type = "DEBUG";
//      break;
//  case JBIG2_SEVERITY_INFO:
//      if (params->verbose < 2)
//          return;
//      type = "info";
//      break;
//  case JBIG2_SEVERITY_WARNING:
//      if (params->verbose < 1)
//          return;
//      type = "WARNING";
//      break;
//  case JBIG2_SEVERITY_FATAL:
//      type = "FATAL ERROR";
//      break;
//  default:
//      type = "unknown message";
//      break;
//  }
//  if (seg_idx == -1)
//      segment[0] = '\0';
//  else
//      snprintf(segment, sizeof(segment), "(segment 0x%02x)", seg_idx);
//
//  len = snprintf(NULL, 0, "jbig2dec %s %s %s", type, buf, segment);
//  if (len < 0) {
//      return;
//  }
//
//  message = malloc(len + 1);
//  if (message == NULL) {
//      return;
//  }
//
//  len = snprintf(message, len + 1, "jbig2dec %s %s %s", type, buf, segment);
//  if (len < 0)
//  {
//      free(message);
//      return;
//  }
//
//  if (params->last_message != NULL && strcmp(message, params->last_message)) {
//      if (params->repeats > 1)
//          fprintf(stderr, "jbig2dec %s last message repeated %ld times\n", params->type, params->repeats);
//      fprintf(stderr, "%s\n", message);
//      free(params->last_message);
//      params->last_message = message;
//      params->severity = severity;
//      params->type = type;
//      params->repeats = 0;
//  }
//  else if (params->last_message != NULL) {
//      params->repeats++;
//      if (params->repeats % 1000000 == 0)
//          fprintf(stderr, "jbig2dec %s last message repeated %ld times so far\n", params->type, params->repeats);
//      free(message);
//  }
//  else if (params->last_message == NULL) {
//      fprintf(stderr, "%s\n", message);
//      params->last_message = message;
//      params->severity = severity;
//      params->type = type;
//      params->repeats = 0;
//  }
//}

int
jbig2_page_info(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data, uint32_t flag)
{
    Jbig2Page *page, *pages;

    /* a new page info segment implies the previous page is finished */
    page = &(ctx->pages[ctx->current_page]);

    /* find a free page */
    {
        int index, j;

        index = ctx->current_page;
        while (ctx->pages[index].state != JBIG2_PAGE_FREE)
        {
            index++;
            if (index >= ctx->max_page_index)
            {
                /* grow the list */
                pages = (Jbig2Page *)jbig2_realloc(ctx->allocator, ctx->pages, (ctx->max_page_index <<= 2), sizeof(Jbig2Page));
                if (pages == NULL)
                {
                    return -1;
                }
                ctx->pages = pages;
                for (j = index; j < ctx->max_page_index; j++)
                {
                    ctx->pages[j].state = JBIG2_PAGE_FREE;
                    ctx->pages[j].number = 0;
                    ctx->pages[j].image = NULL;
                }
            }
        }
        page = &(ctx->pages[index]);
        ctx->current_page = index;
        page->state = JBIG2_PAGE_NEW;
        page->number = segment->page_association;
    }

    /* FIXME: would be nice if we tried to work around this */

    /* 7.4.8.x */
    page->width = jbig2_get_uint32(segment_data);
    page->height = jbig2_get_uint32(segment_data + 4);

    page->x_resolution = jbig2_get_uint32(segment_data + 8);
    page->y_resolution = jbig2_get_uint32(segment_data + 12);
    page->flags = segment_data[16];
    /* 7.4.8.2 */
    if (page->height == 0xFFFFFFFF)
    {
    }
    else
    {
        uint32_t stride;
        if (page->width == 0 || page->height == 0)
        {
            page->image = NULL;
        }

        page->image = jbig2_new(ctx, Jbig2Image, 1);
        if (page->image == NULL)
        {
            rt_kprintf("malloc failed : fail to malloc page->image\n");
            return -1;
        }
        stride = ((page->width - 1) >> 3) + 1;    /* generate a byte-aligned stride */

        /* check for integer multiplication overflow */
        if (page->height > (INT32_MAX / stride))
        {
            jbig2_free(ctx->allocator, page->image);
            page->image = NULL;
            return -1;
        }
        //page->image->data = jbig2_new(ctx, uint8_t, (size_t)page->height * stride);
        //if (page->image->data == NULL) {
        //  jbig2_free(ctx->allocator, page->image);
        //  page->image = NULL;
        //}

        page->image->width = page->width;
        page->image->height = page->height;
        page->image->stride = stride;
        page->image->refcount = 1;
    }

    return 0;
}

int
jbig2_complete_page(Jbig2Ctx *ctx)
{
    //if (ctx->segment_index != ctx->n_segments) {
    //  Jbig2Segment *segment = ctx->segments[ctx->segment_index];
    //}

    ctx->pages[ctx->current_page].state = JBIG2_PAGE_COMPLETE;
    return 0;
}

int
jbig2_end_of_page(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    //uint32_t page_number = ctx->pages[ctx->current_page].number;
    int code = jbig2_complete_page(ctx);
    if (code < 0)
        return -1;

    return 0;
}

typedef struct
{
    Jbig2WordStream super;
    const unsigned char *data;
    size_t size;
} Jbig2WordStreamBuf;//

static int//
jbig2_word_stream_buf_get_next_word(Jbig2WordStream *self, size_t offset, uint32_t *word)
{
    Jbig2WordStreamBuf *z = (Jbig2WordStreamBuf *)self;
    uint32_t val = 0;
    int ret = 0;

    if (self == NULL || word == NULL)
        return -1;
    if (offset >= z->size)
    {
        *word = 0;
        return 0;
    }

    if (offset < z->size)
    {
        val |= z->data[offset] << 24;
        ret++;
    }
    if (offset + 1 < z->size)
    {
        val |= z->data[offset + 1] << 16;
        ret++;
    }
    if (offset + 2 < z->size)
    {
        val |= z->data[offset + 2] << 8;
        ret++;
    }
    if (offset + 3 < z->size)
    {
        val |= z->data[offset + 3];
        ret++;
    }
    *word = val;
    return ret;
}

Jbig2WordStream *//
jbig2_word_stream_buf_new(Jbig2Ctx *ctx, const unsigned char *data, size_t size)
{
    Jbig2WordStreamBuf *result = jbig2_new(ctx, Jbig2WordStreamBuf, 1);
    //Jbig2WordStreamBuf *result = (Jbig2WordStreamBuf *)malloc(sizeof(Jbig2WordStreamBuf) * 1);

    if (result == NULL)
    {
        //rt_kprintf("7-----------------------------------------------\n");
        return NULL;
    }

    result->super.get_next_word = jbig2_word_stream_buf_get_next_word;
    result->data = data;
    result->size = size;

    return &result->super;
}

static void//
jbig2_arith_bytein(Jbig2ArithState *as)
{
    int new_bytes;
    unsigned char B;

    /* invariant: as->next_word_bytes > 0 */

    /* Figure G.3 */
    B = (unsigned char)((as->next_word >> 24) & 0xFF);
    if (B == 0xFF)
    {
        unsigned char B1;

        if (as->next_word_bytes == 1)
        {
            Jbig2WordStream *ws = as->ws;

            new_bytes = ws->get_next_word(ws, as->offset, &as->next_word);
            as->next_word_bytes = new_bytes;
            as->offset += new_bytes;

            B1 = (unsigned char)((as->next_word >> 24) & 0xFF);
            if (B1 > 0x8F)
            {
                as->C += 0xFF00;
                as->CT = 8;
                as->next_word = 0xFF000000 | (as->next_word >> 8);
                as->next_word_bytes = 4;
                as->offset--;
            }
            else
            {
                as->C += B1 << 9;
                as->CT = 7;
            }
        }
        else
        {
            B1 = (unsigned char)((as->next_word >> 16) & 0xFF);
            if (B1 > 0x8F)
            {
                as->C += 0xFF00;
                as->CT = 8;
            }
            else
            {
                as->next_word_bytes--;
                as->next_word <<= 8;
                as->C += (B1 << 9);
                as->CT = 7;
            }
        }
    }
    else
    {
        as->CT = 8;
        as->next_word <<= 8;
        as->next_word_bytes--;
        if (as->next_word_bytes == 0)
        {
            Jbig2WordStream *ws = as->ws;

            new_bytes = ws->get_next_word(ws, as->offset, &as->next_word);
            as->offset += new_bytes;
            as->next_word_bytes = new_bytes;
        }
        B = (unsigned char)((as->next_word >> 24) & 0xFF);
        as->C += (B << 8);
    }
}

Jbig2ArithState *//
jbig2_arith_new(Jbig2Ctx *ctx, Jbig2WordStream *ws)
{
    Jbig2ArithState *result;
    int new_bytes;

    result = jbig2_new(ctx, Jbig2ArithState, 1);
    //result = (Jbig2ArithState *)malloc(sizeof(Jbig2ArithState) * 1);
    if (result == NULL)
    {
        //rt_kprintf("8-----------------------------------------------\n");
        return NULL;
    }

    result->ws = ws;

    new_bytes = ws->get_next_word(ws, 0, &result->next_word);
    result->next_word_bytes = new_bytes;
    result->offset = new_bytes;
    result->C = (result->next_word >> 8) & 0xFF0000;
    jbig2_arith_bytein(result);
    result->C <<= 7;
    result->CT -= 7;
    result->A = 0x8000;

    return result;
}

static void//
jbig2_arith_renormd(Jbig2ArithState *as)
{
    /* Figure E.18 */
    do
    {
        if (as->CT == 0)
            jbig2_arith_bytein(as);
        as->A <<= 1;
        as->C <<= 1;
        as->CT--;
    }
    while ((as->A & 0x8000) == 0);
}

#if OPTI
char
jbig2_arith_decode(Jbig2ArithState *as, uint8_t *pcx) // , int *code
{
    uint8_t cx = *pcx;
    const Jbig2ArithQe *pqe;
    unsigned int index = cx & 0x7f;
    char D;

    if (index >= 47)
    {
        return 0;
    }
    else
    {
        pqe = &jbig2_arith_Qe[index];
    }

    /* Figure E.15 */
    as->A -= pqe->Qe;
    if (
        !((as->C >> 16) < pqe->Qe)
    )
    {
        as->C -= pqe->Qe << 16;
        if ((as->A & 0x8000) == 0)
        {
            /* MPS_EXCHANGE, Figure E.16 */
            if (as->A < pqe->Qe)
            {
                D = 1 - (cx >> 7);
                *pcx ^= pqe->lps_xor;
            }
            else
            {
                D = cx >> 7;
                *pcx ^= pqe->mps_xor;
            }

#if 0 //OPTI
            {
                /* Figure E.18 */
                do
                {
                    if (as->CT == 0)
                        jbig2_arith_bytein(as);
                    as->A <<= 1;
                    as->C <<= 1;
                    as->CT--;
                }
                while ((as->A & 0x8000) == 0);
            }
#else
            jbig2_arith_renormd(as);
#endif
            return D;
        }
        else
        {
            return cx >> 7;
        }
    }
    else
    {
        /* LPS_EXCHANGE, Figure E.17 */
        if (as->A < pqe->Qe)
        {
            as->A = pqe->Qe;
            D = cx >> 7;
            *pcx ^= pqe->mps_xor;
        }
        else
        {
            as->A = pqe->Qe;
            D = 1 - (cx >> 7);
            *pcx ^= pqe->lps_xor;
        }
#if 0 //OPTI
        {
            /* Figure E.18 */
            do
            {
                if (as->CT == 0)
                    jbig2_arith_bytein(as);
                as->A <<= 1;
                as->C <<= 1;
                as->CT--;
            }
            while ((as->A & 0x8000) == 0);
        }
#else
        jbig2_arith_renormd(as);
#endif
        return D;
    }
}
#else
char
jbig2_arith_decode(Jbig2ArithState *as, uint8_t *pcx, int *code)
{
    uint8_t cx = *pcx;
    const Jbig2ArithQe *pqe;
    unsigned int index = cx & 0x7f;
    char D;

    if (index >= 47)
    {
        *code = -1;
        return 0;
    }
    else
    {
        pqe = &jbig2_arith_Qe[index];
    }

    /* Figure E.15 */
    as->A -= pqe->Qe;
    if (
        !((as->C >> 16) < pqe->Qe)
    )
    {
        as->C -= pqe->Qe << 16;
        if ((as->A & 0x8000) == 0)
        {
            /* MPS_EXCHANGE, Figure E.16 */
            if (as->A < pqe->Qe)
            {
                D = 1 - (cx >> 7);
                *pcx ^= pqe->lps_xor;
            }
            else
            {
                D = cx >> 7;
                *pcx ^= pqe->mps_xor;
            }

#if 0 //OPTI
            {
                /* Figure E.18 */
                do
                {
                    if (as->CT == 0)
                        jbig2_arith_bytein(as);
                    as->A <<= 1;
                    as->C <<= 1;
                    as->CT--;
                }
                while ((as->A & 0x8000) == 0);
            }
#else
            jbig2_arith_renormd(as);
#endif
            *code = 0;
            return D;
        }
        else
        {
            *code = 0;
            return cx >> 7;
        }
    }
    else
    {
        /* LPS_EXCHANGE, Figure E.17 */
        if (as->A < pqe->Qe)
        {
            as->A = pqe->Qe;
            D = cx >> 7;
            *pcx ^= pqe->mps_xor;
        }
        else
        {
            as->A = pqe->Qe;
            D = 1 - (cx >> 7);
            *pcx ^= pqe->lps_xor;
        }
#if 0 //OPTI
        {
            /* Figure E.18 */
            do
            {
                if (as->CT == 0)
                    jbig2_arith_bytein(as);
                as->A <<= 1;
                as->C <<= 1;
                as->CT--;
            }
            while ((as->A & 0x8000) == 0);
        }
#else
        jbig2_arith_renormd(as);
#endif
        *code = 0;
        return D;
    }
}
#endif

void//
jbig2_image_free(Jbig2Ctx *ctx, Jbig2Image *image)
{
    if (image != NULL)
    {
        //jbig2_free(ctx->allocator, image->data);
        jbig2_free(ctx->allocator, image);
    }
}

void
jbig2_image_release(Jbig2Ctx *ctx, Jbig2Image *image)
{
    if (image == NULL)
        return;
    image->refcount--;
    if (image->refcount == 0)
        jbig2_image_free(ctx, image);
}

int
jbig2_parse_segment(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    uint8_t val = segment->flags & 63;
    if (val == 38 || val == 39)
    {
        unsigned char seg_flags;
        int8_t gbat[8];
        int offset;
        uint32_t gbat_bytes = 0;
        int code = 0;
        uint32_t stride;
        Jbig2Image *image = NULL;
        Jbig2WordStream *ws = NULL;
        Jbig2ArithState *as = NULL;
        uint8_t *GB_stats = NULL;
        uint32_t width, height;// x, y;
        //uint8_t flags;
        int stats_size;
        //int flag_t = 0;
        //Jbig2Page *page = &ctx->pages[ctx->current_page];

        /* 7.4.6 */

        width = jbig2_get_uint32(segment_data);
        height = jbig2_get_uint32(segment_data + 4);
        //x = jbig2_get_uint32(segment_data + 8);
        //y = jbig2_get_uint32(segment_data + 12);
        //flags = segment_data[16];

        /* 7.4.6.2 */
        seg_flags = segment_data[17];

        /* 7.4.6.3 */
        if (!(seg_flags & 1))
        {
            gbat_bytes = (seg_flags & 6) ? 2 : 8;
            memcpy(gbat, segment_data + 18, gbat_bytes);
        }

        offset = 18 + gbat_bytes;

        /* Check for T.88 amendment 2 */

        /* Table 34 */
        image = jbig2_new(ctx, Jbig2Image, 1);
        if (NULL == image)
        {
            rt_kprintf("malloc failed : fail to malloc image\n");
            return -1;
        }
        stride = ((width - 1) >> 3) + 1;

        if (height > (INT32_MAX / stride))
        {
            jbig2_free(ctx->allocator, image);
            image = NULL;
            return -1;
        }
        //if (image->data == NULL) {
        //  jbig2_free(ctx->allocator, image);
        //  return NULL;
        //}

        image->width = width;
        image->height = height;
        image->stride = stride;
        image->refcount = 1;

#if CONTEXT_13
        stats_size = 1 << 13;
#else
        stats_size = 1 << 16;
#endif
        GB_stats = jbig2_new(ctx, uint8_t, stats_size);
        if (NULL == GB_stats)
        {
            rt_kprintf("malloc failed : fail to malloc GB_stats\n");
            return -1;
        }
        memset(GB_stats, 0, stats_size);

        ws = jbig2_word_stream_buf_new(ctx, segment_data + offset, segment->data_length - offset);
        if (NULL == ws)
        {
            rt_kprintf("malloc failed : fail to malloc ws\n");
            return -1;
        }
        as = jbig2_arith_new(ctx, ws);
        if (NULL == as)
        {
            rt_kprintf("malloc failed : fail to malloc as\n");
            return -1;
        }

        code = -1;
        if (gbat[0] == +3 && gbat[1] == -1 && gbat[2] == -3 && gbat[3] == -1 && gbat[4] == +2 && gbat[5] == -2 && gbat[6] == -2 && gbat[7] == -2)
        {
            const uint32_t GBW = image->width;
            const uint32_t GBH = image->height;
            //const uint32_t rowstride = image->stride;
            uint32_t x, y;
            unsigned char *line2 = NULL;
            unsigned char *line1 = NULL;

            if (GBW <= 0)
                code = 0;

            for (y = 0; y < GBH; y++)
            {
                uint32_t CONTEXT;
                uint32_t line_m1;
                uint32_t line_m2;
                uint32_t padded_width = (GBW + 7) & -8;
                int code_t = 0;

#if CONTEXT_13
                line_m1 = line1 ? (line1[0]) : 0;
                line_m2 = line2 ? line2[0] << 4 : 0;
                CONTEXT = ((line_m1 >> 1) & 0x1f8) | (line_m2 & 0x1e00);
#else
                line_m1 = line1 ? line1[0] : 0;
                line_m2 = line2 ? line2[0] << 6 : 0;
                CONTEXT = (line_m1 & 0x7f0) | (line_m2 & 0xf800);
#endif

                for (x = 0; x < padded_width; x += 8)
                {
#if OPTI
                    unsigned char result = 0;
#else
                    unsigned char result = 0;
#endif
                    int x_minor;
                    int minor_width = GBW - x > 8 ? 8 : GBW - x;

                    if (line1)
                        line_m1 = (line_m1 << 8) | (x + 8 < GBW ? line1[(x >> 3) + 1] : 0);

                    if (line2)
                    {
#if CONTEXT_13
                        line_m2 = (line_m2 << 8) | (x + 8 < GBW ? line2[(x >> 3) + 1] << 4 : 0);
#else
                        line_m2 = (line_m2 << 8) | (x + 8 < GBW ? line2[(x >> 3) + 1] << 6 : 0);
#endif
                    }
#if OPTI
                    {
                        if (minor_width == 8)
                        {
                            uint8_t bit;
                            // 0
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[0] | ((line_m1 >> 7) & 0x10) | ((line_m2 >> 7) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (7 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (7)) & CONTEXT_VALUE2);
                            result = (bit << 7);
                            // 1
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[1] | ((line_m1 >> 6) & 0x10) | ((line_m2 >> 6) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (6 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (6)) & CONTEXT_VALUE2);
                            result |= (bit << 6);
                            // 2
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[2] | ((line_m1 >> 5) & 0x10) | ((line_m2 >> 5) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (5 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (5)) & CONTEXT_VALUE2);
                            result |= (bit << 5);
                            // 3
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[3] | ((line_m1 >> 4) & 0x10) | ((line_m2 >> 4) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (4 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (4)) & CONTEXT_VALUE2);
                            result |= (bit << 4);
                            // 4
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[4] | ((line_m1 >> 3) & 0x10) | ((line_m2 >> 3) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (3 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (3)) & CONTEXT_VALUE2);
                            result |= (bit << 3);
                            // 5
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[5] | ((line_m1 >> 2) & 0x10) | ((line_m2 >> 2) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (2 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (2)) & CONTEXT_VALUE2);
                            result |= (bit << 2);
                            // 6
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[6] | ((line_m1 >> 1) & 0x10) | ((line_m2 >> 1) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (1 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2 >> (1)) & CONTEXT_VALUE2);
                            result |= (bit << 1);
                            // 7
                            bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                            //if (code_t)
                            //  code = -1;
                            //code = code_t*2 - 1;
                            //CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit[7] | ((line_m1) & 0x10) | ((line_m2 ) & 0x800);
                            CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (0 + CONTEXT_VALUE3)) & CONTEXT_VALUE1) | ((line_m2)& CONTEXT_VALUE2);
                            result |= (bit);
                            //result = (bit[0] << 7) | (bit[1] << 6) | (bit[2] << 5) | (bit[3] << 4) | (bit[4] << 3) | (bit[5] << 2) | (bit[6] << 1) | (bit[7]) ;
                        }
                        else
                        {
                            for (x_minor = 0; x_minor < minor_width; x_minor++)
                            {
                                uint8_t bit;

                                bit = jbig2_arith_decode(as, &GB_stats[CONTEXT]);
                                if (code_t)
                                    return -1;
                                result |= bit << (7 - x_minor);
                                CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (7 + CONTEXT_VALUE3 - x_minor)) & CONTEXT_VALUE1) | ((line_m2 >> (7 - x_minor)) & CONTEXT_VALUE2);
                            }
                        }
                    }
#else
                    for (x_minor = 0; x_minor < minor_width; x_minor++)
                    {
                        uint8_t bit;

                        bit = jbig2_arith_decode(as, &GB_stats[CONTEXT], &code_t);
                        if (code_t)
                            return -1;
                        result |= bit << (7 - x_minor);
                        CONTEXT = ((CONTEXT & CONTEXT_VALUE0) << 1) | bit | ((line_m1 >> (7 + CONTEXT_VALUE3 - x_minor)) & CONTEXT_VALUE1) | ((line_m2 >> (7 - x_minor)) & CONTEXT_VALUE2);
                    }
#endif
                    if (result != 0)
                    {
                        fb[(y + yoffset) * (xVir >> 3) + ((x + xoffset) >> 3)] |= result;
                    }
                }
                line2 = line1;
                line1 = fb + (xVir / 8) * y;
            }

            code = 0;
        }

        jbig2_free(ctx->allocator, as);
        jbig2_free(ctx->allocator, ws);
        jbig2_free(ctx->allocator, GB_stats);
        jbig2_image_release(ctx, image);

        return code;
    }
    else if (48 == val)
    {
        return jbig2_page_info(ctx, segment, segment_data, 48);
    }
    else if (49 == val)
    {
        ctx->pages[ctx->current_page].state = JBIG2_PAGE_COMPLETE;
    }
    else if (51 == val)
    {
        ctx->state = JBIG2_FILE_EOF;
    }
    return 0;
}

int
jbig2_data_in(Jbig2Ctx *ctx, const unsigned char *data, size_t size, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    const size_t initial_buf_size = 1024;
    if (ctx->buf == NULL)
    {
        size_t buf_size = initial_buf_size;

        do
        {
            buf_size <<= 1;
        }
        while (buf_size < size);

        ctx->buf = jbig2_new(ctx, unsigned char, buf_size);
        //(unsigned char*)malloc(sizeof(unsigned char) * 2048);
        if (ctx->buf == NULL)
        {
            rt_kprintf("malloc failed: fail to malloc ctx->buf.\n");
            RT_ASSERT(0);
            return -1;
        }
        ctx->buf_size = buf_size;
        ctx->buf_rd_ix = 0;
        ctx->buf_wr_ix = 0;
    }
    else if (ctx->buf_wr_ix + size > ctx->buf_size)
    {
        if (ctx->buf_rd_ix <= (ctx->buf_size >> 1) && ctx->buf_wr_ix - ctx->buf_rd_ix + size <= ctx->buf_size)
        {
            memmove(ctx->buf, ctx->buf + ctx->buf_rd_ix, ctx->buf_wr_ix - ctx->buf_rd_ix);
        }
        else
        {
            unsigned char *buf;
            size_t buf_size = initial_buf_size;

            do
                buf_size <<= 1;
            while (buf_size < ctx->buf_wr_ix - ctx->buf_rd_ix + size);
            buf = jbig2_new(ctx, unsigned char, buf_size);
            //buf = (unsigned char*)malloc(sizeof(unsigned char) * buf_size);
            if (buf == NULL)
            {
                rt_kprintf("malloc failed: fail to malloc buf.\n");
                RT_ASSERT(0);
                return -1;
            }
            memcpy(buf, ctx->buf + ctx->buf_rd_ix, ctx->buf_wr_ix - ctx->buf_rd_ix);
            jbig2_free(ctx->allocator, ctx->buf);
            ctx->buf = buf;
            ctx->buf_size = buf_size;
        }
        ctx->buf_wr_ix -= ctx->buf_rd_ix;
        ctx->buf_rd_ix = 0;
    }
    memcpy(ctx->buf + ctx->buf_wr_ix, data, size);
    ctx->buf_wr_ix += size;

    /* data has now been added to buffer */

    while (1)
    {
        if (JBIG2_FILE_HEADER == ctx->state)
        {
            if (ctx->buf_wr_ix - ctx->buf_rd_ix < 9)
                return 0;
            const unsigned char jbig2_id_string[8] = { 0x97, 0x4a, 0x42, 0x32, 0x0d, 0x0a, 0x1a, 0x0a };
            if (memcmp(ctx->buf + ctx->buf_rd_ix, jbig2_id_string, 8))
            {
                jbig2_free(ctx->allocator, ctx->buf);
                RT_ASSERT(0);
                return -1;
            }
            /* Check for T.88 amendment 2 */
            if ((ctx->buf[ctx->buf_rd_ix + 8] & 0x04) || (ctx->buf[ctx->buf_rd_ix + 8] & 0x08))
            {
                jbig2_free(ctx->allocator, ctx->buf);
                RT_ASSERT(0);
                return -1;
            }
            /* D.4.3 */
            if (ctx->buf_wr_ix - ctx->buf_rd_ix < 13)
                return 0;
            ctx->buf_rd_ix += 13;
            ctx->state = JBIG2_FILE_SEQUENTIAL_HEADER;
        }
        else if (JBIG2_FILE_SEQUENTIAL_HEADER == ctx->state)
        {
            size_t header_size;
            Jbig2Segment *segment = jbig2_parse_segment_header(ctx, ctx->buf + ctx->buf_rd_ix, ctx->buf_wr_ix - ctx->buf_rd_ix, &header_size);
            if (segment == NULL)
                return 0;
            ctx->buf_rd_ix += header_size;

            ctx->segments[ctx->n_segments++] = segment;
            ctx->state = JBIG2_FILE_SEQUENTIAL_BODY;
        }
        else if (JBIG2_FILE_SEQUENTIAL_BODY == ctx->state)
        {
            Jbig2Segment *segment = ctx->segments[ctx->segment_index];
            if (segment->data_length > ctx->buf_wr_ix - ctx->buf_rd_ix)
                return 0;

            int code = jbig2_parse_segment(ctx, segment, ctx->buf + ctx->buf_rd_ix, fb, xVir, xoffset, yoffset);
            ctx->buf_rd_ix += segment->data_length;
            ctx->segment_index++;
            ctx->state = JBIG2_FILE_SEQUENTIAL_HEADER;
            if (code < 0)
            {
                ctx->state = JBIG2_FILE_EOF;
                jbig2_free(ctx->allocator, ctx->buf);
                RT_ASSERT(0);
                return -1;
            }
        }
        else if (JBIG2_FILE_EOF == ctx->state)
        {
            if (ctx->buf_rd_ix == ctx->buf_wr_ix)
                return 0;

            jbig2_free(ctx->allocator, ctx->buf);
            RT_ASSERT(0);
            return -1;
        }
    }
    return 0;
}

static void
flush_errors(jbig2dec_params_t *params)
{
    if (params->repeats > 1)
    {
        fprintf(stderr, "jbig2dec last message repeated %ld times\n", params->repeats);
    }
}

Jbig2Allocator *//
jbig2_ctx_free(Jbig2Ctx *ctx)
{
    Jbig2Allocator *ca;
    int i;

    if (ctx == NULL)
    {
        //rt_kprintf("9-----------------------------------------------\n");
        return NULL;
    }
    ca = ctx->allocator;
    jbig2_free(ca, ctx->buf);
    if (ctx->segments != NULL)
    {
        for (i = 0; i < ctx->n_segments; i++)
        {
            if (ctx->segments[i] == NULL)
                continue;
            jbig2_free(ctx->allocator, ctx->segments[i]->referred_to_segments);
            if ((4 == (ctx->segments[i]->flags & 63) || 40 == (ctx->segments[i]->flags & 63)) && ctx->segments[i]->result != NULL)
            {
                jbig2_image_release(ctx, (Jbig2Image *)ctx->segments[i]->result);
            }
            jbig2_free(ctx->allocator, ctx->segments[i]);
        }
        jbig2_free(ca, ctx->segments);
    }

    if (ctx->pages != NULL)
    {
        for (i = 0; i <= ctx->current_page; i++)
            if (ctx->pages[i].image != NULL)
                jbig2_image_release(ctx, ctx->pages[i].image);
        jbig2_free(ca, ctx->pages);
    }

    jbig2_free(ca, ctx);

    return ca;
}

int jbig2_decompression(image_info_t *img_info, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{

    Jbig2Ctx *ctx = NULL;
    uint8_t buf[4096];
    jbig2dec_params_t params;


    uint8_t read_flag = 0;
    uint32_t size = img_info->size;
    uint8_t i = 0;

    /* set defaults */
    params.mode = render;
    params.verbose = 1;
    params.output_filename = NULL;
    params.output_format = jbig2dec_format_none;
    params.embedded = 0;
    params.last_message = NULL;
    params.repeats = 0;

    ctx = jbig2_ctx_new(NULL);

    /* pull the whole file/global stream into memory */
    while (1)
    {
        int n_bytes;
        if (read_flag == 1)
        {
            break;
        }

        if (size > 4096)
        {
            memcpy(buf, img_info->data + i * 4096, sizeof(buf));
            size = size - 4096;
            n_bytes = 4096;
        }
        else
        {
            memcpy(buf, img_info->data + i * 4096, size * sizeof(buf[0]));
            n_bytes = size;
            read_flag = 1;
        }
        i++;

        if (jbig2_data_in(ctx, buf, n_bytes, fb, xVir, xoffset, yoffset))
        {
            printf("error return from decompressing process\n");
            RT_ASSERT(0);
            break;
        }
    }
    flush_errors(&params);
    jbig2_ctx_free(ctx);
    return 0;
}
#endif