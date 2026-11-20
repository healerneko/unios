
/* UniOS: tiny UEFI hardware postcard for the Lenovo B490. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short i16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned long long UINTN;
typedef u16 CHAR16;
typedef u64 EFI_STATUS;
typedef void *EFI_HANDLE;
typedef struct { u32 a; u16 b, c; u8 d[8]; } EFI_GUID;
typedef struct { u16 Year;u8 Month,Day,Hour,Minute,Second,Pad1;u32 Nanosecond; i16 TimeZone;u8 Daylight,Pad2; } EFI_TIME;
typedef struct EFI_RNG EFI_RNG;
struct EFI_RNG { void *GetInfo; EFI_STATUS (__attribute__((ms_abi)) *GetRNG)(EFI_RNG*,EFI_GUID*,UINTN,u8*); };
typedef struct { u32 MediaId;u8 RemovableMedia,MediaPresent,LogicalPartition,ReadOnly,WriteCaching;u32 BlockSize,IoAlign;u64 LastBlock,LowestAlignedLba;u32 LogicalBlocksPerPhysicalBlock,OptimalTransferLengthGranularity; } EFI_BLOCK_MEDIA;
typedef struct { u64 Revision;EFI_BLOCK_MEDIA *Media;void *Reset,*ReadBlocks,*WriteBlocks,*FlushBlocks; } EFI_BLOCK_IO;
typedef struct { u8 Length,DescriptorType;u16 BcdUSB;u8 DeviceClass,DeviceSubClass,DeviceProtocol,MaxPacketSize0;u16 IdVendor,IdProduct,BcdDevice;u8 StrManufacturer,StrProduct,StrSerialNumber,NumConfigurations; } EFI_USB_DEVICE_DESC;
typedef struct EFI_USB_IO EFI_USB_IO;
struct EFI_USB_IO { void *ControlTransfer,*BulkTransfer,*AsyncInterruptTransfer,*SyncInterruptTransfer,*IsochronousTransfer,*AsyncIsochronousTransfer;EFI_STATUS (__attribute__((ms_abi)) *GetDeviceDescriptor)(EFI_USB_IO*,EFI_USB_DEVICE_DESC*);void *GetConfigDescriptor,*GetInterfaceDescriptor,*GetEndpointDescriptor,*GetStringDescriptor,*GetSupportedLanguages,*PortReset; };
typedef struct { u64 Signature; u32 Revision, HeaderSize, Crc32, Reserved; } EFI_TABLE_HEADER;
typedef struct EFI_TEXT_OUT EFI_TEXT_OUT;
struct EFI_TEXT_OUT { void *Reset; EFI_STATUS (__attribute__((ms_abi)) *OutputString)(EFI_TEXT_OUT *, CHAR16 *); void *TestString; void *QueryMode; void *SetMode; EFI_STATUS (__attribute__((ms_abi)) *SetAttribute)(EFI_TEXT_OUT*,u32); EFI_STATUS (__attribute__((ms_abi)) *ClearScreen)(EFI_TEXT_OUT*); EFI_STATUS (__attribute__((ms_abi)) *SetCursorPosition)(EFI_TEXT_OUT*,u32,u32); };
typedef struct EFI_TEXT_IN EFI_TEXT_IN;
typedef struct { u16 ScanCode, UnicodeChar; } EFI_INPUT_KEY;
typedef struct { u8 Blue, Green, Red, Reserved; } EFI_PIXEL;
typedef struct { u32 Version, HorizontalResolution, VerticalResolution, PixelFormat; u32 PixelInformation[4]; u32 PixelsPerScanLine; } EFI_GOP_INFO;
typedef struct { u32 MaxMode, Mode; EFI_GOP_INFO *Info; UINTN SizeOfInfo; u64 FrameBufferBase, FrameBufferSize; } EFI_GOP_MODE;
typedef struct EFI_GOP EFI_GOP;
struct EFI_GOP { void *QueryMode; void *SetMode; EFI_STATUS (__attribute__((ms_abi)) *Blt)(EFI_GOP*,EFI_PIXEL*,u32,UINTN,UINTN,UINTN,UINTN,UINTN,UINTN,UINTN); EFI_GOP_MODE *Mode; };
struct EFI_TEXT_IN { void *Reset; EFI_STATUS (__attribute__((ms_abi)) *ReadKeyStroke)(EFI_TEXT_IN*,EFI_INPUT_KEY*); void *WaitForKey; };
typedef struct EFI_SYSTEM_TABLE {
 EFI_TABLE_HEADER H; CHAR16 *FirmwareVendor; u32 FirmwareRevision; EFI_HANDLE ConsoleInHandle;
 EFI_TEXT_IN *ConIn; EFI_HANDLE ConsoleOutHandle; EFI_TEXT_OUT *ConOut; EFI_HANDLE StandardErrorHandle;
 EFI_TEXT_OUT *StdErr; void *RuntimeServices; void *BootServices; UINTN NumberOfTableEntries; void *ConfigurationTable;
} EFI_SYSTEM_TABLE;
typedef struct EFI_FILE EFI_FILE;
struct EFI_FILE {
 u64 Revision; EFI_STATUS (__attribute__((ms_abi)) *Open)(EFI_FILE*,EFI_FILE**,CHAR16*,u64,u64); EFI_STATUS (__attribute__((ms_abi)) *Close)(EFI_FILE*); EFI_STATUS (__attribute__((ms_abi)) *Delete)(EFI_FILE*); EFI_STATUS (__attribute__((ms_abi)) *Read)(EFI_FILE*,UINTN*,void*);
 EFI_STATUS (__attribute__((ms_abi)) *Write)(EFI_FILE*,UINTN*,void*); EFI_STATUS (__attribute__((ms_abi)) *GetPosition)(EFI_FILE*,u64*); EFI_STATUS (__attribute__((ms_abi)) *SetPosition)(EFI_FILE*,u64);
 EFI_STATUS (__attribute__((ms_abi)) *GetInfo)(EFI_FILE*,EFI_GUID*,UINTN*,void*); EFI_STATUS (__attribute__((ms_abi)) *SetInfo)(EFI_FILE*,EFI_GUID*,UINTN,void*); EFI_STATUS (__attribute__((ms_abi)) *Flush)(EFI_FILE*);
};
typedef struct { void *Revision; EFI_STATUS (__attribute__((ms_abi)) *OpenVolume)(void*,EFI_FILE**); } EFI_SIMPLE_FS;
typedef struct { u32 Revision; void *ParentHandle; void *SystemTable; EFI_HANDLE DeviceHandle; void *FilePath; void *Reserved; u32 LoadOptionsSize; void *LoadOptions; void *ImageBase; u64 ImageSize; u32 ImageCodeType, ImageDataType; void *Unload; } EFI_LOADED_IMAGE;
static EFI_GUID loaded_guid={0x5b1b31a1,0x9562,0x11d2,{0x8e,0x3f,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static EFI_GUID fs_guid={0x964e5b22,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static EFI_GUID global_guid={0x8be4df61,0x93ca,0x11d2,{0xaa,0x0d,0x00,0xe0,0x98,0x03,0x2b,0x8c}};
static EFI_GUID gop_guid={0x9042a9de,0x23dc,0x4a38,{0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}};
static EFI_GUID file_info_guid={0x09576e92,0x6d3f,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static EFI_GUID rng_guid={0x3152bca5,0xeade,0x433d,{0x86,0x2e,0xc0,0x1c,0xdc,0x29,0x1f,0x44}};
static EFI_GUID block_guid={0x964e5b21,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static EFI_GUID usb_guid={0x2b2f68d6,0x0cd2,0x44cf,{0x8e,0x8b,0xbb,0xa2,0x0b,0x1b,0x5b,0x75}};
static EFI_GUID fs_info_guid={0x09576e91,0x6d3f,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static CHAR16 fail_open[] = {'E','r','r','o',' ','a','o',' ','c','r','i','a','r',' ','U','N','I','O','S','\\','L','O','G','.','T','X','T','.','\r','\n',0};
static CHAR16 fail_write[] = {'E','r','r','o',' ','a','o',' ','e','s','c','r','e','v','e','r',' ','o',' ','l','o','g','.','\r','\n',0};
EFI_STATUS __attribute__((ms_abi)) efi_main(EFI_HANDLE, EFI_SYSTEM_TABLE *);
/* Gera uma entrada .reloc para o carregador UEFI poder mover o app. */
static void * volatile relocation_anchor = (void *)&efi_main;
static CHAR16 code_line[]={'E','F','I',' ','s','t','a','t','u','s',':',' ','0','0','0','0','0','0','0','0','0','0','0','0','0','0','\r','\n',0};
static void show_status(EFI_TEXT_OUT *out, EFI_STATUS status){ const char *h="0123456789ABCDEF"; for(int i=0;i<16;i++) code_line[11+i]=(CHAR16)h[(status>>((15-i)*4))&15]; out->OutputString(out,code_line); }
static char report[768];
static unsigned pos;
static u8 auth_salt[16],auth_hash[32];
static int auth_loaded;
#define AUTH_ITERATIONS 100000
static u32 cpuid(u32 leaf,u32 sub,u32 *b,u32 *c,u32 *d);
static char cpu_brand[49];
static u32 cpu_cores=1;
static u64 memory_total_mib,boot_epoch;
static char shell_history[16][160];
static UINTN shell_history_count;
static EFI_PIXEL moon_art[470*300];
static void out(EFI_SYSTEM_TABLE *st,const CHAR16 *s){st->ConOut->OutputString(st->ConOut,(CHAR16*)s);}
static void stall(EFI_SYSTEM_TABLE *st,UINTN us){EFI_STATUS (__attribute__((ms_abi)) *pause)(UINTN)=((void**)st->BootServices)[3+28];pause(us);}
static u32 rotr32(u32 x,u32 n){return (x>>n)|(x<<(32-n));}
static void sha256_block(u32 h[8],const u8 block[64]){
 static const u32 k[64]={0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2};
 u32 w[64];for(int i=0;i<16;i++)w[i]=((u32)block[i*4]<<24)|((u32)block[i*4+1]<<16)|((u32)block[i*4+2]<<8)|block[i*4+3];
 for(int i=16;i<64;i++){u32 x=w[i-15],y=w[i-2];u32 s0=rotr32(x,7)^rotr32(x,18)^(x>>3),s1=rotr32(y,17)^rotr32(y,19)^(y>>10);w[i]=w[i-16]+s0+w[i-7]+s1;}
 u32 a=h[0],b=h[1],c=h[2],d=h[3],e=h[4],f=h[5],g=h[6],z=h[7];
 for(int i=0;i<64;i++){u32 s1=rotr32(e,6)^rotr32(e,11)^rotr32(e,25),ch=(e&f)^(~e&g),t1=z+s1+ch+k[i]+w[i];u32 s0=rotr32(a,2)^rotr32(a,13)^rotr32(a,22),maj=(a&b)^(a&c)^(b&c),t2=s0+maj;z=g;g=f;f=e;e=d+t1;d=c;c=b;b=a;a=t1+t2;}
 h[0]+=a;h[1]+=b;h[2]+=c;h[3]+=d;h[4]+=e;h[5]+=f;h[6]+=g;h[7]+=z;
}
static void sha256(const u8 *data,UINTN length,u8 digest[32]){
 static const u32 initial[8]={0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19};
 u32 h[8];for(int i=0;i<8;i++)h[i]=initial[i];u8 padded[128];UINTN total=((length+9+63)/64)*64;
 for(UINTN i=0;i<total;i++)padded[i]=0;for(UINTN i=0;i<length;i++)padded[i]=data[i];padded[length]=0x80;u64 bits=(u64)length*8;
 for(int i=0;i<8;i++)padded[total-1-i]=(u8)(bits>>(i*8));
 for(UINTN i=0;i<total;i+=64)sha256_block(h,padded+i);
 for(int i=0;i<8;i++){digest[i*4]=(u8)(h[i]>>24);digest[i*4+1]=(u8)(h[i]>>16);digest[i*4+2]=(u8)(h[i]>>8);digest[i*4+3]=(u8)h[i];}
}
static void hmac_sha256(const u8 *key,UINTN keylen,const u8 *message,UINTN length,u8 digest[32]){
 u8 k[64]={0},inner[128],middle[32],outer[96];for(UINTN i=0;i<keylen&&i<64;i++)k[i]=key[i];
 for(int i=0;i<64;i++)inner[i]=k[i]^0x36;for(UINTN i=0;i<length;i++)inner[64+i]=message[i];sha256(inner,64+length,middle);
 for(int i=0;i<64;i++)outer[i]=k[i]^0x5c;for(int i=0;i<32;i++)outer[64+i]=middle[i];sha256(outer,96,digest);
}
static void pbkdf2_sha256(const u8 *password,UINTN password_len,const u8 salt[16],u32 iterations,u8 derived[32]){
 u8 input[20],u[32],t[32];for(int i=0;i<16;i++)input[i]=salt[i];input[16]=input[17]=input[18]=0;input[19]=1;
 hmac_sha256(password,password_len,input,20,u);for(int i=0;i<32;i++)t[i]=u[i];
 for(u32 round=1;round<iterations;round++){hmac_sha256(password,password_len,u,32,u);for(int i=0;i<32;i++)t[i]^=u[i];}
 for(int i=0;i<32;i++)derived[i]=t[i];
}
static int password_bytes(const CHAR16 *password,u8 bytes[64],UINTN *length){UINTN n=0;while(password[n]){if(password[n]>127||n>=63)return 0;bytes[n]=(u8)password[n];n++;}*length=n;return n>0;}
static int constant_equal(const u8 *a,const u8 *b,UINTN length){u8 diff=0;for(UINTN i=0;i<length;i++)diff|=a[i]^b[i];return diff==0;}
static void make_salt(EFI_SYSTEM_TABLE *st,u8 salt[16]){
 EFI_STATUS (__attribute__((ms_abi)) *locate)(EFI_GUID*,void*,void**)=((void**)st->BootServices)[3+37];EFI_RNG *rng=0;
 locate(&rng_guid,0,(void**)&rng);
 if(rng&&rng->GetRNG&&!rng->GetRNG(rng,0,16,salt))return;
 u8 seed[64]={0};EFI_TIME now={0};EFI_STATUS (__attribute__((ms_abi)) *get_time)(EFI_TIME*,void*)=((void**)st->RuntimeServices)[3];get_time(&now,0);
 for(int i=0;i<sizeof(now);i++)seed[i]=((u8*)&now)[i];u64 count=0;EFI_STATUS (__attribute__((ms_abi)) *monotonic)(u64*)=((void**)st->BootServices)[3+27];monotonic(&count);
 for(int i=0;i<8;i++)seed[16+i]=(u8)(count>>(i*8));u32 b,c,d;u32 a=cpuid(0,0,&b,&c,&d);u32 vals[4]={a,b,c,d};for(int i=0;i<16;i++)seed[24+i]=((u8*)vals)[i];
 u8 digest[32];sha256(seed,40,digest);for(int i=0;i<16;i++)salt[i]=digest[i];
}
static void status_line(EFI_SYSTEM_TABLE *st,int first,const CHAR16 *text){
 st->ConOut->SetAttribute(st->ConOut,0x0a);
 out(st,(CHAR16*)L"[  OK  ] ");
 st->ConOut->SetAttribute(st->ConOut,0x07); out(st,text); out(st,(CHAR16*)L"\r\n"); stall(st,3000000);
}
static EFI_GOP *get_gop(EFI_SYSTEM_TABLE *st){
 EFI_STATUS (__attribute__((ms_abi)) *locate)(EFI_GUID*,void*,void**)=((void**)st->BootServices)[3+37];
 EFI_GOP *gop=0; if(locate(&gop_guid,0,(void**)&gop))return 0; return gop;
}
static u32 draw_moon(EFI_SYSTEM_TABLE *st,int pulse){
 EFI_GOP *gop=get_gop(st); if(!gop || !gop->Mode || !gop->Mode->Info)return 0;
 if(gop->Mode->Info->HorizontalResolution<470 || gop->Mode->Info->VerticalResolution<300)return 0;
 EFI_PIXEL bg={60,24,36,0}, ivory={238,218,255,0}, purple=pulse?(EFI_PIXEL){255,205,250,0}:(EFI_PIXEL){226,143,190,0}, lilac=pulse?(EFI_PIXEL){255,235,255,0}:(EFI_PIXEL){255,197,224,0};
 for(int y=0;y<300;y++)for(int x=0;x<470;x++)moon_art[y*470+x]=bg;
 for(int y=0;y<300;y++)for(int x=0;x<470;x++){
  int dx=x-178,dy=y-150;
  if(dx*dx+dy*dy<=103*103)moon_art[y*470+x]=ivory;
  dx=x-128; dy=y-150;
  if(dx*dx+dy*dy<=96*96)moon_art[y*470+x]=bg;
 }
 for(int i=-7;i<=7;i++){
  int thick=(7-((i<0)?-i:i))/3;
  for(int t=-thick;t<=thick;t++){
   moon_art[(63+i)*470+348+t]=purple;moon_art[63*470+348+i+t]=purple;
   if(i>=-5&&i<=5){moon_art[(173+i)*470+414+t]=lilac;moon_art[173*470+414+i+t]=lilac;}
   if(i>=-3&&i<=3){moon_art[(250+i)*470+294+t]=purple;moon_art[250*470+294+i+t]=purple;}
  }
 }
 EFI_STATUS status=gop->Blt(gop,&bg,0,0,0,0,0,gop->Mode->Info->HorizontalResolution,gop->Mode->Info->VerticalResolution,0);if(status)return 0;
 for(int y=0;y<300;y++)for(int x=0;x<470;){EFI_PIXEL color=moon_art[y*470+x];if(color.Blue==bg.Blue&&color.Green==bg.Green&&color.Red==bg.Red){x++;continue;}int end=x+1;while(end<470){EFI_PIXEL next=moon_art[y*470+end];if(next.Blue!=color.Blue||next.Green!=color.Green||next.Red!=color.Red)break;end++;}status=gop->Blt(gop,&color,0,0,0,x,y,end-x,1,0);if(status)return 0;x=end;}
 return gop->Mode->Info->HorizontalResolution;
}
static UINTN draw_moon_text(EFI_SYSTEM_TABLE *st,EFI_FILE *root){
 static CHAR16 path[]={'M','O','O','N','.','T','X','T',0};
 EFI_FILE *file=0;
 st->ConOut->SetAttribute(st->ConOut,0x0a);
 if(root->Open(root,&file,path,1,0)){
  out(st,(CHAR16*)L"Moon.txt nao encontrado no volume UNIOS.\r\n");
  st->ConOut->SetAttribute(st->ConOut,0x07);return 1;
 }
 static u8 bytes[2048];UINTN size=sizeof(bytes);EFI_STATUS status=file->Read(file,&size,bytes);file->Close(file);
 if(status){out(st,(CHAR16*)L"Nao foi possivel ler Moon.txt.\r\n");st->ConOut->SetAttribute(st->ConOut,0x07);return 1;}
 static CHAR16 text[2048];UINTN used=0,lines=0;
 for(UINTN i=0;i<size&&used+2<sizeof(text)/sizeof(text[0]);){
  u32 cp;u8 a=bytes[i++];
  if(a<0x80)cp=a;
  else if((a&0xe0)==0xc0&&i<size){cp=((u32)(a&0x1f)<<6)|(bytes[i++]&0x3f);}
  else if((a&0xf0)==0xe0&&i+1<size){cp=((u32)(a&0x0f)<<12)|((u32)(bytes[i]&0x3f)<<6)|(bytes[i+1]&0x3f);i+=2;}
  else if((a&0xf8)==0xf0&&i+2<size){i+=3;cp='?';}
  else cp='?';
  if(cp=='\r')continue;
  if(cp=='\n'){text[used++]='\r';text[used++]='\n';lines++;continue;}
  text[used++]=(CHAR16)(cp<=0xffff?cp:'?');
 }
 if(!used||text[used-1]!='\n'){text[used++]='\r';text[used++]='\n';lines++;}
 text[used]=0;out(st,text);st->ConOut->SetAttribute(st->ConOut,0x07);return lines;
}

