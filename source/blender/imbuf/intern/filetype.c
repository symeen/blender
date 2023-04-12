/* SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup imbuf
 */

#include <stddef.h>

#include "BLI_utildefines.h"

#include "IMB_filetype.h"
#include "IMB_imbuf.h"
#include "IMB_imbuf_types.h"

#include "IMB_colormanagement.h"

#include "oiio/openimageio_api.h"

#ifdef WITH_OPENEXR
#  include "openexr/openexr_api.h"
#endif

const ImFileType IMB_FILE_TYPES[] = {
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_jpeg,
        .load = imb_load_jpeg,
        .load_filepath = NULL,
        .load_filepath_thumbnail = imb_thumbnail_jpeg,
        .save = imb_savejpeg,
        .flag = 0,
        .filetype = IMB_FTYPE_JPG,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_png,
        .load = imb_load_png,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_png,
        .flag = 0,
        .filetype = IMB_FTYPE_PNG,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_bmp,
        .load = imb_load_bmp,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_bmp,
        .flag = 0,
        .filetype = IMB_FTYPE_BMP,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_tga,
        .load = imb_load_tga,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_tga,
        .flag = 0,
        .filetype = IMB_FTYPE_TGA,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_iris,
        .load = imb_loadiris,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_saveiris,
        .flag = 0,
        .filetype = IMB_FTYPE_IMAGIC,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_dpx,
        .load = imb_load_dpx,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_dpx,
        .flag = IM_FTYPE_FLOAT,
        .filetype = IMB_FTYPE_DPX,
        .default_save_role = COLOR_ROLE_DEFAULT_FLOAT,
    },
#ifdef WITH_CINEON
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_cineon,
        .load = imb_load_cineon,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_cineon,
        .flag = IM_FTYPE_FLOAT,
        .filetype = IMB_FTYPE_CINEON,
        .default_save_role = COLOR_ROLE_DEFAULT_FLOAT,
    },
#endif
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_tiff,
        .load = imb_load_tiff,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_tiff,
        .flag = 0,
        .filetype = IMB_FTYPE_TIF,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_hdr,
        .load = imb_load_hdr,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_hdr,
        .flag = IM_FTYPE_FLOAT,
        .filetype = IMB_FTYPE_RADHDR,
        .default_save_role = COLOR_ROLE_DEFAULT_FLOAT,
    },
#ifdef WITH_OPENEXR
    {
        .init = imb_initopenexr,
        .exit = imb_exitopenexr,
        .is_a = imb_is_a_openexr,
        .load = imb_load_openexr,
        .load_filepath = NULL,
        .load_filepath_thumbnail = imb_load_filepath_thumbnail_openexr,
        .save = imb_save_openexr,
        .flag = IM_FTYPE_FLOAT,
        .filetype = IMB_FTYPE_OPENEXR,
        .default_save_role = COLOR_ROLE_DEFAULT_FLOAT,
    },
#endif
#ifdef WITH_OPENJPEG
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_jp2,
        .load = imb_load_jp2,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = imb_save_jp2,
        .flag = IM_FTYPE_FLOAT,
        .filetype = IMB_FTYPE_JP2,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
#endif
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_dds,
        .load = imb_load_dds,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = NULL,
        .flag = 0,
        .filetype = IMB_FTYPE_DDS,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_psd,
        .load = imb_load_psd,
        .load_filepath = NULL,
        .load_filepath_thumbnail = NULL,
        .save = NULL,
        .flag = IM_FTYPE_FLOAT,
        .filetype = IMB_FTYPE_PSD,
        .default_save_role = COLOR_ROLE_DEFAULT_FLOAT,
    },
#ifdef WITH_WEBP
    {
        .init = NULL,
        .exit = NULL,
        .is_a = imb_is_a_webp,
        .load = imb_loadwebp,
        .load_filepath = NULL,
        .load_filepath_thumbnail = imb_load_filepath_thumbnail_webp,
        .save = imb_savewebp,
        .flag = 0,
        .filetype = IMB_FTYPE_WEBP,
        .default_save_role = COLOR_ROLE_DEFAULT_BYTE,
    },
#endif
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0},
};

const ImFileType *IMB_FILE_TYPES_LAST = &IMB_FILE_TYPES[ARRAY_SIZE(IMB_FILE_TYPES) - 1];

const ImFileType *IMB_file_type_from_ftype(int ftype)
{
  for (const ImFileType *type = IMB_FILE_TYPES; type < IMB_FILE_TYPES_LAST; type++) {
    if (ftype == type->filetype) {
      return type;
    }
  }
  return NULL;
}

const ImFileType *IMB_file_type_from_ibuf(const ImBuf *ibuf)
{
  return IMB_file_type_from_ftype(ibuf->ftype);
}

void imb_filetypes_init(void)
{
  const ImFileType *type;

  for (type = IMB_FILE_TYPES; type < IMB_FILE_TYPES_LAST; type++) {
    if (type->init) {
      type->init();
    }
  }
}

void imb_filetypes_exit(void)
{
  const ImFileType *type;

  for (type = IMB_FILE_TYPES; type < IMB_FILE_TYPES_LAST; type++) {
    if (type->exit) {
      type->exit();
    }
  }
}
