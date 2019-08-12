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

#if !defined (UINT32_MAX)
#define UINT32_MAX 0xffffffff
#endif

#define get_uint16(bptr)\
    (((bptr)[0] << 8) | (bptr)[1])
#define get_int16(bptr)\
    (((int)get_uint16(bptr) ^ 0x8000) - 0x8000)

#define MAX_QE_ARRAY_SIZE 47



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

uint16_t
jbig2_get_uint16(const unsigned char *bptr)
{
    return get_uint16(bptr);
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

const Jbig2ArithQe jbig2_arith_Qe[MAX_QE_ARRAY_SIZE] =
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
    /* Check for integer multiplication overflow when computing
    the full size of the allocation. */
    //if (num > 0 && size > SIZE_MAX / num)
    //rt_kprintf("size is %d and num is %d\n", size, num);
    if (num > 0 && size > SIZE_MAX / num)
    {
        return NULL;
    }

    return allocator->alloc(allocator, size * num);
}

void *
jbig2_realloc(Jbig2Allocator *allocator, void *p, size_t size, size_t num)
{
    /* check for integer multiplication overflow */
    if (num > 0 && size >= SIZE_MAX / num)
        return NULL;
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
        return NULL;

    //result = jbig2_new(ctx, Jbig2Segment, 1);
    result = (Jbig2Segment *)malloc(sizeof(Jbig2Segment) * 1);
    if (result == NULL)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate segment");
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
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, result->number, "insufficient data to parse segment header", -1);
        jbig2_free(ctx->allocator, result);
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
            jbig2_error(ctx, JBIG2_SEVERITY_FATAL, result->number, "failed to allocate referred to segments");
            return NULL;
        }

        for (i = 0; i < referred_to_segment_count; i++)
        {
            referred_to_segments[i] =
                (referred_to_segment_size == 1) ? buf[offset] :
                (referred_to_segment_size == 2) ? jbig2_get_uint16(buf + offset) : jbig2_get_uint32(buf + offset);
            offset += referred_to_segment_size;
            jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, result->number, "segment %d refers to segment %d", result->number, referred_to_segments[i]);
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
    jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, result->number, "segment %d is associated with page %d", result->number, result->page_association);

    /* 7.2.7 */
    result->rows = UINT32_MAX;
    result->data_length = jbig2_get_uint32(buf + offset);
    *p_header_size = offset + 4;

    /* no body parsing results yet */
    result->result = NULL;

    return result;
}

Jbig2Ctx *
jbig2_ctx_new(Jbig2Allocator *allocator, Jbig2Options options, Jbig2GlobalCtx *global_ctx, Jbig2ErrorCallback error_callback, void *error_callback_data)
{
    Jbig2Ctx *result;

    if (allocator == NULL)
        allocator = &jbig2_default_allocator;

    result = (Jbig2Ctx *)jbig2_alloc(allocator, sizeof(Jbig2Ctx), 1);

    result->allocator = allocator;
    result->options = options;
    result->global_ctx = (const Jbig2Ctx *)global_ctx;
    result->error_callback = error_callback;
    result->error_callback_data = error_callback_data;

    result->state = (options & JBIG2_OPTIONS_EMBEDDED) ? JBIG2_FILE_SEQUENTIAL_HEADER : JBIG2_FILE_HEADER;

    result->buf = NULL;

    result->n_segments = 0;
    result->n_segments_max = 16;
    result->segments = jbig2_new(result, Jbig2Segment *, result->n_segments_max);
    //result->segments == (Jbig2Segment **)malloc(sizeof(Jbig2Segment *) * result->n_segments_max);
    if (NULL == result->segments)
    {
        rt_kprintf("------------------------------fail to malloc-------------------------------\n");
    }
    result->segment_index = 0;

    result->current_page = 0;
    result->max_page_index = 4;
    result->pages = jbig2_new(result, Jbig2Page, result->max_page_index);
    //result->pages = (Jbig2Page *)malloc(sizeof(Jbig2Page) * result->max_page_index);
    if (NULL == result->pages)
    {
        rt_kprintf("------------------------------fail to malloc-------------------------------\n");
    }

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
            result->pages[index].stripe_size = 0;
            result->pages[index].striped = 0;
            result->pages[index].end_row = 0;
            result->pages[index].flags = 0;
            result->pages[index].image = NULL;
        }
    }

    return result;
}

