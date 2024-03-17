/**
 * @file full_embed.c
 * @author Thomas Joubert <thomas.joubert1@huawei-partners.com>
 * @brief libyang extension plugin - Full Embed
 *
 * Copyright (c) 2024 CESNET, z.s.p.o.
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */

#include <stdio.h>
#include <assert.h>

#include "compat.h"
#include "libyang.h"
#include "plugins_exts.h"

/**
 * @brief Parse full-embed extension instances.
 *
 * Implementation of ::lyplg_ext_parse_clb callback set as lyext_plugin::parse.
 */
static LY_ERR
full_embed_parse(struct lysp_ctx *pctx, struct lysp_ext_instance *ext)
{
    puts("Parsing full-embed extension instance\n");
}

/**
 * @brief Compile full-embed extension instances.
 *
 * Implementation of ::lyplg_ext_compile_clb callback set as lyext_plugin::compile.
 */
static LY_ERR
full_embed_compile(struct lysc_ctx *cctx, const struct lysp_ext_instance *extp, struct lysc_ext_instance *ext)
{
    puts("Compiling full-embed extension instance\n");
}

/**
 * @brief INFO printer
 *
 * Implementation of ::lyplg_ext_sprinter_info_clb set as ::lyext_plugin::printer_info
 */
static LY_ERR
full_embed_printer_info(struct lyspr_ctx *ctx, struct lysc_ext_instance *ext, ly_bool *flag)
{
    lyplg_ext_print_info_extension_instance(ctx, ext, flag);
    return LY_SUCCESS;
}

/**
 * @brief Free parsed full-embed extension instance data.
 *
 * Implementation of ::lyplg_clb_parse_free_clb callback set as lyext_plugin::pfree.
 */
static void
full_embed_pfree(const struct ly_ctx *ctx, struct lysp_ext_instance *ext)
{
    lyplg_ext_pfree_instance_substatements(ctx, ext->substmts);
}

/**
 * @brief Free compiled full-embed extension instance data.
 *
 * Implementation of ::lyplg_clb_compile_free_clb callback set as lyext_plugin::cfree.
 */
static void
full_embed_cfree(const struct ly_ctx *ctx, struct lysc_ext_instance *ext)
{
    lyplg_ext_cfree_instance_substatements(ctx, ext->substmts);
}

static void
full_embed_sprinter_node(uint16_t nodetype, const char **flags)
{
    if (nodetype & LYS_USES) {
        *flags = "-u";
    } else {
        *flags = "--";
    }
}

static LY_ERR
full_embed_sprinter_cnode(const struct lysc_node *node, const void *UNUSED(plugin_priv), ly_bool *UNUSED(skip),
        const char **flags, const char **UNUSED(add_opts))
{
    full_embed_sprinter_node(node->nodetype, flags);
    return LY_SUCCESS;
}

static LY_ERR
full_embed_sprinter_pnode(const struct lysp_node *node, const void *UNUSED(plugin_priv), ly_bool *UNUSED(skip),
        const char **flags, const char **UNUSED(add_opts))
{
    full_embed_sprinter_node(node->nodetype, flags);
    return LY_SUCCESS;
}

static LY_ERR
full_embed_sprinter_ctree(struct lysc_ext_instance *ext, const struct lyspr_tree_ctx *ctx,
        const char **UNUSED(flags), const char **UNUSED(add_opts))
{
    LY_ERR rc = LY_SUCCESS;

    assert(ctx);
    rc = lyplg_ext_sprinter_ctree_add_ext_nodes(ctx, ext, full_embed_sprinter_cnode);
    return rc;
}

static LY_ERR
full_embed_sprinter_ptree(struct lysp_ext_instance *ext, const struct lyspr_tree_ctx *ctx,
        const char **UNUSED(flags), const char **UNUSED(add_opts))
{
    LY_ERR rc = LY_SUCCESS;

    assert(ctx);
    rc = lyplg_ext_sprinter_ptree_add_ext_nodes(ctx, ext, full_embed_sprinter_pnode);
    return rc;
}

LIBYANG_API_DEF LY_ERR
lyplg_ext_full_embed_create_context(const struct lysc_ext_instance *ext, struct ly_ctx **ctx)
{
    puts("Creating context for full-embed extension instance\n");
    (void)ext;
    (void)ctx;
    return LY_SUCCESS;
}

/**
 * @brief Plugin descriptions for the full-embed extension
 *
 * Note that external plugins are supposed to use:
 *
 *   LYPLG_EXTENSIONS = {
 */
const struct lyplg_ext_record plugins_full_embed[] = {
    {
        .module = "ietf-yang-full-embed",
        .revision = "2023-11-05",
        .name = "full-embed",

        .plugin.id = "ly2 full embed v1",
        .plugin.parse = full_embed_parse,
        .plugin.compile = full_embed_compile,
        .plugin.printer_info = full_embed_printer_info,
        .plugin.printer_ctree = full_embed_sprinter_ctree,
        .plugin.printer_ptree = full_embed_sprinter_ptree,
        .plugin.node = NULL,
        .plugin.snode = NULL,
        .plugin.validate = NULL,
        .plugin.pfree = full_embed_pfree,
        .plugin.cfree = full_embed_cfree
    },
    {0}     /* terminating zeroed record */
};
