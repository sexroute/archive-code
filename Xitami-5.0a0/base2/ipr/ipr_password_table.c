/*---------------------------------------------------------------------------
    ipr_password_table.c - ipr_password_table component

    This class implements a hash container for ipr_password with the ability
    to load password files in various formats. One table can hold passwords
    of any type (Basic or Digest), the type is verified when the password is
    validated.  See http://tools.ietf.org/html/rfc2617. The class is
    threadsafe and may be used from concurrent threads.
    Generated from ipr_password_table.icl by icl_gen using GSL/4.
    
    Copyright (c) 1996-2009 iMatix Corporation
    All rights reserved.
    
    This file is licensed under the BSD license as follows:
    
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
    * Neither the name of iMatix Corporation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
    
    THIS SOFTWARE IS PROVIDED BY IMATIX CORPORATION "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL IMATIX CORPORATION BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

#include "icl.h"                        //  iCL base classes
#include "ipr_password_table.h"         //  Definitions for our class

//  Shorthand for class type                                                   

#define self_t              ipr_password_table_t

//  Shorthands for class methods                                               

#define self_new            ipr_password_table_new
#define self_annihilate     ipr_password_table_annihilate
#define self_insert         ipr_password_table_insert
#define self_remove         ipr_password_table_remove
#define self_search_digest  ipr_password_table_search_digest
#define self_load           ipr_password_table_load
#define self_save           ipr_password_table_save
#define self_sync           ipr_password_table_sync
#define self_guard_set      ipr_password_table_guard_set
#define self_guard_load     ipr_password_table_guard_load
#define self_guard_save     ipr_password_table_guard_save
#define self_guard_sync     ipr_password_table_guard_sync
#define self_basic          ipr_password_table_basic
#define self_digest         ipr_password_table_digest
#define self_set_nonce_ttl  ipr_password_table_set_nonce_ttl
#define self_set_nonce_quota  ipr_password_table_set_nonce_quota
#define self_set_nonce_test  ipr_password_table_set_nonce_test
#define self_set_debug      ipr_password_table_set_debug
#define self_selftest       ipr_password_table_selftest
#define self_search         ipr_password_table_search
#define self_apply          ipr_password_table_apply
#define self_terminate      ipr_password_table_terminate
#define self_show           ipr_password_table_show
#define self_destroy        ipr_password_table_destroy
#define self_alloc          ipr_password_table_alloc
#define self_free           ipr_password_table_free
#define self_lock           ipr_password_table_lock
#define self_unlock         ipr_password_table_unlock
#define self_link           ipr_password_table_link
#define self_unlink         ipr_password_table_unlink
#define self_show_animation  ipr_password_table_show_animation
#define self_new_in_scope   ipr_password_table_new_in_scope

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_NEW))
static icl_stats_t *s_ipr_password_table_new_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_DESTROY))
static icl_stats_t *s_ipr_password_table_annihilate_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_INSERT))
static icl_stats_t *s_ipr_password_table_insert_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_REMOVE))
static icl_stats_t *s_ipr_password_table_remove_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SEARCH_DIGEST))
static icl_stats_t *s_ipr_password_table_search_digest_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_LOAD))
static icl_stats_t *s_ipr_password_table_load_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SAVE))
static icl_stats_t *s_ipr_password_table_save_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SYNC))
static icl_stats_t *s_ipr_password_table_sync_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_SET))
static icl_stats_t *s_ipr_password_table_guard_set_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_LOAD))
static icl_stats_t *s_ipr_password_table_guard_load_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_SAVE))
static icl_stats_t *s_ipr_password_table_guard_save_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_SYNC))
static icl_stats_t *s_ipr_password_table_guard_sync_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_BASIC))
static icl_stats_t *s_ipr_password_table_basic_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_DIGEST))
static icl_stats_t *s_ipr_password_table_digest_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_NONCE_TTL))
static icl_stats_t *s_ipr_password_table_set_nonce_ttl_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA))
static icl_stats_t *s_ipr_password_table_set_nonce_quota_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_NONCE_TEST))
static icl_stats_t *s_ipr_password_table_set_nonce_test_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_DEBUG))
static icl_stats_t *s_ipr_password_table_set_debug_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SELFTEST))
static icl_stats_t *s_ipr_password_table_selftest_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SEARCH))
static icl_stats_t *s_ipr_password_table_search_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_APPLY))
static icl_stats_t *s_ipr_password_table_apply_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_TERMINATE))
static icl_stats_t *s_ipr_password_table_terminate_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SHOW))
static icl_stats_t *s_ipr_password_table_show_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_DESTROY_PUBLIC))
static icl_stats_t *s_ipr_password_table_destroy_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_ALLOC))
static icl_stats_t *s_ipr_password_table_alloc_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_FREE))
static icl_stats_t *s_ipr_password_table_free_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_LOCK))
static icl_stats_t *s_ipr_password_table_lock_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_UNLOCK))
static icl_stats_t *s_ipr_password_table_unlock_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_LINK))
static icl_stats_t *s_ipr_password_table_link_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_UNLINK))
static icl_stats_t *s_ipr_password_table_unlink_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SHOW_ANIMATION))
static icl_stats_t *s_ipr_password_table_show_animation_stats = NULL;
#endif
#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_NEW_IN_SCOPE))
static icl_stats_t *s_ipr_password_table_new_in_scope_stats = NULL;
#endif
#define ipr_password_table_annihilate(self)  ipr_password_table_annihilate_ (self, __FILE__, __LINE__)
static void
    ipr_password_table_annihilate_ (
ipr_password_table_t * ( * self_p ),    //  Reference to object reference
char * file,                            //  Source file
size_t line                             //  Line number
);

#define ipr_password_table_alloc()      ipr_password_table_alloc_ (__FILE__, __LINE__)
static ipr_password_table_t *
    ipr_password_table_alloc_ (
char * file,                            //  Source file for call
size_t line                             //  Line number for call
);

#define ipr_password_table_free(self)   ipr_password_table_free_ (self, __FILE__, __LINE__)
static void
    ipr_password_table_free_ (
ipr_password_table_t * self,            //  Object reference
char * file,                            //  Source file
size_t line                             //  Line number
);

Bool
    ipr_password_table_animating = TRUE;  //  Animation enabled by default

//  Hash support functions
static inline unsigned int
    s_key_hash (char * key, size_t hash_size);
static inline Bool
    s_key_equal (char * key1, char * key2);

//  Table functions to be called once locks are in place
static int
    s_ipr_password_table_insert (ipr_password_table_t *self, ipr_password_t *item, char * key);
static ipr_password_t *
    s_ipr_password_table_lookup (ipr_password_table_t *self, char * key);
static void
    s_ipr_password_table_remove (ipr_password_t *item);
static void
    s_ipr_password_table_purge (ipr_password_table_t *self);
/*  -------------------------------------------------------------------------
    ipr_password_table_new

    Type: Component method
    Creates and initialises a new ipr_password_table_t object, returns a
    reference to the created object.
    -------------------------------------------------------------------------
 */

ipr_password_table_t *
    ipr_password_table_new_ (
    char * file,                        //  Source file for call
    size_t line,                        //  Line number for call
    char * filename                     //  Name of associated file
)
{
    ipr_password_table_t *
        self = NULL;                    //  Object reference

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_NEW))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_new_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" file=\"%s\""
" line=\"%u\""
" filename=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, file, line, filename);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_NEW))
    icl_trace_record (NULL, ipr_password_table_dump, 1);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_NEW))
    icl_stats_inc ("ipr_password_table_new", &s_ipr_password_table_new_stats);
#endif

    self = ipr_password_table_alloc_ (file, line);
    if (self) {
        self->object_tag   = IPR_PASSWORD_TABLE_ALIVE;
        self->links        = 1;
        self->zombie       = FALSE;
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
        self->history_last = 0;

        //  Track possession operation in history
        self->history_file  [0] = file;
        self->history_line  [0] = line;
        self->history_type  [0] = "new";
        self->history_links [0] = self->links;
#endif
#if (defined (BASE_THREADSAFE))
        self->mutex = icl_mutex_new ();
#endif
#if defined (DEBUG)
        icl_mem_set_callback (self, ipr_password_table_show_);
#endif

self->max_items = IPR_PASSWORD_TABLE_INITIAL_SIZE;
self->table_items = icl_mem_alloc (sizeof (ipr_password_t*) *
    IPR_PASSWORD_TABLE_INITIAL_SIZE);
assert (self->table_items);
memset (self->table_items, 0, sizeof (ipr_password_t*) *
    IPR_PASSWORD_TABLE_INITIAL_SIZE);

//
self->list = ipr_password_list_new ();
self->nonce_ttl = 3600;             //  Default values
self->nonce_quota = 256;
if (filename) {
    self->file_name = icl_mem_strdup (filename);
    self_load (self, filename);
}
}
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_NEW))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 1);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_NEW))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_new_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" file=\"%s\""
" line=\"%u\""
" filename=\"%s\""
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, file, line, filename, self);
#endif


    return (self);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_annihilate

    Type: Component method
    -------------------------------------------------------------------------
 */

