# UniOS

Projeto experimental UEFI para Lenovo B490 e virtualização em UEFI/OVMF.

## Comandos

O shell oferece 25 comandos sem autenticação: `info`, `ls`, `cd`, `pwd`, `mkdir`, `cat`, `touch`, `clear`, `echo`, `whoami`, `uname`, `date`, `uptime`, `free`, `cpuinfo`, `meminfo`, `lsblk`, `lsusb`, `df`, `history`, `stat`, `wc`, `head`, `tail` e `exit`. `help` mostra a lista resumida.

Há também 25 operações atrás de `sudo` (cada chamada pede a senha): `passwd`, `mkdir`, `touch`, `rm`, `rmdir`, `cp`, `mv`, `write`, `append`, `truncate`, `clearlog`, `reboot`, `poweroff`, `info`, `ls`, `cat`, `stat`, `wc`, `head`, `tail`, `lsblk`, `lsusb`, `df`, `cpuinfo` e `meminfo`. As consultas repetidas com `sudo` exigem senha, mas não ganham acesso extra no modelo atual.

O prompt mostra a pasta atual (por exemplo, `usuario@UniOS:~/Downloads$`). `ls`, `cd`, `pwd` e `cat` trabalham no volume UNIOS; `ls` oculta `.` e `..`, como no uso padrão. `mkdir` aceita `-p` para criar também pastas intermediárias; `mkdir` e `touch` criam itens quando a mídia permite escrita. `lsblk` e `lsusb` mostram os dispositivos que o firmware UEFI expõe; `head` e `tail` limitam a leitura a arquivos de até 8 KiB nesta versão. No ISO, que é somente leitura, comandos de gravação podem falhar; no pendrive podem gravar no volume de dados.

## Imagens

Rode `./build.sh` para compilar as duas opções:

- `build/unios.iso`: CD UEFI para Boxes. Configure o firmware da VM como OVMF/UEFI. Perfil e log não persistem no ISO.
- `build/unios.img`: imagem USB de 256 MiB, com partição EFI e volume FAT32 UNIOS gravável.

Na primeira configuração, o UniOS pede nome, usuário e senha duas vezes. Em mídia gravável, salva salt e hash PBKDF2-SHA-256 em `UNIOS/AUTH.TXT`; nos próximos boots pede a senha. Perfis antigos que ainda não têm hash pedem para cadastrar uma senha nova. No ISO somente leitura, a senha vale apenas durante a sessão. `sudo passwd` pede a senha atual e permite trocá-la. `sudo write <arquivo> <texto>` substitui o conteúdo e `sudo append <arquivo> <texto>` acrescenta texto ao arquivo.

Autenticação e `sudo` são controles internos do aplicativo UEFI; ainda não isolam arquivos contra alguém que possa editar a mídia ou substituir o programa. Esse shell UEFI não tem rede. Para usar `ping` e `wget`, inicialize a edição Linux Live abaixo.

## Etapa 3: protótipo de kernel

`./build-stage3.sh` gera `build/unios-stage3.iso` e `build/unios-kernel.elf`. Essa ISO experimental usa GRUB/Multiboot2 para iniciar nosso protótipo x86_64; ele desenha a tela UniOS e para. Ainda não tem gerenciamento de memória, teclado, armazenamento ou rede.

## UniOS Linux Live

`./build-linux-live.sh` gera `build/unios-linux.iso` e `build/unios-linux.img`. Essa edição usa o kernel CachyOS instalado no computador durante a compilação e inclui drivers para ancoragem USB RNDIS, redes Intel E1000 e RTL8139 do QEMU, armazenamento USB e FAT32. Traz shell BusyBox, `ping`, DHCP e GNU `wget` com HTTPS. Não precisa de `sudo` no shell Live, que roda como root.

O root da edição Live fica na RAM, então arquivos em `/tmp` desaparecem ao reiniciar; o boot grava `UNIOS.LOG` na partição FAT da imagem USB. A edição foi iniciada por UEFI no QEMU e nela `ping` para `1.1.1.1` e `wget https://example.com` funcionaram usando a placa virtual E1000. O teste não passou o celular diretamente para o QEMU; o suporte RNDIS está incluído para testar no Lenovo com o celular conectado por USB.