static void
error_callback(void *error_callback_data, const char *buf, Jbig2Severity severity, int32_t seg_idx)
{
    jbig2dec_params_t *params = (jbig2dec_params_t *)error_callback_data;
    char *type;
    char segment[22];
    int len;
    char *message;

    switch (severity)
    {
    case JBIG2_SEVERITY_DEBUG:
        if (params->verbose < 3)
            return;
        type = "DEBUG";
        break;
    case JBIG2_SEVERITY_INFO:
        if (params->verbose < 2)
            return;
        type = "info";
        break;
    case JBIG2_SEVERITY_WARNING:
        if (params->verbose < 1)
            return;
        type = "WARNING";
        break;
    case JBIG2_SEVERITY_FATAL:
        type = "FATAL ERROR";
        break;
    default:
        type = "unknown message";
        break;
    }
    if (seg_idx == -1)
        segment[0] = '\0';
    else
        snprintf(segment, sizeof(segment), "(segment 0x%02x)", seg_idx);

    len = snprintf(NULL, 0, "jbig2dec %s %s %s", type, buf, segment);
    if (len < 0)
    {
        return;
    }

    message = malloc(len + 1);
    if (message == NULL)
    {
        return;
    }

    len = snprintf(message, len + 1, "jbig2dec %s %s %s", type, buf, segment);
    if (len < 0)
    {
        free(message);
        return;
    }

    if (params->last_message != NULL && strcmp(message, params->last_message))
    {
        if (params->repeats > 1)
            fprintf(stderr, "jbig2dec %s last message repeated %ld times\n", params->type, params->repeats);
        fprintf(stderr, "%s\n", message);
        free(params->last_message);
        params->last_message = message;
        params->severity = severity;
        params->type = type;
        params->repeats = 0;
    }
    else if (params->last_message != NULL)
    {
        params->repeats++;
        if (params->repeats % 1000000 == 0)
            fprintf(stderr, "jbig2dec %s last message repeated %ld times so far\n", params->type, params->repeats);
        free(message);
    }
    else if (params->last_message == NULL)
    {
        fprintf(stderr, "%s\n", message);
        params->last_message = message;
        params->severity = severity;
        params->type = type;
        params->repeats = 0;
    }
}

int
jbig2_error(Jbig2Ctx *ctx, Jbig2Severity severity, int32_t segment_number, const char *fmt, ...)
{
    char buf[1024];
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    if (n < 0 || n == sizeof(buf))
        strncpy(buf, "failed to generate error string", sizeof(buf));
    ctx->error_callback(ctx->error_callback_data, buf, severity, segment_number);
    return -1;
}

void
jbig2_image_clear(Jbig2Ctx *ctx, Jbig2Image *image, int value)
{
    const uint8_t fill = value ? 0xFF : 0x00;

    //memset(image->data, fill, image->stride * image->height);
    //memset(image->data, fill, 1 * image->height);
}

/* allocate a Jbig2Image structure and its associated bitmap */
Jbig2Image *
jbig2_image_new(Jbig2Ctx *ctx, uint32_t width, uint32_t height, uint32_t flag)
{
    Jbig2Image *image;
    uint32_t stride;

    if (width == 0 || height == 0)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to create zero sized image");
        return NULL;
    }

    image = jbig2_new(ctx, Jbig2Image, 1);
    //image = (Jbig2Image *)malloc(sizeof(Jbig2Image) * 1);
    if (image == NULL)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate image");
        return NULL;
    }

    stride = ((width - 1) >> 3) + 1;    /* generate a byte-aligned stride */

    /* check for integer multiplication overflow */
    if (height > (INT32_MAX / stride))
    {
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "integer multiplication overflow (stride=%u, height=%u)", stride, height);
        jbig2_free(ctx->allocator, image);
        return NULL;
    }
    //image->data = jbig2_new(ctx, uint8_t, (size_t)height * stride);
    //image->data = (uint8_t *)malloc(sizeof(uint8_t) * (size_t)height * stride);
    if (flag == 48)
    {
    }
    else if (flag == 38)
        image->data = jbig2_new(ctx, uint8_t, (size_t)1 * stride);
    if (image->data == NULL)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate image data buffer (stride=%u, height=%u)", stride, height);
        jbig2_free(ctx->allocator, image);
        return NULL;
    }

    image->width = width;
    image->height = height;
    image->stride = stride;
    image->refcount = 1;

    return image;
}