static void
    ipr_password_table_annihilate_ (
    ipr_password_table_t * ( * self_p ),   //  Reference to object reference
    char * file,                        //  Source file
    size_t line                         //  Line number
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    int
        history_last;
#endif

    ipr_password_table_t *
        self = *self_p;                 //  Dereferenced Reference to object reference

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_DESTROY))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_destroy_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%u\""
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DESTROY))
    icl_trace_record (NULL, ipr_password_table_dump, 2);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_DESTROY))
    icl_stats_inc ("ipr_password_table_annihilate", &s_ipr_password_table_annihilate_stats);
#endif

#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    //  Track possession operation in history
    history_last = icl_atomic_inc32 ((volatile qbyte *) &self->history_last) + 1;
    self->history_file  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = file;
    self->history_line  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = line;
    self->history_type  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = "destroy";
    self->history_links [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = self->links;
#endif

    IPR_PASSWORD_TABLE_ASSERT_SANE (self);
#if (defined (BASE_THREADSAFE))
    mutex = self->mutex;
    if (mutex)
         icl_mutex_lock (mutex);
#endif

s_ipr_password_table_purge (self);
if (self->table_items)
    icl_mem_free (self->table_items);

icl_mem_free (self->file_name);
ipr_password_list_destroy (&self->list);
ipr_nonce_table_destroy (&self->nonces);
#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DESTROY))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 2);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_DESTROY))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_destroy_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%u\""
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line, self);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_insert

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Insert a new item into the hash table if possible. If successful,
    the number of links to the item is automatically incremented.
    Trying to insert a duplicate key will result in nothing being inserted.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_insert (
    ipr_password_table_t * self,        //  Reference to object
    char * key,                         //  Hash key
    ipr_password_t * item               //  Item to insert
)
{

    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_INSERT))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_insert_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" item=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, item);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_INSERT))
    icl_trace_record (NULL, ipr_password_table_dump, 3);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_INSERT))
    icl_stats_inc ("ipr_password_table_insert", &s_ipr_password_table_insert_stats);
#endif


IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
if (item->table_head) {
    if (item->table_head != self) {
        icl_console_print ("E: ipr_password item inserted into multiple table containers");
        assert (item->table_head == self);
    }
    s_ipr_password_table_remove (item);
}
rc = s_ipr_password_table_insert (self, item, key);

ipr_password_list_queue (self->list, item);
assert (ipr_password_list_count (self->list) == self->nbr_items);
}
else
    rc = -1;                        //  Return error on zombie object.


#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_INSERT))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 3);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_INSERT))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_insert_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" item=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, item, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_remove

    Type: Component method
    Remove an item from a hash table.  If the item was not in any hash
    table, this function does nothing.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_remove (
    ipr_password_t * item               //  Item to remove
)
{

    ipr_password_table_t *
        self = item->table_head;        //  The list
    int
        rc = 0;                         //  Not documented

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_REMOVE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_remove_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" item=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, item);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_REMOVE))
    icl_trace_record (NULL, ipr_password_table_dump, 4);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_REMOVE))
    icl_stats_inc ("ipr_password_table_remove", &s_ipr_password_table_remove_stats);
#endif


if (self
&&  self == item->table_head) { //      Catch case where item moved
    s_ipr_password_table_remove (item);
}

ipr_password_list_remove (item);

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_REMOVE))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 4);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_REMOVE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_remove_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" item=\"%pp\""
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, item, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_search_digest

    Type: Component method
    Searches for an entry using username and realm, the key for digest
    passwords being "username:realm" rather than "username" as for basic
    passwords.
    -------------------------------------------------------------------------
 */

ipr_password_t *
    ipr_password_table_search_digest (
    ipr_password_table_t * self,        //  Not documented
    char * username,                    //  Not documented
    char * realm                        //  Not documented
)
{
icl_shortstr_t
    key;
    ipr_password_t *
        password;                       //  Not documented

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SEARCH_DIGEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_search_digest_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" username=\"%s\""
" realm=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, username, realm);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SEARCH_DIGEST))
    icl_trace_record (NULL, ipr_password_table_dump, 5);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SEARCH_DIGEST))
    icl_stats_inc ("ipr_password_table_search_digest", &s_ipr_password_table_search_digest_stats);
#endif

//
icl_shortstr_fmt (key, "%s:%s", username, realm);
password = self_search (self, key);
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SEARCH_DIGEST))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 5);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SEARCH_DIGEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_search_digest_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" username=\"%s\""
" realm=\"%s\""
" password=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, username, realm, password);
#endif


    return (password);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_load

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Loads a password file into the table, merging the loaded passwords with
    any passwords already in the table.  Password files are in the format
    produced by the Apache htpasswd or htdigest tools.  Each line contains
    {key}:{hash}, where {key} consists of one or more words separated by ":".
    Stores the loaded file's time and size, and returns the number of entries
    loaded from the file.  If the file could not be found, returns -1. Lines
    are limited to 4096 bytes, keys to 255 characters.  Existing entries are
    updated it their hash has changed, else left unchanged.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_load (
    ipr_password_table_t * self,        //  Reference to object
    char * filename                     //  Name of associated file
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

#   define IPR_PASSWD_LINE_MAX    4096
    FILE
        *file;
    char
        *line;
    ipr_regexp_t
        *regexp;                        //  Regexp for matching each line
    char
        *key = NULL,
        *hash = NULL;
    ipr_password_t
        *password;
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_LOAD))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_load_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" filename=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, filename);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LOAD))
    icl_trace_record (NULL, ipr_password_table_dump, 6);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_LOAD))
    icl_stats_inc ("ipr_password_table_load", &s_ipr_password_table_load_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
assert (filename);
file = fopen (filename, "r");
if (file) {
    //                        key                     hash
    //                         |                        |
    regexp = ipr_regexp_new ("^((?:[^: ]+)(?::[^: ]+)?):([^`s]+)");
    line = icl_mem_alloc (IPR_PASSWD_LINE_MAX + 1);
    while (fgets (line, IPR_PASSWD_LINE_MAX, file) != NULL) {
        if (ipr_regexp_match (regexp, line, &key, &hash) == 2) {
            password = ipr_password_table_search (self, key);
            if (password) {
                if (strneq (password->hash, hash)) {
                    ipr_password_update (password, hash);
                    rc++;
                }
            }
            else {
                password = ipr_password_new (self, key, hash);
                ipr_password_guard_set (password,
                    self->hit_quota, self->miss_quota, self->time_to_live);
                rc++;
            }
            icl_mem_strfree (&key);
            icl_mem_strfree (&hash);
        }
    }
    ipr_regexp_destroy (&regexp);
    icl_mem_free (line);
    fclose (file);

    icl_mem_free (self->file_name);
    self->file_name = icl_mem_strdup (filename);
    self->file_size = ipr_file_size (self->file_name);
    self->file_time = ipr_file_time (self->file_name);
}
else
    rc = -1;
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LOAD))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 6);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_LOAD))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_load_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" filename=\"%s\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, filename, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_save

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Saves the table to a text file, one entry per line.  If file name is null
    the saved password filename is used.  Returns the number of entries
    written.  If there was an error writing to the file, returns -1.  This
    method is UNSAFE if external tools also modify the password file.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_save (
    ipr_password_table_t * self         //  Reference to object
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

FILE
    *file;
char
    *tmpname;
ipr_password_t
    *password;
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SAVE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_save_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SAVE))
    icl_trace_record (NULL, ipr_password_table_dump, 7);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SAVE))
    icl_stats_inc ("ipr_password_table_save", &s_ipr_password_table_save_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
//  Save to temporary file and switch when done, to avoid data loss if
//  we crash part way through saving (disk full, etc.)
assert (self->file_name);
tmpname = ipr_file_tmpfile ();
file = fopen (tmpname, "w");
if (file) {
    password = ipr_password_list_first (self->list);
    while (password) {
        fprintf (file, "%s:%s\n", password->key, password->hash);
        password = ipr_password_list_next (&password);
        rc++;
    }
    fclose (file);
    ipr_file_rename (self->file_name, tmpname);
    icl_mem_free (tmpname);
    self->file_size = ipr_file_size (self->file_name);
    self->file_time = ipr_file_time (self->file_name);
}
else
    rc = -1;
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SAVE))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 7);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SAVE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_save_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_sync

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Reloads a password table from a disk file, if the disk file changed.
    Returns number of items changed, or -1 if the file could not be read.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_sync (
    ipr_password_table_t * self         //  Reference to object
)
{
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SYNC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_sync_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SYNC))
    icl_trace_record (NULL, ipr_password_table_dump, 8);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SYNC))
    icl_stats_inc ("ipr_password_table_sync", &s_ipr_password_table_sync_stats);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
