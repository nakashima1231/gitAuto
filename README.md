
# gitAuto

Utilitário de linha de comando em C que automatiza o fluxo básico do Git: `add → commit → push` em um único comando.

----------

## Compilação

**Pré-requisito:** compilador GCC instalado e Git disponível no PATH.

```bash
gcc gitAuto.c -o gitAuto

```

No Windows, o executável gerado será `gitAuto.exe`.

----------

## Uso

```
gitAuto <mensagem>
gitAuto -m <mensagem>
gitAuto --help

```

Argumento

Descrição

`<mensagem>`

Mensagem do commit (obrigatória)

`-m <mensagem>`

Forma alternativa com flag explícita

`--help`

Exibe o menu de ajuda

----------

## Exemplos

```bash
# Sem flag
.\gitAuto.exe "corrigindo bug no login"

# Com flag -m
.\gitAuto.exe -m "adicionando validação de formulário"

# Ajuda
.\gitAuto.exe --help

```

----------

## Como funciona

O programa executa as três etapas sequencialmente e para imediatamente se alguma falhar:

```
[1/3] git add .
[2/3] git commit -m "<mensagem>"
[3/3] git push origin <branch-atual>

```

A branch é detectada automaticamente via `git branch --show-current`. Se não for possível detectar, usa `main` como fallback.

----------

## Saída esperada

```
[1/3] Adicionando arquivos...
[OK] Arquivos adicionados!
[2/3] Commitando...
[INFO] Commit: corrigindo bug no login
[OK] Commit realizado!
[3/3] Enviando para main...
[OK] Codigo enviado com sucesso!

```

Erros são exibidos em vermelho com indicação da etapa que falhou.

----------

## Limitações conhecidas

-   Funciona apenas com o remote `origin`
-   Não exibe o diff antes de adicionar os arquivos
-   Cores ANSI podem não funcionar corretamente no Prompt de Comando clássico do Windows (funciona no PowerShell e terminais modernos)

----------

## Melhorias futuras

### Funcionalidades planejadas

-   [ ] **Modo interativo** — se nenhuma mensagem for passada, solicitar via `stdin` ao invés de retornar erro
-   [ ] **Suporte a remote customizado** — flag `-r <remote>` para substituir `origin` (ex: `gitAuto -r upstream "fix"`)
-   [ ] **Seleção de branch** — flag `-b <branch>` para fazer push em uma branch diferente da atual

### Sugestões de evolução

-   [ ] **Validação de mensagem de commit** — avisar se a mensagem for muito curta (ex: menos de 5 caracteres) ou se não seguir nenhuma convenção (Conventional Commits: `feat:`, `fix:`, `docs:` etc.)
-   [ ] **Dry run** — flag `--dry-run` que exibe os comandos que seriam executados sem de fato rodá-los; útil para revisar antes de enviar
-   [ ] **Preview do `git status`** — mostrar quais arquivos serão adicionados antes de executar o `add`, pedindo confirmação do usuário
-   [ ] **Arquivo de configuração** — suporte a um `~/.gitautorc` com preferências padrão (remote, branch padrão, formato de mensagem)
-   [ ] **Verificação de conflitos** — rodar `git fetch` antes do push e avisar se a branch remota estiver à frente, evitando erros de rejected push
-   [ ] **Log local** — registrar em um arquivo `.gitauto.log` o histórico de commits feitos pelo utilitário com timestamp

----------

## Estrutura do projeto

```
gitAuto/
├── gitAuto.c       # Código-fonte
```
----------

## Autor
Gabriel Makiyama Nakashima

gabrielmnakashima2@gmail.com

Desenvolvido como utilitário pessoal de produtividade.

![Makoto nijima de persona 5 Royal](https://media1.tenor.com/m/ySbYADc1H8MAAAAC/makoto-niijima-persona-5.gif)