static void
dump_page_info(Jbig2Ctx *ctx, Jbig2Segment *segment, Jbig2Page *page)
{
    if (page->x_resolution == 0)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "page %d image is %dx%d (unknown res)", page->number, page->width, page->height);
    }
    else if (page->x_resolution == page->y_resolution)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "page %d image is %dx%d (%d ppm)", page->number, page->width, page->height, page->x_resolution);
    }
    else
    {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number,
                    "page %d image is %dx%d (%dx%d ppm)", page->number, page->width, page->height, page->x_resolution, page->y_resolution);
    }
    if (page->striped)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "\tmaximum stripe size: %d", page->stripe_size);
    }
}

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
                pages = jbig2_renew(ctx, ctx->pages, Jbig2Page, (ctx->max_page_index <<= 2));
                if (pages == NULL)
                {
                    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "failed to reallocate pages");
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
    /* Check for T.88 amendment 3 */

    /* 7.4.8.6 */
    {
        int16_t striping = jbig2_get_int16(segment_data + 17);

        if (striping & 0x8000)
        {
        }
        else
        {
            page->striped = 0;
            page->stripe_size = 0;      /* would page->height be better? */
        }
    }
    page->end_row = 0;

    dump_page_info(ctx, segment, page);

    /* allocate an appropriate page image buffer */
    /* 7.4.8.2 */
    if (page->height == 0xFFFFFFFF)
    {
    }
    else
    {
        page->image = jbig2_image_new(ctx, page->width, page->height, flag);
    }
    if (page->image == NULL)
    {
    }
    else
    {
        /* 8.2 (3) fill the page with the default pixel value */
        jbig2_image_clear(ctx, page->image, (page->flags & 4));
        jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, segment->number,
                    "allocated %dx%d page image (%d bytes)", page->image->width, page->image->height, page->image->stride * page->image->height);
    }

    return 0;
}

int
jbig2_complete_page(Jbig2Ctx *ctx)
{
    if (ctx->segment_index != ctx->n_segments)
    {
        Jbig2Segment *segment = ctx->segments[ctx->segment_index];
    }

    ctx->pages[ctx->current_page].state = JBIG2_PAGE_COMPLETE;
    return 0;
}

int
jbig2_end_of_page(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data)
{
    uint32_t page_number = ctx->pages[ctx->current_page].number;
    int code;

    if (segment->page_association != page_number)
    {
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number,
                    "end of page marker for page %d doesn't match current page number %d", segment->page_association, page_number);
    }

    jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "end of page %d", page_number);

    code = jbig2_complete_page(ctx);
    if (code < 0)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "failed to complete page");

    return 0;
}

void//
jbig2_get_region_segment_info(Jbig2RegionSegmentInfo *info, const uint8_t *segment_data)
{
    /* 7.4.1 */
    info->width = jbig2_get_uint32(segment_data);
    info->height = jbig2_get_uint32(segment_data + 4);
    info->x = jbig2_get_uint32(segment_data + 8);
    info->y = jbig2_get_uint32(segment_data + 12);
    info->flags = segment_data[16];
    info->op = (Jbig2ComposeOp)(info->flags & 0x7);
}

int//
jbig2_generic_stats_size(Jbig2Ctx *ctx, int template)
{
    int stats_size = template == 0 ? 1 << 16 : template == 1 ? 1 << 13 : 1 << 10;

                                        return stats_size;
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
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate word stream");
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
        jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate arithmetic coding state");
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

char//
jbig2_arith_decode(Jbig2ArithState *as, Jbig2ArithCx *pcx, int *code)
{
    Jbig2ArithCx cx = *pcx;
    const Jbig2ArithQe *pqe;
    unsigned int index = cx & 0x7f;
    char D;

    if (index >= MAX_QE_ARRAY_SIZE)
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
            jbig2_arith_renormd(as);
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
        jbig2_arith_renormd(as);
        *code = 0;
        return D;
    }
}