if (ipr_file_size (self->file_name) != self->file_size
||  ipr_file_time (self->file_name) != self->file_time)
    rc = ipr_password_table_load (self, self->file_name);
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SYNC))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 8);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SYNC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_sync_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_guard_set

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Sets the password guard policy for all passwords in the table.  Should
    be invoked after loading a new password table for the first time.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_guard_set (
    ipr_password_table_t * self,        //  Reference to object
    size_t hit_quota,                   //  Not documented
    size_t miss_quota,                  //  Not documented
    size_t time_to_live                 //  Not documented
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

ipr_password_t
    *password;
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_SET))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_set_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" hit_quota=\"%u\""
" miss_quota=\"%u\""
" time_to_live=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, hit_quota, miss_quota, time_to_live);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SET))
    icl_trace_record (NULL, ipr_password_table_dump, 9);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_SET))
    icl_stats_inc ("ipr_password_table_guard_set", &s_ipr_password_table_guard_set_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
self->hit_quota = hit_quota;
self->miss_quota = miss_quota;
self->time_to_live = time_to_live;
password = ipr_password_list_first (self->list);
while (password) {
    ipr_password_guard_set (password, hit_quota, miss_quota, time_to_live);
    password = ipr_password_list_next (&password);
}
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SET))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 9);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_SET))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_set_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" hit_quota=\"%u\""
" miss_quota=\"%u\""
" time_to_live=\"%u\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, hit_quota, miss_quota, time_to_live, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_guard_load

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Loads password guard data, if any, for the password table.  The guard
    data is in a file with the same name as the password table file, with
    the string "_guard" following the file name.  Each line in the file is
    of the format {key}:{proplist} where proplist is a list of name=value
    pairs.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_guard_load (
    ipr_password_table_t * self         //  Reference to object
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

icl_shortstr_t
    guard_file;
FILE
    *file;
char
    *line;
ipr_regexp_t
    *regexp;                        //  Regexp for matching each line
char
    *key = NULL,
    *proplist = NULL;
ipr_password_t
    *password;
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_LOAD))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_load_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_LOAD))
    icl_trace_record (NULL, ipr_password_table_dump, 10);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_LOAD))
    icl_stats_inc ("ipr_password_table_guard_load", &s_ipr_password_table_guard_load_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
icl_shortstr_fmt (guard_file, "%s_guard", self->file_name);
file = fopen (guard_file, "r");
if (file) {
    //                        key                     proplist
    //                         |                        |
    regexp = ipr_regexp_new ("^((?:[^: ]+)(?::[^: ]+)?):(.*)");
    line = icl_mem_alloc (IPR_PASSWD_LINE_MAX + 1);
    while (fgets (line, IPR_PASSWD_LINE_MAX, file) != NULL) {
        if (ipr_regexp_match (regexp, line, &key, &proplist) == 2) {
            password = ipr_password_table_search (self, key);
            if (password)
                ipr_password_guard_get (password, proplist);
            icl_mem_strfree (&key);
            icl_mem_strfree (&proplist);
            rc++;
        }
    }
    ipr_regexp_destroy (&regexp);
    icl_mem_free (line);
    fclose (file);
    self->dirty = FALSE;
}
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_LOAD))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 10);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_LOAD))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_load_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_guard_save

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Saves the table's guard data to a text file, one entry per line.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_guard_save (
    ipr_password_table_t * self         //  Reference to object
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

icl_shortstr_t
    guard_file;
FILE
    *file;
char
    *tmpname;
ipr_password_t
    *password;
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_SAVE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_save_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SAVE))
    icl_trace_record (NULL, ipr_password_table_dump, 11);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_SAVE))
    icl_stats_inc ("ipr_password_table_guard_save", &s_ipr_password_table_guard_save_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
//  Save to temporary file and switch when done, to avoid data loss if
//  we crash part way through saving (disk full, etc.)
tmpname = ipr_file_tmpfile ();
file = fopen (tmpname, "w");
if (file) {
    password = ipr_password_list_first (self->list);
    while (password) {
        ipr_password_guard_put (password, file);
        password = ipr_password_list_next (&password);
    }
    fclose (file);
    icl_shortstr_fmt (guard_file, "%s_guard", self->file_name);
    ipr_file_rename (guard_file, tmpname);
    icl_mem_free (tmpname);
    self->dirty = FALSE;
}
else
    rc = -1;
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SAVE))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 11);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_SAVE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_save_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_guard_sync

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Saves the guard data for the table if the table was 'dirty', i.e. if any
    password has modified guard data.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_guard_sync (
    ipr_password_table_t * self         //  Reference to object
)
{
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_SYNC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_sync_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SYNC))
    icl_trace_record (NULL, ipr_password_table_dump, 12);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_GUARD_SYNC))
    icl_stats_inc ("ipr_password_table_guard_sync", &s_ipr_password_table_guard_sync_stats);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
if (self->dirty)
    ipr_password_table_guard_save (self);
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SYNC))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 12);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_GUARD_SYNC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_guard_sync_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_basic

    Type: Component method
    Authenticates using the Basic authentication mechanism defined in RFC
    2617. Accepts a response (the content of the HTTP Authorization header,
    which should start with "Basic "), and returns a challenge (sent back as
    the WWW-Authenticate header), or NULL if the authentication succeeded.
    Sets self->username to the resolved user name, if any, and self->result
    to 0 or an IPR_PASSWORD_xyz error code.  Allocates a new challenge string
    if needed, and the caller should free it when done.  The address is used
    for logging, and may be null.
    -------------------------------------------------------------------------
 */

