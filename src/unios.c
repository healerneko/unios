/* UniOS: tiny UEFI hardware postcard for the Lenovo B490. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef unsigned long long UINTN;
typedef u16 CHAR16;
typedef u64 EFI_STATUS;
typedef void *EFI_HANDLE;
typedef struct { u32 a; u16 b, c; u8 d[8]; } EFI_GUID;
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
 u64 Revision; EFI_STATUS (__attribute__((ms_abi)) *Open)(EFI_FILE*,EFI_FILE**,CHAR16*,u64,u64); EFI_STATUS (__attribute__((ms_abi)) *Close)(EFI_FILE*); void *Delete; EFI_STATUS (__attribute__((ms_abi)) *Read)(EFI_FILE*,UINTN*,void*);
 EFI_STATUS (__attribute__((ms_abi)) *Write)(EFI_FILE*,UINTN*,void*); void *GetPosition; void *SetPosition;
 EFI_STATUS (__attribute__((ms_abi)) *GetInfo)(EFI_FILE*,EFI_GUID*,UINTN*,void*); void *SetInfo; EFI_STATUS (__attribute__((ms_abi)) *Flush)(EFI_FILE*);
};
typedef struct { void *Revision; EFI_STATUS (__attribute__((ms_abi)) *OpenVolume)(void*,EFI_FILE**); } EFI_SIMPLE_FS;
typedef struct { u32 Revision; void *ParentHandle; void *SystemTable; EFI_HANDLE DeviceHandle; void *FilePath; void *Reserved; u32 LoadOptionsSize; void *LoadOptions; void *ImageBase; u64 ImageSize; u32 ImageCodeType, ImageDataType; void *Unload; } EFI_LOADED_IMAGE;
static EFI_GUID loaded_guid={0x5b1b31a1,0x9562,0x11d2,{0x8e,0x3f,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static EFI_GUID fs_guid={0x964e5b22,0x6459,0x11d2,{0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}};
static EFI_GUID global_guid={0x8be4df61,0x93ca,0x11d2,{0xaa,0x0d,0x00,0xe0,0x98,0x03,0x2b,0x8c}};
static EFI_GUID gop_guid={0x9042a9de,0x23dc,0x4a38,{0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}};
static CHAR16 fail_open[] = {'E','r','r','o',' ','a','o',' ','c','r','i','a','r',' ','U','N','I','O','S','\\','L','O','G','.','T','X','T','.','\r','\n',0};
static CHAR16 fail_write[] = {'E','r','r','o',' ','a','o',' ','e','s','c','r','e','v','e','r',' ','o',' ','l','o','g','.','\r','\n',0};
EFI_STATUS __attribute__((ms_abi)) efi_main(EFI_HANDLE, EFI_SYSTEM_TABLE *);
/* Gera uma entrada .reloc para o carregador UEFI poder mover o app. */
static void * volatile relocation_anchor = (void *)&efi_main;
static CHAR16 code_line[]={'E','F','I',' ','s','t','a','t','u','s',':',' ','0','0','0','0','0','0','0','0','0','0','0','0','0','0','\r','\n',0};
static void show_status(EFI_TEXT_OUT *out, EFI_STATUS status){ const char *h="0123456789ABCDEF"; for(int i=0;i<16;i++) code_line[11+i]=(CHAR16)h[(status>>((15-i)*4))&15]; out->OutputString(out,code_line); }
static char report[768];
static unsigned pos;
static EFI_PIXEL moon_art[470*300];
static void out(EFI_SYSTEM_TABLE *st,const CHAR16 *s){st->ConOut->OutputString(st->ConOut,(CHAR16*)s);}
static void stall(EFI_SYSTEM_TABLE *st,UINTN us){EFI_STATUS (__attribute__((ms_abi)) *pause)(UINTN)=((void**)st->BootServices)[3+28];pause(us);}
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
static void draw_moon_text(EFI_SYSTEM_TABLE *st){
 /* Lua crescente em ASCII: funciona mesmo quando o GOP grafico do firmware falha. */
 st->ConOut->SetAttribute(st->ConOut,0x0d);
 out(st,(CHAR16*)L"                  *\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x0f);
 for(int row=-4;row<=4;row++){
  int y=row*2;
  out(st,(CHAR16*)L"          ");
  for(int x=-8;x<=8;x++){
   int outer=x*x+y*y<=64;
   int shadow=(x+4)*(x+4)+y*y<=49;
   CHAR16 pixel=(outer&&!shadow)?'@':' ';
   CHAR16 cell[2]={pixel,0};out(st,cell);
  }
  if(row==-2||row==2){st->ConOut->SetAttribute(st->ConOut,0x0d);out(st,(CHAR16*)L"  *");st->ConOut->SetAttribute(st->ConOut,0x0f);}
  out(st,(CHAR16*)L"\r\n");
 }
 st->ConOut->SetAttribute(st->ConOut,0x0d);
 out(st,(CHAR16*)L"              *\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x07);
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
 const char *tail="\r\nSenha=campo demonstrativo; nao armazenada\r\nAutenticacao=nao implementada\r\n";while(*tail)text[p++]=*tail++;
 static CHAR16 path[]={'U','N','I','O','S','\\','P','R','O','F','I','L','E','.','T','X','T',0};EFI_FILE *f=0;
 if(root->Open(root,&f,path,0x8000000000000003ULL,0x20ULL))return 0;
 UINTN n=p;EFI_STATUS status=f->Write(f,&n,text);f->Flush(f);f->Close(f);return !status&&n==p;
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
static void profile_wizard(EFI_SYSTEM_TABLE *st,EFI_FILE *root,CHAR16 *shell_user,UINTN shell_user_size){
 if(profile_exists(root)){if(!load_profile_user(root,shell_user,shell_user_size)){const CHAR16 fallback[]=L"usuario";for(UINTN i=0;i<sizeof(fallback)/2;i++)shell_user[i]=fallback[i];}return;}
 CHAR16 name[64]={0},password[64]={0},user[32]={0};
 OUT("Primeira configuracao do perfil UniOS\r\n");
 read_field(st,(CHAR16*)L"Nome: ",name,64,0);
 read_field(st,(CHAR16*)L"Senha (demonstracao): ",password,64,1);
 read_field(st,(CHAR16*)L"Usuario: ",user,32,0);
 if(save_profile(root,name,user)){OUT("Perfil salvo em UNIOS\\PROFILE.TXT.\r\n");UINTN i=0;while(user[i]&&i+1<shell_user_size){shell_user[i]=user[i];i++;}shell_user[i]=0;}
 else OUT("Nao consegui salvar o perfil.\r\n");
 for(UINTN i=0;i<64;i++)password[i]=0;
 OUT("A senha nao foi armazenada; autenticacao real vem com o kernel.\r\n");
}
static void show_info(EFI_SYSTEM_TABLE *st){CHAR16 text[800];for(UINTN i=0;i<pos;i++)text[i]=(u8)report[i];text[pos]=0;out(st,text);}
static int command_is(const char *command,const char *wanted){while(*command&&*wanted&&*command==*wanted){command++;wanted++;}return !*command&&!*wanted;}
static void prompt(EFI_SYSTEM_TABLE *st,CHAR16 *user){
 st->ConOut->SetAttribute(st->ConOut,0x0a);out(st,user);
 st->ConOut->SetAttribute(st->ConOut,0x0b);out(st,(CHAR16*)L"@UniOS");
 st->ConOut->SetAttribute(st->ConOut,0x0d);out(st,(CHAR16*)L"~");
 st->ConOut->SetAttribute(st->ConOut,0x0a);out(st,(CHAR16*)L"$ ");
 st->ConOut->SetAttribute(st->ConOut,0x07);
}
static int shell(EFI_SYSTEM_TABLE *st,CHAR16 *user,int has_return){
 EFI_TEXT_IN *in=st->ConIn;EFI_INPUT_KEY key;UINTN index=0;void *event=in->WaitForKey;
 EFI_STATUS (__attribute__((ms_abi)) *wait)(UINTN,void**,UINTN*)=((void**)st->BootServices)[3+9];
 char command[64];
 for(;;){UINTN length=0;command[0]=0;prompt(st,user);
  for(;;){if(wait(1,&event,&index)||in->ReadKeyStroke(in,&key))continue;
   if(key.UnicodeChar==13){command[length]=0;out(st,(CHAR16*)L"\r\n");break;}
   if(key.UnicodeChar==8){if(length){length--;command[length]=0;out(st,(CHAR16*)L"\b \b");}continue;}
   if(key.UnicodeChar>=32&&key.UnicodeChar<127&&length+1<sizeof(command)){command[length++]=(char)key.UnicodeChar;command[length]=0;CHAR16 echo[2]={(CHAR16)key.UnicodeChar,0};out(st,echo);}
  }
  if(command_is(command,"info")){show_info(st);continue;}
  if(command_is(command,"exit")){finish_to_os(st,has_return);return 0;}
  if(command[0])out(st,(CHAR16*)L"Comando desconhecido. Use info ou exit.\r\n");
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
 brand[48]=0;int first=0,last=47;while(first<48&&brand[first]==' ')first++;while(last>=first&&brand[last]==' ')brand[last--]=0;
 u32 sig=cpuid(1,0,&b,&c,&d);u32 fam=(sig>>8)&15,model=(sig>>4)&15;if(fam==15)fam+=(sig>>20)&255;if(fam==6||fam==15)model|=((sig>>16)&15)<<4;
 status_line(st,0,(CHAR16*)L"Processador identificado via CPUID");
 status_line(st,0,(CHAR16*)L"Familia e modelo do processador lidos");
 u32 cores=1;if(max_standard>=4){u32 eax=cpuid(4,0,&b,&c,&d);cores=((eax>>26)&63)+1;}
 status_line(st,0,(CHAR16*)L"Nucleos fisicos contados");
 u64 ram=memory_mib(st);status_line(st,0,(CHAR16*)L"Mapa de memoria UEFI consultado");
 EFI_GOP *gop=get_gop(st);u32 width=0,height=0;if(gop&&gop->Mode&&gop->Mode->Info){width=gop->Mode->Info->HorizontalResolution;height=gop->Mode->Info->VerticalResolution;}
 status_line(st,0,(CHAR16*)L"Modo grafico e resolucao consultados");
 status_line(st,0,(CHAR16*)L"Teclado UEFI pronto para entrada");
 EFI_STATUS (__attribute__((ms_abi)) *hp)(EFI_HANDLE,EFI_GUID*,void**)=((void**)st->BootServices)[3+16];EFI_LOADED_IMAGE *li=0;EFI_FILE *root=0,*f=0;
 EFI_STATUS status=hp(image,&loaded_guid,(void**)&li);if(status){OUT("[FAIL ] Dispositivo de boot indisponivel\r\n");show_status(st->ConOut,status);return status;}
 status=find_log_volume(st,&root);if(status){OUT("[FAIL ] Particao de dados UNIOS nao encontrada\r\n");show_status(st->ConOut,status);return status;}
 status_line(st,0,(CHAR16*)L"Particao de dados UNIOS encontrada");
 put("UniOS - caderno de bordo\r\n========================\r\nMaquina: Lenovo B490 (37722QP)\r\nCPU: ");put(brand+first);put("\r\nFamilia/modelo CPUID: ");hex32((fam<<16)|model);put("\r\nNucleos fisicos: ");put_dec(cores);put("\r\nMemoria no mapa UEFI: ");put_dec(ram);put(" MiB\r\nResolucao UEFI: ");put_dec(width);put(" x ");put_dec(height);put("\r\nArquitetura: x86_64 UEFI\r\nFirmware: Lenovo H1ET73WW (1.16)\r\n\r\nUniOS e um mini-projeto experimental.\r\n");
 {static CHAR16 path[]={'U','N','I','O','S','\\','L','O','G','.','T','X','T',0};status=root->Open(root,&f,path,0x8000000000000003ULL,0x20ULL);}
 if(status){st->ConOut->OutputString(st->ConOut,fail_open);show_status(st->ConOut,status);return status;}
 {UINTN n=pos;status=f->Write(f,&n,report);if(status||n!=pos){st->ConOut->OutputString(st->ConOut,fail_write);show_status(st->ConOut,status);return status?status:1;}}
 f->Flush(f);f->Close(f);
 status_line(st,0,(CHAR16*)L"LOG.TXT atualizado no volume UNIOS");
 u16 return_id=0;int has_return=find_return_boot_option(st,&return_id);
 st->ConOut->ClearScreen(st->ConOut);
 draw_moon_text(st);
 st->ConOut->SetCursorPosition(st->ConOut,0,11);
 st->ConOut->SetAttribute(st->ConOut,0x0d);OUT("BOAS-VINDAS AO UniOS\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x0b);OUT("Um universo de possibilidades\r\n\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x0e);OUT("Primeira configuracao do sistema\r\n\r\n");
 st->ConOut->SetAttribute(st->ConOut,0x07);
 CHAR16 shell_user[32]={0};profile_wizard(st,root,shell_user,32);
 OUT("\r\nComandos disponiveis: info, exit\r\n");
 shell(st,shell_user,has_return);
 return 0;
}