static int//
jbig2_decode_generic_template0(Jbig2Ctx *ctx,
                               Jbig2Segment *segment,
                               const Jbig2GenericRegionParams *params, Jbig2ArithState *as,
                               Jbig2Image *image, Jbig2ArithCx *GB_stats,
                               rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{

    const uint32_t GBW = image->width;
    const uint32_t GBH = image->height;
    const uint32_t rowstride = image->stride;
    uint32_t x, y;
    unsigned char *line2 = NULL;
    unsigned char *line1 = NULL;
    //unsigned char *gbreg_line = (unsigned char *)image->data;

    if (GBW <= 0)
        return 0;

    for (y = 0; y < GBH; y++)
    {
        uint32_t CONTEXT;
        uint32_t line_m1;
        uint32_t line_m2;
        uint32_t padded_width = (GBW + 7) & -8;
        int code = 0;

        line_m1 = line1 ? line1[0] : 0;
        line_m2 = line2 ? line2[0] << 6 : 0;
        CONTEXT = (line_m1 & 0x7f0) | (line_m2 & 0xf800);

        /* 6.2.5.7 3d */
        for (x = 0; x < padded_width; x += 8)
        {
            unsigned char result = 0;
            int x_minor;
            int minor_width = GBW - x > 8 ? 8 : GBW - x;

            if (line1)
                line_m1 = (line_m1 << 8) | (x + 8 < GBW ? line1[(x >> 3) + 1] : 0);

            if (line2)
                line_m2 = (line_m2 << 8) | (x + 8 < GBW ? line2[(x >> 3) + 1] << 6 : 0);

            /* This is the speed-critical inner loop. */
            for (x_minor = 0; x_minor < minor_width; x_minor++)
            {
                uint8_t bit;

                bit = jbig2_arith_decode(as, &GB_stats[CONTEXT], &code);
                if (code)
                    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "failed to decode arithmetic code when handling generic template0 optimized");
                result |= bit << (7 - x_minor);
                CONTEXT = ((CONTEXT & 0x7bf7) << 1) | bit | ((line_m1 >> (7 - x_minor)) & 0x10) | ((line_m2 >> (7 - x_minor)) & 0x800);
            }
            //gbreg_line[x >> 3] = result;
            fb[(y + yoffset) * (xVir / 8) + (x + xoffset) / 8] |= result;
        }

        line2 = line1;
        line1 = fb + (xVir / 8) * y;
        //gbreg_line += rowstride;
    }

    return 0;
}

int//
jbig2_decode_generic_region(Jbig2Ctx *ctx,
                            Jbig2Segment *segment, const Jbig2GenericRegionParams *params, Jbig2ArithState *as, Jbig2Image *image, Jbig2ArithCx *GB_stats
                            , rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    const int8_t *gbat = params->gbat;

    if (!params->MMR && params->GBTEMPLATE == 0)
    {

        if (!params->USESKIP && gbat[0] == +3 && gbat[1] == -1 && gbat[2] == -3 && gbat[3] == -1 && gbat[4] == +2 && gbat[5] == -2 && gbat[6] == -2 && gbat[7] == -2)
            return jbig2_decode_generic_template0(ctx, segment, params, as, image, GB_stats, fb, xVir, xoffset, yoffset);
    }

    {
        int i;

        for (i = 0; i < 8; i++)
            jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, segment->number, "gbat[%d] = %d", i, params->gbat[i]);
    }

    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "unsupported generic region (MMR=%d, GBTEMPLATE=%d)", params->MMR, params->GBTEMPLATE);
}