char *
    ipr_password_table_basic (
    ipr_password_table_t * self,        //  Reference to self
    char * address,                     //  IP address of caller
    char * realm,                       //  Authentication realm
    char * response                     //  Authentication response
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

char
    *decoded,                       //  Start of decoded response
    *password;                      //  After ':' in decoded response
ipr_password_t
    *entry;                         //  Password entry in table
    char *
        challenge = NULL;               //  Not documented

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_BASIC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_basic_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" address=\"%s\""
" realm=\"%s\""
" response=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, address, realm, response);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_BASIC))
    icl_trace_record (NULL, ipr_password_table_dump, 13);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_BASIC))
    icl_stats_inc ("ipr_password_table_basic", &s_ipr_password_table_basic_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

//
strclr (self->username);
strclr (self->realm);
self->result = IPR_PASSWORD_SYNTAX;
response = ipr_str_defix (response, "Basic ");
if (response) {
    decoded = icl_mem_alloc (apr_base64_decode_len (response) + 1);
    apr_base64_decode (decoded, response);
    password = strchr (decoded, ':');

    if (password) {
        *password++ = 0;            //  Split password off decoded
        icl_shortstr_cpy (self->username, decoded);
        icl_shortstr_cpy (self->realm, realm);
        entry = ipr_password_table_search (self, self->username);
        if (entry) {
            if (entry->expired) {
                ipr_password_miss (entry, address);
                self->result = IPR_PASSWORD_EXPIRED;
            }
            else
            if (entry->type == IPR_PASSWD_BASIC) {
                //  Do a check through APR's algorithms, and as plain text
                if (apr_password_validate (password, entry->hash) == 0
                ||  streq (password, entry->hash)) {
                    ipr_password_hit (entry, address);
                    self->result = IPR_PASSWORD_OK;
                }
                else {
                    ipr_password_miss (entry, address);
                    self->result = IPR_PASSWORD_INCORRECT;
                }
            }
            else {
                ipr_password_miss (entry, address);
                self->result = IPR_PASSWORD_BADTYPE;
            }
        }
        else
            self->result = IPR_PASSWORD_NOTFOUND;
    }
    icl_mem_free (decoded);
}
else
    self->result = IPR_PASSWORD_CHALLENGE;

if (self->result != IPR_PASSWORD_OK)
    challenge = ipr_str_format ("Basic realm=\"%s\"", realm);
#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_BASIC))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 13);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_BASIC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_basic_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" address=\"%s\""
" realm=\"%s\""
" response=\"%s\""
" challenge=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, address, realm, response, challenge);
#endif


    return (challenge);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_digest

    Type: Component method
    Authenticates using the Digest authentication mechanism defined in RFC
    2617. Accepts a response (the content of the HTTP Authorization header,
    which should start with "Digest "), and returns a challenge (sent back as
    the WWW-Authenticate header), or NULL if the authentication succeeded.
    Sets self->username to the resolved user name, if any, and self->result
    to 0 or an IPR_PASSWORD_xyz error code.  Allocates a new challenge string
    if needed, and the caller should free it when done.  The address is used
    -------------------------------------------------------------------------
 */

char *
    ipr_password_table_digest (
    ipr_password_table_t * self,        //  Reference to self
    char * address,                     //  IP address of caller
    char * realm,                       //  Authentication realm
    char * response,                    //  Authentication response
    char * method,                      //  HTTP request method
    char * uri                          //  HTTP request URI
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

ipr_dict_table_t
    *fields;                        //  For parsing the credentials
char
    *auth_username,                 //  Authorization credentials
    *auth_realm,                    //    broken into individual pieces
    *auth_nonce,
    *auth_uri,
    *auth_qop,
    *auth_count,
    *auth_cnonce,
    *auth_response;
ipr_nonce_t
    *nonce;                         //  Security nonce
ipr_password_t
    *entry;                         //  User name entry in passwd file
    char *
        challenge = NULL;               //  Not documented

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_DIGEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_digest_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" address=\"%s\""
" realm=\"%s\""
" response=\"%s\""
" method=\"%s\""
" uri=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, address, realm, response, method, uri);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DIGEST))
    icl_trace_record (NULL, ipr_password_table_dump, 14);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_DIGEST))
    icl_stats_inc ("ipr_password_table_digest", &s_ipr_password_table_digest_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

//
if (self->nonces == NULL)
    self->nonces = ipr_nonce_table_new ();

//  Check Authorization: header for Digest credentials
strclr (self->username);
strclr (self->realm);
self->result = IPR_PASSWORD_SYNTAX;
response = ipr_str_defix (response, "Digest ");
if (response) {
    //  Break credentials into distinct pieces
    fields = ipr_dict_table_new ();
    ipr_dict_table_props_load (fields, response);
    auth_username = ipr_dict_table_lookup (fields, "username");
    auth_realm    = ipr_dict_table_lookup (fields, "realm");
    auth_nonce    = ipr_dict_table_lookup (fields, "nonce");
    auth_uri      = ipr_dict_table_lookup (fields, "uri");
    auth_qop      = ipr_dict_table_lookup (fields, "qop");
    auth_count    = ipr_dict_table_lookup (fields, "nc");
    auth_cnonce   = ipr_dict_table_lookup (fields, "cnonce");
    auth_response = ipr_dict_table_lookup (fields, "response");

    icl_shortstr_cpy (self->username, auth_username);
    icl_shortstr_cpy (self->realm, realm);

    //  Lookup nonce and password entry
    nonce = ipr_nonce_table_search (self->nonces, auth_nonce);
    entry = ipr_password_table_search_digest (self, self->username, realm);

    if (!entry) {
        self->result = IPR_PASSWORD_NOTFOUND;
        if (self->debug)
            icl_console_print ("P: no password for '%s:%s'", self->username, realm);
    }
    else
    if (entry->expired) {
        ipr_password_miss (entry, address);
        self->result = IPR_PASSWORD_EXPIRED;
        if (self->debug)
            icl_console_print ("P: '%s:%s' password has expired", self->username, realm);
    }
    else
    if (!nonce || ipr_nonce_expired (nonce)) {
        self->result = IPR_PASSWORD_TRYAGAIN;
        ipr_nonce_destroy (&nonce);
        if (self->debug)
            icl_console_print ("P: credentials used an expired nonce");
    }
    else
    //  Possible man-in-the-middle attacks, or proxy gone bad
    //  These could be caused by poorly coded clients, but that
    //  is marginally likely these days
    if (strneq (auth_uri, uri)
    ||  strneq (auth_realm, realm)
    ||  strneq (auth_qop, "auth")
    ||  strnull (auth_cnonce)
    ||  nonce->count >= (int64_t) strtoull (auth_count, NULL, 16)) {
        ipr_password_miss (entry, address);
        self->result = IPR_PASSWORD_HOSTILE;
        if (self->debug)
            icl_console_print ("P: credentials are badly formatted");
    }
    else {
        char
            *HA2,                       //  MD5 (method : uri)
            *HA3;                       //  Calculated response

        //  Format HA2 = md5 (method ":" uri)
        HA2 = ipr_str_md5 ("%s:%s", method, uri);
        HA3 = ipr_str_md5 ("%s:%s:%s:%s:%s:%s",
            entry->hash, nonce->key, auth_count, auth_cnonce, "auth", HA2);
        if (self->debug) {
            icl_console_print ("P: hash for '%s:%s' is %s", self->username, realm, entry->hash);
            icl_console_print ("P: realm=%s method=%s uri=%s qop=auth nonce=%s nc=%s cnonce=%s",
                realm, method, uri, nonce->key, auth_count, auth_cnonce);
            icl_console_print ("P: response=%s HA2=%s HA3=%s", auth_response, HA2, HA3);
        }
        if (streq (HA3, auth_response)) {
            ipr_password_hit (entry, address);
            self->result = IPR_PASSWORD_OK;
        }
        else {
            ipr_password_miss (entry, address);
            self->result = IPR_PASSWORD_INCORRECT;
        }
        icl_mem_free (HA2);
        icl_mem_free (HA3);
    }
    ipr_dict_table_destroy (&fields);
}
else
    self->result = IPR_PASSWORD_CHALLENGE;

if (self->result != IPR_PASSWORD_OK) {
    if (!self->nonce_test)
        nonce = ipr_nonce_new (self->nonces, NULL, self->nonce_ttl, self->nonce_quota);

    challenge = ipr_str_format (
        "Digest realm=\"%s\", qop=\"auth\", algorithm=\"MD5\", nonce=\"%s\"%s",
        realm, self->nonce_test? self->nonce_test: nonce->key,
        response? ", stale=\"true\"": "");
}
#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DIGEST))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 14);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_DIGEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_digest_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" address=\"%s\""
" realm=\"%s\""
" response=\"%s\""
" method=\"%s\""
" uri=\"%s\""
" challenge=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, address, realm, response, method, uri, challenge);
#endif


    return (challenge);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_set_nonce_ttl

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Sets the time-to-live for new nonces, in seconds.  By default, nonces
    expire after one hour (ttl = 3600).  If ttl is zero, new nonces are
    granted infinite time to live.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_set_nonce_ttl (
    ipr_password_table_t * self,        //  Reference to object
    size_t ttl                          //  Time to live, seconds
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_NONCE_TTL))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_nonce_ttl_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" ttl=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, ttl);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_TTL))
    icl_trace_record (NULL, ipr_password_table_dump, 15);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_NONCE_TTL))
    icl_stats_inc ("ipr_password_table_set_nonce_ttl", &s_ipr_password_table_set_nonce_ttl_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
self->nonce_ttl = ttl;
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_TTL))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 15);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_NONCE_TTL))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_nonce_ttl_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" ttl=\"%u\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, ttl, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_set_nonce_quota

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Sets the lifespan for new nonces, as a number of hits.  By default,
    nonces expire after 256 hits.  If the quota is zero, new nonces are
    granted infinite hits.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_set_nonce_quota (
    ipr_password_table_t * self,        //  Reference to object
    size_t quota                        //  Lifespan, in hits
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_nonce_quota_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" quota=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, quota);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA))
    icl_trace_record (NULL, ipr_password_table_dump, 16);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA))
    icl_stats_inc ("ipr_password_table_set_nonce_quota", &s_ipr_password_table_set_nonce_quota_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
self->nonce_quota = quota;
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 16);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_nonce_quota_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" quota=\"%u\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, quota, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_set_nonce_test

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Sets the test nonce value: if set, there will only be once nonce with
    this precise value.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_set_nonce_test (
    ipr_password_table_t * self,        //  Reference to object
    char * value                        //  Test nonce value
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_NONCE_TEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_nonce_test_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" value=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, value);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_TEST))
    icl_trace_record (NULL, ipr_password_table_dump, 17);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_NONCE_TEST))
    icl_stats_inc ("ipr_password_table_set_nonce_test", &s_ipr_password_table_set_nonce_test_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
if (self->nonces == NULL)
    self->nonces = ipr_nonce_table_new ();
self->nonce_test = value;
ipr_nonce_assume (self->nonces, self->nonce_test, self->nonce_ttl, self->nonce_quota);
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_TEST))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 17);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_NONCE_TEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_nonce_test_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" value=\"%s\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, value, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_set_debug

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    Sets the debug option, causes detailed output of the authentication methods.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_set_debug (
    ipr_password_table_t * self,        //  Reference to object
    Bool value                          //  Enable debug?
)
{
#if (defined (BASE_THREADSAFE))
    icl_mutex_t
        *mutex;
#endif

    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_DEBUG))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_debug_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" value=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, value);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_DEBUG))
    icl_trace_record (NULL, ipr_password_table_dump, 18);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SET_DEBUG))
    icl_stats_inc ("ipr_password_table_set_debug", &s_ipr_password_table_set_debug_stats);
