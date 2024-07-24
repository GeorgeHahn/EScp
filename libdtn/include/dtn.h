/* DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
 *
 *  THIS IS A HAND GENERATED FILE. YOU MUST MANUALLY ENSURE IT MATCHES
 *  ARGS.H, FILE_IO.H, AND ANY OTHER FILES IT MAY OR MAY NOT DEPEND ON
 *
 * DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
 */

// See rust/README.md for information on how to use it.


#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>

#include <dirent.h>

struct sockaddr_storage {
  char byte[128];
};

extern uint64_t verbose_logging;

struct iovec
  {
    void *iov_base; /* Pointer to data.  */
    uint64_t iov_len; /* Length of data.  */
  };

#define THREAD_COUNT  32
#define ESCP_MSG_COUNT 16384
#define ESCP_MSG_SZ    128
extern struct dtn_args* ESCP_DTN_ARGS;
extern uint64_t ESCP_DROPPED_MSG;

struct dtn_args* args_new () ;
void affinity_set ( struct dtn_args* args );
struct sockaddr_storage dns_lookup( char*, char* );
char* dtn_log_getnext();
char* dtn_err_getnext();

struct file_object {
  // Generic object that abstracts file_io operation to different engines
  int32_t QD;
  int32_t pad12;

  uint32_t blk_sz;
  uint16_t id;
  uint16_t io_type;  // Posix, uring, ...

  int64_t  head;
  int64_t  tail;     // 32

  uint64_t pad11;    //
  int32_t  io_flags; // i.e. O_DIRECT, O_RDONLY
  int32_t  io_ret;   // 48

  uint32_t thread_count;
  uint64_t pad1;
  uint32_t pad2;      // 64


  void*    pvdr;     // Provider internal ptr
  char*    args;

  int   (*open)    (const char*, int, ...);

  DIR*   (*fopendir) (int);
  struct dirent* (*readdir) (DIR *dirp);

  int   (*close_fd) (int);
  int   (*close)    (void*);
  int   (*truncate) (void*, int64_t);
  int   (*fstat)   (int, struct stat*);

  void* (*fetch)   (void*);
  void  (*flush)   (void*);
  void* (*set)     (void*, int32_t key, uint64_t value);
  void* (*get)     (void*, int32_t key);
  void* (*submit)  (void*, int32_t* sz, uint64_t* offset);
  void* (*complete)(void*, void*);

  void* (*cleanup) (void*);


};

void file_iotest( void* );
void file_iotest_finish();

void file_randrd( void* buf, int count );
void file_prng( void* buf, int sz );

struct file_object* file_memoryinit( void*, int );

void* file_posixget( void* arg, int32_t key );
void* file_posixset( void* arg, int32_t key, uint64_t value );

int file_posixinit( struct file_object* fob );
void* file_posixfetch( void* arg );
void file_posixflush( void* arg );

int file_uringinit( struct file_object* fob );
int file_dummyinit( struct file_object* fob );
// int shmem_init( struct file_object* fob );

int32_t file_hash( void* block, int sz, int seed );


struct file_stat_type* file_addfile(uint64_t fileno, int fd, uint32_t crc, int64_t);
struct file_stat_type* file_next( int id );
struct file_stat_type* file_wait( uint64_t fileno );

int file_get_activeport( void* args );

struct dtn_args {
  bool do_server;
  bool do_ssh;
  bool do_crypto;
  bool do_hash;
  bool nodirect;
  bool recursive;

  int file_count;
  int host_count;
  int mtu;
  int block;
  int flags;
  int QD;

  int compression;
  int hugepages;

  int64_t disable_io;
  uint64_t pacing;

  char* io_engine_name;
  int io_engine;
  unsigned int window;

  uint64_t session_id;
  uint8_t crypto_key[16];

  bool do_affinity;
  int cpumask_len;
  uint8_t cpumask_bytes[32];
  uint64_t nodemask;

  int sock_store_count;
  struct sockaddr_storage sock_store[THREAD_COUNT] __attribute__ ((aligned(64)));

  struct file_object *fob __attribute__ ((aligned(64)));
  int thread_id __attribute__ ((aligned(64)));
  int thread_count __attribute__ ((aligned(64)));
  uint16_t active_port __attribute__ ((aligned(64)));


  uint64_t debug_claim __attribute__ ((aligned(64)));
  uint64_t debug_count __attribute__ ((aligned(64)));
  uint8_t  debug_buf[ESCP_MSG_SZ*ESCP_MSG_COUNT];
  uint64_t debug_poison;

  uint64_t msg_claim   __attribute__ ((aligned(64)));
  uint64_t msg_count   __attribute__ ((aligned(64)));
  uint8_t  msg_buf[ESCP_MSG_SZ*ESCP_MSG_COUNT];
  uint64_t msg_poison;

  uint64_t bytes_io     __attribute__ ((aligned(64)));
  uint64_t files_closed __attribute__ ((aligned(64)));
  uint64_t files_open   __attribute__ ((aligned(64)));

};

void meta_send( char* buf, char* hdr, int len );
void tx_start(struct dtn_args* args );
int rx_start(struct dtn_args* args );
void print_args ( struct dtn_args* args );
void finish_transfer( struct dtn_args* args, uint64_t );
void dtn_waituntilready( void* arg );
void tx_init( struct dtn_args* args );

int64_t get_bytes_io( struct dtn_args* dtn );
int64_t tx_getclosed();

char* human_write(uint64_t number, bool is_bytes);

struct fc_info_struct {
  uint64_t state;
  uint64_t file_no;
  uint64_t bytes;
  uint32_t crc;
  uint32_t completion;
  uint64_t pad2[4];
};
struct fc_info_struct* fc_pop();
void fc_push( uint64_t file_no, uint64_t bytes, uint32_t crc );

uint8_t* meta_recv();
void meta_complete();