int
jbig2_image_compose(Jbig2Ctx *ctx, Jbig2Image *dst, Jbig2Image *src, int x, int y, Jbig2ComposeOp op)
{
    uint32_t i, j;
    uint32_t w, h;
    uint32_t leftbyte, rightbyte;
    uint32_t shift;
    uint8_t *s, *ss;
    uint8_t *d, *dd;
    uint8_t mask, rightmask;

    /* The optimized code for the OR operator below doesn't
    handle the source image partially placed outside the
    destination (above and/or to the left). The affected
    intersection of the destination is computed correctly,
    however the correct subset of the source image is not
    chosen. Instead the upper left corner of the source image
    is always used.

    In the unoptimized version that handles all operators
    (including OR) the correct subset of the source image is
    chosen.

    The workaround is to check whether the x/y coordinates to
    the composition operator are negative and in this case use
    the unoptimized implementation.

    TODO: Fix the optimized OR implementation if possible. */

    /* optimized code for the prevalent OR operator */

    /* clip */
    w = src->width;
    h = src->height;
    ss = src->data;

    if (x < 0)
    {
        if (w < (uint32_t) - x)
            w = 0;
        else
            w += x;
        x = 0;
    }
    if (y < 0)
    {
        if (h < (uint32_t) - y)
            h = 0;
        else
            h += y;
        y = 0;
    }
    w = ((uint32_t)x + w < dst->width) ? w : ((dst->width >= (uint32_t)x) ? dst->width - (uint32_t)x : 0);
    h = ((uint32_t)y + h < dst->height) ? h : ((dst->height >= (uint32_t)y) ? dst->height - (uint32_t)y : 0);

    /* check for zero clipping region */
    if ((w <= 0) || (h <= 0))
    {
        return 0;
    }

    leftbyte = (uint32_t)x >> 3;
    rightbyte = ((uint32_t)x + w - 1) >> 3;
    shift = x & 7;

    /* general OR case */
    s = ss;
    d = dd = dst->data + y * dst->stride + leftbyte;
    if (d < dst->data ||
            leftbyte > dst->stride ||
            d - leftbyte + (size_t)h * dst->stride > dst->data + (size_t)dst->height * dst->stride ||
            s - leftbyte + (size_t)(h - 1) * src->stride + rightbyte > src->data + (size_t)src->height * src->stride)
    {
        return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "preventing heap overflow in jbig2_image_compose");
    }
    if (leftbyte == rightbyte)
    {
        mask = 0x100 - (0x100 >> w);
        for (j = 0; j < h; j++)
        {
            *d |= (*s & mask) >> shift;
            d += dst->stride;
            s += src->stride;
        }
    }
    else if (shift == 0)
    {
        rightmask = (w & 7) ? 0x100 - (1 << (8 - (w & 7))) : 0xFF;
        for (j = 0; j < h; j++)
        {
            for (i = leftbyte; i < rightbyte; i++)
                *d++ |= *s++;
            *d |= *s & rightmask;
            d = (dd += dst->stride);
            s = (ss += src->stride);
        }
    }
    else
    {
        char overlap = (((w + 7) >> 3) < ((x + w + 7) >> 3) - (x >> 3));

        mask = 0x100 - (1 << shift);
        if (overlap)
            rightmask = (0x100 - (0x100 >> ((x + w) & 7))) >> (8 - shift);
        else
            rightmask = 0x100 - (0x100 >> (w & 7));
        for (j = 0; j < h; j++)
        {
            *d++ |= (*s & mask) >> shift;
            for (i = leftbyte; i < rightbyte - 1; i++)
            {
                *d |= ((*s++ & ~mask) << (8 - shift));
                *d++ |= ((*s & mask) >> shift);
            }
            if (overlap)
                *d |= (*s & rightmask) << (8 - shift);
            else
                *d |= ((s[0] & ~mask) << (8 - shift)) | ((s[1] & rightmask) >> shift);
            d = (dd += dst->stride);
            s = (ss += src->stride);
        }
    }

    return 0;
}

int//
jbig2_page_add_result(Jbig2Ctx *ctx, Jbig2Page *page, Jbig2Image *image, uint32_t x, uint32_t y, Jbig2ComposeOp op)
{
    int code;
    /* ensure image exists first */
    if (page->image == NULL)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "page info possibly missing, no image defined");

    code = jbig2_image_compose(ctx, page->image, image, x, y, op);
    if (code < 0)
        return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "failed to compose image with page");

    return 0;
}

void
jbig2_word_stream_buf_free(Jbig2Ctx *ctx, Jbig2WordStream *ws)
{
    jbig2_free(ctx->allocator, ws);
}

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