#endif

#if (defined (BASE_THREADSAFE))
    mutex = self ? self->mutex : NULL;
    if (mutex)
        icl_mutex_lock (mutex);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

//
self->debug = value;
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_THREADSAFE))
    if (mutex)
        icl_mutex_unlock (mutex);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_DEBUG))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 18);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SET_DEBUG))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_set_debug_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" value=\"%i\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, value, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_selftest

    Type: Component method
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_selftest (
void)
{
ipr_password_table_t
    *table;
size_t
    nbr_items;
ipr_password_t
    *password;
char
    *challenge,
    *response;

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SELFTEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_selftest_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SELFTEST))
    icl_trace_record (NULL, ipr_password_table_dump, 19);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SELFTEST))
    icl_stats_inc ("ipr_password_table_selftest", &s_ipr_password_table_selftest_stats);
#endif

    //
    //  Simple tests of password management
    table = ipr_password_table_new (NULL);
    password = ipr_password_assume (table, "Aladdin", "hash");
    assert (password->type == IPR_PASSWD_BASIC);
    assert (streq (password->hash, "hash"));
    assert (ipr_password_table_search (table, "Aladdin"));
    assert (ipr_password_table_search (table, "Unknown") == NULL);
    ipr_password_destroy (&password);
    assert (ipr_password_table_search (table, "Aladdin") == NULL);
    ipr_password_table_destroy (&table);

    //  Test file load/sync/save functions
    ipr_file_delete ("nosuch");
    table = ipr_password_table_new ("nosuch");
    assert (table->nbr_items == 0);
    ipr_password_table_destroy (&table);

    ipr_file_delete ("test_password");
    table = ipr_password_table_new ("test_password");
    assert (ipr_password_table_load (table, "nosuch") == -1);
    ipr_password_assume (table, "Aladdin-md5", "$apr1$Uibxh...$Ud.6/BCLoSHsscd08Vj8q1");
    ipr_password_assume (table, "Aladdin-sha", "{SHA}W8r/fyL/UzygmbNAjq2HbA67qac=");
    ipr_password_assume (table, "Aladdin-crypt", "yyih1EpzpWg46");
    ipr_password_assume (table, "Aladdin-plain", "open sesame");
    nbr_items = table->nbr_items;
    assert (ipr_password_table_save (table) == nbr_items);
    ipr_password_table_destroy (&table);

    table = ipr_password_table_new ("test_password");
    assert (ipr_password_table_sync (table) == 0);
    assert (table->nbr_items == nbr_items);
    ipr_file_delete ("test_password");
    assert (ipr_password_table_sync (table) == -1);
    assert (table->nbr_items == nbr_items);
    ipr_password_table_destroy (&table);

    //  Test guard methods
    table = ipr_password_table_new ("test_password");
    ipr_password_assume (table, "Aladdin-1", "password1");
    ipr_password_assume (table, "Aladdin-2", "password2");
    assert (table->nbr_items == 2);
    assert (table->dirty == FALSE);
    ipr_password_table_guard_set (table, 256, 16, 3600);
    table->dirty = TRUE;
    ipr_password_table_guard_save (table);
    assert (ipr_password_table_save (table) == 2);
    assert (table->dirty == FALSE);
    ipr_password_table_destroy (&table);

    table = ipr_password_table_new ("test_password");
    assert (table->nbr_items == 2);
    ipr_password_table_guard_load (table);
    password = ipr_password_table_search (table, "Aladdin-1");
    assert (password);
    assert (password->hit_quota == 256);
    assert (password->miss_quota == 16);
    ipr_password_table_destroy (&table);

    //  Test Basic authentication, using the example from RFC 2617
    //
    table = ipr_password_table_new (NULL);

    challenge = ipr_password_table_basic (table, "127.0.0.1", "WallyWorld", NULL);
    assert (challenge);
    assert (streq (challenge, "Basic realm=\"WallyWorld\""));
    icl_mem_free (challenge);

    ipr_password_assume (table, "Aladdin", "$apr1$Uibxh...$Ud.6/BCLoSHsscd08Vj8q1");
    challenge = ipr_password_table_basic (
        table, "127.0.0.1", "WallyWorld", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    assert (challenge == NULL);
    assert (streq (table->username, "Aladdin"));

    ipr_password_assume (table, "Aladdin", "{SHA}W8r/fyL/UzygmbNAjq2HbA67qac=");
    challenge = ipr_password_table_basic (
        table, "127.0.0.1", "WallyWorld", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    assert (challenge == NULL);
    assert (streq (table->username, "Aladdin"));

#   if defined (__UNIX__)
    //  APR only supports crypt hash on Unix/Linux systems
    ipr_password_assume (table, "Aladdin", "yyih1EpzpWg46");
    challenge = ipr_password_table_basic (
        table, "127.0.0.1", "WallyWorld", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    assert (challenge == NULL);
    assert (streq (table->username, "Aladdin"));
#   endif

    ipr_password_assume (table, "Aladdin", "open sesame");
    challenge = ipr_password_table_basic (
        table, "127.0.0.1", "WallyWorld", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    assert (challenge == NULL);
    assert (streq (table->username, "Aladdin"));

    ipr_password_assume (table, "Aladdin", "bad password");
    challenge = ipr_password_table_basic (
        table, "127.0.0.1", "WallyWorld", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    assert (challenge);
    assert (streq (challenge, "Basic realm=\"WallyWorld\""));
    assert (table->result == IPR_PASSWORD_INCORRECT);
    assert (streq (table->username, "Aladdin"));
    icl_mem_free (challenge);

    password = ipr_password_table_search (table, "Aladdin");
    ipr_password_destroy (&password);
    challenge = ipr_password_table_basic (
        table, "127.0.0.1", "WallyWorld", "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==");
    assert (challenge);
    assert (streq (challenge, "Basic realm=\"WallyWorld\""));
    assert (table->result == IPR_PASSWORD_NOTFOUND);
    icl_mem_free (challenge);

    //  Test Digest authentication, using the example from RFC 2617
    //
    //  These methods don't report much, just test they are stable
    ipr_password_table_set_nonce_ttl   (table, 30);
    ipr_password_table_set_nonce_quota (table, 16);

    //  Check challenge if we don't supply any credentials
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", NULL, "GET", "/dir/index.html");
    assert (challenge);
    assert (ipr_str_prefixed (challenge, "Digest realm="));
    assert (table->result == IPR_PASSWORD_CHALLENGE);
    icl_mem_free (challenge);

    password = ipr_password_assume (table, "Mufasa:testrealm@host.com", "939e7578ed9e3c518a452acee763bce9");
    assert (password->type == IPR_PASSWD_DIGEST);

    //  Force this nonce for the test case
    ipr_password_table_set_nonce_test (table, "dcd98b7102dd2f0e8b11d0f600bfb0c093");

    //  This is the Authorization header we expect from the browser
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",

    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge == NULL);
    assert (streq (table->username, "Mufasa"));

    //  Try various mangled Authorization headers
    //  Bad user name
    response = "Digest username=\"Mustafa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_NOTFOUND);
    icl_mem_free (challenge);

    //  URI not accurate
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.htm\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_HOSTILE);
    icl_mem_free (challenge);

    //  Realm does not match
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@hosts.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_HOSTILE);
    icl_mem_free (challenge);

    //  Nonce has changed
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c0931\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_TRYAGAIN);
    icl_mem_free (challenge);

    //  QoP is incorrect
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth-int, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_HOSTILE);
    icl_mem_free (challenge);

    //  NC has not changed
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000000, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_HOSTILE);
    icl_mem_free (challenge);

    //  cnonce not specified
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "response=\"6629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_HOSTILE);
    icl_mem_free (challenge);

    //  Bad response hash
    response = "Digest username=\"Mufasa\", " \
               "realm=\"testrealm@host.com\", " \
               "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", " \
               "uri=\"/dir/index.html\", " \
               "qop=auth, " \
               "nc=00000001, " \
               "cnonce=\"0a4f113b\", " \
               "response=\"7629fae49393a05397450978507c4ef1\", " \
               "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"",
    challenge = ipr_password_table_digest (
        table, "127.0.0.1", "testrealm@host.com", response, "GET", "/dir/index.html");
    assert (challenge);
    assert (table->result == IPR_PASSWORD_INCORRECT);
    assert (streq (table->username, "Mufasa"));
    icl_mem_free (challenge);

    ipr_password_table_destroy (&table);
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SELFTEST))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 19);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SELFTEST))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_selftest_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_search

    Type: Component method
    Find object by key in the hash table. Returns reference to object
    if found, else null.
    -------------------------------------------------------------------------
 */