static u64 memory_mib(EFI_SYSTEM_TABLE *st){
 void **bs=(void**)st->BootServices;
 EFI_STATUS (__attribute__((ms_abi)) *get_map)(UINTN*,void*,UINTN*,UINTN*,u32*)=bs[3+4];
 EFI_STATUS (__attribute__((ms_abi)) *allocate)(u32,UINTN,void**)=bs[3+5];
 EFI_STATUS (__attribute__((ms_abi)) *release)(void*)=bs[3+6];
 UINTN size=0,key=0,descriptor_size=0;u32 version=0;
 EFI_STATUS status=get_map(&size,0,&key,&descriptor_size,&version);
 if(status!=0x8000000000000005ULL||!descriptor_size)return 0;
 void *map=0;if(allocate(2,size+descriptor_size*2,&map))return 0;
 size+=descriptor_size*2;status=get_map(&size,map,&key,&descriptor_size,&version);
 u64 pages=0;
 if(!status)for(UINTN offset=0;offset+40<=size;offset+=descriptor_size){u8 *d=(u8*)map+offset;u32 type=*(u32*)d;u64 count=*(u64*)(d+24);if((type>=1&&type<=7)||type==9||type==10||type==14)pages+=count;}
 release(map);return (pages*4096)/(1024*1024);
}
static void put(const char *s){ while(*s) report[pos++]=*s++; }
static void hex32(u32 x){ const char *h="0123456789ABCDEF"; for(int i=7;i>=0;i--) report[pos++]=h[(x>>(i*4))&15]; }
static void put_dec(u64 n){char digits[20];int count=0;if(!n){report[pos++]='0';return;}while(n&&count<20){digits[count++]=(char)('0'+n%10);n/=10;}while(count)report[pos++]=digits[--count];}
static u32 cpuid(u32 leaf,u32 sub,u32 *b,u32 *c,u32 *d){u32 a=leaf; __asm__ volatile("cpuid":"+a"(a),"=b"(*b),"=c"(*c),"=d"(*d):"c"(sub)); return a;}
static EFI_STATUS find_log_volume(EFI_SYSTEM_TABLE *st, EFI_FILE **result){
 void **bs=(void**)st->BootServices;
 EFI_STATUS (__attribute__((ms_abi)) *locate_handles)(u32,EFI_GUID*,void*,UINTN*,EFI_HANDLE**)=bs[3+36];
 EFI_STATUS (__attribute__((ms_abi)) *handle_protocol)(EFI_HANDLE,EFI_GUID*,void**)=bs[3+16];
 EFI_STATUS (__attribute__((ms_abi)) *free_pool)(void*)=bs[3+6];
 UINTN count=0; EFI_HANDLE *handles=0;
 EFI_STATUS status=locate_handles(2,&fs_guid,0,&count,&handles);
 if(status)return status;
 *result=0;
 static CHAR16 marker_name[]={'U','N','I','O','S','.','T','A','G',0};
 for(UINTN i=0;i<count;i++){
  EFI_SIMPLE_FS *fs=0; EFI_FILE *root=0,*marker=0;
  status=handle_protocol(handles[i],&fs_guid,(void**)&fs);
  if(status)continue;
  status=fs->OpenVolume(fs,&root);
  if(status)continue;
  status=root->Open(root,&marker,marker_name,1,0);
  if(!status){
   marker->Close(marker); free_pool(handles); *result=root; return 0;
  }
  root->Close(root);
 }
 free_pool(handles);
 return 0x800000000000000eULL;
}
static int contains_folded(const u16 *s, const char *needle){
 for(;*s;s++){
  const u16 *a=s; const char *b=needle;
  while(*b && *a){u16 c=*a; char d=*b; if(c>='A'&&c<='Z')c+=32; if(d>='A'&&d<='Z')d+=32; if(c!=(u16)d)break; a++; b++;}
  if(!*b)return 1;
 }
 return 0;
}
static int find_return_boot_option(EFI_SYSTEM_TABLE *st, u16 *selected){
 void **rt=(void**)st->RuntimeServices;
 EFI_STATUS (__attribute__((ms_abi)) *getvar)(CHAR16*,EFI_GUID*,u32*,UINTN*,void*)=rt[3+6];
 EFI_STATUS (__attribute__((ms_abi)) *setvar)(CHAR16*,EFI_GUID*,u32,UINTN,void*)=rt[3+8];
 static CHAR16 order_name[]={'B','o','o','t','O','r','d','e','r',0};
 u16 order[128]; UINTN bytes=sizeof(order); u32 attrs=0;
 if(getvar(order_name,&global_guid,&attrs,&bytes,order) || bytes>sizeof(order) || bytes%2)return 0;
 UINTN count=bytes/2; u16 found=0; static const char hex[]="0123456789ABCDEF";
 for(int pass=0;pass<3 && !found;pass++)for(UINTN i=0;i<count;i++){
  u16 id=order[i]; u16 option_name[]={'B','o','o','t','0','0','0','0',0};
  option_name[4]=hex[(id>>12)&15]; option_name[5]=hex[(id>>8)&15]; option_name[6]=hex[(id>>4)&15]; option_name[7]=hex[id&15];
  u8 data[2048]; UINTN size=sizeof(data); attrs=0;
  if(getvar(option_name,&global_guid,&attrs,&size,data) || size<8 || size>sizeof(data))continue;
  u16 *description=(u16*)(data+6); UINTN max=(size-6)/2; int terminated=0;
  for(UINTN j=0;j<max;j++)if(!description[j]){terminated=1;break;}
  if(!terminated)continue;
  if((pass==0 && contains_folded(description,"refind")) ||
     (pass==1 && contains_folded(description,"cachyos")) ||
     (pass==2 && contains_folded(description,"linux boot manager"))){found=id;break;}
 }
 if(!found)return 0;
 static CHAR16 next_name[]={'B','o','o','t','N','e','x','t',0};
 if(setvar(next_name,&global_guid,7,sizeof(found),&found))return 0;
 *selected=found; return 1;
}
static void finish_to_os(EFI_SYSTEM_TABLE *st, int has_target){
 EFI_STATUS (__attribute__((ms_abi)) *reset)(u32,EFI_STATUS,UINTN,void*)=((void**)st->RuntimeServices)[3+10];
 st->ConOut->OutputString(st->ConOut,(CHAR16*)L"\r\nEncerrando o UniOS...\r\n");
 if(has_target)reset(1,0,0,0); /* BootNext aponta para rEFInd/CachyOS. */
 reset(2,0,0,0); /* Sem entrada conhecida: desligar para evitar ciclo no USB. */
}
#define OUT(s) st->ConOut->OutputString(st->ConOut,(CHAR16*)L##s)
static void read_field(EFI_SYSTEM_TABLE *st,const CHAR16 *prompt,CHAR16 *buffer,UINTN capacity,int secret){
 out(st,prompt);UINTN length=0;EFI_TEXT_IN *in=st->ConIn;EFI_INPUT_KEY key;UINTN index=0;void *event=in->WaitForKey;
 EFI_STATUS (__attribute__((ms_abi)) *wait)(UINTN,void**,UINTN*)=((void**)st->BootServices)[3+9];
 for(;;){if(wait(1,&event,&index)||in->ReadKeyStroke(in,&key))continue;
  if(key.UnicodeChar==13){buffer[length]=0;out(st,(CHAR16*)L"\r\n");return;}
  if(key.UnicodeChar==8){if(length){length--;buffer[length]=0;out(st,(CHAR16*)L"\b \b");}continue;}
  if(key.UnicodeChar>=32&&key.UnicodeChar<127&&length+1<capacity){buffer[length++]=key.UnicodeChar;buffer[length]=0;CHAR16 echo[2]={(CHAR16)(secret?'*':key.UnicodeChar),0};out(st,echo);}
 }
}
static int save_profile(EFI_FILE *root,CHAR16 *name,CHAR16 *user){
 char text[256]="Nome=";UINTN p=5;
 for(UINTN i=0;name[i]&&p<120;i++)text[p++]=(char)name[i];
 const char *middle="\r\nUsuario=";while(*middle)text[p++]=*middle++;
 for(UINTN i=0;user[i]&&p<160;i++)text[p++]=(char)user[i];
 const char *tail="\r\nConta=UniOS local\r\n";while(*tail)text[p++]=*tail++;
 static CHAR16 path[]={'U','N','I','O','S','\\','P','R','O','F','I','L','E','.','T','X','T',0};EFI_FILE *f=0;
 if(root->Open(root,&f,path,0x8000000000000003ULL,0x20ULL))return 0;
 UINTN n=p;EFI_STATUS status=f->Write(f,&n,text);f->Flush(f);f->Close(f);return !status&&n==p;
}
static int hex_digit(char c){if(c>='0'&&c<='9')return c-'0';if(c>='a'&&c<='f')return c-'a'+10;if(c>='A'&&c<='F')return c-'A'+10;return -1;}
static char hex_char(u8 n){return "0123456789abcdef"[n&15];}
static const char *field_value(const char *data,const char *key){UINTN k=0;while(key[k])k++;for(const char *p=data;*p;p++){if((p==data||p[-1]=='\n')){UINTN i=0;while(i<k&&p[i]==key[i])i++;if(i==k)return p+k;}}return 0;}
static int decode_hex(const char *value,u8 *output,UINTN bytes){for(UINTN i=0;i<bytes;i++){int hi=hex_digit(value[i*2]),lo=hex_digit(value[i*2+1]);if(hi<0||lo<0)return 0;output[i]=(u8)((hi<<4)|lo);}return value[bytes*2]=='\r'||value[bytes*2]=='\n'||value[bytes*2]==0;}
static int save_auth(EFI_FILE *root){
 static char text[192];UINTN n=0;const char *a="Algorithm=PBKDF2-SHA256\r\nIterations=100000\r\nSalt=";while(*a)text[n++]=*a++;
 for(int i=0;i<16;i++){text[n++]=hex_char(auth_salt[i]>>4);text[n++]=hex_char(auth_salt[i]);}
 a="\r\nHash=";while(*a)text[n++]=*a++;for(int i=0;i<32;i++){text[n++]=hex_char(auth_hash[i]>>4);text[n++]=hex_char(auth_hash[i]);}text[n++]='\r';text[n++]='\n';
 static CHAR16 path[]={'U','N','I','O','S','\\','A','U','T','H','.','T','X','T',0};EFI_FILE *file=0;
 if(root->Open(root,&file,path,0x8000000000000003ULL,0x20ULL))return 0;
 UINTN written=n;EFI_STATUS status=file->Write(file,&written,text);file->Flush(file);file->Close(file);return !status&&written==n;
}
static int load_auth(EFI_FILE *root){
 static CHAR16 path[]={'U','N','I','O','S','\\','A','U','T','H','.','T','X','T',0};EFI_FILE *file=0;
 if(root->Open(root,&file,path,1,0))return 0;
 static char data[256];UINTN n=sizeof(data)-1;EFI_STATUS status=file->Read(file,&n,data);file->Close(file);if(status||n>=sizeof(data))return -1;data[n]=0;
 const char *iterations=field_value(data,"Iterations="),*salt=field_value(data,"Salt="),*hash=field_value(data,"Hash=");if(!iterations||!salt||!hash)return 0;
 u32 rounds=0;while(*iterations>='0'&&*iterations<='9'){rounds=rounds*10+(u32)(*iterations++-'0');if(rounds>500000)return -1;}if(rounds!=AUTH_ITERATIONS)return -1;
 if(!decode_hex(salt,auth_salt,16)||!decode_hex(hash,auth_hash,32))return -1;auth_loaded=1;return 1;
}
static int set_auth(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const CHAR16 *password){
 u8 bytes[64];UINTN length=0;if(!password_bytes(password,bytes,&length))return 0;
 make_salt(st,auth_salt);pbkdf2_sha256(bytes,length,auth_salt,AUTH_ITERATIONS,auth_hash);auth_loaded=1;
 for(UINTN i=0;i<sizeof(bytes);i++)bytes[i]=0;
 return save_auth(root);
}
static int verify_auth(EFI_SYSTEM_TABLE *st,const CHAR16 *password){
 u8 bytes[64],derived[32];UINTN length=0;if(!auth_loaded||!password_bytes(password,bytes,&length))return 0;
 pbkdf2_sha256(bytes,length,auth_salt,AUTH_ITERATIONS,derived);for(UINTN i=0;i<sizeof(bytes);i++)bytes[i]=0;
 return constant_equal(derived,auth_hash,32);
}
static int profile_exists(EFI_FILE *root){
 static CHAR16 path[]={'U','N','I','O','S','\\','P','R','O','F','I','L','E','.','T','X','T',0};EFI_FILE *f=0;
 if(root->Open(root,&f,path,1,0))return 0;f->Close(f);return 1;
}
static int load_profile_user(EFI_FILE *root,CHAR16 *user,UINTN capacity){
 static CHAR16 path[]={'U','N','I','O','S','\\','P','R','O','F','I','L','E','.','T','X','T',0};EFI_FILE *f=0;
 if(root->Open(root,&f,path,1,0))return 0;
 char data[256];UINTN n=sizeof(data)-1;EFI_STATUS status=f->Read(f,&n,data);f->Close(f);if(status)return 0;data[n]=0;
 const char *key="Usuario=";char *at=data;
 while(*at){const char *a=at,*b=key;while(*b&&*a==*b){a++;b++;}if(!*b){at=(char*)a;break;}at++;}
 if(!*at)return 0;UINTN i=0;while(at[i]&&at[i]!='\r'&&at[i]!='\n'&&i+1<capacity){user[i]=(u8)at[i];i++;}user[i]=0;return i>0;
}
static int password_matches(CHAR16 *a,CHAR16 *b){UINTN i=0;while(a[i]&&b[i]&&a[i]==b[i])i++;return a[i]==0&&b[i]==0;}
static int set_password_interactive(EFI_SYSTEM_TABLE *st,EFI_FILE *root){
 CHAR16 first[64]={0},confirm[64]={0};
 for(;;){read_field(st,(CHAR16*)L"Nova senha (minimo 6 caracteres): ",first,64,1);
  UINTN n=0;while(first[n])n++;if(n<6){OUT("Use pelo menos 6 caracteres.\r\n");continue;}
  read_field(st,(CHAR16*)L"Confirme a senha: ",confirm,64,1);if(!password_matches(first,confirm)){OUT("As senhas nao conferem. Tente novamente.\r\n");for(UINTN i=0;i<64;i++)first[i]=confirm[i]=0;continue;}
  OUT("Calculando hash da senha...\r\n");
  int stored=set_auth(st,root,first);for(UINTN i=0;i<64;i++)first[i]=confirm[i]=0;
  if(stored)OUT("Hash da senha salvo em UNIOS\\AUTH.TXT.\r\n");else OUT("Senha ativa nesta sessao; a midia nao permitiu salvar o hash.\r\n");return 1;
 }
}
static int authenticate_user(EFI_SYSTEM_TABLE *st){
 CHAR16 password[64];for(int attempt=0;attempt<3;attempt++){
  read_field(st,(CHAR16*)L"Senha: ",password,64,1);OUT("Verificando senha...\r\n");int valid=verify_auth(st,password);for(UINTN i=0;i<64;i++)password[i]=0;
  if(valid){OUT("Acesso autorizado.\r\n");return 1;}OUT("Senha incorreta.\r\n");
 }
 return 0;
}
static int profile_wizard(EFI_SYSTEM_TABLE *st,EFI_FILE *root,CHAR16 *shell_user,UINTN shell_user_size){
 if(profile_exists(root)){
  if(!load_profile_user(root,shell_user,shell_user_size)){const CHAR16 fallback[]=L"usuario";for(UINTN i=0;i<sizeof(fallback)/2;i++)shell_user[i]=fallback[i];}
  int state=load_auth(root);
  if(state>0){OUT("Login UniOS\r\n");return authenticate_user(st);}
  if(state<0){OUT("AUTH.TXT invalido; acesso bloqueado.\r\n");return 0;}
  OUT("Perfil antigo sem hash de senha. Configure uma senha nova.\r\n");return set_password_interactive(st,root);
 }
 CHAR16 name[64]={0},user[32]={0};OUT("Primeira configuracao do perfil UniOS\r\n");
 read_field(st,(CHAR16*)L"Nome: ",name,64,0);read_field(st,(CHAR16*)L"Usuario: ",user,32,0);
 UINTN i=0;while(user[i]&&i+1<shell_user_size){shell_user[i]=user[i];i++;}shell_user[i]=0;
 if(save_profile(root,name,user))OUT("Perfil salvo em UNIOS\\PROFILE.TXT.\r\n");else OUT("Perfil desta sessao nao sera salvo na midia somente leitura.\r\n");
 return set_password_interactive(st,root);
}
static void show_info(EFI_SYSTEM_TABLE *st){CHAR16 text[800];for(UINTN i=0;i<pos;i++)text[i]=(u8)report[i];text[pos]=0;out(st,text);}
static int command_is(const char *command,const char *wanted){while(*command&&*wanted&&*command==*wanted){command++;wanted++;}return !*command&&!*wanted;}
static int resolve_path(const char *cwd,const char *arg,char *result,UINTN capacity){
 char joined[256];UINTN used=0;
 if(arg[0]!='/'&&arg[0]!='\\'){for(UINTN i=0;cwd[i]&&used+2<sizeof(joined);i++)joined[used++]=cwd[i];if(used)joined[used++]='\\';}
 for(UINTN i=0;arg[i]&&used+1<sizeof(joined);i++)joined[used++]=(arg[i]=='/')?'\\':arg[i];joined[used]=0;
 char normalized[128];UINTN n=0,i=0;
 while(joined[i]){
  while(joined[i]=='\\')i++;
  if(!joined[i])break;
  char part[64];UINTN len=0;
  while(joined[i]&&joined[i]!='\\'){if(len+1>=sizeof(part))return 0;part[len++]=joined[i++];}part[len]=0;
  if(len==1&&part[0]=='.')continue;
  if(len==2&&part[0]=='.'&&part[1]=='.'){if(n){while(n&&normalized[n-1]!='\\')n--;if(n)n--;}continue;}
  if(n){if(n+1>=sizeof(normalized))return 0;normalized[n++]='\\';}
  if(n+len>=sizeof(normalized))return 0;for(UINTN j=0;j<len;j++)normalized[n++]=part[j];
 }
 if(n+1>capacity)return 0;for(UINTN j=0;j<n;j++)result[j]=normalized[j];result[n]=0;return 1;
}
static void path_to_efi(const char *path,CHAR16 *wide){UINTN i=0;while(path[i]){wide[i]=(path[i]=='/')?'\\':(u8)path[i];i++;}wide[i]=0;}
static int is_directory(EFI_FILE *file){
 static u64 info[128];UINTN size=sizeof(info);
 if(file->GetInfo(file,&file_info_guid,&size,info)||size<80)return 0;
 return (*(u64*)((u8*)info+72)&0x10)!=0;
}
static void prompt(EFI_SYSTEM_TABLE *st,CHAR16 *user,const char *cwd){
 st->ConOut->SetAttribute(st->ConOut,0x0a);out(st,user);
 st->ConOut->SetAttribute(st->ConOut,0x0b);out(st,(CHAR16*)L"@UniOS:");
 if(!cwd[0])out(st,(CHAR16*)L"~");
 else{
  out(st,(CHAR16*)L"~/");CHAR16 path[128];UINTN i=0;
  while(cwd[i]&&i+1<sizeof(path)/sizeof(path[0])){path[i]=(cwd[i]=='\\')?'/':(u8)cwd[i];i++;}
  path[i]=0;out(st,path);
 }
 st->ConOut->SetAttribute(st->ConOut,0x0a);out(st,(CHAR16*)L"$ ");
 st->ConOut->SetAttribute(st->ConOut,0x07);
}
static void command_help(EFI_SYSTEM_TABLE *st){
 out(st,(CHAR16*)L"Comandos UniOS (27):\r\n");
 out(st,(CHAR16*)L"  help          mostra esta ajuda\r\n  info          informacoes do computador\r\n  ls [caminho]  lista arquivos e pastas\r\n  cd [caminho]  muda de pasta; cd / volta a raiz\r\n  pwd           mostra a pasta atual\r\n  mkdir [-p] <nome> cria pastas\r\n  cat <arquivo> mostra o conteudo de um arquivo\r\n  touch <nome>  cria um arquivo vazio\r\n  clear         limpa a tela\r\n  echo <texto>  mostra texto\r\n  whoami        mostra o usuario\r\n  uname         mostra UniOS e arquitetura\r\n  date          mostra data e hora do firmware\r\n  uptime        tempo desde o boot\r\n  free          memoria visivel no mapa UEFI\r\n  cpuinfo       detalhes do processador\r\n  meminfo       mapa de memoria UEFI\r\n  lsblk         lista dispositivos de bloco UEFI\r\n  lsusb         lista dispositivos USB UEFI\r\n  df            espaco do volume UNIOS\r\n  history       comandos recentes\r\n  stat <caminho> tipo e tamanho\r\n  wc <arquivo>  linhas, palavras e bytes\r\n  head <arquivo> primeiras dez linhas\r\n  tail <arquivo> ultimas dez linhas\r\n  sudo <comando> autentica e executa operacoes administrativas\r\n    sudo passwd|mkdir|touch|rm|rmdir|cp|mv|write|append|truncate\r\n    sudo clearlog|reboot|poweroff|info|ls|cat|stat|wc|head|tail\r\n    sudo lsblk|lsusb|df|cpuinfo|meminfo\r\n  exit          encerra o UniOS\r\n");
}
static void output_dec(EFI_SYSTEM_TABLE *st,u64 value){CHAR16 text[24];UINTN n=0;if(!value)text[n++]='0';while(value&&n<22){text[n++]=(CHAR16)('0'+value%10);value/=10;}for(UINTN i=0;i<n/2;i++){CHAR16 t=text[i];text[i]=text[n-1-i];text[n-1-i]=t;}text[n]=0;out(st,text);}
static void output_hex16(EFI_SYSTEM_TABLE *st,u16 value){static const CHAR16 h[]=L"0123456789abcdef";CHAR16 text[5];for(int i=0;i<4;i++)text[i]=h[(value>>((3-i)*4))&15];text[4]=0;out(st,text);}
static EFI_STATUS locate_handles(EFI_SYSTEM_TABLE *st,EFI_GUID *guid,EFI_HANDLE **handles,UINTN *count){EFI_STATUS (__attribute__((ms_abi)) *locate)(u32,EFI_GUID*,void*,UINTN*,EFI_HANDLE**)=((void**)st->BootServices)[3+36];return locate(2,guid,0,count,handles);}
static void command_lsblk(EFI_SYSTEM_TABLE *st){
 EFI_HANDLE *handles=0;UINTN count=0;EFI_STATUS status=locate_handles(st,&block_guid,&handles,&count);if(status){out(st,(CHAR16*)L"Nenhum dispositivo de bloco UEFI encontrado.\r\n");return;}
 EFI_STATUS (__attribute__((ms_abi)) *hp)(EFI_HANDLE,EFI_GUID*,void**)=((void**)st->BootServices)[3+16];EFI_STATUS (__attribute__((ms_abi)) *free_pool)(void*)=((void**)st->BootServices)[3+6];UINTN shown=0;
 out(st,(CHAR16*)L"DISPOSITIVO   TAMANHO MiB   BLOCO   ESTADO\r\n");
 for(UINTN i=0;i<count;i++){EFI_BLOCK_IO *io=0;if(hp(handles[i],&block_guid,(void**)&io)||!io||!io->Media||!io->Media->MediaPresent)continue;
  shown++;out(st,(CHAR16*)L"uefi-block");output_dec(st,shown);out(st,(CHAR16*)L"       ");output_dec(st,((io->Media->LastBlock+1)*(u64)io->Media->BlockSize)/(1024*1024));out(st,(CHAR16*)L"         ");output_dec(st,io->Media->BlockSize);out(st,(CHAR16*)L"   ");out(st,io->Media->ReadOnly?(CHAR16*)L"somente leitura\r\n":(CHAR16*)L"gravavel\r\n");
 }
 if(!shown)out(st,(CHAR16*)L"Nenhuma midia presente.\r\n");if(handles)free_pool(handles);
}
static void command_lsusb(EFI_SYSTEM_TABLE *st){
 EFI_HANDLE *handles=0;UINTN count=0;EFI_STATUS status=locate_handles(st,&usb_guid,&handles,&count);if(status){out(st,(CHAR16*)L"Nenhum dispositivo USB UEFI encontrado.\r\n");return;}
 EFI_STATUS (__attribute__((ms_abi)) *hp)(EFI_HANDLE,EFI_GUID*,void**)=((void**)st->BootServices)[3+16];EFI_STATUS (__attribute__((ms_abi)) *free_pool)(void*)=((void**)st->BootServices)[3+6];UINTN shown=0;
 out(st,(CHAR16*)L"BUS  DISPOSITIVO  ID VENDOR:PRODUCT\r\n");
 for(UINTN i=0;i<count;i++){EFI_USB_IO *io=0;EFI_USB_DEVICE_DESC d;if(hp(handles[i],&usb_guid,(void**)&io)||!io||io->GetDeviceDescriptor(io,&d))continue;shown++;out(st,(CHAR16*)L"001  ");output_dec(st,shown);out(st,(CHAR16*)L"            ");output_hex16(st,d.IdVendor);out(st,(CHAR16*)L":");output_hex16(st,d.IdProduct);out(st,(CHAR16*)L"\r\n");}
 if(!shown)out(st,(CHAR16*)L"Nenhum USB enumerado pelo firmware.\r\n");if(handles)free_pool(handles);
}
static void command_date(EFI_SYSTEM_TABLE *st){EFI_TIME t={0};EFI_STATUS (__attribute__((ms_abi)) *get_time)(EFI_TIME*,void*)=((void**)st->RuntimeServices)[3];if(get_time(&t,0)){out(st,(CHAR16*)L"Relogio UEFI indisponivel.\r\n");return;}output_dec(st,t.Year);out(st,(CHAR16*)L"-");if(t.Month<10)out(st,(CHAR16*)L"0");output_dec(st,t.Month);out(st,(CHAR16*)L"-");if(t.Day<10)out(st,(CHAR16*)L"0");output_dec(st,t.Day);out(st,(CHAR16*)L" ");if(t.Hour<10)out(st,(CHAR16*)L"0");output_dec(st,t.Hour);out(st,(CHAR16*)L":");if(t.Minute<10)out(st,(CHAR16*)L"0");output_dec(st,t.Minute);out(st,(CHAR16*)L":");if(t.Second<10)out(st,(CHAR16*)L"0");output_dec(st,t.Second);out(st,(CHAR16*)L"\r\n");}
static u64 epoch_seconds(EFI_TIME *t){u64 days=0;for(u32 y=1970;y<t->Year;y++)days+=((y%4==0&&y%100!=0)||y%400==0)?366:365;static const u8 month_days[12]={31,28,31,30,31,30,31,31,30,31,30,31};for(u32 m=1;m<t->Month&&m<=12;m++){days+=month_days[m-1];if(m==2&&((t->Year%4==0&&t->Year%100!=0)||t->Year%400==0))days++;}if(t->Day)days+=t->Day-1;return (((days*24+t->Hour)*60+t->Minute)*60+t->Second);}
static void command_uptime(EFI_SYSTEM_TABLE *st){EFI_TIME t={0};EFI_STATUS (__attribute__((ms_abi)) *get_time)(EFI_TIME*,void*)=((void**)st->RuntimeServices)[3];if(!boot_epoch||get_time(&t,0)){out(st,(CHAR16*)L"Uptime indisponivel.\r\n");return;}u64 now=epoch_seconds(&t),sec=now>=boot_epoch?now-boot_epoch:0;output_dec(st,sec/86400);out(st,(CHAR16*)L" dias, ");output_dec(st,(sec/3600)%24);out(st,(CHAR16*)L" horas, ");output_dec(st,(sec/60)%60);out(st,(CHAR16*)L" minutos\r\n");}
static void command_free(EFI_SYSTEM_TABLE *st,int detailed){if(detailed)out(st,(CHAR16*)L"Mapa de memoria UEFI: ");else out(st,(CHAR16*)L"RAM visivel no mapa UEFI: ");output_dec(st,memory_total_mib);out(st,(CHAR16*)L" MiB\r\n");}
static void command_cpuinfo(EFI_SYSTEM_TABLE *st){out(st,(CHAR16*)L"Processador: ");CHAR16 text[50];for(int i=0;i<48;i++)text[i]=(u8)cpu_brand[i];text[48]=0;out(st,text);out(st,(CHAR16*)L"\r\nNucleos fisicos: ");output_dec(st,cpu_cores);out(st,(CHAR16*)L"\r\nArquitetura: x86_64 UEFI\r\n");}
static void command_history(EFI_SYSTEM_TABLE *st){UINTN start=shell_history_count>16?shell_history_count-16:0;for(UINTN i=start;i<shell_history_count;i++){output_dec(st,i+1);out(st,(CHAR16*)L"  ");CHAR16 line[160];UINTN n=0;const char *src=shell_history[i%16];while(src[n]&&n+1<160){line[n]=(u8)src[n];n++;}line[n]=0;out(st,line);out(st,(CHAR16*)L"\r\n");}}
static int resolve_open_file(EFI_FILE *root,const char *cwd,const char *arg,EFI_FILE **file){char path[128];if(!resolve_path(cwd,arg,path,sizeof(path)))return 0;if(!path[0])return 0;CHAR16 wide[128];path_to_efi(path,wide);return !root->Open(root,file,wide,1,0);}
static void command_stat(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *arg){EFI_FILE *f=root;if(arg[0]&&!resolve_open_file(root,cwd,arg,&f)){out(st,(CHAR16*)L"Arquivo ou pasta nao encontrado.\r\n");return;}static u64 info[128];UINTN size=sizeof(info);if(f->GetInfo(f,&file_info_guid,&size,info)||size<80){out(st,(CHAR16*)L"Informacoes indisponiveis.\r\n");if(f!=root)f->Close(f);return;}u64 bytes=*(u64*)((u8*)info+8),attrs=*(u64*)((u8*)info+72);out(st,(CHAR16*)L"Tipo: ");out(st,(attrs&0x10)?(CHAR16*)L"pasta\r\n":(CHAR16*)L"arquivo\r\n");out(st,(CHAR16*)L"Tamanho: ");output_dec(st,bytes);out(st,(CHAR16*)L" bytes\r\n");if(f!=root)f->Close(f);}
static void command_wc(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *arg){EFI_FILE *f=0;if(!resolve_open_file(root,cwd,arg,&f)){out(st,(CHAR16*)L"Arquivo nao encontrado.\r\n");return;}static u8 buf[256];u64 bytes=0,lines=0,words=0;int inword=0;for(;;){UINTN n=sizeof(buf);EFI_STATUS status=f->Read(f,&n,buf);if(status||!n)break;bytes+=n;for(UINTN i=0;i<n;i++){if(buf[i]=='\n')lines++;if(buf[i]==' '||buf[i]=='\r'||buf[i]=='\n'||buf[i]=='\t')inword=0;else if(!inword){words++;inword=1;}}}f->Close(f);output_dec(st,lines);out(st,(CHAR16*)L" linhas  ");output_dec(st,words);out(st,(CHAR16*)L" palavras  ");output_dec(st,bytes);out(st,(CHAR16*)L" bytes\r\n");}
static void command_head_tail(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *arg,int tail){EFI_FILE *f=0;if(!resolve_open_file(root,cwd,arg,&f)){out(st,(CHAR16*)L"Arquivo nao encontrado.\r\n");return;}static u8 data[8192];UINTN used=0;while(used<sizeof(data)){UINTN n=sizeof(data)-used;EFI_STATUS status=f->Read(f,&n,data+used);if(status||!n)break;used+=n;}f->Close(f);UINTN begin=0,end=used;if(tail){int lines=0;for(UINTN i=used;i>0;i--)if(data[i-1]=='\n'&&++lines==11){begin=i;break;}}else{int lines=0;for(UINTN i=0;i<used;i++)if(data[i]=='\n'&&++lines==10){end=i+1;break;}}for(UINTN i=begin;i<end;i++){if(data[i]=='\r')continue;CHAR16 c=(data[i]<128)?data[i]:'?';CHAR16 one[2]={c,0};out(st,one);}if(used==sizeof(data))out(st,(CHAR16*)L"\r\n[arquivo limitado a 8 KiB]\r\n");}
static void command_df(EFI_SYSTEM_TABLE *st,EFI_FILE *root){static u64 info[128];UINTN size=sizeof(info);if(root->GetInfo(root,&fs_info_guid,&size,info)||size<36){out(st,(CHAR16*)L"Dados do volume indisponiveis.\r\n");return;}u64 total=*(u64*)((u8*)info+16),free_bytes=*(u64*)((u8*)info+24);out(st,(CHAR16*)L"Volume UNIOS: total ");output_dec(st,total/(1024*1024));out(st,(CHAR16*)L" MiB, livre ");output_dec(st,free_bytes/(1024*1024));out(st,(CHAR16*)L" MiB\r\n");}
static void command_ls(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *arg){
 static u64 entry_buffer[128];static CHAR16 name_line[260];
 char path[128];if(!resolve_path(cwd,arg,path,sizeof(path))){out(st,(CHAR16*)L"Caminho muito longo.\r\n");return;}
 EFI_FILE *dir=root;int close_dir=0;CHAR16 wide[128];
 if(path[0]){path_to_efi(path,wide);if(root->Open(root,&dir,wide,1,0)){out(st,(CHAR16*)L"Pasta nao encontrada.\r\n");return;}close_dir=1;if(!is_directory(dir)){dir->Close(dir);out(st,(CHAR16*)L"O caminho nao e uma pasta.\r\n");return;}}
 for(;;){UINTN bytes=sizeof(entry_buffer);EFI_STATUS status=dir->Read(dir,&bytes,entry_buffer);if(status||!bytes)break;if(bytes<82)continue;
  u8 *entry=(u8*)entry_buffer;u64 attrs=*(u64*)(entry+72);CHAR16 *name=(CHAR16*)(entry+80);UINTN i=0;
  while(name[i]&&i+2<sizeof(name_line)/sizeof(name_line[0])){name_line[i]=name[i];i++;}
  if(!i)continue;
  if((i==1&&name[0]=='.')||(i==2&&name[0]=='.'&&name[1]=='.'))continue;
  if(attrs&0x10){name_line[i++]='/';name_line[i]=0;st->ConOut->SetAttribute(st->ConOut,0x0b);}else{ name_line[i]=0;st->ConOut->SetAttribute(st->ConOut,0x07); }
  out(st,name_line);out(st,(CHAR16*)L"\r\n");
 }
 st->ConOut->SetAttribute(st->ConOut,0x07);if(close_dir)dir->Close(dir);
}
static void command_mkdir(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *arg,int parents){
 if(!arg[0]){out(st,(CHAR16*)L"Informe o nome da pasta.\r\n");return;}
 char path[128];if(!resolve_path(cwd,arg,path,sizeof(path))||!path[0]){out(st,(CHAR16*)L"Caminho invalido ou muito longo.\r\n");return;}
 if(!parents){CHAR16 wide[128];path_to_efi(path,wide);EFI_FILE *dir=0;
  if(root->Open(root,&dir,wide,0x8000000000000003ULL,0x10ULL)){out(st,(CHAR16*)L"Falha ao criar a pasta. A midia pode ser somente leitura ou o nome ja existe.\r\n");return;}
  dir->Close(dir);return;
 }
 for(UINTN i=0;;i++)if(path[i]=='\\'||path[i]==0){
  char saved=path[i];path[i]=0;CHAR16 wide[128];path_to_efi(path,wide);EFI_FILE *dir=0;
  EFI_STATUS status=root->Open(root,&dir,wide,1,0);
  if(!status){int valid=is_directory(dir);dir->Close(dir);if(!valid){path[i]=saved;out(st,(CHAR16*)L"Um componente do caminho nao e uma pasta.\r\n");return;}}
  else{
   status=root->Open(root,&dir,wide,0x8000000000000003ULL,0x10ULL);
   if(status){path[i]=saved;out(st,(CHAR16*)L"Falha ao criar a pasta. A midia pode ser somente leitura.\r\n");return;}
   dir->Close(dir);
  }
  path[i]=saved;if(!saved)break;
 }
}