int//
jbig2_immediate_generic_region(Jbig2Ctx *ctx, Jbig2Segment *segment, const unsigned char *segment_data, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset, rt_int32_t flag)
{
    Jbig2RegionSegmentInfo rsi;
    unsigned char seg_flags;
    int8_t gbat[8];
    int offset;
    uint32_t gbat_bytes = 0;
    Jbig2GenericRegionParams params;
    int code = 0;
    Jbig2Image *image = NULL;
    Jbig2WordStream *ws = NULL;
    Jbig2ArithState *as = NULL;
    Jbig2ArithCx *GB_stats = NULL;
    uint32_t height;
    Jbig2Page *page = &ctx->pages[ctx->current_page];

    /* 7.4.6 */

    jbig2_get_region_segment_info(&rsi, segment_data);
    jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "generic region: %u x %u @ (%u, %u), flags = %02x", rsi.width, rsi.height, rsi.x, rsi.y, rsi.flags);

    /* 7.4.6.4 */
    height = rsi.height;

    /* 7.4.6.2 */
    seg_flags = segment_data[17];
    jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "segment flags = %02x", seg_flags);

    /* 7.4.6.3 */
    if (!(seg_flags & 1))
    {
        gbat_bytes = (seg_flags & 6) ? 2 : 8;
        memcpy(gbat, segment_data + 18, gbat_bytes);
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "gbat: %d, %d", gbat[0], gbat[1]);
    }

    offset = 18 + gbat_bytes;

    /* Check for T.88 amendment 2 */

    /* Table 34 */
    params.MMR = seg_flags & 1;
    params.GBTEMPLATE = (seg_flags & 6) >> 1;
    params.TPGDON = (seg_flags & 8) >> 3;
    params.USESKIP = 0;
    memcpy(params.gbat, gbat, gbat_bytes);

    image = jbig2_image_new(ctx, rsi.width, height, flag);
    jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, segment->number, "allocated %d x %d image buffer for region decode results", rsi.width, height);

    if (params.MMR)
    {
    }
    else
    {
        int stats_size = jbig2_generic_stats_size(ctx, params.GBTEMPLATE);

        GB_stats = jbig2_new(ctx, Jbig2ArithCx, stats_size);
        //GB_stats = (Jbig2ArithCx *)malloc(sizeof(Jbig2ArithCx) * stats_size);
        memset(GB_stats, 0, stats_size);

        ws = jbig2_word_stream_buf_new(ctx, segment_data + offset, segment->data_length - offset);
        as = jbig2_arith_new(ctx, ws);
        code = jbig2_decode_generic_region(ctx, segment, &params, as, image, GB_stats, fb, xVir, xoffset, yoffset);
    }

    //code = jbig2_page_add_result(ctx, &ctx->pages[ctx->current_page], image, rsi.x, rsi.y, rsi.op);

    jbig2_free(ctx->allocator, as);
    jbig2_word_stream_buf_free(ctx, ws);
    jbig2_free(ctx->allocator, GB_stats);
    jbig2_image_release(ctx, image);

    return code;
}