ipr_password_t *
    ipr_password_table_search (
    ipr_password_table_t * self,        //  Table to search
    char * key                          //  Hash key
)
{

    ipr_password_t *
        item = NULL;                    //  Not documented

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SEARCH))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_search_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SEARCH))
    icl_trace_record (NULL, ipr_password_table_dump, 20);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SEARCH))
    icl_stats_inc ("ipr_password_table_search", &s_ipr_password_table_search_stats);
#endif


//
IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (key)
    item = s_ipr_password_table_lookup (self, key);


#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SEARCH))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 20);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SEARCH))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_search_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" item=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, item);
#endif


    return (item);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_apply

    Type: Component method
    This method iterates through all the items in the hash and calls the
    callback function for each of them.
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_apply (
    ipr_password_table_t * self,        //  Table to iterate
    ipr_password_table_callback_fn * callback,   //  Not documented
    void * argument                     //  Arbitrary argument pointer
)
{

size_t
    pos;
ipr_password_t
    *item;

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_APPLY))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_apply_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" callback=\"%pp\""
" argument=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, callback, argument);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_APPLY))
    icl_trace_record (NULL, ipr_password_table_dump, 21);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_APPLY))
    icl_stats_inc ("ipr_password_table_apply", &s_ipr_password_table_apply_stats);
#endif


//
IPR_PASSWORD_TABLE_ASSERT_SANE (self);
for (pos = 0; pos != self->max_items; pos ++) {
    item = self->table_items [pos];
    while (item) {
        callback (item, argument);
        item = item->table_next;
    }
}

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_APPLY))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 21);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_APPLY))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_apply_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" callback=\"%pp\""
" argument=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, callback, argument);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_terminate

    Type: Component method
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_terminate (
void)
{

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_TERMINATE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_terminate_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_TERMINATE))
    icl_trace_record (NULL, ipr_password_table_dump, 22);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_TERMINATE))
    icl_stats_inc ("ipr_password_table_terminate", &s_ipr_password_table_terminate_stats);
#endif


#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_TERMINATE))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 22);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_TERMINATE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_terminate_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_show

    Type: Component method
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_show_ (
    void * item,                        //  The opaque pointer
    int opcode,                         //  The callback opcode
    FILE * trace_file,                  //  File to print to
    char * file,                        //  Source file
    size_t line                         //  Line number
)
{
    ipr_password_table_t
        *self;
    int
        container_links;
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    qbyte
        history_index;
#endif


#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SHOW))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_show_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" item=\"%pp\""
" opcode=\"%i\""
" trace_file=\"%pp\""
" file=\"%s\""
" line=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, item, opcode, trace_file, file, line);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SHOW))
    icl_trace_record (NULL, ipr_password_table_dump, 23);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SHOW))
    icl_stats_inc ("ipr_password_table_show", &s_ipr_password_table_show_stats);
#endif

self = item;
container_links = 0;
    assert (opcode == ICL_CALLBACK_DUMP);

    fprintf (trace_file, "    <ipr_password_table zombie = \"%u\" links = \"%u\" containers = \"%u\" file = \"%s\" line = \"%lu\"  pointer = \"%p\" />\n", self->zombie, self->links, container_links, file, (unsigned long) line, self);
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    if (self->history_last > IPR_PASSWORD_TABLE_HISTORY_LENGTH) {
        fprintf (trace_file, "        <!-- possess history too large (%d) - call iMatix-tech -->\n",
            self->history_last);
        history_index = (self->history_last + 1) % IPR_PASSWORD_TABLE_HISTORY_LENGTH;
        self->history_last %= IPR_PASSWORD_TABLE_HISTORY_LENGTH;
    }
    else
        history_index = 0;

    for (; history_index != self->history_last; history_index = (history_index + 1) % IPR_PASSWORD_TABLE_HISTORY_LENGTH) {
        fprintf (trace_file, "       <%s file = \"%s\" line = \"%lu\" links = \"%lu\" />\n",
            self->history_type [history_index],
            self->history_file [history_index],
            (unsigned long) self->history_line  [history_index],
            (unsigned long) self->history_links [history_index]);
    }
    fprintf (trace_file, "    </ipr_password_table>\n");
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SHOW))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 23);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SHOW))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_show_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" item=\"%pp\""
" opcode=\"%i\""
" trace_file=\"%pp\""
" file=\"%s\""
" line=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, item, opcode, trace_file, file, line);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_destroy

    Type: Component method
    Destroys a ipr_password_table_t object. Takes the address of a
    ipr_password_table_t reference (a pointer to a pointer) and nullifies the
    reference after use.  Does nothing if the reference is already
    null.
    Performs an agressive destroy of an object.  This involves:
    1. Removing the object from any containers it is in.
    2. Making the object an zombie
    3. Decrementing the object's link count
    4. If the link count is zero then freeing the object.
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_destroy_ (
    ipr_password_table_t * ( * self_p ),   //  Reference to object reference
    char * file,                        //  Source fileSource file
    size_t line                         //  Line numberLine number
)
{
    ipr_password_table_t *
        self = *self_p;                 //  Dereferenced Reference to object reference

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_DESTROY_PUBLIC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_destroy_public_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" self=\"%pp\""
" file=\"%s\""
" line=\"%i\""
" links=\"%i\""
" zombie=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, self, file, line, self?self->links:0, self?self->zombie:0);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DESTROY_PUBLIC))
    icl_trace_record (NULL, ipr_password_table_dump, 24);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_DESTROY_PUBLIC))
    icl_stats_inc ("ipr_password_table_destroy", &s_ipr_password_table_destroy_stats);
#endif

if (self) {
    if (icl_atomic_cas32 (&self->zombie, TRUE, FALSE) == FALSE)
        ipr_password_table_annihilate_ (self_p, file, line);

    if (self->links == 0) {
        icl_console_print ("Missing link on ipr_password_table object");
        ipr_password_table_show_ (self, ICL_CALLBACK_DUMP, stderr, file, line);
        abort ();
    }

    if (icl_atomic_dec32 ((volatile qbyte *) &self->links) == 0)
        ipr_password_table_free_ ((ipr_password_table_t *) self, file, line);
    *self_p = NULL;
}
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DESTROY_PUBLIC))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 24);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_DESTROY_PUBLIC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_destroy_public_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" self=\"%pp\""
" file=\"%s\""
" line=\"%i\""
" links=\"%i\""
" zombie=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, self, file, line, self?self->links:0, self?self->zombie:0);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_alloc

    Type: Component method
    -------------------------------------------------------------------------
 */

static ipr_password_table_t *
    ipr_password_table_alloc_ (
    char * file,                        //  Source file for call
    size_t line                         //  Line number for call
)
{

    ipr_password_table_t *
        self = NULL;                    //  Object reference

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_ALLOC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_alloc_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" file=\"%s\""
" line=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, file, line);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_ALLOC))
    icl_trace_record (NULL, ipr_password_table_dump, 25);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_ALLOC))
    icl_stats_inc ("ipr_password_table_alloc", &s_ipr_password_table_alloc_stats);
#endif

self = (ipr_password_table_t *) icl_mem_alloc_ (sizeof (ipr_password_table_t), file, line);
if (self)
    memset (self, 0, sizeof (ipr_password_table_t));