static void command_file(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *arg,int create_file){
 if(!arg[0]){out(st,(CHAR16*)L"Informe um nome ou caminho.\r\n");return;}
 char path[128];CHAR16 wide[128];if(!resolve_path(cwd,arg,path,sizeof(path))||!path[0]){out(st,(CHAR16*)L"Caminho invalido ou muito longo.\r\n");return;}path_to_efi(path,wide);
 EFI_FILE *file=0;u64 mode=create_file?0x8000000000000003ULL:1ULL;
 EFI_STATUS status=root->Open(root,&file,wide,mode,0);
 if(status){out(st,(CHAR16*)L"Falha ao acessar o caminho. A midia pode ser somente leitura.\r\n");return;}
 if(!create_file){
  static u8 bytes[256];static CHAR16 text[258];
  for(;;){UINTN count=sizeof(bytes);status=file->Read(file,&count,bytes);if(status||!count)break;UINTN n=0;
   for(UINTN i=0;i<count&&n+2<sizeof(text)/sizeof(text[0]);i++){u8 c=bytes[i];if(c=='\r')continue;if(c=='\n'){text[n++]='\r';text[n++]='\n';}else text[n++]=(c<128)?c:'?';}
   text[n]=0;out(st,text);
  }
  if(status)out(st,(CHAR16*)L"Erro durante a leitura.\r\n");
 }
 file->Close(file);
}
static int open_path(EFI_FILE *root,const char *cwd,const char *arg,CHAR16 wide[128]){char path[128];if(!resolve_path(cwd,arg,path,sizeof(path))||!path[0])return 0;path_to_efi(path,wide);return 1;}
static int admin_remove(EFI_FILE *root,const char *cwd,const char *arg,int want_dir){CHAR16 path[128];if(!open_path(root,cwd,arg,path))return 0;EFI_FILE *file=0;if(root->Open(root,&file,path,3,0))return 0;int isdir=is_directory(file);if(isdir!=want_dir){file->Close(file);return 0;}return !file->Delete(file);}
static int admin_copy(EFI_FILE *root,const char *cwd,const char *source,const char *destination){CHAR16 src[128],dst[128];if(!open_path(root,cwd,source,src)||!open_path(root,cwd,destination,dst))return 0;EFI_FILE *in=0,*outf=0;if(root->Open(root,&in,src,1,0))return 0;EFI_FILE *old=0;if(!root->Open(root,&old,dst,3,0))old->Delete(old);if(root->Open(root,&outf,dst,0x8000000000000003ULL,0)){in->Close(in);return 0;}static u8 bytes[512];int ok=1;for(;;){UINTN n=sizeof(bytes);EFI_STATUS status=in->Read(in,&n,bytes);if(status||!n)break;UINTN written=n;if(outf->Write(outf,&written,bytes)||written!=n){ok=0;break;}}outf->Flush(outf);outf->Close(outf);in->Close(in);return ok;}
static int admin_write(EFI_FILE *root,const char *cwd,const char *path_arg,const char *content,int append){CHAR16 path[128];if(!open_path(root,cwd,path_arg,path))return 0;EFI_FILE *file=0;EFI_STATUS status=root->Open(root,&file,path,0x8000000000000003ULL,0);if(status&&append)status=root->Open(root,&file,path,0x8000000000000003ULL,0x20ULL);if(status)return 0;if(append)file->SetPosition(file,~0ULL);else file->SetPosition(file,0);UINTN n=0;while(content[n])n++;status=file->Write(file,&n,(void*)content);file->Flush(file);file->Close(file);return !status;}
static void command_sudo(EFI_SYSTEM_TABLE *st,EFI_FILE *root,const char *cwd,const char *input,int has_return){
 char op[24];UINTN n=0;while(input[n]&&input[n]!=' '&&n+1<sizeof(op)){op[n]=input[n];n++;}op[n]=0;const char *arg=input+n;while(*arg==' ')arg++;if(!op[0]){OUT("Uso: sudo <comando>\r\n");return;}
 CHAR16 password[64];read_field(st,(CHAR16*)L"Senha atual para sudo: ",password,64,1);OUT("Verificando senha...\r\n");int valid=verify_auth(st,password);for(UINTN i=0;i<64;i++)password[i]=0;if(!valid){OUT("Senha incorreta.\r\n");return;}
 if(command_is(op,"passwd")){OUT("Acesso administrativo autorizado.\r\n");set_password_interactive(st,root);return;}
 if(command_is(op,"mkdir")){int parents=0;const char *name=arg;if(name[0]=='-'&&name[1]=='p'&&(name[2]==0||name[2]==' ')){parents=1;name+=2;while(*name==' ')name++;}command_mkdir(st,root,cwd,name,parents);return;}
 if(command_is(op,"touch")){command_file(st,root,cwd,arg,1);return;}
 if(command_is(op,"rm")||command_is(op,"rmdir")){if(admin_remove(root,cwd,arg,command_is(op,"rmdir")))return;OUT("Nao foi possivel remover o caminho.\r\n");return;}
 if(command_is(op,"cp")||command_is(op,"mv")){char first[128];UINTN i=0;while(arg[i]&&arg[i]!=' '&&i+1<sizeof(first)){first[i]=arg[i];i++;}first[i]=0;const char *dest=arg+i;while(*dest==' ')dest++;if(!first[0]||!dest[0]){OUT("Uso: sudo cp|mv origem destino\r\n");return;}if(!admin_copy(root,cwd,first,dest)){OUT("Falha ao copiar arquivo.\r\n");return;}if(command_is(op,"mv")&&!admin_remove(root,cwd,first,0)){OUT("Copia criada, mas nao consegui remover a origem.\r\n");return;}return;}
 if(command_is(op,"write")||command_is(op,"append")){char path[128];UINTN i=0;while(arg[i]&&arg[i]!=' '&&i+1<sizeof(path)){path[i]=arg[i];i++;}path[i]=0;const char *text=arg+i;while(*text==' ')text++;if(!path[0]){OUT("Uso: sudo write|append arquivo texto\r\n");return;}if(!admin_write(root,cwd,path,text,command_is(op,"append")))OUT("Falha ao gravar arquivo.\r\n");return;}
 if(command_is(op,"truncate")){if(!admin_remove(root,cwd,arg,0)){OUT("Nao foi possivel esvaziar o arquivo.\r\n");return;}command_file(st,root,cwd,arg,1);return;}
 if(command_is(op,"clearlog")){static const char path[]="UNIOS\\LOG.TXT";if(admin_remove(root,"",path,0))return;OUT("Nao consegui remover LOG.TXT.\r\n");return;}
 if(command_is(op,"reboot")||command_is(op,"poweroff")){EFI_STATUS (__attribute__((ms_abi)) *reset)(u32,EFI_STATUS,UINTN,void*)=((void**)st->RuntimeServices)[3+10];reset(command_is(op,"reboot")?1:2,0,0,0);return;}
 if(command_is(op,"info")){show_info(st);return;}
 if(command_is(op,"ls")){command_ls(st,root,cwd,arg);return;}
 if(command_is(op,"cat")){command_file(st,root,cwd,arg,0);return;}
 if(command_is(op,"stat")){command_stat(st,root,cwd,arg);return;}
 if(command_is(op,"wc")){command_wc(st,root,cwd,arg);return;}
 if(command_is(op,"head")){command_head_tail(st,root,cwd,arg,0);return;}
 if(command_is(op,"tail")){command_head_tail(st,root,cwd,arg,1);return;}
 if(command_is(op,"lsblk")){command_lsblk(st);return;}
 if(command_is(op,"lsusb")){command_lsusb(st);return;}
 if(command_is(op,"df")){command_df(st,root);return;}
 if(command_is(op,"cpuinfo")){command_cpuinfo(st);return;}
 if(command_is(op,"meminfo")){command_free(st,1);return;}
 OUT("Comando sudo ainda nao implementado nesta etapa.\r\n");(void)has_return;
}
static int shell(EFI_SYSTEM_TABLE *st,EFI_FILE *root,CHAR16 *user,int has_return){
 EFI_TEXT_IN *in=st->ConIn;EFI_INPUT_KEY key;UINTN index=0;void *event=in->WaitForKey;
 EFI_STATUS (__attribute__((ms_abi)) *wait)(UINTN,void**,UINTN*)=((void**)st->BootServices)[3+9];
 char command[160],cwd[128]={0};
 for(;;){UINTN length=0;command[0]=0;prompt(st,user,cwd);
  for(;;){if(wait(1,&event,&index)||in->ReadKeyStroke(in,&key))continue;
   if(key.UnicodeChar==13){command[length]=0;out(st,(CHAR16*)L"\r\n");break;}
   if(key.UnicodeChar==8){if(length){length--;command[length]=0;out(st,(CHAR16*)L"\b \b");}continue;}
   if(key.UnicodeChar>=32&&key.UnicodeChar<127&&length+1<sizeof(command)){command[length++]=(char)key.UnicodeChar;command[length]=0;CHAR16 echo[2]={(CHAR16)key.UnicodeChar,0};out(st,echo);}
  }
  if(command[0]){char *dest=shell_history[shell_history_count%16];UINTN h=0;while(command[h]&&h+1<160){dest[h]=command[h];h++;}dest[h]=0;shell_history_count++;}
  char *verb=command;while(*verb==' ')verb++;char *arg=verb;while(*arg&&*arg!=' ')arg++;if(*arg){*arg++=0;while(*arg==' ')arg++;}
  UINTN arglen=0;while(arg[arglen])arglen++;while(arglen&&arg[arglen-1]==' ')arg[--arglen]=0;
  if(command_is(verb,"help")){command_help(st);continue;}
  if(command_is(verb,"sudo")){
   command_sudo(st,root,cwd,arg,has_return);continue;
  }
  if(command_is(verb,"info")){show_info(st);continue;}
  if(command_is(verb,"whoami")){out(st,user);out(st,(CHAR16*)L"\r\n");continue;}
  if(command_is(verb,"uname")){out(st,(CHAR16*)L"UniOS-UEFI 0.2 x86_64\r\n");continue;}
  if(command_is(verb,"date")){command_date(st);continue;}
  if(command_is(verb,"uptime")){command_uptime(st);continue;}
  if(command_is(verb,"free")){command_free(st,0);continue;}
  if(command_is(verb,"meminfo")){command_free(st,1);continue;}
  if(command_is(verb,"cpuinfo")){command_cpuinfo(st);continue;}
  if(command_is(verb,"df")){command_df(st,root);continue;}
  if(command_is(verb,"history")){command_history(st);continue;}
  if(command_is(verb,"stat")){command_stat(st,root,cwd,arg);continue;}
  if(command_is(verb,"wc")){command_wc(st,root,cwd,arg);continue;}
  if(command_is(verb,"head")){command_head_tail(st,root,cwd,arg,0);continue;}
  if(command_is(verb,"tail")){command_head_tail(st,root,cwd,arg,1);continue;}
  if(command_is(verb,"lsblk")){command_lsblk(st);continue;}
  if(command_is(verb,"lsusb")){command_lsusb(st);continue;}
  if(command_is(verb,"echo")){CHAR16 text[160];UINTN n=0;while(arg[n]&&n+2<sizeof(text)/sizeof(text[0])){text[n]=(u8)arg[n];n++;}text[n++]=13;text[n++]=10;text[n]=0;out(st,text);continue;}
  if(command_is(verb,"ls")){command_ls(st,root,cwd,arg);continue;}
  if(command_is(verb,"pwd")){out(st,(CHAR16*)L"/");CHAR16 path[128];UINTN i=0;while(cwd[i]&&i+1<sizeof(path)/sizeof(path[0])){path[i]=(cwd[i]=='\\')?'/':(u8)cwd[i];i++;}path[i]=0;out(st,path);out(st,(CHAR16*)L"\r\n");continue;}
  if(command_is(verb,"cd")){char path[128];if(!arg[0])path[0]=0;else if(!resolve_path(cwd,arg,path,sizeof(path))){out(st,(CHAR16*)L"Caminho muito longo.\r\n");continue;}
   if(path[0]){CHAR16 wide[128];EFI_FILE *dir=0;path_to_efi(path,wide);if(root->Open(root,&dir,wide,1,0)){out(st,(CHAR16*)L"Pasta nao encontrada.\r\n");continue;}int valid=is_directory(dir);dir->Close(dir);if(!valid){out(st,(CHAR16*)L"O caminho nao e uma pasta.\r\n");continue;}}
   UINTN i=0;while(path[i]&&i+1<sizeof(cwd)){cwd[i]=path[i];i++;}cwd[i]=0;continue;
  }
  if(command_is(verb,"mkdir")){int parents=0;if(arg[0]=='-'&&arg[1]=='p'&&(arg[2]==0||arg[2]==' ')){parents=1;arg+=2;while(*arg==' ')arg++;}else if(arg[0]=='-'&&arg[1]=='-'&&arg[2]=='p'&&arg[3]=='a'&&arg[4]=='r'&&arg[5]=='e'&&arg[6]=='n'&&arg[7]=='t'&&arg[8]=='s'&&(arg[9]==0||arg[9]==' ')){parents=1;arg+=9;while(*arg==' ')arg++;}command_mkdir(st,root,cwd,arg,parents);continue;}
  if(command_is(verb,"cat")){command_file(st,root,cwd,arg,0);continue;}
  if(command_is(verb,"touch")){command_file(st,root,cwd,arg,1);continue;}
  if(command_is(verb,"clear")){st->ConOut->ClearScreen(st->ConOut);continue;}
  if(command_is(verb,"exit")){finish_to_os(st,has_return);return 0;}
  if(verb[0])out(st,(CHAR16*)L"Comando desconhecido. Use help.\r\n");
 }
}
EFI_STATUS __attribute__((ms_abi)) efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *st){
 (void)relocation_anchor;
 st->ConOut->ClearScreen(st->ConOut);
 status_line(st,1,(CHAR16*)L"Firmware UEFI x86_64 inicializado");
 status_line(st,0,(CHAR16*)L"Perfil do Lenovo B490 carregado");
 u32 b,c,d,max_standard=cpuid(0,0,&b,&c,&d); char brand[49];
 u32 max_extended=cpuid(0x80000000,0,&b,&c,&d);
 if(max_extended>=0x80000004){for(int leaf=0;leaf<3;leaf++){u32 a=cpuid(0x80000002+leaf,0,&b,&c,&d);u32 vals[4]={a,b,c,d};for(int j=0;j<4;j++)for(int k=0;k<4;k++)brand[leaf*16+j*4+k]=(char)(vals[j]>>(k*8));}}
 else for(int i=0;i<48;i++)brand[i]=' ';
 brand[48]=0;int first=0,last=47;while(first<48&&brand[first]==' ')first++;while(last>=first&&brand[last]==' ')brand[last--]=0;for(int i=0;i<49;i++)cpu_brand[i]=brand[i];
 u32 sig=cpuid(1,0,&b,&c,&d);u32 fam=(sig>>8)&15,model=(sig>>4)&15;if(fam==15)fam+=(sig>>20)&255;if(fam==6||fam==15)model|=((sig>>16)&15)<<4;
 status_line(st,0,(CHAR16*)L"Processador identificado via CPUID");
 status_line(st,0,(CHAR16*)L"Familia e modelo do processador lidos");
 u32 cores=1;if(max_standard>=4){u32 eax=cpuid(4,0,&b,&c,&d);cores=((eax>>26)&63)+1;}cpu_cores=cores;
 status_line(st,0,(CHAR16*)L"Nucleos fisicos contados");
 u64 ram=memory_mib(st);memory_total_mib=ram;EFI_TIME boot_time={0};EFI_STATUS (__attribute__((ms_abi)) *get_time)(EFI_TIME*,void*)=((void**)st->RuntimeServices)[3];if(!get_time(&boot_time,0))boot_epoch=epoch_seconds(&boot_time);status_line(st,0,(CHAR16*)L"Mapa de memoria UEFI consultado");
 EFI_GOP *gop=get_gop(st);u32 width=0,height=0;if(gop&&gop->Mode&&gop->Mode->Info){width=gop->Mode->Info->HorizontalResolution;height=gop->Mode->Info->VerticalResolution;}
 status_line(st,0,(CHAR16*)L"Modo grafico e resolucao consultados");
 status_line(st,0,(CHAR16*)L"Teclado UEFI pronto para entrada");
 EFI_STATUS (__attribute__((ms_abi)) *hp)(EFI_HANDLE,EFI_GUID*,void**)=((void**)st->BootServices)[3+16];EFI_LOADED_IMAGE *li=0;EFI_FILE *root=0,*f=0;
 EFI_STATUS status=hp(image,&loaded_guid,(void**)&li);if(status){OUT("[FAIL ] Dispositivo de boot indisponivel\r\n");show_status(st->ConOut,status);return status;}
 status=find_log_volume(st,&root);if(status){OUT("[FAIL ] Particao de dados UNIOS nao encontrada\r\n");show_status(st->ConOut,status);return status;}
 status_line(st,0,(CHAR16*)L"Particao de dados UNIOS encontrada");
 put("UniOS - caderno de bordo\r\n========================\r\nMaquina: Lenovo B490 (37722QP)\r\nCPU: ");put(brand+first);put("\r\nFamilia/modelo CPUID: ");hex32((fam<<16)|model);put("\r\nNucleos fisicos: ");put_dec(cores);put("\r\nMemoria no mapa UEFI: ");put_dec(ram);put(" MiB\r\nResolucao UEFI: ");put_dec(width);put(" x ");put_dec(height);put("\r\nArquitetura: x86_64 UEFI\r\nFirmware: Lenovo H1ET73WW (1.16)\r\n\r\nUniOS e um mini-projeto experimental.\r\n");
 {static CHAR16 path[]={'U','N','I','O','S','\\','L','O','G','.','T','X','T',0};status=root->Open(root,&f,path,0x8000000000000003ULL,0x20ULL);}
 if(status){status_line(st,0,(CHAR16*)L"LOG.TXT nao salvo (midia somente leitura)");}
 else{
  UINTN n=pos;status=f->Write(f,&n,report);f->Flush(f);f->Close(f);
  if(status||n!=pos)status_line(st,0,(CHAR16*)L"LOG.TXT nao salvo (midia somente leitura)");
  else status_line(st,0,(CHAR16*)L"LOG.TXT atualizado no volume UNIOS");
 }
 u16 return_id=0;int has_return=find_return_boot_option(st,&return_id);
 st->ConOut->ClearScreen(st->ConOut);
 UINTN moon_lines=draw_moon_text(st,root);
 st->ConOut->SetCursorPosition(st->ConOut,0,moon_lines);
 st->ConOut->SetAttribute(st->ConOut,0x0d);OUT("BOAS-VINDAS AO UniOS\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x0b);OUT("Um universo de possibilidades\r\n\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x0e);OUT("Acesso ao sistema\r\n\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x07);
 CHAR16 shell_user[32]={0};if(!profile_wizard(st,root,shell_user,32)){OUT("Acesso negado. Encerrando o UniOS.\r\n");finish_to_os(st,has_return);return 0;}
 OUT("\r\nDigite help para ver os comandos disponiveis.\r\n");
 shell(st,root,shell_user,has_return);
 return 0;
}
