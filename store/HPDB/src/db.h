/* db.h - A DB handler implementation
 *
 * Copyright (c) 2011-2012, FangDong <yp.fangdong@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */



#ifndef __DB_H_
#define __DB_H_

#include <stdint.h>
#include "hfile.h"
#include "hable.h"
#include "utils.h"









typedef struct DBHANDLE DB;

struct DBHANDLE {
	hable_t *memtable;
	hfilelist_t *hfiles;
	int8_t path[PATH_MAX];
	int32_t (*close)(DB *db);
	int32_t (*del)(const DB *db, sds key);
	int32_t (*put)(const DB *db, sds key, sds value);
	sds (*get)(const DB *db, sds key);
	int32_t (*sync)(DB *db);
} ;


DB *db_new();
void db_free(DB *db);
void db_destroy(DB *db);

int32_t _db_addhfile(DB *db, hfile_t *fp);
int32_t _db_delhfile(DB *db, hfile_t *fp);

DB *db_open(const int8_t *pathname);
int32_t _db_close(DB *db);
int32_t _db_del(const DB *db, sds key);
int32_t _db_put(const DB *db, sds key, sds value);
int8_t *_db_get(const DB *db, sds key);
int32_t _db_sync(DB *db);












#endif