int
jbig2_parse_segment(Jbig2Ctx *ctx, Jbig2Segment *segment, const uint8_t *segment_data, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number,
                "segment %d, flags=%x, type=%d, data_length=%d", segment->number, segment->flags, segment->flags & 63, segment->data_length);
    switch (segment->flags & 63)
    {
    case 38:                   /* immediate generic region */
    case 39:                   /* immediate lossless generic region */
        return jbig2_immediate_generic_region(ctx, segment, segment_data, fb, xVir, xoffset, yoffset, 38);
    case 48:
        return jbig2_page_info(ctx, segment, segment_data, 48);
    case 49:
        return jbig2_end_of_page(ctx, segment, segment_data);
    case 51:
        ctx->state = JBIG2_FILE_EOF;
        jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "end of file");
        break;
    default:
        jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "unknown segment type %d", segment->flags & 63);
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

        //rt_kprintf("buf_size == %d; size = %d\n", buf_size, size);

        ctx->buf = jbig2_new(ctx, unsigned char, buf_size);
        //(unsigned char*)malloc(sizeof(unsigned char) * 2048);
        if (ctx->buf == NULL)
        {
            //rt_kprintf("aaaaaaaaaaaaaaaaaaa\n");
            return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate buffer when reading data");
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
                return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "failed to allocate bigger buffer when reading data");
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

    for (;;)
    {
        const unsigned char jbig2_id_string[8] = { 0x97, 0x4a, 0x42, 0x32, 0x0d, 0x0a, 0x1a, 0x0a };
        Jbig2Segment *segment;
        size_t header_size;
        int code;

        switch (ctx->state)
        {
        case JBIG2_FILE_HEADER:
            //rt_kprintf("2222222222222222222222222222222222222222222222233333333333333333333\n");
            /* D.4.1 */
            if (ctx->buf_wr_ix - ctx->buf_rd_ix < 9)
                return 0;
            if (memcmp(ctx->buf + ctx->buf_rd_ix, jbig2_id_string, 8))
                return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "not a JBIG2 file header");
            /* D.4.2 */
            ctx->file_header_flags = ctx->buf[ctx->buf_rd_ix + 8];
            /* Check for T.88 amendment 2 */
            if (ctx->file_header_flags & 0x04)
                return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "file header indicates use of 12 adaptive template pixels (NYI)");
            /* Check for T.88 amendment 3 */
            if (ctx->file_header_flags & 0x08)
                return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, -1, "file header indicates use of colored region segments (NYI)");
            if (ctx->file_header_flags & 0xFC)
            {
                jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "reserved bits (2-7) of file header flags are not zero (0x%02x)", ctx->file_header_flags);
            }
            /* D.4.3 */
            if (!(ctx->file_header_flags & 2))          /* number of pages is known */
            {
                if (ctx->buf_wr_ix - ctx->buf_rd_ix < 13)
                    return 0;
                ctx->n_pages = jbig2_get_uint32(ctx->buf + ctx->buf_rd_ix + 9);
                ctx->buf_rd_ix += 13;
                if (ctx->n_pages == 1)
                    jbig2_error(ctx, JBIG2_SEVERITY_INFO, -1, "file header indicates a single page document");
                else
                    jbig2_error(ctx, JBIG2_SEVERITY_INFO, -1, "file header indicates a %d page document", ctx->n_pages);
            }
            else              /* number of pages not known */
            {
                ctx->n_pages = 0;
                ctx->buf_rd_ix += 9;
            }
            /* determine the file organization based on the flags - D.4.2 again */
            if (ctx->file_header_flags & 1)
            {
                ctx->state = JBIG2_FILE_SEQUENTIAL_HEADER;
                jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "file header indicates sequential organization");
            }
            else
            {
                ctx->state = JBIG2_FILE_RANDOM_HEADERS;
                jbig2_error(ctx, JBIG2_SEVERITY_DEBUG, -1, "file header indicates random-access organization");
            }
            break;
        case JBIG2_FILE_SEQUENTIAL_HEADER:
        case JBIG2_FILE_RANDOM_HEADERS:
            //rt_kprintf("2222222222222222222222222224444444444444444444444444444444444\n");
            segment = jbig2_parse_segment_header(ctx, ctx->buf + ctx->buf_rd_ix, ctx->buf_wr_ix - ctx->buf_rd_ix, &header_size);
            if (segment == NULL)
                return 0; /* need more data */
            ctx->buf_rd_ix += header_size;

            if (ctx->n_segments == ctx->n_segments_max)
            {
                Jbig2Segment **segments;

                segments = jbig2_renew(ctx, ctx->segments, Jbig2Segment *, (ctx->n_segments_max <<= 2));
                if (segments == NULL)
                {
                    ctx->state = JBIG2_FILE_EOF;
                    return jbig2_error(ctx, JBIG2_SEVERITY_FATAL, segment->number, "failed to allocate space for more segments");
                }
                ctx->segments = segments;
            }


            ctx->segments[ctx->n_segments++] = segment;
            if (ctx->state == JBIG2_FILE_RANDOM_HEADERS)
            {
                if ((segment->flags & 63) == 51)        /* end of file */
                    ctx->state = JBIG2_FILE_RANDOM_BODIES;
            }
            else              /* JBIG2_FILE_SEQUENTIAL_HEADER */
                ctx->state = JBIG2_FILE_SEQUENTIAL_BODY;
            break;
        case JBIG2_FILE_SEQUENTIAL_BODY:
        case JBIG2_FILE_RANDOM_BODIES:
            //rt_kprintf("222222222222222222222222222555555555555555555555555555555555555\n");
            segment = ctx->segments[ctx->segment_index];

            /* immediate generic regions may have unknown size */
            if (segment->data_length == 0xffffffff && (segment->flags & 63) == 38)
            {
                unsigned char *s, *e, *p;
                int mmr;
                unsigned char mmr_marker[2] = { 0x00, 0x00 };
                unsigned char arith_marker[2] = { 0xff, 0xac };
                unsigned char *desired_marker;

                s = p = ctx->buf + ctx->buf_rd_ix;
                e = ctx->buf + ctx->buf_wr_ix;

                if (e - p < 18)
                    return 0; /* need more data */

                mmr = p[17] & 1;
                p += 18;
                desired_marker = mmr ? mmr_marker : arith_marker;

                /* look for two byte marker */
                if (e - p < 2)
                    return 0; /* need more data */

                while (p[0] != desired_marker[0] || p[1] != desired_marker[1])
                {
                    p++;
                    if (e - p < 2)
                        return 0; /* need more data */
                }
                p += 2;

                /* the marker is followed by a four byte row count */
                if (e - p < 4)
                    return 0; /* need more data */
                segment->rows = jbig2_get_uint32(p);
                p += 4;

                segment->data_length = p - s;
                jbig2_error(ctx, JBIG2_SEVERITY_INFO, segment->number, "unknown length determined to be %u", segment->data_length);
            }
            else if (segment->data_length > ctx->buf_wr_ix - ctx->buf_rd_ix)
                return 0; /* need more data */

            code = jbig2_parse_segment(ctx, segment, ctx->buf + ctx->buf_rd_ix, fb, xVir, xoffset, yoffset);
            ctx->buf_rd_ix += segment->data_length;
            ctx->segment_index++;
            if (ctx->state == JBIG2_FILE_RANDOM_BODIES)
            {
                if (ctx->segment_index == ctx->n_segments)
                    ctx->state = JBIG2_FILE_EOF;
            }
            else              /* JBIG2_FILE_SEQUENCIAL_BODY */
            {
                ctx->state = JBIG2_FILE_SEQUENTIAL_HEADER;
            }
            if (code < 0)
            {
                ctx->state = JBIG2_FILE_EOF;
                return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, segment->number, "failed to decode; treating as end of file");
            }
            break;
        case JBIG2_FILE_EOF:
            //rt_kprintf("2222222222222222222222222555555555555555555555555555555555555\n");
            if (ctx->buf_rd_ix == ctx->buf_wr_ix)
                return 0;
            return jbig2_error(ctx, JBIG2_SEVERITY_WARNING, -1, "garbage beyond end of file");
        }
    }
    //rt_kprintf("2222222222222222222222222222666666666666666666666666666666666666666666666666\n");
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
        return NULL;

    ca = ctx->allocator;
    jbig2_free(ca, ctx->buf);
    if (ctx->segments != NULL)
    {
        for (i = 0; i < ctx->n_segments; i++)
            jbig2_free_segment(ctx, ctx->segments[i]);
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

void
jbig2_free_segment(Jbig2Ctx *ctx, Jbig2Segment *segment)
{
    if (segment == NULL)
        return;

    jbig2_free(ctx->allocator, segment->referred_to_segments);
    /* todo: we need either some separate fields or
    a more complex result object rather than this
    brittle special casing */
    switch (segment->flags & 63)
    {
    //case 0:                    /* symbol dictionary */
    //    if (segment->result != NULL)
    //        jbig2_sd_release(ctx, (Jbig2SymbolDict *) segment->result);
    //    break;
    case 4:                    /* intermediate text region */
    case 40:                   /* intermediate refinement region */
        if (segment->result != NULL)
            jbig2_image_release(ctx, (Jbig2Image *)segment->result);
        break;
    //case 16:                   /* pattern dictionary */
    //    if (segment->result != NULL)
    //        jbig2_hd_release(ctx, (Jbig2PatternDict *) segment->result);
    //    break;
    //case 53:                   /* user-supplied huffman table */
    //    if (segment->result != NULL)
    //        jbig2_table_free(ctx, (Jbig2HuffmanParams *) segment->result);
    //    break;
    default:
        /* anything else is probably an undefined pointer */
        break;
    }
    jbig2_free(ctx->allocator, segment);
}

int jbig2_decompression(image_info_t *img_info, rt_uint8_t *fb, rt_int32_t xVir, rt_int32_t xoffset, rt_int32_t yoffset)
{
    FILE *f_page = NULL;
    Jbig2Ctx *ctx = NULL;
    uint8_t buf[4096];
    jbig2dec_params_t params;
    int filearg;
    int code;
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

    unsigned char *p = NULL;
    p = (unsigned char *)malloc(sizeof(unsigned char) * 500);
    if (NULL == p)
    {
        rt_kprintf("------------------------------fail to malloc-------------------------------\n");
    }
    free(p);

    switch (params.mode)
    {
    case render:
        ctx = jbig2_ctx_new(NULL, (Jbig2Options)(f_page != NULL || params.embedded ? JBIG2_OPTIONS_EMBEDDED : 0), NULL, error_callback, &params);

        ///* pull the whole file/global stream into memory */
        for (;;)
        {
            if (read_flag == 1)
            {
                break;
            }
            int n_bytes;

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
                break;
            }
        }
        break;
    }

    flush_errors(&params);
    jbig2_ctx_free(ctx);
    return 0;
}

#endif