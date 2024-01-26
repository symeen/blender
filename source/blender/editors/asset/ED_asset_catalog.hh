/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup edasset
 *
 * UI/Editor level API for catalog operations, creating richer functionality than the asset system
 * catalog API provides (which this uses internally).
 *
 * Functions can be expected to not perform any change when #ED_asset_catalogs_read_only() returns
 * true. Generally UI code should disable such functionality in this case, so these functions are
 * not called at all.
 *
 * Note that `ED_asset_catalog.hh` is part of this API.
 */

#pragma once

#include <optional>

#include "AS_asset_catalog.hh"

#include "BLI_string_ref.hh"

struct bScreen;

void ED_asset_catalogs_save_from_main_path(blender::asset_system::AssetLibrary *library,
                                           const Main *bmain);

/**
 * Saving catalog edits when the file is saved is a global option shared for each asset library,
 * and as such ignores the per asset library #ED_asset_catalogs_read_only().
 */
void ED_asset_catalogs_set_save_catalogs_when_file_is_saved(bool should_save);
bool ED_asset_catalogs_get_save_catalogs_when_file_is_saved(void);

/**
 * Returns if the catalogs of \a library are allowed to be editable, or if the UI should forbid
 * edits.
 */
[[nodiscard]] bool ED_asset_catalogs_read_only(const blender::asset_system::AssetLibrary &library);

blender::asset_system::AssetCatalog *ED_asset_catalog_add(
    blender::asset_system::AssetLibrary *library,
    blender::StringRefNull name,
    blender::StringRef parent_path = nullptr);
void ED_asset_catalog_remove(blender::asset_system::AssetLibrary *library,
                             const blender::asset_system::CatalogID &catalog_id);

void ED_asset_catalog_rename(blender::asset_system::AssetLibrary *library,
                             blender::asset_system::CatalogID catalog_id,
                             blender::StringRefNull new_name);
/**
 * Reinsert catalog identified by \a src_catalog_id as child to catalog identified by \a
 * dst_parent_catalog_id. If \a dst_parent_catalog_id is not set, the catalog is moved to the root
 * level of the tree.
 * The name of the reinserted catalog is made unique within the parent. Note that moving a catalog
 * to the same level it was before will also change its name, since the name uniqueness check isn't
 * smart enough to ignore the item to be reinserted. So the caller is expected to handle this case
 * to avoid unwanted renames.
 *
 * Nothing is done (debug builds run into an assert) if the given catalog IDs can't be identified.
 */
void ED_asset_catalog_move(
    blender::asset_system::AssetLibrary *library,
    blender::asset_system::CatalogID src_catalog_id,
    std::optional<blender::asset_system::CatalogID> dst_parent_catalog_id = std::nullopt);