#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_ALLOC))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 25);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_ALLOC))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_alloc_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" file=\"%s\""
" line=\"%u\""
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, file, line, self);
#endif


    return (self);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_free

    Type: Component method
    Freess a ipr_password_table_t object.
    -------------------------------------------------------------------------
 */

static void
    ipr_password_table_free_ (
    ipr_password_table_t * self,        //  Object reference
    char * file,                        //  Source file
    size_t line                         //  Line number
)
{
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    int
        history_last;
#endif


#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_FREE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_free_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_FREE))
    icl_trace_record (NULL, ipr_password_table_dump, 26);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_FREE))
    icl_stats_inc ("ipr_password_table_free", &s_ipr_password_table_free_stats);
#endif

    if (self) {
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
        //  Track possession operation in history
        history_last = icl_atomic_inc32 ((volatile qbyte *) &self->history_last) + 1;
        self->history_file  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = file;
        self->history_line  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = line;
        self->history_type  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = "free";
        self->history_links [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = self->links;
#endif

#if (defined (BASE_THREADSAFE))
    if (self->mutex)
        icl_mutex_destroy (&self->mutex);
#endif
        memset (&self->object_tag, 0, sizeof (ipr_password_table_t) - ((byte *) &self->object_tag - (byte *) self));
//        memset (self, 0, sizeof (ipr_password_table_t));
        self->object_tag = IPR_PASSWORD_TABLE_DEAD;
        icl_mem_free (self);
    }
    self = NULL;
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_FREE))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 26);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_FREE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_free_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%u\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_lock

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_lock (
    ipr_password_table_t * self         //  Reference to object
)
{
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_LOCK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_lock_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LOCK))
    icl_trace_record (NULL, ipr_password_table_dump, 27);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_LOCK))
    icl_stats_inc ("ipr_password_table_lock", &s_ipr_password_table_lock_stats);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

#if (defined (BASE_THREADSAFE))
    icl_mutex_lock (self->mutex);
#endif
}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LOCK))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 27);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_LOCK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_lock_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_unlock

    Type: Component method
    Accepts a ipr_password_table_t reference and returns zero in case of success,
    1 in case of errors.
    -------------------------------------------------------------------------
 */

int
    ipr_password_table_unlock (
    ipr_password_table_t * self         //  Reference to object
)
{
    int
        rc = 0;                         //  Return code

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_UNLOCK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_unlock_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_UNLOCK))
    icl_trace_record (NULL, ipr_password_table_dump, 28);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_UNLOCK))
    icl_stats_inc ("ipr_password_table_unlock", &s_ipr_password_table_unlock_stats);
#endif

IPR_PASSWORD_TABLE_ASSERT_SANE (self);
if (!self->zombie) {

#if (defined (BASE_THREADSAFE))
    icl_mutex_unlock (self->mutex);
#endif

}
else
    rc = -1;                        //  Return error on zombie object.

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_UNLOCK))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 28);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_UNLOCK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_unlock_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" rc=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, rc);
#endif


    return (rc);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_link

    Type: Component method
    Adds a link (reference count) to an object.

    If the object has been zombified (ie destroyed while extra links were present),
    this method returns NULL and does not add any links.

    This method does not lock the object.
    -------------------------------------------------------------------------
 */

ipr_password_table_t *
    ipr_password_table_link_ (
    ipr_password_table_t * self,        //  Not documented
    char * file,                        //  Source file for call
    size_t line                         //  Line number for call
)
{
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    int
        history_last;
#endif

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_LINK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_link_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%u\""
" links=\"%i\""
" zombie=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line, self?self->links:0, self?self->zombie:0);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LINK))
    icl_trace_record (NULL, ipr_password_table_dump, 29);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_LINK))
    icl_stats_inc ("ipr_password_table_link", &s_ipr_password_table_link_stats);
#endif

    if (self) {
        IPR_PASSWORD_TABLE_ASSERT_SANE (self);
        if (file)
            icl_mem_possess_ (self, file, line);
        icl_atomic_inc32 ((volatile qbyte *) &self->links);
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
        //  Track possession operation in history
        history_last = icl_atomic_inc32 ((volatile qbyte *) &self->history_last) + 1;
        self->history_file  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = file;
        self->history_line  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = line;
        self->history_type  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = "link";
        self->history_links [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = self->links;
#endif
    }
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LINK))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 29);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_LINK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_link_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%u\""
" links=\"%i\""
" zombie=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line, self?self->links:0, self?self->zombie:0);
#endif


    return (self);
}
/*  -------------------------------------------------------------------------
    ipr_password_table_unlink

    Type: Component method
    Removes a link (reference count) to an object.  Sets the object pointer to NULL
    to indicate that it is no longer valid.
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_unlink_ (
    ipr_password_table_t * ( * self_p ),   //  Reference to object reference
    char * file,                        //  Source file for call
    size_t line                         //  Line number for call
)
{
#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
    int
        history_last;
#endif

    ipr_password_table_t *
        self = *self_p;                 //  Dereferenced Reference to object reference

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_UNLINK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_unlink_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%i\""
" links=\"%i\""
" zombie=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line, self?self->links:0, self?self->zombie:0);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_UNLINK))
    icl_trace_record (NULL, ipr_password_table_dump, 30);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_UNLINK))
    icl_stats_inc ("ipr_password_table_unlink", &s_ipr_password_table_unlink_stats);
#endif

    if (self) {
        IPR_PASSWORD_TABLE_ASSERT_SANE (self);
        if (self->links == 0) {
            icl_console_print ("Missing link on ipr_password_table object");
            ipr_password_table_show_ (self, ICL_CALLBACK_DUMP, stderr, file, line);
            abort ();
        }

#if defined (DEBUG) || defined (BASE_HISTORY) || defined (BASE_HISTORY_IPR_PASSWORD_TABLE)
        //  Track possession operation in history.  Pre-empt value of links
        //  after operation; otherwise race condition can result in writing
        //  to freed memory.
        history_last = icl_atomic_inc32 ((volatile qbyte *) &self->history_last) + 1;
        self->history_file  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = file;
        self->history_line  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = line;
        self->history_type  [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = "unlink";
        self->history_links [history_last % IPR_PASSWORD_TABLE_HISTORY_LENGTH] = self->links - 1;
#endif
        if (icl_atomic_dec32 ((volatile qbyte *) &self->links) == 0) {

        if (icl_atomic_cas32 (&self->zombie, TRUE, FALSE) == FALSE)
            ipr_password_table_annihilate_ (self_p, file, line);
        ipr_password_table_free_ ((ipr_password_table_t *) self, file, line);
    }
    *self_p = NULL;
}
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_UNLINK))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 30);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_UNLINK))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_unlink_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self=\"%pp\""
" file=\"%s\""
" line=\"%i\""
" links=\"%i\""
" zombie=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self, file, line, self?self->links:0, self?self->zombie:0);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_show_animation

    Type: Component method
    Enables animation of the component. Animation is sent to stdout.
    To enable animation you must generate using the option -animate:1.
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_show_animation (
    Bool enabled                        //  Are we enabling or disabling animation?
)
{

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SHOW_ANIMATION))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_show_animation_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" enabled=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, enabled);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SHOW_ANIMATION))
    icl_trace_record (NULL, ipr_password_table_dump, 31);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_SHOW_ANIMATION))
    icl_stats_inc ("ipr_password_table_show_animation", &s_ipr_password_table_show_animation_stats);
#endif

ipr_password_table_animating = enabled;
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SHOW_ANIMATION))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 31);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_SHOW_ANIMATION))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_show_animation_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" enabled=\"%i\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, enabled);
#endif

}
/*  -------------------------------------------------------------------------
    ipr_password_table_new_in_scope

    Type: Component method
    -------------------------------------------------------------------------
 */

