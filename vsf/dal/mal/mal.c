/***************************************************************************
 *   Copyright (C) 2009 - 2010 by Simon Qian <SimonQian@SimonQian.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "app_type.h"

#include "mal.h"

#if DAL_MAL_EN

#include "mal_driver.h"

#define MAL_RETRY_CNT					0xFFFF

static vsf_err_t mal_init_nb(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->init_nb))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->init_nb(info);
}

static vsf_err_t mal_init_nb_isready(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if (NULL == mal_driver)
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	if (mal_driver->init_nb_isready != NULL)
	{
		return mal_driver->init_nb_isready(info);
	}
	return VSFERR_NONE;
}

static vsf_err_t mal_fini(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->fini))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->fini(info);
}

static vsf_err_t mal_getinfo(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->getinfo))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->getinfo(info);
}

static vsf_err_t mal_poll(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	vsf_err_t err = VSFERR_NONE;
	
	if (NULL == mal_driver)
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	if (mal_driver->poll != NULL)
	{
		err = mal_driver->poll(info);
	}
	return err;
}

static vsf_err_t mal_eraseblock_nb_start(struct dal_info_t *info, 
										uint64_t address, uint64_t count)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseblock_nb_start))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseblock_nb_start(info, address, count);
}

static vsf_err_t mal_eraseblock_nb(struct dal_info_t *info, uint64_t address)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseblock_nb))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseblock_nb(info, address);
}

static vsf_err_t mal_eraseblock_nb_isready(struct dal_info_t *info, 
											uint64_t address)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseblock_nb_isready))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseblock_nb_isready(info, address);
}

static vsf_err_t mal_eraseblock_nb_waitready(struct dal_info_t *info, 
												uint64_t address)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if (NULL == mal_driver)
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	if (mal_driver->eraseblock_nb_waitready != NULL)
	{
		return mal_driver->eraseblock_nb_waitready(info, address);
	}
	else
	{
		if (mal_driver->eraseblock_nb_isready != NULL)
		{
			uint32_t dly;
			vsf_err_t err = VSFERR_FAIL;
			
			dly = MAL_RETRY_CNT;
			while (dly--)
			{
				err = mal_eraseblock_nb_isready(info, address);
				if (!err || (err && (err != VSFERR_NOT_READY)))
				{
					break;
				}
			}
			return err;
		} 
		return VSFERR_FAIL;
	}
}

static vsf_err_t mal_eraseblock_nb_end(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseblock_nb_end))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseblock_nb_end(info);
}

static vsf_err_t mal_eraseall_nb_start(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseall_nb_start))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseall_nb_start(info);
}

static vsf_err_t mal_eraseall_nb_isready(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseall_nb_isready))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseall_nb_isready(info);
}

static vsf_err_t mal_eraseall_nb_waitready(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if (NULL == mal_driver)
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	if (mal_driver->eraseall_nb_waitready != NULL)
	{
		return mal_driver->eraseall_nb_waitready(info);
	}
	else
	{
		if (mal_driver->eraseall_nb_isready != NULL)
		{
			uint32_t dly;
			vsf_err_t err = VSFERR_FAIL;
			
			dly = MAL_RETRY_CNT;
			while (dly--)
			{
				err = mal_eraseall_nb_isready(info);
				if (!err || (err && (err != VSFERR_NOT_READY)))
				{
					break;
				}
			}
			return err;
		} 
		return VSFERR_FAIL;
	}
}

static vsf_err_t mal_eraseall_nb_end(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->eraseall_nb_end))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->eraseall_nb_end(info);
}

static vsf_err_t mal_readblock_nb_start(struct dal_info_t *info, 
										uint64_t address, uint64_t count)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->readblock_nb_start))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->readblock_nb_start(info, address, count);
}

static vsf_err_t mal_readblock_nb(struct dal_info_t *info, 
									uint64_t address, uint8_t *buff)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->readblock_nb))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->readblock_nb(info, address, buff);
}

static vsf_err_t mal_readblock_nb_isready(struct dal_info_t *info, 
											uint64_t address, uint8_t *buff)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->readblock_nb_isready))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->readblock_nb_isready(info, address, buff);
}

static vsf_err_t mal_readblock_nb_waitready(struct dal_info_t *info, 
											uint64_t address, uint8_t *buff)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if (NULL == mal_driver)
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	if (mal_driver->readblock_nb_waitready != NULL)
	{
		return mal_driver->readblock_nb_waitready(info, address, buff);
	}
	else
	{
		if (mal_driver->readblock_nb_isready != NULL)
		{
			uint32_t dly;
			vsf_err_t err = VSFERR_FAIL;
			
			dly = MAL_RETRY_CNT;
			while (dly--)
			{
				err = mal_readblock_nb_isready(info, address, buff);
				if (!err || (err && (err != VSFERR_NOT_READY)))
				{
					break;
				}
			}
			return err;
		} 
		return VSFERR_FAIL;
	}
}

static vsf_err_t mal_readblock_nb_end(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->readblock_nb_end))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->readblock_nb_end(info);
}

static vsf_err_t mal_writeblock_nb_start(struct dal_info_t *info, 
											uint64_t address, uint64_t count)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->writeblock_nb_start))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->writeblock_nb_start(info, address, count);
}

static vsf_err_t mal_writeblock_nb(struct dal_info_t *info, 
									uint64_t address, uint8_t *buff)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->writeblock_nb))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->writeblock_nb(info, address, buff);
}

static vsf_err_t mal_writeblock_nb_isready(struct dal_info_t *info, 
											uint64_t address, uint8_t *buff)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->writeblock_nb_isready))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->writeblock_nb_isready(info, address, buff);
}

static vsf_err_t mal_writeblock_nb_waitready(struct dal_info_t *info, 
												uint64_t address, uint8_t *buff)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if (NULL == mal_driver)
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	if (mal_driver->writeblock_nb_waitready != NULL)
	{
		return mal_driver->writeblock_nb_waitready(info, address, buff);
	}
	else
	{
		if (mal_driver->writeblock_nb_isready != NULL)
		{
			uint32_t dly;
			vsf_err_t err = VSFERR_FAIL;
			
			dly = MAL_RETRY_CNT;
			while (dly--)
			{
				err = mal_writeblock_nb_isready(info, address, buff);
				if (!err || (err && (err != VSFERR_NOT_READY)))
				{
					break;
				}
			}
			return err;
		} 
		return VSFERR_FAIL;
	}
}

static vsf_err_t mal_writeblock_nb_end(struct dal_info_t *info)
{
	struct mal_driver_t* mal_driver =
			(struct mal_driver_t *)(((struct mal_info_t*)info->extra)->driver);
	
	if ((NULL == mal_driver) || (NULL == mal_driver->writeblock_nb_end))
	{
		return VSFERR_NOT_SUPPORT;
	}
	
	return mal_driver->writeblock_nb_end(info);
}

static vsf_err_t mal_init(struct dal_info_t *info)
{
	vsf_err_t err;
	
	err = mal_init_nb(info);
	if (!err)
	{
		do {
			err = mal_init_nb_isready(info);
		} while (err && (VSFERR_NOT_READY == err));
	}
	return err;
}

static vsf_err_t mal_eraseblock(struct dal_info_t *info, 
								uint64_t address, uint64_t count)
{
	struct mal_info_t *mal_info = (struct mal_info_t *)info->extra;
	uint64_t erase_block_size, i;
	
	erase_block_size = mal_info->erase_page_size ? 
					mal_info->erase_page_size : mal_info->capacity.block_size;
	if (!erase_block_size || 
		mal_eraseblock_nb_start(info, address, count))
	{
		return VSFERR_FAIL;
	}
	
	for (i = 0; i < count; i++)
	{
		if (mal_eraseblock_nb(info, address) || 
			mal_eraseblock_nb_waitready(info, address))
		{
			return VSFERR_FAIL;
		}
		address += erase_block_size;
	}
	
	return mal_eraseblock_nb_end(info);
}

static vsf_err_t mal_eraseall(struct dal_info_t *info)
{
	if (mal_eraseall_nb_start(info))
	{
		// erase all not available, try erase block
		struct mal_info_t *mal_info = (struct mal_info_t *)info->extra;
		uint64_t block_number = mal_info->capacity.block_number;
		
		if (!block_number || 
			mal_eraseblock(info, 0, block_number))
		{
			return VSFERR_FAIL;
		}
		return VSFERR_NONE;
	}
	else
	{
		if (mal_eraseall_nb_waitready(info) || 
			mal_eraseall_nb_end(info))
		{
			return VSFERR_FAIL;
		}
		return VSFERR_NONE;
	}
}

static vsf_err_t mal_readblock(struct dal_info_t *info, 
								uint64_t address, uint8_t *buff, uint64_t count)
{
	struct mal_info_t *mal_info = (struct mal_info_t *)info->extra;
	uint64_t read_block_size, i;
	
	read_block_size = mal_info->read_page_size ? 
					mal_info->read_page_size : mal_info->capacity.block_size;
	if (!read_block_size || 
		mal_readblock_nb_start(info, address, count))
	{
		return VSFERR_FAIL;
	}
	
	for (i = 0; i < count; i++)
	{
		if (mal_readblock_nb_waitready(info, address, buff) || 
			mal_readblock_nb(info, address, buff))
		{
			return VSFERR_FAIL;
		}
		address += read_block_size;
		buff += read_block_size;
	}
	
	return mal_readblock_nb_end(info);
}

static vsf_err_t mal_writeblock(struct dal_info_t *info, 
								uint64_t address, uint8_t *buff, uint64_t count)
{
	struct mal_info_t *mal_info = (struct mal_info_t *)info->extra;
	uint64_t write_block_size, i;
	
	write_block_size = mal_info->write_page_size ? 
					mal_info->write_page_size : mal_info->capacity.block_size;
	if (!write_block_size || 
		mal_writeblock_nb_start(info, address, count))
	{
		return VSFERR_FAIL;
	}
	
	for (i = 0; i < count; i++)
	{
		if (mal_writeblock_nb(info, address, buff) || 
			mal_writeblock_nb_waitready(info, address, buff))
		{
			return VSFERR_FAIL;
		}
		address += write_block_size;
		buff += write_block_size;
	}
	
	return mal_writeblock_nb_end(info);
}

const struct mal_t mal = 
{
	mal_init,
	mal_fini,
	mal_getinfo,
	mal_poll,
	
	mal_eraseall,
	mal_eraseblock,
	mal_readblock,
	mal_writeblock,
	
	mal_init_nb,
	mal_init_nb_isready,
	
	mal_eraseall_nb_start,
	mal_eraseall_nb_isready,
	mal_eraseall_nb_waitready,
	mal_eraseall_nb_end,
	
	mal_eraseblock_nb_start,
	mal_eraseblock_nb,
	mal_eraseblock_nb_isready,
	mal_eraseblock_nb_waitready,
	mal_eraseblock_nb_end,
	
	mal_readblock_nb_start,
	mal_readblock_nb,
	mal_readblock_nb_isready,
	mal_readblock_nb_waitready,
	mal_readblock_nb_end,
	
	mal_writeblock_nb_start,
	mal_writeblock_nb,
	mal_writeblock_nb_isready,
	mal_writeblock_nb_waitready,
	mal_writeblock_nb_end
};

#endif