void
    ipr_password_table_new_in_scope_ (
    ipr_password_table_t * * self_p,    //  Not documented
    icl_scope_t * _scope,               //  Not documented
    char * file,                        //  Source file for call
    size_t line,                        //  Line number for call
    char * filename                     //  Name of associated file
)
{
    icl_destroy_t *
        _destroy;                       //  Not documented

#if (defined (BASE_ANIMATE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)  ||  defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_NEW_IN_SCOPE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_new_in_scope_start"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self_p=\"%pp\""
" _scope=\"%pp\""
" file=\"%s\""
" line=\"%u\""
" filename=\"%s\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self_p, _scope, file, line, filename);
#endif

#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_NEW_IN_SCOPE))
    icl_trace_record (NULL, ipr_password_table_dump, 32);
#endif

#if (defined (BASE_STATS)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE)  ||  defined (BASE_STATS_IPR_PASSWORD_TABLE_NEW_IN_SCOPE))
    icl_stats_inc ("ipr_password_table_new_in_scope", &s_ipr_password_table_new_in_scope_stats);
#endif

*self_p = ipr_password_table_new_ (file,line,filename);

if (*self_p) {
    _destroy = icl_destroy_new   ((void * *) self_p, (icl_destructor_fn *) ipr_password_table_destroy_);
    icl_destroy_list_queue (_scope, _destroy);
    icl_destroy_unlink (&_destroy);
}
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_NEW_IN_SCOPE))
    icl_trace_record (NULL, ipr_password_table_dump, 0x10000 + 32);
#endif

#if (defined (BASE_ANIMATE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE)   || defined (BASE_ANIMATE_IPR_PASSWORD_TABLE_NEW_IN_SCOPE))
    if (ipr_password_table_animating)
        icl_console_print ("<ipr_password_table_new_in_scope_finish"
#if (defined (BASE_THREADSAFE))
" thread=\"%pp\""
#endif
" self_p=\"%pp\""
" _scope=\"%pp\""
" file=\"%s\""
" line=\"%u\""
" filename=\"%s\""
" _destroy=\"%pp\""
"/>"
#if (defined (BASE_THREADSAFE))
, apr_os_thread_current ()
#endif
, self_p, _scope, file, line, filename, _destroy);
#endif

}
#if (defined (BASE_TRACE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_NEW)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DESTROY)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_INSERT)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_REMOVE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SEARCH_DIGEST)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LOAD)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SAVE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SYNC)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SET)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_LOAD)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SAVE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_GUARD_SYNC)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_BASIC)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DIGEST)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_TTL)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_QUOTA)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_NONCE_TEST)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SET_DEBUG)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SELFTEST)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SEARCH)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_APPLY)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_TERMINATE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SHOW)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_DESTROY_PUBLIC)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_ALLOC)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_FREE)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LOCK)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_UNLOCK)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_LINK)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_UNLINK)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_SHOW_ANIMATION)   || defined (BASE_TRACE_IPR_PASSWORD_TABLE_NEW_IN_SCOPE) )
void
ipr_password_table_dump (icl_os_thread_t thread, apr_time_t time, qbyte info)
{
    dbyte
        method = info & 0xFFFF;
    char
        *method_name = NULL;
        
    switch (method) {
        case 1: method_name = "new"; break;
        case 2: method_name = "destroy"; break;
        case 3: method_name = "insert"; break;
        case 4: method_name = "remove"; break;
        case 5: method_name = "search digest"; break;
        case 6: method_name = "load"; break;
        case 7: method_name = "save"; break;
        case 8: method_name = "sync"; break;
        case 9: method_name = "guard set"; break;
        case 10: method_name = "guard load"; break;
        case 11: method_name = "guard save"; break;
        case 12: method_name = "guard sync"; break;
        case 13: method_name = "basic"; break;
        case 14: method_name = "digest"; break;
        case 15: method_name = "set nonce ttl"; break;
        case 16: method_name = "set nonce quota"; break;
        case 17: method_name = "set nonce test"; break;
        case 18: method_name = "set debug"; break;
        case 19: method_name = "selftest"; break;
        case 20: method_name = "search"; break;
        case 21: method_name = "apply"; break;
        case 22: method_name = "terminate"; break;
        case 23: method_name = "show"; break;
        case 24: method_name = "destroy public"; break;
        case 25: method_name = "alloc"; break;
        case 26: method_name = "free"; break;
        case 27: method_name = "lock"; break;
        case 28: method_name = "unlock"; break;
        case 29: method_name = "link"; break;
        case 30: method_name = "unlink"; break;
        case 31: method_name = "show animation"; break;
        case 32: method_name = "new in scope"; break;
    }
    icl_console_print_thread_time (thread, time,
                                   "ipr_password_table %s%s",
                                   (info > 0xFFFF) ? "/" : "",
                                   method_name);
}
#endif

static inline unsigned int
s_key_hash (char * key, size_t hash_size)
{
    uint
        key_hash = 0;

    //  Torek hashing function
    while (*key) {
        key_hash *= 33;
        key_hash += *key;
        key++;
    }
    key_hash %= hash_size;
    return (key_hash);
}

static inline Bool
s_key_equal (char * key1, char * key2)
{
    return (streq (key1, key2));
}

static int
s_ipr_password_table_insert (ipr_password_table_t *self, ipr_password_t *item, char * key)
{
    qbyte
        index,
        new_index;
    ipr_password_t
        *current_item,
        *next_item;
    int
        rc = 0;

    if (self->nbr_items >= self->max_items * IPR_PASSWORD_TABLE_LOAD_FACTOR / 100) {

        //  Load factor of hash table was exceeded
        //  We need to increase its size by GROWTH_FACTOR and rebuild it
        ipr_password_t
            **new_items;
        size_t
            new_max_items;

        //  Create new hash table
        new_max_items = self->max_items * IPR_PASSWORD_TABLE_GROWTH_FACTOR / 100;
        new_items = icl_mem_alloc (sizeof (ipr_password_t*) * new_max_items);
        assert (new_items);
        memset (new_items, 0, sizeof (ipr_password_t*) * new_max_items);

        //  Move all items to the new hash table
        for (index = 0; index != self->max_items; index++) {
            current_item = self->table_items [index];
            while (current_item) {
                next_item = current_item->table_next;
                new_index = s_key_hash (current_item->key, new_max_items);
                current_item->table_index = new_index;
                current_item->table_next = new_items [new_index];
                new_items [new_index] = current_item;
                current_item = next_item;
            }
        }

        //  Destroy old hash table
        icl_mem_free (self->table_items);
        self->table_items = new_items;
        self->max_items = new_max_items;
    }

    //  Insert new item itself
    index = s_key_hash (key, self->max_items);
    current_item = self->table_items [index];
    while (current_item) {
        if (s_key_equal (current_item->key, key)) {
            //  Attempted duplicate insertion
            rc = -1;
            break;
        }
        current_item = current_item->table_next;
    }
    if (!current_item) {
        item->table_head = self;
        item->table_index = index;
        item->table_next = self->table_items [index];
        self->table_items [index] = item;
        icl_shortstr_cpy (item->key, key);
        self->nbr_items++;
    }
    return rc;
}

static ipr_password_t *
s_ipr_password_table_lookup (ipr_password_table_t *self, char * key)
{
    qbyte
        index;
    ipr_password_t
        *item;

    index = s_key_hash (key, self->max_items);
    item = self->table_items [index];

    while (item) {
        if (s_key_equal (item->key, key))
            break;
        item = item->table_next;
    }
    return item;
}

static void
s_ipr_password_table_remove (ipr_password_t *item)
{
    ipr_password_t
        *current_item,
        **prev_item;

    prev_item = &(item->table_head->table_items [item->table_index]);
    current_item = item->table_head->table_items [item->table_index];

    while (current_item) {
        if (current_item == item)
            break;
        prev_item = &(current_item->table_next);
        current_item = current_item->table_next;
    }
    assert (current_item == item);

    if (item) {
        item->table_head->nbr_items--;
        *prev_item = item->table_next;
        item->table_head = NULL;
        item->table_index = 0;
        item->table_next = NULL;
        icl_shortstr_cpy (item->key, "");
    }
}

static void
s_ipr_password_table_purge (ipr_password_table_t *self)
{
    uint
        table_idx;
    ipr_password_t
        *current_item,
        *next_item;

    for (table_idx = 0; table_idx < self->max_items; table_idx++) {
        current_item = self->table_items [table_idx];
        while (current_item) {
            next_item = current_item->table_next;
            s_ipr_password_table_remove (current_item);
            ipr_password_destroy (&current_item);
            current_item = next_item;
        }
    }
}

//  Embed the version information in the resulting binary                      

char *ipr_password_table_version_start  = "VeRsIoNsTaRt:ipc";
char *ipr_password_table_component  = "ipr_password_table ";
char *ipr_password_table_version   = "1.0 ";
char *ipr_password_table_copyright  = "Copyright (c) 1996-2009 iMatix Corporation";
char *ipr_password_table_filename  = "ipr_password_table.icl ";
char *ipr_password_table_builddate  = "2009/02/19 ";
char *ipr_password_table_version_end  = "VeRsIoNeNd:ipc";

